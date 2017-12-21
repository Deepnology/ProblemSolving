#ifndef UNIQUE_WORD_ABBREVIATION_H
#define UNIQUE_WORD_ABBREVIATION_H
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "Debug.h"
/*
Leetcode: Unique Word Abbreviation
An abbreviation of a word follows the form <first letter><number><last letter>.
Below are some examples of word abbreviations:
a) it                      --> it    (no abbreviation)

     1
b) d|o|g                   --> d1g

              1    1  1
     1---5----0----5--8
c) i|nternationalizatio|n  --> i18n

              1
     1---5----0
d) l|ocalizatio|n          --> l10n
Assume you have a dictionary and given a word, find whether its abbreviation is unique in the dictionary.
A word's abbreviation is unique if no other word from the dictionary has the same abbreviation.
Example: 
Given dictionary = [ "deer", "door", "cake", "card" ]

isUnique("dear") -> false
isUnique("cart") -> true
isUnique("cane") -> false
isUnique("make") -> true
*/
class UniqueWordAbbreviation
{
	std::unordered_map<std::string, std::unordered_set<std::string>> abbrMap;//first: abbreviation, second: a set of corresponding dict words

public:
	explicit UniqueWordAbbreviation(const std::vector<std::string> & dict)
	{
		for (const auto & s : dict)
		{
			abbrMap[this->GetAbbr(s)].insert(s);
		}

		Debug::Print2D<std::string>()(abbrMap);
	}
	~UniqueWordAbbreviation() {}

	bool isUnique(const std::string & s)
	{
		std::string abbr = this->GetAbbr(s);
		bool res = abbrMap[abbr].empty() || abbrMap[abbr].count(s) == abbrMap[abbr].size();//empty() or (count(s)==1 && size()==1)

		std::cout << "UniqueWordAbbreviation isUnique for \"" << s << "\": " << res << std::endl;
		return res;
	}

private:
	std::string GetAbbr(const std::string & s)
	{
		return s.front() + std::to_string(s.length() - 2) + s.back();
	}
};
/*
Row#0	= d2r: deer, door
Row#1	= c2e: cake
Row#2	= c2d: card

UniqueWordAbbreviation isUnique for "dear": 0
UniqueWordAbbreviation isUnique for "cart": 1
UniqueWordAbbreviation isUnique for "cane": 0
UniqueWordAbbreviation isUnique for "make": 1
*/
#endif
