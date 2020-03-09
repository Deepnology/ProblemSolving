#ifndef COMPLEX_NUMBER_MULTIPLICATION_H
#define COMPLEX_NUMBER_MULTIPLICATION_H
#include "Debug.h"
/*
Leetcode: Complex Number Multiplication
Given two strings representing two complex numbers.
You need to return a string representing their multiplication. Note i^2 = -1 according to the definition.
Example 1:
Input: "1+1i", "1+1i"
Output: "0+2i"
Explanation: (1 + i) * (1 + i) = 1 + i^2 + 2 * i = 2i, and you need convert it to the form of 0+2i.
Example 2:
Input: "1+-1i", "1+-1i"
Output: "0+-2i"
Explanation: (1 - i) * (1 - i) = 1 + i^2 - 2 * i = -2i, and you need convert it to the form of 0+-2i.
Note:
The input strings will not have extra blank.
The input strings will be given in the form of a+bi, where the integer a and b will both belong to the range of [-100, 100]. And the output should be also in this form.

*/
class ComplexNumberMultiplication
{
public:
	ComplexNumberMultiplication() {}

	std::string UseFormula(std::string a, std::string b)
	{
		//(ra+(ia)i)*(rb+(ib)i)=(ra*rb-ia*ib)+(ra*ib+rb*ia)i
		std::istringstream aa(a);
		std::istringstream bb(b);
		int ra;
		int ia;
		int rb;
		int ib;
		char plus;
		aa >> ra >> plus >> ia;
		bb >> rb >> plus >> ib;
		std::string res;
		res += std::to_string(ra*rb - ia*ib);
		res += "+";
		res += std::to_string(ra*ib + rb*ia);
		res += "i";

		std::cout << "ComplexNumberMultiplication UseFormula for \"" << a << "\", \"" << b << "\": " << res << std::endl;
		return res;
	}
};
/*
ComplexNumberMultiplication UseFormula for "1+1i", "1+1i": 0+2i
ComplexNumberMultiplication UseFormula for "1+-1i", "1+-1i": 0+-2i
*/
#endif
