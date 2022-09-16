#include "dag.h"

Dag::Dag(){
        DagNode n = DagNode(TRAPEZOID, 0);
        n.setDagId(0);
        dVector.push_back(n);
}

std::vector<DagNode>& Dag::getdVector(){
    return dVector;
}


size_t Dag::insertInVector(DagNode& K){
        K.setDagId(dVector.size());
        dVector.push_back(K);
        return dVector.size() - 1;
}

size_t Dag::insertInVector(cg3::Point2d K){
        pVector.push_back(K);
        return pVector.size() - 1;
}

size_t Dag::insertInVector(cg3::Segment2d K){
        sVector.push_back(K);
        return sVector.size() - 1;
}

void Dag::deleteInVector(nodeType type, size_t index)
{
    switch(type){
    case POINT:
        pVector.erase(pVector.begin() + index);
        break;
    case SEGMENT:
        sVector.erase(sVector.begin() + index);
        break;
    case TRAPEZOID:
        break;
    case DAGNODE:
        dVector.erase(dVector.begin() + index);
        break;
    }
}

size_t Dag::replaceNode(size_t old_index, DagNode n){
    n.setDagId(old_index);
    dVector[old_index] = n;
    return old_index;

}

cg3::Point2d& Dag::getElementInPVector(size_t index){
    return pVector[index];
}

DagNode& Dag::getElementInDVector(size_t index){
    return dVector[index];
}

cg3::Segment2d& Dag::getElementInSVector(size_t index){
    return sVector[index];
}

std::vector<cg3::Segment2d>& Dag::getsVector(){
    return sVector;
}

std::vector<cg3::Point2d>& Dag::getpVector(){
    return pVector;
}

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

