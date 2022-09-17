#include "drawable_trapezoidalmap.h"

DrawableTrapezoidalMap::DrawableTrapezoidalMap(){
    srand(time(NULL));
}

void DrawableTrapezoidalMap::draw() const{
    for(const Trapezoid& t : getMap()){
        cg3::opengl::drawQuad2(t.getTop().p1(),t.getTop().p2(),t.getBottom().p2(),t.getBottom().p1(),
                               t.getColor(), 1, true);
        cg3::opengl::drawLine2(t.getTop().p1(),t.getTop().p2(),t.getBorderColor(), t.getBorderWidth());
        cg3::opengl::drawLine2(t.getBottom().p1(),t.getBottom().p2(),t.getBorderColor(), t.getBorderWidth());
        cg3::opengl::drawLine2(t.getTop().p1(),t.getBottom().p1(),t.getBorderColor(), t.getBorderWidth());
        cg3::opengl::drawLine2(t.getTop().p2(),t.getBottom().p2(),t.getBorderColor(), t.getBorderWidth());
    }
}

cg3::Point3d DrawableTrapezoidalMap::sceneCenter() const{
    const cg3::BoundingBox2& bbox = cg3::BoundingBox2();
    return cg3::Point3d(bbox.center().x(),bbox.center().y(),0);
}

double DrawableTrapezoidalMap::sceneRadius() const{
    const cg3::BoundingBox2& bbox = cg3::BoundingBox2();
    return bbox.diag();
}
