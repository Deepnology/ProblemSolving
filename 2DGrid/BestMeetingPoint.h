#ifndef BEST_MEETING_POINT_H
#define BEST_MEETING_POINT_H
#include "Debug.h"
/*
Leetcode: Best Meeting Point
A group of two or more people wants to meet and minimize the total travel distance.
You are given a 2D grid of values 0 or 1, where each 1 marks the home of someone in the group.
The distance is calculated using Manhattan Distance, where distance(p1, p2) = |p2.x - p1.x| + |p2.y - p1.y|.
For example, given three people living at (0,0), (0,4), and (2,2):
1 - 0 - 0 - 0 - 1
|   |   |   |   |
0 - 0 - 0 - 0 - 0
|   |   |   |   |
0 - 0 - 1 - 0 - 0
The point (0,2) is an ideal meeting point, as the total travel distance of 2+2+2=6 is minimal. So return 6.
Hint:
Try to solve it in one dimension first. How can this solution apply to the two dimension case?


This problem is converted to find the median value on x-axis and y-axis.
For even points, the median can be either the left or right of the middle pair (because sum of distances from other points to both the median points are the same).
For odd points, the median is the middle point.
The min total distances are the sum of x distances from all points to the median point on the x-axis and the sum of y distances from all points to the median point on the y-axis.
*/
class BestMeetingPoint
{
public:
	BestMeetingPoint() {}
	~BestMeetingPoint() {}

	int MinTotalDist(const std::vector<std::vector<int>> & board)
	{
		int N = board.size();
		int M = board[0].size();

		std::vector<int> rows;
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < M; ++j)
			{
				if (board[i][j] == 1)
					rows.push_back(i);
			}
		}
		//now rows contains all x-values and is sorted

		std::vector<int> cols;
		for (int j = 0; j < M; ++j)
		{
			for (int i = 0; i < N; ++i)
			{
				if (board[i][j] == 1)
					cols.push_back(j);
			}
		}
		//now cols contains all y-values and is sorted

		int sumDist = 0;
		int rowMedian = rows[rows.size() / 2];
		for (const int & i : rows)
			sumDist += std::abs(i - rowMedian);

		int colMedian = cols[cols.size() / 2];
		for (const int & j : cols)
			sumDist += std::abs(j - colMedian);

		Debug::Print2D<int>()(board, false);
		std::cout << "rows: " << Debug::ToStr1D<int>()(rows) << std::endl;
		std::cout << "cols: " << Debug::ToStr1D<int>()(cols) << std::endl;
		std::cout << "BestMeetingPoint MinTotalDist FindXandYMedian: " << sumDist << ", at (" << rowMedian << ", " << colMedian << ")" << std::endl;
		return sumDist;
	}
};
/*
[rY][cX]
Row#0	= 1, 0, 0, 0, 1
Row#1	= 0, 0, 0, 0, 0
Row#2	= 0, 0, 1, 0, 0

rows: 0, 0, 2
cols: 0, 2, 4
BestMeetingPoint MinTotalDist FindXandYMedian: 6, at (0, 2)
[rY][cX]
Row#0	= 1, 0, 0, 0, 0, 1, 1
Row#1	= 0, 0, 0, 1, 0, 0, 0
Row#2	= 0, 0, 0, 0, 0, 0, 1
Row#3	= 0, 1, 1, 0, 0, 0, 0
Row#4	= 0, 0, 0, 0, 0, 1, 0
Row#5	= 0, 1, 0, 0, 1, 0, 0

rows: 0, 0, 0, 1, 2, 3, 3, 4, 5, 5
cols: 0, 1, 1, 2, 3, 4, 5, 5, 6, 6
BestMeetingPoint MinTotalDist FindXandYMedian: 36, at (3, 4)
*/
#endif
