/*MEMO*/
#ifndef CATALAN_NUMBER_H
#define CATALAN_NUMBER_H
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include "Debug.h"
/*
http://www.geeksforgeeks.org/program-nth-catalan-number/
http://www-groups.dcs.st-and.ac.uk/history/Miscellaneous/CatalanNumbers/catalan.html
The first few Catalan numbers for n = 0, 1, 2, 3, ... are 1, 1, 2, 5, 14, 42, 132, 429, 1430, 4862, 16796, ...

Applications:
1. Count the number of expressions containing n pairs of parentheses which are correctly matched
   For n=3: ((())), ()(()), ()()(), (())(), (()())
2. Count the number of possible Binary Search Tree with n keys, see also UniqueBinarySearchTree.h
3. Count the number of full binary trees with n+1 leaves
   (A rooted binary tree is full if every vertex has either two children or no children)
   For example, n = 3 (4 leaves)
     _x_      _x_     _x_     _x_     _x_
    /   \    /   \   /   \   /   \   /   \
    x   x    x   x   x   x   x   x   x   x
   / \ / \  / \     / \         / \     / \
   x x x x  x x     x x         x x     x x
           / \       / \       / \       / \
		   x x       x x       x x       x x
4. Count the number of ways a polygon with n+2 sides can be cut into n triangles
5. Count the number of paths of length 2n through an n-by-n grid that do not rise above the main diagonal

Recur: O(3^n) time
DP1D: O(n^2) time, O(n) space
UseBinomialCoefficient: O(n) time

Recurion/DP1D formula:
C0 = C1 = 1
          n-1
Cn = Sigma     Ci*Cn-1-i
          i=0

UseBinomialCoefficient formula:
      1     / 2n \      1           (2n)!         (2n)!
Cn = --- * |      | = ----- * -------------- = ----------
     n+1    \  n /     n+1     n! * (2n-n)!     (n+1)!*n!

*/
class CatalanNumber
{
public:
	CatalanNumber(){}
	~CatalanNumber(){}

	unsigned long int Recur(unsigned int n)
	{
		unsigned long int res = this->recur(n);
		std::cout << "CatalanNumber Recur for \"" << n << "\": " << res << std::endl;
		return res;
	}
private:
	unsigned long int recur(unsigned int n)
	{
		if (n <= 1)
			return 1;
		/*
		catalan(n) is sum of catalan(i)*catalan(n-1-i)
		*/
		unsigned long int sum = 0;
		for (unsigned int i = 0; i < n; ++i)
			sum += this->recur(i) * this->recur(n - 1 - i);//C0*Cn-1 +...+ Cn-1*C0

		return sum;
	}

public:
	unsigned long int Recur2(unsigned int n)
	{
		unsigned long int res = this->recur2(n);
		std::cout << "CatalanNumber Recur2 for \"" << n << "\": " << res << std::endl;
		return res;
	}
private:
	unsigned long int recur2(unsigned int n)
	{
		if (n <= 1)
			return 1;

		unsigned long int sum = 0;
		for (unsigned int i = 0; i < n / 2; ++i)
			sum += this->recur2(i) * this->recur2(n - 1 - i);

		sum *= 2;
		if (n % 2)
		{
			unsigned long int c = this->recur2(n / 2);
			sum += c*c;
		}
		return sum;
	}

public:
	unsigned long int DP1D(unsigned int n)
	{
		std::vector<unsigned long int> dp(n + 1);

		dp[0] = dp[1] = 1;

		for (unsigned int i = 2; i <= n; ++i)
		{
			dp[i] = 0;
			for (unsigned int j = 0; j < i; ++j)
				dp[i] += dp[j] * dp[i - 1 - j];//C0*Cn-1 +...+ Cn-1*C0
		}

		std::cout << Debug::ToStr1D<unsigned long int>()(dp) << std::endl;
		std::cout << "CatalanNumber DP1D for \"" << n << "\": " << dp[n] << std::endl;
		return dp[n];
	}

public:
	unsigned long int UseBinomialCoefficient(unsigned int n)
	{
		/*calculate value of 2nCn*/
		unsigned long int c = this->BinomialCoefficient(2 * n, n);
		/*2nCn/(n+1)*/
		unsigned long int res = c / (n + 1);

		std::cout << "CatalanNumber UseBinomialCoefficient for \"" << n << "\": " << res << std::endl;
		return res;
	}
private:
	unsigned long int BinomialCoefficient(unsigned int n, unsigned int k)//O(n) time
	{
		unsigned long int res = 1;

		/*since C(n, k) = C(n, n-k)*/
		if (k > n - k)
			k = n - k;

		/*calculate value of [n*(n-1)*...*(n-k+1)] / [k*(k-1)*...*1]*/
		for (unsigned int i = 0; i < k; ++i)
		{
			res *= (n - i);
			res /= (i + 1);
		}
		return res;
	}
};
/*
CatalanNumber Recur for "10": 16796
CatalanNumber Recur2 for "10": 16796
1, 1, 2, 5, 14, 42, 132, 429, 1430, 4862, 16796
CatalanNumber DP1D for "10": 16796
CatalanNumber UseBinomialCoefficient for "10": 16796
*/
#endif