#ifndef TRAPEZOIDALMAP_H
#define TRAPEZOIDALMAP_H

#include "trapezoid.h"
#include <cg3/geometry/point2.h>
#include <cg3/geometry/segment2.h>


class TrapezoidalMap
{
    public:
        TrapezoidalMap();

    private:
        std::vector<Trapezoid> t_map;
};

#endif // TRAPEZOIDALMAP_H
