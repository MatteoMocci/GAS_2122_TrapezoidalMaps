#include "trapezoid.h"
/**
 * @brief Trapezoid::Trapezoid
 * This constructor initializes a trapezoid by initializing each of the four values with the values in input
 * @param leftp the point to the left of the trapezoid
 * @param rightp the point to the right of the trapezoid
 * @param top the segment in the top 
 * @param bottom
 */
Trapezoid::Trapezoid(cg3::Point2d leftp, cg3::Point2d rightp, cg3::Segment2d top, cg3::Segment2d bottom):
    leftp(leftp), rightp(rightp), bottom(bottom), top(top){

}


cg3::Point2d Trapezoid::getLeftp(){
    return this->leftp;
}
cg3::Point2d Trapezoid::getRightp(){
    return this->rightp;
}
cg3::Segment2d Trapezoid::getBottom(){
    return this->bottom;
}
cg3::Segment2d Trapezoid::getTop(){
    return this->top;
}
void Trapezoid::setLeftp(cg3::Point2d leftp){
    this->leftp = leftp;
}
void Trapezoid::setRightp(cg3::Point2d rightp){
    this->rightp = rightp;
}
void Trapezoid::setBottom(cg3::Segment2d bottom){
    this->bottom = bottom;
}
void Trapezoid::setTop(cg3::Segment2d top){
    this->top = top;
}

