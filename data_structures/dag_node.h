#ifndef DAG_NODE_H
#define DAG_NODE_H

#include <iostream>
#include "trapezoid.h"

struct AbstractNode{
    static size_t last_index;
};


template <class T>
class DagNode : public AbstractNode{
    public:
        T key;
        DagNode(T key);

    private:
        size_t leftc;
        size_t rightc;
        size_t index;
};

template class DagNode<Trapezoid>;
template class DagNode<cg3::Point2d>;
template class DagNode<cg3::Segment2d>;
#endif // DAG_NODE_H
