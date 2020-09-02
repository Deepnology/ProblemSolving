#ifndef _NTH_DAY_OF_THE_YEAR_H
#define _NTH_DAY_OF_THE_YEAR_H
#include "Debug.h"
/*
Leetcode: Day of the Year
Given a string date representing a Gregorian calendar date formatted as YYYY-MM-DD, return the day number of the year.
Example 1:
Input: date = "2019-01-09"
Output: 9
Explanation: Given date is the 9th day of the year in 2019.
Example 2:
Input: date = "2019-02-10"
Output: 41
Example 3:
Input: date = "2003-03-01"
Output: 60
Example 4:
Input: date = "2004-03-01"
Output: 61
 */
class NthDayOfTheYear
{
public:
    int Count(std::string date)
    {
        std::vector<int> days({31,28,31,30,31,30,31,31,30,31,30,31});
        int Y = stoi(date.substr(0,4));
        int M = stoi(date.substr(5,2));
        int D = stoi(date.substr(8,2));
        bool isLeapYear = false;
        if((Y%4==0 && Y%100!=0) || Y%400==0)
            isLeapYear = true;
        int res = 0;
        for (int i = 0; i < M-1; ++i)
            if (i == 1) //Feburary
                res += isLeapYear ? 29 : days[i];
            else
                res += days[i];
        res += D;
        return res;
    }
};
#endif
