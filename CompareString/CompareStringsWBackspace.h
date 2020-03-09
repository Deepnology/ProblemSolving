#ifndef _COMPARE_STRINGS_W_BACKSPACE_H
#define _COMPARE_STRINGS_W_BACKSPACE_H
#include "Debug.h"
/*
Leetcode: Backspace string compare
Given two strings S and T, return if they are equal when both are typed into empty text editors. # means a backspace character.
Example 1:
Input: S = "ab#c", T = "ad#c"
Output: true
Explanation: Both S and T become "ac".
Example 2:
Input: S = "ab##", T = "c#d#"
Output: true
Explanation: Both S and T become "".
Example 3:
Input: S = "a##c", T = "#a#c"
Output: true
Explanation: Both S and T become "c".
Example 4:
Input: S = "a#c", T = "b"
Output: false
Explanation: S becomes "c" while T becomes "b".
 */
class CompareStringsWBackspace
{
public:
    CompareStringsWBackspace(){}

    void Test(const std::string & S, const std::string & T)
    {
        bool res1 = InPlace(S, T);
        bool res2 = UseStack(S, T);
        std::cout << "CompareStringsWBackspace InPlace and UseStack for [" << S << "," << T << "]: " << res1 << ", " << res2 << std::endl;
    }

    bool InPlace(const std::string & S, const std::string & T)
    {
        int N = S.size();
        int M = T.size();
        int i = N-1;
        int j = M-1;
        int countS = 0;
        int countT = 0;
        while (i >= 0 || j >= 0)
        {
            while (i >= 0 && (S[i] == '#' || countS > 0))
            {
                if (S[i] == '#') ++countS;
                else --countS;
                --i;
            }
            while (j >= 0 && (T[j] == '#' || countT > 0))
            {
                if (T[j] == '#') ++countT;
                else --countT;
                --j;
            }
            if (i < 0 || j < 0)
                return i == j;
            if (S[i] != T[j])
                return false;
            --i; --j;
        }
        return i == j;
    }

    bool UseStack(const std::string & S, const std::string & T)
    {
        std::string s;
        std::string t;
        for (auto c : S)
            if (c == '#')
            {
                if (!s.empty())
                    s.pop_back();
            }
            else
                s.push_back(c);
        for (auto c : T)
            if (c == '#')
            {
                if (!t.empty())
                    t.pop_back();
            }
            else
                t.push_back(c);
        return s == t;
    }
};
/*
CompareStringsWBackspace InPlace and UseStack for [a##C,#a#C]: 1, 1
 */
#endif
