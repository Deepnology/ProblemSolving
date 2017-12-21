#ifndef HEAP_SORT_H
#define HEAP_SORT_H
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include "Debug.h"
/*
http://rosettacode.org/wiki/Sorting_algorithms/Heapsort#C
http://www.algorithmist.com/index.php/Heap_sort.c
Category: Selection Sort
in-place comparison-based sort
slower than Quick Sort, not stable but with better worse case of O(nlogn)
Best case: O(nlogn)
Average case: O(nlogn)
Worst case: O(nlogn)
Stability: unstable

see also BinaryMinHeap.h, YoungTableau.h
*/
class HeapSort
{
public:
	HeapSort(){}
	~HeapSort(){}

	void GO(std::vector<int> & A)
	{
		std::string before = Debug::ToStr1D<int>()(A);
		int N = A.size();

		/*
		make max heap: parent node must be greater equal to both child nodes. O(nlogn) time, after tighter analysis is O(n) time
		why max heap? we can repeat popping out the top element of a max heap and then insert it to the end of the array for sorting
		why do max heapify from middle to begin? it's a bottom-up manner from the last element in the previous level of leaves (leaves are the 2nd half of the level order array, which can be skipped)
		*/
		for (int i = N / 2; i >= 0; --i)
			this->siftDownRecur(A, i, N - 1);

		std::cout << "MaxHeapify: " << Debug::ToStr1D<int>()(A) << std::endl;

		/*
		sort max heap in the ascending order. O(nlogn) time
		repeat popping out the top element of the max heap and insert it to the running end of the array, without affecting already sorted elements in the back
		insert the element from the running end to top of heap and do max heapify to keep max heap properties in the unsorted range, without affecting already sorted elements in the back
		*/
		for (int i = N - 1; i >= 1; --i)
		{
			std::swap(A[0], A[i]);
			this->siftDownRecur(A, 0, i - 1);
		}

		std::cout << "HeapSort for \"" << before << "\": " << Debug::ToStr1D<int>()(A) << std::endl;
	}
private:
	void siftDownRecur(std::vector<int> & A, int begin, int end)//move begin(root) down recur for maxHeap property, O(log(end-begin)) time
	{
		int leftChild = 2 * begin + 1;
		int rightChild = 2 * begin + 2;
		int maxChild;
		if (rightChild <= end)
		{
			maxChild = A[leftChild] < A[rightChild] ? rightChild : leftChild;
		}
		else if (leftChild <= end)
		{
			maxChild = leftChild;
		}
		else
			return;
		
		if (A[begin] < A[maxChild])
		{
			std::swap(A[begin], A[maxChild]);
			this->siftDownRecur(A, maxChild, end);
		}
	}

public:
	void GO2(std::vector<int> & v)
	{
		std::string before = Debug::ToStr1D<int>()(v);
		/*
		std::make_heap
		Rearranges the elements in the range [first,last) in such a way that they form a heap.
		The element with the highest value is always pointed by first.
		The order of the other elements depends on the particular implementation.
		The elements are compared using operator<.
		The complexity is at most 3*std::distance(first,last) comparisons.
		*/
		std::make_heap(v.begin(), v.end());
		std::cout << "MaxHeapify: " << Debug::ToStr1D<int>()(v) << std::endl;
		/*
		std::sort_heap
		Sorts the elements in the heap range [first,last) into ascending order.
		The elements are compared using operator<.
		The complexity is at most n*logn comparisons where n = std::distance(first, last).
		*/
		std::sort_heap(v.begin(), v.end());
		std::cout << "HeapSort2 wSTL for \"" << before << "\": " << Debug::ToStr1D<int>()(v) << std::endl;
	}

	void GO3(std::vector<int> & v)
	{
		std::string before = Debug::ToStr1D<int>()(v);
		/*
		std::make_heap
		Rearranges the elements in the range [first,last) in such a way that they form a heap.
		The element with the highest value is always pointed by first.
		The order of the other elements depends on the particular implementation.
		The elements are compared using operator<.
		The complexity is at most 3*std::distance(first,last) comparisons.
		*/
		std::make_heap(v.begin(), v.end());
		std::cout << "MaxHeapify: " << Debug::ToStr1D<int>()(v) << std::endl;
		std::vector<int>::iterator begin = v.begin();
		std::vector<int>::iterator end = v.end();
		while (begin != end)
			std::pop_heap(begin, end--);
		/*
		std::pop_heap
		Rearranges the elements in the heap range [first,last) in such a way that the part considered a heap is shortened by one:
		The element with the highest value is moved to (last-1).
		While the element with the highest value is moved from first to (last-1) (which now is out of the heap), 
		the other elements are reorganized in such a way that the range [first,last-1) preserves the properties of a heap.
		The complexity is at most 2*logn comparisons where n = std::distance(first, last).
		*/
		
		std::cout << "HeapSort3 wSTL for \"" << before << "\": " << Debug::ToStr1D<int>()(v) << std::endl;
	}
};
/*
MaxHeapify: 81, 69, 78, 62, 67, 45, 61, 58, 0, 64, 5, 34, 24, 27, 41
HeapSort for "41, 67, 34, 0, 69, 24, 78, 58, 62, 64, 5, 45, 81, 27, 61": 0, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 81
MaxHeapify: 81, 69, 78, 62, 67, 45, 61, 58, 0, 64, 5, 34, 24, 27, 41
HeapSort2 wSTL for "41, 67, 34, 0, 69, 24, 78, 58, 62, 64, 5, 45, 81, 27, 61": 0, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 81
MaxHeapify: 81, 69, 78, 62, 67, 45, 61, 58, 0, 64, 5, 34, 24, 27, 41
HeapSort3 wSTL for "41, 67, 34, 0, 69, 24, 78, 58, 62, 64, 5, 45, 81, 27, 61": 0, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 81
*/
#endif

/*
std::push_heap
Given a heap in the range [first,last-1), this function extends the range considered a heap to [first,last) by placing the value in (last-1) into its corresponding location within it.
*/