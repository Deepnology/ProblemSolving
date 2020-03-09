#ifndef PARENTHESIZE_ARITHMETIC_EXPR_H
#define PARENTHESIZE_ARITHMETIC_EXPR_H
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include "Debug.h"
/*
Leetcode: Different Ways to Add Parentheses
Given a string of numbers and operators
, return all possible results from computing all the different possible ways 
to group numbers and operators.
The valid operators are +, - and *.
*/
class ParenthesizeArithmeticExpr
{
public:
	ParenthesizeArithmeticExpr(){}
	~ParenthesizeArithmeticExpr(){}

	std::vector<int> EnumerateAll(std::string s)
	{
		std::vector<int> operand = this->getOperand(s);
		std::vector<int> optr = this->getOptr(s);
		std::cout << Debug::ToStr1D<int>()(operand) << std::endl;
		std::cout << Debug::ToStr1D<int>()(optr) << std::endl;

		int N = operand.size();
		std::vector<int> res = this->recur(operand, optr, 0, N - 1);
		
		std::cout << "ParenthesizeArithmeticExpr EnumerateAll for \"" << s << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
private:
	std::vector<int> recur(const std::vector<int> & operand, const std::vector<int> & optr, int left, int right)
	{
		if (left == right)
			return{ operand[left] };
		if (right - left == 1)
		{
			int r = this->eval(operand[left], operand[right], optr[left]);
			return{ r };
		}

		std::vector<int> res;
		for (int mid = left; mid < right; ++mid)
		{
			std::vector<int> resLeft = recur(operand, optr, left, mid);
			std::vector<int> resRight = recur(operand, optr, mid + 1, right);
			for (const int & l : resLeft)
			{
				for (const int & r : resRight)
				{
					res.push_back(this->eval(l, r, optr[mid]));
				}
			}
		}
		return res;
	}
	int eval(int leftOperand, int rightOperand, int sign)
	{
		switch (sign)
		{
		case 0:
			return leftOperand + rightOperand;
		case 1:
			return leftOperand - rightOperand;
		case 2:
			return leftOperand * rightOperand;
		default:
			return 0;
		}
	}
	std::vector<int> getOperand(const std::string & s)
	{
		int N = s.size();
		std::vector<int> res;
		int num = 0;
		for (int i = 0; i < N; ++i)
		{
			if (s[i] >= '0' && s[i] <= '9')
				num = num * 10 + (s[i] - '0');
			else
			{
				res.push_back(num);
				num = 0;
			}
		}
		res.push_back(num);
		return res;
	}
	std::vector<int> getOptr(const std::string & s)
	{
		int N = s.size();
		std::vector<int> res;
		for (int i = 0; i < N; ++i)
		{
			if (s[i] == '+')
				res.push_back(0);
			else if (s[i] == '-')
				res.push_back(1);
			else if (s[i] == '*')
				res.push_back(2);
		}
		return res;
	}
};
/*
1, 2, 3
0, 0
ParenthesizeArithmeticExpr EnumerateAll for "1+2+3": 6, 6
2, 1, 1
1, 1
ParenthesizeArithmeticExpr EnumerateAll for "2-1-1": 2, 0
2, 3, 4, 5
2, 1, 2
ParenthesizeArithmeticExpr EnumerateAll for "2*3-4*5": -34, -10, -14, -10, 10
*/
#endif