#ifndef BINARY_STR_WO_CONSECU_1S_H
#define BINARY_STR_WO_CONSECU_1S_H
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include "Debug.h"
/*
http://www.geeksforgeeks.org/count-number-binary-strings-without-consecutive-1s/
Given a length N, count all possible distinct binary strings of length N such that there are no consecutive 1's.

For N=2, there are 3 possible binary strings: 00, 01, 10.
For N=3, there are 5 possible binary strings: 000, 010, 100, 101

DP1D: O(n) time, O(n) space
DP: O(n) time, O(1) space
*/
class BinaryStrWoConsecu1s
{
public:
	BinaryStrWoConsecu1s(){}
	~BinaryStrWoConsecu1s(){}

	int Count_DP1D(int n)
	{
		std::vector<int> dp_ending0(n);
		std::vector<int> dp_ending1(n);

		//base cases init for len = 1
		dp_ending0[0] = 1;//'0' is a valid binary string wo consecu 1's
		dp_ending1[0] = 1;//'1' is a valid binary string wo consecu 1's

		for (int i = 1; i < n; ++i)
		{
			dp_ending0[i] = dp_ending0[i - 1] + dp_ending1[i - 1];//ending in 0 can append either a '0' or a '1'
			dp_ending1[i] = dp_ending0[i - 1];//ending in 1 can append only a '0'
		}
		std::cout << Debug::ToStr1D<int>()(dp_ending0) << std::endl;
		std::cout << Debug::ToStr1D<int>()(dp_ending1) << std::endl;
		std::cout << "BinaryStrWoConsecu1s Count_DP1D for \"" << n << "\": " << dp_ending0[n - 1] + dp_ending1[n - 1] << std::endl;
		return dp_ending0[n - 1] + dp_ending1[n - 1];
	}

	int Count_DP(int n)
	{
		int dp_ending0 = 1;
		int dp_ending1 = 1;
		for (int i = 1; i < n; ++i)
		{
			int prev_dp_ending0 = dp_ending0;
			dp_ending0 = dp_ending0 + dp_ending1;
			dp_ending1 = prev_dp_ending0;
		}
		std::cout << "BinaryStrWoConsecu1s Count_DP for \"" << n << "\": " << dp_ending0 + dp_ending1 << std::endl;
		return dp_ending0 + dp_ending1;
	}
};
/*
1, 2, 3, 5, 8
1, 1, 2, 3, 5
BinaryStrWoConsecu1s Count_DP1D for "5": 13
BinaryStrWoConsecu1s Count_DP for "5": 13
*/
#endif