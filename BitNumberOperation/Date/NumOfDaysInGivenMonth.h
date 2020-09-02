#ifndef _NUM_OF_DAYS_IN_GIVEN_MONTH_H
#define _NUM_OF_DAYS_IN_GIVEN_MONTH_H
#include "Debug.h"
/*
Leetcode: Number of Days in a Month
Given a year Y and a month M, return how many days there are in that month.
Example 1:
Input: Y = 1992, M = 7
Output: 31
Example 2:
Input: Y = 2000, M = 2
Output: 29
Example 3:
Input: Y = 1900, M = 2
Output: 28
 */
class NumOfDaysInGivenMonth
{
public:
    int Solve(int Y, int M)
    {
        int res = solve(Y, M);
        std::cout << "NumOfDaysInGivenMonth for year=" << Y << ", month=" << M << ": " << res << std::endl;
        return res;
    }
    int solve(int Y, int M)
    {
        /*
        Leap Year:
            1.The year can be evenly divided by 4;
            2.If the year can be evenly divided by 100, it is NOT a leap year, unless;
            3.The year is also evenly divisible by 400. Then it is a leap year.
        */
        bool isLeapYear = false;
        if((Y%4==0 && Y%100!=0) || Y%400==0)
            isLeapYear = true;

        if(M<=7)
        {
            if(M==2) return isLeapYear ? 29 : 28;
            return (M%2==0) ? 30 : 31;
        }
        return (M%2==0) ? 31 : 30;
    }
};
/*
NumOfDaysInGivenMonth for year=2000, month=2: 29
 */
#endif
