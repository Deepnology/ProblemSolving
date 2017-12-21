#ifndef SORT_CHARS_BY_FREQUENCY_H
#define SORT_CHARS_BY_FREQUENCY_H
#include "Debug.h"
/*
Leetcode: Sort Characters By Frequency
Given a string, sort it in decreasing order based on the frequency of characters.

Example 1:
Input:
"tree"
Output:
"eert"
Explanation:
'e' appears twice while 'r' and 't' both appear once.
So 'e' must appear before both 'r' and 't'. Therefore "eetr" is also a valid answer.

Example 2:
Input:
"cccaaa"
Output:
"cccaaa"
Explanation:
Both 'c' and 'a' appear three times, so "aaaccc" is also a valid answer.
Note that "cacaca" is incorrect, as the same characters must be together.

Example 3:
Input:
"Aabb"
Output:
"bbAa"
Explanation:
"bbaA" is also a valid answer, but "Aabb" is incorrect.
Note that 'A' and 'a' are treated as two different characters.
*/
class SortCharsByFrequency
{
public:
	std::string frequencySort(std::string s)
	{
		std::string before = s;
		std::unordered_map<char, int> charMap;
		for (const auto & c : s)
			++charMap[c];
		std::priority_queue<std::pair<int, char>, std::vector<std::pair<int, char>>, std::less<std::pair<int, char>>> maxHeap;
		for (const auto & p : charMap)
			maxHeap.push({ p.second, p.first });
		s.clear();
		while (!maxHeap.empty())
		{
			s += std::string(maxHeap.top().first, maxHeap.top().second);
			maxHeap.pop();
		}

		std::cout << "SortCharsByFrequency for \"" << before << "\": " << s << std::endl;
		return s;
	}
};
/*
SortCharsByFrequency for "Aabb": bbaA
SortCharsByFrequency for "2a554442f544asfasssffffasss": sssssssffffff44444aaaa55522
*/
#endif
