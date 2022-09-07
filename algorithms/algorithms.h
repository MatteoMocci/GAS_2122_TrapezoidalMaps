#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "data_structures/trapezoid.h"
#include "data_structures/trapezoidalmap.h"
#include <cg3/geometry/segment2.h>
#include "data_structures/dag.h"
#include <cg3/geometry/point2.h>
#include <iostream>

namespace algorithms{
   inline Trapezoid* followSegment(TrapezoidalMap T, Dag D, cg3::Segment2d s);
}

#endif // ALGORITHMS_H
