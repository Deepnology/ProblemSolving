#ifndef MAGICAL_STRING_H
#define MAGICAL_STRING_H
#include "Debug.h"
/*
Leetcode: Magical String
A magical string S consists of only '1' and '2' and obeys the following rules:
The string S is magical because concatenating the number of contiguous occurrences of characters '1' and '2' generates the string S itself.
The first few elements of string S is the following: S = "1221121221221121122......"
If we group the consecutive '1's and '2's in S, it will be:
1 22 11 2 1 22 1 22 11 2 11 22 ......
and the occurrences of '1's or '2's in each group are:
1 2	2 1 1 2 1 2 2 1 2 2 ......
You can see that the occurrence sequence above is the S itself.
Given an integer N as input, return the number of '1's in the first N number in the magical string S.
Note: N will not exceed 100,000.
Example 1:
Input: 6
Output: 3
Explanation: The first 6 elements of magical string S is "12211" and it contains three 1's, so return 3.
*/
class MagicalString
{
public:
	MagicalString() {}

	int Solve(int n)
	{
		int res = CountNum1s(n);
		std::cout << "MagicalString CountNum1s for \"" << n << "\": " << res << std::endl;
		return res;
	}

	int CountNum1s(int n)
	{
		if (n <= 0) return 0;
		if (n <= 3) return 1;

		//if start with 1, then next num must be flipped to 2, which means curNum '2' must have 2 occurrences, so the first 3 must be 1,2,2
		std::vector<int> v({ 1,2,2 });
		int res = 1;//count of 1s so far
		int curNum = 1;
		int curCount = 2;//idx in v
		while ((int)v.size() < n)
		{
			if (curNum == 1)
				res += v[curCount];
			for (int i = 0; i < v[curCount]; ++i)
				v.push_back(curNum);
			curNum = curNum == 1 ? 2 : 1;//flip curNum
			++curCount;//advance idx in v
		}
		//v.size() can be either n or n+1
		if (v.size() == n)
			return res;
		return res - (v.back() == 1 ? 1 : 0);
	}
};
/*
MagicalString CountNum1s for "6": 3
MagicalString CountNum1s for "19": 9
*/
#endif
