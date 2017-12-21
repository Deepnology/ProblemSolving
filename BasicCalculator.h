#ifndef BASIC_CALCULATOR_H
#define BASIC_CALCULATOR_H
#include <string>
#include <stack>
#include <vector>
#include <iostream>
#include "Debug.h"
#include "EvalReversePolishNotation.h"
/*
Leetcode: Basic Calculator
Implement a basic calculator to evaluate a simple expression string.
The expression string may contain open '(' and closing parentheses ')'
, the plus '+' or minus sign '-', non-negative integers and empty spaces ' '.
You may assume that the given expression is always valid.
Some examples:
"1 + 1" = 2
" 2-1 + 2 " = 3
"(1+(4+5+2)-3)+(6+8)" = 23

Leetcode: Basic Calculator II
Implement a basic calculator to evaluate a simple expression string.
The expression string contains only non-negative integers, +, -, *, and / operators.
The integer division should truncate toward zero.
You may assume that the given expression is always valid.
Some examples:
"3+2*2" = 7
" 3/2 " = 1
" 3+5 / 2 " = 5

BruteForce Algorithm for '+' and '-' only
Use a stack to keep track of num, op, num, op, num, ..., where the top of stk should always be a num before evaluating.
When seeing a ')', evaluate all numbers and operators after last '(', then push back to stack.

UseRPN
Convert expression to RPN (Shunting-yard algorithm)
https://en.wikipedia.org/wiki/Shunting-yard_algorithm
Use an opStk to keep track of operators
Use a queue to store the final RPN epxression
When seeing a number: push to the que
When seeing an operator: while the top operator's precedence on opStk is equal to or greater than the current operator, pop out the top operator and push to the que. then push the current operator to the opStk
('*' and '/': 3; '+' and '-': 2)
When seeing a '(': push to the opStk
When seeing a ')': while the top on opStk isn't '(', pop operators off the opStk onto the que. then pop '(' off the opStk but not onto the que.
Then evaluate the RPN queue
*/
class BasicCalculator
{
public:
	BasicCalculator(){}
	~BasicCalculator(){}

	int UseRPN(const std::string & s)
	{
		std::vector<std::string> rpn = this->toRPN(s);
		std::cout << "BasicCalculator RPN for \"" << s << "\": " << Debug::ToStr1D<std::string>()(rpn) << std::endl;
		int res = EvalReversePolishNotation().Evaluate(rpn);
		return res;
	}
private:
	std::vector<std::string> toRPN(const std::string & s)
	{
		std::stack<std::string> opStk;
		std::vector<std::string> que;
		std::string curNum;
		int N = s.size();
		for (int i = 0; i < N; ++i)
		{
			//2 cases for a "negative number": -1..... or ...(-1...)...
			if (s[i] >= '0' && s[i] <= '9' || curNum.empty() && (que.empty() || !opStk.empty() && opStk.top() == "(") && s[i] == '-')
			{
				curNum += s[i];
				if (i == N - 1)
				{
					que.push_back(curNum);
					curNum.clear();
				}
			}
			else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/')
			{
				if (!curNum.empty())
				{
					que.push_back(curNum);
					curNum.clear();
				}

				while (!opStk.empty() &&
					(opStk.top() == "*" || opStk.top() == "/" || (s[i] == '+' || s[i] == '-') && (opStk.top() == "+" || opStk.top() == "-") ))
				{
					que.push_back(opStk.top());
					opStk.pop();
				}
				opStk.push(std::string(1, s[i]));
			}
			else if (s[i] == '(')
			{
				if (!curNum.empty())
				{
					que.push_back(curNum);
					curNum.clear();
				}
				opStk.push(std::string(1, s[i]));
			}
			else if (s[i] == ')')
			{
				if (!curNum.empty())
				{
					que.push_back(curNum);
					curNum.clear();
				}

				while (opStk.top() != "(")
				{
					que.push_back(opStk.top());
					opStk.pop();
				}
				opStk.pop();
			}
			else//space
			{
				if (i == N - 1 && !curNum.empty())
				{
					que.push_back(curNum);
					curNum.clear();
				}
			}

			//std::cout << "opStk: " << Debug::ToStr1D<std::string>()(opStk) << std::endl;
			//std::cout << "que: " << Debug::ToStr1D<std::string>()(que) << std::endl;
		}

		while (!opStk.empty())
		{
			que.push_back(opStk.top());
			opStk.pop();
		}
		return que;
	}

public:
	int BruteForce_OnlyPlusMinus(std::string s)
	{
		std::stack<std::string> stk;
		std::string curNum;
		int N = s.size();
		for (int i = 0; i < N; ++i)
		{
			if (s[i] >= '0' && s[i] <= '9' || curNum.empty() && (stk.empty() || stk.top() == "(") && s[i] == '-')
			{
				curNum += s[i];
				if (i == N - 1)
				{
					stk.push(curNum);
					curNum.clear();
				}
			}
			else if (s[i] == '(' || s[i] == '+' || s[i] == '-')
			{
				if (!curNum.empty())
				{
					stk.push(curNum);
					curNum.clear();
				}
				stk.push(std::string(1, s[i]));//ctor: string(size_t n, char c)
			}
			else if (s[i] == ')')
			{
				if (!curNum.empty())
				{
					stk.push(curNum);
					curNum.clear();
				}
				int res = 0;
				while (stk.top() != "(")
				{
					int right = stoi(stk.top());
					stk.pop();
					std::string op = stk.top();
					if (op == "+" || op == "-")
					{
						stk.pop();
						int left = stoi(stk.top());
						stk.pop();
						if (!stk.empty() && stk.top() == "-")
						{
							left = 0 - left;
							stk.pop();
							stk.push(std::string("+"));
						}
						if (op == "+")
							res += (left + right);
						else if (op == "-")
							res += (left - right);
						stk.push(std::to_string(res));
						res = 0;
					}//op == '('
					else
						res += right;
				}
				stk.pop();
				stk.push(std::to_string(res));
			}
			else//space
			{
				if (i == N - 1 && !curNum.empty())
				{
					stk.push(curNum);
					curNum.clear();
				}
			}
		}
		//now stk contains num, op, num, op, num, ..., where the top of stk must be a num
		
		int res = 0;
		while (!stk.empty())
		{
			int right = stoi(stk.top());
			stk.pop();
			if (!stk.empty())
			{
				std::string op = stk.top();
				stk.pop();
				int left = stoi(stk.top());
				stk.pop();
				if (!stk.empty() && stk.top() == "-")
				{
					left = 0 - left;
					stk.pop();
					stk.push(std::string("+"));
				}
				if (op == "+")
					res += (left + right);
				else if (op == "-")
					res += (left - right);
				stk.push(std::to_string(res));
				res = 0;
			}
			else
				res += right;
		}

		std::cout << "BasicCalculator BruteForce OnlyPlusMinus for \"" << s << "\": " << res << std::endl;
		return res;
	}
};
/*
BasicCalculator RPN for "((2 + 1) * 3)": 2, 1, +, 3, *
2+1
3*3
9
EvalReversePolishNotation for "2, 1, +, 3, *" is: 9
BasicCalculator RPN for "(4 + (13 / 5))": 4, 13, 5, /, +
13/5
4+2
6
EvalReversePolishNotation for "4, 13, 5, /, +" is: 6
BasicCalculator RPN for "(7)-(0)+(4)": 7, 0, -, 4, +
7-0
7+4
11
EvalReversePolishNotation for "7, 0, -, 4, +" is: 11
BasicCalculator RPN for "3+2*2": 3, 2, 2, *, +
2*2
3+4
7
EvalReversePolishNotation for "3, 2, 2, *, +" is: 7
BasicCalculator RPN for "3/2 ": 3, 2, /
3/2
1
EvalReversePolishNotation for "3, 2, /" is: 1
BasicCalculator RPN for "3+5 / 2 ": 3, 5, 2, /, +
5/2
3+2
5
EvalReversePolishNotation for "3, 5, 2, /, +" is: 5
BasicCalculator BruteForce OnlyPlusMinus for "1 + 1": 2
BasicCalculator BruteForce OnlyPlusMinus for " 2-1 + 2 ": 3
BasicCalculator BruteForce OnlyPlusMinus for "(1+(4+5+2)-3)+(6+8)": 23
*/
#endif