#ifndef _COUNT_DAYS_BTW_2_DATES_H
#define _COUNT_DAYS_BTW_2_DATES_H
#include "Debug.h"
/*
Leetcode: Number of Days Between Two Dates
Write a program to count the number of days between two dates.
The two dates are given as strings, their format is YYYY-MM-DD as shown in the examples.
Example 1:
Input: date1 = "2019-06-29", date2 = "2019-06-30"
Output: 1
Example 2:
Input: date1 = "2020-01-15", date2 = "2019-12-31"
Output: 15
Constraints:
The given dates are valid dates between the years 1971 and 2100.
 */
class CountDaysBtw2Dates
{
public:
    int Count(std::string date1, std::string date2)
    {
        int days1 = numOfDaysSince1900_01_01(date1);
        int days2 = numOfDaysSince1900_01_01(date2);
        return std::abs(days1-days2);
    }
private:
    int numOfDaysSince1900_01_01(std::string date)
    {
        std::vector<int> days({31,28,31,30,31,30,31,31,30,31,30,31});
        int Y = stoi(date.substr(0,4));
        int M = stoi(date.substr(5,2));
        int D = stoi(date.substr(8,2));
        int res = 0;
        for (int i = 1900; i < Y; ++i) //accumulate years before this year
            res += IsLeapYear(i) ? 366 : 365;
        for (int i = 0; i < M-1; ++i) //accumulate months before this month
            if (i == 1) //Feburary
                res += IsLeapYear(Y) ? 29 : days[i];
            else
                res += days[i];
        res += D; //accumulate days in this month
        return res;
    }
    bool IsLeapYear(int Y)
    {
        bool isLeapYear = false;
        if((Y%4==0 && Y%100!=0) || Y%400==0)
            isLeapYear = true;
        return isLeapYear;
    }
};
#endif
