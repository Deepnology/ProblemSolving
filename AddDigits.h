#ifndef ADD_DIGITS_H
#define ADD_DIGITS_H
#include <iostream>
#include <sstream>
#include <string>
/*
Leetcode: Add Digits
Given a non-negative integer num, repeatedly add all its digits until the result has only one digit.

For example:
Given num = 38, the process is like: 3 + 8 = 11, 1 + 1 = 2. Since 2 has only one digit, return it.

Follow up:
Could you do it without any loop/recursion in O(1) runtime?

Hint:
A naive implementation of the above process is trivial. Could you come up with other methods?
What are all the possible results?
How do they occur, periodically or randomly?

Enumerate all the numbers:
in out
1   1
2   2
3   3
4   4
5   5
6   6
7   7
8   8
9   9

10  1
11  2
12  3
13  4
14  5
15  6
16  7
17  8
18  9

19  1
20  2
21  3
22  4
23  5
24  6
25  7
26  8
27  9

28  1
29  2
30  3
...


So the result = (n - 1) % 9 + 1
*/
class AddDigits
{
public:
	AddDigits() {}
	~AddDigits() {}

	int Naive(int num)
	{
		int original = num;

		while (num / 10 > 0)
		{
			int copy = num;
			int sum = 0;
			while (copy)
			{
				sum += copy % 10;
				copy /= 10;
			}
			num = sum;
		}

		std::cout << "AddDigits Naive for \"" << original << "\": " << num << std::endl;
		return num;
	}

	int Math(int num)
	{
		int original = num;
		num = (num - 1) % 9 + 1;

		std::cout << "AddDigits Math for \"" << original << "\": " << num << std::endl;
		return num;
	}
};
/*
AddDigits Naive for "19810516": 4
AddDigits Math for "19810516": 4
*/
#endif
