#include "trapezoidalmap.h"


TrapezoidalMap::TrapezoidalMap()
{
    Trapezoid t = Trapezoid(cg3::Point2d(-BOUNDINGBOX,-BOUNDINGBOX),
                  cg3::Point2d(BOUNDINGBOX,-BOUNDINGBOX),
                  cg3::Segment2d(cg3::Point2d(-BOUNDINGBOX,BOUNDINGBOX),cg3::Point2d(BOUNDINGBOX,BOUNDINGBOX)),
                  cg3::Segment2d(cg3::Point2d(-BOUNDINGBOX,-BOUNDINGBOX),cg3::Point2d(BOUNDINGBOX,-BOUNDINGBOX))
                  );
    t.setId(0);
    t_map.push_back(t);

}

const std::vector<Trapezoid> TrapezoidalMap::getMap() const{
    return t_map;
}

size_t TrapezoidalMap::insertTrapezoid(Trapezoid& t){
    t.setId(t_map.size());
    t_map.push_back(t);
    return t_map.size();
}

void TrapezoidalMap::replaceTrapezoid(size_t index, Trapezoid& t){
    t.setId(index);
    t_map[index] = t;
}

Trapezoid& TrapezoidalMap::getTrapezoid(size_t index){
    return t_map[index];
}

