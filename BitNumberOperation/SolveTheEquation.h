#ifndef _SOLVE_THE_EQUATION_H
#define _SOLVE_THE_EQUATION_H
#include "Debug.h"
/*
Leetcode: Solve the equation
Solve a given equation and return the value of x in the form of string "x=#value".
The equation contains only '+', '-' operation, the variable x and its coefficient.
If there is no solution for the equation, return "No solution".
If there are infinite solutions for the equation, return "Infinite solutions".
If there is exactly one solution for the equation, we ensure that the value of x is an integer.
Example 1:
Input: "x+5-3+x=6+x-2"
Output: "x=2"
Example 2:
Input: "x=x"
Output: "Infinite solutions"
Example 3:
Input: "2x=x"
Output: "x=0"
Example 4:
Input: "2x+3x-6x=x+2"
Output: "x=-1"
Example 5:
Input: "x=x+2"
Output: "No solution"
 */
class SolveTheEquation
{
public:
    std::string Solve(std::string equation)
    {
        int N = equation.size();
        int i = 0;
        while (equation[i] != '=')
            ++i;
        std::string s1 = equation.substr(0, i);
        std::string s2 = equation.substr(i+1);
        std::vector<int> left = evalOneSide(s1);
        std::vector<int> right = evalOneSide(s2);
        //std::cout << "left: " << left[0] << "," << left[1] << "; right: " << right[0] << "," << right[1] << std::endl;
        left[0] -= right[0];//move x to the left
        right[1] -= left[1];//move num to the right
        if (left[0] == 0 && right[1] == 0)
            return "Infinite solutions";
        if (left[0] == 0)
            return "No solution";
        return "x=" + std::to_string(right[1] / left[0]);
    }
private:
    std::vector<int> evalOneSide(std::string & s)//[sum of all x, sum of other nums]
    {
        std::vector<int> res(2, 0);
        int N = s.size();
        int i = 0;
        bool sign = true;
        while (i < N)
        {
            if (s[i] == '+')
                sign = true, ++i;
            else if (s[i] == '-')
                sign = false, ++i;

            int num = 1;
            if (isdigit(s[i]))
            {
                int begin = i;
                ++i;
                while (isdigit(s[i]))
                    ++i;
                num = stoi(s.substr(begin, i - begin));
            }

            if (i < N && s[i] == 'x')
            {
                sign ? (res[0] += num) : (res[0] -= num);
                ++i;
            }
            else
                sign ? (res[1] += num) : (res[1] -= num);
        }
        return res;
    }
};
#endif
