#ifndef MISSING_RANGES_IN_SORTED_ARRAY_H
#define MISSING_RANGES_IN_SORTED_ARRAY_H
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include "Debug.h"
/*
Leetcode: Missing Ranges
http://www.danielbit.com/blog/puzzle/leetcode/leetcode-missing-ranges
Given a sorted integer array where the range of elements are [0, 99] inclusive, return its missing ranges.
For example, given [0, 1, 3, 50, 75], return ["2", "4->49", "51->74", "76->99"]

O(n) time, O(1) space
*/
class MissingRangesInSortedArray
{
public:
	MissingRangesInSortedArray(){}
	~MissingRangesInSortedArray(){}

	std::vector<std::string> Solve(const std::vector<int> & sorted, int lower, int upper)
	{
		int N = sorted.size();
		std::vector<std::string> res;

		int prevNum = lower - 1;
		for (int i = 0; i < N; ++i)
		{
			int curNum = sorted[i] <= upper ? sorted[i] : upper + 1;
			if ((curNum - prevNum) > 1)//at least 3 entries in between inclusive 
			{
				if (curNum - prevNum == 2)//exactly 3 entries in between inclusive
					res.push_back(std::to_string(prevNum + 1));
				else//3 more entries in between inclusive
					res.push_back(std::to_string(prevNum + 1) + "->" + std::to_string(curNum - 1));
			}
			prevNum = sorted[i] >= prevNum ? sorted[i] : prevNum;
		}

		int curNum = upper + 1;
		if (curNum - prevNum > 1)//at least 3 entries in between inclusive
		{
			if (curNum - prevNum == 2)//exactly 3 entries in between inclusive
				res.push_back(std::to_string(prevNum + 1));
			else//3 more entries in between inclusive
				res.push_back(std::to_string(prevNum + 1) + "->" + std::to_string(curNum - 1));
		}

		std::cout << "MissingRangesInSortedArray for \"[" << lower << "," << upper << "], From " << Debug::ToStr1D<int>()(sorted) << "\": " << Debug::ToStr1D<std::string>()(res) << std::endl;
		return res;
	}

	std::vector<std::string> Simplified(const std::vector<int> & sorted, int lower, int upper)//nums in sorted are exclusive, but "lower" and "upper" are inclusive
	{
		int N = sorted.size();
		std::vector<std::string> res;

		int prevNum = lower-1;
		for (int i = 0; i < N; ++i)
		{
			if ((sorted[i] - prevNum) > 1)//at least 3 entries in between inclusive
			{
				if (sorted[i] - prevNum == 2)//exactly 3 entries in between inclusive
					res.push_back(std::to_string(prevNum + 1));
				else//3 more entries in between inclusive
					res.push_back(std::to_string(prevNum + 1) + "->" + std::to_string(sorted[i] - 1));
			}
			prevNum = sorted[i];
		}

		if ((upper+1) - prevNum > 1)//at least 3 entries in between inclusive
		{
			if ((upper+1) - prevNum == 2)//exactly 3 entries in between inclusive
				res.push_back(std::to_string(prevNum + 1));
			else//3 more entries in between inclusive
				res.push_back(std::to_string(prevNum + 1) + "->" + std::to_string((upper+1) - 1));
		}

		std::cout << "MissingRangesInSortedArray Simplified for \"[" << lower << "," << upper << "], From " << Debug::ToStr1D<int>()(sorted) << "\": " << Debug::ToStr1D<std::string>()(res) << std::endl;
		return res;
	}
};
/*
MissingRangesInSortedArray for "[42,113], From 9, 25, 32, 47, 47, 56, 59, 68, 70, 72": 42->46, 48->55, 57->58, 60->67, 69, 71, 73->113
MissingRangesInSortedArray Simplified for "[-1,146], From 6, 9, 42, 50, 53, 60, 63, 73, 92, 97": -1->5, 7->8, 10->41, 43->49, 51->52, 54->59, 61->62, 64->72, 74->91, 93->96, 98->146
MissingRangesInSortedArray for "[11,124], From 3, 4, 8, 27, 40, 40, 48, 71, 88, 90": 11->26, 28->39, 41->47, 49->70, 72->87, 89, 91->124
MissingRangesInSortedArray Simplified for "[40,108], From 2, 8, 8, 20, 44, 59, 60, 64, 83, 97": 3->7, 9->19, 21->43, 45->58, 61->63, 65->82, 84->96, 98->108
MissingRangesInSortedArray for "[-28,95], From 3, 14, 16, 29, 44, 44, 70, 76, 81, 84": -28->2, 4->13, 15, 17->28, 30->43, 45->69, 71->75, 77->80, 82->83, 85->95
MissingRangesInSortedArray Simplified for "[5,86], From 8, 12, 30, 31, 41, 44, 57, 77, 86, 97": 5->7, 9->11, 13->29, 32->40, 42->43, 45->56, 58->76, 78->85, 87->96
*/
#endif