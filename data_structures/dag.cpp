#include "dag.h"

Dag::Dag()
{
    AbstractNode::last_index = 0;
    DagNode<Trapezoid> t = Trapezoid(cg3::Point2d(-BOUNDINGBOX,BOUNDINGBOX),
                  cg3::Point2d(BOUNDINGBOX,-BOUNDINGBOX),
                  cg3::Segment2d(cg3::Point2d(-BOUNDINGBOX,BOUNDINGBOX),cg3::Point2d(BOUNDINGBOX,BOUNDINGBOX)),
                  cg3::Segment2d(cg3::Point2d(-BOUNDINGBOX,-BOUNDINGBOX),cg3::Point2d(BOUNDINGBOX,-BOUNDINGBOX))
                  );
    d_vector.push_back(t);
}
