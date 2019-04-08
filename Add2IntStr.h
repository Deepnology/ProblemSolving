#ifndef ADD_2_INT_STR_H
#define ADD_2_INT_STR_H
#include <iostream>
#include <string>
#include <algorithm>
/*
Leetcode: Add Strings
http://www.careercup.com/question?id=6330205329162240
Given two non-negative integers num1 and num2 represented as string, return the sum of num1 and num2.
Note:
The length of both num1 and num2 is < 5100.
Both num1 and num2 contains only digits 0-9.
Both num1 and num2 does not contain any leading zero.
You must not use any built-in BigInteger library or convert the inputs to integer directly.

Leetcode: Add to Array-Form of Integer
For a non-negative integer X, the array-form of X is an array of its digits in left to right order.
For example, if X = 1231, then the array form is [1,2,3,1].
Given the array-form A of a non-negative integer X, return the array-form of the integer X+K.
Example 1:
Input: A = [1,2,0,0], K = 34
Output: [1,2,3,4]
Explanation: 1200 + 34 = 1234
Example 2:
Input: A = [2,7,4], K = 181
Output: [4,5,5]
Explanation: 274 + 181 = 455
Example 3:
Input: A = [2,1,5], K = 806
Output: [1,0,2,1]
Explanation: 215 + 806 = 1021
Example 4:
Input: A = [9,9,9,9,9,9,9,9,9,9], K = 1
Output: [1,0,0,0,0,0,0,0,0,0,0]
Explanation: 9999999999 + 1 = 10000000000

See also Add2BinaryStr.h
*/
class Add2IntStr
{
public:
	Add2IntStr(){}
	~Add2IntStr(){}

	std::string Solve(const std::string & a, const std::string & b)
	{
		int N = std::max(a.size(), b.size());
		std::string res(N + 1, '0');
		int carry = 0;
		int ai = a.size() - 1;
		int bi = b.size() - 1;
		for (int i = N; i >= 0; --i)
		{
			int sum = carry;
			if (ai >= 0)
			{
				sum += a[ai--] - '0';
			}
			if (bi >= 0)
			{
				sum += b[bi--] - '0';
			}
			carry = sum / 10;
			res[i] = sum % 10 + '0';
		}
		if (res[0] == '0')
			res = res.substr(1, N);

		std::cout << "Add2IntStr for \"" << a << "\", \"" << b << "\": " << res << std::endl;
		return res;
	}

	std::vector<int> Solve2(std::vector<int> && A, int K)
	{
		int N = A.size();
		for (int i = N-1; i >= 0; --i)
		{
			A[i] += K;
			K = A[i] / 10;
			A[i] %= 10;
		}
		while (K > 0)
		{
			A.insert(A.begin(), K%10);
			K /= 10;
		}
		return A;
	}
};
/*
Add2IntStr for "6701", "4312": 11013
Add2IntStr for "7001", "23": 7024
Add2IntStr for "1", "2": 3
Add2IntStr for "5", "7": 12
*/
#endif