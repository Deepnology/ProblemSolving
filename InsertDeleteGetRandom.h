#ifndef INSERT_DELETE_GET_RANDOM_H
#define INSERT_DELETE_GET_RANDOM_H
#include "Debug.h"
/*
Leetcode: Insert Delete Get Random O(1)
Design a data structure that supports all following operations in average O(1) time.
insert(val): Inserts an item val to the set if not already present.
remove(val): Removes an item val from the set if present.
getRandom: Returns a random element from current set of elements. Each element must have the same probability of being returned.

Example:
// Init an empty set.
RandomizedSet randomSet = new RandomizedSet();

// Inserts 1 to the set. Returns true as 1 was inserted successfully.
randomSet.insert(1);

// Returns false as 2 does not exist in the set.
randomSet.remove(2);

// Inserts 2 to the set, returns true. Set now contains [1,2].
randomSet.insert(2);

// getRandom should return either 1 or 2 randomly.
randomSet.getRandom();

// Removes 1 from the set, returns true. Set now contains [2].
randomSet.remove(1);

// 2 was already in the set, so return false.
randomSet.insert(2);

// Since 1 is the only number in the set, getRandom always return 1.
randomSet.getRandom();


Leetcode: Insert Delete Get Random O(1) - Duplicates allowed
Design a data structure that supports all following operations in average O(1) time.
Note: Duplicate elements are allowed.
insert(val): Inserts an item val to the collection.
remove(val): Removes an item val from the collection if present.
getRandom: Returns a random element from current collection of elements. The probability of each element being returned is linearly related to the number of same value the collection contains.

Example:
// Init an empty collection.
RandomizedCollection collection = new RandomizedCollection();

// Inserts 1 to the collection. Returns true as the collection did not contain 1.
collection.insert(1);

// Inserts another 1 to the collection. Returns false as the collection contained 1. Collection now contains [1,1].
collection.insert(1);

// Inserts 2 to the collection, returns true. Collection now contains [1,1,2].
collection.insert(2);

// getRandom should return 1 with the probability 2/3, and returns 2 with the probability 1/3.
collection.getRandom();

// Removes 1 from the collection, returns true. Collection now contains [1,2].
collection.remove(1);

// getRandom should return 1 and 2 both equally likely.
collection.getRandom();

Google
http://www.glassdoor.com/Interview/1-Count-the-number-of-positive-integers-less-than-N-that-does-not-contains-digit-4-2-Design-a-data-structure-that-can-d-QTN_499877.htm
http://stackoverflow.com/questions/5682218/data-structure-insert-remove-contains-get-random-element-all-at-o1
Design a data structure that can do the following in O(1) time: 1. insert 2. remove 3. contain 4. getRandom
Use a doubly linked list, where each node contains the value, and a hash map, where the key is the value and value is the iterator to that value in the doubly linked list.
*/
class InsertDeleteGetRandom
{
	std::unordered_map<int, int> entryToIndex;//first: entry, second: index in entries vector
	std::vector<int> entries;
public:
	/** Initialize your data structure here. */
	InsertDeleteGetRandom() {}
	~InsertDeleteGetRandom() {}

	/** Inserts a value to the collection. Returns true if the collection did not already contain the specified element. */
	bool insert(int val)
	{
		bool found = entryToIndex.find(val) != entryToIndex.end();
		if (!found)
		{
			entryToIndex[val] = entries.size();
			entries.push_back(val);
		}
		
		std::cout << "InsertDeleteGetRandom insert \"" << val << "\": " << !found << std::endl;
		return !found;
	}

	/** Removes a value from the collection. Returns true if the collection contained the specified element. */
	bool remove(int val)
	{
		if (entryToIndex.find(val) == entryToIndex.end())
		{
			std::cout << "InsertDeleteGetRandom remove \"" << val << "\": " << 0 << std::endl;
			return false;
		}

		int last = entries.back(); entries.pop_back();
		if (last != val)
		{
			//find idx in entries whose value is val
			//then move last to idx in entries
			int idx = entryToIndex[val];
			entries[idx] = last;
			entryToIndex[last] = idx;
		}
		entryToIndex.erase(val);

		std::cout << "InsertDeleteGetRandom remove \"" << val << "\": " << 1 << std::endl;
		return true;
	}

	/** Get a random element from the collection. */
	int getRandom()
	{
		int res = entries[std::rand() % entries.size()];

		std::cout << "InsertDeleteGetRandom getRandom: " << res << std::endl;
		return res;
	}
};
class InsertDeleteGetRandomDupAllowed
{
	std::unordered_map<int, std::unordered_set<int>> entryToIndices;//first: entry, second: a set of indices in entries vector
	std::vector<int> entries;
public:
	/** Initialize your data structure here. */
	InsertDeleteGetRandomDupAllowed() {}
	~InsertDeleteGetRandomDupAllowed() {}

	/** Inserts a value to the collection. Returns true if the collection did not already contain the specified element. */
	bool insert(int val)
	{
		bool found = entryToIndices.find(val) != entryToIndices.end();
		entryToIndices[val].insert(entries.size());
		entries.push_back(val);

		std::cout << "InsertDeleteGetRandomDupAllowed insert \"" << val << "\": " << !found << std::endl;
		return !found;
	}

	/** Removes a value from the collection. Returns true if the collection contained the specified element. */
	bool remove(int val)
	{
		if (entryToIndices.find(val) == entryToIndices.end())
		{
			std::cout << "InsertDeleteGetRandomDupAllowed remove \"" << val << "\": " << 0 << std::endl;
			return false;
		}

		int last = entries.back(); entries.pop_back();
		entryToIndices[last].erase(entries.size());
		if (last != val)
		{
			//find an arbitrary idx in entries whose value is val
			//then move last to idx in entries
			int idx = *entryToIndices[val].begin();
			entryToIndices[val].erase(idx);
			entryToIndices[last].insert(idx);
			entries[idx] = last;
		}
		if (entryToIndices[val].empty())
			entryToIndices.erase(val);

		std::cout << "InsertDeleteGetRandomDupAllowed remove \"" << val << "\": " << 1 << std::endl;
		return true;
	}

	/** Get a random element from the collection. */
	int getRandom()
	{
		int res = entries[std::rand() % entries.size()];

		std::cout << "InsertDeleteGetRandomDupAllowed getRandom: " << res << std::endl;
		return res;
	}
};
/*
InsertDeleteGetRandom insert "1": 1
InsertDeleteGetRandom remove "2": 0
InsertDeleteGetRandom insert "2": 1
InsertDeleteGetRandom getRandom: 2
InsertDeleteGetRandom remove "1": 1
InsertDeleteGetRandom insert "2": 0
InsertDeleteGetRandom getRandom: 2
InsertDeleteGetRandomDupAllowed insert "1": 1
InsertDeleteGetRandomDupAllowed insert "1": 0
InsertDeleteGetRandomDupAllowed insert "2": 1
InsertDeleteGetRandomDupAllowed getRandom: 1
InsertDeleteGetRandomDupAllowed remove "1": 1
InsertDeleteGetRandomDupAllowed getRandom: 2
*/
#endif
