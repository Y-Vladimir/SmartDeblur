#include "ImageUtils.h"

QImage* ImageUtils::buildKernelImage(const FocusBlur* focusBlur) {
    double radius = focusBlur->radius;
    double edgeFeather = focusBlur->edgeFeather;
    double correctionStrength = focusBlur->correctionStrength;

    // Double radius plus 2*3 pixels to ensure that generated kernel will be fitted inside the image
    int size = 2 * radius + 6;
    size += size%2;

    QImage* kernelImage = new QImage(size, size, QImage::Format_RGB32);
    kernelImage->fill(Qt::black);

    // Prepare painter to have antialiasing and sub-pixel accuracy
    QPainter kernelPainter(kernelImage);
    kernelPainter.setRenderHint(QPainter::Antialiasing);
    kernelPainter.setBrush(QBrush(Qt::white));

    // Draw circle
    kernelPainter.drawEllipse(QPointF(0.5+kernelImage->width()/2.0, 0.5+kernelImage->height()/2.0), radius, radius);
    kernelPainter.end();

    // Draw edge correction - add ring (with radius=kernelRadiaus) blurred by Gauss to the drawed circle
    int center = size/2;
    for (int y = 0; y<size; y++) {
        for (int x = 0; x<size; x++) {
            double dist = sqrt(pow(x-center,2) + pow(y-center,2));
            if (dist <= radius) {
                double mu = radius;
                double sigma = radius*edgeFeather/100;

                // Gaussian normalized by kernelStrength
                double gaussValue = pow(M_E, -pow((dist-mu)/sigma,2)/2);
                gaussValue *= 255*(correctionStrength)/100;

                // Circle pixel value normalized by 1-kernelStrength
                int curValue = qRed(kernelImage->pixel(x,y));
                if (correctionStrength >= 0) {
                    curValue *= (100-correctionStrength)/100;
                }

                // Sum and check
                curValue += gaussValue;
                if (curValue < 0) {
                    curValue = 0;
                }
                if (curValue > 255) {
                    curValue = 255;
                }

                kernelImage->setPixel(x,y,qRgb(curValue, curValue, curValue));
            }
        }
    }


    return kernelImage;
}

QImage *ImageUtils::buildKernelImage(const MotionBlur* motionBlur) {
    // motionLength plus 2*3 pixels to ensure that generated kernel will be fitted inside the image
    double motionLength = motionBlur->radius * 2;
    double motionAngle = motionBlur->angle;

    int size = motionLength + 6;
    size += size%2;

    QImage* kernelImage = new QImage(size, size, QImage::Format_RGB32);
    kernelImage->fill(Qt::black);

    // Prepare painter to have antialiasing and sub-pixel accuracy
    QPainter kernelPainter(kernelImage);
    kernelPainter.setRenderHint(QPainter::Antialiasing);

    // Workarround to have high accuracy, otherwise drawLine method has some micro-mistakes in the rendering
    QPen pen = kernelPainter.pen();
    pen.setColor(Qt::white);
    pen.setWidthF(1.01);
    kernelPainter.setPen(pen);

    double center = 0.5 + size/2;
    double motionAngleRad = M_PI*motionAngle/180;
    QLineF line(center - motionLength*cos(motionAngleRad)/2,
                center - motionLength*sin(motionAngleRad)/2,
                center + motionLength*cos(motionAngleRad)/2,
                center + motionLength*sin(motionAngleRad)/2);
    kernelPainter.drawLine(line);
    kernelPainter.end();

    return kernelImage;
}

void ImageUtils::fillInputMatrix(fftw_complex *inputMatrix, const QImage *inputImage, const int width, const int height, const CurrentChannel channel) {
    for (int y=0; y<height; y++) {
        QRgb *line = (QRgb*)inputImage->constScanLine(y);
        for (int x=0; x<width; x++) {
            int value = 0;
            switch (channel) {
            case RED:   value = qRed(line[x]); break;
            case GREEN: value = qGreen(line[x]); break;
            case BLUE:  value = qBlue(line[x]); break;
            case GRAY:  value = qGray(line[x]); break;
            }
            inputMatrix[y*width + x][0] = centerFFTKoef(x, y) * value;
        }
    }
}

void ImageUtils::fillOutputImage(const QImage *inputImage, const fftw_complex *outputMatrix,  QImage *outputImage, const int width, const int height, const CurrentChannel channel) {
    for (int y = 0; y < height; y++) {
        QRgb *line = (QRgb*) outputImage->scanLine(y);
        for (int x = 0; x < width; x++) {
            double value =  outputMatrix[y*width + x][0] / (width * height);
            value *= centerFFTKoef(x, y);
            value = fabs(value);
            if (value < 0) {
                value = 0;
            }
            if (value > 255) {
                value = 255;
            }

            switch (channel) {
            case RED:   line[x] = qRgb(value, 0, 0); break;
            case GREEN: line[x] = line[x] | qRgb(0, value, 0); break;
            case BLUE:  line[x] = line[x] | qRgb(0, 0, value); break;
            case GRAY:  line[x] = qRgb(value, value, value); break;
            }
        }
    }
}
