#ifndef GAUSSIANBLUR_H
#define GAUSSIANBLUR_H

#include "Blur.h"

class GaussianBlur : public Blur
{
public:
    const QString getName() const{
        return "GaussianBlur";
    }
};

#endif // GAUSSIANBLUR_H
