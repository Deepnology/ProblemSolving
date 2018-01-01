#ifndef REMOVE_DUPLICATES_FROM_SORTED_ARRAY_H
#define REMOVE_DUPLICATES_FROM_SORTED_ARRAY_H
#include <iostream>
#include <string>
#include <sstream>
#include "Debug.h"
/*
Elements of programming interview, Array: Delete duplicates from a sorted array
Write a function which takes as input a sorted array A and updates A so that all duplicates have been removed and the remaining elements have been shifted left to fill the emptied indicies.
Return the number of valid elements in A.
Elements of programming interview, Sorting: Find unique elements (EraseUnique)
Suppose you are given a set of names and your job is to produce a set of unique first names.
If you just remove the last name from all the names, you may have some duplicate first names.
Creating a set of first names that has each name occurring only once.
https://github.com/anson627/leetcode/blob/master/RemoveDuplicatesfromSortedArray/RemoveDuplicatesfromSortedArray.cpp
// Remove Duplicates from Sorted Array
// Given a sorted array, remove the duplicates in place such that each element
// appear only once and return the new length.
//
// Do not allocate extra space for another array, you must do this in place
// with constant memory.
//
// For example,
// Given input array A = [1,1,2],
//
// Your function should return length = 2, and A is now [1,2].
//
// Complexity
// O(n) time

https://github.com/anson627/leetcode/blob/master/RemoveDuplicatesfromSortedArrayII/RemoveDuplicatesfromSortedArrayII.cpp
// Remove Duplicates from Sorted Array II
// Follow up for "Remove Duplicates":
// What if duplicates are allowed at most twice?
//
// For example,
// Given sorted array A = [1,1,1,2,2,3],
//
// Your function should return length = 5, and A is now [1,1,2,2,3].
//
// Complexity
// O(n) time

See also RemoveDupsFromUnsortedArray.h
*/
class RemoveDuplicatesFromSortedArray
{
public:
	RemoveDuplicatesFromSortedArray(){}
	~RemoveDuplicatesFromSortedArray(){}

	int AtMostOnce(std::vector<int> && A)
	{
		int n = A.size();
		if (n < 2)
			return n;
		std::cout << Debug::ToStr1D<int>()(A) << std::endl;

		int newEnd = 1;
		for (int oldCur = 1; oldCur < n; ++oldCur)
		{
			if (A[oldCur - 1] != A[oldCur])
				A[newEnd++] = A[oldCur];
		}
		
		std::cout << "RemoveDuplicatesFromSortedArray AtMostOnce: " << Debug::ToStr1D<int>()(A) << std::endl;
		return newEnd;//newEnd is the size after removal
	}

	int AtMostTwice(std::vector<int> && A)
	{
		int n = A.size();
		if (n < 2)
			return n;
		std::cout << Debug::ToStr1D<int>()(A) << std::endl;

		int newEnd = 1;
		bool first = true;
		for (int oldCur = 1; oldCur < n; ++oldCur)
		{
			if (A[oldCur - 1] != A[oldCur])
			{
				A[newEnd++] = A[oldCur];
				first = true;
			}
			else if (first)
			{
				A[newEnd++] = A[oldCur];
				first = false;
			}
		}

		std::cout << "RemoveDuplicatesFromSortedArray AtMostTwice: " << Debug::ToStr1D<int>()(A) << std::endl;
		return newEnd;//newEnd is the size after removal
	}

	void EraseUnique(std::vector<int> && v)
	{
		/*v is sorted (identical elements are neighbors)*/
		std::string before = Debug::ToStr1D<int>()(v);
		/*
		template<class ForwardIterator>
		ForwardIterator std::unique(ForwardIterator first, ForwardIterator last)

		Removes all but the first element from every consecutive group of equivalent elements in the range [first,last).

		The function cannot alter the properties of the object containing the range of elements (i.e., it cannot alter the size of an array or a container): 
		The removal is done by replacing the duplicate elements by the next element that is not a duplicate
		, and signaling the new size of the shortened range by returning an iterator to the element that should be considered its new past-the-end element.

		The relative order of the elements not removed is preserved
		, while the elements between the returned iterator and last are left in a valid but unspecified state.

		The function uses operator== to compare the pairs of elements.

		Return:
		An iterator to the element that follows the last element not removed.
		The range between first and this iterator includes all the elements in the sequence that were not considered duplicates.
		*/
		v.erase(std::unique(v.begin(), v.end()), v.end());//erase-unique, similiar to erase-remove idiom
		std::cout << "RemoveDuplicatesFromSortedArray EraseUnique for \"" << before << "\": " << Debug::ToStr1D<int>()(v) << std::endl;
	}
};
/*
1, 1, 1, 2, 3, 4, 4, 5, 5, 5, 6, 7, 7, 8, 9, 10, 10, 10, 11, 12, 12
RemoveDuplicatesFromSortedArray AtMostOnce: 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 7, 8, 9, 10, 10, 10, 11, 12, 12
1, 1, 1, 2, 3, 4, 4, 5, 5, 5, 6, 7, 7, 8, 9, 10, 10, 10, 11, 12, 12
RemoveDuplicatesFromSortedArray AtMostTwice: 1, 1, 2, 3, 4, 4, 5, 5, 6, 7, 7, 8, 9, 10, 10, 11, 12, 12, 11, 12, 12
RemoveDuplicatesFromSortedArray EraseUnique for "1, 1, 1, 2, 3, 4, 4, 5, 5, 5, 6, 7, 7, 8, 9, 10, 10, 10, 11, 12, 12": 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12
*/
#endif