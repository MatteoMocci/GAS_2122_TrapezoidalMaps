#include "algorithms.h"
#define TOP_LEFT 0
#define TOP_RIGHT 1
#define BOTTOM_LEFT 2
#define BOTTOM_RIGHT 3


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
        if(utility::isAbove(s,delta[j].getRightp())){//if rightp(Δj) lies above si
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
 * @return the vector with the ids of the dag of the 4 trapezoids
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
/**
 * @brief algorithms::updateDag
 * This is an override of the updateDag function to manage the case of a split in 3. This function returns the vector with the dag id's
 * of the 3 trapezoids, in order to update the field of the trapezoid in the split in 3 algorithm.
 * @param D The dag to update
 * @param s The segment that caused the split and thus the update of the dag
 * @param tsplit the id of the dagNode of the Trapezoid intersected by the segment
 * @param ttop The id of the trapezoid on the top
 * @param tbottom The id of the trapezoid on the bottom
 * @param tother The id of the other trapezoid (left or right)
 * @param left a boolean value that determines if the split in 3 is on the left or on the right
 * @return the vector with the id of the dagNodes representing the 3 trapezoids inserted in the Dag.
 */
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
/**
 * @brief algorithms::updateDag
 * This override of updateDag is used when a split in 2 occurs. As always, the vector of the dagNode id's created for the trapezoids
 * in order to update the field of the trapezoid that stores the position in the Dag in which the trapezoid is present
 * @param D the Dag to update
 * @param s the segment that caused the split and thus the update of the Dag
 * @param tsplit the id of the DagNode representing the trapezoid that is intersected by the segment
 * @param ttop the id of the Trapezoid above the segment
 * @param tbottom the id of the Trapezoid below the segment
 * @return A vector with the id's of the DagNodes representing the top and bottom trapezoid
 */
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
 * @brief algorithms::updateDag
 * This algorithm performs an update of the Dag when a split in 4 occurs with one of the endpoints of the segment being coincident
 * to another one
 * @param D, a reference to the Dag to update
 * @param s, the segment that caused the split
 * @param coincidence, LEFT if the left endpoint is coincident, RIGHT if the right endpoint is coincident
 * @param tsplit, the id of the trapezoid intersected by the segment
 * @param tother, the id of the trapezoid to the side of the segment, in case of left-coincidence, tother is to the right, while in case of
 * right coincidence, tother is to the left
 * @param ttop, the id of the trapezoid above the segment
 * @param tbottom, the id of the trapezoid below the segment
 * @return a vector with the dag ids of the three trapezoids
 */
std::vector<size_t> algorithms::updateDag(Dag& D, cg3::Segment2d s, coincidence coincidence, size_t tsplit, size_t tother, size_t ttop, size_t tbottom){
    //obtain the size of the vectors of dagNodes, points and segment
    size_t pSize = D.getVectorSize(POINT);
    size_t sSize = D.getVectorSize(SEGMENT);
    std::vector<size_t> tId;

    DagNode p, sn,a,b,c;

    //create id of dag nodes
    size_t p_id, s_id, a_id, b_id, c_id = SIZE_MAX;

    //Create point, segment and trapezoid node
    p = DagNode(POINT,pSize);
    sn = DagNode(SEGMENT, sSize);

    switch(coincidence){
    case LEFT:
        a = DagNode(TRAPEZOID,ttop);
        b = DagNode(TRAPEZOID,tbottom);
        c = DagNode(TRAPEZOID,tother);
        break;
    case RIGHT:
        a = DagNode(TRAPEZOID,tother);
        b = DagNode(TRAPEZOID,ttop);
        c = DagNode(TRAPEZOID,tbottom);
        break;
    default:
        break;
    }

    p_id = D.replaceNode(tsplit,p);
    s_id = D.insertInVector(sn);
    a_id = D.insertInVector(a);
    b_id = D.insertInVector(b);
    c_id = D.insertInVector(c);

    switch(coincidence){
    case LEFT:
        D.getElementInDVector(p_id).setLeftc(s_id);
        D.getElementInDVector(p_id).setRightc(c_id);
        D.getElementInDVector(s_id).setLeftc(a_id);
        D.getElementInDVector(s_id).setRightc(b_id);
        D.insertInVector(s.p2());
        break;
    case RIGHT:
        D.getElementInDVector(p_id).setLeftc(a_id);
        D.getElementInDVector(p_id).setRightc(s_id);
        D.getElementInDVector(s_id).setLeftc(b_id);
        D.getElementInDVector(s_id).setRightc(c_id);
        D.insertInVector(s.p1());
        break;
    default:
        break;
    }

    D.insertInVector(s);
    tId.push_back(a_id);
    tId.push_back(b_id);
    tId.push_back(c_id);
    return tId;
}

/**
 * @brief algorithms::updateDag
 * This algorithm performs an update of the Dag when a split in 4 occurs when both endpoints are shared
 * or when a split in 3 with an endpoint coincident occurs.
 * @param D, a reference to the Dag to update
 * @param s, the segment that caused the split
 * @param coincidence, the end point that is coincident (LEFT for a split in 3 to the left, RIGHT for a
 * split in 3 to the right, BOTH for a split in 2 with both endpoints shared)
 * @param tsplit, the id of the trapezoid intersected by the segment
 * @param ttop, the id of the trapezoid above the segment
 * @param tbottom, the id of the trapezoid below the segment
 * @return a vector with the dag ids of the two trapezoids
 */
std::vector<size_t> algorithms::updateDag(Dag& D, cg3::Segment2d s, coincidence coincidence, size_t tsplit, size_t ttop, size_t tbottom){
    //obtain the size of the vectors of dagNodes, points and segment
    size_t sSize = D.getVectorSize(SEGMENT);
    std::vector<size_t> tId;

    DagNode sn,a,b;

    //create id of dag nodes
    size_t s_id, a_id, b_id = SIZE_MAX;

    //Create point, segment and trapezoid node
    sn = DagNode(SEGMENT, sSize);
    a  = DagNode(TRAPEZOID,ttop);
    b  = DagNode(TRAPEZOID,tbottom);

    s_id = D.replaceNode(tsplit,sn);
    a_id = D.insertInVector(a);
    b_id = D.insertInVector(b);

    D.getElementInDVector(s_id).setLeftc(a_id);
    D.getElementInDVector(s_id).setRightc(b_id);
    D.insertInVector(s);

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
                if(utility::isAbove(s,p)){//check if the point is above the segment
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
 * @brief algorithms::splitin2
 * This algorithm performs a split in 2. The old trapezoid is divided in one above and one below. One of the two has to be merged with
 * a previous trapezoid t_merge. The boolean parameter merge_above establishes which of the two has to be merged.
 * The neighbors of the trapezoids are set.
 * The updateDag() method is called in order to reflect the changes in the trapezoidal map in the DAG as well.
 * @param T The trapezoidal Map containing the trapezoids
 * @param s The segment that caused the split
 * @param D The dag that is a search structure for the trapezoidal Map
 * @param trap_id the id of the trapezoid that is intersected by the segment
 * @param merge_above a boolean value that establishes if the trapezoid that has to be merged with the previous is the top or bottom one
 * @param t_merge The trapezoid from the previous split that needs to be merged
 * @param t_prev The id of the other trapezoid from the previous split. It is necessary in order to update its neighbors.
 * @param next The id of the next trapezoid that is intersected by the segment. In this way, the neighbors of this trapezoid
 * won't be updated, since a split will occur after this one
 */
void algorithms::splitin2(TrapezoidalMap& T, const cg3::Segment2d& s, Dag & D, size_t trap_id, bool& merge_above, Trapezoid& t_merge, size_t & t_prev, size_t next, bool& first){
    char dummy;
    Trapezoid ttop, tbottom, t_split;
    size_t merge_id, dag_id;
    t_split = T.getTrapezoid(trap_id);
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
                t_split.getLeftp(),
                t_split.getRightp(),
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
            ttop.setNeighbors(t_merge.getNeighbors());
            top_id = t_merge.getId();
            T.replaceTrapezoid(top_id,ttop);
            bottom_id = trap_id;
            T.replaceTrapezoid(bottom_id,tbottom);
            tbottom.setNeighbors(t_split.getNeighbors());
        }
        else{

            tbottom.setLeftp(t_merge.getLeftp());
            tbottom.setTop(cg3::Segment2d(t_merge.getTop().p1(),tbottom.getTop().p2()));
            tbottom.setBottom(cg3::Segment2d(t_merge.getBottom().p1(),tbottom.getBottom().p2()));
            tbottom.setNeighbors(t_merge.getNeighbors());
            bottom_id = t_merge.getId();
            T.replaceTrapezoid(bottom_id,tbottom);
            top_id = trap_id;
            T.replaceTrapezoid(top_id,ttop);
            ttop.setNeighbors(t_split.getNeighbors());
        }


    if(merge_above){
        T.replaceAllPositionNeighbor(TOP_LEFT,trap_id,bottom_id,next);
        T.replaceAllPositionNeighbor(BOTTOM_LEFT,trap_id,bottom_id,next);
    }
    else{
        T.replaceAllPositionNeighbor(TOP_LEFT,trap_id,top_id,next);
        T.replaceAllPositionNeighbor(BOTTOM_LEFT,trap_id,top_id,next);
    }

    if(merge_above){
        if(utility::isAbove(T.getTrapezoid(t_prev).getBottom(),tbottom.getTop().p1())){
            T.setNeighbor(bottom_id,TOP_LEFT,t_prev);
        }
        if(!utility::isAbove(tbottom.getBottom(),T.getTrapezoid(t_prev).getBottom().p2())){
            T.setNeighbor(bottom_id,BOTTOM_LEFT,t_prev);
        }
        if(!utility::isAbove(tbottom.getBottom(),T.getTrapezoid(t_prev).getTop().p2())){
            T.setNeighbor(t_prev,TOP_RIGHT,bottom_id);
        }
        if(utility::isAbove(tbottom.getBottom(),T.getTrapezoid(t_prev).getBottom().p2())){
            T.setNeighbor(t_prev,BOTTOM_RIGHT,bottom_id);
        }

    }
    else{
        if(utility::isAbove(ttop.getTop(),T.getTrapezoid(t_prev).getTop().p2())){
            T.setNeighbor(top_id,TOP_LEFT,t_prev);
        }
        if(utility::isAbove(T.getTrapezoid(t_prev).getBottom(),ttop.getBottom().p1()) || T.getTrapezoid(t_prev).getBottom().p2() == ttop.getBottom().p1()){
            T.setNeighbor(top_id,BOTTOM_LEFT,t_prev);
        }
        if(!utility::isAbove(ttop.getTop(),T.getTrapezoid(t_prev).getTop().p1())){
            T.setNeighbor(t_prev,TOP_RIGHT,top_id);
        }
        if(utility::isAbove(ttop.getBottom(),T.getTrapezoid(t_prev).getBottom().p2())){
            T.setNeighbor(t_prev,BOTTOM_RIGHT,top_id);
        }
    }

    if(merge_above && utility::isAbove(s,t_split.getRightp())){
        t_merge = T.getTrapezoid(bottom_id);
        merge_above = false;
        t_prev = top_id;
        first = true;
    }
    else if(!merge_above && !utility::isAbove(s,t_split.getRightp()))
    {
        t_merge = T.getTrapezoid(top_id);
        merge_above = true;
        t_prev = bottom_id;
        first = true;
    }
    else{
        if(merge_above){
            t_merge = T.getTrapezoid(top_id);
            bottom_id = trap_id;
            t_prev = bottom_id;
            first = false;
        }
        else{
            t_merge = T.getTrapezoid(bottom_id);
            top_id = trap_id;
            t_prev = top_id;
            first = false;
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
 * @param merge_above a boolean value that determines if the merge has to be done with the trapezoid above or below the segment
 * @param t_merge a reference to the previous trapezoid that has to be merged
 * @param t_prev the id of the other trapezoid generated in the previous split. This is necessary in order to update the neighbors
 * @param next the id of the next Trapezoid that is intersected by the segment. This is necessary in order to avoid to update
 * his neighbors because new trapezoids will be generated in the next split
 */
void algorithms::splitin3(TrapezoidalMap& T, const cg3::Segment2d& s, Dag& D, size_t trap_id, bool left, bool& merge_above, Trapezoid & t_merge, size_t & t_prev, size_t next, bool& first){

    coincidence coincidence;
    bool coincident_above;
    char dummy;
    Trapezoid t_split, tother, ttop, tbottom;
    t_split = T.getTrapezoid(trap_id);
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
                    t_split.getRightp(),
                    cg3::Segment2d(p1t,t_split.getTop().p2()),
                    cg3::Segment2d(s.p1(),cross)
                    );

    //create the trapezoid below
        tbottom = Trapezoid(
                    s.p1(),
                    t_split.getRightp(),
                    cg3::Segment2d(s.p1(),cross),
                    cg3::Segment2d(p1b,t_split.getBottom().p2())
                    );

        if(ttop.getTop().p1() == ttop.getBottom().p1()){
            coincidence = LEFT;
            coincident_above = true;
        }
        else if(tbottom.getTop().p1() == tbottom.getBottom().p1()){
            coincidence = LEFT;
            coincident_above = false;
        }
        else{
            coincidence = NONE;
        }
    }

    else{
        ttop = Trapezoid(
                    t_split.getLeftp(),
                    s.p2(),
                    cg3::Segment2d(t_split.getTop().p1(),p2t),
                    cg3::Segment2d(cross,s.p2()));
        tbottom = Trapezoid(
                    t_split.getLeftp(),
                    s.p2(),
                    cg3::Segment2d(cross,s.p2()),
                    cg3::Segment2d(t_split.getBottom().p1(),p2b)
                    );
        if(ttop.getTop().p1() == ttop.getBottom().p1()){
            coincidence = RIGHT;
            coincident_above = true;
        }
        else if(tbottom.getTop().p1() == tbottom.getBottom().p1()){
            coincidence = RIGHT;
            coincident_above = false;
        }
        else{
            coincidence = NONE;
        }

    }

    //create the other trapezoid of the split (left or right depending by the endpoint)
    if(left && coincidence == NONE){
        tother = Trapezoid(
                    t_split.getLeftp(),
                    s.p1(),
                    cg3::Segment2d(t_split.getTop().p1(),p1t),
                    cg3::Segment2d(t_split.getBottom().p1(),p1b)
                    );
    }
    else if(coincidence == NONE){
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
        ttop.setNeighbors(t_merge.getNeighbors());
        top_id = t_merge.getId();
        T.replaceTrapezoid(top_id,ttop);

    }
    else{
        if(!left){
            tbottom.setLeftp(t_merge.getLeftp());
            tbottom.setTop(cg3::Segment2d(t_merge.getTop().p1(),tbottom.getTop().p2()));
            tbottom.setBottom(cg3::Segment2d(t_merge.getBottom().p1(),tbottom.getBottom().p2()));
            tbottom.setNeighbors(t_merge.getNeighbors());
            bottom_id = t_merge.getId();
            T.replaceTrapezoid(bottom_id,tbottom);
        }

   }

    if(left){
        other_id = trap_id;
        tother.setNeighbors(t_split.getNeighbors());
        ttop.setNeighbors(t_split.getNeighbors());
        tbottom.setNeighbors(t_split.getNeighbors());
        T.replaceTrapezoid(trap_id,tother);
        top_id = T.insertTrapezoid(ttop);
        bottom_id = T.insertTrapezoid(tbottom);

    }
    else{

        if(merge_above){
            bottom_id = trap_id;
            tbottom.setNeighbors(t_split.getNeighbors());

            //tbottom.setNeighbor(TOP_LEFT,t_split.getNeighbor(BOTTOM_LEFT));
            /*
            if(!utility::isAbove(s,tbottom.getTop().p1())){
                tbottom.setNeighbor(TOP_LEFT,t_split.getNeighbor(BOTTOM_LEFT));
            }

            if(utility::isAbove(s,tbottom.getLeftp())){
                tbottom.setNeighbor(BOTTOM_LEFT,t_split.getNeighbor(TOP_LEFT));
            }
            */
            T.replaceTrapezoid(trap_id,tbottom);
            other_id = T.insertTrapezoid(tother);
        }
        else{
            top_id = trap_id;
            ttop.setNeighbors(t_split.getNeighbors());
            T.replaceTrapezoid(trap_id,ttop);
            other_id = T.insertTrapezoid(tother);
        }
    }
    switch(coincidence){
    case NONE:
        dagVector = updateDag(D,s,dag_id,top_id,bottom_id,other_id,left);
        if(left){
            T.setDagId(other_id,dagVector[2]);
            T.setDagId(top_id,dagVector[0]);
            T.setDagId(bottom_id,dagVector[1]);
        }
        else{
            T.setDagId(top_id,dagVector[0]);
            T.setDagId(bottom_id,dagVector[1]);
            T.setDagId(other_id,dagVector[2]);
        }
        break;
    case LEFT:
    case RIGHT:
        dagVector = updateDag(D,s,coincidence,dag_id,top_id,bottom_id);
        T.setDagId(top_id,dagVector[0]);
        T.setDagId(bottom_id,dagVector[1]);
        break;
    default:
        break;
    }


    if(left){
        //set neighbors of left trapezoid
        if(coincidence == NONE){
        T.setNeighbor(other_id,TOP_LEFT,old_neighbors[TOP_LEFT]);
        T.setNeighbor(other_id, TOP_RIGHT, top_id);      //the top right neighbor is the trapezoid above the segment
        T.setNeighbor(other_id,BOTTOM_LEFT,old_neighbors[BOTTOM_LEFT]);
        T.setNeighbor(other_id,BOTTOM_RIGHT,bottom_id);  //the bottom right neighbor is the trapezoid below the segment
        //top-left and bottom-left are the same of the old trapezoid

        //set neighbors of top trapezoid
        T.setNeighbor(top_id,TOP_LEFT,other_id);         //the top left neighbor is the trapezoid to the left of the segment
        //T.setNeighbor(top_id,TOP_RIGHT,old_neighbors[TOP_RIGHT]);       //the top right neighbor is the trapezoid to the right of the segment
        T.setNeighbor(top_id,BOTTOM_LEFT,other_id);      //the bottom left neighbor is the trapezoid to the left of the segment
        //T.setNeighbor(top_id,BOTTOM_RIGHT,old_neighbors[BOTTOM_RIGHT]);    //the bottom right neighbor is the trapezoid to the right of the segment

        //set neighbors of bottom trapezoid
        T.setNeighbor(bottom_id,TOP_LEFT,other_id);      //the top left neighbor is the trapezoid to the left of the segment
        //T.setNeighbor(bottom_id,TOP_RIGHT,old_neighbors[TOP_RIGHT]);    //the top right neighbor is the trapezoid to the right of the segment
        T.setNeighbor(bottom_id,BOTTOM_LEFT,other_id);   //the bottom left neighbor is the trapezoid to the left of the segment
        //T.setNeighbor(bottom_id,BOTTOM_RIGHT,old_neighbors[BOTTOM_RIGHT]); //the bottom right neighbor is the trapezoid to the right of the segment
        }
        else{
            if(coincident_above){
                T.setNeighbor(top_id,TOP_LEFT,SIZE_MAX);
                T.setNeighbor(top_id,BOTTOM_LEFT,SIZE_MAX);
            }
            else{
                T.setNeighbor(bottom_id,TOP_LEFT,SIZE_MAX);
                T.setNeighbor(bottom_id,BOTTOM_LEFT,SIZE_MAX);
            }
        }

    }
    else{
        if(coincidence == NONE){
        //set neighbors of top trapezoid
        //T.setNeighbor(top_id,TOP_LEFT,old_neighbors[TOP_LEFT]);         //the top left neighbor is the trapezoid to the left of the segment
        T.setNeighbor(top_id,TOP_RIGHT,other_id);       //the top right neighbor is the trapezoid to the right of the segment
        //T.setNeighbor(top_id,BOTTOM_LEFT,old_neighbors[BOTTOM_LEFT]);      //the bottom left neighbor is the trapezoid to the left of the segment
        T.setNeighbor(top_id,BOTTOM_RIGHT,other_id);    //the bottom right neighbor is the trapezoid to the right of the segment

        //set neighbors of right trapezoid;
        T.setNeighbor(other_id, TOP_LEFT, top_id);      //the top right neighbor is the trapezoid above the segment
        T.setNeighbor(other_id,TOP_RIGHT,old_neighbors[TOP_RIGHT]);
        T.setNeighbor(other_id,BOTTOM_LEFT,bottom_id);  //the bottom right neighbor is the trapezoid below the segment
        T.setNeighbor(other_id,BOTTOM_RIGHT,old_neighbors[BOTTOM_RIGHT]);
        //top-right and bottom-right are the same of the old trapezoid

        //set neighbors of bottom trapezoid
        //T.setNeighbor(bottom_id,TOP_LEFT,old_neighbors[TOP_LEFT]);      //the top left neighbor is the trapezoid to the left of the segment
        T.setNeighbor(bottom_id,TOP_RIGHT,other_id);    //the top right neighbor is the trapezoid to the right of the segment
        //T.setNeighbor(bottom_id,BOTTOM_LEFT,old_neighbors[BOTTOM_LEFT]);   //the bottom left neighbor is the trapezoid to the left of the segment
        T.setNeighbor(bottom_id,BOTTOM_RIGHT,other_id); //the bottom right neighbor is the trapezoid to the right of the segment
        }
        else{
            if(coincident_above){
                T.setNeighbor(top_id,TOP_RIGHT,SIZE_MAX);
                T.setNeighbor(top_id,BOTTOM_RIGHT,SIZE_MAX);
            }
            else{
                T.setNeighbor(bottom_id,TOP_RIGHT,SIZE_MAX);
                T.setNeighbor(bottom_id,BOTTOM_RIGHT,SIZE_MAX);
            }
        }

        if(merge_above){
            if(utility::isAbove(T.getTrapezoid(t_prev).getBottom(),tbottom.getTop().p1())){
            T.setNeighbor(bottom_id,TOP_LEFT,t_prev);
            }
            if(!utility::isAbove(tbottom.getBottom(),T.getTrapezoid(t_prev).getBottom().p2())){
                T.setNeighbor(bottom_id,BOTTOM_LEFT,t_prev);
            }
            if(!utility::isAbove(tbottom.getBottom(),T.getTrapezoid(t_prev).getTop().p2())){
                T.setNeighbor(t_prev,TOP_RIGHT,bottom_id);
            }
            if(utility::isAbove(tbottom.getBottom(),T.getTrapezoid(t_prev).getBottom().p2())){
                T.setNeighbor(t_prev,BOTTOM_RIGHT,bottom_id);
            }

        }
        else{
            if(utility::isAbove(ttop.getTop(),T.getTrapezoid(t_prev).getTop().p2())){
                T.setNeighbor(top_id,TOP_LEFT,t_prev);
            }
            if(utility::isAbove(T.getTrapezoid(t_prev).getBottom(),ttop.getBottom().p1()) || T.getTrapezoid(t_prev).getBottom().p2() == ttop.getBottom().p1()){
                T.setNeighbor(top_id,BOTTOM_LEFT,t_prev);
            }
            if(!utility::isAbove(ttop.getTop(),T.getTrapezoid(t_prev).getTop().p1()) ){
                T.setNeighbor(t_prev,TOP_RIGHT,top_id);
            }
            if(utility::isAbove(ttop.getBottom(),T.getTrapezoid(t_prev).getBottom().p2())){
                T.setNeighbor(t_prev,BOTTOM_RIGHT,top_id);
            }
        }
    }

    if(left){
        T.replaceAllPositionNeighbor(s,TOP_LEFT,trap_id,top_id,bottom_id,next);
        T.replaceAllPositionNeighbor(s,BOTTOM_LEFT,trap_id,top_id,bottom_id,next);
    }
    else{
        if(coincidence == NONE){
            T.replaceAllPositionNeighbor(TOP_LEFT,trap_id,other_id,next);
            T.replaceAllPositionNeighbor(BOTTOM_LEFT,trap_id,other_id,next);
        }
    }


    if(left){
        if(utility::isAbove(s,t_split.getRightp())){
            t_merge = T.getTrapezoid(bottom_id);
            merge_above = false;
            t_prev = top_id;
            first = false;
        }else{
            t_merge = T.getTrapezoid(top_id);
            merge_above = true;
            t_prev = bottom_id;
            first = false;
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
 * @param trap_id the id of the trapezoid intersected by the segment
 */
void algorithms::splitin4(TrapezoidalMap& T, const cg3::Segment2d& s, Dag& D, size_t trap_id){
    coincidence c = NONE;
    bool coincident_above;
    char dummy;
    Trapezoid t_split = T.getTrapezoid(trap_id);
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

    if(ttop.getTop().p1() == ttop.getBottom().p1()){
        c = LEFT;
        coincident_above = true;
    }
    else if(tbottom.getTop().p1() == tbottom.getBottom().p1()){
        c = LEFT;
        coincident_above = false;
    }


    if(ttop.getTop().p2() == ttop.getBottom().p2()){
        if(c != LEFT){
            c = RIGHT;
        }
        else{
            c = BOTH;
        }
        coincident_above = true;
    }
    else if(tbottom.getTop().p2() == tbottom.getBottom().p2()){
        if(c != LEFT){
            c = RIGHT;
        }
        else{
            c = BOTH;
        }
        coincident_above = false;
    }

    if(c != LEFT){
        left_id = trap_id;
        T.replaceTrapezoid(trap_id,tleft);//replace the old trapezoid in the trapezoidal map with tleft
    }

    //insert the other trapezoids in the trapezoidal map
    top_id = T.insertTrapezoid(ttop);
    bottom_id = T.insertTrapezoid(tbottom);

    if(c != RIGHT && c != BOTH){
        right_id = T.insertTrapezoid(tright);
    }

    //all trapezoids that had tsplit as lower/upper left neighbor now have tright
    if(T.getTsize() > 4){
        T.replaceAllPositionNeighbor(TOP_LEFT,trap_id,right_id);
        T.replaceAllPositionNeighbor(BOTTOM_LEFT,trap_id,right_id);
    }

    if(c != LEFT && c != BOTH){
    //set neighbors of left trapezoid;
        T.setNeighbor(left_id,TOP_LEFT,old_neighbors[TOP_LEFT]);
        T.setNeighbor(left_id, TOP_RIGHT, top_id);      //the top right neighbor is the trapezoid above the segment
        T.setNeighbor(left_id,BOTTOM_LEFT,old_neighbors[BOTTOM_LEFT]);
        T.setNeighbor(left_id,BOTTOM_RIGHT,bottom_id);  //the bottom right neighbor is the trapezoid below the segment
    //top-left and bottom-left are the same of the old trapezoid
    }
    else{
        if(coincident_above){
            T.setNeighbor(top_id,TOP_LEFT,SIZE_MAX);
            T.setNeighbor(top_id,BOTTOM_LEFT,SIZE_MAX);
        }
        else{
            T.setNeighbor(bottom_id,TOP_LEFT,SIZE_MAX);
            T.setNeighbor(bottom_id,BOTTOM_LEFT,SIZE_MAX);
        }
    }

    if(c!= RIGHT && c!= BOTH){
    //set neighbors of right trapezoid;
        T.setNeighbor(right_id, TOP_LEFT, top_id);      //the top right neighbor is the trapezoid above the segment
        T.setNeighbor(right_id,TOP_RIGHT,old_neighbors[TOP_RIGHT]);
        T.setNeighbor(right_id,BOTTOM_LEFT,bottom_id);  //the bottom right neighbor is the trapezoid below the segment
        T.setNeighbor(right_id,BOTTOM_RIGHT,old_neighbors[BOTTOM_RIGHT]);
    //top-right and bottom-right are the same of the old trapezoid
    }
    else{
        if(coincident_above){
            T.setNeighbor(top_id,TOP_RIGHT,SIZE_MAX);
            T.setNeighbor(top_id,BOTTOM_RIGHT,SIZE_MAX);
        }
        else{
            T.setNeighbor(bottom_id,TOP_RIGHT,SIZE_MAX);
            T.setNeighbor(bottom_id,BOTTOM_RIGHT,SIZE_MAX);
        }
    }

    //set neighbors of top trapezoid
    if(c!= LEFT && c != BOTH){
        T.setNeighbor(top_id,TOP_LEFT,left_id);         //the top left neighbor is the trapezoid to the left of the segment
    }
    if(c!= RIGHT && c != BOTH){
        T.setNeighbor(top_id,TOP_RIGHT,right_id); //the top right neighbor is the trapezoid to the right of the segment
    }
    if(c!= LEFT && c != BOTH){
        T.setNeighbor(top_id,BOTTOM_LEFT,left_id);      //the bottom left neighbor is the trapezoid to the left of the segment
    }
    if(c!= RIGHT && c != BOTH){
        T.setNeighbor(top_id,BOTTOM_RIGHT,right_id);    //the bottom right neighbor is the trapezoid to the right of the segment
    }

    //set neighbors of bottom trapezoid
    if(c!= LEFT && c != BOTH){
        T.setNeighbor(bottom_id,TOP_LEFT,left_id);      //the top left neighbor is the trapezoid to the left of the segment
    }
    if(c!= RIGHT && c != BOTH){
        T.setNeighbor(bottom_id,TOP_RIGHT,right_id);    //the top right neighbor is the trapezoid to the right of the segment
    }
    if(c!= LEFT && c != BOTH){
        T.setNeighbor(bottom_id,BOTTOM_LEFT,left_id);   //the bottom left neighbor is the trapezoid to the left of the segment
    }
    if(c!= RIGHT && c != BOTH){
        T.setNeighbor(bottom_id,BOTTOM_RIGHT,right_id); //the bottom right neighbor is the trapezoid to the right of the segment
    }

    switch(c){
    case NONE:
        dagVector = updateDag(D,s,dag_id,left_id,right_id,top_id,bottom_id); //update the Dag
        T.setDagId(left_id,dagVector[0]);
        T.setDagId(top_id,dagVector[1]);
        T.setDagId(bottom_id,dagVector[2]);
        T.setDagId(right_id,dagVector[3]);
        break;
    case LEFT:
        dagVector = updateDag(D,s,c,dag_id,right_id,top_id,bottom_id);
        T.setDagId(top_id,dagVector[0]);
        T.setDagId(bottom_id,dagVector[1]);
        T.setDagId(right_id,dagVector[2]);
        break;
    case RIGHT:
        dagVector = updateDag(D,s,c,dag_id,left_id,top_id,bottom_id);
        T.setDagId(left_id,dagVector[0]);
        T.setDagId(top_id,dagVector[1]);
        T.setDagId(bottom_id,dagVector[2]);
        break;
    case BOTH:
        dagVector = updateDag(D,s,c,dag_id,top_id,bottom_id);
        T.setDagId(top_id,dagVector[0]);
        T.setDagId(bottom_id,dagVector[1]);
        break;
    }

}

/**
 * @brief algorithms::multipleSplit
 * This method performs a multiple split when a segment intersects more than a trapezoid.
 * A split in 3 to the left is called for the first trapezoid, a split in 3 to the right is called for the last trapezoid and, if
 * there are more than 2 elements, a split in 2 is called for all of the middle trapezoids.
 * @param T a reference to the trapezoidal map containing the trapezoids
 * @param s a reference to the segment inserted
 * @param D a reference to the dag to use as a search structure
 * @param delta the list of trapezoids intersected by the segment s
 */
void algorithms::multipleSplit(TrapezoidalMap& T, const cg3::Segment2d& s, Dag& D, std::vector<Trapezoid> delta){
    bool merge_above = false;
    bool first = true;
    size_t t_prev;
    Trapezoid t_merge;
    for(size_t i = 0; i < delta.size(); i++){
        if(i == 0){
            splitin3(T,s,D,delta[0].getId(),true,merge_above,t_merge,t_prev,delta[1].getId(),first);
        }
        else if(i == delta.size() - 1){
            splitin3(T,s,D,delta[delta.size()-1].getId(),false,merge_above,t_merge,t_prev,delta[i+1].getId(),first);
        }
        else{
            splitin2(T,s,D,delta[i].getId(),merge_above,t_merge,t_prev,delta[i+1].getId(),first);
        }
    }


}

