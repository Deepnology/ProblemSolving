#ifndef TRAVELING_SALESMAN_H
#define TRAVELING_SALESMAN_H
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include "Debug.h"
/*
∞ˆæiªP¡Î¡Â
http://www.geeksforgeeks.org/travelling-salesman-problem-set-1/

Traveling salesman problem: 
Given a set of cities and distance between every pair of cities.
Find the shortest possible route that visit every city exactly once and returns to the starting point.
The problem is to find a minimum weight Hamiltonian cycle.

Hamiltonian cycle problem: find a tour that visit every VERTEX exactly once and return to the starting VERTEX.
Hamiltonian path problem: find a tour that visit every VERTEX exactly once but don't need to return the starting VERTEX. see TopologicalSortDAG.h
*/
class TravelingSalesman
{
public:
	TravelingSalesman(){}
	~TravelingSalesman(){}
};
#endif