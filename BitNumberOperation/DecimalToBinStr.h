/*MUST*/
#ifndef DECIMAL_TO_BIN_STR_H
#define DECIMAL_TO_BIN_STR_H
#include <iostream>
#include <sstream>
#include <string>
#include "Debug.h"
#include "KeyGenAux.hpp"
/*
Cracking the coding interview 5.2
decimal(0.37) to binary(0.101)
binary:	0.101 = 1 * (1/2)^1 + 0 * (1/2)^2 + 1 * (1/2)^3
*2:		1.01	=> got 1, left	0.01
*2:		0.1		=> got 0, left	0.1
*2:		1		=> got 1, left	0
*/
class DecimalToBinStr
{
public:
	DecimalToBinStr(){}
	~DecimalToBinStr(){}

	std::string Convert(double decimal)
	{
		int intNum = (int)decimal;
		double fracNum = decimal - intNum;
		
		std::string intStr;
		while (intNum > 0)
		{
			int curLowestBit = intNum % 2;
			intNum >>= 1;//right shift 1 bit (divided by 2)
			intStr = std::to_string(curLowestBit) + intStr;//push "bit" to front of intStr
		}
		
		std::string fracStr;
		while (fracNum > 0)
		{
			if (fracStr.size() > 21)
				break;
			if (fracNum == 1)
			{
				fracStr.append("1");
				break;
			}

			double r = fracNum * 2;
			if (r >= 1)
			{
				fracStr.append("1");
				fracNum = r - 1;
			}
			else
			{
				fracStr.append("0");
				fracNum = r;
			}
		}
		std::string res = intStr + "." + fracStr;
		std::cout << "DecimalToBinStr for \"" << decimal << "\": " << res << std::endl;
		return res;
	}
};
/*
DecimalToBinStr for "3.72": 11.1011100001010001111010
*/
#endif