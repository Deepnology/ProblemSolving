#ifndef PARSE_NESTED_TERNARY_EXPRESSION_H
#define PARSE_NESTED_TERNARY_EXPRESSION_H
#include "Debug.h"
/*
Leetcode: Ternary Expression Parser
Given a string representing arbitrarily nested ternary expressions, calculate the result of the expression.
You can always assume that the given expression is valid and only consists of digits 0-9, ?, :, T and F (T and F represent True and False respectively).
Note:
The length of the given string is <= 10000.
Each number will contain only one digit.
The conditional expressions group right-to-left (as usual in most languages).
The condition will always be either T or F. That is, the condition will never be a digit.
The result of the expression will always evaluate to either a digit 0-9, T or F.

Example 1:
Input: "T?2:3"
Output: "2"
Explanation: If true, then result is 2; otherwise result is 3.

Example 2:
Input: "F?1:T?4:5"
Output: "4"
Explanation: The conditional expressions group right-to-left. Using parenthesis, it is read/evaluated as:
"(F ? 1 : (T ? 4 : 5))"                   "(F ? 1 : (T ? 4 : 5))"
-> "(F ? 1 : 4)"                 or       -> "(T ? 4 : 5)"
-> "4"                                    -> "4"

Example 3:
Input: "T?T?F:5:3"
Output: "F"
Explanation: The conditional expressions group right-to-left. Using parenthesis, it is read/evaluated as:
"(T ? (T ? F : 5) : 3)"                   "(T ? (T ? F : 5) : 3)"
-> "(T ? F : 3)"                 or       -> "(T ? F : 5)"
-> "F"                                    -> "F"
*/
class ParseNestedTernaryExpression
{
public:
	ParseNestedTernaryExpression() {}

	std::string Recur(std::string expression)
	{
		int i = 0;
		std::string res = recur(expression, i);
		std::cout << "ParseNestedTernaryExpression Recur for \"" << expression << "\": " << res << std::endl;
		return res;
	}
private:
	std::string recur(const std::string & expr, int & i)
	{
		int N = expr.size();
		std::string res;
		bool isTrue = true;
		while (i < N)
		{
			if (expr[i] == ':')
			{
				++i;
				return res;
			}
			else if (expr[i] == '?')
			{
				std::string left = recur(expr, ++i);
				std::string right = recur(expr, i);
				if (isTrue)//postorder
					res = left;
				else
					res = right;
				return res;
			}
			else if (i + 1 < N && expr[i + 1] == '?')//T or F must be followed by ?
			{
				if (expr[i] == 'T')
					isTrue = true;
				else if (expr[i] == 'F')
					isTrue = false;
				++i;
			}
			else
			{
				res += expr[i++];
			}
		}
		return res;
	}
};
/*
ParseNestedTernaryExpression Recur for "T?2:3": 2
ParseNestedTernaryExpression Recur for "F?1:T?4:5": 4
ParseNestedTernaryExpression Recur for "T?T?F:5:3": F
*/
#endif
