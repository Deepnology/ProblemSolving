#ifndef POOR_PIGS_H
#define POOR_PIGS_H
#include "Debug.h"
/*
Leetcode: Poor Pigs
There are 1000 buckets, one and only one of them contains poison, the rest are filled with water.
They all look the same.
If a pig drinks that poison it will die within 15 minutes.
What is the minimum amount of pigs you need to figure out which bucket contains the poison within one hour.
Answer this question, and write an algorithm for the follow-up general case.
Follow-up:
If there are n buckets and a pig drinking poison will die within m minutes, how many pigs (x) you need to figure out the "poison" bucket within p minutes?
There is exact one bucket with poison.

Base case: 4 buckets, 15 mins to die, 15 mins to test
buckets:   0   1   2   3
drink by:     A_  _B  AB
binary:   00  10  01  11

2nd case: 8 buckets, 15 mins to die, 40 mins to test
buckets:   0   1   2   3   4   5   6   7
3-based:  00  01  02  10  11  12  20  21
first-rd: __  _B  __  A_  AB  A_  __  _B
second-rd:__  __  _B  __  __  _B  A_  _B

=> each pig represents a digit
=> if we have t tests, we can use t+1 based number to represent (encode) the buckets
=> digit 0 means that digit's corresponding pig doesn't drink
, digit 1 means it drink in 1st round
, digit 2 means it drink in 2nd round
, ....
*/
class PoorPigs
{
public:
	PoorPigs() {}

	int MinNumPigs(int buckets, int minutesToDie, int minutesToTest)
	{
		//if we have numTests allowed, we can use "numbers w/ base = numTests+1" to represent the test results of each bucket
		int numTests = minutesToTest / minutesToDie;
		int numBase = numTests + 1;
		//numPigs = numDigits to represent [0:numBuckets-1] = ceil (log       numBuckets) = ceil (log (numBuckets)/log (numBase))
		//                                                             numBase                       2                2
		int numDigits = (int)std::ceil(log(buckets) / log(numBase));

		std::cout << "PoorPigs MinNumPigs for buckets=\"" << buckets << "\", minutesToDie=\"" << minutesToDie << "\", minutesToTest=\"" << minutesToTest << "\": " << numDigits << std::endl;
		return numDigits;
	}
};
/*
PoorPigs MinNumPigs for buckets="4", minutesToDie="15", minutesToTest="15": 2
PoorPigs MinNumPigs for buckets="8", minutesToDie="15", minutesToTest="40": 2
PoorPigs MinNumPigs for buckets="1000", minutesToDie="15", minutesToTest="60": 5
*/
#endif
