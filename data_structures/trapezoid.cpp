#include "trapezoid.h"
size_t Trapezoid::last_index = 0;
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
    trapIndex(last_index)
{
    last_index++;
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

void Trapezoid::setColor(cg3::Color color){
    this->color = color;
}
