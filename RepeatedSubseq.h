/*HashTable*/
#ifndef REPEATED_SUB_SEQ_H
#define REPEATED_SUB_SEQ_H
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include "Debug.h"
/*
Google
http://www.careercup.com/question?id=5931067269709824
Given a string.
Find if there is any sub-sequence that repeats itself.

In the sense, it should be checked for every pair of characters in the string that is repeated.
This would require O(n^2) time and O(26*26) space, where n is the length of the string.

Or, we can just check every pair of characters of the alphabet to see if there are 2 of the same pairs existing in the string.
This would require O(n) time to record the positions of all characters in the string, and also O(26*26) time to check every pair of characters in the alphabet.
Therefore, O(n) time in total, O(n) space.
*/
class RepeatedSubseq
{
public:
	RepeatedSubseq(){}
	~RepeatedSubseq(){}

	bool CheckAllPairsInAlphabet(const std::string & s)
	{
		int N = s.size();
		std::vector<std::vector<int> > dp(26, std::vector<int>());//dp[i]: all occurrence indices of char i-'a'

		/*1. record the positions of each character in the string*/
		for (int i = 0; i < N; ++i)
		{
			dp[s[i] - 'a'].push_back(i);
		}
		/*2. enumerate all pairs of characters in the alphabet*/
		std::vector<std::pair<char, char> > res;
		for (char firstChar = 'a'; firstChar <= 'z'; ++firstChar)
		{
			for (char secondChar = 'a'; secondChar <= 'z'; ++secondChar)
			{
				if (firstChar == secondChar)
				{
					if (dp[firstChar - 'a'].size() >= 4)//a char occurs at least 4 times: found at least 2 pairs of equal chars
					{
						res.push_back(std::make_pair(firstChar, secondChar));
					}
				}
				else
				{
					if (dp[firstChar - 'a'].size() >= 2 && dp[secondChar - 'a'].size() >= 2 &&//firstChar occurs at least twice and secondChar occurs at least twice
						dp[secondChar - 'a'][dp[secondChar - 'a'].size() - 1] > dp[firstChar - 'a'][1] &&//secondChar last occurrence index > firstChar second occurrence index
						dp[secondChar - 'a'][dp[secondChar - 'a'].size() - 2] > dp[firstChar - 'a'][0]//secondChar prior to last occurrence index > firstChar first occurrence index
						)
					{
						res.push_back(std::make_pair(firstChar, secondChar));
					}
				}
			}
		}
		Debug::Print2D<int>()(dp);
		std::cout << "RepeatedSubseq CheckAllPairsInAlphabet for \"" << s << "\": " << Debug::ToStr1D<char>()(res) << std::endl;
		return res.size() > 0;
	}

	
};
/*
[cX][rY]
Row#0	= 2, 7,  ,  ,  ,  ,  ,  ,  ,  ,  ,  , 0, 1, 3, 4, 5, 6, 8, 9, 10, 12, 13, 15, 16, 17
Row#1	= 11, 14,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,

RepeatedSubseq CheckAllPairsInAlphabet for "mnaopqrbstuavwbxyz": [a,b]
[cX][rY]
Row#0	= 2, 11,  ,  ,  ,  ,  ,  ,  ,  ,  ,  , 0, 1, 3, 4, 5, 6, 8, 9, 10, 12, 13, 15, 16, 17
Row#1	= 7, 14,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,

RepeatedSubseq CheckAllPairsInAlphabet for "mnaopqrastubvwbxyz": [a,b]
[cX][rY]
Row#0	= 2,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  , 0, 1, 3, 4, 5, 6, 8, 9, 10, 12, 13, 15, 16, 17
Row#1	= 7,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,
Row#2	= 11,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,
Row#3	= 14,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,

RepeatedSubseq CheckAllPairsInAlphabet for "mnaopqrastuavwaxyz": [a,a]
[cX][rY]
Row#0	= 3, 15, 1, 17,  ,  ,  ,  ,  ,  ,  ,  , 0, 2, 4, 5, 7, 9, 12, 13, 14, 16, 18, 20, 22, 24
Row#1	= 6, 19, 8, 21,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,
Row#2	= 10, 25, 11, 23,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,

RepeatedSubseq CheckAllPairsInAlphabet for "mcnaopaqcracstubvdwbxdydzb": [a,b], [a,c], [a,d], [b,d], [c,a], [c,b], [c,d], [d,b]
*/
#endif