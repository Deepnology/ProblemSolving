#ifndef _SKIP_LIST_H
#define _SKIP_LIST_H
#include <vector>
#include <iostream>
#include <sstream>
/*
Insert, Search, Remove: O(logN) time in average, O(N) time in worst case
 */
class SkipList
{
	struct Node
	{
		int Key;
		std::vector<Node*> Forward;
		Node(int key_, int maxLevel):Key(key_), Forward(maxLevel+1, NULL)
		{}
	};
	const int m_MaxLevel;
	const double m_Fraction;//the fraction of the nodes with level i pointers also having level i+1 pointers
	Node * m_Header;
	int m_CurLevel;
public:
	SkipList(int maxLevel, double fraction): m_MaxLevel(maxLevel), m_Fraction(fraction), m_Header(new Node(-1, m_MaxLevel)), m_CurLevel(0)
	{

	}
	void Insert(int key)
	{
		Node * cur = m_Header;
		std::vector<Node*> pre(m_MaxLevel+1, NULL);

		//fill up pre[0 : m_curLevel]
		for (int i = m_CurLevel; i >= 0; --i)//move from top to bottom
		{
			while (cur->Forward[i] != NULL && cur->Forward[i]->Key < key)//move from left to right
				cur = cur->Forward[i];
			pre[i] = cur;
		}

		Node * nxt = cur->Forward[0];
		if (nxt == NULL || nxt->Key != key)
		{
			int randLevel = GetRandomLevel();
			if (randLevel > m_CurLevel)
			{
				for (int i = m_CurLevel + 1; i < randLevel + 1; ++i)
					pre[i] = m_Header;
				m_CurLevel = randLevel;
			}
			Node * newNode = new Node(key, randLevel);
			for (int i = 0; i <= randLevel; ++i)
			{
				newNode->Forward[i] = pre[i]->Forward[i];
				pre[i]->Forward[i] = newNode;
			}
		}

		std::cout << "Insert " << key << ":" << std::endl;
		Print();
	}
	bool Search(int key)
	{
		Node * cur = m_Header;
		for (int i = m_CurLevel; i >= 0; --i)//move from top to bottom
		{
			while (cur->Forward[i] && cur->Forward[i]->Key < key)//move from left to right
				cur = cur->Forward[i];
		}
		Node * nxt = cur->Forward[0];
		bool found = false;
		if (nxt && nxt->Key == key)
			found = true;
		std::cout << "Search " << key << ": " << found << std::endl;
		return found;
	}
	void Remove(int key)
	{
		Node * cur = m_Header;
		std::vector<Node*> pre(m_MaxLevel+1, NULL);
		for (int i = m_CurLevel; i >= 0; --i)
		{
			while (cur->Forward[i] != NULL && cur->Forward[i]->Key < key)
				cur = cur->Forward[i];
			pre[i] = cur;
		}
		Node * nxt = cur->Forward[0];
		if (nxt != NULL && nxt->Key == key)
		{
			for (int i = 0; i <= m_CurLevel; ++i)
			{
				if (pre[i]->Forward[i] != nxt)
					break;
				pre[i]->Forward[i] = nxt->Forward[i];
			}
			while (m_CurLevel > 0 && m_Header->Forward[m_CurLevel] == NULL)
				--m_CurLevel;
		}

		std::cout << "Remove " << key << ":" << std::endl;
		Print();
	}
	void Print()
	{
		std::ostringstream oss;
		for (int i = m_CurLevel; i >= 0; --i)
		{
			Node * cur = m_Header->Forward[i];
			oss << "Level" << i << ": ";
			while (cur)
			{
				oss << cur->Key << " ";
				cur = cur->Forward[i];
			}
			oss << std::endl;
		}
		std::cout << oss.str() << std::endl;
	}
private:
	int GetRandomLevel()
	{
		double r = (double)rand() / RAND_MAX;
		int resLevel = 0;
		while (r < m_Fraction && resLevel < m_MaxLevel)
		{
			++resLevel;
			r = (double)rand() / RAND_MAX;
		}
		return resLevel;
	}
};
#endif
