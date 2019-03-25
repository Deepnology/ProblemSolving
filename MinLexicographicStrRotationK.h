#ifndef _MIN_LEXICOGRAPHIC_STR_ROTATION_K_H
#define _MIN_LEXICOGRAPHIC_STR_ROTATION_K_H
#include "Debug.h"
/*
Leetcode: Orderly Queue
A string S of lowercase letters is given.  Then, we may make any number of moves.
In each move, we choose one of the first K letters (starting from the left), remove it, and place it at the end of the string.
Return the lexicographically smallest string we could have after any number of moves.
Example 1:
Input: S = "cba", K = 1
Output: "acb"
Explanation:
In the first move, we move the 1st character ("c") to the end, obtaining the string "bac".
In the second move, we move the 1st character ("b") to the end, obtaining the final result "acb".
Example 2:
Input: S = "baaca", K = 3
Output: "aaabc"
Explanation:
In the first move, we move the 1st character ("b") to the end, obtaining the string "aacab".
In the second move, we move the 3rd character ("c") to the end, obtaining the final result "aaabc".
 */
class MinLexicographicStrRotationK
{
public:
    MinLexicographicStrRotationK(){}
    ~MinLexicographicStrRotationK(){}

    std::string OrderlyQueue(std::string S, int K)
    {
        std::string res = GenericMinLexStrRotation(S, K);
        std::cout << "MinLexicographicStrRotationK for \"" << S << "\", K=" << K << ": " << res << std::endl;
        return res;
    }

    std::string GenericMinLexStrRotation(std::string S, int K)
    {
        if (K == 1)//min lex string rotation
        {
            /*
            std::string res(S);
            int N = S.size();
            for (int i = 1; i < N; ++i) //O(N^2) time
                res = std::min(res, S.substr(i)+S.substr(0,i));
            return res;
            */
            std::string res(S);
            int N = S.size();
            char minC = 'z';
            for (auto & c : S)
                minC = std::min(minC, c);
            for (int i = 1; i < N;) //worst case is still O(N^2) time
            {
                if (S[i] == minC)//only compare a string starting w/ minC
                {
                    res = std::min(res, S.substr(i)+S.substr(0,i));
                    while (i < N && S[i] == minC)//skip same minC
                        ++i;
                }
                else
                    ++i;
            }
            return res;
        }
        else
        {
            std::sort(S.begin(), S.end());
            return S;
        }
    }
};
/*
MinLexicographicStrRotationK for "cba", K=1: acb
MinLexicographicStrRotationK for "baaca", K=3: aaabc
 */
#endif
