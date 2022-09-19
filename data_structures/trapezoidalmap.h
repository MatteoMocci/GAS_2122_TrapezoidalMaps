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
        size_t getTsize() const ;

        //methods for managing the vector of trapezoids
        size_t insertTrapezoid(Trapezoid& t);
        void replaceTrapezoid(size_t index, Trapezoid& t);
        Trapezoid& getTrapezoid(size_t index);
        void clearTmap();
        void insertBoundingBoxT();

        //methods to access to the neighbors of a trapezoid
        size_t getNeighbor(size_t trap, size_t index);
        void setNeighbor(size_t trap, size_t index, size_t rep);
        std::vector<size_t> getAllTasNeighbor(size_t position, size_t trap);
        void replaceAllPositionNeighbor(size_t position, size_t old_trap, size_t new_trap);


    private:
        std::vector<Trapezoid> t_map; //the vector containing the trapezoids

};

#endif // TRAPEZOIDALMAP_H
