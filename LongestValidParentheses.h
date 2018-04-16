#ifndef LONGEST_VALID_PARENTHESES_H
#define LONGEST_VALID_PARENTHESES_H
#include <string>
#include <iostream>
#include <sstream>
#include <stack>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, StacksAndQueues: Compute the longest substring with matching parens
Leetcode: Longest Valid Parentheses
Given a string containing just the characters '(' and ')', find the length of the longest valid (well-formed) parentheses substring.
For "(()", the longest valid parentheses substring is "()", which has length = 2.
Another example is ")()())", where the longest valid parentheses substring is "()()", which has length = 4.
Complexity:
Stack based: O(n) time, O(n) space
Two Scans: O(n) time, O(1) space
See also ValidParentheses.h, RemoveInvalidParentheses.h
*/
class LongestValidParentheses
{
public:
	LongestValidParentheses(){}
	~LongestValidParentheses(){}

	int Stack(const std::string & s)
	{
		std::stack<int> leftPrenIdxStk;//stores only '(' indices
		int maxCount = 0;
		int preInvalidRightPrenIdx = -1;
		int N = s.size();
		for (int i = 0; i < N; ++i)
		{
			if (s[i] == '(')
			{
				leftPrenIdxStk.push(i);
			}
			else//')'
			{
				if (leftPrenIdxStk.empty())
					preInvalidRightPrenIdx = i;
				else
				{
					leftPrenIdxStk.pop();
					//now leftPrenIdxStk.top() is the prev '(' that hasn't met its corresponding ')'
					maxCount = std::max(maxCount, i - (leftPrenIdxStk.empty() ? preInvalidRightPrenIdx : leftPrenIdxStk.top()));
				}
			}
		}
		std::cout << "LongestValidParentheses Stack for \"" << s << "\": " << maxCount << std::endl;
		return maxCount;
	}

	int InPlace_TwoScans(const std::string & s)
	{
		int N = s.size();
		int leftToRight = this->Iterate(s, '(', 0, N, 1);//use '('
		int rightToLeft = this->Iterate(s, ')', N - 1, -1, -1);//use ')'
		int res = std::max(leftToRight, rightToLeft);
		std::cout << "LongestValidParentheses InPlace_TwoScans for \"" << s << "\": max of (" << leftToRight << "," << rightToLeft << ")" << std::endl;
		return res;
	}
private:
	int Iterate(const std::string & s, char c, int start, int end, int step)
	{
		int maxLen = 0;
		int balance = 0;//the remaining count of '(' or ')' after "pair cancellation"
		int curMaxLen = 0;
		for (int i = start; i != end; i += step)
		{
			++curMaxLen;
			if (s[i] == c)
			{
				++balance;
			}
			else
			{
				--balance;//pair cancellation
			}
			if (balance == 0)//balance might never be equal to 0 in one direction, but it must have a chance to sum to 0 in another direction (that's why to test both directions)
				maxLen = std::max(maxLen, curMaxLen);
			else if (balance < 0)
			{
				balance = 0;//reset
				curMaxLen = 0;//reset
			}
		}
		return maxLen;
	}

public:
	std::string TwoScans_FindLongestValidSubstr(const std::string & s)
	{
		int N = s.size();
		int balance = 0;
		std::string LtoR;
		std::string resLtoR;
		for (int i = 0; i < N; ++i)
		{
			if (s[i] == '(')
			{
				++balance;
				LtoR.push_back(s[i]);
			}
			else if (s[i] == ')')
			{
				--balance;
				LtoR.push_back(s[i]);
			}
			if (balance == 0)
			{
				if (LtoR.size() > resLtoR.size())
					resLtoR = LtoR;
			}
			else if (balance < 0)
			{
				balance = 0;
				LtoR.clear();
			}
		}

		//iterate from right to left
		balance = 0;
		std::string RtoL;
		std::string resRtoL;
		for (int i = N-1; i >= 0; --i)
		{
			if (s[i] == ')')
			{
				++balance;
				RtoL.push_back(s[i]);
			}
			else if (s[i] == '(')
			{
				--balance;
				RtoL.push_back(s[i]);
			}
			if (balance == 0)
			{
				if (RtoL.size() > resRtoL.size())
					resRtoL = RtoL;
			}
			else if (balance < 0)
			{
				balance = 0;
				RtoL.clear();
			}
		}
		std::reverse(resRtoL.begin(), resRtoL.end());

		std::cout << resLtoR << "," << resRtoL << std::endl;
		std::string res = resLtoR.size() > resRtoL.size() ? resLtoR : resRtoL;
		std::cout << "LongestValidParentheses TwoScans_FindLongestValidSubstr for \"" << s << "\": " << res << std::endl;
		return res;
	}
	std::string TwoScans_FindLongestValidSubseq(const std::string & s)
	{
		int N = s.size();
		int balance = 0;
		std::string LtoR;
		for (int i = 0; i < N; ++i)
		{
			if (s[i] == '(')
			{
				++balance;
			}
			else if (s[i] == ')')
			{
				--balance;
			}
			if (balance >= 0)
			{
				LtoR.push_back(s[i]);
			}
			else
			{
				++balance;
			}
		}

		std::cout << LtoR << std::endl;
		std::string res;
		N = LtoR.size();
		//iterate LtoR from right to left
		balance = 0;
		for (int i = N-1; i >= 0; --i)
		{
			if (LtoR[i] == ')')
			{
				++balance;
			}
			else if (LtoR[i] == '(')
			{
				--balance;
			}
			if (balance >= 0)
			{
				res.push_back(LtoR[i]);
			}
			else
			{
				++balance;
			}
		}
		std::reverse(res.begin(), res.end());

		std::cout << "LongestValidParentheses TwoScans_FindLongestValidSubseq for \"" << s << "\": " << res << std::endl;
		return res;
	}
    std::string Stack_FindLongestValidSubseq(const std::string & s)
    {
        int N = s.size();
        std::stack<int> prenIdxStk;
        for (int i = 0; i < N; ++i)
        {
            if (s[i] == '(')
            {
                prenIdxStk.push(i);
            }
            else if (s[i] == ')')
            {
                if (prenIdxStk.empty() || s[prenIdxStk.top()] != '(')
                    prenIdxStk.push(i);
                else
                    prenIdxStk.pop();
            }
        }
        std::string res(s);
        while (!prenIdxStk.empty())//erase chars from right to left
        {
            int topIdx = prenIdxStk.top(); prenIdxStk.pop();
            res.erase(topIdx, 1);
        }

        std::cout << "LongestValidParentheses Stack_FindLongestValidSubseq for \"" << s << "\": " << res << std::endl;
        return res;
    }
};
/*
LongestValidParentheses Stack for ")(((())()()(((": 8
LongestValidParentheses InPlace_TwoScans for ")(((())()()(((": max of (0,8)
,(())()()
LongestValidParentheses TwoScans_FindLongestValidSubstr for ")(((())()()(((": (())()()
(())(),(())()
LongestValidParentheses TwoScans_FindLongestValidSubstr for ")(())()((": (())()
()(),()
LongestValidParentheses TwoScans_FindLongestValidSubstr for "()())()": ()()
,
LongestValidParentheses TwoScans_FindLongestValidSubstr for ")(":
()(),()()
LongestValidParentheses TwoScans_FindLongestValidSubstr for "()())())(()()": ()()
()(),()
LongestValidParentheses TwoScans_FindLongestValidSubstr for "()())())(()(()": ()()
(())(),(())()
LongestValidParentheses TwoScans_FindLongestValidSubstr for "()())(())()(()(()": (())()
(()(())),(()(()))
LongestValidParentheses TwoScans_FindLongestValidSubstr for "()()))(()))(()(()))(()": (()(()))
(((())()()(((
LongestValidParentheses TwoScans_FindLongestValidSubseq for ")(((())()()(((": (())()()
(())()((
LongestValidParentheses TwoScans_FindLongestValidSubseq for ")(())()((": (())()
()()()
LongestValidParentheses TwoScans_FindLongestValidSubseq for "()())()": ()()()
(
LongestValidParentheses TwoScans_FindLongestValidSubseq for ")(":
()()()(()()
LongestValidParentheses TwoScans_FindLongestValidSubseq for "()())())(()()": ()()()()()
()()()(()(()
LongestValidParentheses TwoScans_FindLongestValidSubseq for "()())())(()(()": ()()()()()
()()(())()(()(()
LongestValidParentheses TwoScans_FindLongestValidSubseq for "()())(())()(()(()": ()()(())()()()
()()(())(()(()))(()
LongestValidParentheses TwoScans_FindLongestValidSubseq for "()()))(()))(()(()))(()": ()()(())(()(()))()
LongestValidParentheses Stack_FindLongestValidSubseq for ")(((())()()(((": (())()()
LongestValidParentheses Stack_FindLongestValidSubseq for ")(())()((": (())()
LongestValidParentheses Stack_FindLongestValidSubseq for "()())()": ()()()
LongestValidParentheses Stack_FindLongestValidSubseq for ")(":
LongestValidParentheses Stack_FindLongestValidSubseq for "()())())(()()": ()()()()()
LongestValidParentheses Stack_FindLongestValidSubseq for "()())())(()(()": ()()()()()
LongestValidParentheses Stack_FindLongestValidSubseq for "()())(())()(()(()": ()()(())()()()
LongestValidParentheses Stack_FindLongestValidSubseq for "()()))(()))(()(()))(()": ()()(())(()(()))()
*/
#endif