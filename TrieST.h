#ifndef TRIE_ST_H
#define TRIE_ST_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>
#include "Debug.h"
/*
Leetcode: Implement Trie (Prefix Tree), see also WordSearch2.h
void Put(const std::string & key)
bool Contains(const std::string & key)
bool ContainsKeyWPrefix(const std::string & prefix)
{
	Node * n = getRecur(root, prefix, 0);
	return n != NULL;
}
private:
void putRecur(Node *& x, const std::string & key, int begin)
Node * getRecur(Node * x, const std::string & key, int begin)

Leetcode: Add and Search Word - Data structure design, see also WordSearch2.h
Design a data structure that supports the following two operations:
void addWord(word)
bool search(word)
search(word) can search a literal word or a regular expression string containing only letters a-z or '.'.
A '.' means it can represent any one letter.
std::queue<std::string> KeysThatMatch(const std::string & pattern)
private:
void keysThatMatchRecur(Node * x, std::string & prefix, const std::string & pattern, std::queue<std::string> & results)

http://algs4.cs.princeton.edu/52trie/
http://algs4.cs.princeton.edu/52trie/TrieST.java.html
A string symbol table for extended ASCII strings, implemented using a 256-way trie.
*/
template<class Val>
class TrieST
{
private:
	//R-way trie node
	struct Node
	{
		Node(): isKey(false), next(256, NULL){}
		Val val;
		bool isKey;
		std::vector<Node *> next;
	};
	Node * root;
	int N;//number of keys in trie

public:
	TrieST(): root(NULL), N(0){}
	~TrieST()
	{
		this->Delete();
	}
	Val Get(const std::string & key) const
	{
		Node * found = this->getRecur(root, key, 0);
		Val res;
		if (found && found->isKey)
			res = found->val;

		std::cout << "TrieST Get \"" << key << "\": " << res << std::endl;
		return res;
	}
	bool Contains(const std::string & key) const
	{
		Node * found = this->getRecur(root, key, 0);
		bool res = found && found->isKey;

		std::cout << "TrieST Contains \"" << key << "\": " << res << std::endl;
		return res;
	}
private:
	Node * getRecur(Node * cur, const std::string & key, int begin) const
	{
		if (cur == NULL)
			return NULL;
		if (begin == key.size())
			return cur;

		int c = key[begin];
		return this->getRecur(cur->next[c], key, begin + 1);
	}
public:
	//Inserts the key-value pair into the symbol table, overwriting the old value with the new value if the key is already in the symbol table.
	void Put(const std::string & key, Val val)
	{
		this->putRecur(root, key, val, 0);
		std::cout << "TrieST Put [" << key << "," << val << "]" << std::endl;
	}
private:
	void putRecur(Node *& cur, const std::string & key, Val val, int begin)
	{
		if (cur == NULL)
			cur = new Node();
		if (begin == key.size())
		{
			if (!cur->isKey)
			{
				cur->isKey = true;
				++N;
			}
			cur->val = val;
			return;
		}

		int c = key[begin];
		this->putRecur(cur->next[c], key, val, begin + 1);
	}

public:
	//Removes the key from the set if the key is present.
	void Delete(const std::string & key)
	{
		this->deleteRecur(root, key, 0);
		std::cout << "TrieST Delete \"" << key << "\"" << std::endl;
	}
private:
	void deleteRecur(Node *& cur, const std::string & key, int begin)
	{
		if (cur == NULL)
			return;
		if (begin == key.size())
		{
			if (cur->isKey)
			{
				cur->isKey = false;
				--N;
			}
		}
		else
		{
			int c = key[begin];
			this->deleteRecur(cur->next[c], key, begin + 1);
		}

		//remove subtrie rooted at cur if it is completely empty
		if (cur->isKey)
			return;
		for (int c = 0; c < 256; ++c)
		{
			if (cur->next[c] != NULL)
				return;
		}

		//std::cout << "TrieST::Delete(" << cur->val << ")" << std::endl;
		delete cur;
		cur = NULL;
	}
public:
	void Delete()
	{
		this->deleteRecur(root);
		std::cout << "TrieST Delete" << std::endl;
	}
private:
	void deleteRecur(Node *& cur)
	{
		if (cur == NULL)
			return;

		for (int c = 0; c < 256; ++c)
		{
			this->deleteRecur(cur->next[c]);
		}

		//std::cout << "TrieST::Delete(" << cur->val << ")" << std::endl;
		delete cur;
		cur = NULL;
	}
public:
	//Return the number of key-value pairs in this symbol table.
	int Size() const
	{
		return N;
	}
	bool IsEmpty() const
	{
		return this->Size() == 0;
	}

	//Returns all keys in the symbol table
	std::vector<std::string> Keys()
	{
		std::vector<std::string> res = this->KeysWithPrefix(std::string());
		std::cout << "TrieST Keys: " << Debug::ToStr1D<std::string>()(res) << std::endl;
		return res;
	}

	//Returns all of the keys in the set that start with prefix.
	std::vector<std::string> KeysWithPrefix(const std::string & prefix)
	{
		Node * prefixNode = this->getRecur(root, prefix, 0);
		std::string path(prefix);
		std::vector<std::string> res;
		this->keysWPrefixRecur(prefixNode, path, res);
		std::cout << "TrieST KeysWithPrefix \"" << prefix << "\": " << Debug::ToStr1D<std::string>()(res) << std::endl;
		return res;
	}
private:
	void keysWPrefixRecur(Node * cur, std::string & prefix, std::vector<std::string> & res)
	{
		if (cur == NULL)
			return;

		if (cur->isKey)
			res.push_back(prefix);

		for (int c = 0; c < 256; ++c)
		{
			prefix.push_back(c);
			this->keysWPrefixRecur(cur->next[c], prefix, res);
			prefix.pop_back();
		}
	}

public:
	//Returns all of the keys in the symbol table that match pattern, where . symbol is treated as a wildcard character
	std::vector<std::string> KeysThatMatch(const std::string & pattern)
	{
		std::string path;
		std::vector<std::string> res;
		this->keysThatMatchRecur(root, path, pattern, res);
		std::cout << "TrieST KeysThatMatch \"" << pattern << "\": " << Debug::ToStr1D<std::string>()(res) << std::endl;
		return res;
	}
private:
	void keysThatMatchRecur(Node * cur, std::string & prefix, const std::string & pattern, std::vector<std::string> & res)
	{
		if (cur == NULL)
			return;
		int begin = prefix.size();
		if (begin == pattern.size())
		{
			if (cur->isKey)
				res.push_back(prefix);
			return;
		}

		char c = pattern[begin];
		if (c == '.')
		{
			for (int ch = 0; ch < 256; ++ch)
			{
				prefix.push_back(ch);
				this->keysThatMatchRecur(cur->next[ch], prefix, pattern, res);
				prefix.pop_back();
			}
		}
		else
		{
			prefix.push_back(c);
			this->keysThatMatchRecur(cur->next[(int)c], prefix, pattern, res);
			prefix.pop_back();
		}
	}
public:
	//Returns the string key in the symbol table that is the longest prefix of query, or null, if no such string
	std::string LongestPrefixKeyOf(const std::string & query) const
	{
		int length = 0;
		this->longestPrefixKeyOfRecur(root, query, 0, length);
		std::cout << "TrieST LongestPrefixKeyOf \"" << query << "\": " << query.substr(0, length) << std::endl;
		return query.substr(0, length);
	}
private:
	void longestPrefixKeyOfRecur(Node * cur, const std::string & query, int begin, int & length) const
	{
		if (cur == NULL)
			return;

		if (cur->isKey)
			length = begin;

		if (begin == query.size())
			return;

		char c = query[begin];
		this->longestPrefixKeyOfRecur(cur->next[c], query, begin + 1, length);
	}
public:
	//Returns the longest prefix of all the keys in the symbol table that is also a prefix of query, or null, if no such string
	std::string LongestPrefixOf(const std::string & query) const
	{
		int length = 0;
		this->longestPrefixOfRecur(root, query, 0, length);
		std::cout << "TrieST LongestPrefixOf \"" << query << "\": " << query.substr(0, length) << std::endl;
		return query.substr(0, length);
	}
private:
	void longestPrefixOfRecur(Node * cur, const std::string & query, int begin, int & length) const
	{
		if (cur == NULL)
			return;

		length = begin;

		if (begin == query.size())
			return;

		char c = query[begin];
		return this->longestPrefixOfRecur(cur->next[c], query, begin + 1, length);
	}
};
/*
TrieST Put [peter,1]
TrieST Put [piper,2]
TrieST Put [picked,3]
TrieST Put [a,4]
TrieST Put [peck,5]
TrieST Put [of,6]
TrieST Put [pickled,7]
TrieST Put [peppers,8]
TrieST Get "peter": 1
TrieST Get "piper": 2
TrieST Get "picked": 3
TrieST Get "a": 4
TrieST Get "peck": 5
TrieST Get "of": 6
TrieST Get "pickled": 7
TrieST Get "peppers": 8
TrieST Contains "p": 0
TrieST Contains "pe": 0
TrieST Contains "pi": 0
TrieST Contains "pet": 0
TrieST Contains "a": 1
TrieST KeysWithPrefix "": a, of, peck, peppers, peter, picked, pickled, piper
TrieST Keys: a, of, peck, peppers, peter, picked, pickled, piper
TrieST KeysWithPrefix "pe": peck, peppers, peter
TrieST KeysThatMatch "p..er": peter, piper
TrieST LongestPrefixKeyOf "peterpiper": peter
TrieST LongestPrefixOf "picture": pic
TrieST Delete "peter"
TrieST Delete "picked"
TrieST KeysWithPrefix "": a, of, peck, peppers, pickled, piper
TrieST Keys: a, of, peck, peppers, pickled, piper
TrieST Delete
TrieST KeysWithPrefix "":
TrieST Keys:
TrieST Delete
*/
#endif