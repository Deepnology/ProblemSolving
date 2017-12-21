#ifndef PARENTHESIZE_BOOL_EXPR_H
#define PARENTHESIZE_BOOL_EXPR_H
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "Debug.h"
/*
http://www.geeksforgeeks.org/dynamic-programming-set-37-boolean-parenthesization-problem/
Cracking the coding interview: Recursion and DP
Given a boolean expression which contains symbols(T, F) and operators(&, |, ^), count the number of ways we can parenthesize the expression to yield a result of True or False.
For example:
count("1|1&0^0", true): 3
count("1|1&0^0", false): 2

What we should know before hand:
count(exp1 | exp2, true) =	count(exp1, true) * count(exp2, true) +
							count(exp1, true) * count(exp2, false) +
							count(exp1, false) * count(exp2, true)

count(exp1 & exp2, true) =	count(exp1, true) * count(exp2, true)

count(exp1 ^ exp2, true) =	count(exp1, true) * count(exp2, false) +
							count(exp1, false) * count(exp2, true)

count(exp1 | exp2, false) =	count(exp1, false) * count(exp2, false)

count(exp1 & exp2, false) =	count(exp1, false) * count(exp2, false) +
							count(exp1, true) * count(exp2, false) +
							count(exp1, false) * count(exp2, true)

count(exp1 ^ exp2, false) =	count(exp1, true) * count(exp2, true) +
							count(exp1, false) * count(exp2, false)

See also SynthesizeExpression.h
*/
class ParenthesizeBoolExpr
{
public:
	ParenthesizeBoolExpr(){}
	~ParenthesizeBoolExpr(){}

public:
	int CountRecur(const std::string & exp, bool result)
	{
		int res = this->countRecur(exp, result, 0, exp.size() - 1);
		std::cout << "ParenthesizeBoolExpr CountRecur for evaluating \"" << exp << "\" as \"" << result << "\": " << res << std::endl;
		return res;
	}
private:
	int countRecur(const std::string & exp, bool result, int start, int end)//both start and end must be pointing to OPERANDs
	{
		if (start == end)
		{
			if (exp[start] == '1' && result)
				return 1;
			else if (exp[start] == '0' && !result)
				return 1;
			else
				return 0;
		}
		
		int count = 0;
		if (result)//evaluated true
		{
			for (int opIdx = start + 1; opIdx < end; opIdx += 2)//opIdx: operator index
			{
				char op = exp[opIdx];
				if (op == '&')
				{
					count += this->countRecur(exp, true, start, opIdx - 1) * this->countRecur(exp, true, opIdx + 1, end);//1&1
				}
				else if (op == '|')
				{
					count += this->countRecur(exp, true, start, opIdx - 1) * this->countRecur(exp, true, opIdx + 1, end);//1|1
					count += this->countRecur(exp, true, start, opIdx - 1) * this->countRecur(exp, false, opIdx + 1, end);//1|0
					count += this->countRecur(exp, false, start, opIdx - 1) * this->countRecur(exp, true, opIdx + 1, end);//0|1
				}
				else if (op == '^')
				{
					count += this->countRecur(exp, true, start, opIdx - 1) * this->countRecur(exp, false, opIdx + 1, end);//1^0
					count += this->countRecur(exp, false, start, opIdx - 1) * this->countRecur(exp, true, opIdx + 1, end);//0^1
				}
			}
		}
		else//evaluated false
		{
			for (int opIdx = start + 1; opIdx < end; opIdx += 2)
			{
				char op = exp[opIdx];
				if (op == '&')
				{
					count += this->countRecur(exp, false, start, opIdx - 1) * this->countRecur(exp, false, opIdx + 1, end);//0&0
					count += this->countRecur(exp, true, start, opIdx - 1) * this->countRecur(exp, false, opIdx + 1, end);//1&0
					count += this->countRecur(exp, false, start, opIdx - 1) * this->countRecur(exp, true, opIdx + 1, end);//0&1
				}
				else if (op == '|')
				{
					count += this->countRecur(exp, false, start, opIdx - 1) * this->countRecur(exp, false, opIdx + 1, end);//0|0
				}
				else if (op == '^')
				{
					count += this->countRecur(exp, true, start, opIdx - 1) * this->countRecur(exp, true, opIdx + 1, end);//1^1
					count += this->countRecur(exp, false, start, opIdx - 1) * this->countRecur(exp, false, opIdx + 1, end);//0^0
				}
			}
		}
		return count;
	}

public:
	int Count_DP2D_Recur(const std::string & exp, bool result)
	{
		int N = exp.size();
		std::vector<std::vector<std::pair<int, int>>> dp2d(N, std::vector<std::pair<int, int> >(N, std::make_pair(-1, -1)));
		int res = this->count_DP2D_Recur(exp, result, 0, exp.size() - 1, dp2d);
		Debug::Print2D<int>()(dp2d, false);
		std::cout << "ParenthesizeBoolExpr Count_DP2D_Recur for evaluating \"" << exp << "\" as \"" << result << "\": " << res << std::endl;
		return res;
	}
private:
	int count_DP2D_Recur(const std::string & exp, bool result, int start, int end, std::vector<std::vector<std::pair<int, int>>> & dp2d)//both start and end must be pointing to OPERANDs
	{
		if (result && dp2d[start][end].first != -1)
			return dp2d[start][end].first;
		else if (!result && dp2d[start][end].second != -1)
			return dp2d[start][end].second;

		if (start == end)
		{
			if (exp[start] == '1' && result)
				return dp2d[start][end].first = 1;
			else if (exp[start] == '0' && !result)
				return dp2d[start][end].second = 1;
			else
				return 0;
		}

		int count = 0;
		if (result)//evaluated true
		{
			for (int opIdx = start + 1; opIdx < end; opIdx += 2)
			{
				char op = exp[opIdx];
				if (op == '&')
				{
					count += this->count_DP2D_Recur(exp, true, start, opIdx - 1, dp2d) * this->count_DP2D_Recur(exp, true, opIdx + 1, end, dp2d);
				}
				else if (op == '|')
				{
					count += this->count_DP2D_Recur(exp, true, start, opIdx - 1, dp2d) * this->count_DP2D_Recur(exp, true, opIdx + 1, end, dp2d);
					count += this->count_DP2D_Recur(exp, true, start, opIdx - 1, dp2d) * this->count_DP2D_Recur(exp, false, opIdx + 1, end, dp2d);
					count += this->count_DP2D_Recur(exp, false, start, opIdx - 1, dp2d) * this->count_DP2D_Recur(exp, true, opIdx + 1, end, dp2d);
				}
				else if (op == '^')
				{
					count += this->count_DP2D_Recur(exp, true, start, opIdx - 1, dp2d) * this->count_DP2D_Recur(exp, false, opIdx + 1, end, dp2d);
					count += this->count_DP2D_Recur(exp, false, start, opIdx - 1, dp2d) * this->count_DP2D_Recur(exp, true, opIdx + 1, end, dp2d);
				}
			}
		}
		else//evaluated false
		{
			for (int opIdx = start + 1; opIdx < end; opIdx += 2)
			{
				char op = exp[opIdx];
				if (op == '&')
				{
					count += this->count_DP2D_Recur(exp, false, start, opIdx - 1, dp2d) * this->count_DP2D_Recur(exp, false, opIdx + 1, end, dp2d);
					count += this->count_DP2D_Recur(exp, true, start, opIdx - 1, dp2d) * this->count_DP2D_Recur(exp, false, opIdx + 1, end, dp2d);
					count += this->count_DP2D_Recur(exp, false, start, opIdx - 1, dp2d) * this->count_DP2D_Recur(exp, true, opIdx + 1, end, dp2d);
				}
				else if (op == '|')
				{
					count += this->count_DP2D_Recur(exp, false, start, opIdx - 1, dp2d) * this->count_DP2D_Recur(exp, false, opIdx + 1, end, dp2d);
				}
				else if (op == '^')
				{
					count += this->count_DP2D_Recur(exp, true, start, opIdx - 1, dp2d) * this->count_DP2D_Recur(exp, true, opIdx + 1, end, dp2d);
					count += this->count_DP2D_Recur(exp, false, start, opIdx - 1, dp2d) * this->count_DP2D_Recur(exp, false, opIdx + 1, end, dp2d);
				}
			}
		}
		if (result)
			dp2d[start][end].first = count;
		else
			dp2d[start][end].second = count;
		return count;
	}

public:
	int Count_DP2D_Iterate(const std::string & exp, bool result)
	{
		int N = exp.size();
		std::vector<std::vector<std::pair<int, int>>> dp2d(N, std::vector<std::pair<int, int> >(N, std::make_pair(-1, -1)));
		for (int i = 0; i < N; i += 2)
		{
			dp2d[i][i].first = exp[i] == 1 ? 1 : 0;
			dp2d[i][i].second = exp[i] == 0 ? 1 : 0;
		}

		//refer to geeksforgeeks
		//for (int len = 3; len <= N; len += 2)
		//{
		//	for (int start = 0, end = len - 1; end < N; start += 2, end += 2)
		//	{
		//		dp2d[start][end].first = dp2d[start][end].second = 0;
		//		//for (int i = )
		//	}
		//}

		return result ? dp2d[0][N - 1].first : dp2d[0][N - 1].second;
	}
};
/*
ParenthesizeBoolExpr CountRecur for evaluating "1|1&0^0" as "1": 3
[rY][cX]
Row#0	= [1,-1], [-1,-1], [1,0], [-1,-1], [1,1], [-1,-1], [3,-1]
Row#1	= [-1,-1], [-1,-1], [-1,-1], [-1,-1], [-1,-1], [-1,-1], [-1,-1]
Row#2	= [-1,-1], [-1,-1], [1,-1], [-1,-1], [0,1], [-1,-1], [0,2]
Row#3	= [-1,-1], [-1,-1], [-1,-1], [-1,-1], [-1,-1], [-1,-1], [-1,-1]
Row#4	= [-1,-1], [-1,-1], [-1,-1], [-1,-1], [-1,1], [-1,-1], [0,1]
Row#5	= [-1,-1], [-1,-1], [-1,-1], [-1,-1], [-1,-1], [-1,-1], [-1,-1]
Row#6	= [-1,-1], [-1,-1], [-1,-1], [-1,-1], [-1,-1], [-1,-1], [-1,1]

ParenthesizeBoolExpr Count_DP2D_Recur for evaluating "1|1&0^0" as "1": 3
[rY][cX]
Row#0	= [1,-1], [-1,-1], [1,0], [-1,-1], [1,1], [-1,-1], [-1,2]
Row#1	= [-1,-1], [-1,-1], [-1,-1], [-1,-1], [-1,-1], [-1,-1], [-1,-1]
Row#2	= [-1,-1], [-1,-1], [1,-1], [-1,-1], [0,1], [-1,-1], [-1,2]
Row#3	= [-1,-1], [-1,-1], [-1,-1], [-1,-1], [-1,-1], [-1,-1], [-1,-1]
Row#4	= [-1,-1], [-1,-1], [-1,-1], [-1,-1], [-1,1], [-1,-1], [0,1]
Row#5	= [-1,-1], [-1,-1], [-1,-1], [-1,-1], [-1,-1], [-1,-1], [-1,-1]
Row#6	= [-1,-1], [-1,-1], [-1,-1], [-1,-1], [-1,-1], [-1,-1], [-1,1]

ParenthesizeBoolExpr Count_DP2D_Recur for evaluating "1|1&0^0" as "0": 2
*/
#endif