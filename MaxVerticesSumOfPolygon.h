#ifndef MAX_VERTICES_SUM_OF_POLYGON_H
#define MAX_VERTICES_SUM_OF_POLYGON_H
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include "Debug.h"
/*
Google
http://www.careercup.com/question?id=15168662
http://stackoverflow.com/questions/3781962/building-an-expression-with-maximum-value
Given a polygon with N vertices and N edges.
There is an integer number (could be negative) on every vertex and an operation in set (*,+) on every edge.
Every time we remove an edge from the polygon and merge the two vertices linked by the edge to a new vertex with value (v1 op v2).
The last case would be two vertices with two edge, and the result is the bigger one.
Return the max result value that can be gotten from a given polygon.

DP2D: O(n^4) time, O(n^2) space
See also MatrixChainMultiplication.h, MaxSumParenthesizeArithmeticExpr.h
*/
class MaxVerticesSumOfPolygon
{
public:
	MaxVerticesSumOfPolygon(){}
	~MaxVerticesSumOfPolygon(){}

	int DP2D(const std::vector<int> & v, const std::vector<int> & e)
	{
		int N = v.size();
		std::vector<std::vector<std::pair<int, int> > > dp(N, std::vector<std::pair<int, int> >(N));
		int resMax = INT_MIN;
		int resMin = INT_MAX;
		/*
		for each startVertex, we find the max vertices sum of [(startVertex%N)....(startVertex+N-1)%N] among all different combinations of parenthensizations
		, which means the range of [startVertex....startVertex-1]
		, which also means we "ignore the edge in between startVertex to startVertex-1"
		dp[i][j].first: max in the range v[i]~v[j] inclusive
		dp[i][j].second: min in the range v[i]~v[j] inclusive
		*/
		for (int startVertex = 0; startVertex < N; ++startVertex)
		{
			/*
			dp[][] is always 0 based for simplicity
			shift startVertex to 0 based system
			*/
			for (int i = 0; i < N; ++i)
			{
				dp[i][i].first = v[(i + startVertex) % N];//re-init: when start/end is the same, it is the vertex number itself
				dp[i][i].second = v[(i + startVertex) % N];//re-init: when start/end is the same, it is the vertex number itself
			}

			for (int len = 2; len <= N; ++len)
			{
				for (int first = 0; first < N - len + 1; ++first)//last = first + len - 1 < N ===> first < N - len + 1
				{
					int last = first + len - 1;//len = last - first + 1, inclusive
					dp[first][last].first = INT_MIN;
					dp[first][last].second = INT_MAX;
					for (int mid = first; mid < last; ++mid)
					{
						/*T: *, P: +*/
						int maxTmax = dp[first][mid].first * dp[mid + 1][last].first;
						int maxTmin = dp[first][mid].first * dp[mid + 1][last].second;
						int minTmax = dp[first][mid].second * dp[mid + 1][last].first;
						int minTmin = dp[first][mid].second * dp[mid + 1][last].second;

						int maxPmax = dp[first][mid].first + dp[mid + 1][last].first;
						
						int minPmin = dp[first][mid].second + dp[mid + 1][last].second;

						int max = INT_MIN;
						int min = INT_MAX;
						if (e[(mid + startVertex) % N] == 0)//+
						{
							max = maxPmax;
							min = minPmin;
						}
						else if (e[(mid + startVertex) % N] == 1)//*
						{
							max = this->max(maxTmax, maxTmin, minTmax, minTmin);
							min = this->min(maxTmax, maxTmin, minTmax, minTmin);
						}
						
						if (max > dp[first][last].first)
							dp[first][last].first = max;
						if (min < dp[first][last].second)
							dp[first][last].second = min;
					}
				}
			}
			if (dp[0][N - 1].first > resMax)
				resMax = dp[0][N - 1].first;
			if (dp[0][N - 1].second < resMin)
				resMin = dp[0][N - 1].second;
			Debug::Print2D<int>()(dp, false);
		}

		std::cout << "MaxVerticesSumOfPolygon DP2D for \"" << Debug::ToStr1D<int>()(v) << "\", \"" << Debug::ToStr1D<int>()(e) << "\": " << resMax << ", Min: " << resMin << std::endl;
		return resMax;
	}

private:
	int min(int a, int b, int c, int d)
	{
		return std::min(a,
			std::min(b,
			std::min(c, d)));
	}
	int max(int a, int b, int c, int d)
	{
		return std::max(a,
			std::max(b,
			std::max(c, d)));
	}
};
/*
[rY][cX]
Row#0	= [-2,-2], [-6,-6], [-4,-10], [2,-40], [320,-70], [325,-65]
Row#1	= [0,0], [3,3], [5,5], [20,11], [-61,-160], [-21,-155]
Row#2	= [0,0], [0,0], [2,2], [8,8], [-64,-64], [-24,-59]
Row#3	= [0,0], [0,0], [0,0], [4,4], [-32,-32], [-12,-27]
Row#4	= [0,0], [0,0], [0,0], [0,0], [-8,-8], [-3,-3]
Row#5	= [0,0], [0,0], [0,0], [0,0], [0,0], [5,5]

[rY][cX]
Row#0	= [3,3], [5,5], [20,11], [-61,-160], [-21,-155], [310,-360]
Row#1	= [0,0], [2,2], [8,8], [-64,-64], [-24,-59], [118,-144]
Row#2	= [0,0], [0,0], [4,4], [-32,-32], [-12,-27], [54,-72]
Row#3	= [0,0], [0,0], [0,0], [-8,-8], [-3,-3], [6,-18]
Row#4	= [0,0], [0,0], [0,0], [0,0], [5,5], [-10,-10]
Row#5	= [0,0], [0,0], [0,0], [0,0], [0,0], [-2,-2]

[rY][cX]
Row#0	= [2,2], [8,8], [-64,-64], [-24,-59], [118,-144], [354,-432]
Row#1	= [0,0], [4,4], [-32,-32], [-12,-27], [54,-72], [162,-216]
Row#2	= [0,0], [0,0], [-8,-8], [-3,-3], [6,-18], [18,-54]
Row#3	= [0,0], [0,0], [0,0], [5,5], [-10,-10], [-30,-30]
Row#4	= [0,0], [0,0], [0,0], [0,0], [-2,-2], [-6,-6]
Row#5	= [0,0], [0,0], [0,0], [0,0], [0,0], [3,3]

[rY][cX]
Row#0	= [4,4], [-32,-32], [-12,-27], [54,-72], [162,-216], [270,-360]
Row#1	= [0,0], [-8,-8], [-3,-3], [6,-18], [18,-54], [30,-90]
Row#2	= [0,0], [0,0], [5,5], [-10,-10], [-30,-30], [-20,-50]
Row#3	= [0,0], [0,0], [0,0], [-2,-2], [-6,-6], [-4,-10]
Row#4	= [0,0], [0,0], [0,0], [0,0], [3,3], [5,5]
Row#5	= [0,0], [0,0], [0,0], [0,0], [0,0], [2,2]

[rY][cX]
Row#0	= [-8,-8], [-3,-3], [6,-18], [18,-54], [30,-90], [120,-360]
Row#1	= [0,0], [5,5], [-10,-10], [-30,-30], [-20,-50], [10,-200]
Row#2	= [0,0], [0,0], [-2,-2], [-6,-6], [-4,-10], [2,-40]
Row#3	= [0,0], [0,0], [0,0], [3,3], [5,5], [20,11]
Row#4	= [0,0], [0,0], [0,0], [0,0], [2,2], [8,8]
Row#5	= [0,0], [0,0], [0,0], [0,0], [0,0], [4,4]

[rY][cX]
Row#0	= [5,5], [-10,-10], [-30,-30], [-20,-50], [10,-200], [1600,-350]
Row#1	= [0,0], [-2,-2], [-6,-6], [-4,-10], [2,-40], [320,-70]
Row#2	= [0,0], [0,0], [3,3], [5,5], [20,11], [-61,-160]
Row#3	= [0,0], [0,0], [0,0], [2,2], [8,8], [-64,-64]
Row#4	= [0,0], [0,0], [0,0], [0,0], [4,4], [-32,-32]
Row#5	= [0,0], [0,0], [0,0], [0,0], [0,0], [-8,-8]

MaxVerticesSumOfPolygon DP2D for "-2, 3, 2, 4, -8, 5", "1, 0, 1, 1, 0, 1": 1600, Min: -432
[rY][cX]
Row#0	= [-8,-8], [-16,-16], [8,-19], [104,-95]
Row#1	= [0,0], [2,2], [-1,-1], [-5,-13]
Row#2	= [0,0], [0,0], [-3,-3], [-15,-15]
Row#3	= [0,0], [0,0], [0,0], [5,5]

[rY][cX]
Row#0	= [2,2], [-1,-1], [-5,-13], [11,-21]
Row#1	= [0,0], [-3,-3], [-15,-15], [9,-23]
Row#2	= [0,0], [0,0], [5,5], [-3,-3]
Row#3	= [0,0], [0,0], [0,0], [-8,-8]

[rY][cX]
Row#0	= [-3,-3], [-15,-15], [9,-23], [33,-46]
Row#1	= [0,0], [5,5], [-3,-3], [-6,-11]
Row#2	= [0,0], [0,0], [-8,-8], [-16,-16]
Row#3	= [0,0], [0,0], [0,0], [2,2]

[rY][cX]
Row#0	= [5,5], [-3,-3], [-6,-11], [13,-14]
Row#1	= [0,0], [-8,-8], [-16,-16], [8,-19]
Row#2	= [0,0], [0,0], [2,2], [-1,-1]
Row#3	= [0,0], [0,0], [0,0], [-3,-3]

MaxVerticesSumOfPolygon DP2D for "-8, 2, -3, 5", "1, 0, 1, 0": 104, Min: -95
[rY][cX]
Row#0	= [1,1], [3,3], [-3,-6], [-9,-18]
Row#1	= [0,0], [2,2], [-4,-4], [-12,-12]
Row#2	= [0,0], [0,0], [-2,-2], [-6,-6]
Row#3	= [0,0], [0,0], [0,0], [3,3]

[rY][cX]
Row#0	= [2,2], [-4,-4], [-12,-12], [-10,-16]
Row#1	= [0,0], [-2,-2], [-6,-6], [-5,-8]
Row#2	= [0,0], [0,0], [3,3], [4,4]
Row#3	= [0,0], [0,0], [0,0], [1,1]

[rY][cX]
Row#0	= [-2,-2], [-6,-6], [-5,-8], [-3,-12]
Row#1	= [0,0], [3,3], [4,4], [6,6]
Row#2	= [0,0], [0,0], [1,1], [3,3]
Row#3	= [0,0], [0,0], [0,0], [2,2]

[rY][cX]
Row#0	= [3,3], [4,4], [6,6], [0,-12]
Row#1	= [0,0], [1,1], [3,3], [-3,-6]
Row#2	= [0,0], [0,0], [2,2], [-4,-4]
Row#3	= [0,0], [0,0], [0,0], [-2,-2]

MaxVerticesSumOfPolygon DP2D for "1, 2, -2, 3", "0, 1, 1, 0": 0, Min: -18
[rY][cX]
Row#0	= [1,1], [2,2], [12,12]
Row#1	= [0,0], [2,2], [12,12]
Row#2	= [0,0], [0,0], [6,6]

[rY][cX]
Row#0	= [2,2], [12,12], [14,13]
Row#1	= [0,0], [6,6], [7,7]
Row#2	= [0,0], [0,0], [1,1]

[rY][cX]
Row#0	= [6,6], [7,7], [14,8]
Row#1	= [0,0], [1,1], [2,2]
Row#2	= [0,0], [0,0], [2,2]

MaxVerticesSumOfPolygon DP2D for "1, 2, 6", "1, 1, 0": 14, Min: 8
[rY][cX]
Row#0	= [1,1], [2,2], [8,8]
Row#1	= [0,0], [2,2], [8,8]
Row#2	= [0,0], [0,0], [6,6]

[rY][cX]
Row#0	= [2,2], [8,8], [9,9]
Row#1	= [0,0], [6,6], [7,7]
Row#2	= [0,0], [0,0], [1,1]

[rY][cX]
Row#0	= [6,6], [7,7], [14,8]
Row#1	= [0,0], [1,1], [2,2]
Row#2	= [0,0], [0,0], [2,2]

MaxVerticesSumOfPolygon DP2D for "1, 2, 6", "1, 0, 0": 14, Min: 8
[rY][cX]
Row#0	= [2,2], [12,12]
Row#1	= [0,0], [6,6]

[rY][cX]
Row#0	= [6,6], [8,8]
Row#1	= [0,0], [2,2]

MaxVerticesSumOfPolygon DP2D for "2, 6", "1, 0": 12, Min: 8
*/
#endif