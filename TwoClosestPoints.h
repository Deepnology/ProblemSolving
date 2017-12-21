#ifndef TWO_CLOSEST_POINTS_H
#define TWO_CLOSEST_POINTS_H
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <limits>
#include "Debug.h"
/*
Elements of programming interview, Recursion: Find the two closest points
http://www.geeksforgeeks.org/closest-pair-of-points/
You are given a list of pairs of points in the 2D Cartesian plane.
Each point has integer x and y coordinates.
How would you find the two closest points?

1D case:
approach1:
brute force 2 for loops
O(n^2) time

approach2:
sort the array,
iterate through the points in the array and compare the distance between successive points with the running minimum
O(nlogn) time
see also MinPairDiff2SortedArrays.h, TwoDifference.h

approach3:
divide and conquer:
partition the set about the median, solve the problem for the left and right partitions, and combine results.
the last step entails finding points closest to the median from the left and right partitions.
O(nlogn) time

2D case:
approach1:
brute force 2 for loops
O(n^2) time

approach2:
divide and conquer:
O(nlogn) time

*/
class TwoClosestPoints
{
public:
	TwoClosestPoints(){}
	~TwoClosestPoints(){}
	typedef std::pair<int, int> Point;//first: x, second: y

	std::tuple<Point, Point, double> DivideConquerRecur(std::vector<Point> & v)
	{
		std::sort(v.begin(), v.end(), [](const Point & a, const Point & b)->bool
		{
			return a.first < b.first;
		});

		std::tuple<Point, Point, double> res = this->recur(v, 0, v.size() - 1);
		std::cout << "TwoClosestPoints DivideConquerRecur for \"" << Debug::ToStr1D<int>()(v) << "\": " << "[(" << std::get<0>(res).first << "," << std::get<0>(res).second << "), (" << std::get<1>(res).first << "," << std::get<1>(res).second << "), " << std::get<2>(res) << "]" << std::endl;
		return res;
	}

private:
	std::tuple<Point, Point, double> recur(const std::vector<Point> & v, int start, int end)
	{
		if (end - start + 1 <= 3)//less equal than 3 points
			return this->BruteForce(v, start, end);

		int mid = (start + end) / 2;
		std::tuple<Point, Point, double> left = this->recur(v, start, mid);
		std::tuple<Point, Point, double> right = this->recur(v, mid + 1, end);
		std::tuple<Point, Point, double> minLR = std::get<2>(left) < std::get<2>(right) ? left : right;

		//1. keep the points whose x-distance-to-v[mid] < minLR (the points on both the right side and left side of the vertical line of v[mid] with a smaller distance than minLR)
		std::vector<Point> remain;
		for (int i = start; i <= end; ++i)
			if (std::abs(v[i].first - v[mid].first) < std::get<2>(minLR))
				remain.push_back(v[i]);

		//2. sort the remain based on y value
		std::sort(remain.begin(), remain.end(), [](const Point & a, const Point & b)->bool
		{
			return a.second < b.second;
		});
		std::tuple<Point, Point, double> res;
		std::get<2>(res) = std::numeric_limits<double>::max();
		//3. enumerate all possible point-pairs in remain and keep track of min distance of a point-pair whose y-distance < minLR
		for (int i = 0; i < (int)remain.size(); ++i)
		{
			//pick the points whose y-distance is smaller than minLR
			//it is proven that the inner loop runs at most 6 times
			//so the 2 for loops run in O(n) time instead of O(n^2) time
			for (int j = i + 1; j < (int)remain.size() && remain[j].second - remain[i].second < std::get<2>(minLR); ++j)
			{
				double dist = this->distance(remain[i], remain[j]);
				if (dist < std::get<2>(res))
					res = std::make_tuple(remain[i], remain[j], dist);
			}
		}

		//4. pick the min from the "min distance point-pair from remain" and minLR
		res = std::get<2>(res) < std::get<2>(minLR) ? res : minLR;
		return res;
	}

	std::tuple<Point, Point, double> BruteForce(const std::vector<Point> & v, int start, int end)
	{
		std::tuple<Point, Point, double> res;
		std::get<2>(res) = std::numeric_limits<double>::max();
		for (int i = start; i < end; ++i)
		{
			for (int j = i + 1; j < end; ++j)
			{
				double dist = this->distance(v[i], v[j]);
				if (dist < std::get<2>(res))
					res = std::make_tuple(v[i], v[j], dist);
			}
		}
		return res;
	}

	double distance(const Point & a, const Point & b)
	{
		int deltaX = a.first - b.first;
		int deltaY = a.second - b.second;
		return std::sqrt(deltaX*deltaX + deltaY*deltaY);
	}
};
/*
TwoClosestPoints DivideConquerRecur for "[2,3], [3,4], [5,1], [12,30], [12,10], [40,50]": [(2,3), (3,4), 1.41421]
*/
#endif