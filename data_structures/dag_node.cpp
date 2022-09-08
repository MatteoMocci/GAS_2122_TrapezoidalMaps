#include "dag_node.h"
size_t AbstractNode::last_index = 0;

template <class T>
DagNode<T>::DagNode(T key)
{
    this->key = key;
    this->index = last_index;
    last_index++;
    this->type = boost::typeindex::type_id<T>().pretty_name();
}

/*
template<>
DagNode<Trapezoid> DagNode<Trapezoid>::search(cg3::Point2d p, DagNode<Trapezoid> node){
    return node;
}
*/

