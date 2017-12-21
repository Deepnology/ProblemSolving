#ifndef MAX_NUM_BY_SWAP_2_DIGITS_H
#define MAX_NUM_BY_SWAP_2_DIGITS_H
#include "Debug.h"
/*
Leetcode: Maximum Swap
Given a non-negative integer, you could swap two digits at most once to get the maximum valued number.
Return the maximum valued number you could get.
Example 1:
Input: 2736
Output: 7236
Explanation: Swap the number 2 and the number 7.
Example 2:
Input: 9973
Output: 9973
Explanation: No swap.
*/
class MaxNumBySwap2Digits
{
public:
	MaxNumBySwap2Digits() {}

	int Linear(int num)
	{
		std::string str = std::to_string(num);
		std::vector<int> lastIdx(10, -1);//rightmost idx of digits [0:9]
		int N = str.size();
		for (int i = 0; i < N; ++i)//from MSD to LSD
			lastIdx[str[i] - '0'] = i;
		for (int i = 0; i < N; ++i)//from MSD to LSD
		{
			for (int j = 9; j >= 0; --j)//from 9 to 0
			{
				if (lastIdx[j] != -1 && j >(str[i] - '0') //there exists a bigger digit
					&& lastIdx[j] > i)//the bigger digit is on the right side of i
				{
					char c = str[i];
					str[i] = '0' + j;
					str[lastIdx[j]] = c;
					return stoi(str);
				}
			}
		}
		return num;
	}
};
#endif
