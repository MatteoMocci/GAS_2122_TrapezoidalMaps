#include "trapezoidalmap.h"


TrapezoidalMap::TrapezoidalMap()
{
    Trapezoid t = Trapezoid(cg3::Point2d(-BOUNDINGBOX,-BOUNDINGBOX),
                  cg3::Point2d(BOUNDINGBOX,-BOUNDINGBOX),
                  cg3::Segment2d(cg3::Point2d(-BOUNDINGBOX,BOUNDINGBOX),cg3::Point2d(BOUNDINGBOX,BOUNDINGBOX)),
                  cg3::Segment2d(cg3::Point2d(-BOUNDINGBOX,-BOUNDINGBOX),cg3::Point2d(BOUNDINGBOX,-BOUNDINGBOX))
                  );
    t_map.push_back(t);

}

const std::vector<Trapezoid>& TrapezoidalMap::getMap() const{
    return t_map;
}

void TrapezoidalMap::splitin4(cg3::Segment2d s){
    Trapezoid t1 = Trapezoid(
                t_map[0].getLeftp(),
                cg3::Point2d(s.p1().x(),t_map[0].getLeftp().y()),
                cg3::Segment2d(t_map[0].getTop().p1(),cg3::Point2d(s.p1().x(), t_map[0].getTop().p1().y())),
                cg3::Segment2d(t_map[0].getBottom().p1(),cg3::Point2d(s.p1().x(), t_map[0].getBottom().p1().y()))
                );
    Trapezoid t2 = Trapezoid(
                s.p1(),
                s.p2(),
                cg3::Segment2d(cg3::Point2d(s.p1().x(),t_map[0].getTop().p1().y()),cg3::Point2d(s.p2().x(),t_map[0].getTop().p2().y())),
                s
                );
    Trapezoid t3 = Trapezoid(
                cg3::Point2d(s.p1().x(),t_map[0].getBottom().p1().y()),
                cg3::Point2d(s.p2().x(),t_map[0].getBottom().p2().y()),
                s,
                cg3::Segment2d(cg3::Point2d(s.p1().x(),t_map[0].getBottom().p1().y()), cg3::Point2d(s.p2().x(),t_map[0].getBottom().p2().y()))
                );
    Trapezoid t4 = Trapezoid(
                cg3::Point2d(s.p2().x(),t_map[0].getLeftp().y()),
                t_map[0].getRightp(),
                cg3::Segment2d(cg3::Point2d(s.p2().x(),t_map[0].getTop().p2().y()),t_map[0].getTop().p2()),
                cg3::Segment2d(cg3::Point2d(s.p2().x(),t_map[0].getBottom().p2().y()),t_map[0].getBottom().p2())
                );
    t_map.pop_back();
    t_map.push_back(t1);
    t_map.push_back(t2);
    t_map.push_back(t3);
    t_map.push_back(t4);
}
