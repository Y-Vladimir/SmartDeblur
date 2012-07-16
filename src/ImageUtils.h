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


#include "fftw3.h"

#include "Models/Blur.h"
#include "Models/FocusBlur.h"
#include "Models/MotionBlur.h"

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

    static void fillInputMatrix(fftw_complex *inputMatrix, const QImage *inputImage, const int width, const int height, const CurrentChannel channel);
    static void fillOutputImage(const QImage *inputImage, const fftw_complex *outputMatrix, QImage *outputImage, const int width, const int height, const CurrentChannel channel);
};

#endif // IMAGEUTILS_H
