#ifndef THE_NEAREST_RESTAURANT_PROBLEM_H
#define THE_NEAREST_RESTAURANT_PROBLEM_H
/*
Elements of programming interview
Consider the problem of developing a web-service that takes a geographical location, and returns the nearest restaurant.
The service starts with a set S of n restaurant locations--each location is a pair of x, y-coordinates.
A query consists of a location, and should return the nearest restaurant (ties may be broken arbitrarily).

Approach1:
Build 2 BSTs on the restaurant locations: Tx sorted on the x coordinates, and Ty sorted on the y coordinates.
A query on location (p,q) can be performed by finding all the points Pdelta whose x coordinate is in the range [p-delta, p+delta]
, and all the points Qdelta whose y coordinate is in the range [q-delta,q+delta]
, computing Rdelta = Pdelta SET Qdelta and finding the point in Rdelta closest to (p,q).
(Union = U, Set = n)
Heuristically, if delta is chosen correctly, Rdelta is a small subset of S, and a brute-force search for the closest point in Rdelta is fast.
Of course, delta has to be chosen correctly--one approach is to start with a small value and keep doubling it until Rdelta is nonempty.
This approach performs poorly on pathological data, but works well in practice.

Approach2:
Quadtrees, which decompose the plane into regions which are balanced with respect to the number of points they contain.

Approach3:
Kdtrees, which organize points in a k-dimensional space and provide range searches and nearest neighbor searches efficiently.

*/
class TheNearestRestaurantProblem
{
public:
	TheNearestRestaurantProblem(){}
	~TheNearestRestaurantProblem(){}
};
#endif