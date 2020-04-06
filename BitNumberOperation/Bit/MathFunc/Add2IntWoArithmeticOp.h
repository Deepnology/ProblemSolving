/*MUST*/
#ifndef	ADD_2_INT_WO_ARITHMETIC_OP_H
#define ADD_2_INT_WO_ARITHMETIC_OP_H
#include <iostream>
#include <string>
/*
Leetcode: Sum of Two Integers
Calculate the sum of two integers a and b, but you are not allowed to use the operator + and -.
Cracking the coding interview: Hard
Add two numbers without using arithmetic operations.
*/
class Add2IntWoArithmeticOp
{
public:
	Add2IntWoArithmeticOp(){}
	~Add2IntWoArithmeticOp(){}
public:
	int Solve_Recur(int a, int b)
	{
		int res = this->addRecur(a, b);
		std::cout << "Add2IntWoArithmeticOp Recur for \"" << a << "\", \"" << b << "\": " << res << std::endl;
		return res;
	}
private:
	int addRecur(int a, int b)
	{
		if (b == 0)
			return a;
		int sum = a ^ b;//(a + b) without carry
		int carry = (a & b) << 1;//only (a + b)'s carry
		return this->addRecur(sum, carry);
	}

public:
	int Solve_Iterate(int a, int b)
	{
		std::cout << "Add2IntWoArithmeticOp Iterate for \"" << a << "\", \"" << b << "\": ";

		while (b != 0)
		{
			int sum = a ^ b;//(a + b) without carry
			int carry = (a & b) << 1;//only (a + b)'s carry
			a = sum;
			b = carry;
		}

		std::cout << a << std::endl;
		return a;
	}

	int Negate(int a)
	{
		return this->addRecur(~a, 1);/*invert all the digits of a, then plus 1. (Two's Complement)*/
	}
	int Subtract(int a, int b)
	{
		int res = this->addRecur(a, this->Negate(b));
		std::cout << "Add2IntWoArithmeticOp Subtract for \"" << a << "\", \"" << b << "\": " << res << std::endl;
		return res;
	}
};
/*
Add2IntWoArithmeticOp Recur for "759", "674": 1433
Add2IntWoArithmeticOp Iterate for "759", "674": 1433
Add2IntWoArithmeticOp Subtract for "759", "674": 85
*/
#endif