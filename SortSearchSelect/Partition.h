#ifndef PARTITION_H
#define PARTITION_H
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <vector>
/*
1. Partition
http://rosettacode.org/wiki/Sorting_algorithms/Quicksort#C
http://homepage.cs.uiowa.edu/~sriram/21/fall05/ExamplePrograms/ReaderFiles/Chap07/partition/partition.java
std::partition
template <class ForwardIterator, class UnaryPredicate>
ForwardIterator partition (ForwardIterator first, ForwardIterator last, UnaryPredicate pred);

Rearranges the elements from the range [first,last), in such a way that all the elements for which pred returns true precede all those for which it returns false. 
The iterator returned points to the first element of the second group.

The relative ordering within each group is not necessarily the same as before the call. 

Return:
An iterator that points to the first element of the second group of elements (those for which pred returns false), or last if this group is empty.

std::nth_element (a special case of std::partition)
template <class RandomAccessIterator, class Compare>
void nth_element (RandomAccessIterator first, RandomAccessIterator nth, RandomAccessIterator last, Compare comp);

Rearranges the elements in the range [first,last), in such a way that the element at the nth position is the element that would be in that position in a sorted sequence.
The other elements are left without any specific order, except that none of the elements preceding nth are greater than it, and none of the elements following it are less.

Return:
none

O(last - first + 1) time

2. ThreeWayPartition:
Elements of programming interview, Arrays: The Dutch national flag problem
Write a function that takes an array A of length n and an index i into A, and rearranges the elements such that all elements less than A[i] appear first, followed by elements equal to A[i], followed by elements greater than A[i].
*/
class Partition
{
public:
	Partition(){}
	~Partition(){}
	/*return an index that points to the first element, which is also the pivotVal, of the second group of elements*/
	int SmallerThanPivot(int A[], int first, int last, int pivot)
	{
		int pivotVal = A[pivot];
		std::swap(A[pivot], A[last]);
		int i = first;
		int j = last;
		while (i <= j)
		{
			if (A[i] < pivotVal)
				++i;
			else if (!(A[j] < pivotVal))
				--j;
			else
				std::swap(A[i++], A[j--]);
		}
		//now i > j 
		//i is the first element of the second group elements (those for which not smaller than pivot)
		//i should be the correct position to place the pivot element
		//std::cout << A[j] << "...." << A[i] << std::endl;
		std::swap(A[i], A[last]);
		return i;
	}

	int SmallerThanPivot2(int A[], int first, int last, int pivot)
	{
		int pivotVal = A[pivot];
		std::swap(A[pivot], A[last]);
		int curFrontCount = first;
		for (int i = first; i <= last; ++i)
		{
			if (A[i] < pivotVal)
			{
				std::swap(A[curFrontCount++], A[i]);
			}
			//curFrontCount points to the leftmost element that is >= pivotVal
		}
		//now:
		//all elements on res's left side: < pivotVal
		//all elements on res's right side: >= pivotVal
		//the element on res: >= pivotVal
		std::swap(A[curFrontCount], A[last]);
		//now the element on curFrontCount: == pivotVal
		return curFrontCount;
	}

	/*return an index that points to the first element, which is not necessarily the pivotVal, of the second group of elements*/
	int SmallerThanPivotVal(int A[], int first, int last, int pivotVal)
	{
		int i = first;
		int j = last;
		while (i <= j)
		{
			if (A[i] < pivotVal)
				++i;
			else if (!(A[j] < pivotVal))
				--j;
			else
				std::swap(A[i++], A[j--]);
		}
		/*
		now i > j and i points to the first element of the second group
		make sure the first element of the second group A[i] is also the smallest element of the second group
		*/
		for (int k = i; k <= last; ++k)
		{
			if (!(A[i] < A[k]))
				std::swap(A[i], A[k]);
		}
		return i;
	}
	int SmallerThanPivotVal2(int A[], int first, int last, int pivotVal)
	{
		int curFrontCount = first;
		for (int i = first; i <= last; ++i)
		{
			if (A[i] < pivotVal)
			{
				std::swap(A[curFrontCount++], A[i]);
			}
		}
		/*
		now curFrontCount points to the first element of the second group
		make sure the first element of the second group A[curFrontCount] is also the smallest element of the second group
		*/
		for (int i = curFrontCount; i <= last; ++i)
		{
			if (!(A[curFrontCount] < A[i]))
				std::swap(A[curFrontCount], A[i]);
		}
		return curFrontCount;
	}


	std::pair<int, int> ThreeWay_SmallerThan2PivotVals(int A[], int first, int last, int pivotVal1, int pivotVal2)
	{
		if (pivotVal1 > pivotVal2)
			std::swap(pivotVal1, pivotVal2);
		//now pivotVal1 <= pivotVal2

		int curFrontCount = first;
		int curBackCount = last;
		int i = first;
		while (i <= curBackCount)
		{
			if (A[i] < pivotVal1)
			{
				std::swap(A[curFrontCount++], A[i++]);
			}
			else if (A[i] < pivotVal2)
			{
				++i;
			}
			else
			{
				std::swap(A[curBackCount--], A[i]);
			}
		}
		return std::make_pair(curFrontCount, ++curBackCount);
	}

	std::pair<int, int> ThreeWay_SmallerEqualGreaterThanPivot(int A[], int first, int last, int pivot)
	{
		int pivotVal = A[pivot];

		int curFrontCount = first;
		int curBackCount = last;
		int i = first;
		while (i <= curBackCount)
		{
			if (A[i] < pivotVal)
			{
				std::swap(A[curFrontCount++], A[i++]);
			}
			else if (A[i] == pivotVal)
			{
				++i;
			}
			else
			{
				std::swap(A[curBackCount--], A[i]);
			}
		}
		return std::make_pair(curFrontCount, ++curBackCount);
	}

	std::vector<int> FourWay_SmallerThan3PivotVals(int A[], int first, int last, int pivotVal1, int pivotVal2, int pivotVal3)
	{
		if (pivotVal1 > pivotVal2)
			std::swap(pivotVal1, pivotVal2);
		if (pivotVal3 < pivotVal1)
		{
			std::swap(pivotVal3, pivotVal1);
			std::swap(pivotVal2, pivotVal3);
		}
		else if (pivotVal3 < pivotVal2)
			std::swap(pivotVal3, pivotVal2);

		int curFrontCount = first;
		int i2 = first;
		int i3 = last;
		int curBackCount = last;
		while (i2 <= i3)
		{
			if (A[i2] < pivotVal1)
			{
				std::swap(A[curFrontCount++], A[i2++]);
			}
			else if (A[i2] < pivotVal2)
			{
				++i2;
			}
			else
			{
				std::swap(A[i2], A[i3]);
				if (A[i3] >= pivotVal3)
					std::swap(A[i3], A[curBackCount--]);
				--i3;
			}
		}

		return{ curFrontCount, ++i3, ++curBackCount };
	}
};
/*
Partition Pivot: 1, "41, 67, 34, 0, 69, 24, 78, 58, 62, 64, 5, 45, 81, 27, 61" => "41, 61, 34, 0, 27, 24, 45, 58, 62, 64, 5, 67, 81, 69, 78". pivot: 11
Partition Pivot2: 1, "41, 67, 34, 0, 69, 24, 78, 58, 62, 64, 5, 45, 81, 27, 61" => "41, 61, 34, 0, 24, 58, 62, 64, 5, 45, 27, 67, 81, 78, 69". pivot: 11
Partition PivotVal: 68, "41, 67, 34, 0, 69, 24, 78, 58, 62, 64, 5, 45, 81, 27, 61" => "41, 67, 34, 0, 61, 24, 27, 58, 62, 64, 5, 45, 69, 81, 78". pivot: 12
Partition PivotVal2: 68, "41, 67, 34, 0, 69, 24, 78, 58, 62, 64, 5, 45, 81, 27, 61" => "41, 67, 34, 0, 24, 58, 62, 64, 5, 45, 27, 61, 69, 81, 78". pivot: 12
ThreeWayPartition 2PivotVals: 35, 68, "41, 67, 34, 0, 69, 24, 78, 58, 62, 64, 5, 45, 81, 27, 61" => "34, 0, 24, 27, 5, 41, 67, 58, 62, 64, 61, 45, 81, 78, 69". pivots: 5, 12
ThreeWayPartition Pivot: 67, "41, 67, 34, 67, 69, 24, 78, 58, 73, 67, 5, 45, 81, 27, 67" => "41, 34, 24, 27, 58, 45, 5, 67, 67, 67, 67, 81, 73, 78, 69". pivots: 7, 11
FourWayPartition 3PivotVals: 25, 50, 75, "62, 27, 20, 28, 75, 59, 28, 56, 58, 87, 88, 84, 75, 14, 94" => "14, 20, 27, 28, 28, 59, 56, 58, 62, 87, 88, 84, 75, 75, 94". pivots: 2, 5, 9
*/
#endif