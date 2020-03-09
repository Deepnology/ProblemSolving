#ifndef NEAT_PRINT_WORD_WRAP_2_H
#define NEAT_PRINT_WORD_WRAP_2_H
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "Debug.h"
/*
http://www.geeksforgeeks.org/dynamic-programming-set-18-word-wrap/
cost of line = (number of extra spaces in the line)^3
total cost = sum of costs for all lines

Consider this string with line width equal to 15:
"Geeks for Geeks presents word wrap problem"
The optimized arrangement of the string:
Geeks for Geeks
presents word
wrap problem

The total extra spaces in line 1, line 2, and line 3 are 0, 2, and 3, respectively.
The total cost is 0 + 2*2*2 + 3*3*3 = 35

DP2D: O(n^2) time, O(n^2) space
*/
class NeatPrintWordWrap2
{
public:
	NeatPrintWordWrap2(){}
	~NeatPrintWordWrap2(){}

	void MinCost_DP2D(const std::vector<std::string> & strs, int lineWidth)
	{
		int N = strs.size();
		std::vector<std::vector<int> > extras(N + 1, std::vector<int>(N + 1));
		//extras[i][j]: number of extra spaces if strs[i]~strs[j] were put in a single line

		std::vector<std::vector<int> > cost(N + 1, std::vector<int>(N + 1));
		//cost[i][j]: cost of a line which has words strs[i]~strs[j]

		std::vector<int> dp(N + 1);
		//dp[i]: total cost of optimal arrangement of words strs[i]~strs[j]

		for (int i = 1; i <= N; ++i)
		{
			extras[i][i] = lineWidth - strs[i - 1].size();
			for (int j = i + 1; j <= N; ++j)
				extras[i][j] = extras[i][j - 1] - strs[j - 1].size() - 1;
		}


		for (int i = 1; i <= N; ++i)
		{
			for (int j = i; j <= N; ++j)
			{
				if (extras[i][j] < 0)
					cost[i][j] = INT_MAX;
				else if (j == N && extras[i][j] >= 0)
					cost[i][j] = 0;
				else
					cost[i][j] = extras[i][j] * extras[i][j];
			}
		}

		dp[0] = 0;
		for (int j = 1; j <= N; ++j)
		{
			dp[j] = INT_MAX;
			for (int i = 1; i <= j; ++i)
			{
				if (dp[i - 1] != INT_MAX && cost[i][j] != INT_MAX && (dp[i - 1] + cost[i][j] < dp[j]))
				{
					dp[j] = dp[i - 1] + cost[i][j];

				}
			}
		}

		Debug::Print2D<int>()(extras, false);
		Debug::Print2D<int>()(cost, false);
		std::cout << Debug::ToStr1D<int>()(dp) << std::endl;
	}
};
#endif