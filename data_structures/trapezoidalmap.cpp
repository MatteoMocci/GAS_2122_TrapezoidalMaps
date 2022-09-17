#include "trapezoidalmap.h"

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

