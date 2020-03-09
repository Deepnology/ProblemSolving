#ifndef _REPEAT_REVERSE_SUBSTRS_IN_PARENTHESES_H
#define _REPEAT_REVERSE_SUBSTRS_IN_PARENTHESES_H
/*
Leetcode: Reverse Substrings Between Each Pair of Parentheses
You are given a string s that consists of lower case English letters and brackets.
Reverse the strings in each pair of matching parentheses, starting from the innermost one.
Your result should not contain any brackets.
Example 1:
Input: s = "(abcd)"
Output: "dcba"
Example 2:
Input: s = "(u(love)i)"
Output: "iloveu"
Explanation: The substring "love" is reversed first, then the whole string is reversed.
Example 3:
Input: s = "(ed(et(oc))el)"
Output: "leetcode"
Explanation: First, we reverse the substring "oc", then "etco", and finally, the whole string.
Example 4:
Input: s = "a(bcdefghijkl(mno)p)q"
Output: "apmnolkjihgfedcbq"
 */
class RepeatReverseSubstrsInParentheses
{
public:
    std::string UseStack(std::string s)
    {
        std::vector<int> stk;
        std::string res;
        int N = s.size();
        for (int i = 0; i < N; ++i)
        {
            if (s[i] == '(')
                stk.push_back(i);
            else if (s[i] == ')')
            {
                int begin = stk.back(); stk.pop_back();
                std::reverse(s.begin()+begin+1, s.begin()+i);
            }
        }
        for (int i = 0; i < N; ++i)
            if (s[i] != '(' && s[i] != ')')
                res.push_back(s[i]);

        std::cout << "RepeatReverseSubstrsInParenthesese UseStack for " << s << ": " << res << std::endl;
        return res;
    }
};
/*
RepeatReverseSubstrsInParenthesese UseStack for (i)love(u): iloveu
 */
#endif
