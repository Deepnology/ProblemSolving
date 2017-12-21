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
};
/*
MissingRangesInSortedArray for "[27,102], From 12, 13, 14, 36, 37, 40, 45, 52, 59, 80": 27->35, 38->39, 41->44, 46->51, 53->58, 60->79, 81->102
MissingRangesInSortedArray for "[30,75], From 8, 16, 21, 38, 45, 46, 54, 56, 76, 77": 30->37, 39->44, 47->53, 55, 57->75
MissingRangesInSortedArray for "[-10,131], From 4, 9, 19, 45, 46, 67, 70, 81, 85, 96": -10->3, 5->8, 10->18, 20->44, 47->66, 68->69, 71->80, 82->84, 86->95, 97->131
MissingRangesInSortedArray for "[-23,97], From 1, 5, 43, 44, 51, 54, 71, 77, 85, 93": -23->0, 2->4, 6->42, 45->50, 52->53, 55->70, 72->76, 78->84, 86->92, 94->97
MissingRangesInSortedArray for "[21,89], From 10, 12, 32, 36, 38, 51, 52, 59, 86, 89": 21->31, 33->35, 37, 39->50, 53->58, 60->85, 87->88
MissingRangesInSortedArray for "[-45,91], From 6, 14, 18, 24, 32, 45, 56, 57, 79, 97": -45->5, 7->13, 15->17, 19->23, 25->31, 33->44, 46->55, 58->78, 80->91
MissingRangesInSortedArray for "[-49,78], From 9, 9, 11, 25, 43, 43, 56, 73, 90, 91": -49->8, 10, 12->24, 26->42, 44->55, 57->72, 74->78
MissingRangesInSortedArray for "[-31,98], From 10, 11, 11, 19, 38, 38, 46, 62, 74, 80": -31->9, 12->18, 20->37, 39->45, 47->61, 63->73, 75->79, 81->98
MissingRangesInSortedArray for "[23,98], From 5, 20, 31, 32, 42, 68, 71, 72, 73, 98": 23->30, 33->41, 43->67, 69->70, 74->97
MissingRangesInSortedArray for "[-42,124], From 2, 32, 37, 42, 52, 64, 72, 75, 87, 99": -42->1, 3->31, 33->36, 38->41, 43->51, 53->63, 65->71, 73->74, 76->86, 88->98, 100->124
MissingRangesInSortedArray for "[36,65], From 2, 11, 11, 28, 43, 63, 65, 66, 70, 79": 36->42, 44->62, 64
MissingRangesInSortedArray for "[37,58], From 15, 29, 32, 37, 41, 70, 70, 83, 87, 95": 38->40, 42->58
*/
#endif