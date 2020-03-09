#ifndef _FIND_TGT_WORD_GIVEN_MATCH_COUNT_COMP_H
#define _FIND_TGT_WORD_GIVEN_MATCH_COUNT_COMP_H
#include "Debug.h"
/*
Leetcode: Guess the Word
This problem is an interactive problem new to the LeetCode platform.
We are given a word list of unique words, each word is 6 letters long, and one word in this list is chosen as secret.
You may call master.guess(word) to guess a word.
The guessed word should have type string and must be from the original list with 6 lowercase letters.
This function returns an integer type, representing the number of exact matches (value and position) of your guess to the secret word.
Also, if your guess is not in the given wordlist, it will return -1 instead.
For each test case, you have 10 guesses to guess the word.
At the end of any number of calls, if you have made 10 or less calls to master.guess and at least one of these guesses was the secret, you pass the testcase.
Besides the example test case below, there will be 5 additional test cases, each with 100 words in the word list.
The letters of each word in those testcases were chosen independently at random from 'a' to 'z', such that every word in the given word lists is unique.
Example 1:
Input: secret = "acckzz", wordlist = ["acckzz","ccbazz","eiowzz","abcczz"]
Explanation:
master.guess("aaaaaa") returns -1, because "aaaaaa" is not in wordlist.
master.guess("acckzz") returns 6, because "acckzz" is secret and has all 6 matches.
master.guess("ccbazz") returns 3, because "ccbazz" has 3 matches.
master.guess("eiowzz") returns 2, because "eiowzz" has 2 matches.
master.guess("abcczz") returns 4, because "abcczz" has 4 matches.
We made 5 calls to master.guess and one of them was the secret, so we pass the test case.
Note:  Any solutions that attempt to circumvent the judge will result in disqualification.
 */
class FindTgtWordGivenMatchCountComp
{
public:
    FindTgtWordGivenMatchCountComp(){}

    struct Master
    {
        int guess(const std::string & a)
        {
            std::string b = "acckzz";//tgt word
            int res = 0;
            int N = a.size();
            for (int i = 0; i < N; ++i)
                if (a[i] == b[i])
                    ++res;
            std::cout << "Guess " << a << " to [acckzz]: " << res << std::endl;
            return res;
        }
    };

    void Solve(std::vector<std::string> && wordlist, Master & master)
    {
        while (!wordlist.empty())
        {
            //select a res word to guess
            //and eliminate all words that have different matchCount from res if res is wrong
            //in order to eliminate as many words as possible, select a word that has min maxFreqOfMatchCounts to all other words
            //maxFreqOfMatchCounts means how the word is close to ALL other words
            //min of maxFreqOfMatchCounts means the worst case
            std::string res;
            int minMaxFreq = INT_MAX;//min of maxFrequencies
            for (auto & s1 : wordlist)
            {
                std::vector<int> matchCount(7,0);
                for (auto & s2 : wordlist)
                {
                    int numMatch = match(s1, s2);
                    ++matchCount[numMatch];
                }
                //max frequency of match counts for s1 to all other words
                int maxFreq = *std::max_element(matchCount.begin(), matchCount.end());
                if (maxFreq < minMaxFreq)
                {
                    minMaxFreq = maxFreq;
                    res = s1;
                }
            }

            int matchCount = master.guess(res);
            if (matchCount == 6) return;
            for (auto itr = wordlist.begin(); itr != wordlist.end();)
            {
                if (match(res, *itr) != matchCount)
                    itr = wordlist.erase(itr);
                else
                    ++itr;
            }
        }

    }

    int match(const std::string & a, const std::string & b)
    {
        int res = 0;
        int N = a.size();
        for (int i = 0; i < N; ++i)
            if (a[i] == b[i])
                ++res;
        return res;
    }
};
/*
Guess acckzz to [acckzz]: 6
 */
#endif
