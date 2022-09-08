#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "data_structures/trapezoidalmap.h"
#include "data_structures/dag.h"
#include <iostream>

namespace algorithms{
   Trapezoid* followSegment(TrapezoidalMap T, Dag D, cg3::Segment2d s);
   void updateDag(TrapezoidalMap& Tmap, Trapezoid T, Dag& D);

   template<typename T>
   size_t getIndex(std::vector<T> v, T K);
}

#endif // ALGORITHMS_H
