#ifndef TST_H
#define TST_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>
/*
http://algs4.cs.princeton.edu/52trie/
http://algs4.cs.princeton.edu/52trie/TST.java.html
http://www.geeksforgeeks.org/ternary-search-tree/
Symbol table with string keys, implemented using a ternary search trie (TST).
*/
template<class Val>
class TST
{
private:
	struct Node
	{
		Node(): isKey(false), left(NULL), mid(NULL), right(NULL){}
		Val val;
		bool isKey;
		char c;
		Node * left;
		Node * mid;
		Node * right;
	};
	Node * root;
	int N;
public:
	TST():root(NULL), N(0){}
	~TST()
	{
		this->Delete();
	}

	int Size() const
	{
		return N:
	}
	bool Contains(const std::string & key) const
	{
		Node * n = this->getRecur(root, key, 0);
		return n != NULL && n->isKey;
	}
	Val Get(const std::string & key) const
	{
		if (key.empty())
			return Val();
		Node * x = this->getRecur(root, key, 0);
		if (x == NULL)
			return Val();
		return x->val;
	}
private:
	//Return subtrie corresponding to given key
	Node * getRecur(Node * x, const std::string & key, int begin) const
	{
		if (key.empty())
			return NULL;
		if (x == NULL)
			return NULL;
		char c = key[begin];
		if (c < x->c)
			return this->getRecur(x->left, key, begin);
		else if (c > x->c)
			return this->getRecur(x->right, key, begin);
		else if (begin < (int)key.size() - 1)
			return this->getRecur(x->mid, key, begin + 1);
		else
			return x;
	}

public:
	//Insert string s into the symbol table
	void Put(const std::string & s, Val val)
	{
		if (!this->Contains(s))
			++N;
		this->putRecur(root, s, val, 0);
	}
private:
	void putRecur(Node *& x, const std::string & s, Val val, int begin)
	{
		char c = s[begin];
		if (x == NULL)
		{
			x = new Node;
			x->c = c;
		}

		if (c < x->c)
			this->putRecur(x->left, s, val, begin);
		else if (c > x->c)
			this->putRecur(x->right, s, val, begin);
		else if (begin < (int)s.size() - 1)
			this->putRecur(x->mid, s, val, begin + 1);
		else
		{
			x->val = val;
			x->isKey = true;
		}
	}

public:
	//Returns the string key in the symbol table that is the longest prefix of s, or null, if no such string
	std::string LongestPrefixKeyOf(const std::string & s)
	{
		if (s.empty())
			return std::string();
		int length = 0;
		Node * x = root;
		int i = 0;
		while (x != NULL && i < (int)s.size())
		{
			char c = s[i];
			if (c < x->c)
				x = x->left;
			else if (c > x->c)
				x = x->right;
			else
			{
				++i;
				if (x->isKey)
					length = i;
				x = x->mid;
			}
		}
		return s.substr(0, length);
	}

	//Returns the longest prefix of all the keys in the symbol table that is also a prefix of query, or null, if no such string
	std::string LongestPrefixOf(const std::string & s)
	{
		if (s.empty())
			return std::string();
		int length = 0;
		Node * x = root;
		int i = 0;
		while (x != NULL && i < (int)s.size())
		{
			char c = s[i];
			if (c < x->c)
				x = x->left;
			else if (c > x->c)
				x = x->right;
			else
			{
				++i;
				length = i;
				x = x->mid;
			}
		}
		return s.substr(0, length);
	}

	//all keys in symbol table
	std::queue<std::string> Keys()
	{
		std::queue<std::string> queue;
		this->keysWPrefixRecur(root, std::string(), queue);
		return queue;
	}

	//all keys starting with given prefix
	std::queue<std::string> KeysWithPrefix(const std::string & prefix)
	{
		std::queue<std::string> queue;
		Node * x = this->getRecur(root, prefix, 0);
		if (x == NULL)
			return queue;
		if (x->isKey)
			queue.push(prefix);
		this->keysWPrefixRecur(x->mid, prefix, queue);
		return queue;
	}

	//return all keys matching given wildcard pattern
	std::queue<std::string> KeysThatMatch(const std::string & pat)
	{
		std::queue<std::string> queue;
		this->keysThatMatchRecur(root, std::string(), 0, pat, queue);
		return queue;
	}
private:
	void keysWPrefixRecur(Node * x, const std::string & prefix, std::queue<std::string> & queue)
	{
		if (x == NULL)
			return;
		this->keysWPrefixRecur(x->left, prefix, queue);
		if (x->isKey)
			queue.push(std::string(prefix + x->c));
		this->keysWPrefixRecur(x->mid, std::string(prefix + x->c), queue);
		this->keysWPrefixRecur(x->right, prefix, queue);
	}
	void keysThatMatchRecur(Node * x, const std::string & prefix, int i, const std::string & pat, std::queue<std::string> & queue)
	{
		if (x == NULL)
			return;
		char c = pat[i];
		if (c == '.' || c < x->c)
			this->keysThatMatchRecur(x->left, prefix, i, pat, queue);
		if (c == '.' || c == x->c)
		{
			if (i == (int)pat.size() - 1 && x->isKey)
				queue.push(std::string(prefix + x->c));
			if (i < (int)pat.size() - 1)
				this->keysThatMatchRecur(x->mid, std::string(prefix + x->c), i + 1, pat, queue);
		}
		if (c == '.' || c > x->c)
			this->keysThatMatchRecur(x->right, prefix, i, pat, queue);
	}

public:
	void Delete(const std::string & key)
	{
		this->deleteRecur(root, key, 0);
	}
private:
	void deleteRecur(Node *& x, const std::string & key, int begin)
	{
		if (x == NULL)
			return;
		char c = key[begin];
		if (c < x->c)
			this->deleteRecur(x->left, key, begin);
		else if (c > x->c)
			this->deleteRecur(x->right, key, begin);
		else if (begin < (int)key.size() - 1)
			this->deleteRecur(x->mid, key, begin + 1);
		else
		{
			if (x->isKey)
			{
				x->isKey = false;
				--N;
			}
		}

		if (x->isKey || x->left != NULL || x->mid != NULL || x->right != NULL)
			return;

		delete x;
		x = NULL;
	}

public:
	void Delete()
	{
		this->deleteRecur(root);
	}
private:
	void deleteRecur(Node *& x)
	{
		if (x == NULL)
			return;
		this->deleteRecur(x->left);
		this->deleteRecur(x->mid);
		this->deleteRecur(x->right);

		delete x;
		x = NULL;
	}
};


#endif