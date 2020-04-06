#ifndef FRACTION_ADDITION_SUBTRACTION_H
#define FRACTION_ADDITION_SUBTRACTION_H
#include "Debug.h"
#include <numeric>
/*
Leetcode: Fraction Addition Subtraction
Given a string representing an expression of fraction addition and subtraction, you need to return the calculation result in string format.
The final result should be irreducible fraction.
If your final result is an integer, say 2, you need to change it to the format of fraction that has denominator 1.
So in this case, 2 should be converted to 2/1.
Example 1:
Input:"-1/2+1/2"
Output: "0/1"
Example 2:
Input:"-1/2+1/2+1/3"
Output: "1/3"
Example 3:
Input:"1/3-1/2"
Output: "-1/6"
Example 4:
Input:"5/3+1/3"
Output: "2/1"
Note:
The input string only contains '0' to '9', '/', '+' and '-'. So does the output.
Each fraction (input and output) has format +OR- numerator/denominator.
If the first input fraction or the output is positive, then '+' will be omitted.
The input only contains valid irreducible fractions, where the numerator and denominator of each fraction will always be in the range [1,10]. If the denominator is 1, it means this fraction is actually an integer in a fraction format defined above.
The number of given fractions will be in the range [1,10].
The numerator and denominator of the final result are guaranteed to be valid and in the range of 32-bit int.
*/
class FractionAdditionSubtraction
{
public:
	FractionAdditionSubtraction() {}

	std::string Evaluate(std::string expression)
	{
		std::istringstream iss(expression);
		int DVD = 0;
		int DVS = 1;//initial is 0/1
		int dvd;
		int dvs;
		char divide;
		while (iss >> dvd >> divide >> dvs)
		{
			DVD = DVD*dvs + dvd*DVS;
			DVS = DVS*dvs;
			// DVD/DVS + dvd/dvs = (DVD*dvs+dvd*DVS) / DVS*dvs
			int gcd = std::abs(GCD(DVD, DVS));
			DVD /= gcd;
			DVS /= gcd;
		}
		return std::to_string(DVD) + "/" + std::to_string(DVS);
	}

	int GCD(int a, int b)
	{
		while (a)
		{
			int tmp = a;
			a = b % a;
			b = tmp;
		}
		return b;
	}
};
#endif
