#include "dag.h"

/**
 * @brief Dag::Dag
 * Constructor of the DAG. The first node inserted in the dag is the node that represent a trapezoid, i.e
 * the bounding box
 */
Dag::Dag(){
    insertBoundingBoxD();
}

/**
 * @brief Dag::insertBoundingBoxD
 * This method inserts the node representing the trapezoid of the bounding box in the dag
 */
void Dag::insertBoundingBoxD(){
    DagNode n = DagNode(TRAPEZOID, 0);
    n.setDagId(0);
    dVector.push_back(n);
}

/**
 * @brief Dag::getdVector
 * @return A reference to the vector containing the DagNodes
 */
std::vector<DagNode>& Dag::getdVector(){
    return dVector;
}

/**
 * @brief Dag::insertInVector
 * This methods sets the id of the dagNode, insert the DagNode passed as parameter
 * into the vector of the DagNodes and returns the position in which the dagNode is added.
 * @param K a reference to the DagNode to insert into the vector
 * @return the position in which the DagNode is inserted
 */
size_t Dag::insertInVector(DagNode& K){
        K.setDagId(dVector.size()); //the size of the vector is last index + 1.
        //So if an element is added at the end, its id will be the old size of the vector
        dVector.push_back(K); //the node is added to the vector
        return dVector.size() - 1; //return the position in which the element has been added
}

/**
 * @brief Dag::insertInVector
 * This methods inserts the point passed as parameter
 * into the vector of the points and returns the position in which the point is added.
 * @param K a reference to the Point to insert into the vector
 * @return the position in which the Point is inserted
 */
size_t Dag::insertInVector(cg3::Point2d K){
        pVector.push_back(K); //the point is added to the vector of points
        return pVector.size() - 1; //return the position in which the point has been added
}

/**
 * @brief Dag::insertInVector
 * This method inserts the segment passed as parameter
 * into the vector of the segments and returns the position in which the segment is added.
 * @param K a reference to the Segment to insert into the vector
 * @return the position in which the Segment is inserted
 */
size_t Dag::insertInVector(cg3::Segment2d K){
        sVector.push_back(K); //the segment is added to the vector of segments
        return sVector.size() - 1; //return the position in which the segment is inserted
}

/**
 * @brief Dag::deleteInVector
 * This method deletes the element in the position specified by the index from one of the vectors.
 * The vector chosen depends on the type parameter.
 * @param type the type of the vector where the element has to be deleted
 * @param index the position of the element to delete
 */
void Dag::deleteInVector(nodeType type, size_t index)
{
    switch(type){
    case POINT:
        pVector.erase(pVector.begin() + index); //if it's a point delete from the point vector
        break;
    case SEGMENT:
        sVector.erase(sVector.begin() + index); //if it's a segment delete from the segment vector
        break;
    case TRAPEZOID:
        break;
    case DAGNODE: //if it's a dagNode, delete from the dagNode vector
        dVector.erase(dVector.begin() + index);
        break;
    }
}

/**
 * @brief Dag::replaceNode
 * This method replaces a node in the DagNode vector. The element in the position old_index is replaced by the
 * DagNode passed as parameter.
 * @param old_index the index of the element to delete
 * @param n the node insert in place of the old element
 * @return the position in which the element is added
 */
size_t Dag::replaceNode(size_t old_index, DagNode n){
    n.setDagId(old_index);  //the id of the new node will be the same of the old node
    dVector[old_index] = n; //the new node replaces the old node in the vector
    return old_index;       //return the index in which the node is inserted

}

/**
 * @brief Dag::getElementInPVector
 * This method returns a reference to the element of the point vector in the position passed as parameter
 * @param index the position of the element to return
 * @return a reference to the point in the requested position
 */
cg3::Point2d& Dag::getElementInPVector(size_t index){
    return pVector[index];
}

/**
 * @brief Dag::getElementInDVector
 * This method returns a reference to the element of the Dag vector in the position passed as parameter
 * @param index the position of the element to return
 * @return a reference to the DagNode in the requested position
 */
DagNode& Dag::getElementInDVector(size_t index){
    return dVector[index];
}

/**
 * @brief Dag::getElementInSVector
 * This method returns a reference to the element of the segment vector in the position passed as parameter
 * @param index the position of the element to return
 * @return a reference to the segment in the requested position
 */
cg3::Segment2d& Dag::getElementInSVector(size_t index){
    return sVector[index];
}

/**
 * @brief Dag::getsVector
 * @return A reference to the vector of segments
 */
std::vector<cg3::Segment2d>& Dag::getsVector(){
    return sVector;
}

/**
 * @brief Dag::getpVector
 * @return A reference to the vector of points
 */
std::vector<cg3::Point2d>& Dag::getpVector(){
    return pVector;
}

/**
 * @brief Dag::getVectorSize
 * This method returns the size of a vector. The vector chosen depends on the type parameter
 * @param type the type of the vector of which decide the size
 * @return the size of the vector chosen
 */
size_t Dag::getVectorSize(nodeType type){
    switch(type){
    case POINT:
        return pVector.size();
        break;
    case SEGMENT:
        return sVector.size();
        break;
    case DAGNODE:
        return dVector.size();
        break;
    default:
        return 0;
        break;
    }
}

/**
 * @brief Dag::clearDag
 * This method clears the Dag when the clear button is pressed on the interface.
 * The vector of dagNodes, points and segments are cleared and the boundingbox is reinserted in the DAG.
 */
void Dag::clearDag(){
    dVector.clear(); //remove all elements from dagNode vector
    pVector.clear(); //remove all elements from point vector
    sVector.clear(); //remove all elements from segment vector
    insertBoundingBoxD();
}

/**
 * @brief Dag::findSegment
 * This method checks if the segment s is present in the vector of segments and returns his position
 * @param[in] s the segment to check
 * @param[out] found a reference to a boolean that is set to true if the segment is found
 * @param[out] index a reference to a size_t that is set with the position in which the segment is found
 */
void Dag::findSegment(cg3::Segment2d s, bool& found, size_t& index){
    for (size_t i = 0; i < sVector.size(); i++){
        if(utility::pointEqual(sVector[i].p1(),s.p1()) && utility::pointEqual(sVector[i].p2(),s.p2())){
            index = i;
            found = true;
            return;
        }
    }
    found = false;
}

/**
 * @brief Dag::findPoint
 * This method checks if the point p is present in the vector of points and returns his position
 * @param[in] p the point to check
 * @param[out] found a reference to a boolean that is set to true if the point is found
 * @param[out] index a reference to a size_t that is set with the position in which the point is found
 */
void Dag::findPoint(cg3::Point2d p, bool& found, size_t& index){
    for (size_t i = 0; i < sVector.size(); i++){
        if(utility::pointEqual(pVector[i],p)){
            index = i;
            found = true;
            return;
        }
    }
    found = false;
}
