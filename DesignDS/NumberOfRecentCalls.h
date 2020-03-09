#ifndef _NUMBER_OF_RECENT_CALLS_H
#define _NUMBER_OF_RECENT_CALLS_H
#include "Debug.h"
/*
Leetcode: Number of Recent Calls
Write a class RecentCounter to count recent requests.
It has only one method: ping(int t), where t represents some time in milliseconds.
Return the number of pings that have been made from 3000 milliseconds ago until now.
Any ping with time in [t - 3000, t] will count, including the current ping.
It is guaranteed that every call to ping uses a strictly larger value of t than before.
Example 1:
Input: inputs = ["RecentCounter","ping","ping","ping","ping"], inputs = [[],[1],[100],[3001],[3002]]
Output: [null,1,2,3,3]
 */
class NumberOfRecentCalls
{
    std::queue<int> timeQue;
public:
    NumberOfRecentCalls(){}

    int Ping(int timeStamp)
    {
        timeQue.push(timeStamp);
        while (!timeQue.empty() && timeQue.front() < timeStamp - 3000)
            timeQue.pop();

        std::cout << "NumberOfRecentCalls Ping " << timeStamp << ": " << timeQue.size() << std::endl;
        return timeQue.size();
    }
};
/*
NumberOfRecentCalls Ping 1: 1
NumberOfRecentCalls Ping 100: 2
NumberOfRecentCalls Ping 3001: 3
NumberOfRecentCalls Ping 3002: 3
 */
#endif
