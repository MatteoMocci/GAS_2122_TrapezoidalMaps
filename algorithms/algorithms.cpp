#include "algorithms.h"

#define P2_NODE dSize
#define S_NODE dSize + 1
#define A_NODE dSize + 2
#define B_NODE dSize + 3
#define C_NODE dSize + 4
#define D_NODE dSize + 5
/*
 * Input. 	A trapezoidal map T, a search structure D for T, and a new segment si
 * Output. 	The sequence Δ0, Δ1, …, Δk of trapezoids intersected by si
 * 1. Let p and q be the left and right endpoint of si
 * 2. Search with p in the search structure D to find Δ0
 * 3.	j ← 0
 * 4.	while q lies to the right of rightp(Δj)
 * 5.		do if rightp(Δj) lies above si
 * 6.				then Δj+1 be the lower right neighbor of Δj
 * 7.				else Δj+1 be the upper right neighbor of Δj
 * 8.			j ← j+1
 * 9.	return Δ0, Δ1, …, Δk

DagNode algorithms::followSegment(std::vector<Trapezoid> T, Dag D, cg3::Segment2d s){
    // Punto 1
    cg3::Point2d p = s.p1();
    cg3::Point2d q = s.p2();

    //Punto 2
    //implementare la ricerca nel Dag passando come parametro il punto p
}
*/

void algorithms::updateDag(Dag& D, cg3::Segment2d s, size_t tsplit, size_t tleft, size_t tright, size_t ttop, size_t tbottom){

    //obtain the size of the vectors of dagNodes, points and segment
    size_t dSize = D.getVectorSize(DAGNODE);
    size_t pSize = D.getVectorSize(POINT);
    size_t sSize = D.getVectorSize(SEGMENT);

    //create id of dag nodes
    size_t p1_id, p2_id, s_id, a_id, b_id, c_id, d_id = SIZE_MAX;

    //Create point, segment and trapezoid node
    DagNode p1 = DagNode(POINT,pSize);      //id = dSize
    DagNode p2 = DagNode(POINT,pSize + 1);  //id = dSize + 1
    DagNode sn = DagNode(SEGMENT, sSize);   //id = dSize + 2
    DagNode a = DagNode(TRAPEZOID, tleft);  //id = dSize + 3
    DagNode b = DagNode(TRAPEZOID, ttop);   //id = dSize + 4
    DagNode c = DagNode(TRAPEZOID, tbottom);//id = dSize + 5
    DagNode d = DagNode(TRAPEZOID, tright); //id = dSize + 6



    //push the nodes in the dag vector
    p1_id = D.replaceNode(tsplit,p1);
    p2_id = D.insertInVector(p2);
    s_id = D.insertInVector(sn);
    a_id = D.insertInVector(a);
    b_id = D.insertInVector(b);
    c_id = D.insertInVector(c);
    d_id = D.insertInVector(d);

    //set left and right children
    D.getElementInDVector(p1_id).setLeftc(a_id);
    D.getElementInDVector(p1_id).setRightc(p2_id);
    D.getElementInDVector(p2_id).setLeftc(s_id);
    D.getElementInDVector(p2_id).setRightc(d_id);
    D.getElementInDVector(s_id).setLeftc(b_id);
    D.getElementInDVector(s_id).setRightc(c_id);

    //push the points and the segment in the respective vector
    D.insertInVector(s.p1());
    D.insertInVector(s.p2());
    D.insertInVector(s);

}

template<typename T>
size_t algorithms::getIndex(std::vector<T> v, T K)
{
    auto it = find(v.begin(), v.end(), K);

    // If element was found
    if (it != v.end())
    {

        // calculating the index of K
        return it - v.begin();

    }
    else {
        return -1;
    }
}

bool algorithms::isAbove(cg3::Segment2d s, cg3::Point2d p){
    double v1[] {s.p2().x() - s.p1().x(), s.p2().y() - s.p1().y()};
    double v2[] = {s.p2().x()-p.x(), s.p2().y() -p.y()};
    double xp = v1[0]*v2[1] - v1[1]*v2[0]; //prodotto scalare
    if (xp > 0){
        return true;
    }
    else{
        return false;
    }

}

size_t algorithms::queryPoint(Dag dag, cg3::Point2d p){
    DagNode d = dag.getElementInDVector(0);
    while(true){
        switch(d.getNodeType()){
            case POINT:
                if(p.x() < dag.getElementInPVector(d.getEntityId()).x()){
                    d = dag.getElementInDVector(d.getLeftC());
                }
                else{
                    d = dag.getElementInDVector(d.getRightC());
                }
            break;
            case SEGMENT:{
                cg3::Segment2d s = dag.getElementInSVector(d.getEntityId());
                if(isAbove(s,p)){
                    d = dag.getElementInDVector(d.getLeftC());
                }
                else{
                   d = dag.getElementInDVector(d.getRightC());
                }
            }
            break;
            case TRAPEZOID:
                return d.getDagId();
            break;
        default:
            break;
    }
   }
}

void algorithms::splitin4(TrapezoidalMap& T, const cg3::Segment2d& s, Dag& D){
    size_t dag_id = queryPoint(D,s.p1()); //retrieve the id of the trapezoid containing the point
    size_t trap_id = D.getElementInDVector(dag_id).getEntityId();
    Trapezoid t_split = T.getTrapezoid(trap_id); //retrieve the trapezoid

    //create the left trapezoid
    Trapezoid tleft = Trapezoid(
                t_split.getLeftp(),
                s.p1(),
                cg3::Segment2d(t_split.getTop().p1(),cg3::Point2d(s.p1().x(), t_split.getTop().p1().y())),
                cg3::Segment2d(t_split.getBottom().p1(),cg3::Point2d(s.p1().x(), t_split.getBottom().p1().y()))
                );

    //create the trapezoid above
    Trapezoid ttop = Trapezoid(
                s.p1(),
                s.p2(),
                cg3::Segment2d(cg3::Point2d(s.p1().x(),t_split.getTop().p1().y()),cg3::Point2d(s.p2().x(),t_split.getTop().p2().y())),
                s
                );

    //create the trapezoid below
    Trapezoid tbottom = Trapezoid(
                cg3::Point2d(s.p1().x(),t_split.getBottom().p1().y()),
                cg3::Point2d(s.p2().x(),t_split.getBottom().p2().y()),
                s,
                cg3::Segment2d(cg3::Point2d(s.p1().x(),t_split.getBottom().p1().y()), cg3::Point2d(s.p2().x(),t_split.getBottom().p2().y()))
                );

    //create the right trapezoid
    Trapezoid tright = Trapezoid(
                cg3::Point2d(s.p2().x(),t_split.getLeftp().y()),
                t_split.getRightp(),
                cg3::Segment2d(cg3::Point2d(s.p2().x(),t_split.getTop().p2().y()),t_split.getTop().p2()),
                cg3::Segment2d(cg3::Point2d(s.p2().x(),t_split.getBottom().p2().y()),t_split.getBottom().p2())
                );

    T.replaceTrapezoid(trap_id,tleft);//delete the old trapezoid
    T.insertTrapezoid(ttop);
    T.insertTrapezoid(tbottom);
    T.insertTrapezoid(tright);

    updateDag(D,s,dag_id,tleft.getId(),tright.getId(),ttop.getId(),tbottom.getId());
}

