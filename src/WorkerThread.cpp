#include "WorkerThread.h"

WorkerThread::WorkerThread(QObject *parent) : QThread(parent) {
    deconvolutionTool = new DeconvolutionTool();
    mutex = new QMutex();
    requestCondition = new QWaitCondition();
}

int WorkerThread::initFFT(const QImage *inputImage) {
    deconvolutionTool->initFFT(inputImage);
    isRequestUpdated = false;
    return deconvolutionTool->getThreadsCount();
}

void WorkerThread::deconvolutionRequest(QImage *inputImage, QImage *outputImage, Blur* blur) {
    this->blur = blur;
    this->inputImage = inputImage;
    this->outputImage = outputImage;
    isRequestUpdated = true;

    deconvolutionTool->cancelProcessing();

    // Wake-up waited thread
    requestCondition->wakeAll();
}

DeconvolutionTool *WorkerThread::getDeconvolutionTool() {
    return deconvolutionTool;
}

void WorkerThread::run() {
    qDebug("Started");
    QTime timer;
    while (true) {
        mutex->lock();
        requestCondition->wait(mutex);

        // Deconvoltion in the cycle in order to catch last request during processing one of previous requests
        // Otherwise we can miss the last request (kind of "Race Condition" issue)
        while (isRequestUpdated) {
            isRequestUpdated = false;
            timer.restart();
            bool result = deconvolutionTool->doDeconvolution(inputImage, outputImage, blur);
            emit deconvolutionFinished(timer.elapsed());
            // if gray preivew is not canceled, start color preview
            if (result && blur->mode != HIGH_QUALITY) {
                blur->mode = PREVIEW_COLOR;
                if (deconvolutionTool->doDeconvolution(inputImage, outputImage, blur)) {
                    emit deconvolutionFinished(timer.elapsed());
                }
            }
        }

        mutex->unlock();
    }
}

