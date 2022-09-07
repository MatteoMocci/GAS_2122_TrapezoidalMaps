#include "dag_node.h"
size_t AbstractNode::last_index = 0;

template <class T>
DagNode<T>::DagNode(T key)
{
    this->key = key;
    this->index = last_index;
    last_index++;
}

