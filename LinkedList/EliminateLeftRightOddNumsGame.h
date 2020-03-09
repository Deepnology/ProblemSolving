#ifndef ELIMINATE_LEFT_RIGHT_ODD_NUMS_GAME_H
#define ELIMINATE_LEFT_RIGHT_ODD_NUMS_GAME_H
#include "Debug.h"
/*
Leetcode: Elimination Game
There is a list of sorted integers from 1 to n. Starting from left to right, remove the first number and every other number afterward until you reach the end of the list.
Repeat the previous step again, but this time from right to left, remove the right most number and every other number from the remaining numbers.
We keep repeating the steps again, alternating left to right and right to left, until a single number remains.
Find the last number that remains starting with a list of length n.
Example:
Input:
n = 9,
1 2 3 4 5 6 7 8 9
2 4 6 8
2 6
6
Output:
6
*/
class EliminateLeftRightOddNumsGame
{
public:
	EliminateLeftRightOddNumsGame() {}

	int Recur(int n)//O(logn) time
	{
		int res = recur(n, true);
		std::cout << "EliminateLeftRightOddNumsGame for \"1..." << n << "\": " << res << std::endl;
		return res;
	}
private:
	int recur(int n, bool isLeft)//returns the last position of input n
	{
		if (n == 1) return 1;

		//now consider the cases to eliminate ODD nums
		if (isLeft || (n & 1))
		{
			int lastPosition = recur(n / 2, !isLeft);//gets lastPosition of input n/2
			return lastPosition * 2;//gets lastPosition of input n
		}
		else//the cases to eliminate EVEN nums
		{
			int lastPosition = recur(n / 2, !isLeft);//gets lastPosition of input n/2
			return lastPosition * 2 - 1;//gets lastPosition of input n
		}
	}
};
/*
EliminateLeftRightOddNumsGame for "1...9": 6
*/
#endif
