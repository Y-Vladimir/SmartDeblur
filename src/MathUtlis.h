#ifndef MATHUTLIS_H
#define MATHUTLIS_H

#ifdef _MSC_VER
#define _USE_MATH_DEFINES
#include <cmath>
#else
#include <math.h>
#endif

#if defined (Q_WS_WIN)
#include "fftw3.h"
#else
#include <fftw3.h>
#endif

class MathUtlis
{
public:
    MathUtlis();
    //static void gradient(fftw_complex *inputMatrix, const QImage *inputImage, const int width, const int height);
};

#endif // MATHUTLIS_H
