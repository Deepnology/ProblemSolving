#ifndef _CALENDAR_INTERVAL_H
#define _CALENDAR_INTERVAL_H
#include "Debug.h"
/*
Leetcode: My Calendar I
Implement a MyCalendar class to store your events.
 A new event can be added if adding the event will not cause a double booking.
Your class will have the method, book(int start, int end).
 Formally, this represents a booking on the half open interval [start, end), the range of real numbers x such that start <= x < end.
A double booking happens when two events have some non-empty intersection (ie., there is some time that is common to both events.)
For each call to the method MyCalendar.book, return true if the event can be added to the calendar successfully without causing a double booking.
 Otherwise, return false and do not add the event to the calendar.
Your class will be called like this: MyCalendar cal = new MyCalendar(); MyCalendar.book(start, end)
Example 1:
MyCalendar();
MyCalendar.book(10, 20); // returns true
MyCalendar.book(15, 25); // returns false
MyCalendar.book(20, 30); // returns true
Explanation:
The first event can be booked.  The second can't because time 15 is already booked by another event.
The third event can be booked, as the first event takes every time less than 20, but not including 20.

Leetcode: My Calendar II
Implement a MyCalendarTwo class to store your events.
 A new event can be added if adding the event will not cause a triple booking.
Your class will have one method, book(int start, int end).
 Formally, this represents a booking on the half open interval [start, end), the range of real numbers x such that start <= x < end.
A triple booking happens when three events have some non-empty intersection (ie., there is some time that is common to all 3 events.)
For each call to the method MyCalendar.book, return true if the event can be added to the calendar successfully without causing a triple booking.
 Otherwise, return false and do not add the event to the calendar.
Your class will be called like this: MyCalendar cal = new MyCalendar(); MyCalendar.book(start, end)
Example 1:
MyCalendar();
MyCalendar.book(10, 20); // returns true
MyCalendar.book(50, 60); // returns true
MyCalendar.book(10, 40); // returns true
MyCalendar.book(5, 15); // returns false
MyCalendar.book(5, 10); // returns true
MyCalendar.book(25, 55); // returns true
Explanation:
The first two events can be booked.  The third event can be double booked.
The fourth event (5, 15) can't be booked, because it would result in a triple booking.
The fifth event (5, 10) can be booked, as it does not use time 10 which is already double booked.
The sixth event (25, 55) can be booked, as the time in [25, 40) will be double booked with the third event;
the time [40, 50) will be single booked, and the time [50, 55) will be double booked with the second event.

Leetcode: My Calendar III
Implement a MyCalendarThree class to store your events.
 A new event can always be added.
Your class will have one method, book(int start, int end).
 Formally, this represents a booking on the half open interval [start, end), the range of real numbers x such that start <= x < end.
A K-booking happens when K events have some non-empty intersection (ie., there is some time that is common to all K events.)
For each call to the method MyCalendar.book, return an integer K representing the largest integer such that there exists a K-booking in the calendar.
Your class will be called like this: MyCalendarThree cal = new MyCalendarThree(); MyCalendarThree.book(start, end)
Example 1:
MyCalendarThree();
MyCalendarThree.book(10, 20); // returns 1
MyCalendarThree.book(50, 60); // returns 1
MyCalendarThree.book(10, 40); // returns 2
MyCalendarThree.book(5, 15); // returns 3
MyCalendarThree.book(5, 10); // returns 3
MyCalendarThree.book(25, 55); // returns 3
Explanation:
The first two events can be booked and are disjoint, so the maximum K-booking is a 1-booking.
The third event [10, 40) intersects the first event, and the maximum K-booking is a 2-booking.
The remaining events cause the maximum K-booking to be only a 3-booking.
Note that the last event locally causes a 2-booking, but the answer is still 3 because
eg. [10, 20), [10, 40), and [5, 15) are still triple booked.
 */
class CalendarIntervalI
{
    std::map<int,int> map;//<start time, end time>
public:
    CalendarIntervalI(){}
    bool CheckOverlap_Book(int start, int end)
    {
        if (map.empty())//adding this case to avoid when itr hitting map.end() without prev(itr)
        {
            map.insert({start,end});
            return true;
        }
        auto itr = map.lower_bound(start);

        //1. first check prev(itr)'s range in case of itr==map.end(): start1<end2&&start2<end1 for overlap
        if (itr != map.begin() && start < std::prev(itr)->second && std::prev(itr)->first < end)
            return false;
        //2. check itr's range: start1<end2&&start2<end1 for overlap
        if (itr->first < end && start < itr->second)
            return false;

        map.insert({start,end});
        return true;
    }
};
class CalendarIntervalII
{
    std::map<int,int> map;//<start/end time, positive/negative count>
public:
    CalendarIntervalII(){}
    bool CheckTripleOverlap_Book(int start, int end)
    {
        ++map[start];
        --map[end];

        int count = 0;
        for (const auto & p : map)
        {
            count += p.second;
            if (count == 3)
            {
                --map[start];
                ++map[end];
                return false;
            }
        }
        return true;
    }
};
class CalendarIntervalIII
{
    std::map<int,int> map;//<start/end time, positive/negative count>
public:
    CalendarIntervalIII(){}
    int CountMaxOverlap_Book(int start, int end)
    {
        ++map[start];
        --map[end];
        int res = 0;
        int count = 0;
        for (const auto & p : map)
        {
            count += p.second;
            res = std::max(res, count);
        }
        return res;
    }
};
#endif
