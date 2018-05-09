#ifndef _NEXT_CLOSEST_TIME_H
#define _NEXT_CLOSEST_TIME_H
#include "Debug.h"
/*
Leetcode: Next Closest Time
Given a time represented in the format "HH:MM", form the next closest time by reusing the current digits.
There is no limit on how many times a digit can be reused.
You may assume the given input string is always valid.
For example, "01:34", "12:09" are all valid. "1:34", "12:9" are all invalid.
Example 1:
Input: "19:34"
Output: "19:39"
Explanation: The next closest time choosing from digits 1, 9, 3, 4, is 19:39, which occurs 5 minutes later.
It is not 19:33, because this occurs 23 hours and 59 minutes later.
Example 2:
Input: "23:59"
Output: "22:22"
Explanation: The next closest time choosing from digits 2, 3, 5, 9, is 22:22.
It may be assumed that the returned time is next day's time since it is smaller than the input time numerically.
 */
class NextClosestTime
{
public:
    NextClosestTime(){}

    std::string Solve(std::string time)
    {
        std::string res = ReplaceDigitByDigit(time);
        std::cout << "NextClosestTime for \"" << time << "\": " << res << std::endl;
        return res;
    }
private:
    std::string ReplaceDigitByDigit(std::string time)
    {
        std::set<char> charSet;
        for (char c : time)
            if (c != ':')
            {
                charSet.insert(c);
            }
        char minChar = *charSet.begin();

        for (int i = 4; i >= 0; --i)
        {
            if (time[i] == ':') continue;
            auto itr = std::upper_bound(charSet.begin(), charSet.end(), time[i]);
            if (itr == charSet.end()) continue;
            if (i == 0 && *itr >= '3') continue;
            if (i == 1 && time[0] == '2' && *itr >= '4') continue;
            if (i == 3 && *itr >= '6') continue;
            time[i] = *itr;
            for (int j = i+1; j < 5; ++j)
            {
                if (time[j] == ':') continue;
                time[j] = minChar;
            }
            return time;
        }
        for (int i = 0; i < 5; ++i)
        {
            if (time[i] == ':') continue;
            time[i] = minChar;
        }
        return time;
    }
};
/*
NextClosestTime for "19:34": 19:39
NextClosestTime for "23:59": 22:22
 */
#endif
