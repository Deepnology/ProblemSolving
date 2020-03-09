#ifndef NEXT_PRE_PALINDROME_NUM_H
#define NEXT_PRE_PALINDROME_NUM_H
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Debug.h"
/*
http://www.geeksforgeeks.org/given-a-number-find-next-smallest-palindrome-larger-than-this-number/
http://www.ardendertat.com/2011/12/01/programming-interview-questions-19-find-next-palindrome-number/
see ClosestPalindromeNum.h
*/
class NextPrePalindromeNum
{
public:
	NextPrePalindromeNum(){}
	~NextPrePalindromeNum(){}

	void Next_InPlace(std::vector<int> & A)
	{
		std::string before = Debug::ToStr1D<int>()(A);
		int N = A.size();

		/*
		1. if all digits are 9:
		add one more digit to array, and make head and tail 1, others 0
		*/
		bool all9s = true;
		for (int i = 0; i < N; ++i)
			if (A[i] != 9)
			{
				all9s = false;
				break;
			}
		if (all9s)
		{
			N += 1;
			A.resize(N);
			for (int i = 0; i < N; ++i)
				if (i == 0 || i == N - 1)
					A[i] = 1;
				else
					A[i] = 0;
		}
		else
		{
			/*
			2. transform the number to a CLOSEST palindrome number:
			start from middle, keep the left (higher) digits unchanged
			, and replace the right (lower) asymmetric digits with the left (higher) digits
			*/
			bool lessEqual = false;
			int mid = N / 2;//mid points to the right of middle pair for even N

			int left = mid - 1;//always mid-1
			int right = (N % 2 == 1) ? mid + 1 : mid;//mid+1 for odd N; mid for even N

			//2.1 skip symmetric digits from middle in both sides
			while (left >= 0 && A[left] == A[right])
				--left, ++right;

			if (left < 0 || A[left] < A[right])
				lessEqual = true;//A is less equal than the original number

			//2.2 replace right asymmetric digits with left digits
			while (left >= 0)
				A[right++] = A[left--];
			//now A is a CLOSEST palindrome

			/*
			3. the NEXT palindrome would be:
			increment the "left half digits" (should include mid for odd N; exclude mid for even N)
			, and replace right half digits with symmetric left digits
			*/
			if (lessEqual)
			{
				int carry = 1;
				left = mid - 1;//always mid-1

				//right = N%2==1 ? mid+1 : mid
				if (N % 2 == 1)//odd: increment the middle digit
				{
					A[mid] += carry;
					carry = A[mid] / 10;
					A[mid] %= 10;
					right = mid + 1;
				}
				else//even
					right = mid;

				//propagate carry for the left half digits
				//replace right half digits with symmetric left digits
				while (left >= 0)
				{
					A[left] += carry;
					carry = A[left] / 10;
					A[left] %= 10;
					A[right++] = A[left--];
				}
			}
		}

		std::cout << "NextPrePalindromeNum Array for \"" << before << "\": " << Debug::ToStr1D<int>()(A) << std::endl;
	}

	int Next(int n)
	{
		int before = n;
		std::vector<int> num;
		while (n)
		{
			num.push_back(n % 10);
			n /= 10;
		}
		std::reverse(num.begin(), num.end());
		this->Next_InPlace(num);
		int res = 0;
		int N = num.size();
		for (int i = 0; i < N; ++i)
		{
			res = res * 10 + num[i];
		}
		std::cout << "NextPrePalindromeNum Int for \"" << before << "\": " << res << std::endl;
		return res;
	}
};
/*
NextPrePalindromeNum Array for "9, 9, 9, 9, 9": 1, 0, 0, 0, 0, 1
NextPrePalindromeNum Int for "99999": 100001
NextPrePalindromeNum Array for "1, 2, 9, 2, 1": 1, 3, 0, 3, 1
NextPrePalindromeNum Int for "12921": 13031
NextPrePalindromeNum Array for "8, 9, 9, 9, 9": 9, 0, 0, 0, 9
NextPrePalindromeNum Int for "89999": 90009
NextPrePalindromeNum Array for "9, 4, 8, 7, 9, 7, 8, 5, 9": 9, 4, 8, 8, 0, 8, 8, 4, 9
NextPrePalindromeNum Int for "948797859": 948808849
*/
#endif