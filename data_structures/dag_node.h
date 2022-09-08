#ifndef DAG_NODE_H
#define DAG_NODE_H

#include <iostream>
#include "trapezoid.h"
#include <boost/type_index.hpp>

struct AbstractNode{
    static size_t last_index;

    protected:
    size_t leftc;
    size_t rightc;
    size_t index;
    std::string type;
};


template <class T>
class DagNode : public AbstractNode{
    public:
        T key;
        DagNode(T key);
        //virtual AbstractNode search(cg3::Point2d p, DagNode<T>) = 0;
};

#endif // DAG_NODE_H
