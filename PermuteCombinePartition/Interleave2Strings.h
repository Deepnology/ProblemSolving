/*Recur*/
#ifndef INTERLEAVE_2_STRINGS_H
#define INTERLEAVE_2_STRINGS_H
#include <vector>
#include <string>
#include <iostream>
#include "Debug.h"
/*
Google
http://www.careercup.com/question?id=14360665
Given 2 strings.
Find out all the interleavings of the 2 strings.
For example:
"ab" and "cd": abcd, acbd, acdb, cabd, cadb, cdab
"abcd" and "xy": abcdxy, abcxdy, abcxyd, abxcdy, abxcyd, abxycd, axbcdy, axbcyd, axbycd, axybcd, xabcdy, xabcyd, xabycd, xaybcd, xyabcd
*/
class Interleave2Strings
{
public:
	Interleave2Strings(){}
	~Interleave2Strings(){}

	std::vector<std::string> Recur(const std::string & s1, const std::string & s2)
	{
		std::vector<std::string> res;
		std::string path;
		this->recur(s1, s2, 0, 0, path, res);
		std::cout << "Interleave2Strings for \"" << s1 << "\", \"" << s2 << "\": " << Debug::ToStr1D<std::string>()(res) << std::endl;
		return res;
	}

	void recur(const std::string & s1, const std::string & s2, int i1, int i2, std::string & path, std::vector<std::string> & res)
	{
		int N1 = s1.size();
		int N2 = s2.size();
		if (i1 == N1 && i2 == N2)
		{
			res.push_back(path);
			return;
		}

		if (i1 == N1)
		{
			path.append(s2.substr(i2));
			this->recur(s1, s2, N1, N2, path, res);
			path.erase(i1 + i2);
			return;
		}
		if (i2 == N2)
		{
			path.append(s1.substr(i1));
			this->recur(s1, s2, N1, N2, path, res);
			path.erase(i1 + i2);
			return;
		}
		
		path += s1[i1];
		this->recur(s1, s2, i1 + 1, i2, path, res);
		path.pop_back();
		path += s2[i2];
		this->recur(s1, s2, i1, i2 + 1, path, res);
		path.pop_back();
	}

};
/*
Interleave2Strings for "ab", "cd": abcd, acbd, acdb, cabd, cadb, cdab
Interleave2Strings for "abcd", "xy": abcdxy, abcxdy, abcxyd, abxcdy, abxcyd, abxycd, axbcdy, axbcyd, axbycd, axybcd, xabcdy, xabcyd, xabycd, xaybcd, xyabcd
*/
#endif