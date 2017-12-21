#ifndef COLLECT_STRINGS_W_GIVEN_PREFIX_H
#define COLLECT_STRINGS_W_GIVEN_PREFIX_H
#include "Debug.h"
/*
Leetcode: Map Sum Pairs
Implement a MapSum class with insert, and sum methods.
For the method insert, you'll be given a pair of (string, integer).
The string represents the key and the integer represents the value.
If the key already existed, then the original key-value pair will be overridden to the new one.
For the method sum, you'll be given a string representing the prefix, and you need to return the sum of all the pairs' value whose key starts with the prefix.
Example 1:
Input: insert("apple", 3), Output: Null
Input: sum("ap"), Output: 3
Input: insert("app", 2), Output: Null
Input: sum("ap"), Output: 5

See also WordSquare.h
*/
class CollectStringsWGivenPrefix
{
	struct Trie
	{
		Trie(bool isWord_ = false, int val_ = 0) :isWord(isWord_), val(val_), children(26, NULL) {}
		std::vector<Trie*> children;
		bool isWord;
		int val;
	};
	Trie * Insert(Trie * root, std::string & word, int val)
	{
		if (root == NULL)
			root = new Trie();
		Trie * cur = root;
		int N = word.size();
		for (int i = 0; i < N; ++i)
		{
			if (cur->children[word[i] - 'a'] == NULL)
			{
				if (i == N - 1)
					cur->children[word[i] - 'a'] = new Trie(true, val);
				else
					cur->children[word[i] - 'a'] = new Trie(false, 0);
			}
			else
			{
				if (i == N - 1)
				{
					cur->children[word[i] - 'a']->isWord = true;
					cur->children[word[i] - 'a']->val = val;
				}
			}
			cur = cur->children[word[i] - 'a'];
		}
		return root;
	}
	int Find(Trie * root, std::string & prefix)
	{
		int res = 0;
		if (root == NULL) return res;
		Trie * cur = root;
		int N = prefix.size();
		int i = 0;
		for (; i < N; ++i)
		{
			if (cur->children[prefix[i] - 'a'])
				cur = cur->children[prefix[i] - 'a'];
			else
				break;
		}
		if (i < N) return res;//found nothing
		CollectRecur(cur, res);
		return res;
	}
	void CollectRecur(Trie * cur, int & res)
	{
		if (cur->isWord)
			res += cur->val;
		for (int i = 0; i < 26; ++i)
		{
			if (cur->children[i])
			{
				CollectRecur(cur->children[i], res);
			}
		}
	}
	Trie * root;
public:

	CollectStringsWGivenPrefix()
	{
		root = new Trie();
	}
	void insert(std::string key, int val)
	{
		Insert(root, key, val);
	}
	int sum(std::string prefix)
	{
		return Find(root, prefix);
	}
};
//use std::map
class CollectStringsWGivenPrefix_UseMap
{
	std::map<std::string, int> map;//strings are sorted
public:
	CollectStringsWGivenPrefix_UseMap() {}

	void insert(std::string key, int val)
	{
		map[key] = val;
	}
	int sum(std::string prefix)
	{
		int res = 0;
		int N = prefix.size();
		//equivalent to DFS thru all trie nodes below the "prefix" node
		for (auto itr = map.lower_bound(prefix); itr != map.end() && itr->first.substr(0, N) == prefix; ++itr)
			res += itr->second;
		return res;
	}
};
#endif
