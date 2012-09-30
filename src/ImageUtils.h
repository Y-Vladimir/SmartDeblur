#ifndef IMAGEUTILS_H
#define IMAGEUTILS_H

#ifdef _MSC_VER
#define _USE_MATH_DEFINES
#include <cmath>
#else
#include <math.h>
#endif

#include <QDebug>
#include <QTime>
#include <QImage>
#include <QPainter>
#if defined (Q_WS_WIN)
#include "fftw3.h"
#else
#include <fftw3.h>
#endif
#include "Models/Blur.h"
#include "Models/FocusBlur.h"
#include "Models/MotionBlur.h"
#include "Models/GaussianBlur.h"
#include "Models/ProcessingContext.h"

enum CurrentChannel {
    RED,
    GREEN,
    BLUE,
    GRAY
};


// Optimized version of pow(-1, x+y)
inline signed char centerFFTKoef(int x, int y) {
    return((x+y) & 1) == 0 ? 1 : -1;
    // return pow(-1, x+y);
    // return 1;
}

class ImageUtils {

public:
    static QImage* buildKernelImage(const FocusBlur* focusBlur);
    static QImage* buildKernelImage(const MotionBlur* motionBlur);
    static QImage *buildKernelImage(const GaussianBlur* gaussianBlur);

    static void fillInputMatrix(ProcessingContext *processingContext, const CurrentChannel channel);
    static void fillMatrixFromImage(ProcessingContext *processingContext, const CurrentChannel channel);
    static void fillImageFromMatrix(ProcessingContext *processingContext, const CurrentChannel channel);
};

#endif // IMAGEUTILS_H
