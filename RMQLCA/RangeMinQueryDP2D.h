#ifndef	RANGE_MIN_QUERY_DP2D_H
#define RANGE_MIN_QUERY_DP2D_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <algorithm>
#include <functional>
#include "Debug.h"
/*
http://www.topcoder.com/tc?d1=tutorials&d2=lowestCommonAncestor&module=Static
*/
class RangeMinQueryDP2D
{
public:
	RangeMinQueryDP2D(){}
	~RangeMinQueryDP2D(){}

	//O(n^2) time
	std::vector<std::vector<int> > Construct(const std::vector<int> & A)
	{
		int N = A.size();
		std::vector<std::vector<int> > dp2d(N, std::vector<int>(N, 0));
		//dp2d[rangeStart][rangeEnd]: range min
		//in dp2d table, construct only upper right side above the diagonal
		//because rangeStart <= rangeEnd

		for (int i = 0; i < N; ++i)
			dp2d[i][i] = A[i];
		for (int i = 0; i < N; ++i)
		{
			for (int j = i + 1; j < N; ++j)
			{
				dp2d[i][j] = std::min(dp2d[i][j - 1], A[j]);
				/*
				if (dp2d[i][j - 1] < A[j])
					dp2d[i][j] = dp2d[i][j - 1];
				else
					dp2d[i][j] = A[j];
				*/
			}
		}
		std::cout << "RangeMinQueryDP2D Construct for \"" << Debug::ToStr1D<int>()(A) << "\": " << std::endl;
		Debug::Print2D<int>()(dp2d, false);
		return dp2d;
	}

	//O(1) time
	int QueryRange(const std::vector<std::vector<int> > & DP2D, int targetStart, int targetEnd)
	{
		int N = DP2D.size();
		if (targetStart < 0 || targetEnd > N - 1 || targetStart > targetEnd)
			throw std::runtime_error("Invalid Input");
		int res = DP2D[targetStart][targetEnd];
		std::cout << "RangeMinQueryDP2D QueryRange for \"" << targetStart << "," << targetEnd << "\": " << res << std::endl;
		return res;
	}
};
/*
angeMinQueryDP2D Construct for "16, 18, 33, 98":
[rY][cX]
Row#0	= 16, 16, 16, 16
Row#1	= 0, 18, 18, 18
Row#2	= 0, 0, 33, 33
Row#3	= 0, 0, 0, 98

RangeMinQueryDP2D QueryRange for "1,3": 18
*/
#endif