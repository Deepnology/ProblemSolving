#ifndef _DECODE_NESTED_REPEATED_STR_AT_INDEX_H
#define _DECODE_NESTED_REPEATED_STR_AT_INDEX_H
#include "Debug.h"
/*
Leetcode: Decoded String At Index
An encoded string S is given.  To find and write the decoded string to a tape, the encoded string is read one character at a time and the following steps are taken:
If the character read is a letter, that letter is written onto the tape.
If the character read is a digit (say d), the entire current tape is repeatedly written d-1 more times in total.
Now for some encoded string S, and an index K, find and return the K-th letter (1 indexed) in the decoded string.
Example 1:
Input: S = "leet2code3", K = 10
Output: "o"
Explanation:
The decoded string is "leetleetcodeleetleetcodeleetleetcode".
The 10th letter in the string is "o".
Example 2:
Input: S = "ha22", K = 5
Output: "h"
Explanation:
The decoded string is "hahahaha".  The 5th letter is "h".
Example 3:
Input: S = "a2345678999999999999999", K = 1
Output: "a"
Explanation:
The decoded string is "a" repeated 8301530446056247680 times.  The 1st letter is "a".
 */
class DecodeNestedRepeatedStrAtIndex
{
public:
    //O(N) time
    std::string Recur(std::string S, int K) //K is 1-based index
    {
        std::string res = recur(S, K-1);//K-1: change to 0-based index
        std::cout << "DecodeNestedRepeatedStrAtIndex for [" << S << "] at " << K << ": " << res << std::endl;
        return res;
    }
    std::string recur(std::string S, int k)//k is 0-based index
    {
        int N = S.size();
        long long curLen = 0;
        for (int i = 0; i < N; ++i)
        {
            if (!isdigit(S[i]))//char
            {
                if (curLen == k) return S.substr(i, 1);
                ++curLen;
            }
            else//digit
            {
                if (curLen * (S[i]-'0') >= k+1) //cur string covers target index k
                    return recur(S.substr(0, i), k%curLen);//2nd iterate cur string
                curLen *= (S[i]-'0');
            }
        }
        return "";
    }
};
/*
DecodeNestedRepeatedStrAtIndex for [leet2code3] at 10: o
 */
#endif
