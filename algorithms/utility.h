#ifndef UTILITY_H
#define UTILITY_H

#include <cg3/geometry/point2.h>
#include <cg3/geometry/segment2.h>
#include "cg3/geometry/line2.h"

namespace utility{
    bool isAbove(cg3::Segment2d s, cg3::Point2d p);
    bool pointEqual(cg3::Point2d p1, cg3::Point2d p2);
    bool segmentGoesUp(cg3::Point2d p1, cg3::Point2d p2);
    float slope(cg3::Point2d p1, cg3::Point2d p2);

}

#endif // UTILITY_H
