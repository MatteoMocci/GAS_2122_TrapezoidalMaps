#ifndef TRAPEZOIDALMAP_H
#define TRAPEZOIDALMAP_H

#include "trapezoid.h"

class TrapezoidalMap
{
    public:
        TrapezoidalMap();
        void splitin4(cg3::Segment2d s, Trapezoid t_split);
        const std::vector<Trapezoid>& getMap() const;

    private:
        std::vector<Trapezoid> t_map;
};

#endif // TRAPEZOIDALMAP_H
