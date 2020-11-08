#ifndef _VERIFY_EQUALITY_EQUATIONS_H
#define _VERIFY_EQUALITY_EQUATIONS_H
#include "Debug.h"
/*
Leetcode: Satisfiability of Equality Equations
Given an array equations of strings that represent relationships between variables, each string equations[i] has length 4 and takes one of two different forms: "a==b" or "a!=b".  Here, a and b are lowercase letters (not necessarily different) that represent one-letter variable names.
Return true if and only if it is possible to assign integers to variable names so as to satisfy all the given equations.
Example 1:
Input: ["a==b","b!=a"]
Output: false
Explanation: If we assign say, a = 1 and b = 1, then the first equation is satisfied, but not the second.  There is no way to assign the variables to satisfy both equations.
Example 2:
Input: ["b==a","a==b"]
Output: true
Explanation: We could assign a = 1 and b = 1 to satisfy both equations.
Example 3:
Input: ["a==b","b==c","a==c"]
Output: true
Example 4:
Input: ["a==b","b!=c","c==a"]
Output: false
Example 5:
Input: ["c==c","b==d","x!=z"]
Output: true
 */
class VerifyEqualityEquations
{
public:
    bool Verify(std::vector<std::string> & equations)
    {
        std::vector<int> chdToP;
        for (int i = 0; i < 26; ++i)
            chdToP.push_back(i);
        for (auto & e : equations)
        {
            if (e[1]=='=')
            {
                int root1 = Find(chdToP, e[0]-'a');
                int root2 = Find(chdToP, e[3]-'a');
                if (root1 != root2)
                    chdToP[root2] = root1;
            }
        }
        for (auto & e : equations)
        {
            if (e[1]=='!')
            {
                int root1 = Find(chdToP, e[0]-'a');
                int root2 = Find(chdToP, e[3]-'a');
                if (root1 == root2) return false;
            }
        }
        return true;
    }
    int Find(std::vector<int> & chdToP, int cur)
    {
        while (cur != chdToP[cur])
        {
            chdToP[cur] = chdToP[chdToP[cur]];
            cur = chdToP[cur];
        }
        return cur;
    }
};
#endif
