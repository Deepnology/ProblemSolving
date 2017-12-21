#ifndef FIND_NTH_DIGIT_FROM_1_TO_INFINITY_H
#define FIND_NTH_DIGIT_FROM_1_TO_INFINITY_H
#include "Debug.h"
/*
Leetcode: Nth Digit
Find the nth digit of the infinite integer sequence 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ...
Note:
n is positive and will fit within the range of a 32-bit signed integer (n < 2^31).
Example 1:
Input:
3
Output:
3
Example 2:
Input:
11
Output:
0
Explanation:
The 11th digit of the sequence 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ... is a 0, which is part of the number 10.
*/
class FindNthDigitFrom1toInfinity
{
public:
	FindNthDigitFrom1toInfinity() {}

	//nums: 1-9, 10-99, 100-999, ...
	//len:    1,     2,       3, ...
	//count:  9,    90,     900, ...
	int Solve(int n)
	{
		int numLen = 1;//the len of nums in each level
		long long numCount = 9;//the count of nums in each level
		long long numBegin = 1;//the begin num in each level
		long long digitCount = 0;//total digit count so far
		while (digitCount + numLen*numCount < (long long)n)
		{
			digitCount += numLen*numCount;
			numLen += 1;
			numCount *= 10;
			numBegin *= 10;
		}
		long long tgtNum = (n - digitCount - 1) / numLen + numBegin;
		int idx = (n - digitCount - 1) % numLen;//the idx starting from MSD of tgtNum
		int res = std::to_string(tgtNum)[idx] - '0';

		std::cout << "FindNthDigitFrom1toInfinity for \"" << n << "\"-th: " << res << std::endl;
		return res;
	}
};
/*
FindNthDigitFrom1toInfinity for "3"-th: 3
FindNthDigitFrom1toInfinity for "11"-th: 0
FindNthDigitFrom1toInfinity for "1000"-th: 3
*/
#endif
