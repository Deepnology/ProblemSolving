#ifndef _SCORE_OF_PARENTHESES_H
#define _SCORE_OF_PARENTHESES_H
#include "Debug.h"
/*
Leetcode: Score of Parentheses
Given a balanced parentheses string S, compute the score of the string based on the following rule:
() has score 1
AB has score A + B, where A and B are balanced parentheses strings.
(A) has score 2 * A, where A is a balanced parentheses string.
Example 1:
Input: "()"
Output: 1
Example 2:
Input: "(())"
Output: 2
Example 3:
Input: "()()"
Output: 2
Example 4:
Input: "(()(()))"
Output: 6
 */
class ScoreOfParentheses
{
public:
    ScoreOfParentheses(){}
    int UseStack(std::string S)
    {
        std::stack<int> stk;
        int N = S.size();
        int res = 0;
        for (int i = 0; i < N; ++i)
        {
            if (S[i] == '(')
                stk.push(0);
            else
            {
                int cur = stk.top() == 0 ? 1 : stk.top() * 2;
                stk.pop();
                if (!stk.empty())
                {
                    int pre = stk.top();
                    stk.pop();
                    stk.push(pre+cur);
                }
                else
                    res += cur;
            }
        }
        std::cout << "ScoreOfParentheses UseStack for [" << S << "]: " << res << std::endl;
        return res;

    }
    int ConstSpace(std::string S)
    {
        int N = S.size();
        int count = 0;
        int res = 0;
        for (int i = 0; i < N; ++i)
        {
            if (S[i] == '(') ++count;
            else if (S[i] == ')') --count;
            if (S[i] == '(' && i+1 < N && S[i+1] == ')')
                res += pow(2, count-1);
        }
        std::cout << "ScoreOfParentheses ConstSpace for [" << S << "]: " << res << std::endl;
        return res;
    }
};
/*
ScoreOfParentheses UseStack for [(()(()))]: 6
ScoreOfParentheses ConstSpace for [(()(()))]: 6
 */
#endif
