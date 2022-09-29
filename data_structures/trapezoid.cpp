#include "trapezoid.h"
int Trapezoid::lastQueried = -1;
cg3::Color Trapezoid::lastColor = cg3::Color(0,0,0);
/**
 * @brief Trapezoid::Trapezoid
 * This constructor initializes a trapezoid by initializing each of the four attributes with the values in input.
 * The neighbor array is initialized as well.
 * @param leftp the point to the left of the trapezoid
 * @param rightp the point to the right of the trapezoid
 * @param top the segment above the trapezoid
 * @param bottom the segment below the trapezoid
 */
Trapezoid::Trapezoid(cg3::Point2d leftp, cg3::Point2d rightp, cg3::Segment2d top, cg3::Segment2d bottom):
    leftp(leftp), rightp(rightp), bottom(bottom), top(top), color(cg3::Color(rand()%256, rand()%256, rand()%256)),
    borderColor(cg3::Color(0,0,0)), borderWidth(2), dagIndex(SIZE_MAX)
{
    setEmptyNeighbors();
}

/**
 * @brief Trapezoid::getLeftp
 * @return the point to the left of the trapezoid
 */
const cg3::Point2d Trapezoid::getLeftp() const{
    return this->leftp;
}

/**
 * @brief Trapezoid::getRightp
 * @return the point to the right of the trapezoid
 */
const cg3::Point2d Trapezoid::getRightp() const{
    return this->rightp;
}

/**
 * @brief Trapezoid::getBottom
 * @return the segment below the trapezoid
 */
const cg3::Segment2d Trapezoid::getBottom() const{
    return this->bottom;
}

/**
 * @brief Trapezoid::getTop
 * @return the segment above the trapezoid
 */
const cg3::Segment2d Trapezoid::getTop() const{
    return this->top;
}

/**
 * @brief Trapezoid::getColor
 * @return the color to use for drawing the trapezoid
 */
const cg3::Color Trapezoid::getColor() const{
    return this->color;
}

/**
 * @brief Trapezoid::getBorderColor
 * @return the color to use for the border of the trapezoid
 */
const cg3::Color Trapezoid::getBorderColor() const{
    return this->borderColor;
}
/**
 * @brief Trapezoid::getBorderWidth
 * @return the value of the width to use for the border of the trapezoid
 */
size_t Trapezoid::getBorderWidth() const{
    return this->borderWidth;
}

/**
 * @brief Trapezoid::getId
 * @return the numeric id which identifies the trapezoid
 */
size_t Trapezoid::getId() const{
    return this->trapIndex;
}

/**
 * @brief Trapezoid::getDagId
 * @return the position in the dag in which the trapezoid is stored
 */
size_t Trapezoid::getDagId() const{
    return this->dagIndex;
}
/**
 * @brief Trapezoid::setLeftp
 * This method sets the value of the left point member of the trapezoid
 * @param leftp the point to set as left
 */
void Trapezoid::setLeftp(cg3::Point2d leftp){
    this->leftp = leftp;
}

/**
 * @brief Trapezoid::setRightp
 * This method sets the value of the right point member of the trapezoid
 * @param rightp the point to set as right
 */
void Trapezoid::setRightp(cg3::Point2d rightp) {
    this->rightp = rightp;
}

/**
 * @brief Trapezoid::setBottom
 * This method sets the value of the bottom member of the trapezoid
 * @param bottom the segment to set as bottom
 */
void Trapezoid::setBottom(cg3::Segment2d bottom){
    this->bottom = bottom;
}

/**
 * @brief Trapezoid::setTop
 * This method sets the value of the top member of the trapezoid
 * @param top the segment to set as top
 */
void Trapezoid::setTop(cg3::Segment2d top){
    this->top = top;
}

/**
 * @brief Trapezoid::setId
 * This method sets the value of the id of the trapezoid, the position of the trapezoid in the trapezoidalmap
 * @param index the number to set as id
 */
void Trapezoid::setId(size_t index){
    trapIndex = index;
}

/**
 * @brief Trapezoid::setColor
 * This method sets the value of the color to use for filling the trapezoid
 * @param color the color to set
 */
void Trapezoid::setColor(cg3::Color color){
    this->color = color;
}

/**
 * @brief Trapezoid::setBorderColor
 * This method sets the value of the color to use for the border of the trapezoid
 * @param color the color to set
 */
void Trapezoid::setBorderColor(cg3::Color color){
    this->borderColor = color;
}

/**
 * @brief Trapezoid::setBorderWidth
 * This method sets the value of the border width of the trapezoid
 * @param width the value of the width to set
 */
void Trapezoid::setBorderWidth(size_t width){
    this->borderWidth = width;
}

/**
 * @brief Trapezoid::setEmptyNeighbors
 * This method initializes every element of the neighbor array with a placeholder value (SIZE_MAX)
 * that indicates that the trapezoid doesn't have a neighbor for that position
 */
void Trapezoid::setEmptyNeighbors(){
    for(size_t i = 0; i <= 3; i++){
        neighbors[i] = SIZE_MAX;
    }
}

/**
 * @brief Trapezoid::getNeighbor
 * This method returns the id of the neighbor in the position indicated by the parameter index.
 * 0 = TOP_LEFT, 1 = TOP_RIGHT, 2 = BOTTOM_LEFT, 3 = BOTTOM_RIGHT
 * @param index the position of the neighbor id to return
 * @return the id of the trapezoid that is the neighbor in that position
 */
size_t Trapezoid::getNeighbor(size_t index){
    return neighbors[index];
}

/**
 * @brief Trapezoid::getNeighbors
 * @return the vector of neighbors of the current trapezoid
 */
size_t* Trapezoid::getNeighbors(){
    return neighbors;
}



/**
 * @brief Trapezoid::setNeighbor
 * This method replaces the value in the position index with the value rep passed as parameter
 * @param index the position of the neighbor array in which replace the value
 * @param rep the new value for that position
 */
void Trapezoid::setNeighbor(size_t index, size_t rep){
    neighbors[index] = rep;
}


/**
 * @brief Trapezoid::setNeighbor
 * This method replaces the value in the position index with the value rep passed as parameter
 * @param index the position of the neighbor array in which replace the value
 * @param rep the new value for that position
 */
void Trapezoid::setNeighbors(size_t neighbors[]){
    for(size_t i = 0; i < 4; i++){
        this->neighbors[i] = neighbors[i];
    }
}
/**
 * @brief Trapezoid::setDagId
 * This method sets the attribute that represent the position in the dag in which the trapezoid is stored
 * @param index the position in which the trapezoid is stored in the dagNode vector
 */
void Trapezoid::setDagId(size_t index){
    dagIndex = index;
}
