/*MUST*/
#ifndef NUM_OF_2S_H
#define NUM_OF_2S_H
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include "Debug.h"
/*
Leetcode: Number of Digit One
Cracking the coding interview: Hard
Count the number of "digit-2"s that appear in all the numbers between 0 and n.

Algorithm
For each digit in the number:
1. digitNum < 2: roundDown / 10
61523 for digitIdx=3
02xxx
12xxx
22xxx
32xxx
42xxx
52xxx
=> 6000 2s in total
=> round down 61523 to 60000, then divided by 10 to get 6000

2. digitNum > 2: roundUp / 10
63523 for digitIdx=3
02xxx
12xxx
22xxx
32xxx
42xxx
52xxx
62xxx
=> 7000 2s in total
=> round up 63523 to 70000, then divided by 10 to get 7000

3. digitNum == 2: roundDown / 10 + right + 1
62523 for digitIdx=3
02xxx
12xxx
22xxx
32xxx
42xxx
52xxx
62xxx (62000-62523 only)
=> (6000 + 524) 2s in total
=> round down 62523 to 60000, then divided by 10 to get 6000
=> 62523 % 10^3 to get 523
*/
class NumOf2s
{
public:
	NumOf2s(){}
	~NumOf2s(){}
	/*BruteForce: count 2s for each number from 0 to N*/
	int BruteForce_0toN(int N)
	{
		int count = 0;
		for (int i = 2; i <= N; ++i)
		{
			count += this->BruteForce_SingleNum(i);
		}
		std::cout << "NumOf2s BruteForce for \"0 to " << N << "\": " << count << std::endl;
		return count;
	}
private:
	int BruteForce_SingleNum(int N)
	{
		int count = 0;
		while (N > 0)
		{
			if (N % 10 == 2)//if the lowest digit is equal to 2
				++count;
			N /= 10;
		}
		return count;
	}

public:
	/*DigitByDigit: count 2s for each digit in N*/
	int DigitByDigit_0toN(int N)
	{
		int count = 0;
		int digitCount = 0;
		int copy = N;
		while (copy > 0)
		{
			++digitCount;
			copy /= 10;
		}
		std::cout << "digitCount for \"" << N << "\": " << digitCount << std::endl;

		for (int i = 0; i < digitCount; ++i)
			count += this->SingleDigit(N, i);

		std::cout << "NumOf2s DigitByDigit for \"0 to " << N << "\": " << count << std::endl;
		return count;
	}
private:
	int SingleDigit(int N, int digitIdx)
	{
		int powOf10 = (int)std::pow(10, digitIdx);//10^digitIdx
		int nextPowOf10 = powOf10 * 10;

		int roundDown = N - N % nextPowOf10;//keep all higher digits and replace current digit and all lower digits with 0
		int roundUp = roundDown + nextPowOf10;//increment the first higher digit and replace current digit and all lower digits with 0

		int digitNum = (N / powOf10) % 10;
		int right = N % powOf10;//the digits on the right side of digitIdx

		std::cout << "digit, right, roundDown, roundUp: " << digitNum << ", " << right << ", " << roundDown << ", " << roundUp << std::endl;

		if (digitNum < 2)
		{
			return roundDown / 10;
		}
		else if (digitNum == 2)
		{
			return roundDown / 10 + right + 1;
		}
		else
		{
			return roundUp / 10;
		}
	}
};
/*
NumOf2s BruteForce for "0 to 25": 9
digitCount for "25": 2
digit, right, roundDown, roundUp: 5, 0, 20, 30
digit, right, roundDown, roundUp: 2, 5, 0, 100
NumOf2s DigitByDigit for "0 to 25": 9
NumOf2s BruteForce for "0 to 61523": 34507
digitCount for "61523": 5
digit, right, roundDown, roundUp: 3, 0, 61520, 61530
digit, right, roundDown, roundUp: 2, 3, 61500, 61600
digit, right, roundDown, roundUp: 5, 23, 61000, 62000
digit, right, roundDown, roundUp: 1, 523, 60000, 70000
digit, right, roundDown, roundUp: 6, 1523, 0, 100000
NumOf2s DigitByDigit for "0 to 61523": 34507
NumOf2s BruteForce for "0 to 63523": 36107
digitCount for "63523": 5
digit, right, roundDown, roundUp: 3, 0, 63520, 63530
digit, right, roundDown, roundUp: 2, 3, 63500, 63600
digit, right, roundDown, roundUp: 5, 23, 63000, 64000
digit, right, roundDown, roundUp: 3, 523, 60000, 70000
digit, right, roundDown, roundUp: 6, 3523, 0, 100000
NumOf2s DigitByDigit for "0 to 63523": 36107
NumOf2s BruteForce for "0 to 62523": 35331
digitCount for "62523": 5
digit, right, roundDown, roundUp: 3, 0, 62520, 62530
digit, right, roundDown, roundUp: 2, 3, 62500, 62600
digit, right, roundDown, roundUp: 5, 23, 62000, 63000
digit, right, roundDown, roundUp: 2, 523, 60000, 70000
digit, right, roundDown, roundUp: 6, 2523, 0, 100000
NumOf2s DigitByDigit for "0 to 62523": 35331
*/
#endif