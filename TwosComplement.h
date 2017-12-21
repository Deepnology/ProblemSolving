#ifndef TWOS_COMPLEMENT_H
#define TWOS_COMPLEMENT_H
#include <string>
#include <iostream>
#include <sstream>
/*
The two's complement of an n-bit number is the result of subtracting the number from 2^n.
The tow's complement of a number behaves like the negative of the original number in most arithmetic.
The two's complement system has the advantage that the arithmetic operations of addition, subtraction, and multiplication are identical to the ones defined for unsigned binary numbders.
This requires inputs to be represented with the same number of bits and overflow beyond those bits is discarded from the result.
Indeed zero has only a single representation.

*/
class TwosComplement
{
public:
	TwosComplement(){}
	~TwosComplement(){}

	int Solve(int n)
	{
		int res = ~n + 1;
		std::cout << "TwosComplement for \"" << n << " (" << ToHexFullLength(n) << ")\": " << res << " (" << ToHexFullLength(res) << ")" << std::endl;
		return res;
	}

private:
	std::string ToHexFullLength(int num)
	{
		if (num == 0) return "0";
		std::string res;
		for (int i = 0; i <= 28; i += 4)//from lowest 4 bits to highest 4 bits
		{
			int cur = num >> i;
			res = map[cur & 0xf] + res;
		}
		return res;
	}
	std::vector<std::string> map = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "a", "b", "c", "d", "e", "f" };
};
/*
TwosComplement for "27 (0000001b)": -27 (ffffffe5)
TwosComplement for "-27 (ffffffe5)": 27 (0000001b)
TwosComplement for "0 (0)": 0 (0)									//0 ....no change
TwosComplement for "1 (00000001)": -1 (ffffffff)					//1
TwosComplement for "-1 (ffffffff)": 1 (00000001)					//-1
TwosComplement for "-1 (ffffffff)": 1 (00000001)					//~0 ....(~0 equals -1)
TwosComplement for "0 (0)": 0 (0)									//~0+1 ....no change (~0 equals -1)
TwosComplement for "-2 (fffffffe)": 2 (00000002)					//~0-1
TwosComplement for "2147483647 (7fffffff)": -2147483647 (80000001)	//INT_MAX
TwosComplement for "2147483646 (7ffffffe)": -2147483646 (80000002)	//INT_MAX-1
TwosComplement for "-2147483648 (80000000)": -2147483648 (80000000)	//~INT_MAX ....no change (~INT_MAX equals INT_MIN)
TwosComplement for "-2147483647 (80000001)": 2147483647 (7fffffff)	//~INT_MAX+1
TwosComplement for "-2147483648 (80000000)": -2147483648 (80000000)	//INT_MIN ....no change
TwosComplement for "-2147483647 (80000001)": 2147483647 (7fffffff)	//INT_MIN+1
TwosComplement for "2147483647 (7fffffff)": -2147483647 (80000001)	//~INT_MIN .... (~INT_MIN equals INT_MAX)
TwosComplement for "2147483646 (7ffffffe)": -2147483646 (80000002)	//~INT_MIN-1
TwosComplement for "0 (0)": 0 (0)									//~-1 ....no change (~-1 equals 0)
TwosComplement for "1 (00000001)": -1 (ffffffff)					//~-2
TwosComplement for "2 (00000002)": -2 (fffffffe)					//~-3
TwosComplement for "-2 (fffffffe)": 2 (00000002)					//~1
*/
#endif