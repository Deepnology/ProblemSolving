#ifndef DESIGN_SEARCH_AUTOCOMPLETE_SYSTEM_H
#define DESIGN_SEARCH_AUTOCOMPLETE_SYSTEM_H
#include "Debug.h"
/*
Leetcode: Design Search Autocomplete System
Design a search autocomplete system for a search engine.
Users may input a sentence (at least one word and end with a special character '#').
For each character they type except '#', you need to return the top 3 historical hot sentences that have prefix the same as the part of sentence already typed.
Here are the specific rules:
The hot degree for a sentence is defined as the number of times a user typed the exactly same sentence before.
The returned top 3 hot sentences should be sorted by hot degree (The first is the hottest one).
If several sentences have the same degree of hot, you need to use ASCII-code order (smaller one appears first).
If less than 3 hot sentences exist, then just return as many as you can.
When the input is a special character, it means the sentence ends, and in this case, you need to return an empty list.

Your job is to implement the following functions:
The constructor function:
AutocompleteSystem(String[] sentences, int[] times): This is the constructor.
The input is historical data.
Sentences is a string array consists of previously typed sentences.
Times is the corresponding times a sentence has been typed.
Your system should record these historical data.

Now, the user wants to input a new sentence.
The following function will provide the next character the user types:
List<String> input(char c):
The input c is the next character typed by the user.
The character will only be lower-case letters ('a' to 'z'), blank space (' ') or a special character ('#').
Also, the previously typed sentence should be recorded in your system.
The output will be the top 3 historical hot sentences that have prefix the same as the part of sentence already typed.

Example:
Operation: AutocompleteSystem(["i love you", "island","ironman", "i love leetcode"], [5,3,2,2])
The system have already tracked down the following sentences and their corresponding times:
"i love you" : 5 times
"island" : 3 times
"ironman" : 2 times
"i love leetcode" : 2 times
Now, the user begins another search:

Operation: input('i')
Output: ["i love you", "island","i love leetcode"]
Explanation:
There are four sentences that have prefix "i".
Among them, "ironman" and "i love leetcode" have same hot degree.
Since ' ' has ASCII code 32 and 'r' has ASCII code 114, "i love leetcode" should be in front of "ironman".
Also we only need to output top 3 hot sentences, so "ironman" will be ignored.

Operation: input(' ')
Output: ["i love you","i love leetcode"]
Explanation:
There are only two sentences that have prefix "i ".

Operation: input('a')
Output: []
Explanation:
There are no sentences that have prefix "i a".

Operation: input('#')
Output: []
Explanation:
The user finished the input, the sentence "i a" should be saved as a historical sentence in system.
And the following input will be counted as a new search.
*/
class DesignSearchAutocompleteSystem
{
	struct Trie
	{
		Trie() :children(27, NULL), isKey(false), times(0) {}
		std::vector<Trie*> children;
		bool isKey;
		int times;
	};
	Trie * _root;
	std::string history;
	int Idx(char c)
	{
		if (c == ' ') return 26;
		return c - 'a';
	}
	char Char(int i)
	{
		if (i == 26) return ' ';
		return i + 'a';
	}
	void Insert(Trie * root, std::string & s, int times)
	{
		int N = s.size();
		int cur = 0;
		while (true)
		{

			if (!root->children[Idx(s[cur])])
			{
				root->children[Idx(s[cur])] = new Trie;
			}
			if (cur == N - 1)
			{
				root->children[Idx(s[cur])]->isKey = true;
				root->children[Idx(s[cur])]->times += times;
				break;
			}
			root = root->children[Idx(s[cur])];
			++cur;
		}
	}
	struct Less
	{
		bool operator()(const std::pair<int, std::string> & a, const std::pair<int, std::string> & b)
		{
			return a.first != b.first ? a.first < b.first : a.second > b.second;
		}
	};
	//collect all keys w/ prefix==s
	void recur(Trie * root, std::string & s, int N, int cur, std::priority_queue<std::pair<int, std::string>, std::vector<std::pair<int, std::string>>, Less> & maxHeap)
	{
		while (cur < N)
		{
			if (!root->children[Idx(s[cur])])
				return;
			root = root->children[Idx(s[cur])];
			++cur;
		}
		//now cur>=N
		if (root->isKey)
			maxHeap.push({ root->times, s });
		for (int i = 0; i < 27; ++i)
		{
			if (root->children[i])
			{
				s.push_back(Char(i));
				recur(root->children[i], s, N, cur + 1, maxHeap);
				s.pop_back();
			}
		}
	}
public:
	DesignSearchAutocompleteSystem(std::vector<std::string> sentences, std::vector<int> times) : _root(0), history()
	{
		_root = new Trie;
		int N = sentences.size();
		for (int i = 0; i < N; ++i)
			Insert(_root, sentences[i], times[i]);
	}

	std::vector<std::string> input(char c)
	{
		if (c != '#')
		{
			history.push_back(c);
			std::priority_queue<std::pair<int, std::string>, std::vector<std::pair<int, std::string>>, Less> maxHeap;
			int N = history.size();
			recur(_root, history, N, 0, maxHeap);
			int count = 0;
			std::vector<std::string> res;
			while (count++ < 3 && !maxHeap.empty())
			{
				res.push_back(maxHeap.top().second);
				maxHeap.pop();
			}
			return res;
		}
		else//c == '#' (end of input)
		{
			if (!history.empty())
			{
				Insert(_root, history, 1);
				history.clear();
			}
			return std::vector<std::string>();
		}
	}
};
/*

*/
#endif
