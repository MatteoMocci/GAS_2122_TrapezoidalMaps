#ifndef TRAPEZOID_H
#define TRAPEZOID_H

#include <cg3/geometry/point2.h>
#include <cg3/geometry/segment2.h>
#include <cg3/utilities/color.h>
#define BOUNDINGBOX 1e+6

class Trapezoid
{

public:
    Trapezoid() = default;
    Trapezoid(cg3::Point2d leftp, cg3::Point2d rightp, cg3::Segment2d top, cg3::Segment2d bottom);
    const cg3::Point2d getLeftp() const;
    const cg3::Point2d getRightp() const;
    const cg3::Segment2d getBottom() const;
    const cg3::Segment2d getTop() const;
    const cg3::Color getColor() const;
    const cg3::Color getBorderColor() const;
    size_t getBorderWidth() const;
    size_t getId() const;
    void setLeftp(cg3::Point2d leftp);
    void setRightp(cg3::Point2d rightp);
    void setBottom(cg3::Segment2d bottom);
    void setTop(cg3::Segment2d top);
    void setColor(cg3::Color color);
    void setId(size_t index);
    void setBorderColor(cg3::Color color);
    void setBorderWidth(size_t width);
    friend bool operator==(const Trapezoid&, const Trapezoid&);
    static int lastQueried;
    static cg3::Color lastColor;

private:
    cg3::Point2d leftp;
    cg3::Point2d rightp;
    cg3::Segment2d bottom;
    cg3::Segment2d top;
    cg3::Color color;
    cg3::Color borderColor;
    size_t borderWidth;
    size_t trapIndex;


    /*
    size_t topleftnIndex;
    size_t toprightnIndex;
    size_t bottomleftnIndex;
    size_t bottomrightnIndex;
    */
};

#endif // TRAPEZOID_H
