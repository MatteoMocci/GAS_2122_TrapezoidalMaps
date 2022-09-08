#ifndef DAG_H
#define DAG_H

#include "dag_node.h"

class Dag
{
    public:
        Dag();
        AbstractNode search(cg3::Point2d p);
    private:
        std::vector<AbstractNode> d_vector;
        size_t root = 0;
};

#endif // DAG_H
