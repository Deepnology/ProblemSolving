/*#FindSubstrSubseq*/
#ifndef _REPEATED_STRING_MATCH_H
#define _REPEATED_STRING_MATCH_H
#include "Debug.h"
/*
Leetcode: Repeated String Match
Given two strings A and B, find the minimum number of times A has to be repeated such that B is a substring of it.
If no such solution, return -1.
For example, with A = "abcd" and B = "cdabcdab".
Return 3, because by repeating A three times (“abcdabcdabcd”), B is a substring of it
 ; and B is not a substring of A repeated two times ("abcdabcd").
Note:
The length of A and B will be between 1 and 10000.
 */
class RepeatedStringMatch
{
public:
    RepeatedStringMatch(){}

    int BruteForce(const std::string & A, const std::string & B)
    {
        //find substring B in a circular form of A
        int res = -1;
        int N = A.size();
        int M = B.size();
        for (int i = 0; i < N; ++i)//match B starting from A[i] with repetition
        {
            int j = 0;
            while(A[(i+j)%N] == B[j])
                ++j;
            if (j == M)
            {
                res = (i+j)/N + ((i+j)%N != 0 ? 1:0);
                break;
            }
        }

        std::cout << "RepeatedStringMatch BruteForce for \"" << A << "\", \"" << B << "\": " << res << std::endl;
        return res;
    }
    int UseKMP(const std::string & A, const std::string & B)
    {
        std::vector<int> LPS = getLPS(B);
        int res = -1;
        int N = A.size();
        int M = B.size();
        int i = 0;
        int j = 0;
        for (; i < N; )//match B starting from A[i] with repetition
        {
            for (; j < M; )
            {
                if (A[(i+j)%N] == B[j])
                {
                    ++j;
                }
                else
                {
                    if (j != 0)
                    {
                        i = i+j;//skip matched chars in A !!!
                        j = LPS[j-1];
                    }
                    else
                        ++i;//advance i to start a new match at A[i+1]
                    break;
                }
            }
            if (j == M)
            {
                res = (i+j)/N + ((i+j)%N != 0 ? 1:0);
                break;
            }
        }
        std::cout << "RepeatedStringMatch UseKMP for \"" << A << "\", \"" << B << "\": " << res << std::endl;
        return res;
    }
private:
    std::vector<int> getLPS(const std::string & s)
    {
        int N = s.size();
        std::vector<int> LPS(N, 0);
        int i = 1;
        int j = 0;
        while (i < N)
        {
            if (s[i] == s[j]) LPS[i++] = ++j;
            else if (j != 0) j = LPS[j - 1];
            else ++i;
        }
        return LPS;
    }
};
/*
RepeatedStringMatch BruteForce for "abcd", "cdabcdab": 3
RepeatedStringMatch BruteForce for "abaabaa", "abaababaab": -1
RepeatedStringMatch UseKMP for "abcd", "cdabcdab": 3
RepeatedStringMatch UseKMP for "abaabaa", "abaababaab": -1
 */
#endif
