#ifndef ONE_EDIT_DISTANCE_H
#define ONE_EDIT_DISTANCE_H
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include "Debug.h"
/*
Leetcode: One Edit Distance
Given two strings S and T, determine if they are both one edit distance apart.
http://meetqun.com/thread-2854-1-1.html
2 cases for 1 edit distance:
1. same length with 1 difference letter
2. length difference is 1, with 0 diff letters excluding the extra 1 letter in the longer string

O(n) time, O(1) space
*/
class OneEditDistance
{
public:
	OneEditDistance(){}
	~OneEditDistance(){}

	bool Solve(const std::string & s1, const std::string & s2)
	{
		if (s1.size() > s2.size())
			return this->Solve(s2, s1);
		//now N1 <= N2

		int N1 = s1.size();
		int N2 = s2.size();
		bool res;

		if (N2 - N1 > 1)//more than 1 edit distance
			res = false;
		else
		{
			//now N1 == N2 (must have 1 diff), or N1 + 1 == N2 (must have 0 diff excluding the extra 1 letter in the longer string)

			bool found1stDiff = false;
			bool found2ndDiff = false;
			for (int i = 0, j = 0; i < N1; ++i, ++j)
			{
				if (s1[i] != s2[j])
				{
					if (found1stDiff)
					{
						found2ndDiff = true;
						break;
					}
					found1stDiff = true;

					if (N1 != N2)//exclude current j
						--i;
				}
			}

			if (found2ndDiff)
			{
				res = false;
			}
			else
			{
				res = found1stDiff || 
					N1 != N2;//found no diff from s1[0]~s1[N1-1], but s2 has one more letter than s1 in the back
			}
		}

		std::cout << "OneEditDistance for \"" << s1 << "\" and \"" << s2 << "\": " << res << std::endl;
		return res;
	}
};
/*
OneEditDistance for "abc" and "abcd": 1
OneEditDistance for "abcd" and "axcd": 1
OneEditDistance for "abc" and "xabc": 1
OneEditDistance for "abcd" and "abcd": 0
OneEditDistance for "axc" and "abcd": 0
*/
#endif