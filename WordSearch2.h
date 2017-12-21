/*MEMO*/
#ifndef WORD_SEARCH_2_H
#define WORD_SEARCH_2_H
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include "Debug.h"
/*
Leetcode: Word Search II
Given a 2D board and a list of words from the dictionary, find all words in the board.
Each word must be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or vertically neighboring.
The same letter cell may not be used more than once in a word.
For example,
Given words = ["oath","pea","eat","rain"] and board =
[
  ['o','a','a','n'],
  ['e','t','a','e'],
  ['i','h','k','r'],
  ['i','f','l','v']
]
Return ["eat","oath"].
Note:
You may assume that all inputs are consist of lowercase letters a-z.

You would need to optimize your backtracking to pass the larger test.
Could you stop backtracking earlier?
If the current candidate does not exist in all words' prefix, you could stop backtracking immediately.
What kind of data structure could answer such query efficiently?
Does a hash table work? Why or why not? How about a Trie?
If you would like to learn how to implement a basic trie, please work on this problem: Implement Trie (Prefix Tree) first.
*/
class WordSearch2
{
	class TrieNode
	{
	public:
		// Initialize your data structure here.
		TrieNode() : isKey(false), next(26, NULL){}
		bool isKey;
		std::vector<TrieNode *> next;
	};

	class Trie
	{
	public:
		Trie() : root(NULL) {}

		// Inserts a word into the trie.
		void insert(std::string key)
		{
			this->insertRecur(root, key, 0);
		}
		void insertRecur(TrieNode *& x, const std::string & key, int begin)
		{
			if (x == NULL)
				x = new TrieNode();
			if (begin == key.size())
			{
				if (!x->isKey)
					x->isKey = true;
				return;
			}

			int c = key[begin] - 'a';
			this->insertRecur(x->next[c], key, begin + 1);
		}

		// Returns if the word is in the trie.
		bool search(std::string key) 
		{
			TrieNode * n = this->getRecur(root, key, 0);
			return n != NULL && n->isKey;
		}
		TrieNode * getRecur(TrieNode * x, const std::string & key, int begin)
		{
			if (x == NULL)
				return NULL;
			if (begin == key.size())
				return x;

			int c = key[begin] - 'a';
			return this->getRecur(x->next[c], key, begin + 1);
		}

		// Returns if there is any word in the trie
		// that starts with the given prefix.
		bool startsWith(std::string prefix)
		{
			TrieNode * n = this->getRecur(root, prefix, 0);
			return n != NULL;
		}

		void Delete(const std::string & key)
		{
			this->deleteRecur(root, key, 0);
		}
		void deleteRecur(TrieNode *& x, const std::string & key, int begin)
		{
			if (x == NULL)
				return;
			if (begin == key.size())
			{
				x->isKey = false;
			}
			else
			{
				int c = key[begin] - 'a';
				this->deleteRecur(x->next[c], key, begin + 1);
			}

			if (x->isKey)
				return;
			for (int i = 0; i < 26; ++i)
			{
				if (x->next[i] != NULL)
					return;
			}
			delete x;
			x = NULL;
		}

		bool searchWildcard(std::string pattern)
		{
			std::string path;
			return this->searchWildCardRecur(root, path, pattern);
		}
		bool searchWildCardRecur(TrieNode * x, std::string & prefix, const std::string & pattern)
		{
			if (x == NULL)
				return false;
			int begin = prefix.size();
			if (begin == pattern.size())
			{
				if (x->isKey)
					return true;
				return false;
			}

			char c = pattern[begin];
			if (c == '.')
			{
				for (int ch = 0; ch < 26; ++ch)
				{
					prefix.push_back(ch + 'a');
					if (this->searchWildCardRecur(x->next[ch], prefix, pattern))
						return true;
					prefix.pop_back();
				}
			}
			else
			{
				prefix.push_back(c);
				if (this->searchWildCardRecur(x->next[c - 'a'], prefix, pattern))
					return true;
				prefix.pop_back();
			}
			return false;
		}
	private:
		TrieNode * root;
	};

public:
	WordSearch2(){}
	~WordSearch2(){}

	std::vector<std::string> DFS_ConstSpace_Trie(std::vector<std::vector<char> > & board, std::vector<std::string> & words)//[rowY][columnX]
	{
		if (board.empty() || board[0].empty() || words.empty())
			return std::vector<std::string>();
		Debug::Print2D<char>()(board, false);

		Trie trie;
		for (const auto & str : words)
			trie.insert(str);

		int M = board.size();
		int N = board[0].size();

		std::vector<std::string> res;
		std::string path;
		for (int i = 0; i < M; ++i)//for each row from top to bottom
		{
			for (int j = 0; j < N; ++j)//for each col from left to right
			{
				char c = board[i][j];
				path.push_back(c);
				board[i][j] = '.';
				this->dfs_ConstSpace_Recur(board, i, j, trie, path, res);
				board[i][j] = c;
				path.pop_back();
			}
		}

		std::cout << "WordSearch2 DFS_ConstSpace_Trie for \"" << Debug::ToStr1D<std::string>()(words) << "\": " << Debug::ToStr1D<std::string>()(res) << std::endl;
		return res;
	}
private:
	void dfs_ConstSpace_Recur(std::vector<std::vector<char> > & board
		, int curRow, int curCol, Trie & trie, std::string & path, std::vector<std::string> & res)
	{
		if (!trie.startsWith(path))
			return;
		if (trie.search(path))
		{
			res.push_back(path);
			trie.Delete(path);// delete the key when found to avoid duplicates!!!!
		}

		int M = board.size();
		int N = board[0].size();

		if (curRow - 1 >= 0 && board[curRow - 1][curCol] != '.')
		{
			char c = board[curRow - 1][curCol];
			path.push_back(c);
			board[curRow - 1][curCol] = '.';
			this->dfs_ConstSpace_Recur(board, curRow - 1, curCol, trie, path, res);
			board[curRow - 1][curCol] = c;
			path.pop_back();
		}
		if (curRow + 1 < M && board[curRow + 1][curCol] != '.')
		{
			char c = board[curRow + 1][curCol];
			path.push_back(c);
			board[curRow + 1][curCol] = '.';
			this->dfs_ConstSpace_Recur(board, curRow + 1, curCol, trie, path, res);
			board[curRow + 1][curCol] = c;
			path.pop_back();
		}
		if (curCol - 1 >= 0 && board[curRow][curCol - 1] != '.')
		{
			char c = board[curRow][curCol - 1];
			path.push_back(c);
			board[curRow][curCol - 1] = '.';
			this->dfs_ConstSpace_Recur(board, curRow, curCol - 1, trie, path, res);
			board[curRow][curCol - 1] = c;
			path.pop_back();
		}
		if (curCol + 1 < N && board[curRow][curCol + 1] != '.')
		{
			char c = board[curRow][curCol + 1];
			path.push_back(c);
			board[curRow][curCol + 1] = '.';
			this->dfs_ConstSpace_Recur(board, curRow, curCol + 1, trie, path, res);
			board[curRow][curCol + 1] = c;
			path.pop_back();
		}
	}
};
/*
[rY][cX]
Row#0	= o, a, a, n
Row#1	= e, t, a, e
Row#2	= i, h, k, r
Row#3	= i, f, l, v

WordSearch2 DFS_ConstSpace_Trie for "oath, pea, eat, rain": oath, eat
*/
#endif