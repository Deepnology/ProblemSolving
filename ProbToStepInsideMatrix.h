#ifndef PROB_TO_STEP_INSIDE_MATRIX_H
#define PROB_TO_STEP_INSIDE_MATRIX_H
#include <vector>
#include <queue>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include "Debug.h"
/*
Google
http://www.careercup.com/question?id=15556758
Given a NxN matrix representing an island.
At a given location x, y in the matrix, you can step up, down, left, and right for a particular number of steps.
Calculate the probability at location x, y with a number of steps that you still remain inside the matrix.
O(steps * N^2) time, O(steps * N^2) space

Leetcode: Knight Probability in Chessboard
*/
class ProbToStepInsideMatrix
{
public:
	ProbToStepInsideMatrix(){}
	~ProbToStepInsideMatrix(){}

	double SolveDFS(int N, int steps, int x, int y)
	{
		if (x < 0 || x >= N || y < 0 || y >= N)
			return -1.0;
		std::vector<std::vector<std::vector<double> > > dp(N, std::vector<std::vector<double> >(N, std::vector<double>(steps, -1.0)));
		/*no need to iterate x from 0~N-1 and y from 0~N-1*/
		this->dfsRecur(N, x, y, steps, dp);

		Debug::Print3D<double>()(dp);
		double res = dp[x][y][steps - 1];
		std::cout << "ProbToStepInsideMatrix for \"" << N << "x" << N << "\", \"" << steps << "\" steps at [" << x << "," << y << "]: " << res << std::endl;
		return res;
	}
	double dfsRecur(int N, int curX, int curY, int curSteps, std::vector<std::vector<std::vector<double> > > & dp)
	{
		if (curSteps == 0)//reaches end and still remain inside matrix: prob is 1
			return 1.0;
		if (dp[curX][curY][curSteps - 1] != -1.0)
			return dp[curX][curY][curSteps - 1];

		//now we still have curSteps to advance from [curX,curY]
		double prob = 0.0;
		if (curX > 0)
			prob += 0.25 * this->dfsRecur(N, curX - 1, curY, curSteps - 1, dp);
		if (curX < (N - 1))
			prob += 0.25 * this->dfsRecur(N, curX + 1, curY, curSteps - 1, dp);
		if (curY > 0)
			prob += 0.25 * this->dfsRecur(N, curX, curY - 1, curSteps - 1, dp);
		if (curY < (N - 1))
			prob += 0.25 * this->dfsRecur(N, curX, curY + 1, curSteps - 1, dp);
		return dp[curX][curY][curSteps - 1] = prob;
	}

	//Leetcode: Knight Probability in Chessboard
	double KnightProbability(int N, int K, int r, int c)
	{
		if (K == 0)
			return 1.0;
		std::vector<std::vector<std::vector<double>>> dp(N, std::vector<std::vector<double>>(N, std::vector<double>(K, -1.0)));
		recur(N, r, c, K, dp);
		return dp[r][c][K-1];
	}
	double recur(int N, int row, int col, int steps, std::vector<std::vector<std::vector<double>>> & dp)
	{
		if (steps == 0)
			return 1.0;
		if (dp[row][col][steps-1] != -1.0)
			return dp[row][col][steps-1];
		double prob = 0;
		if (row+2 < N && col-1 >= 0)
			prob += 1.0/8.0 * recur(N, row+2, col-1, steps-1, dp);
		if (row+2 < N && col+1 < N)
			prob += 1.0/8.0 * recur(N, row+2, col+1, steps-1, dp);
		if (row-2 >= 0 && col-1 >= 0)
			prob += 1.0/8.0 * recur(N, row-2, col-1, steps-1, dp);
		if (row-2 >= 0 && col+1 < N)
			prob += 1.0/8.0 * recur(N, row-2, col+1, steps-1, dp);

		if (col+2 < N && row-1 >= 0)
			prob += 1.0/8.0 * recur(N, row-1, col+2, steps-1, dp);
		if (col+2 < N && row+1 < N)
			prob += 1.0/8.0 * recur(N, row+1, col+2, steps-1, dp);
		if (col-2 >= 0 && row-1 >= 0)
			prob += 1.0/8.0 * recur(N, row-1, col-2, steps-1, dp);
		if (col-2 >= 0 && row+1 < N)
			prob += 1.0/8.0 * recur(N, row+1, col-2, steps-1, dp);

		return dp[row][col][steps-1] = prob;
	}
};
/*
[cX][rY][dZ]
Row#0	= -1,-1,-1.	-1,-1,-1.	0.75,-1,-1.	-1,-1,-1.	-1,-1,-1.
Row#1	= -1,-1,-1.	1,-1,-1.	-1,0.9375,-1.	1,-1,-1.	-1,-1,-1.
Row#2	= 0.75,-1,-1.	-1,0.9375,-1.	1,-1,0.9375.	-1,0.9375,-1.	0.75,-1,-1.
Row#3	= -1,-1,-1.	1,-1,-1.	-1,0.9375,-1.	1,-1,-1.	-1,-1,-1.
Row#4	= -1,-1,-1.	-1,-1,-1.	0.75,-1,-1.	-1,-1,-1.	-1,-1,-1.

ProbToStepInsideMatrix for "5x5", "3" steps at [2,2]: 0.9375
*/
#endif