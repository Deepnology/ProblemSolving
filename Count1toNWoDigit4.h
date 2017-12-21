/*MUST*/
#ifndef COUNT_1toN_WO_DIGIT_4_H
#define COUNT_1toN_WO_DIGIT_4_H
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <math.h>
#include "Debug.h"
/*
http://www.careercup.com/question?id=4752301805797376
https://sites.google.com/site/spaceofjameschen/annnocements/countthenumberofpositiveintegerslessthannthatdoesnotcontainsdigit4--google
Count the number of positive integer less than N that does not contain digit 4.

For 1~100 (hundred-decade), there are 9*9 numbers that doesn't contain digit 4.
(100 subtract 40~49, 4, 14, 24, 34, 54, 64, 74, 84, 94)
(then we got 9 10-decades with each contains 9 numbers)

For 1~1000 (thousand-decade), there are 9*9*9 numbers that doesn't contain digit 4.
(1000 subtract 400~499, and for each hundred-decade there are 9*9 numbers)
(then we got 9 hundred-decades with each contains 9 numbers)

For a number that falls in between of 10's power, 10, 100, 1000, 10000, etc., there are 3 cases.
a) If the most significant digit is less than 4, the count of numbers that doesn't contain digit 4 is msd * 9^(order of magnitude of 10's power) + the count for the remainder.
b) If the most significant digit is greater than, the count of numbers that doesn't contain digit 4 is (msd-1) * 9^(order of magnitude of 10's power) + the count for the remainder,
because we can just exclude the numbers with msd of 4.
c) If the most significant digit is 4, the count of number that doesn't contain digit 4 is equal to 3xxx..., which is 3 * 9^(order of magnitude of 10's power) + the count for the remainder,
where the remainder should be 999...
*/
class Count1toNWoDigit4
{
public:
	Count1toNWoDigit4(){}
	~Count1toNWoDigit4(){}

	int Recur(int n)
	{
		int res = this->recur(n);
		std::cout << "Count1toNWoDigit4 Recur for \"" << n << "\": " << res << std::endl;
		return res;
	}
	int recur(int n)
	{
		/*base cases for n is a single digit*/
		if (n < 4)
			return n;
		if (n >= 4 && n <= 9)
			return n - 1;


		int order = (int)floor(log10(n));
		int pow10 = (int)pow(10, order);

		int msd = n / pow10;
		int remainder = n % pow10;

		int pow9 = (int)pow(9, order);

		//similar to base case...
		if (msd < 4)
			return msd * pow9 + this->recur(remainder);//ex 378: should count from [1:300] and [1:78], where [1:300] equals to 3*9^2
		else if (msd == 4)
			return (msd - 1) * pow9 + this->recur(pow10 - 1);//ex 478: should count from [1:399], which is equivalent to [1:300] and [1:99], where [1:300] equals to 3*9^2 
		else
			return (msd - 1) * pow9 + this->recur(remainder);//ex 578: should count from [1:399], [500], and [1,78], where "[1:399] and [500]" equals to 4*9^2
															 //ex 678: should count from [1:399], [500], [501:600], and [1:78], where "[1:399], [500], and [501:600]" equals to 5*9^2
	}
};
/*
Count1toNWoDigit4 Recur for "100": 81
Count1toNWoDigit4 Recur for "400": 323
Count1toNWoDigit4 Recur for "10000": 6561
Count1toNWoDigit4 Recur for "72481643": 29996891
*/
#endif