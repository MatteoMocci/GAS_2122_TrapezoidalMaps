#include "trapezoidalmap.h"
#define TOP_LEFT 0
#define TOP_RIGHT 1
#define BOTTOM_LEFT 2
#define BOTTOM_RIGHT 3

/**
 * @brief TrapezoidalMap::TrapezoidalMap
 * This is the constructor of the trapezoidal map. This constructor calls the method which inserts the trapezoid
 * representing the bounding box into the vector.
 */
TrapezoidalMap::TrapezoidalMap()
{
    insertBoundingBoxT();
}

/**
 * @brief TrapezoidalMap::insertBoundingBoxT
 * This method inserts the trapezoid representing the bounding box into the trapezoidal map
 */
void TrapezoidalMap::insertBoundingBoxT(){
    Trapezoid t = Trapezoid(cg3::Point2d(-BOUNDINGBOX,-BOUNDINGBOX),
                  cg3::Point2d(BOUNDINGBOX,-BOUNDINGBOX),
                  cg3::Segment2d(cg3::Point2d(-BOUNDINGBOX,BOUNDINGBOX),cg3::Point2d(BOUNDINGBOX,BOUNDINGBOX)),
                  cg3::Segment2d(cg3::Point2d(-BOUNDINGBOX,-BOUNDINGBOX),cg3::Point2d(BOUNDINGBOX,-BOUNDINGBOX))
                  );
    t.setId(0); //the bounding box is the first trapezoid to be inserted, thus it occupies the position 0
    t.setColor(cg3::Color(144,238,144)); //the color of the bounding box is light green
    t.setDagId(0);
    t_map.push_back(t); //the trapezoid is inserted at the end of the vector
}

/**
 * @brief TrapezoidalMap::getMap
 * @return the vector containing the trapezoids of the trapezoidal map
 */
const std::vector<Trapezoid> TrapezoidalMap::getMap() const{
    return t_map;
}

/**
 * @brief TrapezoidalMap::insertTrapezoid
 * This method sets the id of a trapezoid, inserts the trapezoid into the vector and returns the position
 * in which the trapezoid is inserted
 * @param t the reference to the trapezoid to insert
 * @return the position in which the trapezoid is inserted
 */
size_t TrapezoidalMap::insertTrapezoid(Trapezoid& t){
    t.setId(t_map.size()); //size of the map = index of the last element + 1 and the new trapezoid will be
    t_map.push_back(t); //insert the trapezoid in the last position of the vector
    return t_map.size() - 1;
}

/**
 * @brief TrapezoidalMap::replaceTrapezoid
 * When a segment is inserted, the trapezoids intersected
 * are deleted and replaced with new trapezoids and this method manages this operation.
 * @param index the position in the vector of the trapezoid to delete
 * @param t the trapezoid to insert at his place
 */
void TrapezoidalMap::replaceTrapezoid(size_t index, Trapezoid& t){
    t.setId(index);     //the new trapezoid will now have the id of the old trapezoid
    t_map[index] = t;   //the old trapezoid is replaced with the new in the vector
}

/**
 * @brief TrapezoidalMap::getTrapezoid
 * This method returns a reference of the trapezoid in the position passed as parameter
 * @param index the position in which the trapezoid to return is stored in the vector
 * @return the trapezoid in the position index
 */
Trapezoid& TrapezoidalMap::getTrapezoid(size_t index){
    return t_map[index];
}

size_t TrapezoidalMap::getTsize() const{
    return t_map.size();
}

/**
 * @brief TrapezoidalMap::clearTmap
 * This method clears the trapezoidal map. It is called when the "clear" button is pressed in the interface.
 * Firstly, all elements are removed from the vector and then the Trapezoid of the Bounding Box is reinserted
 * into the trapezoidal map
 */
void TrapezoidalMap::clearTmap(){
    t_map.clear(); //remove all elements from the vector of the trapezoidal map
    insertBoundingBoxT(); //insert the trapezoid of the bounding box in the trapezoidal map
}

/**
 * @brief TrapezoidalMap::getNeighbor
 * This method returns for the trapezoid trap the id of the neighbor in the position indicated by the parameter index.
 * 0 = TOP_LEFT, 1 = TOP_RIGHT, 2 = BOTTOM_LEFT, 3 = BOTTOM_RIGHT
 * @param trap the id of the trapezoid of which return the neighbor
 * @param index the position of the neighbor id to return
 * @return the id of the trapezoid that is the neighbor in that position
 */
size_t TrapezoidalMap::getNeighbor(size_t trap, size_t index){
    return t_map[trap].getNeighbor(index);
}


/**
 * @brief TrapezoidalMap::setNeighbor
 * This method replaces the value for the trapezoid of id trap of the neighbors array
 * in the position index with the value rep passed as parameter
 * @param index the position of the neighbor array in which replace the value
 * @param rep the new value for that position
 */
void TrapezoidalMap::setNeighbor(size_t trap, size_t index, size_t rep){
    t_map[trap].setNeighbor(index,rep);
}

/**
 * @brief TrapezoidalMap::getAllTasNeighbor
 * For all trapezoids in t_map, if the neighbor in the index position, is old_trap, then new_trap is replaced as neighbor for that position
 * @param position the position to check if the trapezoid is neighbor
 * @param old_trap the id of the trapezoid to check if it is neighbor of all trapezoids
 * @param new_trap the id to replace when old_trap is found
 */
void TrapezoidalMap::replaceAllPositionNeighbor(size_t position, size_t old_trap, size_t new_trap){
    for(size_t i = 0; i < t_map.size(); i++){
        if (old_trap == t_map[i].getNeighbor(position)){
            t_map[i].setNeighbor(position,new_trap);
        }
    }
}

void TrapezoidalMap::setDagId(size_t trap_id, size_t dag_id){
    t_map[trap_id].setDagId(dag_id);
}
