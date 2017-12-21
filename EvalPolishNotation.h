#ifndef EVAL_POLISH_NOTATION_H
#define EVAL_POLISH_NOTATION_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, StacksAndQueues: Evaluate RPN expressions, variant
http://stackoverflow.com/questions/3205723/how-to-evaluate-an-expression-in-prefix-notation
For example,
{ "/", "-", "*", "2", "5", "*", "1", "2", "-", "11", "9" } = (2*5 - 1*2) / (11-9) = 4
{ "-", "*", "/", "15", "-", "7", "+", "1", "1", "3", "+", "2", "+", "1", "1" } = (15 / (7-(1+1)) * 3) - (2+(1+1)) = 5

See also EvalReversePolishNotation.h
*/
class EvalPolishNotation
{
public:
	EvalPolishNotation(){}
	~EvalPolishNotation(){}

	int Evaluate(const std::vector<std::string> & tokens)
	{
		std::stack<std::string> stk;
		for (std::string str : tokens)
		{
			if (this->IsOperator(str))//str is an Operator
			{
				stk.push(str);
			}
			else//str is an Operand
			{
				//now we have a rightOperand, str
				//if stk.top() is an Operand, it will be a leftOperand, and the next stk.top() will be an Operator for the leftOperand and rightOperand
				//evaluate and save the result to the rightOperand
				//keep popping stk.top() as a leftOperand and the next stk.top() as an Operator, and evaluate with the rightOperand until stk.top() is not an Operand
				int rightOperand = std::stoi(str);
				while (!stk.empty() && !this->IsOperator(stk.top()))
				{
					int leftOperand = std::stoi(stk.top());
					stk.pop();

					//now stk.top() must be an operator
					if (stk.top() == "+")
					{
						std::cout << leftOperand << "+" << rightOperand << std::endl;
						rightOperand = leftOperand + rightOperand;
					}
					else if (stk.top() == "-")
					{
						std::cout << leftOperand << "-" << rightOperand << std::endl;
						rightOperand = leftOperand - rightOperand;
					}
					else if (stk.top() == "*")
					{
						std::cout << leftOperand << "*" << rightOperand << std::endl;
						rightOperand = leftOperand * rightOperand;
					}
					else
					{
						std::cout << leftOperand << "/" << rightOperand << std::endl;
						rightOperand = leftOperand / rightOperand;
					}
					stk.pop();
				}
				
				//now stk.top() is not an Operand
				//push the result rightOperand to stk
				stk.push(std::to_string(rightOperand));
				//std::cout << Debug::ToStr1D<std::string>()(stk) << std::endl;
			}
		}

		std::cout << Debug::ToStr1D<std::string>()(stk) << std::endl;
		std::cout << "EvalPolishNotation for \"" << Debug::ToStr1D<std::string>()(tokens) << "\": " << stk.top() << std::endl;
		return std::stoi(stk.top());
	}

private:
	bool IsOperator(const std::string & str)
	{
		if (str == "+" || str == "-" || str == "*" || str == "/")
			return true;
		return false;
	}
};
/*
2*5
1*2
10-2
11-9
8/2
4
EvalPolishNotation for "/, -, *, 2, 5, *, 1, 2, -, 11, 9": 4
1+1
7-2
15/5
3*3
1+1
2+2
9-4
5
EvalPolishNotation for "-, *, /, 15, -, 7, +, 1, 1, 3, +, 2, +, 1, 1": 5
*/
#endif