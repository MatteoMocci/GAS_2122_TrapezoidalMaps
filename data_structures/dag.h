#ifndef DAG_H
#define DAG_H

#include "dag_node.h"


class Dag
{
    public:
    //constructors
        Dag();

        //getter
        std::vector<DagNode>& getdVector();
        std::vector<cg3::Point2d>& getpVector();
        std::vector<cg3::Segment2d>& getsVector();

        //methods for managing the vectors in the dag
        size_t insertInVector(DagNode& K);
        size_t insertInVector(cg3::Point2d K);
        size_t insertInVector(cg3::Segment2d K);
        size_t replaceNode(size_t old_index, DagNode n);
        void deleteInVector(nodeType type, size_t index);
        size_t getVectorSize(nodeType type);
        cg3::Point2d& getElementInPVector(size_t index);
        DagNode& getElementInDVector(size_t index);
        cg3::Segment2d& getElementInSVector(size_t index);
        void clearDag();
        void insertBoundingBoxD();


    private:
        //attributes of the dag: a vector of dagNodes, of points and segments
        std::vector<DagNode> dVector;
        std::vector<cg3::Point2d> pVector;
        std::vector<cg3::Segment2d> sVector;
};

#endif // DAG_H
