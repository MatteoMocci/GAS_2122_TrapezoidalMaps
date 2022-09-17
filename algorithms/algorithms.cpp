#include "algorithms.h"

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
/**
 * @brief algorithms::updateDag
 * This method updates the Dag after the segment insertion, when a split in 4 occurs.
 * The node of the trapezoid intersected by the segment is removed. The nodes for the segment, the two endpoints
 * and the four trapezoids are created and added to the dag, setting correctly their children.
 * @param D a reference to the Dag
 * @param s the segment inserted
 * @param tsplit the index of the dag node representing the trapezoid of the split
 * @param tleft the id of the trapezoid to the left
 * @param tright the id of the trapezoid to the right
 * @param ttop the id of the trapezoid above
 * @param tbottom the id of the trapezoid below
 */
void algorithms::updateDag(Dag& D, cg3::Segment2d s, size_t tsplit, size_t tleft, size_t tright, size_t ttop, size_t tbottom){

    //obtain the size of the vectors of dagNodes, points and segment
    size_t pSize = D.getVectorSize(POINT);
    size_t sSize = D.getVectorSize(SEGMENT);

    //create id of dag nodes
    size_t p1_id, p2_id, s_id, a_id, b_id, c_id, d_id = SIZE_MAX;

    //Create point, segment and trapezoid node
    DagNode p1 = DagNode(POINT,pSize);
    DagNode p2 = DagNode(POINT,pSize + 1);
    DagNode sn = DagNode(SEGMENT, sSize);
    DagNode a = DagNode(TRAPEZOID, tleft);
    DagNode b = DagNode(TRAPEZOID, ttop);
    DagNode c = DagNode(TRAPEZOID, tbottom);
    DagNode d = DagNode(TRAPEZOID, tright);



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
/**
 * @brief algorithms::getIndex
 * This method returns the index in which an element of type T inside a vector of type T
 * @param v the vector to check
 * @param K the element to find in the vector
 * @return the position of the element in the vector, -1 if the element has not been found
 */
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

/**
 * @brief algorithms::isAbove
 * This method checks if a point p is Above a segment s
 * @param s the segment to check
 * @param p the point to check
 * @return true if the point is above the segment, false otherwise
 */
bool algorithms::isAbove(cg3::Segment2d s, cg3::Point2d p){
    double v1[] {s.p2().x() - s.p1().x(), s.p2().y() - s.p1().y()};
    double v2[] = {s.p2().x()-p.x(), s.p2().y() -p.y()};
    double xp = v1[0]*v2[1] - v1[1]*v2[0]; //prodotto scalare
    if (xp < 0){
        return true;
    }
    else{
        return false;
    }

}

/**
 * This method queries the Dag with a point.
 * The query returns the id of the node representing in the Dag the trapezoid that intersects the point
 * If the current node is a point, then it is checked if the querypoint lies to the left or to the right
 * of the point in the node. If it is in the left, the query proceeds to the left, otherwise to the right.
 * If the current node is a segment, then it is checked if the querypoint is above or below the segment.
 * If it is above, the query proceeds to the left. If it is below, the query proceeds to the right.
 * If the current node is a trapezoid, return that node
 * @brief algorithms::queryPoint
 * @param dag the dag to use for the query
 * @param p the point for which to check the trapezoid in which the point is contained
 * @return the id of the node of the DagVector representing the trapezoid containing the point
 */
size_t algorithms::queryPoint(Dag dag, cg3::Point2d p){
    DagNode d = dag.getElementInDVector(0); //start from the root of the dag
    while(true){
        switch(d.getNodeType()){ //check the type of the node
            case POINT: //if it's a point
                if(p.x() < dag.getElementInPVector(d.getEntityId()).x()){
                    //check if the query point lies to the left of the point of the node
                    d = dag.getElementInDVector(d.getLeftC());
                    //if yes, go to the left child
                }
                else{
                    d = dag.getElementInDVector(d.getRightC());
                    //if no, go to the right child
                }
            break;
            case SEGMENT:{ //if it's a segment
                cg3::Segment2d s = dag.getElementInSVector(d.getEntityId());
                if(isAbove(s,p)){//check if the point is above the segment
                    d = dag.getElementInDVector(d.getLeftC()); //if yes, go to the left child
                }
                else{
                   d = dag.getElementInDVector(d.getRightC()); //if no, go to the right child
                }
            }
            break;
            case TRAPEZOID: //if it's a trapezoid
                return d.getDagId();
                //return the id of the node of the dag that represents that trapezoid
            break;
        default:
            break;
    }
   }
}

/**
 * @brief algorithms::splitin4
 * This method performs a split in 4. The intersecting face is removed from the trapezoidal map and the
 * 4 new trapezoid generated are inserted. Then, the updateDag() method is called in order to
 * reflect the changes in the trapezoidal map in the DAG as well.
 * @param T a reference to the TrapezoidalMap
 * @param s a reference to the segment that caused the split in 4
 * @param D a refernece to the Dag
 */
void algorithms::splitin4(TrapezoidalMap& T, const cg3::Segment2d& s, Dag& D){
    char dummy;
    size_t dag_id = queryPoint(D,s.p1());
    //retrieve the id of the dag node representing the trapezoid containing the point
    size_t trap_id = D.getElementInDVector(dag_id).getEntityId();
    //retrieve the id of the trapezoid
    Trapezoid t_split = T.getTrapezoid(trap_id); //retrieve the trapezoid

    //these 2 segments represent the projection on the x axis of the 2 endpoints of the segment
    cg3::Segment2d proj1 = cg3::Segment2d(cg3::Point2d(s.p1().x(),BOUNDINGBOX),
                                          cg3::Point2d(s.p1().x(), -BOUNDINGBOX));
    cg3::Segment2d proj2 = cg3::Segment2d(cg3::Point2d(s.p2().x(),BOUNDINGBOX),
                                          cg3::Point2d(s.p2().x(), -BOUNDINGBOX));



    cg3::Point2d p1t, p1b, p2t, p2b;
    //the four point of intersections: the intersection with top and bottom of the two projection segments

    //calculate the intersections
    cg3::checkSegmentIntersection2(t_split.getTop(),proj1,dummy,0,p1t);
    cg3::checkSegmentIntersection2(t_split.getBottom(),proj1,dummy,0,p1b);
    cg3::checkSegmentIntersection2(t_split.getTop(),proj2,dummy,0,p2t);
    cg3::checkSegmentIntersection2(t_split.getBottom(),proj2,dummy,0,p2b);


    //create the left trapezoid
    Trapezoid tleft = Trapezoid(
                t_split.getLeftp(),
                s.p1(),
                cg3::Segment2d(t_split.getTop().p1(),p1t),
                cg3::Segment2d(t_split.getBottom().p1(),p1b)
                );

    //create the trapezoid above
    Trapezoid ttop = Trapezoid(
                s.p1(),
                s.p2(),
                cg3::Segment2d(p1t,p2t),
                s
                );

    //create the trapezoid below
    Trapezoid tbottom = Trapezoid(
                s.p1(),
                s.p2(),
                s,
                cg3::Segment2d(p1b,p2b)
                );

    //create the right trapezoid
    Trapezoid tright = Trapezoid(
                s.p2(),
                t_split.getRightp(),
                cg3::Segment2d(p2t,t_split.getTop().p2()),
                cg3::Segment2d(p2b,t_split.getBottom().p2())
                );

    T.replaceTrapezoid(trap_id,tleft);//replace the old trapezoid in the trapezoidal map with tleft
    //insert the other trapezoids in the trapezoidal map
    T.insertTrapezoid(ttop);
    T.insertTrapezoid(tbottom);
    T.insertTrapezoid(tright);

    updateDag(D,s,dag_id,tleft.getId(),tright.getId(),ttop.getId(),tbottom.getId()); //update the Dag
}

