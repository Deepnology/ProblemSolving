#ifndef _MAX_DIST_TO_CLOSEST_PERSON_H
#define _MAX_DIST_TO_CLOSEST_PERSON_H
#include "Debug.h"
/*
Leetcode: Maximize Distance To Closest Person
In a row of seats, 1 represents a person sitting in that seat, and 0 represents that the seat is empty.
There is at least one empty seat, and at least one person sitting.
Alex wants to sit in the seat such that the distance between him and the closest person to him is maximized.
Return that maximum distance to closest person.
Example 1:
Input: [1,0,0,0,1,0,1]
Output: 2
Explanation:
If Alex sits in the second open seat (seats[2]), then the closest person has distance 2.
If Alex sits in any other open seat, the closest person has distance 1.
Thus, the maximum distance to the closest person is 2.
Example 2:
Input: [1,0,0,0]
Output: 3
Explanation:
If Alex sits in the last seat, the closest person is 3 seats away.
This is the maximum distance possible, so the answer is 3.
 */
class MaxDistToClosestPerson
{
public:
    MaxDistToClosestPerson(){}
    ~MaxDistToClosestPerson(){}

    int FindLongest0sSubArr(std::vector<int> && seats)
    {
        int N = seats.size();
        int i = 0;
        int maxLen0 = 0;//find longest 0s subarray
        while (i < N)
        {
            while (i < N && seats[i] == 1)
                ++i;
            int j = i;
            while (j < N && seats[j] == 0)
                ++j;
            if (i==0 || j==N)//0s in the begin or end
            {
                maxLen0 = std::max(maxLen0, j-i);
            }
            else//0s in the middle
            {
                maxLen0 = std::max(maxLen0, (j-i)%2==0?(j-i)/2:(j-i)/2+1);
            }
            i = j;
        }

        std::cout << "MaxDistToClosestPerson FindLongest0sSubArr for [" << Debug::ToStr1D<int>()(seats) << "]: " << maxLen0 << std::endl;
        return maxLen0;
    }
};
/*
MaxDistToClosestPerson FindLongest0sSubArr for [1, 0, 0, 0, 1, 0, 1]: 2
MaxDistToClosestPerson FindLongest0sSubArr for [1, 0, 0, 0]: 3
 */
#endif
