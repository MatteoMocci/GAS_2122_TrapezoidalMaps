#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "data_structures/trapezoidalmap.h"
#include "data_structures/dag.h"
#include <iostream>
#include "cg3/geometry/intersections2.h"

namespace algorithms{
   std::vector<Trapezoid> followSegment(TrapezoidalMap T, Dag D, cg3::Segment2d s);
   void updateDag(Dag& D, size_t t);
   bool isAbove(cg3::Segment2d s, cg3::Point2d p);

   template<typename T>
   size_t getIndex(std::vector<T> v, T K);

   std::vector<size_t> updateDag(Dag& D, cg3::Segment2d s, size_t tsplit, size_t tleft, size_t tright, size_t ttop, size_t tbottom);
   std::vector<size_t> updateDag(Dag& D, cg3::Segment2d s, size_t tsplit, size_t ttop, size_t tbottom, size_t tother, bool left);
   std::vector<size_t> updateDag(Dag& D, cg3::Segment2d s, size_t tsplit, size_t ttop, size_t tbottom);
   size_t queryPoint(Dag dag, cg3::Point2d p);
   void splitin2(TrapezoidalMap& T, const cg3::Segment2d& s, Dag & D, Trapezoid t_split, bool& merge_above, Trapezoid& t_merge);
   void splitin3(TrapezoidalMap& T, const cg3::Segment2d& s, Dag& D, Trapezoid t_split, bool left, bool& merge_above, Trapezoid& t_merge);
   void splitin4(TrapezoidalMap& T, const cg3::Segment2d& s, Dag& D, Trapezoid t_split);
   void multipleSplit(TrapezoidalMap& T, const cg3::Segment2d& s, Dag& D, std::vector<Trapezoid> delta);



}



#endif // ALGORITHMS_H
