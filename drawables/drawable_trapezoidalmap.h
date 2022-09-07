#ifndef DRAWABLETRAPEZOIDALMAP_H
#define DRAWABLETRAPEZOIDALMAP_H

#include "data_structures/trapezoidalmap.h"

#include <cg3/viewer/interfaces/drawable_object.h>

#include <cg3/utilities/color.h>

class DrawableTrapezoidalMap : public TrapezoidalMap
{
public:
    DrawableTrapezoidalMap();

private:

    cg3::Color pointColor;
    cg3::Color segmentColor;

    unsigned int pointSize;
    unsigned int segmentSize;

};

#endif // DRAWABLETRAPEZOIDALMAP_H
