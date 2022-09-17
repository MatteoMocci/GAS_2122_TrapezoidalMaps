#include "trapezoid.h"
int Trapezoid::lastQueried = -1;
cg3::Color Trapezoid::lastColor = cg3::Color(0,0,0);
/**
 * @brief Trapezoid::Trapezoid
 * This constructor initializes a trapezoid by initializing each of the four values with the values in input
 * @param leftp the point to the left of the trapezoid
 * @param rightp the point to the right of the trapezoid
 * @param top the segment in the top 
 * @param bottom
 */
Trapezoid::Trapezoid(cg3::Point2d leftp, cg3::Point2d rightp, cg3::Segment2d top, cg3::Segment2d bottom):
    leftp(leftp), rightp(rightp), bottom(bottom), top(top), color(cg3::Color(rand()%256, rand()%256, rand()%256)),
    borderColor(cg3::Color(0,0,0)), borderWidth(2)
{

}

bool operator==(const Trapezoid& t1, const Trapezoid& t2){
    return t1.trapIndex == t2.trapIndex;
}

const cg3::Point2d Trapezoid::getLeftp() const{
    return this->leftp;
}
const cg3::Point2d Trapezoid::getRightp() const{
    return this->rightp;
}
const cg3::Segment2d Trapezoid::getBottom() const{
    return this->bottom;
}
const cg3::Segment2d Trapezoid::getTop() const{
    return this->top;
}

const cg3::Color Trapezoid::getColor() const{
    return this->color;
}

const cg3::Color Trapezoid::getBorderColor() const{
    return this->borderColor;
}

size_t Trapezoid::getBorderWidth() const{
    return this->borderWidth;
}

size_t Trapezoid::getId() const{
    return this->trapIndex;
}

void Trapezoid::setLeftp(cg3::Point2d leftp){
    this->leftp = leftp;
}
void Trapezoid::setRightp(cg3::Point2d rightp) {
    this->rightp = rightp;
}
void Trapezoid::setBottom(cg3::Segment2d bottom){
    this->bottom = bottom;
}
void Trapezoid::setTop(cg3::Segment2d top){
    this->top = top;
}

void Trapezoid::setId(size_t index){
    trapIndex = index;
}

void Trapezoid::setColor(cg3::Color color){
    this->color = color;
}

void Trapezoid::setBorderColor(cg3::Color color){
    this->borderColor = color;
}

void Trapezoid::setBorderWidth(size_t width){
    this->borderWidth = width;
}
