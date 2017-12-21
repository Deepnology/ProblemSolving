/*MUST*/
#ifndef SQRTX_H
#define SQRTX_H
#include <iostream>
#include <sstream>
#include <string>
#include <limits>
/*
Elements of programming interview, Searching: Compute the integer square root, Compute the real square root
Compute the integer square root:
Write a function which takes a nonnegative integer k and returns the largest integer whose square is greater or equal to k.
Assume k >= 0.
For example, if k = 16, return 4; if k = 300, return 17.
O(logk) time
Compute the real square root:
Implement a function which takes as input a floating point variable x and returns Sqrt(x).
O(log(x/eps)) time

Leetcode: Sqrt(x)
// Implement int sqrt(int x).
//
// Compute and return the square root of x.
//
// Complexity:
// Binary Search, O(log(x)) time

http://www.geeksforgeeks.org/square-root-of-a-perfect-square/
Babylonian method for square root

http://www.careercup.com/question?id=14797683
valid perfect square of a given number (ValidPerfectSquare.h)

http://www.careercup.com/question?id=14467683
find closest perfect square to a given number
*/
class Sqrtx
{
public:
	Sqrtx(){}
	~Sqrtx(){}

	int Int_BinarySearch(int x)
	{
		if (x <= 1)
			return x;

		//find the upper bound of sqrt(x), the answer will be upper bound - 1, which is floor or the exact value of sqrt(x)
		int left = 1;
		int right = x;
		while (left <= right)//keep 1 entry between [left,right] inclusive
		{
			int mid = (left + right) / 2;

			if (mid <= x / mid)//equivalent to mid*mid<=x to prevent from mid*mid overflow
				left = mid + 1;
			else
				right = mid - 1;
		}
		//now left is the upper bound, right is the upper bound - 1

		std::cout << "Sqrtx Int_BinarySearch for \"" << x << "\": " << right << std::endl;
		return right;
	}

	double Real_BinarySearch(double x)
	{
		double left, right;
		if (this->Compare(x, 1.0) < 0)//x < 1.0
		{
			left = x;
			right = 1.0;
		}
		else//x >= 1.0
		{
			left = 1.0;
			right = x;
		}
		
		//find the lower bound of sqrt(x), which will be the exact value or ceil of sqrt(x)
		while (this->Compare(left, right) == -1)//left < right
		{
			double mid = left + (right - left) * 0.5;
			double square = mid * mid;
			int comp = this->Compare(square, x);
			if (comp >= 0)//square >= x
				right = mid;
			else//square < x
				left = mid;
		}
		//now left is the lower bound
		std::cout << "Sqrtx Real_BinarySearch for \"" << x << "\": " << left << std::endl;
		return left;
	}
private:
	/*0 means equal, -1 means smaller, and 1 means larger*/
	int Compare(double a, double b)
	{
		/*use normalization for precision problem*/
		double diff = (a - b) / b;
		return diff < -std::numeric_limits<double>::epsilon() ? -1 : diff > std::numeric_limits<double>::epsilon();
	}
	/*
	std::numeric_limits<T>::epsilon
	Returns the machine epsilon, that is, the difference between 1.0 and the next value representable by the floating-point type T.
	It is only meaningful if std::numeric_limits<T>::is_integer == false.
	*/

public:
	double Real_Babylonian_BinarySearch(double x)
	{
		double right = x;
		double left = 1;
		double accuracy = 0.00001;
		while (right - left > accuracy)
		{
			right = (left + right) / 2;
			left = x / right;
		}

		std::cout << "Sqrtx Real_Babylonian_BinarySearch for \"" << x << "\": " << right << std::endl;
		return right;
	}
};
/*
Sqrtx Int_BinarySearch for "2": 1
Sqrtx Int_BinarySearch for "3": 1
Sqrtx Int_BinarySearch for "4": 2
Sqrtx Int_BinarySearch for "5": 2
Sqrtx Int_BinarySearch for "144": 12
Sqrtx Int_BinarySearch for "147": 12
Sqrtx Int_BinarySearch for "140": 11
Sqrtx Real_BinarySearch for "0": 0
Sqrtx Real_BinarySearch for "1": 1
Sqrtx Real_BinarySearch for "2": 1.41421
Sqrtx Real_BinarySearch for "3": 1.73205
Sqrtx Real_BinarySearch for "4": 2
Sqrtx Real_BinarySearch for "5": 2.23607
Sqrtx Real_BinarySearch for "144": 12
Sqrtx Real_BinarySearch for "147": 12.1244
Sqrtx Real_BinarySearch for "140": 11.8322
Sqrtx Real_BinarySearch for "0.1": 0.316228
Sqrtx Real_BinarySearch for "0.3": 0.547723
Sqrtx Real_BinarySearch for "0.5": 0.707107
Sqrtx Real_Babylonian_BinarySearch for "0": 0
Sqrtx Real_Babylonian_BinarySearch for "1": 1
Sqrtx Real_Babylonian_BinarySearch for "2": 1.41422
Sqrtx Real_Babylonian_BinarySearch for "3": 1.73205
Sqrtx Real_Babylonian_BinarySearch for "4": 2
Sqrtx Real_Babylonian_BinarySearch for "5": 2.23607
Sqrtx Real_Babylonian_BinarySearch for "144": 12
Sqrtx Real_Babylonian_BinarySearch for "147": 12.1244
Sqrtx Real_Babylonian_BinarySearch for "140": 11.8322
*/
#endif