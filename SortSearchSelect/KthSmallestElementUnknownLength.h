#ifndef KTH_SMALLEST_ELEMENT_UNKNOWN_LENGTH_H
#define KTH_SMALLEST_ELEMENT_UNKNOWN_LENGTH_H
#include <vector>
#include <iostream>
#include <istream>
#include <string>
#include <queue>
#include <algorithm>
#include <functional>
#include "Debug.h"
/*
Elements of programming interview, Heaps: Compute the K closest stars, variant
Elements of programming interview, Searching: Find the K-th largest element--large N, small K

Design an algorithm for computing the k-th smallest element in a sequence of elements.
It should run in O(n) expected time where n is the length of the sequence, which is not known in advance.
The value k is known in advance.
Your algorithm should print the k-th smallest element after the sequence has ended.
It should use O(k) additional storage.

BruteForce_MaxHeap: O(nlogk) time, O(k) space
ModifiedSelection: O(n) time, O(k) space

Keep the k smallest elements in an array M of length 2k-1.
We add elements to M, and each time M is full, we find k smallest elements using the selection algorithm.
The larger elements are discarded, and we continue.
The selection algorithm takes O(k) time and is run every k-1 elements, implying an O(n) time complexity.

See also BinarySearchUnknownLength.h
*/
class KthSmallestElementUnknownLength
{
public:
	KthSmallestElementUnknownLength(){}
	~KthSmallestElementUnknownLength(){}

	int BruteForce_MaxHeap(std::istringstream && iss, int K)
	{
		std::string before = iss.str();
		std::priority_queue<int, std::vector<int>, std::less<int> > maxHeap;
		int buf;
		while (iss >> buf)
		{
			if ((int)maxHeap.size() < K)
			{
				maxHeap.push(buf);
			}
			else if (buf < maxHeap.top())
			{
				maxHeap.pop();
				maxHeap.push(buf);
			}
		}
		std::cout << "KthSmallestElementUnknownLength BruteForce_MaxHeap for \"" << K << "-th\" in \"" << before << "\": " << maxHeap.top() << ", [" << Debug::ToStr1D<int>()(maxHeap) << "]" << std::endl;
		return maxHeap.top();
	}

	int ModifiedSelection(std::istringstream && iss, int K)
	{
		std::string before = iss.str();
		std::vector<int> KthSmallest;
		int buf;
		while (iss >> buf)
		{
			KthSmallest.push_back(buf);
			if ((int)KthSmallest.size() == (K * 2) - 1)
			{
				/*rearrange the array such the Kth smallest element is placed at index K-1*/
				std::nth_element(KthSmallest.begin(), KthSmallest.begin() + K - 1, KthSmallest.end(), std::less<int>());
				/*remove those elements that are greater than the Kth smallest element*/
				KthSmallest.resize(K);
			}
		}
		/*rearrange the array such the Kth smallest element is placed at index K-1*/
		std::nth_element(KthSmallest.begin(), KthSmallest.begin() + K - 1, KthSmallest.end(), std::less<int>());

		std::cout << "KthSmallestElementUnknownLength ModifiedSelection for \"" << K << "-th\" in \"" << before << "\": " << KthSmallest[K - 1] << ", [" << Debug::ToStr1D<int>()(KthSmallest) << "]" << std::endl;
		return KthSmallest[K - 1];
	}
};
/*
QuickSort for "3, 9, 8, 7, 6, -5, -5, 13, -2, -1, -7, -9, 5, 4, 4, 11, 2, 12, 1, 14, 20, 19, 17, 16, 18, -3, -4, -6, 21, 11, 13, 15, 16, 24" is: -9, -7, -6, -5, -5, -4, -3, -2, -1, 1, 2, 3, 4, 4, 5, 6, 7, 8, 9, 11, 11, 12, 13, 13, 14, 15, 16, 16, 17, 18, 19, 20, 21, 24
KthSmallestElementUnknownLength BruteForce_MaxHeap for "8-th" in "3 9 8 7 6 -5 -5 13 -2 -1 -7 -9 5 4 4 11 2 12 1 14 20 19 17 16 18 -3 -4 -6 21 11 13 15 16 24": -2, [-2, -3, -4, -5, -5, -6, -7, -9]
KthSmallestElementUnknownLength ModifiedSelection for "8-th" in "3 9 8 7 6 -5 -5 13 -2 -1 -7 -9 5 4 4 11 2 12 1 14 20 19 17 16 18 -3 -4 -6 21 11 13 15 16 24": -2, [-9, -7, -6, -5, -5, -4, -3, -2, 11, 13, 15, 16, 24]
*/
/*
Note that we use less storage, e.g., an array of length 3k/2, and still achieve O(n) time complexity.
The actual run time would be higher with an array of length 3k/2 since we only discard k/2 elements for each call to the selection algorithm.
This is a classic space-time trade-off.
If we use a 4k long array, we could discard 3k elements for one call to the selection algorithm.
Assuming the time complexity of the selection algorithm is proportional to the length of the array
, using a length 4k array compared to a length 3k/2 array yields a speed-up of (3/2) / ((1/2)/(4/3)) = 2.25.
Clearly more storage leads to faster run times (in the extreme we read all n and do a single selection)
, so there is a trade-off with respect to how much storage we want.
*/

/*
Leetcode: Kth Largest Element in a Stream
Design a class to find the kth largest element in a stream.
Note that it is the kth largest element in the sorted order, not the kth distinct element.
Your KthLargest class will have a constructor which accepts an integer k and an integer array nums, which contains initial elements from the stream.
For each call to the method KthLargest.add, return the element representing the kth largest element in the stream.
Example:
int k = 3;
int[] arr = [4,5,8,2];
KthLargest kthLargest = new KthLargest(3, arr);
kthLargest.add(3);   // returns 4
kthLargest.add(5);   // returns 5
kthLargest.add(10);  // returns 5
kthLargest.add(9);   // returns 8
kthLargest.add(4);   // returns 8
 */
class KthLargestElementInAStream
{
	std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
	int K;
public:
	KthLargestElementInAStream(int k, std::vector<int> nums) : K(k)
	{
		for (const auto & i : nums)
			Add(i);
	}
	int Add(int val)
	{
		minHeap.push(val);
		if (minHeap.size() > K)
			minHeap.pop();
		return minHeap.top();
	}
};
#endif