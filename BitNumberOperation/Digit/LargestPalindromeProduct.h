#ifndef LARGEST_PALINDROME_PRODUCT_H
#define LARGEST_PALINDROME_PRODUCT_H
#include "Debug.h"
/*
Leetcode: Largest Palindrome Product
Find the largest palindrome made from the product of two n-digit numbers.
Since the result could be very large, you should return the largest palindrome mod 1337.
Example:
Input: 2
Output: 987
Explanation: 99 x 91 = 9009, 9009 % 1337 = 987
Note:
The range of n is [1,8].

n = 2
palindrom is: 9009
number returned: 987

n = 3
palindrom is: 906609
number returned: 123

n = 4
palindrom is: 99000099
number returned: 597

n = 5
palindrom is: 9966006699
number returned: 677

n = 6
palindrom is: 999000000999
number returned: 1218

n = 7
palindrom is: 99956644665999
number returned: 877

n = 8
palindrom is: 9999000000009999
number returned: 475

n = 9
palindrom is: 999900665566009999
number returned: 1226

n = 10
palindrom is: 461168600006861164
number returned: 670
*/
class LargestPalindromeProduct
{
public:
	LargestPalindromeProduct() {}
	int ConstructCandidatePalindrome(int n)//Passed OJ
	{
		if (n == 1) return 9;
		int upper = 9;
		int lower = 1;
		int numDigit = n;
		while (--numDigit)
		{
			upper = upper * 10 + 9;
			lower = lower * 10;
		}
		for (int i = upper; i >= lower; --i)
		{
			std::string revNum = std::to_string(i);
			std::reverse(revNum.begin(), revNum.end());
			long long palindrome = stoll(std::to_string(i) + revNum);
			//sqrt(palindrome): test only the bigger half factors of palindrome; palindrome/upper: the smallest possible j
			for (int j = upper; j >= std::max((long long)sqrt(palindrome), palindrome / upper); --j)
				if (palindrome%j == 0)
				{
					std::cout << "LargestPalindromeProduct ConstructCandidatePalindrome for \"" << n << "\"-digits: " << palindrome << std::endl;
					return palindrome % 1337;
				}
		}
		return 0;
	}

	int EnumerateAllNumsInRange(int n)//Time Limit Exceeded
	{
		if (n == 1) return 9;
		long long upper = 9;
		long long lower = 1;
		int numDigit = n;
		while (--numDigit)
		{
			upper = upper * 10 + 9;
			lower = lower * 10;
		}
		long long upperNum = upper*upper;
		long long lowerNum = lower*lower;
		for (long long i = upperNum; i >= lowerNum; --i)
		{
			if (isPalindrome(i))
			{
				long long upperMin = (long long)ceil(i / upper);
				for (long long j = upper; j >= upperMin; --j)
				{
					if (i%j == 0)
					{
						std::cout << "LargestPalindromeProduct EnumerateAllNumsInRange for \"" << n << "\"-digits: " << i << std::endl;
						return i % 1337;
					}
				}
			}
		}
		return 0;
	}
private:
	bool isPalindrome(long long x)
	{
		if (x < 0)
			return false;
		//if x = 823454328
		//=> d = 100000000
		long long d = 1;
		while (d * 10 < x)
			d *= 10;
		while (x > 0)
		{
			if (x / d != x % 10)
				return false;

			//if the 1st digit matches the last digit
			x = (x % d) / 10;//remove the 1st digit by x %= 10, and remove the last digit by that result /= 10
			d /= 100;//remove two digits
			//(when 0 < x < 10, x /= 10 will be 0)
		}
		return true;
	}
};
/*
LargestPalindromeProduct ConstructCandidatePalindrome for "2"-digits: 9009
LargestPalindromeProduct ConstructCandidatePalindrome for "3"-digits: 906609
LargestPalindromeProduct ConstructCandidatePalindrome for "4"-digits: 99000099
LargestPalindromeProduct ConstructCandidatePalindrome for "5"-digits: 9966006699
LargestPalindromeProduct ConstructCandidatePalindrome for "6"-digits: 999000000999
LargestPalindromeProduct ConstructCandidatePalindrome for "7"-digits: 99956644665999
LargestPalindromeProduct ConstructCandidatePalindrome for "8"-digits: 9999000000009999
LargestPalindromeProduct EnumerateAllNumsInRange for "2"-digits: 9009
LargestPalindromeProduct EnumerateAllNumsInRange for "3"-digits: 906609
LargestPalindromeProduct EnumerateAllNumsInRange for "4"-digits: 99000099
LargestPalindromeProduct EnumerateAllNumsInRange for "5"-digits: 9966006699
*/
#endif
