#ifndef LFU_CACHE_H
#define LFU_CACHE_H
#include "Debug.h"
/*
Leetcode: LFU Cache
Design and implement a data structure for Least Frequently Used (LFU) cache.
It should support the following operations: get and put.
get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
put(key, value) - Set or insert the value if the key is not already present.
				When the cache reaches its capacity, it should invalidate the least frequently used item before inserting a new item.
				For the purpose of this problem, when there is a tie (i.e., two or more keys that have the same frequency), the least recently used key would be evicted.
Follow up:
Could you do both operations in O(1) time complexity?
Example:
LFUCache cache = new LFUCache( 2 //capacity)
cache.put(1, 1);
cache.put(2, 2);
cache.get(1);       // returns 1
cache.put(3, 3);    // evicts key 2
cache.get(2);       // returns -1 (not found)
cache.get(3);       // returns 3.
cache.put(4, 4);    // evicts key 1.
cache.get(1);       // returns -1 (not found)
cache.get(3);       // returns 3
cache.get(4);       // returns 4

Use a freqList to keep track of distinct freqs sorted in decr order (front: max freq <-> back: min freq)
where each freqNode holds a timeList that keeps track of distinct keys (and their assoc values)
w/ same freqs sorted by the time that the key is accessed in incr order (front: most recent <-> back: least recent).
To evict a key that is min freq least recent when the cache is full, pick the key at freqList.back().timeList.back().
To move a key from its cur freqNode to an incremented freqNode, first check if the incremented freqNode exists.
If so, insert the key to begin of the found freqNode's timeList; otherwise, insert a new freqNode w/ its timeList containing only the key,
to the end of freqList or the next freqNode of the removed freqNode (new freqNode will be inserted at prev of the target freqNode).
*/
class LFUCache
{
	int m_capacity;
	int m_count;
	typedef std::list<std::pair<int, int>> TimeList;//<key,val>, front: most recent, back: least recent
	typedef std::list<std::pair<int, TimeList>> FreqList;//<freq,timeList>, front: max freq, back: min freq
	FreqList m_freqList;
	std::unordered_map<int, FreqList::iterator> m_freqMap;//<freq,freqNode>
	std::unordered_map<int, std::pair<FreqList::iterator, TimeList::iterator>> m_keyMap;//<key,<freqNode,timeNode>>
public:
	LFUCache(int capacity) : m_capacity(capacity), m_count(0)
	{

	}

	int get(int key)
	{
		std::cout << "LFUCache get \"" << key << "\": ";

		auto itr = m_keyMap.find(key);
		if (itr == m_keyMap.end())
		{std::cout << -1 << std::endl; return -1;}

		auto fItr = itr->second.first;
		auto tItr = itr->second.second;
		int freq = fItr->first;
		int value = tItr->second;
		//remove timeNode from timeList
		fItr->second.erase(tItr);
		if (fItr->second.empty())//remove freqNode if timeList is empty
		{
			fItr = m_freqList.erase(fItr);//make fItr points to the next node (for later insertion of new freqNode)
			m_freqMap.erase(freq);
		}
		++freq;

		//move timeNode to prev bigger freqNode
		if (m_freqMap.count(freq))//tgt freqNode exists
		{
			m_freqMap[freq]->second.push_front({ key,value });
		}
		else//tgt freqNode doesn't exist: insert a new freqNode
		{
			std::pair<int, TimeList> freqNode = { freq,{ { key,value } } };
			fItr = m_freqList.insert(fItr, freqNode);
			m_freqMap.insert({ freq,fItr });
		}
		m_keyMap[key] = { m_freqMap[freq],m_freqMap[freq]->second.begin() };

		std::cout << value << std::endl;
		return value;
	}

	void put(int key, int value)
	{
		if (m_capacity == 0) return;
		int freq = 1;
		FreqList::iterator fItr = m_freqList.end();
		if (m_keyMap.count(key))//key already exists: remove it
		{
			fItr = m_keyMap[key].first;
			auto tItr = m_keyMap[key].second;
			freq = fItr->first + 1;//increment freq
			fItr->second.erase(tItr);//remove timeNode
			if (fItr->second.empty())//remove freqNode
			{
				int f = fItr->first;
				fItr = m_freqList.erase(fItr);//make fItr point the next node (for later insertion of new freqNode)
				m_freqMap.erase(f);
			}
			m_keyMap.erase(key);
			--m_count;
		}

		else if (m_count == m_capacity)//remove the min freq least recent key, which must be != input key
		{
			int rmkey = m_freqList.back().second.back().first;
			m_freqList.back().second.pop_back();
			if (m_freqList.back().second.empty())
			{
				int rmfreq = m_freqList.back().first;
				m_freqList.pop_back();
				m_freqMap.erase(rmfreq);
			}
			m_keyMap.erase(rmkey);
			--m_count;
		}

		if (m_freqMap.count(freq))//tgt freqNode already exists: insert key to begin of timeList
		{
			m_freqMap[freq]->second.push_front({ key,value });
		}
		else//tgt freqNode doesn't exist: insert a new freqNode
		{
			std::pair<int, TimeList> freqNode = { freq,{ { key,value } } };
			fItr = m_freqList.insert(fItr, freqNode);
			m_freqMap.insert({ freq,fItr });
		}
		m_keyMap[key] = { m_freqMap[freq],m_freqMap[freq]->second.begin() };
		++m_count;

		std::cout << "LFUCache put \"" << key << ", " << value << "\"" << std::endl;
	}
};

//this is faster (w/o using freqMap)
class LFUCache2
{
	int m_capacity;
	int m_count;
	typedef std::list<std::pair<int, int>> TimeList;//<key,val>, front: most recent, back: least recent
	typedef std::list<std::pair<int, TimeList>> FreqList;//<freq,timeList>, front: max freq, back: min freq
	FreqList m_freqList;
	std::unordered_map<int, std::pair<FreqList::iterator, TimeList::iterator>> m_keyMap;//<key,<freqNode,timeNode>>
public:
	LFUCache2(int capacity) : m_capacity(capacity), m_count(0)
	{

	}

	int get(int key)
	{
		std::cout << "LFUCache2 get \"" << key << "\": ";

		auto itr = m_keyMap.find(key);
		if (itr == m_keyMap.end())
		{
			std::cout << -1 << std::endl; return -1;
		}

		auto fItr = itr->second.first;
		auto tItr = itr->second.second;
		int freq = fItr->first;
		int value = tItr->second;
		//remove timeNode from timeList
		fItr->second.erase(tItr);
		if (fItr->second.empty())//remove freqNode if timeList is empty
		{
			fItr = m_freqList.erase(fItr);//make fItr point to the next node (for later insertion of new freqNode)
		}
		++freq;

		//move timeNode to prev bigger freqNode
		if (fItr != m_freqList.begin() && std::prev(fItr)->first == freq)//tgt freqNode exists: insert key to begin of its timeList
		{
			fItr = std::prev(fItr);
			fItr->second.push_front({ key,value });
		}
		else//tgt freqNode doesn't exist: insert a new freqNode at fItr
		{
			std::pair<int, TimeList> freqNode = { freq,{ { key,value } } };
			fItr = m_freqList.insert(fItr, freqNode);
		}
		m_keyMap[key] = { fItr,fItr->second.begin() };

		std::cout << value << std::endl;
		return value;
	}

	void put(int key, int value)
	{
		if (m_capacity == 0) return;
		int freq = 1;
		FreqList::iterator fItr = m_freqList.end();
		if (m_keyMap.count(key))//key already exists: remove it
		{
			fItr = m_keyMap[key].first;
			auto tItr = m_keyMap[key].second;
			freq = fItr->first + 1;//increment freq
			fItr->second.erase(tItr);//remove timeNode
			if (fItr->second.empty())//remove freqNode
			{
				fItr = m_freqList.erase(fItr);//make fItr point the next node (for later insertion of new freqNode)
			}
			m_keyMap.erase(key);
			--m_count;
		}

		else if (m_count == m_capacity)//remove the min freq least recent key, which must be != input key
		{
			int rmkey = m_freqList.back().second.back().first;
			m_freqList.back().second.pop_back();
			if (m_freqList.back().second.empty())
			{
				m_freqList.pop_back();
			}
			m_keyMap.erase(rmkey);
			--m_count;
		}

		if (fItr != m_freqList.begin() && std::prev(fItr)->first == freq)//tgt freqNode already exists: insert key to begin of its timeList
		{
			fItr = std::prev(fItr);
			fItr->second.push_front({ key,value });
		}
		else//tgt freqNode doesn't exist: insert a new freqNode at fItr
		{
			std::pair<int, TimeList> freqNode = { freq,{ { key,value } } };
			fItr = m_freqList.insert(fItr, freqNode);
		}
		m_keyMap[key] = { fItr,fItr->second.begin() };
		++m_count;

		std::cout << "LFUCache2 put \"" << key << ", " << value << "\"" << std::endl;
	}
};
/*
LFUCache put "1, 1"
LFUCache put "2, 2"
LFUCache get "1": 1
LFUCache put "3, 3"
LFUCache get "2": -1
LFUCache get "3": 3
LFUCache put "4, 4"
LFUCache get "1": -1
LFUCache get "3": 3
LFUCache get "4": 4
LFUCache2 put "1, 1"
LFUCache2 put "2, 2"
LFUCache2 get "1": 1
LFUCache2 put "3, 3"
LFUCache2 get "2": -1
LFUCache2 get "3": 3
LFUCache2 put "4, 4"
LFUCache2 get "1": -1
LFUCache2 get "3": 3
LFUCache2 get "4": 4
*/
#endif
