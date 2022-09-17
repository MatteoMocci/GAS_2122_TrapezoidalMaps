#include "dag_node.h"

/**
 * @brief DagNode::DagNode
 * Constructor of the DagNode class.
 * @param type The type of the entity represented by the node: POINT, SEGMENT or TRAPEZOID
 * @param id   The position of the dag node in the dag vector
 */
DagNode::DagNode(nodeType type, size_t id):
    entity_id(id), type(type)
{
}

/**
 * @brief DagNode::getNodeType
 * @return the type of the entity represented by the node: POINT, SEGMENT or TRAPEZOID
 */
nodeType DagNode::getNodeType() const{
    return type;
}

/**
 * @brief DagNode::getEntityId
 * @return the id of the entity represented by the node:
 * POINT:   the position of the point in the point vector in the dag
 * SEGMENT: the position of the segment in the segment vector in the dag
 * TRAPEZOID: the position of the trapezoid in the trapezoid vector in the dag
 */
size_t DagNode::getEntityId() const{
    return entity_id;
}

/**
 * @brief DagNode::getLeftC
 * @return the id of the node which is the left children of the current node
 */
size_t DagNode::getLeftC() const{
    return leftc;
}

/**
 * @brief DagNode::getRightC
 * @return the id of the node which is the right children of the current node
 */
size_t DagNode::getRightC() const{
    return rightc;
}

/**
 * @brief DagNode::setLeftc
 * This method sets the value of the index of the left children of the current node
 * @param child the id of the node which is the left children of the current node
 */
void DagNode::setLeftc(size_t child){
    leftc = child;
}

/**
 * @brief DagNode::setRightc
 * This method sets the value of the index of the right children of the current node
 * @param child the id of the node which is the right children of the current node
 */
void DagNode::setRightc(size_t child){
    rightc = child;
}

/**
 * @brief DagNode::setDagId
 * This method sets the value of the id of the current node, i.e. its position in the
 * DagNode vector in the Dag.
 * @param index the value to set as the id of the node
 */
void DagNode::setDagId(size_t index){
    dag_index = index;
}

/**
 * @brief DagNode::getDagId
 * @return the id of the node, i.e. its position in the DagNode vector in the Dag
 */
size_t DagNode::getDagId(){
    return dag_index;
}

/**
 * @brief operator ==
 * Override of operator == for dagNodes. Two dagNodes represent the same dagNode when they have the same id.
 * @param d1 the first dagNode to compare
 * @param d2 the second dagNode to compare
 * @return true if the two dagNodes are equal, false otherwise
 */
bool operator==(const DagNode& d1, const DagNode& d2){
    return d1.dag_index == d2.dag_index;
}



