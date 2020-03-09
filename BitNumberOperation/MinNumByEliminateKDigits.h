#ifndef MIN_NUM_BY_ELIMINATE_K_DIGITS_H
#define MIN_NUM_BY_ELIMINATE_K_DIGITS_H
#include "Debug.h"
/*
Leetcode: Remove K Digits
Given a non-negative integer num represented as a string, remove k digits from the number so that the new number is the smallest possible.
Note:
The length of num is less than 10002 and will be >= k.
The given num does not contain any leading zero.
Example 1:
Input: num = "1432219", k = 3
Output: "1219"
Explanation: Remove the three digits 4, 3, and 2 to form the new number 1219 which is the smallest.
Example 2:
Input: num = "10200", k = 1
Output: "200"
Explanation: Remove the leading 1 and the number is 200. Note that the output must not contain leading zeroes.
Example 3:
Input: num = "10", k = 2
Output: "0"
Explanation: Remove all the digits from the number and it is left with nothing which is 0.

see also CreateMaxNumFrom2Arrays.h, SlidingWindowMax.h, SubArrWLessEqualMinMaxDiff.h
*/
class MinNumByEliminateKDigits
{
public:
	MinNumByEliminateKDigits() {}

	std::string SortedStack(std::string num, int k)
	{
		int N = num.size();
		std::string sortedStk;
		int rmCount = 0;
		for (int i = 0; i < N; ++i)
		{
			while (!sortedStk.empty() && sortedStk.back() > num[i] && rmCount < k)//only incr rmCount when popping back !!!
			{
				sortedStk.pop_back();
				++rmCount;
			}
			//skip adding leading 0
			if (!sortedStk.empty() || num[i] != '0')
				sortedStk += num[i];
			//else//leading 0: skip it
			//    ++rmCount;//(don't incr rmCount to count in 0s here !!!)
		}
		while (!sortedStk.empty() && rmCount < k)//only incr rmCount when popping back !!!
		{
			sortedStk.pop_back();
			++rmCount;
		}
		sortedStk = sortedStk.empty() ? "0" : sortedStk;

		std::cout << "MinNumByEliminateKDigits SortedStack for \"" << num << "\", k=\"" << k << "\": " << sortedStk << std::endl;
		return sortedStk;
	}
};
/*
MinNumByEliminateKDigits SortedStack for "1432219", k="3": 1219
MinNumByEliminateKDigits SortedStack for "10200", k="1": 200
MinNumByEliminateKDigits SortedStack for "10200", k="2": 0
MinNumByEliminateKDigits SortedStack for "10", k="2": 0
*/
#endif
