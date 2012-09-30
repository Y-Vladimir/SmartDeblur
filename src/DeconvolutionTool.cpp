#include "DeconvolutionTool.h"

DeconvolutionTool::DeconvolutionTool(QObject* parent):QObject(parent) {
    // Init MultiThreading
    threadsCount = QThread::idealThreadCount() > 0 ? QThread::idealThreadCount() : 2;
    qDebug("Init Multi-Threading with threads count: %d", threadsCount);
    fftw_plan_with_nthreads(threadsCount);
    tvIterationsCount = 500;
    previewMethod = 0;

    inputImageMatrix = NULL;
    outputImageMatrix = NULL;
    kernelMatrix = NULL;
    laplacianMatrix = NULL;
    outLaplacianMatrix = NULL;

    inputImageFFT = NULL;
    outputImageFFT = NULL;
    kernelFFT = NULL;
    kernelTempFFT = NULL;
    laplacianMatrixFFT = NULL;

    realForwardPlan = NULL;
    realForwardKernelPlan = NULL;
    realBackwardPlan = NULL;
    forwardLaplacianPlan = NULL;
    backwardLaplacianPlan = NULL;
}

DeconvolutionTool::~DeconvolutionTool() {
    removeFFTObjects();
}

void DeconvolutionTool::removeFFTObjects() {
    fftw_free(inputImageMatrix);
    fftw_free(outputImageMatrix);
    fftw_free(kernelMatrix);
    fftw_free(laplacianMatrix);
    fftw_free(outLaplacianMatrix);

    fftw_free(inputImageFFT);
    fftw_free(outputImageFFT);
    fftw_free(kernelFFT);
    fftw_free(kernelTempFFT);
    fftw_free(laplacianMatrixFFT);

    fftw_destroy_plan(realForwardPlan);
    fftw_destroy_plan(realForwardKernelPlan);
    fftw_destroy_plan(realBackwardPlan);
    fftw_destroy_plan(forwardLaplacianPlan);
    fftw_destroy_plan(backwardLaplacianPlan);

    isProcessingCancelled = false;
}

void DeconvolutionTool::initFFT(const QImage *inputImage) {
    removeFFTObjects();
    QTime time;
    time.start();
    QString progressText = "Loading image";
    setProgressInterval(1,100, progressText);

    // Read image size
    width = inputImage->width();
    height = inputImage->height();

    // Init FFTW structures with given size
    inputImageMatrix = (double*) fftw_malloc(sizeof(double) * width * height);
    outputImageMatrix = (double*) fftw_malloc(sizeof(double) * width * height);
    kernelMatrix = (double*) fftw_malloc(sizeof(double) * width * height);
    // kernelTempMatrix = (double*)fftw_malloc(sizeof(double)*width*height);
    laplacianMatrix = (double*) fftw_malloc(sizeof(double) * width * height);
    outLaplacianMatrix = (double*) fftw_malloc(sizeof(double) * width * height);

    inputImageFFT = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (width/2+1) * height);
    outputImageFFT = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (width/2+1) * height);
    kernelFFT = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (width/2+1) * height);
    kernelTempFFT = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (width/2+1) * height);
    laplacianMatrixFFT = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (width/2+1) * height);
    setProgressSubValue(10);

    // Init FFTW plan to optimize speed - init once and use many times
    // Column-major Format used. When creating the plan, simply pass
    // the dimensions of the array to the planner in reverse order (width, height..) -> (height, width...)
    realForwardPlan = fftw_plan_dft_r2c_2d(height, width, inputImageMatrix, inputImageFFT, FFTW_MEASURE);
    setProgressSubValue(30);
    realForwardKernelPlan = fftw_plan_dft_r2c_2d(height, width, kernelMatrix, kernelFFT, FFTW_MEASURE);
    setProgressSubValue(50);
    realBackwardPlan = fftw_plan_dft_c2r_2d(height, width, inputImageFFT, outputImageMatrix, FFTW_MEASURE);
    setProgressSubValue(70);
    QApplication::processEvents();
    forwardLaplacianPlan = fftw_plan_dft_r2c_2d(height, width, laplacianMatrix, laplacianMatrixFFT, FFTW_MEASURE);
    setProgressSubValue(90);
    backwardLaplacianPlan = fftw_plan_dft_c2r_2d(height, width, laplacianMatrixFFT, outLaplacianMatrix, FFTW_MEASURE);
    setProgressSubValue(100);

    qDebug("initFFT: %d ms", time.elapsed());
}

bool DeconvolutionTool::doDeconvolution(QImage *inputImage, QImage *outputImage, Blur* blur) {
    isProcessingCancelled = false;
    // Create kernel
    buildKernel(kernelMatrix, width, height, blur);
    fftw_execute(realForwardKernelPlan);
    // Fill processingContext
    ProcessingContext* processingContext = new ProcessingContext();
    processingContext->inputImage = inputImage;
    processingContext->outputImage = outputImage;
    processingContext->inputImageMatrix = inputImageMatrix;
    processingContext->outputImageMatrix = outputImageMatrix;
    processingContext->kernelFFT = kernelFFT;
    processingContext->width = width;
    processingContext->height = height;
    processingContext->blur = blur;

    if (blur->mode == PREVIEW_GRAY) {
        doDeconvolutionForChannel(processingContext, GRAY);
    } else {
        QString progressText= "High-Quality";
        if (blur->mode == PREVIEW_COLOR) {
            progressText = "Color Preview";
        }
        setProgressInterval(10,40, progressText);
        doDeconvolutionForChannel(processingContext, RED);
        setProgressInterval(40,70, progressText);
        doDeconvolutionForChannel(processingContext, GREEN);
        setProgressInterval(70,100, progressText);
        doDeconvolutionForChannel(processingContext, BLUE);

    }

    delete(processingContext);
    return !isProcessingCancelled;
}

int DeconvolutionTool::getThreadsCount() {
    return threadsCount;
}

void DeconvolutionTool::doDeconvolutionForChannel(ProcessingContext* processingContext, const CurrentChannel channel) {
    if (isProcessingCancelled && processingContext->blur->mode != PREVIEW_GRAY) {
        return;
    }

    double blurRadius = processingContext->blur->radius;
    int width = processingContext->width;
    int height = processingContext->height;
    // Read given channel
    ImageUtils::fillMatrixFromImage(processingContext, channel);
    fftw_execute(realForwardPlan);
    processingContext->inputImageFFT = inputImageFFT;

    // Borders processing to prevent ring effect
    multiplayRealFFTs(inputImageFFT, processingContext->kernelFFT, width/2+1, height);
    fftw_execute(realBackwardPlan);
    for (int y = 0; y<height; y++) {
        for (int x = 0; x<width; x++) {
            int index = y*width+x;
            if (x < blurRadius || y < blurRadius || x > width - blurRadius ||y > height - blurRadius) {
                processingContext->inputImageMatrix[index] = outputImageMatrix[y*width + x] / (width * height);
            }

        }
    }

    if (processingContext->blur->mode != HIGH_QUALITY) {
        // Deconvolution in the Frequency domain
        fftw_execute(realForwardPlan);
        if (previewMethod == 0) {
            deconvolutionByWiener(processingContext);
        } else {
            deconvolutionByTikhonov(processingContext);
        }

        // Inverse FFT to return to the Time domain
        fftw_execute(realBackwardPlan);
    } else {
        deconvolutionByTotalVariationPrior(processingContext);
    }

    // Don't cancel in case of preview
    if (!isProcessingCancelled || processingContext->blur->mode == (PREVIEW_GRAY)) {
        ImageUtils::fillImageFromMatrix(processingContext, channel);
    }
}

void DeconvolutionTool::multiplayRealFFTs(fftw_complex *outFFT, const fftw_complex *kernelFFT, const int width, const int height) {
    for (int y = 0; y<height; y++) {
        for (int x = 0; x<width; x++) {
            int index = y*width + x;
            double value = kernelFFT[index][0];
            outFFT[index][0] *= value;
            outFFT[index][1] *= value;
        }
    }
}

void DeconvolutionTool::cancelProcessing() {
    isProcessingCancelled = true;
}

void DeconvolutionTool::setTVIterationsCount(int value) {
    tvIterationsCount = value;
}

void DeconvolutionTool::setPreviewMethod(int value) {
    previewMethod = value;
}

void DeconvolutionTool::deconvolutionByWiener(ProcessingContext* processingContext) {
    double K = pow(1.07, processingContext->blur->smooth)/10000.0;
    int N = (processingContext->width/2+1) * processingContext->height;
    for(int i=0; i<N; i++) {
        double energyValue = pow(processingContext->kernelFFT[i][0], 2) + pow(processingContext->kernelFFT[i][1], 2);
        double wienerValue = processingContext->kernelFFT[i][0] / (energyValue + K);
        processingContext->inputImageFFT[i][0] = wienerValue * processingContext->inputImageFFT[i][0];
        processingContext->inputImageFFT[i][1] = wienerValue * processingContext->inputImageFFT[i][1];
    }
}

void DeconvolutionTool::deconvolutionByTikhonov(ProcessingContext* processingContext) {
    int width = processingContext->width;
    int height = processingContext->height;

    // Create laplacian
    for(int y=0; y<height; y++) {
        for(int x=0; x<width; x++) {
            int index = y*width+x;
            laplacianMatrix[index] = 0;
        }
    }
    laplacianMatrix[0] = 4;
    laplacianMatrix[1] = -1;
    laplacianMatrix[1*width] = -1;
    laplacianMatrix[width-1] = -1;
    laplacianMatrix[(height-1)*width] = -1;

    fftw_execute(forwardLaplacianPlan);
    double K = pow(1.07, processingContext->blur->smooth)/1000.0;
    int N = (width/2+1) * height;
    for(int index=0; index<N; index++) {
        double energyValue = pow(processingContext->kernelFFT[index][0], 2) + pow(processingContext->kernelFFT[index][1], 2);
        double energyLaplacianValue = pow(laplacianMatrixFFT[index][0], 2) + pow(laplacianMatrixFFT[index][1], 2);
        double tikhonovValue = processingContext->kernelFFT[index][0] / (energyValue + K*energyLaplacianValue);
        processingContext->inputImageFFT[index][0] = tikhonovValue * processingContext->inputImageFFT[index][0];
        processingContext->inputImageFFT[index][1] = tikhonovValue * processingContext->inputImageFFT[index][1];

    }
}

void DeconvolutionTool::deconvolutionByTotalVariationPrior(ProcessingContext* processingContext) {
    if (isProcessingCancelled) {
        return;
    }

    int WIDTH = processingContext->width;
    int HEIGHT = processingContext->height;
    fftw_complex *GradientMatrix = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * WIDTH * HEIGHT);
    double *fTV= (double*) fftw_malloc(sizeof(double) * WIDTH * HEIGHT);

    double k = 1.0/(WIDTH * HEIGHT);
    int k2 = WIDTH * HEIGHT;
    int k3 = (WIDTH/2+1) * HEIGHT;

    // copy blur fft
    for(int i=0; i<k3; i++) {
        kernelTempFFT[i][0] = processingContext->kernelFFT[i][0];
        kernelTempFFT[i][1] = processingContext->kernelFFT[i][1];
    }

    fftw_execute(realForwardKernelPlan);

    double epsilon = 0.004;
    double lambda = pow(1.07, processingContext->blur->smooth)/100000.0;;
    double tau = 1.9 / ( 1 + lambda * 8 / epsilon);

    // Pre-multiply: h*(h*f-y) = h*h*f-y*h, so h*h and y*h we can pre-calculate
    // 1. Calculation y*h convolution using FFT
    for(int y=0; y<HEIGHT; y++) {
        for(int x=0; x<WIDTH; x++) {
            int index = y*WIDTH+x;
            fTV[index] = processingContext->inputImageMatrix[index]/255.0;
            laplacianMatrix[index] = fTV[index];
        }
    }
    fftw_execute(forwardLaplacianPlan);
    multiplayRealFFTs(laplacianMatrixFFT, kernelTempFFT, WIDTH/2+1, HEIGHT);
    fftw_execute(backwardLaplacianPlan);
    for(int y=0; y<HEIGHT; y++) {
        for(int x=0; x<WIDTH; x++) {
            int index = y*WIDTH+x;
            double value = outLaplacianMatrix[index]*k;
            processingContext->inputImageMatrix[index] = value;
        }
    }

    // 2. Calculation h*h
    multiplayRealFFTs(kernelTempFFT, kernelTempFFT, WIDTH/2+1, HEIGHT);

    // Apply iterative gradient descent method
    int niter = tvIterationsCount;
    while (niter > 0) {
        if (isProcessingCancelled) {
            fftw_free(GradientMatrix);
            fftw_free(fTV);
            return;
        }
        if (niter%10==0) {
            setProgressSubValue(100*(tvIterationsCount-niter)/tvIterationsCount);
        }

        QTime timeAll;
        timeAll.start();

        QTime time;
        time.start();

        // Calculation fTV*h convolution using FFT
        for(int y=0; y<HEIGHT; y++) {
            for(int x=0; x<WIDTH; x++) {
                int index = y*WIDTH+x;
                laplacianMatrix[index] = fTV[index];
            }
        }
        fftw_execute(forwardLaplacianPlan);
        multiplayRealFFTs(laplacianMatrixFFT, kernelTempFFT, WIDTH/2+1, HEIGHT);
        fftw_execute(backwardLaplacianPlan);
        int fftTime = time.elapsed();

        double tv = 0;
        double epsilonPow2 = epsilon*epsilon;
        for(int y=0; y<HEIGHT; y++) {
            for(int x=0; x<WIDTH; x++) {
                int index = y*WIDTH+x;
                // build gradient
                double curValue = fTV[index];
                if (y<HEIGHT-1) {
                    GradientMatrix[index][0] = fTV[index+WIDTH] - curValue;
                } else {
                    GradientMatrix[index][0] = 0;
                }

                if (x<WIDTH-1) {
                    GradientMatrix[index][1] = fTV[index+1] - curValue;
                } else {
                    GradientMatrix[index][1] = 0;
                }

                // Calculate d
                double kValue = 1/sqrt(epsilonPow2 + GradientMatrix[index][0]*GradientMatrix[index][0] + GradientMatrix[index][1]*GradientMatrix[index][1]);

                GradientMatrix[index][0] *= kValue;
                GradientMatrix[index][1] *= kValue;

                // Calculate divergence
                double divergenceValue = 0;
                if (y>0 && x>0) {
                    double fx = GradientMatrix[index][0] - GradientMatrix[index-WIDTH][0];
                    double fy = GradientMatrix[index][1] - GradientMatrix[index-1][1];
                    divergenceValue = -(fx+fy);
                }

                // update fTV
                fTV[index] = fTV[index] - tau*(outLaplacianMatrix[index]*k - processingContext->inputImageMatrix[index] + lambda*divergenceValue);
                if (niter==1) {
                    double fTVvalue = 255.0*fTV[index];
                    if (fTVvalue <0) {fTVvalue = 0;}
                    if (fTVvalue >255) {fTVvalue = 255;}
                    processingContext->outputImageMatrix[index] = k2 * fTVvalue;
                }
            }
        }

        //  qDebug("Iteration:%d  tv: %f convolution: %d ms all: %d ms", niter, tv, fftTime, timeAll.elapsed());
        niter--;
    }

    fftw_free(GradientMatrix);
    fftw_free(fTV);
}

void DeconvolutionTool::buildKernel(double* outKernel, const int WIDTH, const int HEIGHT, const Blur* blur) {
    QImage* kernelImage;

    double* kernelTempMatrix = (double*)fftw_malloc(sizeof(double)*WIDTH*HEIGHT);
    if (blur->getName() == "FocusBlur") {
        kernelImage = ImageUtils::buildKernelImage((FocusBlur*)blur);
    } else if (blur->getName() == "MotionBlur") {
        kernelImage = ImageUtils::buildKernelImage((MotionBlur*)blur);
    } else if (blur->getName() == "GaussianBlur") {
        kernelImage = ImageUtils::buildKernelImage((GaussianBlur*)blur);
    }
    int size = kernelImage->width();

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
                value = qRed(kernelImage->pixel(xLocal,yLocal));
            }

            kernelTempMatrix[index] = value;
            sumKernelElements += abs(value);
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
        kernelTempMatrix[i] *= k;
    }

    // Translate kernel, because we don't use centered FFT (by multiply input image on pow(-1,x+y))
    // so we need to translate kernel by width/2 to the left and by height/2 to the up
    for (int y=0; y<HEIGHT; y++) {
        for (int x=0; x<WIDTH; x++) {
            int xTranslated = (x + WIDTH/2) % WIDTH;
            int yTranslated = (y + HEIGHT/2) % HEIGHT;
            outKernel[y*WIDTH + x] = kernelTempMatrix[yTranslated*WIDTH + xTranslated];
        }
    }
    fftw_free(kernelTempMatrix);
}

// Build Laplacian matrix
// [ 0  -1   0]
// [-1   4  -1]
// [ 0  -1   0]
void DeconvolutionTool::buildLaplacian(fftw_complex *outLaplacianFFT, const int WIDTH, const int HEIGHT) {
    for (int y = 0; y<HEIGHT; y++) {
        for (int x = 0; x<WIDTH; x++) {
            int index = y*WIDTH + x;
            int value = 0;
            int xCenter = WIDTH/2;
            int yCenter = HEIGHT/2;
            if (x==xCenter && y==yCenter) {
                value = 4;
            }
            if (abs(xCenter-x)+abs(yCenter-y) == 1) {
                value = -1;
            }

            outLaplacianFFT[index][0] = value;
            outLaplacianFFT[index][1] = 0;
        }
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
            // Log scale
            curAmpl = 255 * log(1 + curAmpl) / maxAmpl;
            visualImage.setPixel(x, y, qRgb(curAmpl, curAmpl, curAmpl));
        }
    }

    visualImage.save(path);
}

void DeconvolutionTool::setProgressInterval(int begin, int end, QString text) {
    if (!isProcessingCancelled) {
        beginCurrentProgress = begin;
        endCurrentProgress = end;
        currentProgressText = text;
        emit progressEvent(begin, text);
    } else {
        emit progressEvent(0, text);
    }
}

void DeconvolutionTool::setProgressSubValue(int percentValue) {
    emit progressEvent(beginCurrentProgress + percentValue*(endCurrentProgress - beginCurrentProgress)/100, currentProgressText);
    QApplication::processEvents();
}




