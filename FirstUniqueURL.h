#ifndef FIRST_UNIQUE_URL_H
#define FIRST_UNIQUE_URL_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>
#include "Debug.h"
/*
Google
http://www.careercup.com/question?id=11856466
Given a very long list of URLs, find the first URL which is unique.
Expected O(n) time with one traversal.

Use a trie to store URLs.
Keep a pointer pointing to the head of a doubly linked list.
In the leaf node of the trie, keep a counter which indicates the count of the underlying URL string's occurrence
, and keep a pointer pointing to a corresponding node in the doubly linked list that is just inserted when the count is 1.
When the count raises to 2, delete the corresponding node from the doubly linked list (doubly linked list supports constant time deletion of a node) and mark the pointer to null.
In each node of the linked list, keep a pointer to the leaf node in the trie.

The doubly linked list will be a list of unique URLs.
The first node in the linked list will be the first unique URL.

see also TrieST.h
*/
class FirstUniqueURL
{
public:
	FirstUniqueURL(){}
	~FirstUniqueURL(){}

	struct Node
	{
		Node() : hasVal(false), children(256, nullptr), parent(nullptr), prev(nullptr), next(nullptr), count(0){}
		bool hasVal;
		char c;//the position of this node in parent node's children vector
		std::vector<Node *> children;

		Node * parent;//for tracking bottom-up to root in trie

		Node * prev;//for doubly linked list
		Node * next;//for doubly linked list

		int count;//number of occurrence of key ending at this node
	};

	std::string Find_1Pass(const std::vector<std::string> & urls)
	{
		Node * root = nullptr;
		Node * head = nullptr;
		Node * tail = nullptr;//tail: the current node of the linked list to append new node
		int N = urls.size();
		for (int i = 0; i < N; ++i)
		{
			root = this->insertRecur(root, urls[i], 0, head, tail);

			/*debug print current linked list*/
			Node * h = head;
			std::ostringstream oss;
			while (true)
			{
				if (h == nullptr)
				{
					oss << "N";
					break;
				}
				else
				{
					std::string s;
					this->bottomUpRecur(h, root, s);
					std::reverse(s.begin(), s.end());
					oss << s << "->";
					h = h->next;
				}
			}
			std::cout << oss.str() << std::endl;
			/**/
		}
		//now head->root is the first unique key
		std::string first;
		this->bottomUpRecur(head, root, first);
		std::reverse(first.begin(), first.end());

		std::cout << "FirstUniqueURL for \"" << Debug::ToStr1D<std::string>()(urls) << "\": " << first << std::endl;
		return first;
	}

private:
	/*
	use trie for bottom-up tracking of key
	cannot not use ternary search tree for bottom-up tracking of key because there will be irrelevant nodes in the path up to root
	*/
	void bottomUpRecur(Node * cur, Node * root, std::string & reversed)
	{
		if (cur == nullptr)
			return;
		if (cur == root)//root doesn't have its c value
			return;
		reversed += cur->c;
		this->bottomUpRecur(cur->parent, root, reversed);//go up
	}

	Node * insertRecur(Node * cur, const std::string & key, int begin, Node *& head, Node *& tail)
	{
		if (cur == NULL)
			cur = new Node();
		if (begin == key.size())
		{
			if (!cur->hasVal)
				cur->hasVal = true;
			++cur->count;
			if (cur->count == 1)//insert this node to doubly linked list
			{
				if (head == nullptr)
					head = tail = cur;
				else//append this node to next of tail, advance tail
				{
					tail->next = cur;
					cur->prev = tail;
					tail = cur;
				}
			}
			else if (cur->count == 2)//remove this node from doubly linked list
			{
				if (cur->prev)//cur is not head => no need to update head
				{
					cur->prev->next = cur->next;
				}
				else//cur is head => need to update head
				{
					head = cur->next;
					if (head)
						head->prev = nullptr;//maintain head node's property
				}
				if (cur->next)//cur is not tail => no need to update tail
				{
					cur->next->prev = cur->prev;
				}
				else//cur is tail => need to update tail
				{
					tail = cur->prev;
					if (tail)
						tail->next = nullptr;//maintain tail node's property
				}
			}
			return cur;
		}
		int c = key[begin];
		cur->children[c] = this->insertRecur(cur->children[c], key, begin + 1, head, tail);
		cur->children[c]->parent = cur;
		cur->children[c]->c = c;
		return cur;
	}
};
/*
www.facebook.com->N
N
www.google.com->N
N
N
www.apple.com->N
www.apple.com->www.battle.net->N
www.apple.com->www.battle.net->N
www.apple.com->www.battle.net->www.twitter.com->N
www.apple.com->www.twitter.com->N
www.apple.com->www.twitter.com->linkedin.com->N
www.twitter.com->linkedin.com->N
www.twitter.com->linkedin.com->www.yahoo.com->N
www.twitter.com->linkedin.com->www.yahoo.com->qualgame.com->N
www.twitter.com->linkedin.com->www.yahoo.com->qualgame.com->amazon.com->N
www.twitter.com->linkedin.com->www.yahoo.com->amazon.com->N
FirstUniqueURL for "www.facebook.com, www.facebook.com, www.google.com, www.google.com, www.facebook.com, www.apple.com, www.battle.net, www.google.com, www.twitter.com, www.battle.net, linkedin.com, www.apple.com, www.yahoo.com, qualgame.com, amazon.com, qualgame.com": www.twitter.com
*/
#endif