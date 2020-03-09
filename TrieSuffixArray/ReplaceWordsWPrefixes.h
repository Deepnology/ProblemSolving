#ifndef REPLACE_WORDS_W_PREFIXES_H
#define REPLACE_WORDS_W_PREFIXES_H
#include "Debug.h"
/*
Leetcode: Replace Words
In English, we have a concept called root, which can be followed by some other words to form another longer word- let's call this word successor.
For example, the root an, followed by other, which can form another word another.
Now, given a dictionary consisting of many roots and a sentence.
You need to replace all the successor in the sentence with the root forming it.
If a successor has many roots can form it, replace it with the root with the shortest length.
You need to output the sentence after the replacement.
Example 1:
Input: dict = ["cat", "bat", "rat"]
sentence = "the cattle was rattled by the battery"
Output: "the cat was rat by the bat"
*/
class ReplaceWordsWPrefixes
{
public:
	ReplaceWordsWPrefixes() {}
private:
	struct Trie
	{
		Trie() :children(26, NULL), isKey(false) {}
		std::vector<Trie*> children;
		bool isKey;
	};
	Trie * _root;
	void Insert(Trie * root, std::string & s)
	{
		int N = s.size();
		int cur = 0;
		while (true)
		{
			if (!root->children[s[cur] - 'a'])
			{
				root->children[s[cur] - 'a'] = new Trie;
			}
			if (cur == N - 1)
			{
				root->children[s[cur] - 'a']->isKey = true;
				break;
			}
			root = root->children[s[cur] - 'a'];
			++cur;
		}
	}
	std::string ShortestKey(Trie * root, std::string & s)
	{
		int cur = 0;
		int N = s.size();
		while (cur < N)
		{
			if (root->children[s[cur] - 'a'])
			{
				if (root->children[s[cur] - 'a']->isKey)
					return s.substr(0, cur + 1);
				root = root->children[s[cur] - 'a'];
			}
			else
				break;
			++cur;
		}
		return "";
	}
public:
	std::string UseTrie(std::vector<std::string>& dict, std::string sentence)
	{
		Trie * root = new Trie;
		for (auto & s : dict)
			Insert(root, s);

		std::string res;
		int N = sentence.size();
		int begin = 0;
		int i = 0;
		while (i < N)
		{
			begin = i;
			while (i < N && sentence[i] == ' ')
				++i;
			res += std::string(i - begin, ' ');
			begin = i;
			while (i < N && sentence[i] != ' ')
				++i;
			std::string s = sentence.substr(begin, i - begin);
			std::string k = ShortestKey(root, s);
			if (!k.empty())
				res += k;
			else
				res += s;
		}
		return res;
	}
};
#endif
