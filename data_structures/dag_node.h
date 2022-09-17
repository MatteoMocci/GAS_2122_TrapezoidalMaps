#ifndef DAG_NODE_H
#define DAG_NODE_H

#include <iostream>
#include "trapezoid.h"
#include <boost/type_index.hpp>

enum nodeType {POINT,SEGMENT,TRAPEZOID,DAGNODE};
//this enumeration represents the type of a dag node: a point, a segment or a trapezoid.
//The DAGNODE value is used when managind the vector of dag nodes in a Dag


class DagNode{
    public:
        //constructors
        DagNode(nodeType type, size_t id);

        //getters
        nodeType getNodeType() const;
        size_t getEntityId() const;
        size_t getLeftC() const;
        size_t getRightC() const;

        //setters
        void setLeftc(size_t child);
        void setRightc(size_t child);
        size_t getDagId();
        void setDagId(size_t index);

        //override of == operator for dag nodes
        friend bool operator==(const DagNode& d1, const DagNode& d2);

    private:
        //attributes of a dag node
        size_t leftc;       //the id of the left children in the DAG of the current node
        size_t rightc;      //the id of the right children in the DAG of the current node
        size_t dag_index;   //the id of the current node, i.e. the position in the dag vector
        size_t entity_id;   //the id of the entity represented by the node.
                            //If it's a trapezoid is the position in the trapezoidal map
                            //If it's a point/segment is the position in the point/segment vector in the dag
        nodeType type;      //The type of the enity in the node: POINT, TRAPEZOID or SEGMENT
};


#endif // DAG_NODE_H
