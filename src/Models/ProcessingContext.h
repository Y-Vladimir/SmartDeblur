#ifndef PROCESSINGCONTEXT_H
#define PROCESSINGCONTEXT_H

#include "ImageUtils.h"

class ProcessingContext {

public:
    QImage *inputImage;
    QImage *outputImage;
    double *inputImageMatrix;
    double *outputImageMatrix;
    fftw_complex *inputImageFFT;
    fftw_complex *outputImageFFT;
    fftw_complex *kernelFFT;
    int width;
    int height;
    Blur *blur;
};

#endif // PROCESSINGCONTEXT_H
