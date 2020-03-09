#ifndef COUNT_AND_SAY_H
#define COUNT_AND_SAY_H
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include "Debug.h"
/*
Elements of programming interview, Strings: The look-and-say problem
Leetcode: Count And Say
Notes:
The count-and-say sequence is the sequence of integers beginning as follows:
1, 11, 21, 1211, 111221, ...

1 is read off as "one 1" or 11.
11 is read off as "two 1s" or 21.
21 is read off as "one 2, then one 1" or 1211.
Given an integer n, generate the nth sequence.

Note: The sequence of integers will be represented as a string.
*/
class CountAndSay
{
public:
	CountAndSay(){}
	~CountAndSay(){}

	std::string GO(int n)
	{
		std::vector<std::string> res;
		res.push_back("1");//the first element is always 1
		while ((int)res.size() < n)
		{
			std::string prevSeq = res.back();
			std::ostringstream curSeq;
			int N = prevSeq.size();
			for (int i = 0; i < N; ++i)
			{
				int sameCount = 1;
				while (i < N - 1 && prevSeq[i] == prevSeq[i + 1])
				{
					++sameCount;
					++i;
				}
				//now i points to the last same char
				curSeq << sameCount << prevSeq[i];
			}
			res.push_back(curSeq.str());
		}
		
		std::cout << "CountAndSay for \""<< n << "\" sequences: " << Debug::ToStr1D<std::string>()(res) << std::endl;
		return res[n - 1];//return the n-th sequence
	}
};
/*
CountAndSay for "7" sequences: 1, 11, 21, 1211, 111221, 312211, 13112221
*/
#endif