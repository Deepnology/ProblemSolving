#ifndef KTH_SMALLEST_ELEMENT_2_SORTED_ARRAYS_H
#define KTH_SMALLEST_ELEMENT_2_SORTED_ARRAYS_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>
#include "Debug.h"
/*
Leetcode: Median of Two Sorted Arrays
Elements of programming interview, Searching: Search in two sorted arrays
You are given two sorted arrays A and B of lengths M and N, respectively, and a positive integer K in [1, M+N].
Design an algorithm runs in O(logK) time for computing the K-th smallest element in array formed by merging A and B.
Array elements may be duplicated within and between A and B.
http://www.careercup.com/question?id=13639665
http://www.programcreek.com/2012/12/leetcode-median-of-two-sorted-arrays-java/

Find_Recur: O(log(m+n)) time
Find_Iterate: O(log(min(m,n))) time (see also CreateMaxNumberFrom2Arrays.h)

check also Median2SortedArrays.h
*/
class KthSmallestElement2SortedArrays
{
public:
	KthSmallestElement2SortedArrays(){}
	~KthSmallestElement2SortedArrays(){}

	//O(log(m+n)) time
	int Find_Recur(const std::vector<int> & A, const std::vector<int> & B, int K)//K: 0-based
	{
		std::cout << Debug::ToStr1D<int>()(A) << std::endl;
		std::cout << Debug::ToStr1D<int>()(B) << std::endl;
		int res = this->findRecur(A, 0, A.size() - 1, B, 0, B.size() - 1, K);
		std::cout << "KthSmallestElement2SortedArrays Find_Recur for \"" << K << "-th\": " << res << std::endl;
		return res;
	}
	int findRecur(const std::vector<int> & A, int aStart, int aEnd, const std::vector<int> & B, int bStart, int bEnd, int K)//K: 0-based
	{
		int aLen = aEnd - aStart + 1;
		int bLen = bEnd - bStart + 1;

		// Handle special cases
		if (aLen == 0)
			return B[bStart + K];
		if (bLen == 0)
			return A[aStart + K];
		if (K == 0)
			return A[aStart] < B[bStart] ? A[aStart] : B[bStart];

		// split K into 2 parts evenly based on aLen and bLen
		int aMid = K * aLen / (aLen + bLen);
		int bMid = K - aMid - 1;

		// make aMid and bMid to be array index
		aMid = aMid + aStart;
		bMid = bMid + bStart;

		if (A[aMid] > B[bMid])//now count (bMid-bStart+1) toward K
		{
			K -= (bMid - bStart + 1);
			aEnd = aMid;
			bStart = bMid + 1;
		}
		else//now count (aMid-aStart+1) toward K
		{
			K -= (aMid - aStart + 1);
			bEnd = bMid;
			aStart = aMid + 1;
		}
		return this->findRecur(A, aStart, aEnd, B, bStart, bEnd, K);
	}

	//O(log(min(m,n))) time
	int Find_Iterate(const std::vector<int> & A, const std::vector<int> & B, int K)//K: 1-based
	{
		int M = A.size();
		int N = B.size();
		int leftA = std::max(0, K - N);//A's min count toward K (count entire N toward K if possible) (1-based)
		int rightA = std::min(M, K);//A's max count toward K (count entire M toward K if possible) (1-based)
		int res;
		bool found = false;
		while (leftA < rightA)//keep 2 entries in between [leftA:rightA] inclusive
		{
			int midA = (leftA + rightA) / 2;//take A's midA count toward K (1-based)
			/*
			candidates: midAVal or midBVal
			, as long as midARVal >= midBVal && midAVal <= midBRVal
			*/
			int midAVal = (midA - 1 < 0 ? INT_MIN : A[midA - 1]);//(-1: transform to 0-based) count midA in A
			int midARVal = (midA >= M ? INT_MAX : A[midA]);//next right of midA
			int midBVal = (K - midA - 1 < 0 ? INT_MIN : B[K - midA - 1]);//(-1: transform to 0-based) count K-midA in B
			int midBRVal = (K - midA >= N ? INT_MAX : B[K - midA]);//next right of midB

			//std::cout << "A=>" << leftA << "," << rightA << "," << midA << std::endl;
			//std::cout << "A: (" << midA - 1 << "," << midA << ")=[" << midAVal << "," << midARVal << "]" << std::endl;
			//std::cout << "B: (" << K - midA - 1 << "," << K - midA << ")=[" << midBVal << "," << midBRVal << "]" << std::endl;

			/*
			midAVal, midARVal
			                      midBVal, midBRVal
			*/
			if (midARVal < midBVal)//count midA in A toward K
				leftA = midA + 1;
			/*
			                      midAVal, midARVal
			midBVal, midBRVal
			*/
			else if (midAVal > midBRVal)//count K-midA in B toward K
				rightA = midA - 1;
			/*
			midAVal,         midARVal				OR			midAVal,		midARVal
			           midBVal,        midBRVal			midBVal,	  midBRVal
			*/
			else//midARVal >= midBVal && midAVal <= midBRVal
			{
				//std::cout << "res=max(" << midAVal << "," << midBVal << ")" << std::endl;
				res = std::max(midAVal, midBVal);//count midA in A and K-midA in B toward K
				found = true;
				break;
			}
		}

		if (!found)//do the same thing to regard leftA as midA
		{
			int AVal = leftA - 1 < 0 ? INT_MIN : A[leftA - 1];
			int BVal = K - leftA - 1 < 0 ? INT_MIN : B[K - leftA - 1];
			res = std::max(AVal, BVal);//count leftA in A and K-leftA in B toward K

			//std::cout << "A=>" << leftA << "," << rightA << std::endl;
			//std::cout << "res=max(" << AL << "," << BL << std::endl;
		}

		std::cout << Debug::ToStr1D<int>()(A) << std::endl;
		std::cout << Debug::ToStr1D<int>()(B) << std::endl;
		std::cout << "KthSmallestElement2SortedArrays Find_Iterate for \"" << K << "-th\": " << res << std::endl;
		return res;
	}
};
/*
1, 3, 5, 7, 9, 11
2, 4, 6, 8, 10, 12, 14, 16
KthSmallestElement2SortedArrays Find_Recur for "12-th": 14
1, 3, 5, 7, 9, 11
2, 4, 6, 8, 10, 12, 14, 16
KthSmallestElement2SortedArrays Find_Iterate for "13-th": 14
*/
#endif