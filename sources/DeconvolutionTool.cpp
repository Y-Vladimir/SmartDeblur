#include "DeconvolutionTool.h"



DeconvolutionTool::DeconvolutionTool(QObject* parent):QObject(parent) {
    // Init MultiThreading
    threadsCount = QThread::idealThreadCount() > 0 ? QThread::idealThreadCount() : 2;
    qDebug("Init Multi-Threading with threads count: %d", threadsCount);
    fftw_plan_with_nthreads(threadsCount);

    inputMatrix     = NULL;
    inputMatrix     = NULL;
    outputMatrix    = NULL;
    kernelMatrix    = NULL;
    inputMatrixFFT  = NULL;
    kernelMatrixFFT = NULL;

    forwardImagePlan  = NULL;
    forwardKernelPlan = NULL;
    backwardImagePlan = NULL;
}

void DeconvolutionTool::initFFT(const QImage *inputImage) {
    QTime time;
    time.start();

    // Read image size
    width = inputImage->width();
    height = inputImage->height();

    // Destroy FFTW objects
    fftw_destroy_plan(forwardImagePlan);
    fftw_destroy_plan(forwardKernelPlan);
    fftw_destroy_plan(backwardImagePlan);
    fftw_free(inputMatrix);
    fftw_free(outputMatrix);
    fftw_free(kernelMatrix);
    fftw_free(inputMatrixFFT);
    fftw_free(kernelMatrixFFT);

    // Init FFTW structures with given size
    inputMatrix     = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * width * height);
    outputMatrix    = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * width * height);
    kernelMatrix    = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * width * height);
    inputMatrixFFT  = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * width * height);
    kernelMatrixFFT = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * width * height);

    // Init FFTW plan to optimize speed - init once and use many times
    // Column-major Format used. When creating the plan, simply pass
    // the dimensions of the array to the planner in reverse order (width, height..) -> (height, width...)
    forwardImagePlan  = fftw_plan_dft_2d(height, width, inputMatrix, inputMatrixFFT, FFTW_FORWARD, FFTW_ESTIMATE);
    forwardKernelPlan = fftw_plan_dft_2d(height, width, kernelMatrix, kernelMatrixFFT, FFTW_FORWARD, FFTW_ESTIMATE);
    backwardImagePlan = fftw_plan_dft_2d(height, width, inputMatrixFFT, outputMatrix, FFTW_BACKWARD, FFTW_ESTIMATE);


    qDebug("initFFT: %d ms", time.elapsed());
}

void DeconvolutionTool::doDeconvolution(const QImage *inputImage, QImage *outputImage, const Blur* blur) {
    // Create kernel
    buildKernel(kernelMatrix, width, height, blur);
    fftw_execute(forwardKernelPlan);

    if (blur->previewMode) {
        doDeconvolutionForChannel(inputImage, outputImage, kernelMatrixFFT, width, height, blur->radius, blur->PSNR, GRAY);
    } else {
        emit progressEvent(10);
        doDeconvolutionForChannel(inputImage, outputImage, kernelMatrixFFT, width, height, blur->radius, blur->PSNR, RED);
        emit progressEvent(40);
        doDeconvolutionForChannel(inputImage, outputImage, kernelMatrixFFT, width, height, blur->radius, blur->PSNR, GREEN);
        emit progressEvent(70);
        doDeconvolutionForChannel(inputImage, outputImage, kernelMatrixFFT, width, height, blur->radius, blur->PSNR, BLUE);
        emit progressEvent(99);
    }
}

int DeconvolutionTool::getThreadsCount() {
    return threadsCount;
}

void DeconvolutionTool::doDeconvolutionForChannel(const QImage *inputImage, QImage *outputImage, const fftw_complex *kernelMatrixFFT,
                                                  const int width, const int height, const double kernelRadius, const double PSNR, const CurrentChannel channel) {
    // Read given channel
    ImageUtils::fillInputMatrix(inputMatrix, inputImage, width, height, channel);
    fftw_execute(forwardImagePlan);

    if (channel != GRAY) {
        // Borders processing to prevent ring effect
        multiplayFFTs(inputMatrixFFT, kernelMatrixFFT, inputMatrixFFT, width, height);
        fftw_execute(backwardImagePlan);
        for (int y = 0; y<height; y++) {
            for (int x = 0; x<width; x++) {
                int index = y*width+x;
                if (x < kernelRadius || y < kernelRadius || x > width - kernelRadius ||y > height - kernelRadius) {
                    inputMatrix[index][0] = outputMatrix[y*width + x][0] / (width * height);
                }

                inputMatrix[index][0] = centerFFTKoef(x, y)*fabs(inputMatrix[index][0]);
                inputMatrix[index][1] = 0;
            }
        }
        fftw_execute(forwardImagePlan);
    }

    // Deconvolution in the Frequency domain
    deconvolutionByWiener(kernelMatrixFFT, inputMatrixFFT, inputMatrixFFT, width, height, PSNR);

    // Inverse FFT to return to the Time domain
    fftw_execute(backwardImagePlan);
    ImageUtils::fillOutputImage(inputImage, outputMatrix, outputImage, width, height, channel);
}

void DeconvolutionTool::multiplayFFTs(const fftw_complex *firstFFT, const fftw_complex *secondFFT, fftw_complex *outFFT,  const int width, const int height) {
    for (int y = 0; y<height; y++) {
        for (int x = 0; x<width; x++) {
            int index = y*width + x;
            double value = centerFFTKoef(x, y) * secondFFT[index][0];
            outFFT[index][0] *= value;
            outFFT[index][1] *= value;
        }
    }
}

void DeconvolutionTool::deconvolutionByWiener(const fftw_complex *kernelFFT, const fftw_complex *inImageFFT, fftw_complex *outImageFFT, const int WIDTH, const int HEIGHT, const double K) {
    for(int y=0; y<HEIGHT; y++) {
        for(int x=0; x<WIDTH; x++) {
            int index = y*WIDTH+x;
            double energyValue = pow(kernelFFT[index][0], 2) + pow(kernelFFT[index][1], 2);
            double wienerValue = energyValue / (kernelFFT[index][0] * (energyValue + K));
            wienerValue *= centerFFTKoef(x, y);
            outImageFFT[index][0] = wienerValue * inImageFFT[index][0];
            outImageFFT[index][1] = wienerValue * inImageFFT[index][1];
        }
    }
}

void DeconvolutionTool::buildKernel(fftw_complex* outKernelFFT, const int WIDTH, const int HEIGHT, const Blur* blur) {
    QImage* kernelImage;

    if (blur->getName() == "FocusBlur") {
        kernelImage = ImageUtils::buildKernelImage((FocusBlur*)blur);
    } else if (blur->getName() == "MotionBlur") {
        kernelImage = ImageUtils::buildKernelImage((MotionBlur*)blur);
    }
    int size = kernelImage->width();

    //kernelImage->save("C:/Projects/KernelImage.png");

    // Fill kernel
    double sumKernelElements = 0;
    for (int y = 0; y<HEIGHT; y++) {
        for (int x = 0; x<WIDTH; x++) {
            int index = y*WIDTH + x;
            int value = 0;
            // if we are in the kernel area (of small kernelImage), then take pixel values. Otherwise keep 0
            if (abs(x-WIDTH/2)<(size-2)/2 && abs(y-HEIGHT/2)<(size-2)/2) {
                int xLocal = x-(WIDTH-size)/2;
                int yLocal = y-(HEIGHT-size)/2;
                value = qRed(kernelImage->pixel(xLocal,yLocal))* centerFFTKoef(x, y);;
            }

            outKernelFFT[index][0] = value;
            sumKernelElements += abs(value);
            outKernelFFT[index][1] = 0;
        }
    }

    delete(kernelImage);

    // Zero-protection
    if (sumKernelElements==0) {
        sumKernelElements = 1;
    }

    // Normalize
    double k = 1/sumKernelElements;
    for (int i=0; i<WIDTH*HEIGHT; i++) {
        outKernelFFT[i][0] *= k;
    }
}

void DeconvolutionTool::visualizeFFT(fftw_complex* fft, const int WIDTH, const int HEIGHT, QString path) {
    QImage visualImage(WIDTH, HEIGHT, QImage::Format_RGB32);

    // Find maximum
    float maxAmpl = 0;
    float curAmpl = 0;
    for (int i=0; i<WIDTH*HEIGHT; i++) {
        // Extract Amplitude
        curAmpl = sqrt(pow(fft[i][0], 2) + pow(fft[i][1], 2));
        curAmpl = log(1 + curAmpl);
        if (curAmpl > maxAmpl) {
            maxAmpl = curAmpl;
        }
    }

    // Build image
    for(int y=0; y<HEIGHT; y++) {
        for(int x=0; x<WIDTH; x++) {
            // Normalize
            curAmpl = sqrt(pow(fft[y*WIDTH+x][0], 2) + pow(fft[y*WIDTH+x][1], 2));
            // curAmpl = fft[i*width+j].r;
            // Log scale
            curAmpl = 255 * log(1 + curAmpl) / maxAmpl;
            visualImage.setPixel(x, y, qRgb(curAmpl, curAmpl, curAmpl));
        }
    }

    visualImage.save(path);
}


