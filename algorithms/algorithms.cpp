#include "algorithms.h"
/*
 * Input. 	A trapezoidal map T, a search structure D for T, and a new segment si
 * Output. 	The sequence Δ0, Δ1, …, Δk of trapezoids intersected by si
 * 1. Let p and q be the left and right endpoint of si
 * 2. Search with p in the search structure D to find Δ0
 * 3.	j ← 0
 * 4.	while q lies to the right of rightp(Δj)
 * 5.		do if rightp(Δj) lies above si
 * 6.				then Δj+1 be the lower right neighbor of Δj
 * 7.				else Δj+1 be the upper right neighbor of Δj
 * 8.			j ← j+1
 * 9.	return Δ0, Δ1, …, Δk
*/
inline Trapezoid* algorithms::followSegment(TrapezoidalMap T, Dag D, cg3::Segment2d s){
    // Punto 1
    cg3::Point2d p = s.p1();
    cg3::Point2d q = s.p2();
    std::cout << p << std::endl;
    std::cout << q << std::endl;

    //Punto 2
    //implementare la ricerca nel Dag passando come parametro il punto p
}
