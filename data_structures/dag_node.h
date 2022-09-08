#ifndef DAG_NODE_H
#define DAG_NODE_H

#include <iostream>
#include "trapezoid.h"
#include <boost/type_index.hpp>

enum nodeType {POINT,SEGMENT,TRAPEZOID};


class DagNode{
    public:
        DagNode(nodeType type, size_t id);
        static size_t last_index;

    private:
        size_t leftc;
        size_t rightc;
        size_t dag_index;
        size_t entity_id;
        nodeType type;
};


#endif // DAG_NODE_H
