#ifndef DRAWABLETRAPEZOIDALMAP_H
#define DRAWABLETRAPEZOIDALMAP_H

#include "data_structures/trapezoidalmap.h"

#include <cg3/viewer/interfaces/drawable_object.h>
#include <cg3/geometry/segment2.h>

#include <cg3/utilities/color.h>
#include <cg3/viewer/opengl_objects/opengl_objects2.h>
#include <cg3/geometry/bounding_box2.h>

class DrawableTrapezoidalMap : public TrapezoidalMap, public cg3::DrawableObject
{
public:
    DrawableTrapezoidalMap();
    void draw() const;
    cg3::Point3d sceneCenter() const;
    double sceneRadius() const;

    double getLastQueried() const;
    const cg3::Color getLastColor() const;
    void setLastQueried(size_t last);
    void setLastColor(cg3::Color color);

private:
    int lastQueried = -1;
    cg3::Color lastColor = cg3::Color(0,0,0);

};

#endif // DRAWABLETRAPEZOIDALMAP_H
