#ifndef FIRST_UNIQUE_CHAR_IN_STRING_H
#define FIRST_UNIQUE_CHAR_IN_STRING_H
#include "Debug.h"
/*
Leetcode: First Unique Character in a String
Given a string, find the first non-repeating character in it and return it's index.
If it doesn't exist, return -1.
Examples:
s = "leetcode"
return 0.
s = "loveleetcode",
return 2.
Note: You may assume the string contain only lowercase letters.
Leetcode: First Unique Number
You have a queue of integers, you need to retrieve the first unique integer in the queue.
Implement the FirstUnique class:
FirstUnique(int[] nums) Initializes the object with the numbers in the queue.
int showFirstUnique() returns the value of the first unique integer of the queue, and returns -1 if there is no such integer.
void add(int value) insert value to the queue.
see also FirstUniqueURL.h
*/
class FirstUniqueCharInString
{
public:
	FirstUniqueCharInString() {}

	int UseHashMapAndList(std::string s)
	{
		//similar to LRUCache
		std::list<int> charList;//list of idx of chars that appear for only once
		std::vector<std::pair<int, std::list<int>::iterator>> charMap(26, { 0,charList.end() });//count, itr to list
		int N = s.size();
		for (int i = 0; i < N; ++i)
		{
			++charMap[s[i] - 'a'].first;
			if (charMap[s[i] - 'a'].first == 2)
			{
				charList.erase(charMap[s[i] - 'a'].second);
				//charMap[s[i]-'a'].second = charList.end();
			}
			if (charMap[s[i] - 'a'].first == 1)
			{
				charList.push_back(i);
				charMap[s[i] - 'a'].second = std::prev(charList.end());
			}
		}
		if (charList.empty()) return -1;
		return charList.front();
	}

	int UseHashMap(std::string s)
	{
		std::vector<int> count(26, 0);
		int N = s.size();
		for (int i = 0; i < N; ++i)
			++count[s[i]-'a'];
		for (int i = 0; i < N; ++i)
			if (count[s[i]-'a'] == 1)
				return i;
		return -1;
	}
};
class FirstUniqueNumber
{
    std::list<int> L;
    std::unordered_map<int,std::list<int>::iterator> M;
public:
    FirstUniqueNumber(std::vector<int> & nums)
    {
        for (auto & n : nums)
            add(n);
    }

    int showFirstUnique()
    {
        if (L.empty()) return -1;
        return *L.begin();
    }

    void add(int val)
    {
        if (!M.count(val))
        {
            L.push_back(val);
            auto itr = std::prev(L.end());
            M.insert({val, itr});
        }
        else
        {
            auto itr = M[val];
            if (itr != L.end())//means val is the second time added
            {
                L.erase(itr);
                M[val] = L.end();//mark val that occurs for the second time
            }
        }
    }
};
#endif
