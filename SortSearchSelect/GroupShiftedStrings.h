#ifndef GROUP_SHIFTED_STRINGS_H
#define GROUP_SHIFTED_STRINGS_H
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include "Debug.h"
/*
Leetcode: Group Shifted Strings
Given a string, we can "shift" each of its letter to its successive letter, for example: "abc" -> "bcd". We can keep "shifting" which forms the sequence:
"abc" -> "bcd" -> ... -> "xyz"
Given a list of strings which contains only lowercase alphabets, group all strings that belong to the same shifting sequence.
For example, given: ["abc", "bcd", "acef", "xyz", "az", "ba", "a", "z"],
Return:
[
["abc","bcd","xyz"],
["az","ba"],
["acef"],
["a","z"]
]
Note: For the return value, each inner list's elements must follow the lexicographic order.
See also Anagrams.h
*/
class GroupShiftedStrings
{
public:
	GroupShiftedStrings() {}
	~GroupShiftedStrings() {}

	std::vector<std::vector<std::string>> UseHashMap(const std::vector<std::string> & strs)
	{
		int N = strs.size();
		std::unordered_map<std::string, std::vector<std::string>> shiftMap;//first: left shifted string format, second: all entries with same left shifted string format

		//1. group all entries based on their left shifted string format
		for (int i = 0; i < N; ++i)
		{
			std::string shift = strs[i];
			int M = shift.size();
			if (M > 0)
			{
				int diff = shift[0] - 'a';//compute the distance to shift the first char to 'a'
				for (int j = 0; j < M; ++j)//left shift all chars with the distance
				{
					if (shift[j] - diff < 'a')
						shift[j] = shift[j] - diff + 26;
					else
						shift[j] = shift[j] - diff;
				}
			}

			shiftMap[shift].push_back(strs[i]);
		}

		//2. sort all entries for each left shift string format
		for (auto & p : shiftMap)
		{
			std::sort(p.second.begin(), p.second.end());
		}

		//3. add to res
		std::vector<std::vector<std::string>> res;
		for (auto & p : shiftMap)
		{
			res.emplace_back(p.second);
		}

		Debug::Print2D<std::string>()(shiftMap);
		std::cout << "GroupShiftedStrings UseHashMap for \"" << Debug::ToStr1D<std::string>()(strs) << "\":" << std::endl;
		Debug::Print2D<std::string>()(res, false);
		return res;
	}
};
/*
Row#0	= abc: abc, bcd, xyz
Row#1	= az: az, ba
Row#2	= acef: acef
Row#3	= :
Row#4	= a: a, z

GroupShiftedStrings UseHashMap for "abc, bcd, acef, xyz, az, ba, , a, z":
[rY][cX]
Row#0	= abc, bcd, xyz
Row#1	= az, ba,
Row#2	= acef,  ,
Row#3	= ,  ,
Row#4	= a, z,

*/
#endif
