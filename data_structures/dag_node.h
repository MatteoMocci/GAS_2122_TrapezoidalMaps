#ifndef DAG_NODE_H
#define DAG_NODE_H

#include <iostream>
#include "trapezoid.h"
#include <boost/type_index.hpp>

enum nodeType {POINT,SEGMENT,TRAPEZOID,DAGNODE};


class DagNode{
    public:
        DagNode(nodeType type, size_t id);
        nodeType getNodeType() const;
        size_t getEntityId() const;
        size_t getLeftC() const;
        size_t getRightC() const;
        void setLeftc(size_t child);
        void setRightc(size_t child);
        size_t getDagId();
        void setDagId(size_t index);
        friend bool operator==(const DagNode& d1, const DagNode& d2);

    private:
        size_t leftc;
        size_t rightc;
        size_t dag_index;
        size_t entity_id;
        nodeType type;
};


#endif // DAG_NODE_H
