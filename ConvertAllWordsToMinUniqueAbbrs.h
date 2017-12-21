#ifndef CONVERT_ALL_WORDS_TO_MIN_UNIQUE_ABBRS_H
#define CONVERT_ALL_WORDS_TO_MIN_UNIQUE_ABBRS_H
#include "Debug.h"
/*
Leetcode: Word Abbreviation
Given an array of n distinct non-empty strings, you need to generate minimal possible abbreviations for every word following rules below.
1. Begin with the first character and then the number of characters abbreviated, which followed by the last character.
2. If there are any conflict, that is more than one words share the same abbreviation, a longer prefix is used instead of only the first character until making the map from word to abbreviation become unique.
In other words, a final abbreviation cannot map to more than one original words.
3. If the abbreviation doesn't make the word shorter, then keep it as original.
Example:
Input: ["like", "god", "internal", "me", "internet", "interval", "intension", "face", "intrusion"]
Output: ["l2e","god","internal","me","i6t","interval","inte4n","f2e","intr4n"]
Note:
Both n and the length of each word will not exceed 400.
The length of each word is greater than 1.
The words consist of lowercase English letters only.
The return answers should be in the same order as the original array.
*/
class ConvertAllWordsToMinUniqueAbbrs
{
public:
	ConvertAllWordsToMinUniqueAbbrs() {}

	std::vector<std::string> BruteForce(std::vector<std::string> & dict)
	{
		int N = dict.size();
		std::vector<std::pair<std::string, int>> dict2;//<entry, original idx>
		for (int i = 0; i < N; ++i)
		{
			dict2.push_back({ dict[i], i });
		}
		std::vector<std::string> res(N);

		//for words whose size <= 3, they cannot be abbred
		for (auto itr = dict2.begin(); itr != dict2.end();)
		{
			if (itr->first.size() <= 3)
			{
				res[itr->second] = itr->first;
				itr = dict2.erase(itr);
			}
			else
				++itr;
		}
		
		//for words whose size > 3, start abbr each word from word[1], which will produce min length abbreviation of each word
		int abbrIdx = 1;
		while (!dict2.empty())
		{
			std::unordered_map<std::string, int> abbrCount;
			for (int i = 0; i < (int)dict2.size(); ++i)//first iteration: build abbrCount map
			{
				std::string curAbbr = abbr(dict2[i].first, abbrIdx);
				++abbrCount[curAbbr];
			}
			for (auto itr = dict2.begin(); itr != dict2.end();)//second iteration: remove non-dup abbr
			{
				std::string curAbbr = abbr(itr->first, abbrIdx);
				if (abbrCount[curAbbr] == 1)
				{
					res[itr->second] = curAbbr;
					itr = dict2.erase(itr);
				}
				else
					++itr;
			}
			++abbrIdx;
		}

		std::cout << "ConvertAllWordsToMinUniqueAbbrs for \"" << Debug::ToStr1D<std::string>()(dict) << "\": " << Debug::ToStr1D<std::string>()(res) << std::endl;
		return res;
	}
private:
	std::string abbr(const std::string & s, int abbrIdx)//abbrIdx=1,2,3,...,N-3 (abbrIdx must include at least 2 chars till N-2)
	{
		int N = s.size();
		if (abbrIdx > N - 3) return s;
		return s.substr(0, abbrIdx) + std::to_string(N - 2 - abbrIdx + 1) + s.substr(N - 1);//prefix + abbrLen + last char
	}
};
/*
ConvertAllWordsToMinUniqueAbbrs for "like, god, internal, me, internet, interval, intension, face, intrusion": l2e, god, internal, me, i6t, interval, inte4n, f2e, intr4n
*/
#endif
