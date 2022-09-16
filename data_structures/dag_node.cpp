#include "dag_node.h"

DagNode::DagNode(nodeType type, size_t id):
    entity_id(id), type(type)
{
}

nodeType DagNode::getNodeType() const{
    return type;
}

size_t DagNode::getEntityId() const{
    return entity_id;
}

size_t DagNode::getLeftC() const{
    return leftc;
}

size_t DagNode::getRightC() const{
    return rightc;
}

void DagNode::setLeftc(size_t child){
    leftc = child;
}

void DagNode::setRightc(size_t child){
    rightc = child;
}

void DagNode::setDagId(size_t index){
    dag_index = index;
}

size_t DagNode::getDagId(){
    return dag_index;
}

bool operator==(const DagNode& d1, const DagNode& d2){
    return d1.dag_index == d2.dag_index;
}



