#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "data_structures/trapezoidalmap.h"
#include "data_structures/dag.h"
#include <iostream>
#include "cg3/geometry/intersections2.h"

namespace algorithms{
   std::vector<Trapezoid> followSegment(TrapezoidalMap T, Dag D, cg3::Segment2d s);

   template<typename T>
   size_t getIndex(std::vector<T> v, T K);

   //dag-related methods
   std::vector<size_t> updateDag(Dag& D, cg3::Segment2d s, size_t tsplit, size_t tleft, size_t tright, size_t ttop, size_t tbottom);
   std::vector<size_t> updateDag(Dag& D, cg3::Segment2d s, size_t tsplit, size_t ttop, size_t tbottom, size_t tother, bool left);
   std::vector<size_t> updateDag(Dag& D, cg3::Segment2d s, size_t tsplit, size_t ttop, size_t tbottom);
   std::vector<size_t> updateDag(Dag& D, cg3::Segment2d s, coincidence coincidence, size_t tsplit, size_t tother, size_t ttop, size_t tbottom);
   std::vector<size_t> updateDagBothC(Dag& D, cg3::Segment2d s, size_t tsplit, size_t ttop, size_t tbottom);
   size_t queryPoint(Dag dag, cg3::Point2d p);

   //split methods
   void splitin2(TrapezoidalMap& T, const cg3::Segment2d& s, Dag & D, size_t trap_id, bool& merge_above, Trapezoid& t_merge, size_t & t_prev, size_t next, bool& first);
   void splitin3(TrapezoidalMap& T, const cg3::Segment2d& s, Dag& D, size_t trap_id, bool left, bool& merge_above, Trapezoid & t_merge, size_t & t_prev, size_t next, bool& first);
   void splitin4(TrapezoidalMap& T, const cg3::Segment2d& s, Dag& D, size_t trap_id);
   void multipleSplit(TrapezoidalMap& T, const cg3::Segment2d& s, Dag& D, std::vector<Trapezoid> delta);



}



#endif // ALGORITHMS_H
