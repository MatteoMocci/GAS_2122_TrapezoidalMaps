#include "trapezoidalmap.h"


TrapezoidalMap::TrapezoidalMap()
{
    Trapezoid t = Trapezoid(cg3::Point2d(-BOUNDINGBOX,BOUNDINGBOX),
                  cg3::Point2d(BOUNDINGBOX,-BOUNDINGBOX),
                  cg3::Segment2d(cg3::Point2d(-BOUNDINGBOX,BOUNDINGBOX),cg3::Point2d(BOUNDINGBOX,BOUNDINGBOX)),
                  cg3::Segment2d(cg3::Point2d(-BOUNDINGBOX,-BOUNDINGBOX),cg3::Point2d(BOUNDINGBOX,-BOUNDINGBOX))
                  );
    t_map.push_back(t);

    //il primo trapezoide è la bounding box
    //leftp = il punto in alto a sinistra
    //rightp = il punto in basso a destra
    //top = il segmento superiore della bounding box
    //bottom = il segmento inferiore della bounding box

    //controllare come è costruita una bounding box

}
