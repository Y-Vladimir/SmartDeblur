#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QThread>
#include <QDebug>
#include <QWaitCondition>
#include <QMutex>
#include "DeconvolutionTool.h"
#include "MainWindow.h"

class WorkerThread : public QThread
{
    Q_OBJECT

public:
    explicit WorkerThread(QObject *parent = 0);
    int initFFT(const QImage *inputImage);
    void deconvolutionRequest(QImage *inputImage, QImage *outputImage, Blur *blur);
    DeconvolutionTool* getDeconvolutionTool();


protected:
    void run();

private:
    QMutex *mutex;
    QWaitCondition *requestCondition;
    volatile bool isRequestUpdated;
    QImage *inputImage;
    QImage *outputImage;
    Blur* blur;
    DeconvolutionTool *deconvolutionTool;
    
signals:
    void deconvolutionFinished(int);
};

#endif // WORKERTHREAD_H
