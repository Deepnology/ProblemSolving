#ifndef INT_TO_DECIMAL_STR_H
#define INT_TO_DECIMAL_STR_H
#include <string>
#include <iostream>
#include <sstream>
#include <math.h>
/*
Elements of programming interview, Strings: Interconvert strings and integers
*/
class IntToDecimalStr
{
public:
	IntToDecimalStr(){}
	~IntToDecimalStr(){}

	std::string Solve(int n)
	{
		int before = n;
		std::string res;
		if (n == 0)
			res = "0";
		else
		{
			bool isNeg = false;
			if (n < 0)
			{
				n = -n;
				isNeg = true;
			}
			while (n)
			{
				res.insert(res.begin(), '0' + n % 10);
				n /= 10;
			}
			if (isNeg)
				res.insert(res.begin(), '-');
		}

		std::cout << "IntToDecimalStr for \"" << before << "\": " << res << std::endl;
		return res;
	}
};

class DecimalStrToInt
{
public:
	DecimalStrToInt(){}
	~DecimalStrToInt(){}

	int Solve(const std::string & s)
	{
		int res;
		if (s.empty())
			res = 0;
		else
		{
			bool neg = s[0] == '-' ? true : false;
			res = 0;

			for (int i = neg ? 1 : 0; i < (int)s.size(); ++i)
			{
				if (s[i] - '0' >= 0 && s[i] - '0' <= 9)
					res = res * 10 + s[i] - '0';
			}
			res = neg ? -res : res;
		}
		
		std::cout << "DecimalStrToInt for \"" << s << "\": " << res << std::endl;
		return res;
	}
};
/*
IntToDecimalStr for "12345": 12345
IntToDecimalStr for "-12345": -12345
DecimalStrToInt for "12345": 12345
DecimalStrToInt for "-12345": -12345
*/
#endif