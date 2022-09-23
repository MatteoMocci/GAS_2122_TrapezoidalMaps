#ifndef TRAPEZOID_H
#define TRAPEZOID_H

#include <cg3/geometry/point2.h>
#include <cg3/geometry/segment2.h>
#include <cg3/utilities/color.h>
#define BOUNDINGBOX 1e+6 // the length of a side of the bounding box

class Trapezoid
{

public:

    //constructors
    Trapezoid() = default;
    Trapezoid(cg3::Point2d leftp, cg3::Point2d rightp, cg3::Segment2d top, cg3::Segment2d bottom);

    //getters
    const cg3::Point2d getLeftp() const;
    const cg3::Point2d getRightp() const;
    const cg3::Segment2d getBottom() const;
    const cg3::Segment2d getTop() const;
    const cg3::Color getColor() const;
    const cg3::Color getBorderColor() const;
    size_t getBorderWidth() const;
    size_t getId() const;
    size_t getNeighbor(size_t index);
    size_t* getNeighbors();
    size_t getDagId() const;

    //setters
    void setLeftp(cg3::Point2d leftp);
    void setRightp(cg3::Point2d rightp);
    void setBottom(cg3::Segment2d bottom);
    void setTop(cg3::Segment2d top);
    void setColor(cg3::Color color);
    void setId(size_t index);
    void setBorderColor(cg3::Color color);
    void setBorderWidth(size_t width);
    void setEmptyNeighbors();
    void setNeighbor(size_t index, size_t rep);
    void setNeighbors(size_t neighbors[]);
    void setDagId(size_t index);


    //override of the == operator for trapezoids
    friend bool operator==(const Trapezoid&, const Trapezoid&);

    //static members
    static int lastQueried;
    static cg3::Color lastColor;

private:

    //attributes of a Trapezoid
    cg3::Point2d leftp;     //the point to the left of the trapezoid
    cg3::Point2d rightp;    //the point to the right of the trapezoid
    cg3::Segment2d bottom;  //the segment below the trapezoid
    cg3::Segment2d top;     //the segment above the trapezoid
    cg3::Color color;       //the color for filling the trapezoid
    cg3::Color borderColor; //the color of the border of the trapezoid
    size_t borderWidth;     //the width of the border of the trapezoid
    size_t trapIndex;       //the id of the trapezoid, the position in the trapezoidalmap
    size_t neighbors[4];     //the array of the index of neighbors of a trapezoid
    size_t dagIndex;        //the position in which the element is stored in the dag
};

#endif // TRAPEZOID_H
