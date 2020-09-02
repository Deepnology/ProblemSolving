#ifndef FIBONACCI_NUMBER_H
#define FIBONACCI_NUMBER_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <math.h>
#include "Debug.h"
/*
Leetcode: Fibonacci Number
http://www.geeksforgeeks.org/program-for-nth-fibonacci-number/
http://www.careercup.com/question?id=62018
1. Fibonacci Numbers:
f(0) = 0
f(1) = 1
f(n) = f(n-1) + f(n-2)
First few Fibonacci numbers: 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 141, ...

http://www.geeksforgeeks.org/check-number-fibonacci-number/
2. Check if a number is a Fibonacci number.
A number is Fibonacci if and only if one or both of (5*n^2+4) or (5*n^2-4) is a perfect square.

http://www.geeksforgeeks.org/nth-non-fibonacci-number/
3. N-th Non Fibonacci Number

4. Leetcode: N-th Tribonacci Number

*/
class FibonacciNumber
{
public:
	FibonacciNumber(){}
	~FibonacciNumber(){}

	//1. f(n) = f(n-1) + f(n-2)
	int Recur(int n)
	{
		int res = this->recur(n);
		std::cout << "FibonacciNumber Recur for \"" << n << "\": " << res << std::endl;
		return res;
	}
private:
	int recur(int n)
	{
		if (n <= 1)
			return n;
		return this->recur(n - 1) + this->recur(n - 2);
	}

public:
	int DP1D_Recur(int n)
	{
		std::vector<int> dp(n + 1, 0);
		//dp[n] is the Fibonacci number of n
		int res = this->dP1D_Recur(n, dp);
		std::cout << Debug::ToStr1D<int>()(dp) << std::endl;
		std::cout << "FibonacciNumber DP1D_Recur for \"" << n << "\": " << res << std::endl;
		return res;
	}
private:
	int dP1D_Recur(int n, std::vector<int> & dp)
	{
		if (n <= 1)
			return dp[n] = n;
		if (dp[n] != 0)
			return dp[n];
		return dp[n] = this->dP1D_Recur(n - 1, dp) + this->dP1D_Recur(n - 2, dp);
	}

public:
	int DP1D_Iterate(int n)
	{
		std::vector<int> dp(n + 1, 0);
		dp[0] = 0;
		dp[1] = 1;
		for (int i = 2; i <= n; ++i)
			dp[i] = dp[i - 1] + dp[i - 2];
		
		std::cout << Debug::ToStr1D<int>()(dp) << std::endl;
		std::cout << "FibonacciNumber DP1D_Iterate for \"" << n << "\": " << dp[n] << std::endl;
		return dp[n];
	}

	int Iterate(int n)
	{
		if (n <= 1)
			return n;
		int prev1 = 0;
		int prev2 = 1;
		int cur;
		for (int i = 2; i <= n; ++i)
		{
			cur = prev1 + prev2;
			prev1 = prev2;
			prev2 = cur;
		}
		std::cout << "FibonacciNumber Iterate for \"" << n << "\": " << cur << std::endl;
		return cur;
	}


public:
	//2. valid Fibonacci number
	bool Valid_2PerfectSquare(int n)
	{
		bool res = this->ValidPerfectSquare(5 * n*n + 4) ||
			this->ValidPerfectSquare(5 * n*n - 4);

		std::cout << "FibonacciNumber Valid for \"" << n << "\": " << res << std::endl;
		return res;
	}
private:
	bool ValidPerfectSquare(int n)
	{
		int squareRoot = (int)std::sqrt(n);
		return (squareRoot * squareRoot == n);
	}

public:
	//3. n-th Non-Fibonacci number
	int NonFibonacci(int n)
	{
		//start from 1,1,2,... to avoid count+=-1
		int prev1 = 1;
		int prev2 = 1;
		int cur;
		int count = 0;//nums in FibonacciNum's gap
		while (true)
		{
			cur = prev1 + prev2;
			count += (cur - prev2 - 1);//if start from 0,1,1,..., when cur==1, it will become count+=-1, so skip 0
			if (count >= n)
				break;
			prev1 = prev2;
			prev2 = cur;
		}
		//now: count = num of NonFib before cur
		//count - (cur-prev2-1) = num of NonFib before prev2
		//n - (count-(cur-prev2-1)) = num of NonFib after prev2
		std::cout << prev1 << "," << prev2 << "," << cur << ": " << count << std::endl;
		std::cout << "FibonacciNumber Non-Fibonacci for \"" << n << "\": " << prev2 + n - (count - (cur - prev2 - 1)) << std::endl;
		return prev2 + n - (count - (cur - prev2 - 1));
	}

	//4. Nth Tribonacci Number
    int Tribonacci(int n)
    {
        if (n < 2) return n;
        if (n == 2) return 1;
        int a = 0, b = 1, c = 1;
        int d;
        for (int i = 3; i <= n; ++i)
        {
            d = a + b + c;
            a = b;
            b = c;
            c = d;
        }
        return d;
    }
};
/*
FibonacciNumber Recur for "10": 55
0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55
FibonacciNumber DP1D_Recur for "10": 55
0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55
FibonacciNumber DP1D_Iterate for "10": 55
FibonacciNumber Iterate for "10": 55
FibonacciNumber Valid for "123": 0
FibonacciNumber Valid for "55": 1
2,3,5: 1
FibonacciNumber Non-Fibonacci for "1": 4
3,5,8: 3
FibonacciNumber Non-Fibonacci for "2": 6
3,5,8: 3
FibonacciNumber Non-Fibonacci for "3": 7
5,8,13: 7
FibonacciNumber Non-Fibonacci for "4": 9
5,8,13: 7
FibonacciNumber Non-Fibonacci for "5": 10
5,8,13: 7
FibonacciNumber Non-Fibonacci for "6": 11
5,8,13: 7
FibonacciNumber Non-Fibonacci for "7": 12
8,13,21: 14
FibonacciNumber Non-Fibonacci for "8": 14
8,13,21: 14
FibonacciNumber Non-Fibonacci for "9": 15
8,13,21: 14
FibonacciNumber Non-Fibonacci for "10": 16
*/
#endif