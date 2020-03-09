#ifndef QUICK_SORT_H
#define QUICK_SORT_H
#include <string>
#include <sstream>
#include <iostream>
#include <stack>
#include "Debug.h"
#include "Partition.h"
/*
In-place O(nlogn) time sorting algorithm efficient in random accessed data structures such as array, which has good cache locality of reference.
Tail recursion ensures tail call optimizations by compiler can be done.
Pick a random element and partition the array, such that all numbers that are less than it come before all elements that are greater than it.
Then do that for each half, then each quarter, etc.
Category: Exchange Sort
Also called Partition-Exchange Sort
Divide and conquer
Best case: O(nlogn)
Average case: O(nlogn)
Worst case: O(n^2)
Stability: unstable
*/
class QuickSort
{
public:
	QuickSort(){}
	~QuickSort(){}
	
	void GO_STL(std::vector<int> && A)
	{
		std::string before = Debug::ToStr1D<int>()(A);
		this->RecurSTL(A, 0, A.size() - 1);
		std::string after = Debug::ToStr1D<int>()(A);
		std::cout << "QuickSort STL for \"" << before << "\" is: " << after << std::endl;
	}
private:
	void RecurSTL(std::vector<int> & A, int first, int last)
	{
		if (first >= last)
			return;

		int pivot = (first + last) / 2;
		std::nth_element(A.begin() + first, A.begin() + pivot, A.begin() + last + 1, [](const int & a, const int & b)
		{
			return a < b;
		});
		
		this->RecurSTL(A, first, pivot - 1);//sort A[first]~A[pivot - 1]
		this->RecurSTL(A, pivot + 1, last);//sort A[pivot + 1]~A[last]
	}
	
public:
	void GO(int A[], int n)
	{
		std::string before = Debug::ToStr1D<int>()(A, n);
		this->Recur(A, 0, n - 1);
		std::string after = Debug::ToStr1D<int>()(A, n);
		std::cout << "QuickSort for \"" << before << "\" is: " << after << std::endl;
	}
private:
	void Recur(int A[], int first, int last)
	{
		if (first >= last)
			return;

		int pivot = (first + last) / 2;//select middle (random) element to be the pivot
		pivot = Partition().SmallerThanPivot(A, first, last, pivot);//get the correct pivot index after partition (rearrange)
		
		this->Recur(A, first, pivot - 1);//sort A[first]~A[pivot-1]
		this->Recur(A, pivot + 1, last);//sort A[pivot+1]~A[last]
	}

public:
	void GO2(int A[], int n)
	{
		std::string before = Debug::ToStr1D<int>()(A, n);
		this->Recur2(A, 0, n - 1);
		std::string after = Debug::ToStr1D<int>()(A, n);
		std::cout << "QuickSort2 for \"" << before << "\" is: " << after << std::endl;
	}
private:
	void Recur2(int A[], int first, int last)
	{
		if (first >= last)
			return;

		int pivot = (first + last) / 2;
		pivot = Partition().SmallerThanPivot2(A, first, last, pivot);

		this->Recur2(A, first, pivot - 1);//sort A[first]~A[pivot-1]
		this->Recur2(A, pivot + 1, last);//sort A[pivot+1]~A[last]
	}

public:
	//divide and conquer using a stack!!
	void GO_Iterate(int A[], int n)
	{
		std::string before = Debug::ToStr1D<int>()(A, n);
		std::stack<int> stack;
		stack.push(0);
		stack.push(n - 1);
		while (!stack.empty())
		{
			int last = stack.top();
			stack.pop();
			int first = stack.top();
			stack.pop();
			if (first >= last)
				continue;

			int pivot = (first + last) / 2;
			pivot = Partition().SmallerThanPivot(A, first, last, pivot);

			stack.push(first);
			stack.push(pivot - 1);

			stack.push(pivot + 1);
			stack.push(last);
		}
		std::string after = Debug::ToStr1D<int>()(A, n);
		std::cout << "QuickSort Iterate for \"" << before << "\" is: " << after << std::endl;
	}

};
/*
QuickSort STL for "7, 4, 3, 8, 2, 7, 1, 9, 6, 7, 5, 4, 8" is: 1, 2, 3, 4, 4, 5, 6, 7, 7, 7, 8, 8, 9
QuickSort for "7, 4, 3, 8, 2, 7, 1, 9, 6, 7, 5, 4, 8" is: 1, 2, 3, 4, 4, 5, 6, 7, 7, 7, 8, 8, 9
QuickSort2 for "7, 4, 3, 8, 2, 7, 1, 9, 6, 7, 5, 4, 8" is: 1, 2, 3, 4, 4, 5, 6, 7, 7, 7, 8, 8, 9
QuickSort Iterate for "7, 4, 3, 8, 2, 7, 1, 9, 6, 7, 5, 4, 8" is: 1, 2, 3, 4, 4, 5, 6, 7, 7, 7, 8, 8, 9
*/

#endif