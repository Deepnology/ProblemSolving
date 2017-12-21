#ifndef COUNTING_SORT_2_H
#define COUNTING_SORT_2_H
#include <vector>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <iostream>
#include <string>
#include "Debug.h"
/*
Elements of programming interview, Sorting: Implement counting sort
(This is a generalized counting sort algorithm that needs to distinguish entries with same keys, and with limited memory of number of distinct entries.)
Suppose you need to reorder the elements of a very large array so that equal elements appear together.
If the number of distinct elements is very small relative to the size of the array
, an efficient approach to sorting the array is to count the number of occurrences of each distinct element
and write the appropriate number of each element, in sorted order, to the array.

You are given an array of n Person objects.
Each Person object has a field key.
Rearrange the elements of the array so that Person objects with equal keys appear together.
The order in which distinct keys appear is not important.
Your algorithm must run in O(n) time and O(m) space, where m is the number of distinct entries.
How would your solution change if keys have to appear in sorted order?

GroupSameKeys: O(n) time, O(m) space, where m is the number of distinct entries
Sort: O(n + mlogm) time, O(m) space, where m is the number of distinct entries
      O(nlogn) time, O(n) space, when m == n for regular sort

See also FirstMissingPositive.h, FrequencyOfIdxSeqArray.h
*/
class CountingSort2
{
public:
	CountingSort2(){}
	~CountingSort2(){}

	void GroupSameKeys(std::vector<std::pair<int, std::string> > & v)
	{
		std::string before = Debug::ToStr1D<int, std::string>()(v);
		std::unordered_map<int, int> keyToCount;//first: key, second: count of key
		for (const auto & p : v)
			++keyToCount[p.first];
		std::unordered_map<int, int> keyToIndex;//first: key, second: desired starting index in v
		int index = 0;
		for (const auto & p : keyToCount)
		{
			keyToIndex[p.first] = index;
			index += p.second;
		}
		
		//keep moving the key with the lowest index that is unsorted from keyToIndex to its target position, and decrementing/removing that key from keyToCount and kyeToIndex until keyToIndex is empty
		while (keyToIndex.size())
		{
			auto keyWLowestIdx = keyToIndex.begin();//the lowest index that is unsorted
			int curFrontKey = v[keyWLowestIdx->second].first;//the current key in the front that is going to be moved
			auto curFrontKeyTgtIdx = keyToIndex.find(curFrontKey);
			std::swap(v[keyWLowestIdx->second], v[curFrontKeyTgtIdx->second]);//move the current key in the front to its target index

			std::cout << keyWLowestIdx->first << "," << keyWLowestIdx->second << " (moved " << curFrontKeyTgtIdx->first << " to " << curFrontKeyTgtIdx->second << "):	" << Debug::ToStr1D<int, std::string>()(v) << std::endl;

			--keyToCount[curFrontKeyTgtIdx->first];//decrement the count of the key that was moved
			if (keyToCount[curFrontKeyTgtIdx->first] != 0)
			{
				++curFrontKeyTgtIdx->second;//increment the index of the key that was moved
			}
			else
			{
				keyToIndex.erase(curFrontKeyTgtIdx);//remove the key that was moved
			}
		}

		std::cout << "CountingSort2 GroupSameKeys for \"" << before << "\": " << std::endl << Debug::ToStr1D<int, std::string>()(v) << std::endl;
	}

	void SortKeys(std::vector<std::pair<int, std::string> > & v)
	{
		std::string before = Debug::ToStr1D<int, std::string>()(v);
		std::map<int, int> keyToCount;//use map instead of unordered_map. first: key, second: count of the key
		for (const auto & p : v)
			++keyToCount[p.first];
		std::unordered_map<int, int> keyToIndex;//first: key, second: desired starting index in v
		int index = 0;
		for (const auto & p : keyToCount)//now, since all keys in keyToCount are sorted, the starting indices will be assigned based on the sorted order
		{
			keyToIndex[p.first] = index;
			index += p.second;
		}

		while (keyToIndex.size())
		{
			auto pLowestIndex = keyToIndex.begin();
			int keyAtLowestIndex = v[pLowestIndex->second].first;//the key at lowest index in v
			auto pTargetIndex = keyToIndex.find(keyAtLowestIndex);//the desired index of the key at lowest index in v
			std::swap(v[pLowestIndex->second], v[pTargetIndex->second]);//move key at the lowest index to its desired index

			if (--keyToCount[pTargetIndex->first])
			{
				++pTargetIndex->second;
			}
			else
			{
				keyToIndex.erase(pTargetIndex);
			}
		}

		std::cout << "CountingSort2 SortKeys for \"" << before << "\": " << Debug::ToStr1D<int, std::string>()(v) << std::endl;
	}
};
/*
5,0 (moved 5 to 0):		[5,a], [2,b], [6,c], [9,d], [4,e], [5,f], [9,g], [2,h], [5,i], [7,j], [8,k], [6,l], [7,m], [2,n], [9,o], [4,p], [7,q], [8,r], [5,t]
5,1 (moved 2 to 4):		[5,a], [4,e], [6,c], [9,d], [2,b], [5,f], [9,g], [2,h], [5,i], [7,j], [8,k], [6,l], [7,m], [2,n], [9,o], [4,p], [7,q], [8,r], [5,t]
5,1 (moved 4 to 12):	[5,a], [7,m], [6,c], [9,d], [2,b], [5,f], [9,g], [2,h], [5,i], [7,j], [8,k], [6,l], [4,e], [2,n], [9,o], [4,p], [7,q], [8,r], [5,t]
5,1 (moved 7 to 14):	[5,a], [9,o], [6,c], [9,d], [2,b], [5,f], [9,g], [2,h], [5,i], [7,j], [8,k], [6,l], [4,e], [2,n], [7,m], [4,p], [7,q], [8,r], [5,t]
5,1 (moved 9 to 9):		[5,a], [7,j], [6,c], [9,d], [2,b], [5,f], [9,g], [2,h], [5,i], [9,o], [8,k], [6,l], [4,e], [2,n], [7,m], [4,p], [7,q], [8,r], [5,t]
5,1 (moved 7 to 15):	[5,a], [4,p], [6,c], [9,d], [2,b], [5,f], [9,g], [2,h], [5,i], [9,o], [8,k], [6,l], [4,e], [2,n], [7,m], [7,j], [7,q], [8,r], [5,t]
5,1 (moved 4 to 13):	[5,a], [2,n], [6,c], [9,d], [2,b], [5,f], [9,g], [2,h], [5,i], [9,o], [8,k], [6,l], [4,e], [4,p], [7,m], [7,j], [7,q], [8,r], [5,t]
5,1 (moved 2 to 5):		[5,a], [5,f], [6,c], [9,d], [2,b], [2,n], [9,g], [2,h], [5,i], [9,o], [8,k], [6,l], [4,e], [4,p], [7,m], [7,j], [7,q], [8,r], [5,t]
5,1 (moved 5 to 1):		[5,a], [5,f], [6,c], [9,d], [2,b], [2,n], [9,g], [2,h], [5,i], [9,o], [8,k], [6,l], [4,e], [4,p], [7,m], [7,j], [7,q], [8,r], [5,t]
5,2 (moved 6 to 7):		[5,a], [5,f], [2,h], [9,d], [2,b], [2,n], [9,g], [6,c], [5,i], [9,o], [8,k], [6,l], [4,e], [4,p], [7,m], [7,j], [7,q], [8,r], [5,t]
5,2 (moved 2 to 6):		[5,a], [5,f], [9,g], [9,d], [2,b], [2,n], [2,h], [6,c], [5,i], [9,o], [8,k], [6,l], [4,e], [4,p], [7,m], [7,j], [7,q], [8,r], [5,t]
5,2 (moved 9 to 10):	[5,a], [5,f], [8,k], [9,d], [2,b], [2,n], [2,h], [6,c], [5,i], [9,o], [9,g], [6,l], [4,e], [4,p], [7,m], [7,j], [7,q], [8,r], [5,t]
5,2 (moved 8 to 17):	[5,a], [5,f], [8,r], [9,d], [2,b], [2,n], [2,h], [6,c], [5,i], [9,o], [9,g], [6,l], [4,e], [4,p], [7,m], [7,j], [7,q], [8,k], [5,t]
5,2 (moved 8 to 18):	[5,a], [5,f], [5,t], [9,d], [2,b], [2,n], [2,h], [6,c], [5,i], [9,o], [9,g], [6,l], [4,e], [4,p], [7,m], [7,j], [7,q], [8,k], [8,r]
5,2 (moved 5 to 2):		[5,a], [5,f], [5,t], [9,d], [2,b], [2,n], [2,h], [6,c], [5,i], [9,o], [9,g], [6,l], [4,e], [4,p], [7,m], [7,j], [7,q], [8,k], [8,r]
5,3 (moved 9 to 11):	[5,a], [5,f], [5,t], [6,l], [2,b], [2,n], [2,h], [6,c], [5,i], [9,o], [9,g], [9,d], [4,e], [4,p], [7,m], [7,j], [7,q], [8,k], [8,r]
5,3 (moved 6 to 8):		[5,a], [5,f], [5,t], [5,i], [2,b], [2,n], [2,h], [6,c], [6,l], [9,o], [9,g], [9,d], [4,e], [4,p], [7,m], [7,j], [7,q], [8,k], [8,r]
5,3 (moved 5 to 3):		[5,a], [5,f], [5,t], [5,i], [2,b], [2,n], [2,h], [6,c], [6,l], [9,o], [9,g], [9,d], [4,e], [4,p], [7,m], [7,j], [7,q], [8,k], [8,r]
7,16 (moved 7 to 16):	[5,a], [5,f], [5,t], [5,i], [2,b], [2,n], [2,h], [6,c], [6,l], [9,o], [9,g], [9,d], [4,e], [4,p], [7,m], [7,j], [7,q], [8,k], [8,r]
CountingSort2 GroupSameKeys for "[5,a], [2,b], [6,c], [9,d], [4,e], [5,f], [9,g], [2,h], [5,i], [7,j], [8,k], [6,l], [7,m], [2,n], [9,o], [4,p], [7,q], [8,r], [5,t]":
[5,a], [5,f], [5,t], [5,i], [2,b], [2,n], [2,h], [6,c], [6,l], [9,o], [9,g], [9,d], [4,e], [4,p], [7,m], [7,j], [7,q], [8,k], [8,r]
CountingSort2 SortKeys for "[5,a], [2,b], [6,c], [9,d], [4,e], [5,f], [9,g], [2,h], [5,i], [7,j], [8,k], [6,l], [7,m], [2,n], [9,o], [4,p], [7,q], [8,r], [5,t]": [2,n], [2,b], [2,h], [4,p], [4,e], [5,a], [5,f], [5,t], [5,i], [6,l], [6,c], [7,q], [7,j], [7,m], [8,k], [8,r], [9,g], [9,o], [9,d]
*/
#endif