#ifndef _MAX_NUM_EVENTS_TO_ATTEND_AT_MOST_1_AT_A_TIME_H
#define _MAX_NUM_EVENTS_TO_ATTEND_AT_MOST_1_AT_A_TIME_H
#include "Debug.h"
/*
Leetcode: Maximum Number of Events That Can Be Attended
Given an array of events where events[i] = [startDayi, endDayi].
Every event i starts at startDayi and ends at endDayi.
You can attend an event i at any day d where startTimei <= d <= endTimei.
Notice that you can only attend one event at any time d.
Return the maximum number of events you can attend.
Input: events = [[1,2],[2,3],[3,4]]
Output: 3
Explanation: You can attend all the three events.
One way to attend them all is as shown.
Attend the first event on day 1.
Attend the second event on day 2.
Attend the third event on day 3.
 */
class MaxNumEventsToAttendAtMost1AtATime
{
    struct Greater
    {
        bool operator()(const std::vector<int> & a, const std::vector<int> & b) const
        {
            return a[1] > b[1];
        }
    };
public:
    int Sort_MinHeap(std::vector<std::vector<int>> & events)
    {
        std::sort(events.begin(),events.end(),[](const std::vector<int>&a, const std::vector<int>&b)
        {
            return a[0] < b[0];
        });
        int N = events.size();
        int i = 0;
        int d = 0;
        int res = 0;
        std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, Greater> minHeap;
        while (i < N || !minHeap.empty())
        {
            if (minHeap.empty())
                d = events[i][0];//jump to nearest event
            //move covered events to minHeap
            while (i < N && events[i][0] == d)
                minHeap.push(events[i++]);
            //now we choose an event that has min end time
            minHeap.pop();
            ++res;
            ++d;//advance to next day
            //now remove all events in minHeap whose end time < d
            while (!minHeap.empty() && minHeap.top()[1] < d)
                minHeap.pop();
        }
        return res;
    }
};
#endif
