#ifndef FOCUSBLUR_H
#define FOCUSBLUR_H

#include "Blur.h"

class FocusBlur : public Blur
{
public:
    double edgeFeather;
    double correctionStrength;
     const QString getName() const{
        return "FocusBlur";
    }
};

#endif // FOCUSBLUR_H
