#ifndef MAX_POINTS_ON_A_LINE_H
#define MAX_POINTS_ON_A_LINE_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
#include <algorithm>
#include "Debug.h"
/*
Leetcode: Max Points on a Line
http://blog.csdn.net/lilong_dream/article/details/20283023
// Given n points on a 2D plane, find the maximum number of points that lie
// on the same straight line.
//
//
// Complexity:
// HashTable: O(n^2) time, O(n) space

We have to check all the lines through any 2 arbitrary points.
This results in a nested for loops of O(n^2) time.
*/
class MaxPointsOnALine
{
public:
	MaxPointsOnALine(){}
	~MaxPointsOnALine(){}
	struct Point
	{
		int x;
		int y;
		Point() :x(0), y(0){}
		Point(int x, int y) : x(x), y(y){}
		bool operator==(const Point & rhs) const
		{
			return x == rhs.x && y == rhs.y;
		}
	};

	int Count_HashMap(const std::vector<Point> & points)
	{
		int N = points.size();
		int maxPtCount = 0;
		
		for (int i = 0; i < N; ++i)//when N == 1, it should return 1
		{
			int curMaxPtCount = 1;
			int samePtCount = 0;
			std::unordered_map<double, int> slopeMap;//first: slope, second: count

			for (int j = i + 1; j < N; ++j)
			{
				if (points[j].x == points[i].x && points[j].y == points[i].y)
					++samePtCount;
				else
				{
					double slope = 0;
					if (points[j].x != points[i].x)
						slope = 1.0 * (points[j].y - points[i].y) / (points[j].x - points[i].x);
					else
						slope = std::numeric_limits<double>::infinity();

					if (slopeMap.count(slope) == 0)
						slopeMap[slope] = 2;
					else
						slopeMap[slope] += 1;

					if (slopeMap[slope] > curMaxPtCount)
						curMaxPtCount = slopeMap[slope];
				}
			}
			curMaxPtCount += samePtCount;

			if (curMaxPtCount > maxPtCount)
				maxPtCount = curMaxPtCount;
		}
		std::cout << "MaxPointsOnALine HashMap for \"" << this->PointVecToStr(points) << "\" is: " << maxPtCount << std::endl;
		return maxPtCount;
	}
private:
	std::string PointVecToStr(const std::vector<Point> & points)
	{
		std::ostringstream oss;
		for (int i = 0; i < (int)points.size(); ++i)
		{
			oss << "[" << points[i].x << "," << points[i].y << "]";
			if (i != (int)points.size() - 1)
				oss << ",";
		}
		return oss.str();
	}

	/*
	Elements of programming interview, HashTable: Find the line through the most points
	The combination of pairs of points from n points:
		 n!             n!
	------------ = ------------- = n*(n-1)/2
	k! * (n-k)!     2! * (n-2)!
	The equation of line through (x1, y1) and (x2, y2):
	     y2 - y1         x2*y1 - x1*y2
	y = --------- * x + --------------- = Slope * x + Y-Intercept
	     x2 - x1            x2 - x1
	The problem is to design a hash function for a line.
	The idea is to compute a hash code from the slope and the y-intercept of the line as an ordered pair of doubles.
	Because of finite precision arithmetic, we may have three points that are collinear map to distinct buckets.
	If the generated uniform [0,1] random number lies into [0.3, 0.6) we return the number 6.
	A more robust hash function treats the slope and the y-intercept as rationals.
	A rational is an ordered pair of integers: the numerator and the denominator.
	We need to bring the rational into a canonical form before applying the hash function.
	One canonical form is to make the denominator always nonnegative, and relatively prime to the numerator.
	Lines parallel to the y-axis are a special case.
	For such lines, we use the x-intercept in place of the y-intercept, and use 1/0 as the slope.
	*/
public:
	struct HashPoint
	{
		unsigned operator()(const Point& rhs) const
		{
			return std::hash<int>()(rhs.x) ^ std::hash<int>()(rhs.y);
		}
	};
	struct Line
	{
		std::pair<int, int> slope;
		std::pair<int, int> intercept;
		Line(){}
		Line(const Point & a, const Point & b) : slope(a.x != b.x ? this->GetCanonicalFraction(b.y - a.y, b.x - a.x) : std::make_pair(1, 0))
			, intercept(a.x != b.x ? this->GetCanonicalFraction(b.x * a.y - a.x * b.y, b.x - a.x) : std::make_pair(a.x, 1))
		{}
		bool operator==(const Line & rhs) const
		{
			return slope == rhs.slope && intercept == rhs.intercept;
		}
	private:
		int GCD(int a, int b)
		{
			while (a)
			{
				int tmp = a;
				a = b % a;
				b = tmp;
			}
			return b;
		}
		std::pair<int, int> GetCanonicalFraction(int a, int b)//¬ù¤À
		{
			//1. remove GCD for both
			int gcd = this->GCD(std::abs(a), std::abs(b));
			a /= gcd;
			b /= gcd;
			//2. make sure b (denominator) is non-negative
			return b < 0 ? std::make_pair(-a, -b) : std::make_pair(a, b);
		}
	};
	struct HashLine
	{
		unsigned operator()(const Line & rhs) const
		{
			return std::hash<int>()(rhs.slope.first) ^ std::hash<int>()(rhs.slope.second) ^ std::hash<int>()(rhs.intercept.first) ^ std::hash<int>()(rhs.intercept.second);
		}
	};
	Line FindLine_HashMap(const std::vector<Point> & points)
	{
		int N = points.size();
		std::unordered_map<Line, std::unordered_set<Point, HashPoint>, HashLine> hashMap;
		for (int i = 0; i < N; ++i)
		{
			for (int j = i + 1; j < N; ++j)
			{
				Line curLine(points[i], points[j]);
				hashMap[curLine].emplace(points[i]);
				hashMap[curLine].emplace(points[j]);
			}
		}

		Line maxPtLine;
		int maxPtCount = 0;
		std::unordered_set<Point, HashPoint> maxPtSet;
		for (const auto & p : hashMap)
		{
			if ((int)p.second.size() > maxPtCount)
			{
				maxPtCount = p.second.size();
				maxPtLine = p.first;
				maxPtSet = p.second;
			}
		}

		this->PrintHashMap(hashMap);
		std::cout << "MaxPointsOnALine FindLine_HashMap for " << this->PointVecToStr(points) << "\" is: " << maxPtCount << std::endl;
		return maxPtLine;
	}
private:
	void PrintHashMap(const std::unordered_map<Line, std::unordered_set<Point, HashPoint>, HashLine> & m)
	{
		std::ostringstream oss;
		int N = m.size();
		int count = 0;
		for (const auto & p : m)
		{
			oss << "Slope=[" << p.first.slope.first << "," << p.first.slope.second << "], Intercept=[" << p.first.intercept.first << "," << p.first.intercept.second << "]:	";
			int M = p.second.size();
			int count2 = 0;
			for (const auto & pt : p.second)
			{
				oss << "[" << pt.x << "," << pt.y << "]";
				if (count2++ != M - 1)
					oss << ", ";
			}
			if (count++ != N - 1)
				oss << std::endl;
		}
		std::cout << oss.str() << std::endl;
	}

};
/*
MaxPointsOnALine HashMap for "[0,1],[0,4],[0,7],[1,5],[2,3],[2,9],[3,7],[4,2],[4,5],[4,9],[5,3],[5,4],[6,1],[6,7],[7,6],[7,7]" is: 5
Slope=[1,1], Intercept=[1,1]:	[6,7], [4,5], [2,3], [0,1]
Slope=[1,0], Intercept=[0,1]:	[0,1], [0,4], [0,7]
Slope=[1,4], Intercept=[4,1]:	[0,4], [4,5]
Slope=[2,7], Intercept=[4,1]:	[0,4], [7,6]
Slope=[1,0], Intercept=[5,1]:	[5,3], [5,4]
Slope=[1,4], Intercept=[1,1]:	[0,1], [4,2]
Slope=[4,1], Intercept=[1,1]:	[0,1], [1,5], [2,9]
Slope=[1,1], Intercept=[4,1]:	[3,7], [1,5], [0,4]
Slope=[1,2], Intercept=[7,1]:	[0,7], [4,9]
Slope=[0,1], Intercept=[5,1]:	[1,5], [4,5]
Slope=[2,3], Intercept=[7,3]:	[4,5], [7,7]
Slope=[2,1], Intercept=[1,1]:	[0,1], [3,7], [4,9]
Slope=[0,1], Intercept=[3,1]:	[2,3], [5,3]
Slope=[4,5], Intercept=[7,5]:	[2,3], [7,7]
Slope=[1,0], Intercept=[7,1]:	[7,6], [7,7]
Slope=[2,5], Intercept=[1,1]:	[0,1], [5,3]
Slope=[0,1], Intercept=[7,1]:	[0,7], [3,7], [6,7], [7,7]
Slope=[1,0], Intercept=[6,1]:	[6,1], [6,7]
Slope=[3,5], Intercept=[1,1]:	[5,4], [0,1]
Slope=[1,2], Intercept=[4,1]:	[0,4], [6,7]
Slope=[1,1], Intercept=[7,1]:	[0,7], [2,9]
Slope=[1,3], Intercept=[7,3]:	[5,4], [2,3]
Slope=[0,1], Intercept=[1,1]:	[0,1], [6,1]
Slope=[6,7], Intercept=[1,1]:	[0,1], [7,7]
Slope=[3,7], Intercept=[4,1]:	[0,4], [7,7]
Slope=[5,7], Intercept=[1,1]:	[7,6], [0,1]
Slope=[5,2], Intercept=[4,1]:	[0,4], [2,9]
Slope=[1,0], Intercept=[2,1]:	[2,3], [2,9]
Slope=[-1,2], Intercept=[4,1]:	[0,4], [2,3], [4,2], [6,1]
Slope=[-1,1], Intercept=[7,1]:	[6,1], [0,7]
Slope=[5,4], Intercept=[4,1]:	[0,4], [4,9]
Slope=[0,1], Intercept=[4,1]:	[0,4], [5,4]
Slope=[1,0], Intercept=[4,1]:	[4,2], [4,5], [4,9]
Slope=[5,3], Intercept=[-14,3]:	[4,2], [7,7]
Slope=[-1,5], Intercept=[4,1]:	[0,4], [5,3]
Slope=[1,1], Intercept=[-2,1]:	[5,3], [4,2]
Slope=[-4,5], Intercept=[7,1]:	[0,7], [5,3]
Slope=[-2,1], Intercept=[7,1]:	[0,7], [1,5], [2,3]
Slope=[-1,1], Intercept=[6,1]:	[1,5], [4,2]
Slope=[-4,5], Intercept=[29,5]:	[1,5], [6,1]
Slope=[-5,4], Intercept=[7,1]:	[0,7], [4,2]
Slope=[-1,2], Intercept=[7,1]:	[0,7], [4,5]
Slope=[-3,5], Intercept=[7,1]:	[0,7], [5,4]
Slope=[3,1], Intercept=[-3,1]:	[2,3], [4,9]
Slope=[1,1], Intercept=[-1,1]:	[7,6], [5,4]
Slope=[-1,7], Intercept=[7,1]:	[0,7], [7,6]
Slope=[1,3], Intercept=[14,3]:	[1,5], [7,7]
Slope=[4,3], Intercept=[11,3]:	[1,5], [4,9]
Slope=[-1,2], Intercept=[11,2]:	[1,5], [5,3]
Slope=[-3,2], Intercept=[23,2]:	[3,7], [5,4]
Slope=[-1,4], Intercept=[21,4]:	[1,5], [5,4]
Slope=[-3,5], Intercept=[51,5]:	[2,9], [7,6]
Slope=[2,5], Intercept=[23,5]:	[1,5], [6,7]
Slope=[1,6], Intercept=[29,6]:	[1,5], [7,6]
Slope=[4,1], Intercept=[-5,1]:	[2,3], [3,7]
Slope=[3,5], Intercept=[9,5]:	[7,6], [2,3]
Slope=[1,3], Intercept=[11,3]:	[7,6], [4,5]
Slope=[-2,1], Intercept=[13,1]:	[2,9], [3,7], [4,5], [5,3], [6,1]
Slope=[0,1], Intercept=[9,1]:	[2,9], [4,9]
Slope=[-7,2], Intercept=[16,1]:	[2,9], [4,2]
Slope=[-5,3], Intercept=[37,3]:	[2,9], [5,4]
Slope=[5,2], Intercept=[-8,1]:	[4,2], [6,7]
Slope=[-1,2], Intercept=[10,1]:	[2,9], [6,7]
Slope=[-1,1], Intercept=[9,1]:	[5,4], [4,5]
Slope=[-2,5], Intercept=[49,5]:	[2,9], [7,7]
Slope=[-5,1], Intercept=[22,1]:	[3,7], [4,2]
Slope=[-1,4], Intercept=[31,4]:	[3,7], [7,6]
Slope=[2,1], Intercept=[-6,1]:	[4,2], [5,4]
Slope=[-1,1], Intercept=[13,1]:	[4,9], [7,6], [6,7]
Slope=[4,3], Intercept=[-10,3]:	[4,2], [7,6]
Slope=[-6,1], Intercept=[33,1]:	[4,9], [5,3]
Slope=[-5,1], Intercept=[29,1]:	[4,9], [5,4]
Slope=[-4,1], Intercept=[25,1]:	[4,9], [6,1]
Slope=[-2,3], Intercept=[35,3]:	[4,9], [7,7]
Slope=[4,1], Intercept=[-17,1]:	[5,3], [6,7]
Slope=[3,2], Intercept=[-9,2]:	[5,3], [7,6]
Slope=[2,1], Intercept=[-7,1]:	[5,3], [7,7]
Slope=[-3,1], Intercept=[19,1]:	[5,4], [6,1]
Slope=[3,1], Intercept=[-11,1]:	[6,7], [5,4]
Slope=[3,2], Intercept=[-7,2]:	[5,4], [7,7]
Slope=[5,1], Intercept=[-29,1]:	[6,1], [7,6]
Slope=[6,1], Intercept=[-35,1]:	[6,1], [7,7]
MaxPointsOnALine FindLine_HashMap for [0,1],[0,4],[0,7],[1,5],[2,3],[2,9],[3,7],[4,2],[4,5],[4,9],[5,3],[5,4],[6,1],[6,7],[7,6],[7,7]" is: 5
*/
#endif