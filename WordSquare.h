#ifndef WORD_SQUARE_H
#define WORD_SQUARE_H
#include "Debug.h"
/*
Leetcode: Valid Word Square
Given a sequence of words, check whether it forms a valid word square.
A sequence of words forms a valid word square if the kth row and column read the exact same string, where 0 <= k < max(numRows, numColumns).
Note:
The number of words given is at least 1 and does not exceed 500.
Word length will be at least 1 and does not exceed 500.
Each word contains only lowercase English alphabet a-z.
Input:
[
  "abcd",
  "bnrt",
  "crm",
  "dt"
]
Output:
true
Explanation:
The first row and first column both read "abcd".
The second row and second column both read "bnrt".
The third row and third column both read "crm".
The fourth row and fourth column both read "dt".
Therefore, it is a valid word square.

Leetcode: Word Square
Given a set of words (without duplicates), find all word squares you can build from them.
A sequence of words forms a valid word square if the kth row and column read the exact same string, where 0 <= k < max(numRows, numColumns).
For example, the word sequence ["ball","area","lead","lady"] forms a word square because each word reads the same both horizontally and vertically.
b a l l
a r e a
l e a d
l a d y
Note:
There are at least 1 and at most 1000 words.
All words will have the exact same length.
Word length is at least 1 and at most 5.
Each word contains only lowercase English alphabet a-z.
Example 1:
Input:
["area","lead","wall","lady","ball"]
Output:
[
[ "wall",
  "area",
  "lead",
  "lady"
],
[ "ball",
  "area",
  "lead",
  "lady"
]
]
Explanation:
The output consists of two word squares. The order of output does not matter (just the order of words in each word square matters).
Example 2:
Input:
["abat","baba","atan","atal"]
Output:
[
[ "baba",
  "abat",
  "baba",
  "atan"
],
[ "baba",
  "abat",
  "baba",
  "atal"
]
]
Explanation:
The output consists of two word squares. The order of output does not matter (just the order of words in each word square matters).
*/
class WordSquare
{
public:
	WordSquare() {}
	bool Valid(std::vector<std::string> & words)
	{
		bool res = valid(words);
		Debug::Print2D<std::string>()(words, false);
		std::cout << "WordSquare Valid for the above board: " << res << std::endl;
		return res;
	}
private:
	bool valid(std::vector<std::string> & words)
	{
		int N = words.size();
		for (int i = 0; i < N; ++i)
		{
			int M = words[i].size();
			if (M > N) return false;
			//now M<=N
			for (int j = 0; j < M; ++j)
			{
				if (i >= (int)words[j].size() || words[i][j] != words[j][i])
					return false;
			}
		}
		return true;
	}

public:
	std::vector<std::vector<std::string>> FindAllCombinationPermutation_AllowRepeat(std::vector<std::string> & words)
	{
		std::vector<std::vector<std::string>> res;
		std::vector<std::string> path;
		recur(words, path, res);
		Debug::Print2D<std::string>()(words, false);
		std::cout << "WordSquare FindAllCombinationPermutation_AllowRepeat for the above words: " << std::endl;
		Debug::Print2D<std::string>()(res, true);
		return res;
	}
private:
	void recur(const std::vector<std::string> & words, std::vector<std::string> & path, std::vector<std::vector<std::string>> & res)
	{
		int N = words.size();
		int M = words[0].size();
		if (path.size() == M)
		{
			res.push_back(path);
			return;
		}
		for (int i = 0; i < N; ++i)
		{
			path.push_back(words[i]);
			if (SamePrefix(path, path.size() - 1))
				recur(words, path, res);
			path.pop_back();
		}
	}
	bool SamePrefix(const std::vector<std::string> & words, int idx)
	{
		for (int i = 0; i <= idx; ++i)
			if (words[idx][i] != words[i][idx])
				return false;
		return true;
	}




	struct Trie
	{
		Trie(bool isWord_ = false) :isWord(isWord_), children(26, NULL) {}
		std::vector<Trie*> children;
		bool isWord;
	};
	Trie * Insert(Trie * root, std::string & word)
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
					cur->children[word[i] - 'a'] = new Trie(true);
				else
					cur->children[word[i] - 'a'] = new Trie(false);
			}
			else
			{
				if (i == N - 1)
					cur->children[word[i] - 'a']->isWord = true;
			}
			cur = cur->children[word[i] - 'a'];
		}
		return root;
	}
	std::vector<std::string> Find(Trie * root, std::string & prefix)
	{
		std::vector<std::string> res;
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
		std::string path = prefix;
		CollectRecur(cur, path, res);
		return res;
	}
	void CollectRecur(Trie * cur, std::string & path, std::vector<std::string> & res)
	{
		if (cur->isWord)
			res.push_back(path);
		for (int i = 0; i < 26; ++i)
		{
			if (cur->children[i])
			{
				path.push_back(i + 'a');
				CollectRecur(cur->children[i], path, res);
				path.pop_back();
			}
		}
	}
public:
	std::vector<std::vector<std::string>> FindAllCombinationPermutation_AllowRepeat_Trie(std::vector<std::string> & words)
	{
		std::vector<std::vector<std::string>> res;
		std::vector<std::string> path;
		Trie * root = new Trie();
		for (auto & s : words)
			Insert(root, s);
		recur2(words, root, path, res);
		Debug::Print2D<std::string>()(words, false);
		std::cout << "WordSquare FindAllCombinationPermutation_AllowRepeat_Trie for the above words: " << std::endl;
		Debug::Print2D<std::string>()(res, true);
		return res;
	}
private:
	void recur2(std::vector<std::string> & words, Trie * root, std::vector<std::string> & path, std::vector<std::vector<std::string>> & res)
	{
		int M = words[0].size();
		if (path.size() == M)
		{
			res.push_back(path);
			return;
		}
		if (!path.empty())
		{
			std::string prefix;//prefix=rightmost col in path w/ length=path.size()
			int N = path.size();
			for (int i = 0; i < N; ++i)
				prefix += path[i][N];
			std::vector<std::string> wordsWPrefix = Find(root, prefix);
			for (const auto & s : wordsWPrefix)//try all words w/ cur prefix
			{
				path.push_back(s);
				recur2(words, root, path, res);
				path.pop_back();
			}
		}
		else
		{
			for (const auto & s : words)
			{
				path.push_back(s);
				recur2(words, root, path, res);
				path.pop_back();
			}
		}
	}
};
/*
[rY][cX]
Row#0	= a, b, c, d
Row#1	= b, n, r, t
Row#2	= c, r, m,
Row#3	= d, t,  ,

WordSquare Valid for the above board: 1
[rY][cX]
Row#0	= a, b, c, d
Row#1	= b, e, f, d
Row#2	= c, f,  ,
Row#3	= d, d, a,

WordSquare Valid for the above board: 0
[rY][cX]
Row#0	= a, r, e, a
Row#1	= l, e, a, d
Row#2	= w, a, l, l
Row#3	= l, a, d, y
Row#4	= b, a, l, l

WordSquare FindAllCombinationPermutation_AllowRepeat for the above words:
[cX][rY]
Row#0	= wall, ball
Row#1	= area, area
Row#2	= lead, lead
Row#3	= lady, lady

[rY][cX]
Row#0	= a, r, e, a
Row#1	= l, e, a, d
Row#2	= w, a, l, l
Row#3	= l, a, d, y
Row#4	= b, a, l, l

WordSquare FindAllCombinationPermutation_AllowRepeat_Trie for the above words:
[cX][rY]
Row#0	= wall, ball
Row#1	= area, area
Row#2	= lead, lead
Row#3	= lady, lady

[rY][cX]
Row#0	= a, b, a, t
Row#1	= b, a, b, a
Row#2	= a, t, a, n
Row#3	= a, t, a, l

WordSquare FindAllCombinationPermutation_AllowRepeat for the above words:
[cX][rY]
Row#0	= baba, baba
Row#1	= abat, abat
Row#2	= baba, baba
Row#3	= atan, atal

[rY][cX]
Row#0	= a, b, a, t
Row#1	= b, a, b, a
Row#2	= a, t, a, n
Row#3	= a, t, a, l

WordSquare FindAllCombinationPermutation_AllowRepeat_Trie for the above words:
[cX][rY]
Row#0	= baba, baba
Row#1	= abat, abat
Row#2	= baba, baba
Row#3	= atal, atan
*/
#endif
