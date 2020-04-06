/*MUST*/
#ifndef INCREMENT_DIGIT_STREAM_H
#define INCREMENT_DIGIT_STREAM_H
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <sstream>
#include "Debug.h"
/*
http://www.careercup.com/question?id=14945498
Write a function that takes a "single digit" stream and returns the whole number incremented by 1.
For example, if the stream is 878999, the function takes single digits as 8,7,8,9,9,9, and returns 879000.

Algorithm
need to keep track of the digit priori the first 9, the number of consecutive 9s
then the incremented number will be "digitPrior9 + 1" followed by "count9" 0s
*/
class IncrementDigitStream
{
public:
	IncrementDigitStream(){}
	~IncrementDigitStream(){}

	void Solve(const std::vector<int> & stream)
	{
		int digitPrior9 = 0;//keep track of digitPrior9 whose value isn't 9
		int count9 = 0;//keep track of count9
		std::ostringstream curNum;//the number with all the input digits so far w/o digitPrior9 and w/o count9
		std::string curIncremented;
		int N = stream.size();
		for (int i = 0; i < N; ++i)
		{
			curIncremented = this->Increment(stream[i], digitPrior9, count9, curNum);
			std::cout << curIncremented << std::endl;
		}

		std::cout << "IncrementDigitStream for \"" << Debug::ToStr1D<int>()(stream) << "\": " << curIncremented << std::endl;
	}
	
	std::string Increment(int digit, int & digitPrior9, int & count9, std::ostringstream & curNum)
	{
		if (digit == 9)//current digit is 9: increment count9
		{
			++count9;
		}
		else//current digit is not 9: add all digitPrior9 and count9 to curNum
		{
			//1. append the digit prior 9
			if (!(curNum.str().empty() && digitPrior9 == 0))
				curNum << digitPrior9;
			//2. append 9s
			while (count9)
			{
				curNum << 9;
				--count9;
			}
			//3. update
			digitPrior9 = digit;
		}


		//do increment
		std::ostringstream oss;
		oss << curNum.str();
		int count0 = count9;

		//1. append the incremented digit prior 9
		oss << (digitPrior9 + 1);
		//2. append 0s for number of 9s
		while (count0)
		{
			oss << 0;
			--count0;
		}
		return oss.str();
	}
};
/*
8
79
790
7900
79000
790000
7900000
79000000
790000000
IncrementDigitStream for "7, 8, 9, 9, 9, 9, 9, 9, 9": 790000000
10
99
990
9900
99000
IncrementDigitStream for "9, 8, 9, 9, 9": 99000
10
100
1000
10000
100000
IncrementDigitStream for "9, 9, 9, 9, 9": 100000
2
12
120
1200
11992
119912
1199112
IncrementDigitStream for "1, 1, 9, 9, 1, 1, 1": 1199112
10
91
901
9010
90091
900902
9009011
IncrementDigitStream for "9, 0, 0, 9, 0, 1, 0": 9009011
1
1
10
91
910
9100
90991
909906
9099060
90990591
909905910
9099059091
IncrementDigitStream for "0, 0, 9, 0, 9, 9, 0, 5, 9, 0, 9, 0": 9099059091
*/
#endif