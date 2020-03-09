#ifndef ALL_O_ONE_INCR_DECR_GET_MAX_MIN_H
#define ALL_O_ONE_INCR_DECR_GET_MAX_MIN_H
#include "Debug.h"
/*
Leetcode: All O'one Data Structure
Implement a data structure supporting the following operations:

Inc(Key) - Inserts a new key with value 1. Or increments an existing key by 1. Key is guaranteed to be a non-empty string.
Dec(Key) - If Key's value is 1, remove it from the data structure. Otherwise decrements an existing key by 1. If the key does not exist, this function does nothing. Key is guaranteed to be a non-empty string.
GetMaxKey() - Returns one of the keys with maximal value. If no element exists, return an empty string "".
GetMinKey() - Returns one of the keys with minimal value. If no element exists, return an empty string "".
Challenge: Perform all these in O(1) time complexity.

Similar to LFUCache.h
*/
class AllOoneIncrDecrGetMaxMin
{
	typedef std::list<std::string> KeyList;//front: most recent key <-> back: least recent key
	typedef std::list<std::pair<int, KeyList>> ValList;//front: max val <-> back: min val
	ValList m_valList;
	std::unordered_map<std::string, std::pair<ValList::iterator, KeyList::iterator>> m_keyMap;
public:
	/** Initialize your data structure here. */
	AllOoneIncrDecrGetMaxMin()
	{

	}

	/** Inserts a new key <Key> with value 1. Or increments an existing key by 1. */
	void inc(std::string key)
	{
		std::cout << "AllOoneIncrDecrGetMaxMin inc \"" << key << "\"" << std::endl;

		auto itr = m_keyMap.find(key);
		auto vItr = m_valList.end();
		int val = 1;
		if (itr == m_keyMap.end())//key doesn't exist
		{

		}
		else//key already exists: remove keyNode from cur valNode's keyList
		{
			vItr = itr->second.first;
			auto kItr = itr->second.second;
			val = vItr->first + 1;
			vItr->second.erase(kItr);//remove keyNode
			if (vItr->second.empty())//remove valNode if its keyList is empty
				vItr = m_valList.erase(vItr);
		}

		//move key to prev incremented valNode
		if (vItr != m_valList.begin() && std::prev(vItr)->first == val)
		{
			--vItr;
			vItr->second.push_front(key);
		}
		else
		{
			std::pair<int, KeyList> valNode = { val,{ key } };
			vItr = m_valList.insert(vItr, valNode);
		}
		m_keyMap[key] = { vItr,vItr->second.begin() };
	}

	/** Decrements an existing key by 1. If Key's value is 1, remove it from the data structure. */
	void dec(std::string key)
	{
		std::cout << "AllOoneIncrDecrGetMaxMin dec \"" << key << "\"" << std::endl;

		auto itr = m_keyMap.find(key);
		if (itr == m_keyMap.end()) return;

		//remove keyNode from cur valNode's keyList
		auto vItr = itr->second.first;
		auto kItr = itr->second.second;
		int val = vItr->first - 1;
		vItr->second.erase(kItr);
		if (vItr->second.empty())
			vItr = m_valList.erase(vItr);
		else
			++vItr;//don't forget this!
		if (val == 0)
		{
			m_keyMap.erase(key);
			return;
		}

		//move key to next decremented valNode
		if (vItr != m_valList.end() && vItr->first == val)
		{
			vItr->second.push_front(key);
		}
		else
		{
			std::pair<int, KeyList> valNode = { val,{ key } };
			vItr = m_valList.insert(vItr, valNode);
		}
		m_keyMap[key] = { vItr,vItr->second.begin() };
	}

	/** Returns one of the keys with maximal value. */
	std::string getMaxKey()
	{
		std::string res = "";
		if (!m_valList.empty())
			res = m_valList.front().second.front();

		std::cout << "AllOoneIncrDecrGetMaxMin getMaxKey: " << res << std::endl;
		return res;
	}

	/** Returns one of the keys with Minimal value. */
	std::string getMinKey()
	{
		std::string res = "";
		if (!m_valList.empty())
			res = m_valList.back().second.front();

		std::cout << "AllOoneIncrDecrGetMaxMin getMinKey: " << res << std::endl;
		return res;
	}
};
/*
AllOoneIncrDecrGetMaxMin inc "hello"
AllOoneIncrDecrGetMaxMin inc "hello"
AllOoneIncrDecrGetMaxMin inc "world"
AllOoneIncrDecrGetMaxMin inc "world"
AllOoneIncrDecrGetMaxMin inc "hello"
AllOoneIncrDecrGetMaxMin dec "world"
AllOoneIncrDecrGetMaxMin getMaxKey: hello
AllOoneIncrDecrGetMaxMin getMinKey: world
AllOoneIncrDecrGetMaxMin inc "hello"
AllOoneIncrDecrGetMaxMin getMaxKey: hello
AllOoneIncrDecrGetMaxMin inc "hello"
AllOoneIncrDecrGetMaxMin dec "world"
AllOoneIncrDecrGetMaxMin getMinKey: hello
AllOoneIncrDecrGetMaxMin dec "hello"
AllOoneIncrDecrGetMaxMin inc "world"
AllOoneIncrDecrGetMaxMin getMaxKey: hello
AllOoneIncrDecrGetMaxMin getMinKey: world
*/
#endif
