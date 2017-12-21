#ifndef FREQUENCY_OF_IDX_SEQ_ARRAY_H
#define FREQUENCY_OF_IDX_SEQ_ARRAY_H
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <iostream>
#include "Debug.h"
/*
Amazon
https://sites.google.com/site/spaceofjameschen/annnocements/computethefrequencyofeachelementinanarray--amazon
You are given an array of integers which can contain integers from 1 to N only.
Some elements can be repeated multiple times and some other elements can be absent from the array.
Write a running code on papaer which takes O(1) space apart from the input array and O(N) time to print which elements are not present in the array
and the count of every element which is there in the array along with the element number.
NOTE: The array isn't necessarily sorted.

Algorithm:
We can transform the original array to a negative count array, where A[i]==0 means the element A[i]-1 has 0 count, A[i]==negative means the element A[i]-i has -(negative) count.
Iterate through all elements in the array.
Keep swapping current element to its corresponding position until A[i] becomes a count (<=0).
Then advance to the next element and keep swapping.

See also FirstMissingPositive.h, CountingSort2.h
*/
class FrequencyOfIdxSeqArray
{
public:
	FrequencyOfIdxSeqArray(){}
	~FrequencyOfIdxSeqArray(){}

	/*transform original array to an array of element counts in negative numbers*/
	void Transform(std::vector<int> & v)
	{
		std::string before = Debug::ToStr1D<int>()(v);

		int N = v.size();
		int curIdx = 0;

		while (curIdx < N)
		{
			int tgtIdx = v[curIdx] - 1; /*tgtIdx: the corresponding position for current element*/

			/*
			v[curIdx] > 0: current element is an original number 1 to N. so tgtIdx must be a valid index.
			v[tgtIdx] > 0: the element at target position is an original number 1 to N.
			*/
			if (v[curIdx] > 0 && v[tgtIdx] > 0)
			{
				/*
				move current element to its corresponding position and increment count
				move the original element in that position to current position and do next loop
				*/
				std::swap(v[curIdx], v[tgtIdx]);
				v[tgtIdx] = -1;
			}
			else if (v[curIdx] > 0)/*current element is an original number 1 to N and has already been counted at target position*/
			{
				--v[tgtIdx];
				v[curIdx++] = 0;
			}
			else/*current element is a count number*/
				++curIdx;
		}

		std::cout << "FrequencyOfIdxSeqArray Transform for \"" << before << "\": " << Debug::ToStr1D<int>()(v) << std::endl;
	}
};
/*
FrequencyOfIdxSeqArray Transform for "1, 3, 5, 7, 9, 1, 3, 5, 7, 9, 1": -3, 0, -2, 0, -2, 0, -2, 0, -2, 0, 0
FrequencyOfIdxSeqArray Transform for "11, 11, 9, 10, 7, 10, 3, 5, 7, 9, 1": -1, 0, -1, 0, -1, 0, -2, 0, -2, -2, -2
*/
#endif