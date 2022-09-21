#include "algorithms.h"
#define TOP_LEFT 0
#define TOP_RIGHT 1
#define BOTTOM_LEFT 2
#define BOTTOM_RIGHT 3

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
 */

/**
 * @brief algorithms::followSegment
 * This algorithm, using the trapezoidal map T and the dag D, returns the vectir of trapezoids in T that are intersected by s
 * @param T the trapezoidal map containing the segments
 * @param D the Dag to query with the left endpoint of the segment
 * @param s the segment that intersects the trapezoids
 * @return the vector with all trapezoids intersected by the segment
 */
std::vector<Trapezoid> algorithms::followSegment(TrapezoidalMap T, Dag D, cg3::Segment2d s){

    std::vector<Trapezoid> delta; //the vector that will contain the trapezoids intersected by the segment
    cg3::Point2d p = s.p1(); //p is the left endpoint of the segment
    cg3::Point2d q = s.p2(); //q is the right endpoint of the segment

    size_t i0 = queryPoint(D, p);//query the dag with the left endpoint to find the first intersected trapezoid
    delta.push_back(T.getTrapezoid(D.getElementInDVector(i0).getEntityId())); //add in the vector the first trapezoid found
    size_t j = 0; //variable used in the while loop
    while(q.x() > delta[j].getRightp().x()){//while the right endpoint lies to the right of rightp(Δj)
        if(isAbove(s,delta[j].getRightp())){//if rightp(Δj) lies above si
            delta.push_back(T.getTrapezoid(delta[j].getNeighbor(BOTTOM_RIGHT)));
            //then Δj+1 be the lower right neighbor of Δj
        }
        else{
            delta.push_back(T.getTrapezoid(delta[j].getNeighbor(TOP_RIGHT)));
            //else Δj+1 be the upper right neighbor of Δj
        }
        j++;//update the loop variable
    }
    return delta;//return the vector with the trapezoid
}

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
std::vector<size_t> algorithms::updateDag(Dag& D, cg3::Segment2d s, size_t tsplit, size_t tleft, size_t tright, size_t ttop, size_t tbottom){

    //obtain the size of the vectors of dagNodes, points and segment
    size_t pSize = D.getVectorSize(POINT);
    size_t sSize = D.getVectorSize(SEGMENT);
    std::vector<size_t> tId;

    DagNode p1,p2,sn;
    bool p1AlreadyPresent;
    bool p2AlreadyPresent;
    bool sAlreadyPresent;
    size_t p1_old;
    size_t p2_old;
    size_t s_old;

    D.findPoint(s.p1(),p1AlreadyPresent,p1_old);
    D.findPoint(s.p2(),p2AlreadyPresent,p2_old);
    D.findSegment(s,sAlreadyPresent,s_old);

    //create id of dag nodes
    size_t p1_id, p2_id, s_id, a_id, b_id, c_id, d_id = SIZE_MAX;

    //Create point, segment and trapezoid node
    if(p1AlreadyPresent){
        p1 = DagNode(POINT,p1_old);
    }
    else{
        p1 = DagNode(POINT,pSize);
    }

    if(p2AlreadyPresent){
        p2 = DagNode(POINT,p2_old);
    }
    else{
        if(!p1AlreadyPresent){
            p2 = DagNode(POINT,pSize + 1);
        }
        else{
            p2 = DagNode(POINT,pSize);
        }
    }

    if(sAlreadyPresent){
        sn = DagNode(SEGMENT, s_old);
    }
    else{
        sn = DagNode(SEGMENT, sSize);
    }

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

    tId.push_back(a_id);
    tId.push_back(b_id);
    tId.push_back(c_id);
    tId.push_back(d_id);

    return tId;

}

std::vector<size_t> algorithms::updateDag(Dag& D, cg3::Segment2d s, size_t tsplit, size_t ttop, size_t tbottom, size_t tother, bool left){
    //obtain the size of the vectors of dagNodes, points and segment
    size_t pSize = D.getVectorSize(POINT);
    size_t sSize = D.getVectorSize(SEGMENT);
    DagNode p, sn;

    bool pAlreadyPresent;
    bool sAlreadyPresent;
    size_t p_old;
    size_t s_old;

    if(left){
        D.findPoint(s.p1(),pAlreadyPresent,p_old);
    }
    else{
        D.findPoint(s.p2(),pAlreadyPresent,p_old);
    }
    D.findSegment(s,sAlreadyPresent,s_old);

    //create id of dag nodes
    size_t p_id, s_id, a_id, b_id, c_id = SIZE_MAX;

    std::vector<size_t> tId;

    //Create point, segment and trapezoid node
    if(pAlreadyPresent){
        p = DagNode(POINT,p_old);
    }
    else{
        p = DagNode(POINT,pSize);
    }

    if(sAlreadyPresent){
        sn = DagNode(SEGMENT,s_old);
    }
    else{
        sn = DagNode(SEGMENT, sSize);
    }

    DagNode a = DagNode(TRAPEZOID, ttop);
    DagNode b = DagNode(TRAPEZOID, tbottom);
    DagNode c = DagNode(TRAPEZOID, tother);

    //push the nodes in the dag vector
    p_id = D.replaceNode(tsplit,p);
    s_id = D.insertInVector(sn);
    if(left){
        c_id = D.insertInVector(c);
    }
    a_id = D.insertInVector(a);
    b_id = D.insertInVector(b);
    if(!left){
        c_id = D.insertInVector(c);
    }
    //set left and right children
    if(left){
        D.getElementInDVector(p_id).setLeftc(c_id);
        D.getElementInDVector(p_id).setRightc(s_id);
        D.getElementInDVector(s_id).setLeftc(a_id);
        D.getElementInDVector(s_id).setRightc(b_id);
    }
    else{
        D.getElementInDVector(p_id).setLeftc(s_id);
        D.getElementInDVector(p_id).setRightc(c_id);
        D.getElementInDVector(s_id).setLeftc(a_id);
        D.getElementInDVector(s_id).setRightc(b_id);
    }


    //push the points and the segment in the respective vector
    if(!sAlreadyPresent){
        D.insertInVector(s);
    }

    if(left){
        if(!pAlreadyPresent){
            D.insertInVector(s.p1());
        }
    }
    else{
        if(!pAlreadyPresent){
            D.insertInVector(s.p2());
        }
    }

    tId.push_back(a_id);
    tId.push_back(b_id);
    tId.push_back(c_id);

    return tId;



}

std::vector<size_t> algorithms::updateDag(Dag& D, cg3::Segment2d s, size_t tsplit, size_t ttop, size_t tbottom){
    //obtain the size of the vectors of dagNodes, points and segment
    bool alreadyPresent;
    size_t entity_position;
    D.findSegment(s,alreadyPresent,entity_position);

    size_t sSize = D.getVectorSize(SEGMENT);
    DagNode sn;

    //create id of dag nodes
    size_t s_id, a_id, b_id = SIZE_MAX;

    std::vector<size_t> tId;

    //Create point, segment and trapezoid node

    if(alreadyPresent){
        sn = DagNode(SEGMENT,entity_position);
    }
    else{
        sn = DagNode(SEGMENT,sSize);
    }
    DagNode a = DagNode(TRAPEZOID, ttop);
    DagNode b = DagNode(TRAPEZOID, tbottom);

    //push the nodes in the dag vector
    s_id = tsplit;
    D.replaceNode(tsplit,sn);
    a_id = D.insertInVector(a);
    b_id = D.insertInVector(b);
    //set left and right children
    D.getElementInDVector(s_id).setLeftc(a_id);
    D.getElementInDVector(s_id).setRightc(b_id);

    //push the segment in the respective vector
    if(!alreadyPresent){
        D.insertInVector(s);
    }

    tId.push_back(a_id);
    tId.push_back(b_id);
    return tId;
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

void algorithms::splitin2(TrapezoidalMap& T, const cg3::Segment2d& s, Dag & D, Trapezoid t_split, bool& merge_above, Trapezoid& t_merge){
    char dummy;
    Trapezoid ttop, tbottom;
    size_t merge_id, trap_id, dag_id;
    trap_id = t_split.getId();
    dag_id = t_split.getDagId();
    std::vector<size_t> dagVector;
    cg3::Segment2d proj1, proj2, internal;
    cg3::Point2d p1, p2;
    proj1 =  cg3::Segment2d(cg3::Point2d(t_split.getLeftp().x(),BOUNDINGBOX),
                               cg3::Point2d(t_split.getLeftp().x(), -BOUNDINGBOX));
    proj2 =  cg3::Segment2d(cg3::Point2d(t_split.getRightp().x(),BOUNDINGBOX),
                                cg3::Point2d(t_split.getRightp().x(), -BOUNDINGBOX));

    cg3::checkSegmentIntersection2(s,proj1,dummy,0,p1);
    cg3::checkSegmentIntersection2(s,proj2,dummy,0,p2);
    internal = cg3::Segment2d(p1,p2);

    size_t other_id, top_id, bottom_id;
    size_t * old_neighbors = t_split.getNeighbors();

    cg3::Point2d p1t, p1b, p2t, p2b;
    //the four points of intersections: the intersection with top and bottom of the two projection segments

    //calculate the intersectionss
    cg3::checkSegmentIntersection2(t_split.getTop(),proj1,dummy,0,p1t);
    cg3::checkSegmentIntersection2(t_split.getBottom(),proj1,dummy,0,p1b);
    cg3::checkSegmentIntersection2(t_split.getTop(),proj2,dummy,0,p2t);
    cg3::checkSegmentIntersection2(t_split.getBottom(),proj2,dummy,0,p2b);

    //create the trapezoid above
    ttop = Trapezoid(
                p1,
                p2,
                t_split.getTop(),
                internal
                );

    //create the trapezoid below
    tbottom = Trapezoid(
                t_split.getLeftp(),
                t_split.getRightp(),
                internal,
                t_split.getBottom()
                );

    if(merge_above){
        ttop.setLeftp(t_merge.getLeftp());
        ttop.setTop(cg3::Segment2d(t_merge.getTop().p1(),ttop.getTop().p2()));
        ttop.setBottom(cg3::Segment2d(t_merge.getBottom().p1(),ttop.getBottom().p2()));
        top_id = t_merge.getId();
        T.replaceTrapezoid(top_id,ttop);

    }
    else{
        tbottom.setLeftp(t_merge.getLeftp());
        tbottom.setTop(cg3::Segment2d(t_merge.getTop().p1(),tbottom.getTop().p2()));
        tbottom.setBottom(cg3::Segment2d(t_merge.getBottom().p1(),tbottom.getBottom().p2()));
        bottom_id = t_merge.getId();
        T.replaceTrapezoid(bottom_id,tbottom);
    }

    if(merge_above && isAbove(s,t_split.getRightp())){
        t_merge = tbottom;
        merge_above = false;
    }
    else if(!merge_above && !isAbove(s,t_split.getRightp()))
    {
        t_merge = ttop;
        merge_above = true;
    }
    else{
        if(merge_above){
            t_merge = ttop;
            bottom_id = trap_id;
            T.replaceTrapezoid(trap_id,tbottom);
        }
        else{
            t_merge = tbottom;
            top_id = trap_id;
            T.replaceTrapezoid(trap_id,ttop);
        }
    }
    dagVector = updateDag(D,s,dag_id,top_id,bottom_id);
    T.setDagId(top_id,dagVector[0]);
    T.setDagId(bottom_id,dagVector[1]);
}


/**
 * @brief algorithms::splitin3
 * This method performs a split in 3. The intersecting face t_split is removed from the trapezoidal map and the 3 new trapezoid
 * generated are inserted. The boolean parameter left determines if one of the trapezoid is to the left (true) or to the right (false).
 * Then the updateDag() method is called in order to reflect the changes in the trapezoidal map in the DAG as well.
 * @param T The trapezoidal map containing the trapezoids
 * @param s The segment that caused the split in 3
 * @param D The dag to use a search structure
 * @param t_split the trapezoid to delete
 * @param left This parameter determines if the split occurs in the left or in the right endpoint of the segment, for which
 * the split in 3 is different
 */
void algorithms::splitin3(TrapezoidalMap& T, const cg3::Segment2d& s, Dag& D, Trapezoid t_split, bool left, bool& merge_above, Trapezoid& t_merge){

    char dummy;
    Trapezoid tother, ttop, tbottom;
    size_t trap_id = t_split.getId();
    size_t dag_id = t_split.getDagId();
    cg3::Segment2d proj1, proj2;
    cg3::Point2d cross;
    std::vector<size_t> dagVector;
    //these 2 segments represent the projection on the x axis of the 2 endpoints of the segment
    if(left){
    proj1 = cg3::Segment2d(cg3::Point2d(s.p1().x(),BOUNDINGBOX), cg3::Point2d(s.p1().x(), -BOUNDINGBOX));
    proj2 = cg3::Segment2d(cg3::Point2d(t_split.getRightp().x(),BOUNDINGBOX),
                           cg3::Point2d(t_split.getRightp().x(), -BOUNDINGBOX));
    cg3::checkSegmentIntersection2(s,proj2,dummy,0,cross);
    }
    else{
        proj1 = cg3::Segment2d(cg3::Point2d(t_split.getLeftp().x(),BOUNDINGBOX),
                               cg3::Point2d(t_split.getLeftp().x(), -BOUNDINGBOX));
        proj2 = cg3::Segment2d(cg3::Point2d(s.p2().x(),BOUNDINGBOX), cg3::Point2d(s.p2().x(), -BOUNDINGBOX));
        cg3::checkSegmentIntersection2(s,proj1,dummy,0,cross);
    }

    size_t other_id, top_id, bottom_id;
    size_t * old_neighbors = t_split.getNeighbors();

    cg3::Point2d p1t, p1b, p2t, p2b;
    //the four points of intersections: the intersection with top and bottom of the two projection segments

    //calculate the intersections
    cg3::checkSegmentIntersection2(t_split.getTop(),proj1,dummy,0,p1t);
    cg3::checkSegmentIntersection2(t_split.getBottom(),proj1,dummy,0,p1b);
    cg3::checkSegmentIntersection2(t_split.getTop(),proj2,dummy,0,p2t);
    cg3::checkSegmentIntersection2(t_split.getBottom(),proj2,dummy,0,p2b);



    //create the trapezoid above
    if(left){
    ttop = Trapezoid(
                s.p1(),
                cross,
                cg3::Segment2d(p1t,t_split.getTop().p2()),
                cg3::Segment2d(s.p1(),cross)
                );

    //create the trapezoid below
    tbottom = Trapezoid(
                p1b,
                p2b,
                cg3::Segment2d(s.p1(),cross),
                cg3::Segment2d(p1b,t_split.getBottom().p2())
                );
    }
    else{
        ttop = Trapezoid(
                    cross,
                    s.p2(),
                    cg3::Segment2d(t_split.getTop().p1(),p2t),
                    cg3::Segment2d(cross,s.p2()));
        tbottom = Trapezoid(
                    p1b,
                    p2b,
                    cg3::Segment2d(cross,s.p2()),
                    cg3::Segment2d(t_split.getBottom().p1(),p2b)
                    );
    }

    //create the other trapezoid of the split (left or right depending by the endpoint)
    if(left){
        tother = Trapezoid(
                    t_split.getLeftp(),
                    s.p1(),
                    cg3::Segment2d(t_split.getTop().p1(),p1t),
                    cg3::Segment2d(t_split.getBottom().p1(),p1b)
                    );
    }
    else{
        tother = Trapezoid(
                    s.p2(),
                    t_split.getRightp(),
                    cg3::Segment2d(p2t,t_split.getTop().p2()),
                    cg3::Segment2d(p2b,t_split.getBottom().p2())
                    );
    }

    if(merge_above){
        ttop.setLeftp(t_merge.getLeftp());
        ttop.setTop(cg3::Segment2d(t_merge.getTop().p1(),ttop.getTop().p2()));
        ttop.setBottom(cg3::Segment2d(t_merge.getBottom().p1(),ttop.getBottom().p2()));
        top_id = t_merge.getId();
        T.replaceTrapezoid(top_id,ttop);

    }
    else{
        if(!left){
            tbottom.setLeftp(t_merge.getLeftp());
            tbottom.setTop(cg3::Segment2d(t_merge.getTop().p1(),tbottom.getTop().p2()));
            tbottom.setBottom(cg3::Segment2d(t_merge.getBottom().p1(),tbottom.getBottom().p2()));
            bottom_id = t_merge.getId();
            T.replaceTrapezoid(bottom_id,tbottom);
        }

   }

    if(left){
        other_id = trap_id;
        T.replaceTrapezoid(trap_id,tother);
        top_id = T.insertTrapezoid(ttop);
        bottom_id = T.insertTrapezoid(tbottom);
        if(isAbove(s,t_split.getRightp())){
            t_merge = tbottom;
            merge_above = false;
        }
        else{
            t_merge = ttop;
            merge_above = true;
        }

    }
    else{

        if(merge_above){
            bottom_id = trap_id;
            T.replaceTrapezoid(trap_id,tbottom);
            other_id = T.insertTrapezoid(tother);
        }
        else{
            top_id = trap_id;
            T.replaceTrapezoid(trap_id,ttop);
            other_id = T.insertTrapezoid(tother);
        }
    }
    dagVector = updateDag(D,s,dag_id,top_id,bottom_id,other_id,left);
    if(left){
        T.setDagId(other_id,dagVector[0]);
        T.setDagId(top_id,dagVector[1]);
        T.setDagId(bottom_id,dagVector[2]);
    }
    else{
        T.setDagId(top_id,dagVector[0]);
        T.setDagId(bottom_id,dagVector[1]);
        T.setDagId(other_id,dagVector[2]);
    }

    /*
    //all trapezoids that had tsplit as lower/upper left neighbor now have tright
    if(T.getTsize() > 4){
        T.replaceAllPositionNeighbor(TOP_LEFT,trap_id,right_id);
        T.replaceAllPositionNeighbor(BOTTOM_LEFT,trap_id,right_id);
    }

    //set neighbors of left trapezoid;
    T.setNeighbor(left_id,TOP_LEFT,old_neighbors[TOP_LEFT]);
    T.setNeighbor(left_id, TOP_RIGHT, top_id);      //the top right neighbor is the trapezoid above the segment
    T.setNeighbor(left_id,BOTTOM_LEFT,old_neighbors[BOTTOM_LEFT]);
    T.setNeighbor(left_id,BOTTOM_RIGHT,bottom_id);  //the bottom right neighbor is the trapezoid below the segment
    //top-left and bottom-left are the same of the old trapezoid

    //set neighbors of right trapezoid;
    T.setNeighbor(right_id, TOP_LEFT, top_id);      //the top right neighbor is the trapezoid above the segment
    T.setNeighbor(right_id,TOP_RIGHT,old_neighbors[TOP_RIGHT]);
    T.setNeighbor(right_id,BOTTOM_LEFT,bottom_id);  //the bottom right neighbor is the trapezoid below the segment
    T.setNeighbor(right_id,BOTTOM_RIGHT,old_neighbors[BOTTOM_RIGHT]);
    //top-right and bottom-right are the same of the old trapezoid

    //set neighbors of top trapezoid
    T.setNeighbor(top_id,TOP_LEFT,left_id);         //the top left neighbor is the trapezoid to the left of the segment
    T.setNeighbor(top_id,TOP_RIGHT,right_id);       //the top right neighbor is the trapezoid to the right of the segment
    T.setNeighbor(top_id,BOTTOM_LEFT,left_id);      //the bottom left neighbor is the trapezoid to the left of the segment
    T.setNeighbor(top_id,BOTTOM_RIGHT,right_id);    //the bottom right neighbor is the trapezoid to the right of the segment

    //set neighbors of bottom trapezoid
    T.setNeighbor(bottom_id,TOP_LEFT,left_id);      //the top left neighbor is the trapezoid to the left of the segment
    T.setNeighbor(bottom_id,TOP_RIGHT,right_id);    //the top right neighbor is the trapezoid to the right of the segment
    T.setNeighbor(bottom_id,BOTTOM_LEFT,left_id);   //the bottom left neighbor is the trapezoid to the left of the segment
    T.setNeighbor(bottom_id,BOTTOM_RIGHT,right_id); //the bottom right neighbor is the trapezoid to the right of the segment


    updateDag(D,s,dag_id,left_id,right_id,top_id,bottom_id); //update the Dag
    */
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
void algorithms::splitin4(TrapezoidalMap& T, const cg3::Segment2d& s, Dag& D, Trapezoid t_split){
    char dummy;
    size_t trap_id = t_split.getId();
    size_t dag_id = t_split.getDagId();
    std::vector<size_t> dagVector;


    //these 2 segments represent the projection on the x axis of the 2 endpoints of the segment
    cg3::Segment2d proj1 = cg3::Segment2d(cg3::Point2d(s.p1().x(),BOUNDINGBOX),
                                          cg3::Point2d(s.p1().x(), -BOUNDINGBOX));
    cg3::Segment2d proj2 = cg3::Segment2d(cg3::Point2d(s.p2().x(),BOUNDINGBOX),
                                          cg3::Point2d(s.p2().x(), -BOUNDINGBOX));

    size_t left_id, right_id, top_id, bottom_id; //the id of the 4 trapezoids
    size_t * old_neighbors = t_split.getNeighbors();

    cg3::Point2d p1t, p1b, p2t, p2b;
    //the four points of intersections: the intersection with top and bottom of the two projection segments

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

    left_id = trap_id;
    T.replaceTrapezoid(trap_id,tleft);//replace the old trapezoid in the trapezoidal map with tleft

    //insert the other trapezoids in the trapezoidal map
    top_id = T.insertTrapezoid(ttop);
    bottom_id = T.insertTrapezoid(tbottom);
    right_id = T.insertTrapezoid(tright);

    //all trapezoids that had tsplit as lower/upper left neighbor now have tright
    if(T.getTsize() > 4){
        T.replaceAllPositionNeighbor(TOP_LEFT,trap_id,right_id);
        T.replaceAllPositionNeighbor(BOTTOM_LEFT,trap_id,right_id);
    }

    //set neighbors of left trapezoid;
    T.setNeighbor(left_id,TOP_LEFT,old_neighbors[TOP_LEFT]);
    T.setNeighbor(left_id, TOP_RIGHT, top_id);      //the top right neighbor is the trapezoid above the segment
    T.setNeighbor(left_id,BOTTOM_LEFT,old_neighbors[BOTTOM_LEFT]);
    T.setNeighbor(left_id,BOTTOM_RIGHT,bottom_id);  //the bottom right neighbor is the trapezoid below the segment
    //top-left and bottom-left are the same of the old trapezoid

    //set neighbors of right trapezoid;
    T.setNeighbor(right_id, TOP_LEFT, top_id);      //the top right neighbor is the trapezoid above the segment
    T.setNeighbor(right_id,TOP_RIGHT,old_neighbors[TOP_RIGHT]);
    T.setNeighbor(right_id,BOTTOM_LEFT,bottom_id);  //the bottom right neighbor is the trapezoid below the segment
    T.setNeighbor(right_id,BOTTOM_RIGHT,old_neighbors[BOTTOM_RIGHT]);
    //top-right and bottom-right are the same of the old trapezoid

    //set neighbors of top trapezoid
    T.setNeighbor(top_id,TOP_LEFT,left_id);         //the top left neighbor is the trapezoid to the left of the segment
    T.setNeighbor(top_id,TOP_RIGHT,right_id);       //the top right neighbor is the trapezoid to the right of the segment
    T.setNeighbor(top_id,BOTTOM_LEFT,left_id);      //the bottom left neighbor is the trapezoid to the left of the segment
    T.setNeighbor(top_id,BOTTOM_RIGHT,right_id);    //the bottom right neighbor is the trapezoid to the right of the segment

    //set neighbors of bottom trapezoid
    T.setNeighbor(bottom_id,TOP_LEFT,left_id);      //the top left neighbor is the trapezoid to the left of the segment
    T.setNeighbor(bottom_id,TOP_RIGHT,right_id);    //the top right neighbor is the trapezoid to the right of the segment
    T.setNeighbor(bottom_id,BOTTOM_LEFT,left_id);   //the bottom left neighbor is the trapezoid to the left of the segment
    T.setNeighbor(bottom_id,BOTTOM_RIGHT,right_id); //the bottom right neighbor is the trapezoid to the right of the segment


    dagVector = updateDag(D,s,dag_id,left_id,right_id,top_id,bottom_id); //update the Dag
    T.setDagId(left_id,dagVector[0]);
    T.setDagId(top_id,dagVector[1]);
    T.setDagId(bottom_id,dagVector[2]);
    T.setDagId(right_id,dagVector[3]);
}

/**
 * @brief algorithms::multipleSplit
 * This method performs a multiple split when a segment intersects more than a trapezoid.
 * @param T the trapezoidal map containing the trapezoids
 * @param s the segment inserted
 * @param D the dag to use as a search structure
 * @param delta the list of trapezoids intersected by the segment s
 */
void algorithms::multipleSplit(TrapezoidalMap& T, const cg3::Segment2d& s, Dag& D, std::vector<Trapezoid> delta){
    bool merge_above = false;
    Trapezoid t_merge;
    for(size_t i = 0; i < delta.size(); i++){
        if(i == 0){
            splitin3(T,s,D,delta[0],true,merge_above,t_merge);
        }
        else if(i == delta.size() - 1){
            splitin3(T,s,D,delta[delta.size()-1],false,merge_above,t_merge);
        }
        else{
            splitin2(T,s,D,delta[i],merge_above,t_merge);
        }
    }


}

