#ifndef MODULUS_H_
#define MODULUS_H_
#include <iostream>
#include <string>
/*
http://www.cs.cornell.edu/courses/cs211/2006fa/Sections/S2/recursion.txt
*/
class Modulus
{
public:
	Modulus(){}
	~Modulus(){}

	int Solve_Iterate(int val, int divisor)
	{
		int mod;
		if (divisor == 0)
			mod = 0;
		else
		{
			int positiveDivisor = std::abs(divisor);
			bool isNegative = val < 0;
			int positiveVal = std::abs(val);
			while (positiveVal >= positiveDivisor)
			{
				positiveVal = positiveVal - positiveDivisor;
			}
			mod = isNegative ? -positiveVal : positiveVal;
		}

		std::cout << "Modulus Iterate for \"" << val << " % " << divisor << "\": " << mod << " (" << val % divisor << ")" << std::endl;
		return mod;
	}

	int Solve_Recur(int val, int divisor)
	{
		int mod;
		if (divisor == 0)
			mod = 0;
		else
		{
			int positiveDivisor = std::abs(divisor);
			mod = this->recur(val, positiveDivisor);
		}
		
		std::cout << "Modulus Recur for \"" << val << " % " << divisor << "\": " << mod << " (" << val % divisor << ")" << std::endl;
		return mod;
	}
	int recur(int val, const int & positiveDivisor)
	{
		int positiveVal = std::abs(val);

		if (positiveVal < positiveDivisor)
			return val;
		else
			return val < 0 ? -this->recur(positiveVal - positiveDivisor, positiveDivisor) : 
			this->recur(positiveVal - positiveDivisor, positiveDivisor); 
	}
};
/*
Modulus Recur for "78 % 34": 10 (10)
Modulus Recur for "-78 % 34": -10 (-10)
Modulus Recur for "-78 % -34": -10 (-10)
Modulus Recur for "78 % -34": 10 (10)
Modulus Iterate for "78 % 34": 10 (10)
Modulus Iterate for "-78 % 34": -10 (-10)
Modulus Iterate for "-78 % -34": -10 (-10)
Modulus Iterate for "78 % -34": 10 (10)
*/
#endif