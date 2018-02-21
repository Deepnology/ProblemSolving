#ifndef IMPLEMENT_HASH_MAP_H
#define IMPLEMENT_HASH_MAP_H
#include "Debug.h"
/*
http://blog.csdn.net/u013325815/article/details/52907170
*/
class ImplementHashMap //use <string, int> for simplicity
{
	struct ListNode
	{
		std::string key;
		int val;
		ListNode * next;
		ListNode(const std::string & key_, int val_) : key(key_), val(val_), next(NULL) {}
	};
	size_t m_size;
	std::vector<ListNode*> m_map;
public:
	ImplementHashMap(size_t size): m_size(size), m_map(size, NULL) {}
    ~ImplementHashMap()
    {
        for (auto & cur : m_map)
        {
            while (cur)
            {
                ListNode * del = cur;
                cur = cur->next;
                delete del;
                del = NULL;
            }
        }
    }
	bool Put(const std::string & key, int val)
	{
		size_t idx = std::hash<std::string>()(key) % m_size;
		ListNode * cur = m_map[idx];
		while (cur != NULL)
		{
			if (cur->key.compare(key) == 0)
			{
				cur->val = val;
				return false;
			}
			cur = cur->next;
		}
		//now cur == NULL, add new node to beginning of bucket
		cur = new ListNode(key, val);
		cur->next = m_map[idx];
		m_map[idx] = cur;
		return true;
	}
	std::pair<int,bool> Get(const std::string & key) const
	{
		size_t idx = std::hash<std::string>()(key) % m_size;
		ListNode * cur = m_map[idx];
		while (cur != NULL)
		{
			if (cur->key.compare(key) == 0)
				return{ cur->val, true };
			cur = cur->next;
		}
		return{ 0, false };
	}
	void Remove(const std::string & key)
	{
		size_t idx = std::hash<std::string>()(key) % m_size;
		ListNode * head = m_map[idx];

		//see also RemoveNodesWGivenValLinkedList.h
		//1. remove front nodes whose key are equal
		while (head && head->key.compare(key) == 0)
		{
			ListNode * del = head;
			head = head->next;
			delete del;
		}
		//2. remove non-front nodes whose keys are equal
		ListNode * cur = head;
		while (cur && cur->next)
		{
			if (cur->next->key.compare(key) == 0)
			{
				ListNode * del = cur->next;
				cur->next = cur->next->next;
				delete del;
			}
			else
				cur = cur->next;
		}

		m_map[idx] = head;
	}

	void Print()
	{
		std::ostringstream oss;
		for (size_t i = 0; i < m_size; ++i)
		{
			oss << "Row#" << i << ": ";
			ListNode * head = m_map[i];
			while (head)
			{
				oss << "[" << head->key << "," << head->val << "]";
				if (head->next) oss << ", ";
				head = head->next;
			}
			oss << std::endl;
		}
		std::cout << oss.str() << std::endl;
	}
};
/*
Row#0:
Row#1: [d,4], [b,2], [a,1]
Row#2: [f,6], [e,5], [c,3]

11,22,33
Row#0:
Row#1: [d,4], [b,22], [a,11]
Row#2: [f,6], [e,5], [c,33]

Row#0:
Row#1: [d,4], [b,22]
Row#2: [e,5]
*/
#endif
