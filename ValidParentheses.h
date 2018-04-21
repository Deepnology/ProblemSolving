#ifndef VALID_PARENTHESES_H
#define VALID_PARENTHESES_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
/*
Elements of programming interview, StacksAndQueues: Test a string over "{,},(,),[,]" for well-formedness
https://github.com/anson627/leetcode/blob/master/ValidParentheses/ValidParentheses.cpp
http://discuss.leetcode.com/questions/201/valid-parentheses
// Given a string containing just the characters '(', ')', '{', '}', '[' and
// ']', determine if the input string is valid.
//
// The brackets must close in the correct order, "()" and "()[]{}" are all
// valid but "(]" and "([)]" are not.
see also LongestValidParentheses.h, RemoveInvalidParentheses.h

Leetcode: Valid Parenthesis String
Given a string containing only three types of characters: '(', ')' and '*',
write a function to check whether this string is valid. We define the validity of a string by these rules:
Any left parenthesis '(' must have a corresponding right parenthesis ')'.
Any right parenthesis ')' must have a corresponding left parenthesis '('.
Left parenthesis '(' must go before the corresponding right parenthesis ')'.
'*' could be treated as a single right parenthesis ')' or a single left parenthesis '(' or an empty string.
An empty string is also valid.
Example 1:
Input: "()"
Output: True
Example 2:
Input: "(*)"
Output: True
Example 3:
Input: "(*))"
Output: True
This can be done using DFS.
*/
class ValidParentheses
{
public:
	ValidParentheses(){}
	~ValidParentheses(){}

	bool IsValid(std::string s)
	{
		std::stack<char> stk;
		for (char c : s)
		{
			if (c == '(') stk.push(')');
			else if (c == '{') stk.push('}');
			else if (c == '[') stk.push(']');
			else if (stk.empty()) return false;
			else
			{
				if (stk.top() != c) return false;
				stk.pop();
			}
		}
		bool res = stk.empty();
		return res;
	}
	int FollowUp_FindMatchingPairIdx(std::string valid, int idx)//given a valid string and an idx, find idx's matching parenthesis
	{
		int N = valid.size();
		if (valid[idx] == '(' || valid[idx] == '{' || valid[idx] == '[')
		{
			//search to the right
			int count = 1;
			while (++idx < N)
			{
				if (valid[idx] == '(' || valid[idx] == '{' || valid[idx] == '[')
					++count;
				else
					--count;
				if (count == 0)
					return idx;
			}
		}
		else
		{
			//search to the left
			int count = -1;
			while (--idx >= 0)
			{
				if (valid[idx] == ')' || valid[idx] == '}' || valid[idx] == ']')
					--count;
				else
					++count;
				if (count == 0)
					return idx;
			}
		}
		return -1;
	}
	void Test(std::string s)
	{
		bool valid = IsValid(s);
		std::cout << "ValidParentheses IsValid for \"" << s << "\": " << valid << std::endl;
		if (valid)
		{
			int N = s.size();
			for (int i = 0; i < N; ++i)
			{
				int match = FollowUp_FindMatchingPairIdx(s, i);
				std::cout << "ValidParentheses FindMatchingPairIdx for \"" << s << "\", \"" << i << "\": " << match << std::endl;
			}
		}
	}

	bool Stack_CloseInCorrectOrder(const std::string & s)
	{
		std::cout << "ValidParentheses Stack_CloseInCorrectOrder for \"" << s << "\": ";
		std::stack<char> stk;
		for (char c : s)
		{
			if (c == '(' || c == '[' || c == '{')
				stk.push(c);
			else
			{
				if (stk.empty())
				{
					std::cout << false << std::endl;
					return false;
				}
				else if (c == ')' && stk.top() == '(')
					stk.pop();
				else if (c == ']' && stk.top() == '[')
					stk.pop();
				else if (c == '}' && stk.top() == '{')
					stk.pop();
				else
				{
					std::cout << false << std::endl;
					return false;
				}
			}
		}
		bool res = stk.empty();
		std::cout << res << std::endl;
		return res;
	}
	bool CloseInArbitraryOrder(const std::string & s)
	{
		std::cout << "ValidParentheses CloseInArbitraryOrder for \"" << s << "\": ";
		int count1 = 0;//'('
		int count2 = 0;//'['
		int count3 = 0;//'{'
		for (char c : s)
		{
			switch (c)
			{
			case '(':
				++count1;
				break;
			case '[':
				++count2;
				break;
			case '{':
				++count3;
				break;
			default://non-'(','[','{'
				{
					if (c == ')' && count1 > 0)
						--count1;
					else if (c == ']' && count2 > 0)
						--count2;
					else if (c == '}' && count3 > 0)
						--count3;
					else
					{
						std::cout << false << std::endl;
						return false;
					}
				}
				break;
			}
		}
		bool res = count1 == 0 && count2 == 0 && count3 == 0;
		std::cout << res << std::endl;
		return res;
	}





	bool CloseInCorrectOrder(const std::string & s)
	{
		std::cout << "ValidParentheses CloseInCorrectOrder for \"" << s << "\": ";
		long res = 0;
		int N = s.size();
		for (int i = 0; i < N; ++i)
		{
			char c = s[i];
			int a = 0;
			switch (c)
			{
			case '(':
				a = 1;
				break;
			case ')':
				a = -1;
				break;
			case '[':
				a = 2;
				break;
			case ']':
				a = -2;
				break;
			case '{':
				a = 3;
				break;
			case '}':
				a = -3;
				break;
			}
			if (a > 0)
				res = res * 10 + a;
			else if (a < 0)
			{
				if (res % 10 + a == 0)
					res = res / 10;
				else
				{
					std::cout << false << std::endl;
					return false;
				}
			}
		}
		std::cout << (res == 0 ? true : false) << std::endl;
		return res == 0 ? true : false;
	}
};
class ValidParenthesesWildcard
{
public:
	ValidParenthesesWildcard() {}

	bool OnePass(std::string s)
	{
		//'*', can be '(' or ')' or empty
		//so keep track of a range of balance
		int N = s.size();
		int balanceLow = 0;
		int balanceHigh = 0;
		for (int i = 0; i < N; ++i)
		{
			if (s[i] == '(')
			{
				++balanceLow;
				++balanceHigh;
			}
			else if (s[i] == ')')
			{
				if (balanceLow > 0) --balanceLow;//decrement balanceLow to cancel actual '('
				--balanceHigh;
			}
			else//'*', can be '(' or ')' or empty
			{
				if (balanceLow > 0) --balanceLow;//assume it is ')'
				++balanceHigh;//assume it is '('
			}

			if (balanceHigh < 0)//meet extra ')' in middle of string
				return false;
		}

		return balanceLow == 0;
	}

	bool TwoScans(std::string s)
	{
		int N = s.size();
		int balance = 0;
		int countX = 0;
		for (int i = 0; i < N; ++i)
		{
			if (s[i] == '(') ++balance;
			else if (s[i] == ')') --balance;
			else ++countX;
			if (balance < 0)
			{
				if (countX == 0) return false;
				//now cancel a '*' with a ')'
				--countX;
				++balance;
			}
		}
		balance = 0;
		countX = 0;
		for (int i = N-1; i >= 0; --i)
		{
			if (s[i] == ')') ++balance;
			else if (s[i] == '(') --balance;
			else ++countX;
			if (balance < 0)
			{
				if (countX == 0) return false;
				--countX;
				++balance;
			}
		}
		return true;
	}
};
/*
ValidParentheses IsValid for "({[)(}{])}": 0
ValidParentheses IsValid for "[{()}]": 1
ValidParentheses FindMatchingPairIdx for "[{()}]", "0": 5
ValidParentheses FindMatchingPairIdx for "[{()}]", "1": 4
ValidParentheses FindMatchingPairIdx for "[{()}]", "2": 3
ValidParentheses FindMatchingPairIdx for "[{()}]", "3": 2
ValidParentheses FindMatchingPairIdx for "[{()}]", "4": 1
ValidParentheses FindMatchingPairIdx for "[{()}]", "5": 0
ValidParentheses IsValid for "({[)(}{])}": 0
ValidParentheses IsValid for "[{{(())}}]{[[[]]]}": 1
ValidParentheses FindMatchingPairIdx for "[{{(())}}]{[[[]]]}", "0": 9
ValidParentheses FindMatchingPairIdx for "[{{(())}}]{[[[]]]}", "1": 8
ValidParentheses FindMatchingPairIdx for "[{{(())}}]{[[[]]]}", "2": 7
ValidParentheses FindMatchingPairIdx for "[{{(())}}]{[[[]]]}", "3": 6
ValidParentheses FindMatchingPairIdx for "[{{(())}}]{[[[]]]}", "4": 5
ValidParentheses FindMatchingPairIdx for "[{{(())}}]{[[[]]]}", "5": 4
ValidParentheses FindMatchingPairIdx for "[{{(())}}]{[[[]]]}", "6": 3
ValidParentheses FindMatchingPairIdx for "[{{(())}}]{[[[]]]}", "7": 2
ValidParentheses FindMatchingPairIdx for "[{{(())}}]{[[[]]]}", "8": 1
ValidParentheses FindMatchingPairIdx for "[{{(())}}]{[[[]]]}", "9": 0
ValidParentheses FindMatchingPairIdx for "[{{(())}}]{[[[]]]}", "10": 17
ValidParentheses FindMatchingPairIdx for "[{{(())}}]{[[[]]]}", "11": 16
ValidParentheses FindMatchingPairIdx for "[{{(())}}]{[[[]]]}", "12": 15
ValidParentheses FindMatchingPairIdx for "[{{(())}}]{[[[]]]}", "13": 14
ValidParentheses FindMatchingPairIdx for "[{{(())}}]{[[[]]]}", "14": 13
ValidParentheses FindMatchingPairIdx for "[{{(())}}]{[[[]]]}", "15": 12
ValidParentheses FindMatchingPairIdx for "[{{(())}}]{[[[]]]}", "16": 11
ValidParentheses FindMatchingPairIdx for "[{{(())}}]{[[[]]]}", "17": 10



ValidParentheses Stack_CloseInCorrectOrder for "({[)(}{])}": 0
ValidParentheses CloseInCorrectOrder for "({[)(}{])}": 0
ValidParentheses Stack_CloseInCorrectOrder for "[{()}]": 1
ValidParentheses CloseInCorrectOrder for "[{()}]": 1
ValidParentheses CloseInArbitraryOrder for "({[)(}{])}": 1
*/
#endif