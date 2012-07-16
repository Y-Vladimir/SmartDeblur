#ifndef BLUR_H
#define BLUR_H

#include <QString>

class Blur
{
public:
    bool previewMode;
    double radius;
    double PSNR;
#ifdef _MSC_VER
    const virtual QString getName() const { return "Blur"; };
#else
    const virtual QString getName() const;
#endif
};

#endif // BLUR_H
