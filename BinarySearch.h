#ifndef BINARY_SEARCH_H
#define BINARY_SEARCH_H
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, Searching: Search a sorted array for first occurrence of k (lower bound), Search a sorted array for the first element greater than k (upper bound)
http://www.geeksforgeeks.org/the-ubiquitous-binary-search-set-1/
Binary Search on sorted array
see also SearchForRange.h

Memo
UpperBound: when equal, search right
Keep 3 entries: final right is upper bound
Keep 1 entry: final left is upper bound

LowerBound: when equal, search left
Keep 3 entries: final right is lower bound
keep 1 entry: final left is lower bound

applications:
LongestContinuousBinary0s.h, Sqrtx.h, Divide2IntWoMulDivMod.h, IndexOfOnlyOneSetBit.h, Pow.h, XpowYmodZ.h, ValidPerfectSquare.h, RandomFromProbDist.h, Rand1toNExcludeKSortedNum.h
*/
class BinarySearch
{
public:
	int Index_UpperBound(const std::vector<int> & A, int val)
	{
		int left = -1;
		int right = A.size();
		while (right - left > 1)//keep 3 entries between [left,right] inclusive
		{
			int middle = left + (right - left) / 2;
			if (A[middle] <= val)
				left = middle;
			else
				right = middle;
		}

		//now right is the upper bound of val (the index of the leftmost element that compares greater than val)

		if (right == 0)//val out of range on left
		{
			std::cout << "BinarySearch Index_UpperBound for \"" << val << "\" from \"" << Debug::ToStr1D<int>()(A) << "\": " << right << ", Out Of Range On Left" << std::endl;
			return right;
		}
		else if (right == A.size())//val out of range on right
		{
			std::cout << "BinarySearch Index_UpperBound for \"" << val << "\" from \"" << Debug::ToStr1D<int>()(A) << "\": " << right << ", Out Of Range On Right" << std::endl;
			return A.size();
		}
		else if (A[left] == val)//val found, left points to the last duplicate
		{
			std::cout << "BinarySearch Index_UpperBound for \"" << val << "\" from \"" << Debug::ToStr1D<int>()(A) << "\": " << right << ", Found Last Dup: " << left << std::endl;
			return right;
		}
		else//val in range but not found, [left,right] will be the [floor,ceil] index
		{
			std::cout << "BinarySearch Index_UpperBound for \"" << val << "\" from \"" << Debug::ToStr1D<int>()(A) << "\": " << right << ", [Floor,Ceil]: [" << left << "," << right << "]=[" << A[left] << "," << A[right] << "]" << std::endl;
			return right;
		}
	}
	int Index_LowerBound(const std::vector<int> & A, int val)
	{
		int left = -1;
		int right = A.size();
		while (right - left > 1)//keep 3 entries between [left,right] inclusive
		{
			int middle = left + (right - left) / 2;
			if (A[middle] >= val)
				right = middle;
			else
				left = middle;
		}

		//now right is the lower bound of val (the index of the leftmost element that doesn't compare less than val, or say, compares equal to or greater than val)

		if (right == A.size())//val out of range on right
		{
			std::cout << "BinarySearch Index_LowerBound for \"" << val << "\" from \"" << Debug::ToStr1D<int>()(A) << "\": " << right << ", Out Of Range On Right" << std::endl;
			return right;
		}
		else if (right == 0 && A[right] > val)//val out of range on left
		{
			std::cout << "BinarySearch Index_LowerBound for \"" << val << "\" from \"" << Debug::ToStr1D<int>()(A) << "\": " << right << ", Out Of Range On Left" << std::endl;
			return right;
		}
		else if (A[right] == val)//val found, right points to the first duplicate
		{
			std::cout << "BinarySearch Index_LowerBound for \"" << val << "\" from \"" << Debug::ToStr1D<int>()(A) << "\": " << right << ", Found First Dup: " << right << std::endl;
			return right;
		}
		else//val in range but not found, [left,right] will be the [floor,ceil] index
		{
			std::cout << "BinarySearch Index_LowerBound for \"" << val << "\" from \"" << Debug::ToStr1D<int>()(A) << "\": " << right << ", [Floor,Ceil]: [" << left << "," << right << "]=[" << A[left] << "," << A[right] << "]" << std::endl;
			return right;
		}
	}
public:
	int Index_UpperBound2(const std::vector<int> & A, int val)
	{
		int left = 0;
		int right = A.size() - 1;
		while (left < right)//keep 2 entries between [left,right] inclusive
		{
			int middle = (left + right) / 2;//middle will be the left element of the center pair when (left+right) is odd (special case: middle == left when left+1 == right); otherwise, the center element
			if (A[middle] == val)//since we are looking for the upper bound, next search the right side when equal
				left = middle + 1;//since left <= middle, so next left inclusive would be (middle+1)
			else if (A[middle] > val)
				right = middle;//since middle < right, so next right inclusive would be middle
			else
				left = middle + 1;
		}
		if (A[right] <= val)
		{
			left = right + 1;
		}
		//now left is the upper bound of val
		std::string ubval = (left >= 0 && left < (int)A.size()) ? std::to_string(A[left]) : "N";
		std::string lval = (left >= 0 && left < (int)A.size()) ? std::to_string(A[left]) : "N";
		std::string rval = (right >= 0 && right < (int)A.size()) ? std::to_string(A[right]) : "N";
		std::cout << "BinarySearch Index_UpperBound2 for \"" << val << "\" in \"" << Debug::ToStr1D<int>()(A) << "\": " << left << "=" << ubval << ", l: " << left << "=" << lval << ", r: " << right << "=" << rval << std::endl;
		return left;
	}

	/*just a little modification*/
	int Index_UpperBound3(const std::vector<int> & A, int val)
	{
		int left = 0;
		int right = A.size() - 1;
		while (left <= right)//keep 1 entry between [left,right] inclusive
		{
			int middle = (left + right) / 2;
			if (A[middle] <= val)
				left = middle + 1;
			else
				right = middle - 1;
		}
		//now left is the upper bound of val
		std::string ubval = (left >= 0 && left < (int)A.size()) ? std::to_string(A[left]) : "N";
		std::string lval = (left >= 0 && left < (int)A.size()) ? std::to_string(A[left]) : "N";
		std::string rval = (right >= 0 && right < (int)A.size()) ? std::to_string(A[right]) : "N";
		std::cout << "BinarySearch Index_UpperBound3 for \"" << val << "\" in \"" << Debug::ToStr1D<int>()(A) << "\": " << left << "=" << ubval << ", l: " << left << "=" << lval << ", r: " << right << "=" << rval << std::endl;
		return left;
	}

	int Index_LowerBound2(const std::vector<int> & A, int val)
	{
		int left = 0;
		int right = A.size() - 1;
		while (left < right)//keep 2 entries between [left,right] inclusive
		{
			int middle = (left + right) / 2;
			if (A[middle] == val)//since we are looking for the lower bound, next search the left side when equal
				right = middle;
			else if (A[middle] > val)
				right = middle;
			else
				left = middle + 1;
		}
		if (A[right] < val)
		{
			left = right + 1;
		}
		//now left is the lower bound of val
		std::string lbval = (left >= 0 && left < (int)A.size()) ? std::to_string(A[left]) : "N";
		std::string lval = (left >= 0 && left < (int)A.size()) ? std::to_string(A[left]) : "N";
		std::string rval = (right >= 0 && right < (int)A.size()) ? std::to_string(A[right]) : "N";
		std::cout << "BinarySearch Index_LowerBound2 for \"" << val << "\" in \"" << Debug::ToStr1D<int>()(A) << "\": " << left << "=" << lbval << ", l: " << left << "=" << lval << ", r: " << right << "=" << rval << std::endl;
		return left;
	}

	/*just a little modification*/
	int Index_LowerBound3(const std::vector<int> & A, int val)
	{
		int left = 0;
		int right = A.size() - 1;
		while (left <= right)//keep 1 entry between [left,right] inclusive
		{
			int middle = (left + right) / 2;
			if (A[middle] >= val)
				right = middle - 1;
			else
				left = middle + 1;
		}
		//now left is the lower bound of val
		std::string lbval = (left >= 0 && left < (int)A.size()) ? std::to_string(A[left]) : "N";
		std::string lval = (left >= 0 && left < (int)A.size()) ? std::to_string(A[left]) : "N";
		std::string rval = (right >= 0 && right < (int)A.size()) ? std::to_string(A[right]) : "N";
		std::cout << "BinarySearch Index_LowerBound3 for \"" << val << "\" in \"" << Debug::ToStr1D<int>()(A) << "\": " << left << "=" << lbval << ", l: " << left << "=" << lval << ", r: " << right << "=" << rval << std::endl;
		return left;
	}

public:
	int Index_LowerBound_Recur(const std::vector<int> & A, int val)
	{
		int res = this->index_LowerBound_Recur(A, -1, A.size(), val);
		std::cout << "BinarySearch Index_LowerBound_Recur for \"" << val << "\" in \"" << Debug::ToStr1D<int>()(A) << "\": " << res << std::endl;
		return res;
	}
private:
	int index_LowerBound_Recur(const std::vector<int> & A, int left, int right, int val)
	{
		int index;
		if (right - left <= 1)//below 2 entries between [left,right] inclusive
		{
			if (right == (int)A.size())
				index = right;//out of range on right
			else if (right == 0 && A[right] > val)
				index = -1;//out or range on left
			else
				index = right;//found 1st duplicate at right
		}
		else
		{
			int middle = (left + right) / 2;
			if (A[middle] >= val)
				index = this->index_LowerBound_Recur(A, left, middle, val);
			else
				index = this->index_LowerBound_Recur(A, middle, right, val);
		}
		return index;
	}
public:
	int Index_UpperBound_Recur(const std::vector<int> & A, int val)
	{
		int res = this->index_UpperBound_Recur(A, -1, A.size(), val);
		std::cout << "BinarySearch Index_UpperBound_Recur for \"" << val << "\" in \"" << Debug::ToStr1D<int>()(A) << "\": " << res << std::endl;
		return res;
	}
private:
	int index_UpperBound_Recur(const std::vector<int> & A, int left, int right, int val)
	{
		int index;
		if (right - left <= 1)//below 2 entries between [left,right] inclusive
		{
			if (right == 0)
				index = 0;//out of range on left
			else if (right == (int)A.size())
				index = right;//out of range on right
			else
				index = right;//found last duplicate at left
		}
		else
		{
			int middle = (left + right) / 2;
			if (A[middle] <= val)
				index = this->index_UpperBound_Recur(A, middle, right, val);
			else
				index = this->index_UpperBound_Recur(A, left, middle, val);
		}
		return index;
	}
public:
	int Index_Recur(const std::vector<int> & A, int val)
	{
		int res = this->index_Recur(A, 0, A.size() - 1, val);
		std::cout << "BinarySearch Index_Recur for \"" << val << "\" in \"" << Debug::ToStr1D<int>()(A) << "\": " << res << std::endl;
		return res;
	}
private:
	int index_Recur(const std::vector<int> & A, int left, int right, int val)
	{
		int index;
		if (left > right)//0 entries between [left,right] inclusive
			index = -1;
		else
		{
			int middle = (left + right) / 2;
			if (val == A[middle])
				index = middle;
			else if (A[middle] > val)
				index = this->index_Recur(A, left, middle - 1, val);
			else
				index = this->index_Recur(A, middle + 1, right, val);
		}
		return index;
	}
};
/*
BinarySearch Index_UpperBound for "78" from "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": 16, Found Last Dup: 15
BinarySearch Index_UpperBound2 for "78" in "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": 16=81, l: 16=81, r: 16=81
BinarySearch Index_UpperBound3 for "78" in "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": 16=81, l: 16=81, r: 15=78
BinarySearch Index_LowerBound for "78" from "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": 13, Found First Dup: 13
BinarySearch Index_LowerBound2 for "78" in "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": 13=78, l: 13=78, r: 13=78
BinarySearch Index_LowerBound3 for "78" in "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": 13=78, l: 13=78, r: 12=69
BinarySearch Index_UpperBound for "81" from "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": 17, Out Of Range On Right
BinarySearch Index_UpperBound2 for "81" in "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": 17=N, l: 17=N, r: 16=81
BinarySearch Index_UpperBound3 for "81" in "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": 17=N, l: 17=N, r: 16=81
BinarySearch Index_LowerBound for "81" from "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": 16, Found First Dup: 16
BinarySearch Index_LowerBound2 for "81" in "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": 16=81, l: 16=81, r: 16=81
BinarySearch Index_LowerBound3 for "81" in "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": 16=81, l: 16=81, r: 15=78
BinarySearch Index_UpperBound for "3" from "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": 1, Found Last Dup: 0
BinarySearch Index_UpperBound2 for "3" in "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": 1=5, l: 1=5, r: 1=5
BinarySearch Index_UpperBound3 for "3" in "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": 1=5, l: 1=5, r: 0=3
BinarySearch Index_LowerBound for "3" from "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": 0, Found First Dup: 0
BinarySearch Index_LowerBound2 for "3" in "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": 0=3, l: 0=3, r: 0=3
BinarySearch Index_LowerBound3 for "3" in "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": 0=3, l: 0=3, r: -1=N
BinarySearch Index_UpperBound for "80" from "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": 16, [Floor,Ceil]: [15,16]=[78,81]
BinarySearch Index_UpperBound2 for "80" in "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": 16=81, l: 16=81, r: 16=81
BinarySearch Index_UpperBound3 for "80" in "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": 16=81, l: 16=81, r: 15=78
BinarySearch Index_LowerBound for "80" from "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": 16, [Floor,Ceil]: [15,16]=[78,81]
BinarySearch Index_LowerBound2 for "80" in "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": 16=81, l: 16=81, r: 16=81
BinarySearch Index_LowerBound3 for "80" in "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": 16=81, l: 16=81, r: 15=78
BinarySearch Index_UpperBound for "4" from "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": 1, [Floor,Ceil]: [0,1]=[3,5]
BinarySearch Index_UpperBound2 for "4" in "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": 1=5, l: 1=5, r: 1=5
BinarySearch Index_UpperBound3 for "4" in "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": 1=5, l: 1=5, r: 0=3
BinarySearch Index_LowerBound for "4" from "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": 1, [Floor,Ceil]: [0,1]=[3,5]
BinarySearch Index_LowerBound2 for "4" in "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": 1=5, l: 1=5, r: 1=5
BinarySearch Index_LowerBound3 for "4" in "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": 1=5, l: 1=5, r: 0=3
BinarySearch Index_UpperBound for "37" from "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": 5, [Floor,Ceil]: [4,5]=[34,41]
BinarySearch Index_UpperBound2 for "37" in "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": 5=41, l: 5=41, r: 5=41
BinarySearch Index_UpperBound3 for "37" in "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": 5=41, l: 5=41, r: 4=34
BinarySearch Index_LowerBound for "37" from "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": 5, [Floor,Ceil]: [4,5]=[34,41]
BinarySearch Index_LowerBound2 for "37" in "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": 5=41, l: 5=41, r: 5=41
BinarySearch Index_LowerBound3 for "37" in "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": 5=41, l: 5=41, r: 4=34
BinarySearch Index_UpperBound for "1" from "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": 0, Out Of Range On Left
BinarySearch Index_UpperBound2 for "1" in "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": 0=3, l: 0=3, r: 0=3
BinarySearch Index_UpperBound3 for "1" in "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": 0=3, l: 0=3, r: -1=N
BinarySearch Index_LowerBound for "1" from "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": 0, Out Of Range On Left
BinarySearch Index_LowerBound2 for "1" in "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": 0=3, l: 0=3, r: 0=3
BinarySearch Index_LowerBound3 for "1" in "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": 0=3, l: 0=3, r: -1=N
BinarySearch Index_UpperBound for "88" from "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": 17, Out Of Range On Right
BinarySearch Index_UpperBound2 for "88" in "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": 17=N, l: 17=N, r: 16=81
BinarySearch Index_UpperBound3 for "88" in "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": 17=N, l: 17=N, r: 16=81
BinarySearch Index_LowerBound for "88" from "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": 17, Out Of Range On Right
BinarySearch Index_LowerBound2 for "88" in "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": 17=N, l: 17=N, r: 16=81
BinarySearch Index_LowerBound3 for "88" in "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": 17=N, l: 17=N, r: 16=81
BinarySearch Index_UpperBound for "67" from "3, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 69, 78, 78, 78, 81": 12, Found Last Dup: 11
BinarySearch Index_UpperBound2 for "67" in "3, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 69, 78, 78, 78, 81": 12=69, l: 12=69, r: 12=69
BinarySearch Index_UpperBound3 for "67" in "3, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 69, 78, 78, 78, 81": 12=69, l: 12=69, r: 11=67
BinarySearch Index_LowerBound for "67" from "3, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 69, 78, 78, 78, 81": 1, Found First Dup: 1
BinarySearch Index_LowerBound2 for "67" in "3, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 69, 78, 78, 78, 81": 1=67, l: 1=67, r: 1=67
BinarySearch Index_LowerBound3 for "67" in "3, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 69, 78, 78, 78, 81": 1=67, l: 1=67, r: 0=3
BinarySearch Index_UpperBound for "78" from "3, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 69, 78, 78, 78, 81": 16, Found Last Dup: 15
BinarySearch Index_UpperBound2 for "78" in "3, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 69, 78, 78, 78, 81": 16=81, l: 16=81, r: 16=81
BinarySearch Index_UpperBound3 for "78" in "3, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 69, 78, 78, 78, 81": 16=81, l: 16=81, r: 15=78
BinarySearch Index_LowerBound for "78" from "3, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 69, 78, 78, 78, 81": 13, Found First Dup: 13
BinarySearch Index_LowerBound2 for "78" in "3, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 69, 78, 78, 78, 81": 13=78, l: 13=78, r: 13=78
BinarySearch Index_LowerBound3 for "78" in "3, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 69, 78, 78, 78, 81": 13=78, l: 13=78, r: 12=69
BinarySearch Index_Recur for "78" in "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": 14
BinarySearch Index_Recur for "81" in "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": 16
BinarySearch Index_Recur for "3" in "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": 0
BinarySearch Index_Recur for "80" in "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": -1
BinarySearch Index_Recur for "4" in "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": -1
BinarySearch Index_Recur for "37" in "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": -1
BinarySearch Index_UpperBound_Recur for "78" in "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": 16
BinarySearch Index_UpperBound_Recur for "81" in "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": 17
BinarySearch Index_UpperBound_Recur for "3" in "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": 1
BinarySearch Index_UpperBound_Recur for "80" in "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": 16
BinarySearch Index_UpperBound_Recur for "4" in "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": 1
BinarySearch Index_UpperBound_Recur for "37" in "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": 5
BinarySearch Index_LowerBound_Recur for "78" in "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": 13
BinarySearch Index_LowerBound_Recur for "81" in "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": 16
BinarySearch Index_LowerBound_Recur for "3" in "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": 0
BinarySearch Index_LowerBound_Recur for "80" in "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": 16
BinarySearch Index_LowerBound_Recur for "4" in "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": 1
BinarySearch Index_LowerBound_Recur for "37" in "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": 5
*/
#endif