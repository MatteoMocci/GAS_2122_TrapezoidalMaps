#include "drawable_trapezoidalmap.h"

/**
 * @brief DrawableTrapezoidalMap::DrawableTrapezoidalMap
 * Constructor of the DrawableTrapezoidalMap, it initializes the seed for random number generation
 */
DrawableTrapezoidalMap::DrawableTrapezoidalMap(){
    srand(time(NULL));
}

/**
 * @brief DrawableTrapezoidalMap::draw
 * This method draws all trapezoids in the trapezoidal map
 */
void DrawableTrapezoidalMap::draw() const{
    for(const Trapezoid& t : getMap()){
        //draw the face of the trapezoid
        cg3::opengl::drawQuad2(t.getTop().p1(),t.getTop().p2(),t.getBottom().p2(),t.getBottom().p1(),
                               t.getColor(), 1, true);
        //draw the borders of the trapezoid
        cg3::opengl::drawLine2(t.getTop().p1(),t.getTop().p2(),t.getBorderColor(), t.getBorderWidth());
        cg3::opengl::drawLine2(t.getBottom().p1(),t.getBottom().p2(),t.getBorderColor(), t.getBorderWidth());
        cg3::opengl::drawLine2(t.getTop().p1(),t.getBottom().p1(),t.getBorderColor(), t.getBorderWidth());
        cg3::opengl::drawLine2(t.getTop().p2(),t.getBottom().p2(),t.getBorderColor(), t.getBorderWidth());
    }
}

/**
 * @brief DrawableTrapezoidalMap::sceneCenter
 * Override of the sceneCenter method
 * @return the center of the boundingbox
 */
cg3::Point3d DrawableTrapezoidalMap::sceneCenter() const{
    const cg3::BoundingBox2& bbox = cg3::BoundingBox2();
    return cg3::Point3d(bbox.center().x(),bbox.center().y(),0);
}

/**
 * @brief DrawableTrapezoidalMap::sceneRadius
 * Override of the sceneRadius method
 * @return the diagonal of the bounding box
 */
double DrawableTrapezoidalMap::sceneRadius() const{
    const cg3::BoundingBox2& bbox = cg3::BoundingBox2();
    return bbox.diag();
}

double DrawableTrapezoidalMap::getLastQueried() const{
    return lastQueried;
}

const cg3::Color DrawableTrapezoidalMap::getLastColor() const{
    return lastColor;
}

void DrawableTrapezoidalMap::setLastQueried(size_t last){
    lastQueried = last;
}

void DrawableTrapezoidalMap::setLastColor(cg3::Color color){
    lastColor = color;
}
