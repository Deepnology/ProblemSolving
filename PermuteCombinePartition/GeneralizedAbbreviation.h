#ifndef GENERALIZED_ABBREVIATION_H
#define GENERALIZED_ABBREVIATION_H
#include "Debug.h"
/*
Leetcode: Generalized Abbreviation
Write a function to generate the generalized abbreviations of a word.
Example:
Given word = "word", return the following list (order does not matter):
["word", "1ord", "w1rd", "wo1d", "wor1", "2rd", "w2d", "wo2", "1o1d", "1or1", "w1r1", "1o2", "2r1", "3d", "w3", "4"]

Leetcode: Valid word abbreviation
Given a non-empty string s and an abbreviation abbr, return whether the string matches with the given abbreviation.
A string such as "word" contains only the following valid abbreviations:
["word", "1ord", "w1rd", "wo1d", "wor1", "2rd", "w2d", "wo2", "1o1d", "1or1", "w1r1", "1o2", "2r1", "3d", "w3", "4"]
Notice that only the above abbreviations are valid abbreviations of the string "word".
Any other string is not a valid abbreviation of "word".
Note:
Assume s contains only lowercase letters and abbr contains only lowercase letters and digits.
Example 1:
Given s = "internationalization", abbr = "i12iz4n":
Return true.
Example 2:
Given s = "apple", abbr = "a2e":
Return false.
*/
class GeneralizedAbbreviation
{
public:
	GeneralizedAbbreviation() {}
	~GeneralizedAbbreviation() {}

	std::vector<std::string> Recur(const std::string & s)
	{
		std::vector<std::string> res;
		this->recur(s, 0, "", 0, res);

		std::cout << "GeneralizedAbbreviation Recur for \"" << s << "\": " << Debug::ToStr1D<std::string>()(res) << std::endl;
		return res;
	}
private:
	void recur(const std::string & s, int begin, std::string curStr, int curNum, std::vector<std::string> & res)
	{
		int N = s.size();
		if (begin == N)
		{
			if (curNum != 0)
				curStr += std::to_string(curNum);
			res.push_back(curStr);
			return;
		}

		//include s[begin] to curNum (abbr s[begin])
		recur(s, begin + 1, curStr, curNum + 1, res);

		//include s[begin] to curStr (not abbr s[begin])
		if (curNum != 0)
			curStr += std::to_string(curNum);
		curStr += s[begin];
		recur(s, begin + 1, curStr, 0, res);
	}

public:
	bool Validate(std::string word, std::string abbr)
	{
		bool res = validate(word, abbr);
		std::cout << "GeneralizedAbbreviation Validate for \"" << word << "\" and \"" << abbr << "\": " << res << std::endl;
		return res;
	}
private:
	bool validate(std::string word, std::string abbr)
	{
		std::string num;
		int i = 0;
		int N = word.size();
		int j = 0;
		int M = abbr.size();
		while (i < N && j < M)
		{
			if (isdigit(abbr[j]))//digit
			{
				if (num.empty() && abbr[j] == '0') return false;//single 0 OR any number w/ a leading 0 are invalid!
				num += abbr[j++];
			}
			else//char
			{
				if (!num.empty())
				{
					int count = stoi(num);//count >= 1
					i += count;
					num.clear();
				}
				else
					if (abbr[j++] != word[i++]) return false;
			}
		}
		if (!num.empty())
		{
			i += stoi(num);
		}
		if (i == N && j == M) return true;
		return false;
	}
};
/*
GeneralizedAbbreviation Recur for "word": 4, 3d, 2r1, 2rd, 1o2, 1o1d, 1or1, 1ord, w3, w2d, w1r1, w1rd, wo2, wo1d, wor1, word
GeneralizedAbbreviation Recur for "abcde": 5, 4e, 3d1, 3de, 2c2, 2c1e, 2cd1, 2cde, 1b3, 1b2e, 1b1d1, 1b1de, 1bc2, 1bc1e, 1bcd1, 1bcde, a4, a3e, a2d1, a2de, a1c2, a1c1e, a1cd1, a1cde, ab3, ab2e, ab1d1, ab1de, abc2, abc1e, abcd1, abcde
GeneralizedAbbreviation Recur for "abcdefghij": 10, 9j, 8i1, 8ij, 7h2, 7h1j, 7hi1, 7hij, 6g3, 6g2j, 6g1i1, 6g1ij, 6gh2, 6gh1j, 6ghi1, 6ghij, 5f4, 5f3j, 5f2i1, 5f2ij, 5f1h2, 5f1h1j, 5f1hi1, 5f1hij, 5fg3, 5fg2j, 5fg1i1, 5fg1ij, 5fgh2, 5fgh1j, 5fghi1, 5fghij, 4e5, 4e4j, 4e3i1, 4e3ij, 4e2h2, 4e2h1j, 4e2hi1, 4e2hij, 4e1g3, 4e1g2j, 4e1g1i1, 4e1g1ij, 4e1gh2, 4e1gh1j, 4e1ghi1, 4e1ghij, 4ef4, 4ef3j, 4ef2i1, 4ef2ij, 4ef1h2, 4ef1h1j, 4ef1hi1, 4ef1hij, 4efg3, 4efg2j, 4efg1i1, 4efg1ij, 4efgh2, 4efgh1j, 4efghi1, 4efghij, 3d6, 3d5j, 3d4i1, 3d4ij, 3d3h2, 3d3h1j, 3d3hi1, 3d3hij, 3d2g3, 3d2g2j, 3d2g1i1, 3d2g1ij, 3d2gh2, 3d2gh1j, 3d2ghi1, 3d2ghij, 3d1f4, 3d1f3j, 3d1f2i1, 3d1f2ij, 3d1f1h2, 3d1f1h1j, 3d1f1hi1, 3d1f1hij, 3d1fg3, 3d1fg2j, 3d1fg1i1, 3d1fg1ij, 3d1fgh2, 3d1fgh1j, 3d1fghi1, 3d1fghij, 3de5, 3de4j, 3de3i1, 3de3ij, 3de2h2, 3de2h1j, 3de2hi1, 3de2hij, 3de1g3, 3de1g2j, 3de1g1i1, 3de1g1ij, 3de1gh2, 3de1gh1j, 3de1ghi1, 3de1ghij, 3def4, 3def3j, 3def2i1, 3def2ij, 3def1h2, 3def1h1j, 3def1hi1, 3def1hij, 3defg3, 3defg2j, 3defg1i1, 3defg1ij, 3defgh2, 3defgh1j, 3defghi1, 3defghij, 2c7, 2c6j, 2c5i1, 2c5ij, 2c4h2, 2c4h1j, 2c4hi1, 2c4hij, 2c3g3, 2c3g2j, 2c3g1i1, 2c3g1ij, 2c3gh2, 2c3gh1j, 2c3ghi1, 2c3ghij, 2c2f4, 2c2f3j, 2c2f2i1, 2c2f2ij, 2c2f1h2, 2c2f1h1j, 2c2f1hi1, 2c2f1hij, 2c2fg3, 2c2fg2j, 2c2fg1i1, 2c2fg1ij, 2c2fgh2, 2c2fgh1j, 2c2fghi1, 2c2fghij, 2c1e5, 2c1e4j, 2c1e3i1, 2c1e3ij, 2c1e2h2, 2c1e2h1j, 2c1e2hi1, 2c1e2hij, 2c1e1g3, 2c1e1g2j, 2c1e1g1i1, 2c1e1g1ij, 2c1e1gh2, 2c1e1gh1j, 2c1e1ghi1, 2c1e1ghij, 2c1ef4, 2c1ef3j, 2c1ef2i1, 2c1ef2ij, 2c1ef1h2, 2c1ef1h1j, 2c1ef1hi1, 2c1ef1hij, 2c1efg3, 2c1efg2j, 2c1efg1i1, 2c1efg1ij, 2c1efgh2, 2c1efgh1j, 2c1efghi1, 2c1efghij, 2cd6, 2cd5j, 2cd4i1, 2cd4ij, 2cd3h2, 2cd3h1j, 2cd3hi1, 2cd3hij, 2cd2g3, 2cd2g2j, 2cd2g1i1, 2cd2g1ij, 2cd2gh2, 2cd2gh1j, 2cd2ghi1, 2cd2ghij, 2cd1f4, 2cd1f3j, 2cd1f2i1, 2cd1f2ij, 2cd1f1h2, 2cd1f1h1j, 2cd1f1hi1, 2cd1f1hij, 2cd1fg3, 2cd1fg2j, 2cd1fg1i1, 2cd1fg1ij, 2cd1fgh2, 2cd1fgh1j, 2cd1fghi1, 2cd1fghij, 2cde5, 2cde4j, 2cde3i1, 2cde3ij, 2cde2h2, 2cde2h1j, 2cde2hi1, 2cde2hij, 2cde1g3, 2cde1g2j, 2cde1g1i1, 2cde1g1ij, 2cde1gh2, 2cde1gh1j, 2cde1ghi1, 2cde1ghij, 2cdef4, 2cdef3j, 2cdef2i1, 2cdef2ij, 2cdef1h2, 2cdef1h1j, 2cdef1hi1, 2cdef1hij, 2cdefg3, 2cdefg2j, 2cdefg1i1, 2cdefg1ij, 2cdefgh2, 2cdefgh1j, 2cdefghi1, 2cdefghij, 1b8, 1b7j, 1b6i1, 1b6ij, 1b5h2, 1b5h1j, 1b5hi1, 1b5hij, 1b4g3, 1b4g2j, 1b4g1i1, 1b4g1ij, 1b4gh2, 1b4gh1j, 1b4ghi1, 1b4ghij, 1b3f4, 1b3f3j, 1b3f2i1, 1b3f2ij, 1b3f1h2, 1b3f1h1j, 1b3f1hi1, 1b3f1hij, 1b3fg3, 1b3fg2j, 1b3fg1i1, 1b3fg1ij, 1b3fgh2, 1b3fgh1j, 1b3fghi1, 1b3fghij, 1b2e5, 1b2e4j, 1b2e3i1, 1b2e3ij, 1b2e2h2, 1b2e2h1j, 1b2e2hi1, 1b2e2hij, 1b2e1g3, 1b2e1g2j, 1b2e1g1i1, 1b2e1g1ij, 1b2e1gh2, 1b2e1gh1j, 1b2e1ghi1, 1b2e1ghij, 1b2ef4, 1b2ef3j, 1b2ef2i1, 1b2ef2ij, 1b2ef1h2, 1b2ef1h1j, 1b2ef1hi1, 1b2ef1hij, 1b2efg3, 1b2efg2j, 1b2efg1i1, 1b2efg1ij, 1b2efgh2, 1b2efgh1j, 1b2efghi1, 1b2efghij, 1b1d6, 1b1d5j, 1b1d4i1, 1b1d4ij, 1b1d3h2, 1b1d3h1j, 1b1d3hi1, 1b1d3hij, 1b1d2g3, 1b1d2g2j, 1b1d2g1i1, 1b1d2g1ij, 1b1d2gh2, 1b1d2gh1j, 1b1d2ghi1, 1b1d2ghij, 1b1d1f4, 1b1d1f3j, 1b1d1f2i1, 1b1d1f2ij, 1b1d1f1h2, 1b1d1f1h1j, 1b1d1f1hi1, 1b1d1f1hij, 1b1d1fg3, 1b1d1fg2j, 1b1d1fg1i1, 1b1d1fg1ij, 1b1d1fgh2, 1b1d1fgh1j, 1b1d1fghi1, 1b1d1fghij, 1b1de5, 1b1de4j, 1b1de3i1, 1b1de3ij, 1b1de2h2, 1b1de2h1j, 1b1de2hi1, 1b1de2hij, 1b1de1g3, 1b1de1g2j, 1b1de1g1i1, 1b1de1g1ij, 1b1de1gh2, 1b1de1gh1j, 1b1de1ghi1, 1b1de1ghij, 1b1def4, 1b1def3j, 1b1def2i1, 1b1def2ij, 1b1def1h2, 1b1def1h1j, 1b1def1hi1, 1b1def1hij, 1b1defg3, 1b1defg2j, 1b1defg1i1, 1b1defg1ij, 1b1defgh2, 1b1defgh1j, 1b1defghi1, 1b1defghij, 1bc7, 1bc6j, 1bc5i1, 1bc5ij, 1bc4h2, 1bc4h1j, 1bc4hi1, 1bc4hij, 1bc3g3, 1bc3g2j, 1bc3g1i1, 1bc3g1ij, 1bc3gh2, 1bc3gh1j, 1bc3ghi1, 1bc3ghij, 1bc2f4, 1bc2f3j, 1bc2f2i1, 1bc2f2ij, 1bc2f1h2, 1bc2f1h1j, 1bc2f1hi1, 1bc2f1hij, 1bc2fg3, 1bc2fg2j, 1bc2fg1i1, 1bc2fg1ij, 1bc2fgh2, 1bc2fgh1j, 1bc2fghi1, 1bc2fghij, 1bc1e5, 1bc1e4j, 1bc1e3i1, 1bc1e3ij, 1bc1e2h2, 1bc1e2h1j, 1bc1e2hi1, 1bc1e2hij, 1bc1e1g3, 1bc1e1g2j, 1bc1e1g1i1, 1bc1e1g1ij, 1bc1e1gh2, 1bc1e1gh1j, 1bc1e1ghi1, 1bc1e1ghij, 1bc1ef4, 1bc1ef3j, 1bc1ef2i1, 1bc1ef2ij, 1bc1ef1h2, 1bc1ef1h1j, 1bc1ef1hi1, 1bc1ef1hij, 1bc1efg3, 1bc1efg2j, 1bc1efg1i1, 1bc1efg1ij, 1bc1efgh2, 1bc1efgh1j, 1bc1efghi1, 1bc1efghij, 1bcd6, 1bcd5j, 1bcd4i1, 1bcd4ij, 1bcd3h2, 1bcd3h1j, 1bcd3hi1, 1bcd3hij, 1bcd2g3, 1bcd2g2j, 1bcd2g1i1, 1bcd2g1ij, 1bcd2gh2, 1bcd2gh1j, 1bcd2ghi1, 1bcd2ghij, 1bcd1f4, 1bcd1f3j, 1bcd1f2i1, 1bcd1f2ij, 1bcd1f1h2, 1bcd1f1h1j, 1bcd1f1hi1, 1bcd1f1hij, 1bcd1fg3, 1bcd1fg2j, 1bcd1fg1i1, 1bcd1fg1ij, 1bcd1fgh2, 1bcd1fgh1j, 1bcd1fghi1, 1bcd1fghij, 1bcde5, 1bcde4j, 1bcde3i1, 1bcde3ij, 1bcde2h2, 1bcde2h1j, 1bcde2hi1, 1bcde2hij, 1bcde1g3, 1bcde1g2j, 1bcde1g1i1, 1bcde1g1ij, 1bcde1gh2, 1bcde1gh1j, 1bcde1ghi1, 1bcde1ghij, 1bcdef4, 1bcdef3j, 1bcdef2i1, 1bcdef2ij, 1bcdef1h2, 1bcdef1h1j, 1bcdef1hi1, 1bcdef1hij, 1bcdefg3, 1bcdefg2j, 1bcdefg1i1, 1bcdefg1ij, 1bcdefgh2, 1bcdefgh1j, 1bcdefghi1, 1bcdefghij, a9, a8j, a7i1, a7ij, a6h2, a6h1j, a6hi1, a6hij, a5g3, a5g2j, a5g1i1, a5g1ij, a5gh2, a5gh1j, a5ghi1, a5ghij, a4f4, a4f3j, a4f2i1, a4f2ij, a4f1h2, a4f1h1j, a4f1hi1, a4f1hij, a4fg3, a4fg2j, a4fg1i1, a4fg1ij, a4fgh2, a4fgh1j, a4fghi1, a4fghij, a3e5, a3e4j, a3e3i1, a3e3ij, a3e2h2, a3e2h1j, a3e2hi1, a3e2hij, a3e1g3, a3e1g2j, a3e1g1i1, a3e1g1ij, a3e1gh2, a3e1gh1j, a3e1ghi1, a3e1ghij, a3ef4, a3ef3j, a3ef2i1, a3ef2ij, a3ef1h2, a3ef1h1j, a3ef1hi1, a3ef1hij, a3efg3, a3efg2j, a3efg1i1, a3efg1ij, a3efgh2, a3efgh1j, a3efghi1, a3efghij, a2d6, a2d5j, a2d4i1, a2d4ij, a2d3h2, a2d3h1j, a2d3hi1, a2d3hij, a2d2g3, a2d2g2j, a2d2g1i1, a2d2g1ij, a2d2gh2, a2d2gh1j, a2d2ghi1, a2d2ghij, a2d1f4, a2d1f3j, a2d1f2i1, a2d1f2ij, a2d1f1h2, a2d1f1h1j, a2d1f1hi1, a2d1f1hij, a2d1fg3, a2d1fg2j, a2d1fg1i1, a2d1fg1ij, a2d1fgh2, a2d1fgh1j, a2d1fghi1, a2d1fghij, a2de5, a2de4j, a2de3i1, a2de3ij, a2de2h2, a2de2h1j, a2de2hi1, a2de2hij, a2de1g3, a2de1g2j, a2de1g1i1, a2de1g1ij, a2de1gh2, a2de1gh1j, a2de1ghi1, a2de1ghij, a2def4, a2def3j, a2def2i1, a2def2ij, a2def1h2, a2def1h1j, a2def1hi1, a2def1hij, a2defg3, a2defg2j, a2defg1i1, a2defg1ij, a2defgh2, a2defgh1j, a2defghi1, a2defghij, a1c7, a1c6j, a1c5i1, a1c5ij, a1c4h2, a1c4h1j, a1c4hi1, a1c4hij, a1c3g3, a1c3g2j, a1c3g1i1, a1c3g1ij, a1c3gh2, a1c3gh1j, a1c3ghi1, a1c3ghij, a1c2f4, a1c2f3j, a1c2f2i1, a1c2f2ij, a1c2f1h2, a1c2f1h1j, a1c2f1hi1, a1c2f1hij, a1c2fg3, a1c2fg2j, a1c2fg1i1, a1c2fg1ij, a1c2fgh2, a1c2fgh1j, a1c2fghi1, a1c2fghij, a1c1e5, a1c1e4j, a1c1e3i1, a1c1e3ij, a1c1e2h2, a1c1e2h1j, a1c1e2hi1, a1c1e2hij, a1c1e1g3, a1c1e1g2j, a1c1e1g1i1, a1c1e1g1ij, a1c1e1gh2, a1c1e1gh1j, a1c1e1ghi1, a1c1e1ghij, a1c1ef4, a1c1ef3j, a1c1ef2i1, a1c1ef2ij, a1c1ef1h2, a1c1ef1h1j, a1c1ef1hi1, a1c1ef1hij, a1c1efg3, a1c1efg2j, a1c1efg1i1, a1c1efg1ij, a1c1efgh2, a1c1efgh1j, a1c1efghi1, a1c1efghij, a1cd6, a1cd5j, a1cd4i1, a1cd4ij, a1cd3h2, a1cd3h1j, a1cd3hi1, a1cd3hij, a1cd2g3, a1cd2g2j, a1cd2g1i1, a1cd2g1ij, a1cd2gh2, a1cd2gh1j, a1cd2ghi1, a1cd2ghij, a1cd1f4, a1cd1f3j, a1cd1f2i1, a1cd1f2ij, a1cd1f1h2, a1cd1f1h1j, a1cd1f1hi1, a1cd1f1hij, a1cd1fg3, a1cd1fg2j, a1cd1fg1i1, a1cd1fg1ij, a1cd1fgh2, a1cd1fgh1j, a1cd1fghi1, a1cd1fghij, a1cde5, a1cde4j, a1cde3i1, a1cde3ij, a1cde2h2, a1cde2h1j, a1cde2hi1, a1cde2hij, a1cde1g3, a1cde1g2j, a1cde1g1i1, a1cde1g1ij, a1cde1gh2, a1cde1gh1j, a1cde1ghi1, a1cde1ghij, a1cdef4, a1cdef3j, a1cdef2i1, a1cdef2ij, a1cdef1h2, a1cdef1h1j, a1cdef1hi1, a1cdef1hij, a1cdefg3, a1cdefg2j, a1cdefg1i1, a1cdefg1ij, a1cdefgh2, a1cdefgh1j, a1cdefghi1, a1cdefghij, ab8, ab7j, ab6i1, ab6ij, ab5h2, ab5h1j, ab5hi1, ab5hij, ab4g3, ab4g2j, ab4g1i1, ab4g1ij, ab4gh2, ab4gh1j, ab4ghi1, ab4ghij, ab3f4, ab3f3j, ab3f2i1, ab3f2ij, ab3f1h2, ab3f1h1j, ab3f1hi1, ab3f1hij, ab3fg3, ab3fg2j, ab3fg1i1, ab3fg1ij, ab3fgh2, ab3fgh1j, ab3fghi1, ab3fghij, ab2e5, ab2e4j, ab2e3i1, ab2e3ij, ab2e2h2, ab2e2h1j, ab2e2hi1, ab2e2hij, ab2e1g3, ab2e1g2j, ab2e1g1i1, ab2e1g1ij, ab2e1gh2, ab2e1gh1j, ab2e1ghi1, ab2e1ghij, ab2ef4, ab2ef3j, ab2ef2i1, ab2ef2ij, ab2ef1h2, ab2ef1h1j, ab2ef1hi1, ab2ef1hij, ab2efg3, ab2efg2j, ab2efg1i1, ab2efg1ij, ab2efgh2, ab2efgh1j, ab2efghi1, ab2efghij, ab1d6, ab1d5j, ab1d4i1, ab1d4ij, ab1d3h2, ab1d3h1j, ab1d3hi1, ab1d3hij, ab1d2g3, ab1d2g2j, ab1d2g1i1, ab1d2g1ij, ab1d2gh2, ab1d2gh1j, ab1d2ghi1, ab1d2ghij, ab1d1f4, ab1d1f3j, ab1d1f2i1, ab1d1f2ij, ab1d1f1h2, ab1d1f1h1j, ab1d1f1hi1, ab1d1f1hij, ab1d1fg3, ab1d1fg2j, ab1d1fg1i1, ab1d1fg1ij, ab1d1fgh2, ab1d1fgh1j, ab1d1fghi1, ab1d1fghij, ab1de5, ab1de4j, ab1de3i1, ab1de3ij, ab1de2h2, ab1de2h1j, ab1de2hi1, ab1de2hij, ab1de1g3, ab1de1g2j, ab1de1g1i1, ab1de1g1ij, ab1de1gh2, ab1de1gh1j, ab1de1ghi1, ab1de1ghij, ab1def4, ab1def3j, ab1def2i1, ab1def2ij, ab1def1h2, ab1def1h1j, ab1def1hi1, ab1def1hij, ab1defg3, ab1defg2j, ab1defg1i1, ab1defg1ij, ab1defgh2, ab1defgh1j, ab1defghi1, ab1defghij, abc7, abc6j, abc5i1, abc5ij, abc4h2, abc4h1j, abc4hi1, abc4hij, abc3g3, abc3g2j, abc3g1i1, abc3g1ij, abc3gh2, abc3gh1j, abc3ghi1, abc3ghij, abc2f4, abc2f3j, abc2f2i1, abc2f2ij, abc2f1h2, abc2f1h1j, abc2f1hi1, abc2f1hij, abc2fg3, abc2fg2j, abc2fg1i1, abc2fg1ij, abc2fgh2, abc2fgh1j, abc2fghi1, abc2fghij, abc1e5, abc1e4j, abc1e3i1, abc1e3ij, abc1e2h2, abc1e2h1j, abc1e2hi1, abc1e2hij, abc1e1g3, abc1e1g2j, abc1e1g1i1, abc1e1g1ij, abc1e1gh2, abc1e1gh1j, abc1e1ghi1, abc1e1ghij, abc1ef4, abc1ef3j, abc1ef2i1, abc1ef2ij, abc1ef1h2, abc1ef1h1j, abc1ef1hi1, abc1ef1hij, abc1efg3, abc1efg2j, abc1efg1i1, abc1efg1ij, abc1efgh2, abc1efgh1j, abc1efghi1, abc1efghij, abcd6, abcd5j, abcd4i1, abcd4ij, abcd3h2, abcd3h1j, abcd3hi1, abcd3hij, abcd2g3, abcd2g2j, abcd2g1i1, abcd2g1ij, abcd2gh2, abcd2gh1j, abcd2ghi1, abcd2ghij, abcd1f4, abcd1f3j, abcd1f2i1, abcd1f2ij, abcd1f1h2, abcd1f1h1j, abcd1f1hi1, abcd1f1hij, abcd1fg3, abcd1fg2j, abcd1fg1i1, abcd1fg1ij, abcd1fgh2, abcd1fgh1j, abcd1fghi1, abcd1fghij, abcde5, abcde4j, abcde3i1, abcde3ij, abcde2h2, abcde2h1j, abcde2hi1, abcde2hij, abcde1g3, abcde1g2j, abcde1g1i1, abcde1g1ij, abcde1gh2, abcde1gh1j, abcde1ghi1, abcde1ghij, abcdef4, abcdef3j, abcdef2i1, abcdef2ij, abcdef1h2, abcdef1h1j, abcdef1hi1, abcdef1hij, abcdefg3, abcdefg2j, abcdefg1i1, abcdefg1ij, abcdefgh2, abcdefgh1j, abcdefghi1, abcdefghij
GeneralizedAbbreviation Validate for "internationalization" and "i12iz4n": 1
GeneralizedAbbreviation Validate for "apple" and "a2e": 0
*/
#endif
