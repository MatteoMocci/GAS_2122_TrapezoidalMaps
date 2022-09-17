#ifndef TRAPEZOIDALMAP_H
#define TRAPEZOIDALMAP_H

#include "trapezoid.h"

class TrapezoidalMap
{
    public:
        //constructors
        TrapezoidalMap();

        //getter
        const std::vector<Trapezoid> getMap() const;

        //methods for managing the vector of trapezoids
        size_t insertTrapezoid(Trapezoid& t);
        void replaceTrapezoid(size_t index, Trapezoid& t);
        Trapezoid& getTrapezoid(size_t index);
        void clearTmap();
        void insertBoundingBoxT();


    private:
        std::vector<Trapezoid> t_map; //the vector containing the trapezoids

};

#endif // TRAPEZOIDALMAP_H
