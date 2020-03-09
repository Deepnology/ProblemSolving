#ifndef MULTIPLY_BY_7_H
#define MULTIPLY_BY_7_H
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Debug.h"
/*
http://www.geeksforgeeks.org/efficient-way-to-multiply-with-7/
http://edusagar.com/articles/view/10/BitWise-Operators-interview-Questions
We can multiply a number by 7 using bitwise operator.
First left shift the number by 3 bits (you will get 8n)
then subtract the original number from the shifted number and return the difference (8n-n).
*/
class MultiplyBy7
{
public:
	MultiplyBy7(){}
	~MultiplyBy7(){}

	int Bitwise(unsigned int n)
	{
		int res = (n << 3) - n;
		std::cout << "MultiplyBy7 Bitwise for \"" << n << "\": " << res << std::endl;
		return res;
	}
};
/*
MultiplyBy7 Bitwise for "4": 28
*/
#endif