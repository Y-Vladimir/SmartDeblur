#ifndef BLUR_H
#define BLUR_H

#include <QString>

enum ProcessMode {
    PREVIEW_GRAY,
    PREVIEW_COLOR,
    HIGH_QUALITY
};

class Blur
{
public:
    ProcessMode mode;
    double radius;
    double smooth;
    const virtual QString getName() const = 0;
};

#endif // BLUR_H
