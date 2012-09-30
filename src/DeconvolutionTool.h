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
#include <QApplication>
#include <time.h>

#ifdef _MSC_VER
#define _USE_MATH_DEFINES
#include <cmath>
#else
#include <math.h>
#endif

#include "ImageUtils.h"
#include "Models/ProcessingContext.h"
#if defined (Q_WS_WIN)
#include "fftw3.h"
#else
#include <fftw3.h>
#endif
#include <typeinfo>



class DeconvolutionTool : public QObject
{
    Q_OBJECT

public:
    DeconvolutionTool(QObject* parent = 0);
    ~DeconvolutionTool();
    void initFFT(const QImage *inputImage);
    bool doDeconvolution(QImage *inputImage, QImage *outputImage, Blur *blur);
    int getThreadsCount();
    static void visualizeFFT(fftw_complex *fft, const int WIDTH, const int HEIGHT, QString path);
    static void buildKernel(double* outKernelFFT, const int WIDTH, const int HEIGHT, const Blur* blur);
    static void multiplayRealFFTs(fftw_complex *outFFT, const fftw_complex *kernelFFT, const int width, const int height);
    void cancelProcessing();
    void setTVIterationsCount(int value);
    void setPreviewMethod(int value);

signals:
    void progressEvent(int, QString);

private:
    void removeFFTObjects();
    void setProgressInterval(int begin, int end, QString text);
    void setProgressSubValue(int percentValue);
    void deconvolutionByWiener(ProcessingContext* processingContext);
    void deconvolutionByTikhonov(ProcessingContext *processingContext);
    void deconvolutionByTotalVariationPrior(ProcessingContext *processingContext);

    void buildLaplacian(fftw_complex* outLaplacianFFT, const int WIDTH, const int HEIGHT);
    void doDeconvolutionForChannel(ProcessingContext* processingContext, const CurrentChannel channel);

    volatile bool isProcessingCancelled;

    int beginCurrentProgress, endCurrentProgress;
    QString currentProgressText;

    int width, height;
    int threadsCount;
    int tvIterationsCount;
    int previewMethod;

    double *inputImageMatrix;    
    double *outputImageMatrix;    
    double *kernelMatrix;

    fftw_complex *inputImageFFT;
    fftw_complex *outputImageFFT;
    fftw_complex *kernelFFT;
    fftw_complex *kernelTempFFT;

    fftw_plan realForwardPlan;
    fftw_plan realBackwardPlan;
    fftw_plan realForwardKernelPlan;
    fftw_plan forwardLaplacianPlan;
    fftw_plan backwardLaplacianPlan;

    double *laplacianMatrix;
    double *outLaplacianMatrix;
    fftw_complex *laplacianMatrixFFT;
};



#endif // DECONVOLUTIONTHREAD_H
