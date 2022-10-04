#include "utility.h"
/**
 * @brief algorithms::isAbove
 * This method checks if a point p is Above a segment s
 * @param s the segment to check
 * @param p the point to check
 * @return true if the point is above the segment, false otherwise
 */
bool utility::isAbove(cg3::Segment2d s, cg3::Point2d p){
    double v1[] {s.p2().x() - s.p1().x(), s.p2().y() - s.p1().y()};
    double v2[] = {s.p2().x()-p.x(), s.p2().y() -p.y()};
    double xp = v1[0]*v2[1] - v1[1]*v2[0]; //prodotto scalare
    if (xp < 0){
        return true;
    }
    else{
        return false;
    }

}

bool utility::pointEqual(cg3::Point2d p1, cg3::Point2d p2){
    return (fabs(p1.x() - p2.x()) < 0.005f  && fabs(p1.y() - p2.y()) < 0.005f);
}

bool utility::segmentGoesUp(cg3::Point2d p1, cg3::Point2d p2){
    float slope = (p2.x() - p1.x() != 0) ? (p2.y() - p1.y()) / (p2.x() - p1.x()) : INT_MAX;
    if(slope >= 0){
        return true;
    }
    else{
        return false;
    }
}
