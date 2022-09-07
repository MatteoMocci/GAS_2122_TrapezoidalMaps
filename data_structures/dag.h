#ifndef DAG_H
#define DAG_H

#include "dag_node.h"

class Dag
{
    public:
        Dag();
    private:
        std::vector<AbstractNode> d_vector;
        void search();
};

#endif // DAG_H
