#ifndef DECONVOLUTIONTHREAD_H
#define DECONVOLUTIONTHREAD_H

#include <QThread>
#include <QDebug>
#include <QImage>
#include <QPainter>
#include <QTime>
#include <QThread>
#include <QPixmap>
#include <QObject>
#include <time.h>

#ifdef _MSC_VER
#define _USE_MATH_DEFINES
#include <cmath>
#else
#include <math.h>
#endif

#include "ImageUtils.h"
#include "fftw3.h"
#include <typeinfo>


class DeconvolutionTool : public QObject
{
    Q_OBJECT

public:
    DeconvolutionTool(QObject* parent = 0);
    void initFFT(const QImage *inputImage);
    void doDeconvolution(const QImage *inputImage, QImage *outputImage, const Blur *blur);
    int getThreadsCount();

signals:
    void progressEvent(int);

private:
    void visualizeFFT(fftw_complex *fft, const int WIDTH, const int HEIGHT, QString path);
    void multiplayFFTs(const fftw_complex *firstFFT, const fftw_complex *secondFFT, fftw_complex *outFFT,  const int width, const int height);
    void deconvolutionByWiener(const fftw_complex *kernelFFT, const fftw_complex *inImageFFT, fftw_complex *outImageFFT, const int WIDTH, const int HEIGHT, const double K);

    void buildKernel(fftw_complex* outKernelFFT, const int WIDTH, const int HEIGHT, const Blur *blur);
    void doDeconvolutionForChannel(const QImage *inputImage, QImage *outputImage, const fftw_complex *kernelMatrixFFT, const int width, const int height, const double kernelRadius, const double PSNR, const CurrentChannel channel);

    int width, height;
    int threadsCount;

    fftw_complex *inputMatrix;
    fftw_complex *outputMatrix;
    fftw_complex *kernelMatrix;
    fftw_complex *inputMatrixFFT;
    fftw_complex *kernelMatrixFFT;

    fftw_plan forwardImagePlan;
    fftw_plan forwardKernelPlan;
    fftw_plan backwardImagePlan;
};



#endif // DECONVOLUTIONTHREAD_H
