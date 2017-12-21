#ifndef WORD_BREAK_H
#define WORD_BREAK_H
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <sstream>
#include "Debug.h"
/*
Elements of programming interview, DynamicProgramming: The bedbathandbeyond.com problem, CanBreak_FindOne_DP1D
http://www.careercup.com/question?id=15496741
Cracking the coding interview: Medium
http://www.geeksforgeeks.org/dynamic-programming-set-32-word-break-problem/

https://github.com/anson627/leetcode/blob/master/WordBreak/WordBreak.cpp
// Given a string s and a dictionary of words dict, determine if s can be 
// segmented into a space-separated sequence of one or more dictionary words.
//
// For example, given
// s = "leetcode",
// dict = ["leet", "code"].
//
// Return true because "leetcode" can be segmented as "leet code".
//
// Complexity:
// O(n^2) time, O(n) space

https://github.com/anson627/leetcode/blob/master/WordBreakII/WordBreakII.cpp
// Given a string s and a dictionary of words dict, add spaces in s to 
// construct a sentence where each word is a valid dictionary word.
//
// Return all such possible sentences.
//
// For example, given
// s = "catsanddog",
// dict = ["cat", "cats", "and", "sand", "dog"].
//
// A solution is ["cats and dog", "cat sand dog"].
//
// Complexity:
// DP + Recursion + Memoization O(n^3) time, O(n^3) space
//
// See also PalindromePartitioning.h
*/
class WordBreak
{
public:
	WordBreak(){}
	~WordBreak(){}
	//1. CanBreak
	bool CanBreak_Recur(const std::string & s, const std::unordered_set<std::string> & dict)
	{
		bool res = this->canBreak_recur(s, dict);
		std::cout << "WordBreak CanBreak_Recur for \"" << s << "\" from \"" << Debug::ToStr1D<std::string>()(dict) << "\": " << res << std::endl;
		return res;
	}
private:
	bool canBreak_recur(const std::string & curWord, const std::unordered_set<std::string> & dict)
	{
		int N = curWord.size();
		if (N == 0)
			return true;

		for (int leftLen = 1; leftLen <= N; ++leftLen)
		{
			if (dict.count(curWord.substr(0, leftLen)) && this->canBreak_recur(curWord.substr(leftLen, N - leftLen), dict))
				return true;
		}
		return false;
	}
public:
	bool CanBreak_DP1D(const std::string & s, const std::unordered_set<std::string> & dict)
	{
		int N = s.size();
		std::vector<int> dp(N + 1, 0);
		/*
		dp[curLen]==1 means s[0:curLen-1] can be segmented into a sequence of dict words
		*/

		/*base case init: when s is empty, it can be segmented into a sequence of dict words*/
		dp[0] = 1;
		for (int curLen = 1; curLen <= N; ++curLen)
		{
			for (int leftLen = 0; leftLen < curLen; ++leftLen)
			{
				/*
				if s[0:leftLen-1] can be segmented into a sequence of dict words 
				&& if s[leftLen:curLen-1] can be found in dict
				*/
				if (dp[leftLen] && dict.count(s.substr(leftLen, curLen - leftLen)))
				{
					/*now s[0:curLen-1] can be segmented into a sequence of dict words*/
					dp[curLen] = 1;
					break;
				}
			}
		}

		std::cout << Debug::ToStr1D<int>()(dp) << std::endl;
		std::cout << "WordBreak CanBreak_DP1D for \"" << s << "\" from \"" << Debug::ToStr1D<std::string>()(dict) << "\": " << dp[N] << std::endl;
		return (dp[N] == 1 ? true : false);
	}
	bool CanBreak_FindOne_DP1D(const std::string & s, const std::unordered_set<std::string> & dict)
	{
		int N = s.size();
		std::vector<int> dp(N + 1, 0);
		/*
		dp[curLen]>0 means s[0:curLen-1] can be segmented into a sequence of dict words
		dp[curLen] means the length of last string in the decomposition of s[leftLen, curLen-1]
		*/

		/*base case init: when s is empty, it can be segmented into a sequence of dict words*/
		dp[0] = 1;
		for (int curLen = 1; curLen <= N; ++curLen)
		{
			for (int leftLen = 0; leftLen < curLen; ++leftLen)
			{
				/*
				if s[0:leftLen-1] can be segmented into a sequence of dict words
				&& if s[leftLen:curLen-1] can be found in dict
				*/
				if (dp[leftLen] && dict.count(s.substr(leftLen, curLen - leftLen)))
				{
					/*now s[0:curLen-1] can be segmented into a sequence of dict words*/
					dp[curLen] = curLen - leftLen;//the length of the last string in the decomposition of s[leftLen:curLen-1]
				}
			}
		}

		std::vector<std::string> res;
		if (dp[N])
		{
			int idx = N;
			while (idx >= 1)
			{
				res.push_back(s.substr(idx - 1 - dp[idx] + 1, dp[idx]));//count = idx2 - idx1 + 1, idx1 = idx2 - count + 1
				idx -= dp[idx];
			}
		}
		std::reverse(res.begin(), res.end());

		std::cout << Debug::ToStr1D<int>()(dp) << std::endl;
		std::cout << "WordBreak CanBreak_FindOne_DP1D for \"" << s << "\" from \"" << Debug::ToStr1D<std::string>()(dict) << "\": " << (dp[N] > 0 ? true : false) << " (" << Debug::ToStr1D<std::string>()(res) << ")" << std::endl;
		return (dp[N] > 0 ? true : false);
	}

	//2. FindAllBreaks
	std::vector<std::string> FindAllBreaks_DP2D(const std::string & s, const std::unordered_set<std::string> & dict)
	{
		int N = s.size();
		std::vector<std::vector<int> > dp(N + 1, std::vector<int>());
		
		dp[0].push_back(0);
		for (int curLen = 1; curLen <= N; ++curLen)
		{
			for (int leftLen = 0; leftLen < curLen; ++leftLen)
			{
				if (!dp[leftLen].empty() && dict.count(s.substr(leftLen, curLen - leftLen)))
				{
					dp[curLen].push_back(leftLen);//s[0:curLen-1] can be breakable into leftWord s[0:leftLen-1] and rightWord s[leftLen:curLen-1]
				}
			}
		}

		std::vector<std::vector<std::string>> breakables(N + 1, std::vector<std::string>());
		for (int curLen = 1; curLen <= N; ++curLen)
		{
			for (int leftLen : dp[curLen])
			{
				if (leftLen == 0)
				{
					/*add only rightWord s[0:curLen-1] to breakables[curLen]*/
					breakables[curLen].push_back(s.substr(0, curLen));
					continue;
				}

				/*
				append all leftWord combinations with rightWord s[leftLen:curLen-1]
				, then add each to breakables[curLen]
				*/
				for (std::string leftWord : breakables[leftLen])
				{
					leftWord += " " + s.substr(leftLen, curLen - leftLen);
					breakables[curLen].push_back(leftWord);
				}
			}
		}
		Debug::Print2D<int>()(dp, false);
		Debug::Print2D<std::string>()(breakables, false);
		std::cout << "WordBreak FindAllBreaks_DP2D for \"" << s << "\" from \"" << Debug::ToStr1D<std::string>()(dict) << "\": " << Debug::ToStr1D<std::string>()(breakables[N]) << std::endl;
		return breakables[N];
	}

	std::vector<std::string> FindAllBreaks_DP2D_Recur(const std::string & s, const std::unordered_set<std::string> & dict)
	{
		int N = s.size();
		std::vector<std::vector<int> > dp(N + 1, std::vector<int>());

		/*tricky base case init: when s is empty, it can be segmented into a sequence of dict words*/
		dp[0].push_back(0);
		for (int curLen = 1; curLen <= N; ++curLen)
		{
			for (int leftLen = 0; leftLen < curLen; ++leftLen)
			{
				/*
				if s[0:leftLen-1] can be segmented into a sequence of dict words 
				&& if s[leftLen:curLen-1] can be found in dict
				*/
				if (!dp[leftLen].empty() && dict.count(s.substr(leftLen, curLen - leftLen)))
				{
					/*now s[0:curLen-1] can be segmented into "a sequence of dict words s[0:leftLen-1]" and "a dict word of s[leftLen:curLen-1]"*/
					dp[curLen].push_back(leftLen);
				}
			}
		}

		std::vector<std::vector<std::string> > breakables(N + 1, std::vector<std::string>());
		/*
		breakables[curLen]: a list of strings of "sequence of breakable dict words of s[0:curLen-1]", i.e., all possible sequences of breakable dict words of s[0:curLen-1]
		*/

		std::vector<std::string> allBreaks = this->findAllBreaks_DP2D_Recur(s, dp, breakables, N);

		Debug::Print2D<int>()(dp, false);
		Debug::Print2D<std::string>()(breakables, false);
		std::cout << "WordBreak FindAllBreaks_DP2D_Recur for \"" << s << "\" from \"" << Debug::ToStr1D<std::string>()(dict) << "\": " << Debug::ToStr1D<std::string>()(allBreaks) << std::endl;
		return allBreaks;
	}
private:
	std::vector<std::string> findAllBreaks_DP2D_Recur(const std::string & s, std::vector<std::vector<int> > & dp
		, std::vector<std::vector<std::string> > & breakables, int curLen)
	{
		if (!breakables[curLen].empty())
			return breakables[curLen];

		for (int leftLen : dp[curLen])
		{
			if (leftLen == 0)
			{
				/*add only rightWord s[0:curLen-1] to breakables[curLen]*/
				breakables[curLen].push_back(s.substr(0, curLen));
				continue;
			}

			/*
			append all leftWord combinations with rightWord s[leftLen:curLen-1]
			, then add each to breakables[curLen]
			*/
			std::vector<std::string> leftWordsTillCurLen = this->findAllBreaks_DP2D_Recur(s, dp, breakables, leftLen);
			for (std::string leftWord : leftWordsTillCurLen)
			{
				breakables[curLen].push_back(leftWord + " " + s.substr(leftLen, curLen - leftLen));
			}
		}
		return breakables[curLen];
	}
};
/*
WordBreak CanBreak_Recur for "catsanddog" from "cat, cats, and, sand, dog": 1
1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1
WordBreak CanBreak_DP1D for "catsanddog" from "cat, cats, and, sand, dog": 1
1, 0, 0, 3, 4, 0, 0, 3, 0, 0, 3
WordBreak CanBreak_FindOne_DP1D for "catsanddog" from "cat, cats, and, sand, dog": 1 (cats, and, dog)
[rY][cX]
Row#0	= 0,
Row#1	=  ,
Row#2	=  ,
Row#3	= 0,
Row#4	= 0,
Row#5	=  ,
Row#6	=  ,
Row#7	= 3, 4
Row#8	=  ,
Row#9	=  ,
Row#10	= 7,

[rY][cX]
Row#0	=  ,
Row#1	=  ,
Row#2	=  ,
Row#3	= cat,
Row#4	= cats,
Row#5	=  ,
Row#6	=  ,
Row#7	= cat sand, cats and
Row#8	=  ,
Row#9	=  ,
Row#10	= cat sand dog, cats and dog

WordBreak FindAllBreaks_DP2D for "catsanddog" from "cat, cats, and, sand, dog": cat sand dog, cats and dog
[rY][cX]
Row#0	= 0,
Row#1	=  ,
Row#2	=  ,
Row#3	= 0,
Row#4	= 0,
Row#5	=  ,
Row#6	=  ,
Row#7	= 3, 4
Row#8	=  ,
Row#9	=  ,
Row#10	= 7,

[rY][cX]
Row#0	=  ,
Row#1	=  ,
Row#2	=  ,
Row#3	= cat,
Row#4	= cats,
Row#5	=  ,
Row#6	=  ,
Row#7	= cat sand, cats and
Row#8	=  ,
Row#9	=  ,
Row#10	= cat sand dog, cats and dog

WordBreak FindAllBreaks_DP2D_Recur for "catsanddog" from "cat, cats, and, sand, dog": cat sand dog, cats and dog
WordBreak CanBreak_Recur for "hotdogpopcorn" from "pc, hot, dog, orn, hotdog, po, pop, corn, popcorn": 1
1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 0, 0, 1
WordBreak CanBreak_DP1D for "hotdogpopcorn" from "pc, hot, dog, orn, hotdog, po, pop, corn, popcorn": 1
1, 0, 0, 3, 0, 0, 3, 0, 2, 3, 2, 0, 0, 3
WordBreak CanBreak_FindOne_DP1D for "hotdogpopcorn" from "pc, hot, dog, orn, hotdog, po, pop, corn, popcorn": 1 (hot, dog, po, pc, orn)
[rY][cX]
Row#0	= 0,  ,
Row#1	=  ,  ,
Row#2	=  ,  ,
Row#3	= 0,  ,
Row#4	=  ,  ,
Row#5	=  ,  ,
Row#6	= 0, 3,
Row#7	=  ,  ,
Row#8	= 6,  ,
Row#9	= 6,  ,
Row#10	= 8,  ,
Row#11	=  ,  ,
Row#12	=  ,  ,
Row#13	= 6, 9, 10

[rY][cX]
Row#0	=  ,  ,  ,  ,  ,
Row#1	=  ,  ,  ,  ,  ,
Row#2	=  ,  ,  ,  ,  ,
Row#3	= hot,  ,  ,  ,  ,
Row#4	=  ,  ,  ,  ,  ,
Row#5	=  ,  ,  ,  ,  ,
Row#6	= hotdog, hot dog,  ,  ,  ,
Row#7	=  ,  ,  ,  ,  ,
Row#8	= hotdog po, hot dog po,  ,  ,  ,
Row#9	= hotdog pop, hot dog pop,  ,  ,  ,
Row#10	= hotdog po pc, hot dog po pc,  ,  ,  ,
Row#11	=  ,  ,  ,  ,  ,
Row#12	=  ,  ,  ,  ,  ,
Row#13	= hotdog popcorn, hot dog popcorn, hotdog pop corn, hot dog pop corn, hotdog po pc orn, hot dog po pc orn

WordBreak FindAllBreaks_DP2D for "hotdogpopcorn" from "pc, hot, dog, orn, hotdog, po, pop, corn, popcorn": hotdog popcorn, hot dog popcorn, hotdog pop corn, hot dog pop corn, hotdog po pc orn, hot dog po pc orn
[rY][cX]
Row#0	= 0,  ,
Row#1	=  ,  ,
Row#2	=  ,  ,
Row#3	= 0,  ,
Row#4	=  ,  ,
Row#5	=  ,  ,
Row#6	= 0, 3,
Row#7	=  ,  ,
Row#8	= 6,  ,
Row#9	= 6,  ,
Row#10	= 8,  ,
Row#11	=  ,  ,
Row#12	=  ,  ,
Row#13	= 6, 9, 10

[rY][cX]
Row#0	=  ,  ,  ,  ,  ,
Row#1	=  ,  ,  ,  ,  ,
Row#2	=  ,  ,  ,  ,  ,
Row#3	= hot,  ,  ,  ,  ,
Row#4	=  ,  ,  ,  ,  ,
Row#5	=  ,  ,  ,  ,  ,
Row#6	= hotdog, hot dog,  ,  ,  ,
Row#7	=  ,  ,  ,  ,  ,
Row#8	= hotdog po, hot dog po,  ,  ,  ,
Row#9	= hotdog pop, hot dog pop,  ,  ,  ,
Row#10	= hotdog po pc, hot dog po pc,  ,  ,  ,
Row#11	=  ,  ,  ,  ,  ,
Row#12	=  ,  ,  ,  ,  ,
Row#13	= hotdog popcorn, hot dog popcorn, hotdog pop corn, hot dog pop corn, hotdog po pc orn, hot dog po pc orn

WordBreak FindAllBreaks_DP2D_Recur for "hotdogpopcorn" from "pc, hot, dog, orn, hotdog, po, pop, corn, popcorn": hotdog popcorn, hot dog popcorn, hotdog pop corn, hot dog pop corn, hotdog po pc orn, hot dog po pc orn
*/
#endif