#ifndef NEXT_PREV_NUM_W_SAME_DIGITS_H
#define NEXT_PREV_NUM_W_SAME_DIGITS_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include "Debug.h"
/*
Google
http://www.careercup.com/question?id=4869907900530688
http://stackoverflow.com/questions/9368205/given-a-number-find-the-next-higher-number-which-has-the-exact-same-set-of-digi
http://www.ardendertat.com/2012/01/02/programming-interview-questions-24-find-next-higher-number-with-same-digits/
=> Check also NextPermutation.h, PreviousPermutation.h !! (better)
Next big: find ascendingEnd from right, reverse n[ascendingEnd]~n[end], find upper bound<less> of n[ascendingEnd-1] in n[ascendingEnd]~n[end] and swap.
Prev small: find descendingEnd from right, reverse n[descendingEnd]~n[end], find upper bound<greater> of n[descendingEnd-1] in n[descendingEnd]~n[end] and swap.

Here is another way:
																					123456784987654321
1. from left to right, find leftest digit where its right are in ascending order:			^
																					123456784987654321
2. find the smallest but greater than the found digit on its right side:						 ^
																					123456785987644321
3. swap the above two digits:															    ^    ^
																					123456785123446789
4. sort (reverse) the first found digit's right side:									    ^
*/
class NextPrevNumWSameDigits
{
public:
	NextPrevNumWSameDigits(){}
	~NextPrevNumWSameDigits(){}

	int NextHigher(int n)
	{
		if (n <= 0)
			return -1;
		std::cout << "NextPrevNumWSameDigits NextHigher for \"" << n << "\": ";
		std::vector<int> digits;
		int copy = n;
		while (copy)
		{
			digits.push_back(copy % 10);
			copy /= 10;
		}
		//now left to right: lower digits to higher digits
		int N = digits.size();
		if (N == 1)
		{
			std::cout << n << std::endl;
			return n;
		}
		std::reverse(digits.begin(), digits.end());
		//now left to right: higher digits to lower digits

		//1.
		//scan from the lowest digit
		//find the first digit such that cur < right
		//(all the digits on cur's right side will be in ascending order from right to left)
		int ascendingEnd = N - 1;
		while (ascendingEnd > 0 && digits[ascendingEnd - 1] >= digits[ascendingEnd])
			--ascendingEnd;
		//now digits[ascendingEnd]~digits[N-1] are sorted

		if (ascendingEnd == 0)
		{
			std::reverse(digits.begin(), digits.end());
			int res = 0;
			for (int i = 0; i < N; ++i)
				res = res * 10 + digits[i];
			std::cout << res << std::endl;
			return res;
		}

		int pivot = ascendingEnd - 1;
		//2.
		//find the smallest digit that is greater than digits[pivot] in sorted digits[ascendingEnd]~digits[N-1]
		//since the descending order lower bound is the first element that doesn't compare greater than pivot (compare equal to or smaller than): O(logn)
		//so we want to find the prev element of the lower bound element
		int descendingLowerBound = std::lower_bound(digits.begin() + ascendingEnd, digits.end(), digits[pivot], std::greater<int>()) - digits.begin();
		//descendingLowerBound might be N when it cannot find the first element that doesn't compare greater than pivot

		//3. swap
		std::swap(digits[pivot], digits[descendingLowerBound - 1]);

		//4. sort digits[ascendingEnd]~digits[N-1] in ascending order
		//since digits[ascendingEnd]~digits[N-1] are in descending order
		//so we just need to reverse it
		std::reverse(digits.begin() + ascendingEnd, digits.end());

		int res = 0;
		for (int i = 0; i < N; ++i)
			res = res * 10 + digits[i];

		std::cout << res << std::endl;
		return res;
	}
};
/*
NextPrevNumWSameDigits NextHigher for "324987531": 325134789
NextPermutation for "3, 2, 4, 9, 8, 7, 5, 3, 1": 3, 2, 5, 1, 3, 4, 7, 8, 9
NextPrevNumWSameDigits NextHigher for "987654321": 123456789
NextPermutation for "9, 8, 7, 6, 5, 4, 3, 2, 1": 1, 2, 3, 4, 5, 6, 7, 8, 9
NextPrevNumWSameDigits NextHigher for "324988765": 325467889
NextPermutation for "3, 2, 4, 9, 8, 8, 7, 6, 5": 3, 2, 5, 4, 6, 7, 8, 8, 9
NextPrevNumWSameDigits NextHigher for "324987654": 325446789
NextPermutation for "3, 2, 4, 9, 8, 7, 6, 5, 4": 3, 2, 5, 4, 4, 6, 7, 8, 9
*/
#endif