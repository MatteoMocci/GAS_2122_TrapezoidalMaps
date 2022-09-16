#ifndef TRAPEZOIDALMAP_H
#define TRAPEZOIDALMAP_H

#include "trapezoid.h"

class TrapezoidalMap
{
    public:
        TrapezoidalMap();
        const std::vector<Trapezoid> getMap() const;
        size_t insertTrapezoid(Trapezoid& t);
        void replaceTrapezoid(size_t index, Trapezoid& t);
        Trapezoid& getTrapezoid(size_t index);


    private:
        std::vector<Trapezoid> t_map;

};

#endif // TRAPEZOIDALMAP_H
