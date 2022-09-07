#ifndef TRAPEZOID_H
#define TRAPEZOID_H

#include <cg3/geometry/point2.h>
#include <cg3/geometry/segment2.h>
#define BOUNDINGBOX 1e+6

class Trapezoid
{

public:
    Trapezoid() = default;
    Trapezoid(cg3::Point2d leftp, cg3::Point2d rightp, cg3::Segment2d top, cg3::Segment2d bottom);
    cg3::Point2d getLeftp();
    cg3::Point2d getRightp();
    cg3::Segment2d getBottom();
    cg3::Segment2d getTop();
    void setLeftp(cg3::Point2d leftp);
    void setRightp(cg3::Point2d rightp);
    void setBottom(cg3::Segment2d bottom);
    void setTop(cg3::Segment2d top);

private:
    cg3::Point2d leftp;
    cg3::Point2d rightp;
    cg3::Segment2d bottom;
    cg3::Segment2d top;

    size_t topleftnIndex;
    size_t toprightnIndex;
    size_t bottomleftnIndex;
    size_t bottomrightnIndex;
};

#endif // TRAPEZOID_H
