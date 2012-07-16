#ifndef BLUR_H
#define BLUR_H

#include <QString>

class Blur
{
public:
    bool previewMode;
    double radius;
    double PSNR;
    const virtual QString getName() const = 0;
};

#endif // BLUR_H
