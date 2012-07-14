#ifndef MOTIONBLUR_H
#define MOTIONBLUR_H

#include "Blur.h"

class MotionBlur : public Blur
{
public:
    double angle;
    const QString getName() const{
        return "MotionBlur";
    }
};

#endif // MOTIONBLUR_H
