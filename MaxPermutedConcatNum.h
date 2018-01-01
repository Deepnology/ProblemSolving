#ifndef MAX_PERMUTED_CONCAT_NUM_H
#define MAX_PERMUTED_CONCAT_NUM_H
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include "Debug.h"
/*
https://leetcode.com/problems/largest-number/
http://leetcodesolution.blogspot.tw/2015/01/leetcode-largest-number.html
Given a list of non negative integers, arrange them such that they form the largest number.
For example, given [3, 30, 34, 5, 9], the largest formed number is 9534330.
Note: The result may be very large, so you need to return a string instead of an integer.

The question is how should we sort the numbers?
Given 2 numbers, how do we know which concatenation order yields a bigger combined number?
It is pretty strait forward, just get two string combinations and compare which one is bigger.
For example: [12,121], since 12121 is greater than 12112, 12121 is the number we want.
*/
class MaxPermutedConcatNum
{
public:
	MaxPermutedConcatNum(){}
	~MaxPermutedConcatNum(){}


	std::string BySort(std::vector<int> && v)
	{
		std::string before = Debug::ToStr1D<int>()(v);
		int N = v.size();

		std::sort(v.begin(), v.end(), [](const int & a, const int & b)->bool
		{
			std::string s1 = std::to_string(a) + std::to_string(b);
			std::string s2 = std::to_string(b) + std::to_string(a);
			return s1 < s2;
		});

		/*
		for case [0, 0], if max is 0, then return "0" rather "00"
		*/
		if (v[N - 1] == 0)
			return "0";

		std::string res;
		for (int i = N - 1; i >= 0; --i)
			res.append(std::to_string(v[i]));

		std::cout << Debug::ToStr1D<int>()(v) << std::endl;
		std::cout << "MaxPermutedConcatNum BySort for \"" << before << "\": " << res << std::endl;
		return res;
	}
};
/*
30, 3, 34, 5, 9
MaxPermutedConcatNum BySort for "3, 30, 34, 5, 9": 9534330
121, 12
MaxPermutedConcatNum BySort for "12, 121": 12121
*/
#endif