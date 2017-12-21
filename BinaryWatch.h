#ifndef BINARY_WATCH_H
#define BINARY_WATCH_H
#include "Debug.h"
/*
Leetcode: Binary watch
A binary watch has 4 LEDs on the top which represent the hours (0-11), and the 6 LEDs on the bottom represent the minutes (0-59).
Each LED represents a zero or one, with the least significant bit on the right.

1  2  4  8
	  *  *
1  2  4  8  16  32
*        *   *

For example, the above binary watch reads "3:25".
Given a non-negative integer n which represents the number of LEDs that are currently on, return all possible times the watch could represent.
Example:
Input: n = 1
Return: ["1:00", "2:00", "4:00", "8:00", "0:01", "0:02", "0:04", "0:08", "0:16", "0:32"]
Note:
The order of output does not matter.
The hour must not contain a leading zero, for example "01:00" is not valid, it should be "1:00".
The minute must be consist of two digits and may contain a leading zero, for example "10:2" is not valid, it should be "10:02".
*/
class BinaryWatch
{
public:
	BinaryWatch() {}
	//enumerate all possible times
	std::vector<std::string> EnumerateAllTimes(int num)
	{
		std::vector<std::string> res;
		for (int h = 0; h < 12; ++h)
		{
			for (int m = 0; m < 60; ++m)
			{
				int hCount = countSetBit(h);
				int mCount = countSetBit(m);
				if (hCount + mCount == num)
				{
					std::string minute = std::to_string(m);
					if (minute.size() == 1)
						minute = "0" + minute;
					res.push_back(std::to_string(h) + ":" + minute);
				}
			}
		}

		std::cout << "BinaryWatch EnumerateAllTimes for \"" << num << "\" on-digits: " << Debug::ToStr1D<std::string>()(res) << std::endl;
		return res;
	}
private:
	int countSetBit(int n)
	{
		int count = 0;
		while (n)
		{
			count += (n & 1);
			n >>= 1;
		}
		return count;
	}
};
/*
BinaryWatch EnumerateAllTimes for "1" on-digits: 0:01, 0:02, 0:04, 0:08, 0:16, 0:32, 1:00, 2:00, 4:00, 8:00
*/
#endif
