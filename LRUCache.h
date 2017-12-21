#ifndef LRU_CACHE_H
#define LRU_CACHE_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <map>
#include <set>
#include <list>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, HashTable: Implement an ISBN cache
Implement a cache for looking up prices of books identified by their ISBN.
Use the Least Recently Used (LRU) strategy for cache eviction policy.
Elements of programming interview, BST: The most visited pages problem, Find the most visited pages in a window
You are to implement methods to analyze log file data to find the most visited pages.
Only pages whose timestamps are within a specified duration of the page most recently read are to be considered.
Specifically, implement the following methods:
-void add(Entry p)---add p.page to the set of visited pages. It is guaranteed that if add(q) is called after add(p) then q.timestamp is greater than or equal to p.timestamp.
-List<String> common(k)---return a list of the k most visited pages.

Leecode: LRU Cache
// Design and implement a data structure for Least Recently Used (LRU) cache.
// It should support the following operations: get and set.
//
// get(key) - Get the value (will always be positive) of the key if the key
// exists in the cache, otherwise return -1.
// set(key, value) - Set or insert the value if the key is not already present.
// When the cache reached its capacity, it should invalidate the least
// recently used item before inserting a new item.

*/
//doesn't allow dups of keys
//use list to keep track of distinct keys (and their assoc vals) sorted by the time index that is accessed, where those keys in the back of list out capacity can be evicted
template<class K, class V>
class LRUCache
{
public:
	struct CacheNode
	{
		CacheNode(K k, V v) : key(k), value(v) {}
		K key;
		V value;
	};
	LRUCache(int capacity) : m_capacity(capacity)
	{}
	~LRUCache(){}
	
	V Get(K key)
	{
		if (!m_itrMap.count(key))
			throw std::exception("empty LRU Cache");
		CacheNode cur = *m_itrMap[key];
		m_list.erase(m_itrMap[key]);
		m_list.push_front(cur);
		m_itrMap[key] = m_list.begin();
		return m_list.front().value;
	}
	void Set(K key, V value)
	{
		if (m_itrMap.count(key) != 0)//already exist: remove from list
		{
			m_list.erase(m_itrMap[key]);
		}
		else//doesn't exist: remove the oldest from list if capacity is not big enough to add a new one
		{
			if (m_capacity == (int)m_list.size())
			{
				m_itrMap.erase(m_list.back().key);
				m_list.pop_back();
			}
		}
		//now insert new key value pair to the front of list
		m_list.push_front(CacheNode(key, value));
		m_itrMap[key] = m_list.begin();
	}
	std::list<CacheNode> GetCache() const
	{
		return m_list;
	}
	void Print()
	{
		std::ostringstream oss;
		typename std::list<CacheNode>::iterator prevOfEnd = m_list.end();
		--prevOfEnd;
		for (typename std::list<CacheNode>::iterator i = m_list.begin(); i != m_list.end(); ++i)
		{
			oss << "[" << i->key << "," << i->value << "]";
			if (i != prevOfEnd)
				oss << ", ";
		}
		std::cout << "LRUCache: " << oss.str() << std::endl;
	}
private:
	int m_capacity;
	std::list<CacheNode> m_list;
	std::unordered_map<K, typename std::list<CacheNode>::iterator> m_itrMap;
};

//doesn't allow duplicates of urls
//use list to keep track of distinct urls sorted by the time index that is accessed, where those urls in the back of list out of capacity can be evicted
class URLHistory
{
public:
	explicit URLHistory(int capacity): m_capacity(capacity){}
	~URLHistory(){}

	void Visit(const std::string & url)
	{
		if (m_itrMap.count(url) != 0)//already exist: remove from list
		{
			m_list.erase(m_itrMap[url]);
		}
		else//doesn't exist: remove the oldest from list if capacity is not big enough to add a new one
		{
			if (m_capacity == (int)m_list.size())
			{
				m_itrMap.erase(m_list.back());
				m_list.pop_back();
			}
		}
		//now insert new url to the front
		m_list.push_front(url);
		m_itrMap[url] = m_list.begin();
	}
	std::list<std::string> GetHistory() const
	{
		return m_list;
	}
	void Print()
	{
		std::cout << "URLHistory: " << Debug::ToStr1D<std::string>()(m_list) << std::endl;
	}

private:
	int m_capacity;
	std::list<std::string> m_list;
	std::unordered_map<std::string, std::list<std::string>::iterator> m_itrMap;
};

//allow duplicates of urls
//list<pair<url,timeIdx>> may contain nodes w/ duplicated urls but distinct time indices, where nodes in the back of list out of time window can be evicted
//use set<pair<url,count>> to keep track of distinct urls sorted by their counts, so the K most frequent urls can be queried
class URLHistory2
{
	struct GreaterComp
	{
		bool operator()(const std::pair<std::string, int> & a, const std::pair<std::string, int> & b)
		{
			//for unique keys that appear in a pair type:
			//must compare both fields in the pair
			//otherwise, the field that is not compared won't contribute to the uniqueness if just compare only one field
			return a.second != b.second ? a.second > b.second : a.first > b.first;
		}
	};
	int m_capacity;
	int m_timeWindow;
	std::list<std::pair<std::string, int>> m_list;//first: url, second: time index
	std::set<std::pair<std::string, int>, GreaterComp> m_sorted;//first: url, second: count. (composite key: url for uniqueness, count for sorting)
	std::unordered_map<std::string, std::set<std::pair<std::string, int>, GreaterComp>::iterator> m_itrMap;//first: url, second: itr to m_sorted

public:
	URLHistory2(int capacity, int timeWindow) : m_capacity(capacity), m_timeWindow(timeWindow) {}
	~URLHistory2(){}
private:
	void RemoveOldestUrl()
	{
		if (m_list.empty())
			return;
		//the way to modify a key in a set is to erase and insert
		auto itr = m_itrMap[m_list.back().first];//check how many duplicates of m_list.back().first, then modify a key in m_sorted by erase and insert
		auto p = *itr;
		m_sorted.erase(itr);//erase from m_sorted anyway
		if (p.second == 1)//m_list.back().first has no duplicates, no need to insert back
		{
			m_itrMap.erase(m_list.back().first);
		}
		else//m_list.back().first has duplicates, insert back with decremented key
		{
			auto itrPair = m_sorted.insert({ p.first, p.second - 1 });
			m_itrMap[m_list.back().first] = itrPair.first;
		}
		m_list.pop_back();
	}
public:
	void Visit(const std::string & url, int timeIndex)
	{
		//1. remove all url that are out of time window from back of m_list
		while (!m_list.empty())
		{
			int oldestTimeIdx = m_list.back().second;
			if (oldestTimeIdx < timeIndex - m_timeWindow)
				this->RemoveOldestUrl();
			else
				break;
		}

		//2. remove oldest url if capacity is full
		if (m_capacity == (int)m_list.size())
		{
			this->RemoveOldestUrl();
		}
		
		//3. insert url to m_sorted and m_itrMap
		if (m_itrMap.find(url) != m_itrMap.end())//url already exists in history: modify a key in m_sorted by erase and insert
		{
			auto itr = m_itrMap[url];
			int oldCount = itr->second;
			m_sorted.erase(itr);
			auto itrPair = m_sorted.insert({ url, oldCount + 1 });
			m_itrMap[url] = itrPair.first;
		}
		else//url doesn't exist in history: just insert in m_sorted
		{
			auto itrPair = m_sorted.insert({ url, 1 });
			m_itrMap[url] = itrPair.first;
		}

		//4. push url to m_list
		m_list.push_front({ url, timeIndex });
	}
	std::list<std::string> GetHistory() const
	{
		std::list<std::string> res;
		for (const auto & p : m_list)
			res.push_back(p.first);
		return res;
	}
	std::list<std::string> GetKMostCommon(int k) const
	{
		std::list<std::string> res;
		auto itr = m_sorted.cbegin();
		for (int i = 0; i < k && itr != m_sorted.cend(); ++i, ++itr)
		{
			res.push_back(itr->first);
		}
		return res;
	}

	void Print()
	{
		std::cout << "URLHistory2: " << Debug::ToStr1D<std::string, int>()(m_list)
			<< ", 5MostCommon: " << Debug::ToStr1D<std::string>()(this->GetKMostCommon(5)) << std::endl;
	}
};
#endif