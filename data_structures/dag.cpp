#include "dag.h"

Dag::Dag()
{

}

std::vector<DagNode>& Dag::getdVector(){
    return dVector;
}

void Dag::addNode(DagNode n){
    dVector.push_back(n);
}
