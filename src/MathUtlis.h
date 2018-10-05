#ifndef MATHUTLIS_H
#define MATHUTLIS_H

#ifdef _MSC_VER
#define _USE_MATH_DEFINES
#include <cmath>
#else
#include <math.h>
#endif


class MathUtlis
{
public:
    MathUtlis();
    //static void gradient(fftw_complex *inputMatrix, const QImage *inputImage, const int width, const int height);
};

#endif // MATHUTLIS_H
