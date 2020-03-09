#ifndef EVAL_REVERSE_POLISH_NOTATION_H
#define EVAL_REVERSE_POLISH_NOTATION_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, StacksAndQueues: Evaluate RPN expressions
https://github.com/anson627/leetcode/blob/master/EvaluateReversePolishNotation/EvaluateReversePolishNotation.cpp
// Evaluate Reverse Polish Notation
//
// Evaluate the value of an arithmetic expression in Reverse Polish Notation.
//
// Valid operators are +, -, *, /. Each operand may be an integer or another
// expression.
//
// Some examples:
//  ["2", "1", "+", "3", "*"] -> ((2 + 1) * 3) -> 9
//  ["4", "13", "5", "/", "+"] -> (4 + (13 / 5)) -> 6
//
// Complexity:
// O(n) time, O(n) space

Use stack.
We can loop through each element in the given array. 
When it is a number, push it to the stack. 
When it is an operator, pop two numbers from the stack, do the calculation, and push back the result.

See also EvalPolishNotation.h
*/
class EvalReversePolishNotation
{
public:
	EvalReversePolishNotation(){}
	~EvalReversePolishNotation(){}

	int Evaluate(const std::vector<std::string> & tokens)
	{
		std::stack<long> numStk;//a stack that only stores numbers
		for (std::string str : tokens)
		{
			if (str == "+" || str == "-" || str == "*" || str == "/")//str is an operator: pop top 2 numbers from stack, do calculation, push back the result to stack
			{
				long right = numStk.top();
				numStk.pop();
				long left = numStk.top();
				numStk.pop();

				if (str == "+")
				{
					std::cout << left << "+" << right << std::endl;
					numStk.push(left + right);
				}
				else if (str == "-")
				{
					std::cout << left << "-" << right << std::endl;
					numStk.push(left - right);
				}
				else if (str == "*")
				{
					std::cout << left << "*" << right << std::endl;
					numStk.push(left*right);
				}
				else//str == "/"
				{
					std::cout << left << "/" << right << std::endl;
					numStk.push(left / right);
				}
			}
			else//str is a number: push the number to stack
				numStk.push(std::stol(str));
		}

		std::cout << Debug::ToStr1D<long>()(numStk) << std::endl;
		std::cout << "EvalReversePolishNotation for \"" << Debug::ToStr1D<std::string>()(tokens) << "\" is: " << numStk.top() << std::endl;
		return (int)numStk.top();
	}


};
/*
2+1
3*3
9
EvalReversePolishNotation for "2, 1, +, 3, *" is: 9
13/5
4+2
6
EvalReversePolishNotation for "4, 13, 5, /, +" is: 6
3+4
2*1
7+2
9
EvalReversePolishNotation for "3, 4, +, 2, 1, *, +" is: 9
1+1
2*-2
-4
EvalReversePolishNotation for "1, 1, +, -2, *" is: -4
4/6
0/2
0
EvalReversePolishNotation for "4, 6, /, 2, /" is: 0
*/
#endif