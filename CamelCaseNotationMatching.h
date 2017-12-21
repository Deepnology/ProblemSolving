#ifndef CAMEL_CASE_NOTATION_MATCHING_H
#define CAMEL_CASE_NOTATION_MATCHING_H
#include "Debug.h"
#include <cctype>
/*
Google
https://careercup.com/question?id=5660887265312768
http://www.geeksforgeeks.org/print-words-matching-pattern-camelcase-notation-dictonary/
CamelCase Notation: writing compound words such that each word begins with a upper case letter.
CamelCase Notation Matching:
Given a dict of CamelCase Notation words.
Given a pattern consisting of upper case chars only, return all matched words from the dict.

[HelloMars, HelloWorld, HelloWorldMars, HiHo]

H -> [HelloMars, HelloWorld, HelloWorldMars, HiHo]
HW -> [HelloWorld, HelloWorldMars]
WM -> []
HWM -> [HelloWorldMars]
HH -> [HiHo]
M -> []

Extra condition: the pattern can contain lower case chars and each of them should match exactly 1 lower case char
He -> [HelloMars, HelloWorld, HelloWorldMars]
Ho -> []
HeWorM -> [HelloWorldMars]
HeWxM -> []

Linear (w/ extra condition): use a charMap<UpperCaseChar,count> to record pattern chars and linearly compare char by char

Trie (w/o extra condition):
1) Insert all words from dict to a trie:
Each node represents a upper case char.
Each node can be valid for a key only when it is exactly the last upper case char of a particular word from the dict, in which it adds that particular word to its word vector.
2) Search all words w/ a pattern consisting of upper case chars only:
DFS recur find the key node which is the last upper case char of the given pattern and collect words from its word vector.
Then continue to DFS recur find all child nodes of the key node that are key nodes and collect words from their word vectors.
*/
class CamelCaseNotationMatching
{
public:
	CamelCaseNotationMatching() {}
	~CamelCaseNotationMatching() {}

	std::vector<std::string> Linear(const std::vector<std::string> & strs, const std::string & pattern)
	{
		std::vector<std::string> res;
		int N = strs.size();
		int P = pattern.size();
		std::unordered_map<char, int> patMap;//<upper case char, count>
		for (const auto c : pattern)
			if (std::isupper(c))
				++patMap[c];
		for (int i = 0; i < N; ++i)
		{
			//match strs[i] with pattern
			std::string cur = strs[i];
			int M = cur.size();
			std::unordered_map<char, int> patCopy = patMap;
			int pIdx = 0;
			for (int j = 0; j < M && pIdx < P; ++j)
			{
				if (std::isupper(pattern[pIdx]))//cur upper case char in pattern: must match (if cur[j] is upper case) before used
				{
					if (std::isupper(cur[j]))
					{
						if (!patCopy.empty())
						{
							if (patCopy.count(cur[j]) == 0)
								break;
							if (pattern[pIdx] != cur[j])
								break;
							--patCopy[cur[j]];
							if (patCopy[cur[j]] == 0)
								patCopy.erase(cur[j]);
							++pIdx;//adv pIdx only when matched
						}
						//else: when patCopy is empty, don't adv pIdx
					}
					//else: when cur[j] is lower case, don't adv pIdx
				}
				else//cur lower case char in pattern: must match
				{
					if (pattern[pIdx] != cur[j])
						break;
					++pIdx;//adv pIdx only when matched
				}
			}

			if (pIdx == P)
				res.push_back(cur);
		}

		std::cout << "CamelCaseNotationMatching Linear for \"" << Debug::ToStr1D<std::string>()(strs) << "\", pattern=\"" << pattern << "\": " << Debug::ToStr1D<std::string>()(res) << std::endl;
		return res;
	}
};
/*
CamelCaseNotationMatching Linear for "HelloMars, HelloWorld, HelloWorldMars, HiHo", pattern="H": HelloMars, HelloWorld, HelloWorldMars, HiHo
CamelCaseNotationMatching Linear for "HelloMars, HelloWorld, HelloWorldMars, HiHo", pattern="HW": HelloWorld, HelloWorldMars
CamelCaseNotationMatching Linear for "HelloMars, HelloWorld, HelloWorldMars, HiHo", pattern="WM":
CamelCaseNotationMatching Linear for "HelloMars, HelloWorld, HelloWorldMars, HiHo", pattern="HWM": HelloWorldMars
CamelCaseNotationMatching Linear for "HelloMars, HelloWorld, HelloWorldMars, HiHo", pattern="HH": HiHo
CamelCaseNotationMatching Linear for "HelloMars, HelloWorld, HelloWorldMars, HiHo", pattern="M":
CamelCaseNotationMatching Linear for "HelloMars, HelloWorld, HelloWorldMars, HiHo", pattern="He": HelloMars, HelloWorld, HelloWorldMars
CamelCaseNotationMatching Linear for "HelloMars, HelloWorld, HelloWorldMars, HiHo", pattern="Ho":
CamelCaseNotationMatching Linear for "HelloMars, HelloWorld, HelloWorldMars, HiHo", pattern="HeWorM": HelloWorldMars
CamelCaseNotationMatching Linear for "HelloMars, HelloWorld, HelloWorldMars, HiHo", pattern="HeWxM":
CamelCaseNotationMatching Linear for "WelcomeGeek, WelcomeToGeeksForGeeks, GeeksForGeeks", pattern="WTG": WelcomeToGeeksForGeeks
CamelCaseNotationMatching Linear for "WelcomeGeek, WelcomeToGeeksForGeeks, GeeksForGeeks", pattern="GFG": GeeksForGeeks
CamelCaseNotationMatching Linear for "WelcomeGeek, WelcomeToGeeksForGeeks, GeeksForGeeks", pattern="GG":
CamelCaseNotationMatching Linear for "WelcomeGeek, WelcomeToGeeksForGeeks, GeeksForGeeks", pattern="We": WelcomeGeek, WelcomeToGeeksForGeeks
CamelCaseNotationMatching Linear for "WelcomeGeek, WelcomeToGeeksForGeeks, GeeksForGeeks", pattern="WeGe": WelcomeGeek
CamelCaseNotationMatching Linear for "WelcomeGeek, WelcomeToGeeksForGeeks, GeeksForGeeks", pattern="Ge": GeeksForGeeks
*/
#endif
