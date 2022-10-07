#ifndef TRAPEZOIDALMAP_H
#define TRAPEZOIDALMAP_H

#include "trapezoid.h"
#include "algorithms/utility.h"

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
        void setDagId(size_t trap_id, size_t dag_id);

        //methods to access to the neighbors of a trapezoid
        size_t getNeighbor(size_t trap, size_t index);
        void setNeighbor(size_t trap, size_t index, size_t rep);
        void setNeighbors(size_t trap_id, size_t * neighbors);
        void updateOldNeighbors(bool left, size_t curr_trap, size_t old_trap, size_t new_trap);

    private:
        std::vector<Trapezoid> t_map; //the vector containing the trapezoids

};

#endif // TRAPEZOIDALMAP_H
