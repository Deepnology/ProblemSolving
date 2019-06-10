#ifndef _REMOVE_OUTERMOST_PAREN_OF_EACH_PRIMITIVE_H
#define _REMOVE_OUTERMOST_PAREN_OF_EACH_PRIMITIVE_H
#include "Debug.h"
/*
Leetcode: Remove Outermost Parentheses
A valid parentheses string is either empty (""), "(" + A + ")", or A + B, where A and B are valid parentheses strings, and + represents string concatenation.
For example, "", "()", "(())()", and "(()(()))" are all valid parentheses strings.
A valid parentheses string S is primitive if it is nonempty, and there does not exist a way to split it into S = A+B, with A and B nonempty valid parentheses strings.
Given a valid parentheses string S, consider its primitive decomposition: S = P_1 + P_2 + ... + P_k, where P_i are primitive valid parentheses strings.
Return S after removing the outermost parentheses of every primitive string in the primitive decomposition of S.
Example 1:
Input: "(()())(())"
Output: "()()()"
Explanation:
The input string is "(()())(())", with primitive decomposition "(()())" + "(())".
After removing outer parentheses of each part, this is "()()" + "()" = "()()()".
Example 2:
Input: "(()())(())(()(()))"
Output: "()()()()(())"
Explanation:
The input string is "(()())(())(()(()))", with primitive decomposition "(()())" + "(())" + "(()(()))".
After removing outer parentheses of each part, this is "()()" + "()" + "()(())" = "()()()()(())".
Example 3:
Input: "()()"
Output: ""
Explanation:
The input string is "()()", with primitive decomposition "()" + "()".
After removing outer parentheses of each part, this is "" + "" = "".
Note:
S.length <= 10000
S[i] is "(" or ")"
S is a valid parentheses string
 */
class RemoveOutermostParenOfEachPrimitive
{
public:
    RemoveOutermostParenOfEachPrimitive(){}

    std::string OneScan(std::string S)
    {
        int balance = 0;
        std::string res;
        for (auto c : S)
        {
            if (c == '(')
            {
                if (balance > 0) res.push_back(c);
                ++balance;
            }
            else
            {
                --balance;
                if (balance > 0) res.push_back(c);
            }
        }

        std::cout << "RemoveOutermostParenOfEachPrimitive for \"" << S << "\": " << res << std::endl;
        return res;
    }
};
/*
RemoveOutermostParenOfEachPrimitive for "(()())(())(()(()))": ()()()()(())
 */
#endif
