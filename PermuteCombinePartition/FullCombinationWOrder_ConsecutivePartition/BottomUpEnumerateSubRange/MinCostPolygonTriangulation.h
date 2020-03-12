#ifndef MIN_COST_POLYGON_TRIANGULATION_H
#define MIN_COST_POLYGON_TRIANGULATION_H
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include "Debug.h"
/*
http://www.geeksforgeeks.org/minimum-cost-polynomial-triangulation/
A triangulation of a convex polygon is formed by drawing diagonals between non-adjacent vertices (corners) such that the diagonals never intersect.
The problem is to find the cost of triangulation with the minimum cost.
The cost of a triangulation is sum of the weight of its component triangles.
Weight of each triangle is its perimeter (sum of lengths of all sides).

This problem has recursive substructure.
The idea is to divide the polygon into three parts: a single triangle, the sub-polygon to the left, and the sub-polygon to the right.
We try all possible divisions like this and find the one that minimizes the cost of the triangle plus the cost of the triangulation of the two sub-polygons.

Recur: exponential time
DP2D: O(n^3) time, O(n^2) space

See also MatrixChainMultiplication.h, MaxSumParenthesizeArithmeticExpr.h, MaxVerticesSumOfPolygon.h, OptimalBinarySearchTree.h
*/
class MinCostPolygonTriangulation
{
public:
	MinCostPolygonTriangulation(){}
	~MinCostPolygonTriangulation(){}

	double Recur(const std::vector<std::pair<int, int> > & v)//first: x-coordinate, second: y-coordinate
	{
		int N = v.size();
		if (N < 3)
			return 0;
		double res = this->recur(v, 0, N - 1);
		std::cout << "MinCostPolygonTriangulation Recur for \"" << Debug::ToStr1D<int>()(v) << "\": " << res << std::endl;
		return res;
	}
private:
	double recur(const std::vector<std::pair<int, int> > & v, int left, int right)
	{
		if (left + 2 > right)//left and right are adjacent vertices
			return 0;
		double res = 1000000.0;//infinity
		for (int mid = left + 1; mid < right; ++mid)
		{
			double minCostLeftPolygon = this->recur(v, left, mid);
			double minCostRightPolygon = this->recur(v, mid, right);
			double costCurTriangle = this->Cost(v, left, mid, right);
			double totalCost = minCostLeftPolygon + minCostRightPolygon + costCurTriangle;
			if (totalCost < res)
				res = totalCost;
		}
		return res;
	}
	double Dist(const std::pair<int, int> & p1, const std::pair<int, int> & p2)
	{
		int deltaX = p1.first - p2.first;
		int deltaY = p1.second - p2.second;
		return std::sqrt(deltaX*deltaX + deltaY*deltaY);
	}
	double Cost(const std::vector<std::pair<int, int> > & v, int i, int j, int k)
	{
		std::pair<int, int> p1 = v[i];
		std::pair<int, int> p2 = v[j];
		std::pair<int, int> p3 = v[k];
		return this->Dist(p1, p2) + this->Dist(p2, p3) + this->Dist(p3, p1);
	}

public:
	double DP2D(const std::vector<std::pair<int, int> > & v)
	{
		int N = v.size();
		if (N < 3)
			return 0;

		std::vector<std::vector<double> > dp(N, std::vector<double>(N, 0));

		for (int i = 0; i < N; ++i)
			dp[i][i] = 0;

		for (int len = 3; len <= N; ++len)
		{
			for (int left = 0; left < N - len + 1; ++left)
			{
				int right = left + len - 1;
				dp[left][right] = 1000000.0;//infinity
				for (int mid = left + 1; mid < right; ++mid)
				{
					double cost = dp[left][mid] + dp[mid][right] + this->Cost(v, left, mid, right);
					if (cost < dp[left][right])
						dp[left][right] = cost;
				}
			}
		}
		Debug::Print2D<double>()(dp, false);
		std::cout << "MinCostPolygonTriangulation DP2D for \"" << Debug::ToStr1D<int>()(v) << "\": " << dp[0][N - 1] << std::endl;
		return dp[0][N - 1];
	}
};
/*
MinCostPolygonTriangulation Recur for "[0,0], [1,0], [2,1], [1,2], [0,2]": 15.3006
[rY][cX]
Row#0	= 0, 0, 4.65028, 10.0645, 15.3006
Row#1	= 0, 0, 0, 4.82843, 10.0645
Row#2	= 0, 0, 0, 0, 4.65028
Row#3	= 0, 0, 0, 0, 0
Row#4	= 0, 0, 0, 0, 0

MinCostPolygonTriangulation DP2D for "[0,0], [1,0], [2,1], [1,2], [0,2]": 15.3006
*/
#endif