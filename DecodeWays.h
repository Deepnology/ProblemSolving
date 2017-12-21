#ifndef DECODE_WAYS_H
#define DECODE_WAYS_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Debug.h"
/*
Leetcode: Decode Ways
http://www.geeksforgeeks.org/count-possible-decodings-given-digit-sequence/
A message containing letters from A-Z is being encoded to numbers using
the following mapping:

'A' -> 1
'B' -> 2
...
'Z' -> 26

Given an encoded message containing digits, determine the total number of
ways to decode it.

For example,
Given encoded message "12", it could be decoded as "AB" (1 2) or "L" (12).

The number of ways decoding "12" is 2.

DP1D: O(n) time, O(n) space
DP: O(n) time, O(1) space
DP1D Recur: O(2^n) time, O(n) space
FindAllRecur: O(2^n) time O(n) space

Leetcode: Decode Ways II
A message containing letters from A-Z is being encoded to numbers using the following mapping way:
'A' -> 1
'B' -> 2
...
'Z' -> 26
Beyond that, now the encoded string can also contain the character '*', which can be treated as one of the numbers from 1 to 9.
Given the encoded message containing digits and the character '*', return the total number of ways to decode it.
Also, since the answer may be very large, you should return the output mod 10^9 + 7.
Example 1:
Input: "*"
Output: 9
Explanation: The encoded message can be decoded to the string: "A", "B", "C", "D", "E", "F", "G", "H", "I".
Example 2:
Input: "1*"
Output: 9 + 9 = 18
*/

class DecodeWays
{
public:
	DecodeWays(){}
	~DecodeWays(){}

	int DP1D_Iterate(const std::string & s)
	{
		std::cout << "DecodeWays DP1D_Iterate for \"" << s << "\": ";
		int N = s.size();
		if (N == 0)
		{
			std::cout << 0 << std::endl;
			return 0;
		}
		std::vector<int> dp(N + 1, 0);
		dp[0] = 1;//this is the most tricky part
		//dp[i] is the total decode ways of s[0]~s[i-1]
		for (int i = 1; i <= N; ++i)
		{
			if (s[i - 1] < '0' || s[i - 1] > '9')
			{
				dp[i] = 0;
				std::cout << Debug::ToStr1D<int>()(dp) << std::endl;
				return 0;
			}

			//1. check valid 1 digit numbers
			if (s[i - 1] != '0')//s[i-1] can be '1'~'9'
				dp[i] = dp[i - 1];
			//2. check valid 2 digit numbers
			if (i - 2 >= 0)
				if (s[i - 2] == '1' || //s[i-1] can be '0'~'9'
					(s[i - 2] == '2' && s[i - 1] <= '6'))
					dp[i] += dp[i - 2];

			if (dp[i] == 0)
			{
				std::cout << Debug::ToStr1D<int>()(dp) << std::endl;
				return 0;
			}
		}

		std::cout << Debug::ToStr1D<int>()(dp) << std::endl;
		return dp[N];
	}

	int DP_Iterate(const std::string & s)
	{
		std::cout << "DecodeWays DP_Iterate for \"" << s << "\": ";
		int N = s.size();
		if (N == 0)
		{
			std::cout << 0 << std::endl;
			return 0;
		}
		int dp2 = 0;//total decode ways of s[0]~s[i-2]
		int dp1 = 1;//total decode ways of s[0]~s[i-1]
		int res = 0;
		
		for (int i = 1; i <= N; ++i)
		{
			res = 0;
			if (s[i - 1] < '0' || s[i - 1] > '9')
			{
				std::cout << 0 << std::endl;
				return 0;
			}
			//1. check valid 1 digit numbers
			if (s[i - 1] != '0')//s[i-1] can be '1'~'9'
				res = dp1;
			//2. check valid 2 digit numbers
			if (i - 2 >= 0)
				if (s[i - 2] == '1' || //s[i-1] can be '0'~'9'
					(s[i - 2] == '2' && s[i - 1] <= '6'))
					res += dp2;
			if (res == 0)
			{
				std::cout << 0 << std::endl;
				return 0;
			}
			dp2 = dp1;
			dp1 = res;
		}

		std::cout << res << std::endl;
		return res;
	}

	int DP1D_Recur(const std::string & s)
	{
		std::cout << "DecodeWays DP1D_Recur for \"" << s << "\": ";
		if (s.empty())
		{
			std::cout << 0 << std::endl;
			return 0;
		}
		int N = s.size();
		std::vector<int> memo(N + 1, -1);
		int res = this->recur(s, N, 0, memo);

		std::cout << res << std::endl;
		std::cout << Debug::ToStr1D<int>()(memo) << std::endl;
		return res;
	}
private:
	int recur(const std::string & s, int N, int i, std::vector<int> & memo)
	{
		if (memo[i] != -1)
			return memo[i];
		if (i == N)
			return memo[i] = 1;

		if (s[i] < '0' || s[i] > '9')
			return memo[i] = 0;

		int res = 0;
		if (s[i] != '0')//include only current digit
			res += this->recur(s, N, i + 1, memo);
		if (i + 1 < N)
			if (s[i] == '1' ||
				(s[i] == '2' && s[i + 1] <= '6'))//include both current and next digits
				res += this->recur(s, N, i + 2, memo);
		return memo[i] = res;
	}

public:
	std::vector<std::string> FindAllRecur(const std::string & s)
	{
		std::vector<std::string> res;
		std::string path;
		this->findAllRecur(s, 0, path, res);
		std::cout << "DecodeWays FindAllRecur for \"" << s << "\": " << Debug::ToStr1D<std::string>()(res) << std::endl;
		return res;
	}
private:
	void findAllRecur(const std::string & s, int i, std::string & path, std::vector<std::string> & res)
	{
		int N = s.size();
		if (i == N)
		{
			res.push_back(path);
			return;
		}

		if (s[i] != '0')//include only current digit
		{
			path += (s[i] - '0' + 'a' - 1);
			this->findAllRecur(s, i + 1, path, res);
			path.pop_back();
		}
		if (i + 1 < N)
			if (s[i] == '1' ||
				(s[i] == '2' && s[i + 1] <= '6'))//include both current and next digits
			{
				path += ((10 * (s[i] - '0') + s[i + 1] - '0') + 'a' - 1);
				this->findAllRecur(s, i + 2, path, res);
				path.pop_back();
			}
	}

	int DecodeWaysII(std::string s)
	{
		int N = s.size();
		if (N == 0 || s[0] == '0') return 0;
		std::vector<long> dp(N + 1, 0);
		dp[0] = 1;
		dp[1] = (s[0] == '*' ? 9 : 1);
		//dp[i] is the total decode ways of s[0]~s[i-1]

		for (int i = 2; i <= N; ++i)
		{
			//1. check valid 1 digit numbers
			if (s[i - 1] == '*')//s[i-1] is '*'
				dp[i] += 9 * dp[i - 1];
			else if (s[i - 1] != '0')//s[i-1] can be '1'~'9'
				dp[i] += dp[i - 1];

			//2. check valid 2 digit numbers
			if (s[i - 2] == '*')
			{
				if (s[i - 1] == '*')
					dp[i] += 15 * dp[i - 2];//**: 11,...,19,21,...,26
				else if (s[i - 1] <= '6')
					dp[i] += 2 * dp[i - 2];//*[0:6]: [1:2]+[0:6]
				else
					dp[i] += dp[i - 2];//*7,*8,*9,*0 are all invalid
			}
			else if (s[i - 2] == '1' || s[i - 2] == '2')
			{
				if (s[i - 1] == '*')
				{
					if (s[i - 2] == '1')
						dp[i] += 9 * dp[i - 2];//1*: 1+[1:9]
					else
						dp[i] += 6 * dp[i - 2];//2*: 2+[1:6]
				}
				else if (s[i - 2] == '1' || (s[i - 2] == '2' && s[i - 1] <= '6'))
					dp[i] += dp[i - 2];
			}

			dp[i] %= 1000000007;
		}

		return (int)dp[N];
	}
};
/*
DecodeWays DP1D_Iterate for "1261345723452912364512": 1, 1, 2, 3, 3, 6, 6, 6, 6, 6, 12, 12, 12, 12, 12, 12, 24, 36, 36, 36, 36, 36, 72
DecodeWays DP_Iterate for "1261345723452912364512": 72
DecodeWays DP1D_Recur for "1261345723452912364512": 72
72, 48, 24, 24, 12, 12, 12, 12, 12, 6, 6, 6, 6, 6, 6, 4, 2, 2, 2, 2, 2, 1, 1
DecodeWays FindAllRecur for "1123": aabc, aaw, alc, kbc, kw
*/
#endif