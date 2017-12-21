#ifndef ABC_COMBINATION_1B_2CS_H
#define ABC_COMBINATION_1B_2CS_H
#include "Debug.h"
/*
https://careercup.com/question?id=5717453712654336
Given an integer n, count number of char combinations from 'a', 'b', and 'c' that forms a string in length n.
The string can have at most 1 'b' and up to 2 consecutive 'c's.

n=3, return 19
aaa,aab,aac,aba,abc,aca,acb,baa,bac,bca,caa,cab,cac,cba,cbc,acc,bcc,cca,ccb
invalid: abb,bab,bba,bbb,bbc,bcb,cbb,ccc

Leetcode: Student Attendance Record II
Given a positive integer n, return the number of all possible attendance records with length n, which will be regarded as rewardable.
The answer may be very large, return it after mod 10^9 + 7.
A student attendance record is a string that only contains the following three characters:
'A' : Absent.
'L' : Late.
'P' : Present.
A record is regarded as rewardable if it doesn't contain more than one 'A' (absent) or more than two continuous 'L' (late).
Example 1:
Input: n = 2
Output: 8
Explanation:
There are 8 records with length 2 will be regarded as rewardable:
"PP" , "AP", "PA", "LP", "PL", "AL", "LA", "LL"
Only "AA" won't be regarded as rewardable owing to more than one absent times.
*/
class abcCombination_1b_2cs
{
public:
	abcCombination_1b_2cs() {}
	~abcCombination_1b_2cs() {}

	//Leetcode: Student Attendance Record I
	bool CheckRecord(std::string s)
	{
		int numA = 0;
		int numLL = 0;
		int N = s.size();
		for (int i = 0; i < N; ++i)
		{
			if (s[i] == 'P')
			{
				numLL = 0;
			}
			else if (s[i] == 'A')
			{
				numLL = 0;
				++numA;
				if (numA > 1) return false;
			}
			else
			{
				++numLL;
				if (numLL > 2) return false;
			}
		}
		return true;
	}

	//Leetcode: Student Attendance Record II
	int DFS(int n)//Time Limit Exceeded
	{
		long long res = 0;
		recur(n, 0, 0, 0, res);
		std::cout << "abcCombination_1b_2cs DFS for \"" << n << "\": " << res << std::endl;
		return res % 1000000007;
	}
private:
	void recur(int n, int begin, int countA, int countL, long long & totalCount)
	{
		if (begin == n)
		{
			++totalCount;
			return;
		}
		recur(n, begin + 1, countA, 0, totalCount);//add Present
		if (countA == 0)
		{
			recur(n, begin + 1, 1, 0, totalCount);//add Abscent
		}
		if (countL <= 1)
		{
			recur(n, begin + 1, countA, countL + 1, totalCount);//add Late
		}
	}
public:
	int DP3D(int n)//Memory Limit Exceeded
	{
		std::vector<std::vector<std::vector<int>>> dp(n + 1, std::vector<std::vector<int>>(2, std::vector<int>(3, 0)));
		dp[0][0] = { 1,1,1 };
		dp[0][1] = { 1,1,1 };
		//dp[i][0][0] = dp[i-1][0][2] (target is 0A and 0L: can only add 1P from a situation of 0A and 2L)
		//dp[i][0][1] = dp[i-1][0][2] + dp[i-1][0][0] (target is 0A and 1L: can add 1P from a situation of 0A and 2L, OR can add 1L from a situation of 0A and 0L)
		//dp[i][0][2] = dp[i-1][0][2] + dp[i-1][0][1] (target is 0A and 2L: can add 1P from a situation of 0A and 2L, OR can add 1L from a situation of 0A and 1L)

		//dp[i][1][0] = dp[i-1][1][2] + dp[i-1][0][2] (target is 1A and 0L: can add 1P from a situation of 1A and 2L, OR can add 1A from a situation of 0A and 2L)
		//dp[i][1][1] = dp[i-1][1][2] + dp[i-1][0][2] + dp[i-1][1][0] (target is 1A and 1L: can add 1P from a situation of 1A and 2L, OR can add 1A from a situation of 0A and 2L, OR can add 1L from a situation of 1A and 0L)
		//dp[i][1][2] = dp[i-1][1][2] + dp[i-1][0][2] + dp[i-1][1][1] (target is 1A and 2L: can add 1P from a situation of 1A and 2L, OR can add 1A from a situation of 0A and 2L, OR can add 1L from a situation of 1A and 1L)

		for (int i = 1; i <= n; ++i)
		{
			for (int j = 0; j < 2; ++j)
			{
				for (int k = 0; k < 3; ++k)
				{
					long long numChoice = dp[i - 1][j][2];//can add 1P
					if (j > 0) numChoice += dp[i - 1][j - 1][2];//can add 1A
					if (k > 0) numChoice += dp[i - 1][j][k - 1];//can add 1L
					dp[i][j][k] = numChoice % 1000000007;
				}
			}
		}
		std::cout << "abcCombination_1b_2cs DP3D for \"" << n << "\": " << dp[n][1][2] << std::endl;
		return dp[n][1][2];
	}
	int DP2D(int n)//Accepted
	{
		std::vector<std::vector<int>> dp(2, std::vector<int>(3, 0));
		dp[0] = { 1,1,1 };
		dp[1] = { 1,1,1 };
		for (int i = 1; i <= n; ++i)
		{
			std::vector<std::vector<int>> nxt(2, std::vector<int>(3, 0));
			for (int j = 0; j < 2; ++j)
			{
				for (int k = 0; k < 3; ++k)
				{
					long long numChoice = dp[j][2];//can add 1P
					if (j > 0) numChoice += dp[j - 1][2];//can add 1A
					if (k > 0) numChoice += dp[j][k - 1];//can add 1L
					nxt[j][k] = numChoice % 1000000007;
				}
			}
			dp = nxt;
		}
		std::cout << "abcCombination_1b_2cs DP2D for \"" << n << "\": " << dp[1][2] << std::endl;
		return dp[1][2];
	}









	int DP(int n)//incorrect for n==4 !!!
	{
		if (n == 1)//a, b, c
			return 3;
		if (n == 2)//aa, ab, ac, ba, bc, ca, cb, cc
			return 8;

		int totalPrev = 8;
		int totalPrev1b = 4;//total prev count with 1b
		int totalPrevEnd1c = 2;//total prev count with ending c
		int totalPrevEnd2c = 1;//total prev count with ending cc

		for (int i = 3; i <= n; ++i)
		{
			int totalCur = totalPrev * 3 - totalPrev1b - totalPrevEnd2c;//general case (cur char can be a,b,c) exclude the cases that already contain 1 b (bc cur char can be b) and exclude the cases that already contain ending 2cs (bc cur char can be c)

			int totalCur2c = totalPrevEnd1c;//can choose only c to append to totalPrevEnd1c
			totalPrevEnd1c = totalPrev - totalPrevEnd1c - totalPrevEnd2c;//must exclude ending 1c and ending 2cs to append a c at end
			totalPrevEnd2c = totalCur2c;
			totalPrev1b = totalPrev;
			totalPrev = totalCur;
		}
		std::cout << "abcCombination_1b_2cs DP for \"" << n << "\": " << totalPrev << std::endl;
		return totalPrev;
	}
};
/*
abcCombination_1b_2cs DFS for "1": 3
abcCombination_1b_2cs DFS for "2": 8
abcCombination_1b_2cs DFS for "3": 19
abcCombination_1b_2cs DFS for "4": 43
abcCombination_1b_2cs DFS for "5": 94
abcCombination_1b_2cs DP3D for "1": 3
abcCombination_1b_2cs DP3D for "2": 8
abcCombination_1b_2cs DP3D for "3": 19
abcCombination_1b_2cs DP3D for "4": 43
abcCombination_1b_2cs DP3D for "5": 94
abcCombination_1b_2cs DP3D for "6": 200
abcCombination_1b_2cs DP3D for "7": 418
abcCombination_1b_2cs DP3D for "8": 861
abcCombination_1b_2cs DP2D for "1": 3
abcCombination_1b_2cs DP2D for "2": 8
abcCombination_1b_2cs DP2D for "3": 19
abcCombination_1b_2cs DP2D for "4": 43
abcCombination_1b_2cs DP2D for "5": 94
abcCombination_1b_2cs DP2D for "6": 200
abcCombination_1b_2cs DP2D for "7": 418
abcCombination_1b_2cs DP2D for "8": 861
*/
#endif
