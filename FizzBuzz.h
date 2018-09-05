#ifndef _FIZZ_BUZZ_H
#define _FIZZ_BUZZ_H
#include "Debug.h"
/*
Leetcode: Fizz Buzz
Write a program that outputs the string representation of numbers from 1 to n.
But for multiples of three it should output “Fizz” instead of the number and for the multiples of five output “Buzz”.
For numbers which are multiples of both three and five output “FizzBuzz”.
Example:
n = 15,
Return:
[
    "1",
    "2",
    "Fizz",
    "4",
    "Buzz",
    "Fizz",
    "7",
    "8",
    "Fizz",
    "Buzz",
    "11",
    "Fizz",
    "13",
    "14",
    "FizzBuzz"
]
 */
class FizzBuzz
{
public:
    FizzBuzz(){}

    std::vector<std::string> Solve(int n)
    {
        std::vector<std::string> res;
        for (int i = 1; i <= n; ++i)
        {
            if (i % 15 == 0)
                res.push_back("FizzBuzz");
            else if (i % 5 == 0)
                res.push_back("Buzz");
            else if (i % 3 == 0)
                res.push_back("Fizz");
            else
                res.push_back(std::to_string(i));
        }
        return res;
    }

    std::vector<std::string> WithoutMod(int n)
    {
        std::vector<std::string> res;
        for (int i = 1, fizz = 3, buzz = 5; i <= n; ++i)
        {
            if (i == fizz && i == buzz)
            {
                res.push_back("FizzBuzz");
                fizz += 3; buzz += 5;
            }
            else if (i == fizz)
            {
                res.push_back("Fizz");
                fizz += 3;
            }
            else if (i == buzz)
            {
                res.push_back("Buzz");
                buzz += 5;
            }
            else
                res.push_back(std::to_string(i));
        }
        return res;
    }
};
#endif
