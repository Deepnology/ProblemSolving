/*MUST*/
#ifndef MUL_2_INT_WO_ARITHMETIC_OP_H
#define MUL_2_INT_WO_ARITHMETIC_OP_H
#include <string>
#include <iostream>
#include <sstream>
/*
Elements of programming interview, PrimitiveTypes: Compute x*y without multiply or add

see also Add2IntWoArithmeticOp.h, Multiply2IntStr.h
*/
class Mul2IntWoArithmeticOp
{
public:
	Mul2IntWoArithmeticOp(){}
	~Mul2IntWoArithmeticOp(){}

	int Solve(int a, int b)//better
	{
		std::cout << "Mul2IntWoArithmeticOp for \"" << a << "\", and \"" << b << "\": ";

		if (a < 0 && b < 0)
		{
			a = this->add(~a, 1);/*invert all digits of a then add 1: negate of a*/
			b = this->add(~b, 1);/*invert all digits of b then add 1: negate of b*/
		}
		else if (a >= 0 && b < 0)/*make sure b >= 0*/
		{
			int tmp = a;
			a = b;
			b = tmp;
		}

		/*mimic multiplication of all digits of a and all digits of b in the binary representation*/
		int res = 0;
		while (b > 0)
		{
			if (b & 1)/*b's rightmost digit is 1*/
			{
				res = this->add(res, a);/*add a to res*/
			}
			a <<= 1;/*multiply a by 2 for b's next left digit multiplication*/
			b >>= 1;/*right shift b 1 digit for its next left digit multiplication*/
		}

		std::cout << res << std::endl;
		return res;
	}

	int Solve2(int a, int b)
	{
		std::cout << "Mul2IntWoArithmeticOp2 for \"" << a << "\", and \"" << b << "\": ";

		if (a < 0 && b < 0)
		{
			a = this->add(~a, 1);/*invert all digits of a then add 1: negate of a*/
			b = this->add(~b, 1);/*invert all digits of b then add 1: negate of b*/
		}
		else if (a >= 0 && b < 0)/*make sure b >= 0*/
		{
			int tmp = a;
			a = b;
			b = tmp;
		}

		int res = 0;
		while (b > 0)
		{
			if (this->isEven(b))
			{
				a <<= 1;/*multiply a by 2*/
				b >>= 1;/*divide b by 2*/
			}
			else
			{
				res = this->add(res, a);/*add a to res*/
				b = this->add(b, -1);/*subtract b by 1*/
			}
		}
		
		std::cout << res << std::endl;
		return res;
	}

private:
	int add(int a, int b)
	{
		while (b != 0)
		{
			int carry = a & b;
			a = a ^ b;
			b = carry << 1;
		}
		return a;
	}
	bool isEven(int n)
	{
		return !(n & 1);
	}
};
/*
Mul2IntWoArithmeticOp for "-7", and "50": -350
Mul2IntWoArithmeticOp2 for "-7", and "50": -350
*/
#endif