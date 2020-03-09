#ifndef LETTER_COMBINATION_PHONE_NUM_H
#define LETTER_COMBINATION_PHONE_NUM_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, Strings: Compute all mnemonics for a phone number
Leetcode: Letter Combinations Of a Phone Number
// Given a digit string, return all possible letter combinations that the
// number could represent.
//
// Input:Digit string "23"
// Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
// Note:
// Although the above answer is in lexicographical order, your answer could be
// in any order you want.

O(4^n * n) time, where n is the length of the input digits
*/
class LetterCombinationPhoneNum
{
public:
	LetterCombinationPhoneNum(){}
	~LetterCombinationPhoneNum(){}

	std::vector<std::string> Recur(const std::string & digits)
	{
		std::string path;
		std::vector<std::string> res;
		this->recur(digits, 0, path, res);
		std::cout << "LetterCombinationPhoneNum Recur for \"" << digits << "\": " << Debug::ToStr1D<std::string>()(res) << std::endl;
		return res;
	}
private:
	void recur(const std::string & digits, int begin, std::string & path,
		std::vector<std::string> & res)
	{
		if (begin == digits.size())
		{
			res.push_back(path);
			return;
		}
		/*
		for each char in the key set that begin points to
		(ex. 2: abc)
		add to path and recur down to the next level
		*/
		for (char c : keypad[digits[begin] - '0'])
		{
			path.push_back(c);
			this->recur(digits, begin + 1, path, res);
			path.pop_back();
		}
	}
public:
	std::vector<std::string> Iterate(const std::string & digits)
	{
		std::vector<std::string> res(1, "");
		int N = digits.size();
		for (int i = 0; i < N; ++i)
		{
			/*
			for each existing in-complete combination
			for each next possible char of that existing combination
			copy that existing combination and append the next possible char if that next possible char isn't the last one
			or just append the next possible char if that next possible char is the last one
			*/
			std::string keySet = keypad[digits[i] - '0'];
			int M = res.size();
			for (int j = 0; j < M; ++j)
			{
				int K = keySet.size();
				for (int k = 0; k < K; ++k)
				{
					if (k == K - 1)//2. (no longer need to make copies of prev str res[j]) just append keySet[k] to prev str res[j] (to replace the prev str res[j])
						res[j].push_back(keySet[k]);
					else//1. make copies of prev str res[j], append keySet[k], push back
					{
						auto copy = res[j];
						copy.push_back(keySet[k]);
						res.push_back(copy);
					}
					std::cout << "->" << Debug::ToStr1D<std::string>()(res) << std::endl;
				}
			}
			std::cout << Debug::ToStr1D<std::string>()(res) << std::endl;
		}
		std::cout << "LetterCombinationPhoneNum Iterate for \"" << digits << "\": " << Debug::ToStr1D<std::string>()(res) << std::endl;
		return res;
	}

private:
	static std::string keypad[];
};
std::string LetterCombinationPhoneNum::keypad[] =
{ "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };
/* 0,  1,   2,     3,     4,     5,     6,      7,     8,      9*/

/*
LetterCombinationPhoneNum Recur for "232": ada, adb, adc, aea, aeb, aec, afa, afb, afc, bda, bdb, bdc, bea, beb, bec, bfa, bfb, bfc, cda, cdb, cdc, cea, ceb, cec, cfa, cfb, cfc
->, a
->, a, b
->c, a, b
c, a, b
->c, a, b, cd
->c, a, b, cd, ce
->cf, a, b, cd, ce
->cf, a, b, cd, ce, ad
->cf, a, b, cd, ce, ad, ae
->cf, af, b, cd, ce, ad, ae
->cf, af, b, cd, ce, ad, ae, bd
->cf, af, b, cd, ce, ad, ae, bd, be
->cf, af, bf, cd, ce, ad, ae, bd, be
cf, af, bf, cd, ce, ad, ae, bd, be
->cf, af, bf, cd, ce, ad, ae, bd, be, cfa
->cf, af, bf, cd, ce, ad, ae, bd, be, cfa, cfb
->cfc, af, bf, cd, ce, ad, ae, bd, be, cfa, cfb
->cfc, af, bf, cd, ce, ad, ae, bd, be, cfa, cfb, afa
->cfc, af, bf, cd, ce, ad, ae, bd, be, cfa, cfb, afa, afb
->cfc, afc, bf, cd, ce, ad, ae, bd, be, cfa, cfb, afa, afb
->cfc, afc, bf, cd, ce, ad, ae, bd, be, cfa, cfb, afa, afb, bfa
->cfc, afc, bf, cd, ce, ad, ae, bd, be, cfa, cfb, afa, afb, bfa, bfb
->cfc, afc, bfc, cd, ce, ad, ae, bd, be, cfa, cfb, afa, afb, bfa, bfb
->cfc, afc, bfc, cd, ce, ad, ae, bd, be, cfa, cfb, afa, afb, bfa, bfb, cda
->cfc, afc, bfc, cd, ce, ad, ae, bd, be, cfa, cfb, afa, afb, bfa, bfb, cda, cdb
->cfc, afc, bfc, cdc, ce, ad, ae, bd, be, cfa, cfb, afa, afb, bfa, bfb, cda, cdb
->cfc, afc, bfc, cdc, ce, ad, ae, bd, be, cfa, cfb, afa, afb, bfa, bfb, cda, cdb, cea
->cfc, afc, bfc, cdc, ce, ad, ae, bd, be, cfa, cfb, afa, afb, bfa, bfb, cda, cdb, cea, ceb
->cfc, afc, bfc, cdc, cec, ad, ae, bd, be, cfa, cfb, afa, afb, bfa, bfb, cda, cdb, cea, ceb
->cfc, afc, bfc, cdc, cec, ad, ae, bd, be, cfa, cfb, afa, afb, bfa, bfb, cda, cdb, cea, ceb, ada
->cfc, afc, bfc, cdc, cec, ad, ae, bd, be, cfa, cfb, afa, afb, bfa, bfb, cda, cdb, cea, ceb, ada, adb
->cfc, afc, bfc, cdc, cec, adc, ae, bd, be, cfa, cfb, afa, afb, bfa, bfb, cda, cdb, cea, ceb, ada, adb
->cfc, afc, bfc, cdc, cec, adc, ae, bd, be, cfa, cfb, afa, afb, bfa, bfb, cda, cdb, cea, ceb, ada, adb, aea
->cfc, afc, bfc, cdc, cec, adc, ae, bd, be, cfa, cfb, afa, afb, bfa, bfb, cda, cdb, cea, ceb, ada, adb, aea, aeb
->cfc, afc, bfc, cdc, cec, adc, aec, bd, be, cfa, cfb, afa, afb, bfa, bfb, cda, cdb, cea, ceb, ada, adb, aea, aeb
->cfc, afc, bfc, cdc, cec, adc, aec, bd, be, cfa, cfb, afa, afb, bfa, bfb, cda, cdb, cea, ceb, ada, adb, aea, aeb, bda
->cfc, afc, bfc, cdc, cec, adc, aec, bd, be, cfa, cfb, afa, afb, bfa, bfb, cda, cdb, cea, ceb, ada, adb, aea, aeb, bda, bdb
->cfc, afc, bfc, cdc, cec, adc, aec, bdc, be, cfa, cfb, afa, afb, bfa, bfb, cda, cdb, cea, ceb, ada, adb, aea, aeb, bda, bdb
->cfc, afc, bfc, cdc, cec, adc, aec, bdc, be, cfa, cfb, afa, afb, bfa, bfb, cda, cdb, cea, ceb, ada, adb, aea, aeb, bda, bdb, bea
->cfc, afc, bfc, cdc, cec, adc, aec, bdc, be, cfa, cfb, afa, afb, bfa, bfb, cda, cdb, cea, ceb, ada, adb, aea, aeb, bda, bdb, bea, beb
->cfc, afc, bfc, cdc, cec, adc, aec, bdc, bec, cfa, cfb, afa, afb, bfa, bfb, cda, cdb, cea, ceb, ada, adb, aea, aeb, bda, bdb, bea, beb
cfc, afc, bfc, cdc, cec, adc, aec, bdc, bec, cfa, cfb, afa, afb, bfa, bfb, cda, cdb, cea, ceb, ada, adb, aea, aeb, bda, bdb, bea, beb
LetterCombinationPhoneNum Iterate for "232": cfc, afc, bfc, cdc, cec, adc, aec, bdc, bec, cfa, cfb, afa, afb, bfa, bfb, cda, cdb, cea, ceb, ada, adb, aea, aeb, bda, bdb, bea, beb
*/
#endif