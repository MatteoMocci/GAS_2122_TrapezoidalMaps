#include "dag_node.h"
size_t DagNode::last_index = 0;

DagNode::DagNode(nodeType type, size_t id):
   dag_index(last_index), entity_id(id), type(type)
{
    last_index++;
}



