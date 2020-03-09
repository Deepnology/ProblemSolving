#ifndef ZIGZAG_CONVERSION_H
#define ZIGZAG_CONVERSION_H
#include <string>
#include <vector>
#include <iostream>
#include "Debug.h"
/*
Leetcode: Zig Zag Conversion
The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: (you may want to display this pattern in a fixed font for better legibility)

P   A   H   N
A P L S I I G
Y   I   R
And then read line by line: "PAHNAPLSIIGYIR"
Write the code that will take a string and make this conversion given a number of rows:

string convert(string text, int nRows);
convert("PAYPALISHIRING", 3) should return "PAHNAPLSIIGYIR".

for numRows = 5:
0          8              16
1       7  9          15  17
2    6    10      14      18 
3  5      11  13          19
4         12              20

Observations:
There are 2 "V" in the above arrangement, where each vSize = 2*5-2 = 8.
For each row, 
1st "V": the 1st num idx is the row_idx + vSize*0, the 2nd num idx is the 1st num idx + vSize - 2*row_idx;
2nd "V": the 3rd num idx is the row_idx + vSize*1, the 4th num idx is the 3rd num idx + vSize - 2*row_idx;
....

*/
class ZigZagConversion
{
public:
	ZigZagConversion(){}
	~ZigZagConversion(){}

	std::string Convert(const std::string & s, int numRows)
	{
		int N = s.size();
		if (N == 0 || numRows <= 0)
			return "";
		if (numRows == 1)
			return s;

		std::string res;
		int vSize = 2 * numRows - 2;
		for (int i = 0; i < numRows; ++i)
		{
			for (int j = i; j < N; j += vSize)
			{
				res += s[j];//1st num (the vertical part) in cur "V"
				if (i != 0 && i != numRows - 1 && j + vSize - 2 * i < N)//top row and bottom row don't have 2nd num!!
					res += s[j + vSize - 2 * i];//2nd num (the slash part) in cur "V"
			}
		}

		std::cout << "ZigZagConversion for \"" << s << "\" in \"" << numRows << "\" rows: " << res << std::endl;
		return res;
	}
};
/*
ZigZagConversion for "abcdefghijklmnopqrstu" in "5" rows: aiqbhjprcgkosdflntemu
*/
#endif