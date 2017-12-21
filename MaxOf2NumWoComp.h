/*MUST*/
#ifndef MAX_OF_2_NUM_WO_COMP_H
#define MAX_OF_2_NUM_WO_COMP_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Debug.h"
/*
Cracking the coding interview: Moderate
http://stackoverflow.com/questions/227383/how-do-i-programmatically-return-the-max-of-two-integers-without#227418
http://en.wikipedia.org/wiki/Bitwise_operations_in_C
right shift operator >>
When performed on an unsigned type, the operation performed is a logical shift,
causing the blanks to be filled by "0s" (zeros).
When performed on a signed type, an arithmetic shift is performed,
causing the blank to be filled with "the sign bit of the left operand".

=> right shift 31 on a 32-bit positive integer results in 0
=> right shift 31 on a 32-bit negative integer results in ~0 (all 1s)

(right shift on a signed type and negative value is implementation defined)
*/
class MaxOf2NumWoComp
{
public:
	MaxOf2NumWoComp(){}
	~MaxOf2NumWoComp(){}

	int Solve(int aa, int bb)
	{
		long long a = aa;
		long long b = bb;

		a -= b;//now a becomes "diff"
		a &= (~a) >> 63;//if a is positive, (~a)>>63 becomes ~0, a&(~0) becomes a; if a is negative, (~a)>>63 becomes 0, a&0 becomes 0 => let a AND its complement sign bit
		a += b;

		std::cout << "MaxOf2NumWoComp for \"" << aa << "\", \"" << bb << "\": " << a << std::endl;
		return (int)a;
	}

	int Solve_Min(int aa, int bb)
	{
		long long a = aa;
		long long b = bb;

		a -= b;
		a &= a >> 63;//if a is positive, a>>63 becomes 0, a&0 becomes 0; if a is negative, a>>63 becomes ~0, a&(~0) becomes a => let a AND its sign bit
		a += b;

		std::cout << "MinOf2NumWoComp for \"" << aa << "\", \"" << bb << "\": " << a << std::endl;
		return (int)a;
	}

	int WMultiplication(int aa, int bb)
	{
		long long a = aa;
		long long b = bb;
		long long c = a - b;//might overflow

		int sign_a = this->sign(a);//a > 0: 1, otherwise: 0
		int sign_b = this->sign(b);//b > 0: 1, otherwise: 0
		int sign_c = this->sign(c);//c > 0: 1, otherwise: 0

		int diff_sign = sign_a ^ sign_b;//sign(a) is diff from sign(b): 1, otherwise: 0
		int same_sign = this->flip(diff_sign);//sign(a) is same as sign(b): 1, otherwise: 0

		//now this is the most important part...
		int a_greater_b = diff_sign * sign_a + same_sign * sign_c;//a and b diff_sign: a_greater_b = sign_a, otherwise same_sign: a_greater_b = sign_c
		int b_greater_a = this->flip(a_greater_b);

		int max = a_greater_b * aa + b_greater_a * bb;

		std::cout << "MaxOf2NumWoComp WMultiplication for \"" << aa << "\", \"" << bb << "\": " << max << std::endl;
		return max;
	}

private:
	int flip(int bit)
	{
		return 1 ^ bit;
	}
	int sign(long long a)
	{
		//when performing right shift >> on a signed type, the blanks will be filled with the sign bit.
		a >>= 63;
		//that's why we need to & 1.
		a &= 1;

		return this->flip((int)(a));
	}
};
/*
Signed (0 >> 63) = 0
Signed (-9223372036854775808 >> 63) = -1. Signed ~0LL = -1
Signed (-65535 >> 1) = -32768
Unsigned (0 >> 63) = 0
Unsigned (9223372036854775808 >> 63) = 1
MaxOf2NumWoComp for "2147483647", "-2147483648": 2147483647
MinOf2NumWoComp for "-2147483648", "2147483647": -2147483648
MaxOf2NumWoComp WMultiplication for "-2147483648", "2147483647": 2147483647
MaxOf2NumWoComp WMultiplication for "2147483647", "-2147483648": 2147483647
*/
#endif