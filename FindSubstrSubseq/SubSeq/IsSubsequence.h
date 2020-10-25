#ifndef IS_SUBSEQUENCE_H
#define IS_SUBSEQUENCE_H
#include "Debug.h"
/*
Leetcode: Is Subsequence
Given a string s and a string t, check if s is subsequence of t.
You may assume that there is only lower case English letters in both s and t.
t is potentially a very long (length ~= 500,000) string, and s is a short string (<=100).
A subsequence of a string is a new string which is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters.
(ie, "ace" is a subsequence of "abcde" while "aec" is not).

Example 1:
s = "abc", t = "ahbgdc"
Return true.

Example 2:
s = "axc", t = "ahbgdc"
Return false.

Follow up:
If there are lots of incoming S, say S1, S2, ... , Sk where k >= 1B, and you want to check one by one to see if T has its subsequence.
In this scenario, how would you change your code?

Leetcode: Number of Matching Subsequences
Given string S and a dictionary of words words, find the number of words[i] that is a subsequence of S.
Example :
Input:
S = "abcde"
words = ["a", "bb", "acd", "ace"]
Output: 3
Explanation: There are three words in words that are a subsequence of S: "a", "acd", "ace".
*/
class IsSubsequence
{
public:
	IsSubsequence() {}

	void Validate(std::string s, std::string t)
	{
		bool res1 = BruteForce(s, t);
		bool res2 = FreqLookup(s, t);
		std::cout << "IsSubsequence for \"" << s << "\", \"" << t << "\" BruteForce and FreqLookup: " << res1 << ", " << res2 << std::endl;
	}

	bool BruteForce(std::string s, std::string t)//smaller, bigger
	{
		int N = t.size();
		int M = s.size();
		if (N == 0 && M == 0) return true;
		if (N == 0) return false;
		if (M == 0) return true;

		int j = 0;//s
		for (int i = 0; i < N; ++i)//t
		{
			if (t[i] == s[j])
				++j;
			if (j == M)
				return true;
		}
		return false;
	}

	//follow-up
	bool FreqLookup(std::string s, std::string t)
	{
		int N = t.size();
		int M = s.size();
		if (N == 0 && M == 0) return true;
		if (N == 0) return false;
		if (M == 0) return true;

		//for more freq lookup: using binary search
		std::vector<std::vector<int>> idxList(26, std::vector<int>());
		for (int i = 0; i < N; ++i)
			idxList[t[i] - 'a'].push_back(i);
		int prevIdx = -1;
		for (int i = 0; i < M; ++i)
		{
			auto ub = std::upper_bound(idxList[s[i] - 'a'].begin(), idxList[s[i] - 'a'].end(), prevIdx);
			if (ub == idxList[s[i] - 'a'].end())
				return false;
			prevIdx = *ub;
		}
		return true;
	}

	int CountMatching(std::string S, const std::vector<std::string> & words) //O(S + N * s * logS) time
    {
        std::vector<std::vector<int>> idxList(26, std::vector<int>());
        int N = S.size();
        for (int i = 0; i < N; ++i)
            idxList[S[i]-'a'].push_back(i);

        int res = 0;
        for (auto & s : words)
        {
            N = s.size();
            int prevIdx = -1;
            bool valid = true;
            for (int i = 0; i < N; ++i)
            {
                auto ub = std::upper_bound(idxList[s[i]-'a'].begin(), idxList[s[i]-'a'].end(), prevIdx);
                if (ub == idxList[s[i]-'a'].end())
                {
                    valid = false;
                    break;
                }
                prevIdx = *ub;
            }
            if (valid) ++res;
        }
        return res;
    }

    int CountMatching2(std::string S, const std::vector<std::string> & words) //O(S + N * s) time
    {
        std::vector<std::deque<std::string>> map(26, std::deque<std::string>());
        for (auto & s : words)
            map[s[0]-'a'].push_back(s);
        int res = 0;
        for (auto & c : S)
        {
            int N = map[c-'a'].size();
            while (N-- > 0) // remove only first N words in map[c-'a'] queue
            {
                auto cur = map[c-'a'].front();
                map[c-'a'].pop_front();
                if (cur.size() == 1)
                    ++res;
                else
                    map[cur[1]-'a'].push_back(cur.substr(1));
            }
        }
        return res;
    }
};
/*
Amazon OA
Amazon Fresh is running a promotion in which customers receive prizes for purchasing a secret combination of fruits. The combination will change each day, and the team running the promotion wants to use a code list to make it easy to change the combination.
The code list contains groups of fruits. Both the order of the groups within the code list and the order of the fruits within the groups matter. However, between the groups of fruits, any number, and type of fruit is allowable.
The term "anything" is used to allow for any type of fruit to appear in that location within the group.
Consider the following secret code list: [[apple, apple], [banana, anything, banana]]
Based on the above secret code list, a customer who made either of the following purchases would win the prize:
orange, apple, apple, banana, orange, banana
apple, apple, orange, orange, banana, apple, banana, banana
Write an algorithm to output 1 if the customer is a winner else output 0.
Input
The input to the function/method consists of two arguments:
codeList, a list of lists of strings representing the order and grouping of specific fruits that must be purchased in order to win the prize for the day.
shoppingCart, a list of strings representing the order in which a customer purchases fruit.
Output
Return an integer 1 if the customer is a winner else return 0.
Note
'anything' in the codeList represents that any fruit can be ordered in place of 'anything' in the group. 'anything' has to be something, it cannot be "nothing."
'anything' must represent one and only one fruit.
If secret code list is empty then it is assumed that the customer is a winner.
Example 1:
Input: codeList = [[apple, apple], [banana, anything, banana]] shoppingCart = [orange, apple, apple, banana, orange, banana]
Output: 1
Explanation:
codeList contains two groups - [apple, apple] and [banana, anything, banana].
The second group contains 'anything' so any fruit can be ordered in place of 'anything' in the shoppingCart. The customer is a winner as the customer has added fruits in the order of fruits in the groups and the order of groups in the codeList is also maintained in the shoppingCart.
Example 2:
Input: codeList = [[apple, apple], [banana, anything, banana]]
shoppingCart = [banana, orange, banana, apple, apple]
Output: 0
Explanation:
The customer is not a winner as the customer has added the fruits in order of groups but group [banana, orange, banana] is not following the group [apple, apple] in the codeList.
Example 3:
Input: codeList = [[apple, apple], [banana, anything, banana]] shoppingCart = [apple, banana, apple, banana, orange, banana]
Output: 0
Explanation:
The customer is not a winner as the customer has added the fruits in an order which is not following the order of fruit names in the first group.
Example 4:
Input: codeList = [[apple, apple], [apple, apple, banana]] shoppingCart = [apple, apple, apple, banana]
Output: 0
Explanation:
The customer is not a winner as the first 2 fruits form group 1, all three fruits would form group 2, but can't because it would contain all fruits of group 1.
 */
class IsSubsequence2
{
public:
    //O(N) time
    bool LinearTime(const std::vector<std::vector<std::string>> & codeList, const std::vector<std::string> & shoppingCart)
    {
        int N = shoppingCart.size();
        int M = codeList.size();
        int i = 0; int j = 0;
        while (i < N && j < M)
        {
            int ii = i;
            int k = 0; int S = codeList.size();
            while (ii < N && k < S)
            {
                if (shoppingCart[ii] == codeList[j][k] || codeList[j][k] == "anything")
                {
                    ++ii;
                    ++k;
                }
                else
                    break;
            }
            if (k == S)
            {
                i = ii;
                ++j;
            }
            else
                ++i;
        }
        bool res = j == M;

        Debug::Print2D<std::string>()(codeList, false);
        std::cout << "IsSubsequence2 for above codeList and shoppingCart=[" << Debug::ToStr1D<std::string>()(shoppingCart) << "]: " << res << std::endl;
        return res;
    }
};
/*
IsSubsequence for "abc", "ahbgdc" BruteForce and FreqLookup: 1, 1
IsSubsequence for "axc", "ahbgdc" BruteForce and FreqLookup: 0, 0

[rY][cX]
Row#0	= apple, apple,
Row#1	= banana, anything, banana

IsSubsequence2 for above codeList and shoppingCart=[orange, apple, apple, banana, orange, banana]: 1
[rY][cX]
Row#0	= apple, apple,
Row#1	= banana, anything, banana

IsSubsequence2 for above codeList and shoppingCart=[banana, orange, banana, apple, apple]: 0
[rY][cX]
Row#0	= apple, apple,
Row#1	= banana, anything, banana

IsSubsequence2 for above codeList and shoppingCart=[apple, banana, apple, banana, orange, banana]: 0
[rY][cX]
Row#0	= apple, apple,
Row#1	= apple, apple, banana

IsSubsequence2 for above codeList and shoppingCart=[apple, apple, apple, banana]: 0
*/
#endif
