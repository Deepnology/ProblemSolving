#ifndef HAPPY_NUMBER_H
#define HAPPY_NUMBER_H
#include <iostream>
#include <string>
#include <unordered_set>
/*
Leetcode: Happy Number
Write an algorithm to determine if a number is "happy".
A happy number is a number defined by the following process:
Starting with any positive integer, 
replace the number by the sum of the squares of its digits, 
and repeat the process until the number equals 1 (where it will stay), 
or it loops endlessly in a cycle which does not include 1.
Those numbers for which this process ends in 1 are happy numbers.
Example: 19 is a happy number
1^2 + 9^2 = 82
8^2 + 2^2 = 68
6^2 + 8^2 = 100
1^2 + 0^2 + 0^2 = 1

*/
class HappyNumber
{
public:
	HappyNumber(){}
	~HappyNumber(){}

	bool Recur(int n)
	{
		std::unordered_set<long> visit;
		bool res = this->recur(n, visit);
		std::cout << "HappyNumber Recur for \"" << n << "\": " << res << std::endl;
		return res;
	}

	bool recur(int n, std::unordered_set<long> & visit)
	{
		if (n == 1)
			return true;
		if (visit.find(n) != visit.end())
			return false;

		std::cout << n << std::endl;
		visit.insert(n);
		int sum = 0;
		while (n)
		{
			int LSB = n % 10;
			sum += LSB * LSB;
			n /= 10;
		}
		return this->recur(sum, visit);
	}
};
/*
4
16
37
58
89
145
42
20
HappyNumber Recur for "4": 0
7
49
97
130
10
HappyNumber Recur for "7": 1
12
5
25
29
85
89
145
42
20
4
16
37
58
HappyNumber Recur for "12": 0
*/
#endif