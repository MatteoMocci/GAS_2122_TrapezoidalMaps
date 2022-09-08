#ifndef DAG_H
#define DAG_H

#include "dag_node.h"


class Dag
{
    public:
        Dag();
        std::vector<DagNode>& getdVector();
        void addNode(DagNode n);
    private:
        std::vector<DagNode> dVector;
        size_t root = 0;
};

#endif // DAG_H
