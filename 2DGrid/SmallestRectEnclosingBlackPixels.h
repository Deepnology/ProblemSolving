#ifndef SMALLEST_RECT_ENCLOSING_BLACK_PIXELS_H
#define SMALLEST_RECT_ENCLOSING_BLACK_PIXELS_H
#include "Debug.h"
/*
Leetcode: Smallest Rectangle Enclosing Black Pixels
An image is represented by a binary matrix with 0 as a white pixel and 1 as a black pixel.
The black pixels are connected, i.e., there is only one black region.
Pixels are connected horizontally and vertically.
Given the location (x, y) of one of the black pixels, return the area of the smallest (axis-aligned) rectangle that encloses all black pixels.
For example, given the following image:
[
"0010",
"0110",
"0100"
]
and x = 0, y = 2,
Return 6.

BruteForce: check each pixel to get black pixel's minLeft, maxRight, minTop, maxBottom
DFS: DFS from an arbitrary black pixel to traverse all connected black pixels to get minLeft, maxRight, minTop, maxBottom
BinarySearch: vertical direction: find the 1st black pixel from row_0->row_x (lower bound) to get minTop, find the 1st black pixel from row_N->row_x (lower bound) to get maxBottom. Determining if a row contains a black pixel is linear scan.
              horizontal direction: find the 1st black pixel from col_0->col_y (lower bound) to get minLeft, find the 1st black pixel from col_M->col_y (lower bound) to get maxRight. Determining if a col contains a black pixel is linear scan.
*/
class SmallestRectEnclosingBlackPixels
{
public:
	SmallestRectEnclosingBlackPixels() {}
	~SmallestRectEnclosingBlackPixels() {}

	int BruteForce(const std::vector<std::vector<int>> & board, int x, int y)//x: row, y: col
	{
		int N = board.size();
		int M = board[0].size();

		int minLeft = y;
		int maxRight = y;
		int minTop = x;
		int maxBottom = x;

		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < M; ++j)
			{
				if (board[i][j] == 1)
				{
					minLeft = std::min(minLeft, j);//minLeft is the leftmost 1's col index
					maxRight = std::max(maxRight, j);//maxRight is the leftmost 1's col index
					minTop = std::min(minTop, i);//minTop is the topmost 1's row index
					maxBottom = std::max(maxBottom, i);//maxBottom is the bottommost 1's row index
				}
			}
		}

		int area = (maxRight - minLeft + 1) * (maxBottom - minTop + 1);
		Debug::Print2D<int>()(board, false);
		std::cout << "SmallestRectEnclosingBlackPixels BruteForce for \"(" << x << ", " << y << ")\": " << area << std::endl;
		return area;
	}

	int DFS(const std::vector<std::vector<int>> & board, int x, int y)
	{
		int minLeft = y;
		int maxRight = y;
		int minTop = x;
		int maxBottom = x;
		int N = board.size();
		int M = board[0].size();
		std::vector<std::vector<int>> visit(N, std::vector<int>(M, 0));
		this->recur(board, x, y, minLeft, maxRight, minTop, maxBottom, visit);

		int area = (maxRight - minLeft + 1) * (maxBottom - minTop + 1);
		Debug::Print2D<int>()(board, false);
		std::cout << "SmallestRectEnclosingBlackPixels DFS for \"(" << x << ", " << y << ")\": " << area << std::endl;
		return area;
	}
private:
	void recur(const std::vector<std::vector<int>> & board, int x, int y, int & minLeft, int & maxRight, int & minTop, int & maxBottom,
		std::vector<std::vector<int>> & visit)
	{
		int N = board.size();
		int M = board[0].size();

		visit[x][y] = 1;
		minLeft = std::min(minLeft, y);//minLeft is the leftmost 1's col index
		maxRight = std::max(maxRight, y);//maxRight is the leftmost 1's col index
		minTop = std::min(minTop, x);//minTop is the topmost 1's row index
		maxBottom = std::max(maxBottom, x);//maxBottom is the bottommost 1's row index

		if (x - 1 >= 0 && board[x - 1][y] == 1 && visit[x - 1][y] == 0)
			this->recur(board, x - 1, y, minLeft, maxRight, minTop, maxBottom, visit);
		if (x + 1 < N && board[x + 1][y] == 1 && visit[x + 1][y] == 0)
			this->recur(board, x + 1, y, minLeft, maxRight, minTop, maxBottom, visit);
		if (y - 1 >= 0 && board[x][y - 1] == 1 && visit[x][y - 1] == 0)
			this->recur(board, x, y - 1, minLeft, maxRight, minTop, maxBottom, visit);
		if (y + 1 < M && board[x][y + 1] == 1 && visit[x][y + 1] == 0)
			this->recur(board, x, y + 1, minLeft, maxRight, minTop, maxBottom, visit);
	}

public:
	int BinarySearch(const std::vector<std::vector<int>> & board, int x, int y)
	{
		int N = board.size();
		int M = board[0].size();

		int top = 0;
		int bottom = x;
		while (top <= bottom)
		{
			int mid = top + (bottom - top) / 2;
			if (this->rowContains1(board, mid))
				bottom = mid - 1;
			else
				top = mid + 1;
		}
		//now top is lower bound from top->bottom
		int resTop = top;

		top = x;
		bottom = N - 1;
		while (top <= bottom)
		{
			int mid = top + (bottom - top) / 2;
			if (this->rowContains1(board, mid))
				top = mid + 1;
			else
				bottom = mid - 1;
		}
		//now bottom is lower bound from bottom->top
		int resBottom = bottom;

		
		int left = 0;
		int right = y;
		while (left <= right)
		{
			int mid = left + (right - left) / 2;
			if (this->colContains1(board, mid))
				right = mid - 1;
			else
				left = mid + 1;
		}
		//now left is lower bound from left->right
		int resLeft = left;

		left = y;
		right = M - 1;
		while (left <= right)
		{
			int mid = left + (right - left) / 2;
			if (this->colContains1(board, mid))
				left = mid + 1;
			else
				right = mid - 1;
		}
		//now right is lower bound from right->left
		int resRight = right;

		int area = (resRight - resLeft + 1) * (resBottom - resTop + 1);
		Debug::Print2D<int>()(board, false);
		std::cout << "SmallestRectEnclosingBlackPixels BinarySearch for \"(" << x << ", " << y << "\"): " << area << std::endl;
		return area;
	}

	bool rowContains1(const std::vector<std::vector<int>> & board, int row)
	{
		int N = board.size();
		int M = board[0].size();
		for (int i = 0; i < M; ++i)
		{
			if (board[row][i] == 1)
				return true;
		}
		return false;
	}
	bool colContains1(const std::vector<std::vector<int>> & board, int col)
	{
		int N = board.size();
		int M = board[0].size();
		for (int i = 0; i < N; ++i)
		{
			if (board[i][col] == 1)
				return true;
		}
		return false;
	}
};
/*
[rY][cX]
Row#0	= 0, 0, 1, 0
Row#1	= 0, 1, 1, 0
Row#2	= 0, 1, 0, 0

SmallestRectEnclosingBlackPixels BruteForce for "(0, 2)": 6
[rY][cX]
Row#0	= 0, 0, 1, 0
Row#1	= 0, 1, 1, 0
Row#2	= 0, 1, 0, 0

SmallestRectEnclosingBlackPixels DFS for "(0, 2)": 6
[rY][cX]
Row#0	= 0, 0, 1, 0
Row#1	= 0, 1, 1, 0
Row#2	= 0, 1, 0, 0

SmallestRectEnclosingBlackPixels BinarySearch for "(0, 2"): 6
[rY][cX]
Row#0	= 0, 0, 0, 0, 0, 0, 0, 0
Row#1	= 0, 0, 1, 1, 1, 1, 1, 0
Row#2	= 1, 1, 1, 0, 0, 0, 1, 0
Row#3	= 0, 0, 1, 0, 1, 0, 1, 0
Row#4	= 0, 1, 1, 1, 1, 0, 1, 0
Row#5	= 0, 1, 0, 1, 1, 0, 0, 0
Row#6	= 0, 1, 0, 0, 1, 1, 0, 0
Row#7	= 0, 1, 0, 0, 0, 1, 0, 0
Row#8	= 0, 0, 0, 0, 0, 0, 0, 0

SmallestRectEnclosingBlackPixels BruteForce for "(2, 2)": 49
[rY][cX]
Row#0	= 0, 0, 0, 0, 0, 0, 0, 0
Row#1	= 0, 0, 1, 1, 1, 1, 1, 0
Row#2	= 1, 1, 1, 0, 0, 0, 1, 0
Row#3	= 0, 0, 1, 0, 1, 0, 1, 0
Row#4	= 0, 1, 1, 1, 1, 0, 1, 0
Row#5	= 0, 1, 0, 1, 1, 0, 0, 0
Row#6	= 0, 1, 0, 0, 1, 1, 0, 0
Row#7	= 0, 1, 0, 0, 0, 1, 0, 0
Row#8	= 0, 0, 0, 0, 0, 0, 0, 0

SmallestRectEnclosingBlackPixels DFS for "(2, 2)": 49
[rY][cX]
Row#0	= 0, 0, 0, 0, 0, 0, 0, 0
Row#1	= 0, 0, 1, 1, 1, 1, 1, 0
Row#2	= 1, 1, 1, 0, 0, 0, 1, 0
Row#3	= 0, 0, 1, 0, 1, 0, 1, 0
Row#4	= 0, 1, 1, 1, 1, 0, 1, 0
Row#5	= 0, 1, 0, 1, 1, 0, 0, 0
Row#6	= 0, 1, 0, 0, 1, 1, 0, 0
Row#7	= 0, 1, 0, 0, 0, 1, 0, 0
Row#8	= 0, 0, 0, 0, 0, 0, 0, 0

SmallestRectEnclosingBlackPixels BinarySearch for "(2, 2"): 49
*/
#endif
