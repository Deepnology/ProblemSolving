#ifndef MAX_SUB_SQUARE_BORDER_H
#define MAX_SUB_SQUARE_BORDER_H
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Debug.h"
/*
http://www.careercup.com/question?id=2445
Cracking the coding interview: Hard
Given a square matrix, where each cell is filled with either black or white.
Find the maximum subsquare such that all four borders are filled with black pixels.

For each possible border length starting from N, iterate through all pixels to check the lower right square matrix of each pixel.
Once we found the first valid square matrix, we are done.

BruteForce: O(n^4) time
Preprocess: O(n^3) time, O(n^2) space

Leetcode: Largest 1-Bordered Square
Given a 2D grid of 0s and 1s, return the number of elements in the largest square subgrid that has all 1s on its border
 , or 0 if such a subgrid doesn't exist in the grid.
*/
class MaxSubSquareBorder
{
public:
	MaxSubSquareBorder(){}
	~MaxSubSquareBorder(){}

    int FindAreaSurroundedByMax1sSquareBorder(std::vector<std::vector<int>> & grid)
    {
        //O(N^3) time
        int N = grid.size(); int M = grid[0].size();
        std::vector<std::vector<int>> left(N, std::vector<int>(M, 0));
        std::vector<std::vector<int>> top(N, std::vector<int>(M, 0));
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                if (grid[i][j])
                {
                    left[i][j] = (j>0?left[i][j-1]+1:1);
                    top[i][j] = (i>0?top[i-1][j]+1:1);
                    //std::cout << i << "," << j << ":" << left[i][j] << "," << top[i][j] << std::endl;
                }
        for (int len = std::min(N, M); len > 0; --len)
            for (int i = 0; i+len-1 < N; ++i)
                for (int j = 0; j+len-1 < M; ++j)
                    if (grid[i][j]
                        &&left[i+len-1][j+len-1] >= len && top[i+len-1][j+len-1] >= len
                        && left[i][j+len-1] >= len
                        && top[i+len-1][j] >= len)
                        return len*len;
        return 0;
    }

	void BruteForce(const std::vector<std::vector<int> > & board)
	{
		int N = board.size();
		int curLen;
		int rowY;
		int colX;
		std::vector<std::pair<int, std::pair<int, int> > > res;
		for (curLen = N; curLen >= 2; --curLen)//O(n) time
		{
			int count = N - curLen + 1;
			for (rowY = 0; rowY < count; ++rowY)//O(n) time
			{
				for (colX = 0; colX < count; ++colX)//O(n) time
				{
					if (this->isSquare_4Scan(board, rowY, colX, curLen))//O(n) time
					{
						//since curLen starts from N, the first valid square border should be the one with max border length: return it
						res.push_back(std::make_pair(curLen, std::make_pair(rowY, colX)));
					}
				}
			}
		}
		Debug::Print2D<int>()(board, false);
		std::cout << "MaxSubSquareBorder BruteForce: " << Debug::ToStr1D<int>()(res) << std::endl;
	}
private:
	bool isSquare_4Scan(const std::vector<std::vector<int> > & board, int rowY, int colX, int len)//O(n) time
	{
		for (int i = 0; i < len; ++i)
		{
			/*upper row*/
			if (board[rowY][colX + i] == 0)
				return false;
			/*bottom row*/
			if (board[rowY + len - 1][colX + i] == 0)
				return false;
			/*left col*/
			if (board[rowY + i][colX] == 0)
				return false;
			/*right col*/
			if (board[rowY + i][colX + len - 1] == 0)
				return false;
		}
		return true;
	}

public:
	void Preprocess(const std::vector<std::vector<int> > & board)
	{
		int N = board.size();
		/*
		preprocess: O(n^2) time, O(n^2) space
		borderLens[rowY][colX].first: num of consecutive border pixels below (rowY,colX)
		borderLens[rowY][colX].second: num of consecutive border pixels on the right of (rowY,colX)
		*/
		std::vector<std::vector<std::pair<int, int> > > borderLens(N, std::vector<std::pair<int, int> >(N, std::make_pair(0, 0)));

		for (int rowY = N - 1; rowY >= 0; --rowY)
		{
			for (int colX = N - 1; colX >= 0; --colX)
			{
				if (rowY == N - 1 && colX == N - 1)//bottom rightmost corner pixel
				{
					borderLens[rowY][colX].first = board[rowY][colX];
					borderLens[rowY][colX].second = board[rowY][colX];
				}
				else if (rowY == N - 1)//bottom row
				{
					borderLens[rowY][colX].first = board[rowY][colX];
					if (board[rowY][colX] == 1)
						borderLens[rowY][colX].second = borderLens[rowY][colX + 1].second + 1;
				}
				else if (colX == N - 1)//rightmost col
				{
					borderLens[rowY][colX].second = board[rowY][colX];
					if (board[rowY][colX] == 1)
						borderLens[rowY][colX].first = borderLens[rowY + 1][colX].first + 1;
				}
				else//others
				{
					if (board[rowY][colX] == 1)
					{
						borderLens[rowY][colX].second = borderLens[rowY][colX + 1].second + 1;
						borderLens[rowY][colX].first = borderLens[rowY + 1][colX].first + 1;
					}
				}
			}
		}

		Debug::Print2D<int>()(borderLens, false);

		int curLen;
		int rowY;
		int colX;
		std::vector<std::pair<int, std::pair<int, int> > > res;
		for (curLen = N; curLen >= 2; --curLen)//O(n) time
		{
			int end = N - curLen + 1;
			for (rowY = 0; rowY < end; ++rowY)//O(n) time
			{
				for (colX = 0; colX < end; ++colX)//O(n) time
				{
					if (this->isSquare_Check3Pixels(borderLens, rowY, colX, curLen))//O(1) time
					{
						//since curLen starts from N, the first valid square border should be the one with max border length: return it
						res.push_back(std::make_pair(curLen, std::make_pair(rowY, colX)));
					}
				}
			}
		}
		
		std::cout << "MaxSubSquareBorder Preprocess: " << Debug::ToStr1D<int>()(res) << std::endl;
	}
private:
	bool isSquare_Check3Pixels(const std::vector<std::vector<std::pair<int, int> > > & borderLens, int rowY, int colX, int len)//O(1) time
	{
		/*upper leftmost pixel, check leftmost border below*/
		if (borderLens[rowY][colX].first < len)
			return false;
		/*upper leftmost pixel, check upper border on the right*/
		if (borderLens[rowY][colX].second < len)
			return false;
		/*bottom leftmost pixel, check bottom border on the right*/
		if (borderLens[rowY + len - 1][colX].second < len)
			return false;
		/*upper rightmost pixel, check rightmost border below*/
		if (borderLens[rowY][colX + len - 1].first < len)
			return false;

		return true;
	}
};
/*
[rY][cX]
Row#0	= 1, 1, 1, 0, 0, 0, 0, 0, 0, 0
Row#1	= 1, 1, 1, 1, 1, 0, 0, 0, 0, 0
Row#2	= 1, 1, 1, 0, 1, 0, 0, 0, 0, 0
Row#3	= 0, 1, 0, 1, 1, 1, 1, 1, 1, 1
Row#4	= 1, 1, 1, 1, 1, 0, 0, 1, 0, 1
Row#5	= 1, 0, 0, 1, 0, 0, 0, 1, 0, 1
Row#6	= 1, 0, 0, 1, 1, 0, 0, 1, 0, 1
Row#7	= 1, 1, 1, 1, 1, 1, 1, 1, 0, 1
Row#8	= 0, 0, 0, 1, 0, 0, 0, 0, 0, 1
Row#9	= 0, 0, 0, 1, 1, 1, 1, 1, 1, 1

MaxSubSquareBorder BruteForce: [7,(3,3)], [5,(3,3)], [4,(1,1)], [4,(4,0)], [3,(0,0)], [2,(0,0)], [2,(0,1)], [2,(1,0)], [2,(1,1)], [2,(3,3)], [2,(6,3)]
[rY][cX]
Row#0	= [3,3], [5,2], [3,1], [0,0], [0,0], [0,0], [0,0], [0,0], [0,0], [0,0]
Row#1	= [2,5], [4,4], [2,3], [1,2], [4,1], [0,0], [0,0], [0,0], [0,0], [0,0]
Row#2	= [1,3], [3,2], [1,1], [0,0], [3,1], [0,0], [0,0], [0,0], [0,0], [0,0]
Row#3	= [0,0], [2,1], [0,0], [7,7], [2,6], [1,5], [1,4], [5,3], [1,2], [7,1]
Row#4	= [4,5], [1,4], [1,3], [6,2], [1,1], [0,0], [0,0], [4,1], [0,0], [6,1]
Row#5	= [3,1], [0,0], [0,0], [5,1], [0,0], [0,0], [0,0], [3,1], [0,0], [5,1]
Row#6	= [2,1], [0,0], [0,0], [4,2], [2,1], [0,0], [0,0], [2,1], [0,0], [4,1]
Row#7	= [1,8], [1,7], [1,6], [3,5], [1,4], [1,3], [1,2], [1,1], [0,0], [3,1]
Row#8	= [0,0], [0,0], [0,0], [2,1], [0,0], [0,0], [0,0], [0,0], [0,0], [2,1]
Row#9	= [0,0], [0,0], [0,0], [1,7], [1,6], [1,5], [1,4], [1,3], [1,2], [1,1]

MaxSubSquareBorder Preprocess: [7,(3,3)], [5,(3,3)], [4,(1,1)], [4,(4,0)], [3,(0,0)], [2,(0,0)], [2,(0,1)], [2,(1,0)], [2,(1,1)], [2,(3,3)], [2,(6,3)]
*/
#endif