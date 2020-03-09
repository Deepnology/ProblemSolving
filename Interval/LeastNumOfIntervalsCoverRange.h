/*Facebook*/
#ifndef _LEAST_NUM_OF_INTERVALS_COVER_RANGE_H
#define _LEAST_NUM_OF_INTERVALS_COVER_RANGE_H
#include "Debug.h"
/*
Leetcode: Video Stitching
You are given a series of video clips from a sporting event that lasted T seconds.
These video clips can be overlapping with each other and have varied lengths.
Each video clip clips[i] is an interval: it starts at time clips[i][0] and ends at time clips[i][1].
We can cut these clips into segments freely: for example, a clip [0, 7] can be cut into segments [0, 1] + [1, 3] + [3, 7].
Return the minimum number of clips needed so that we can cut the clips into segments that cover the entire sporting event ([0, T]).
If the task is impossible, return -1.
Example 1:
Input: clips = [[0,2],[4,6],[8,10],[1,9],[1,5],[5,9]], T = 10
Output: 3
Explanation:
We take the clips [0,2], [8,10], [1,9]; a total of 3 clips.
Then, we can reconstruct the sporting event as follows:
We cut [1,9] into segments [1,2] + [2,8] + [8,9].
Now we have segments [0,2] + [2,8] + [8,10] which cover the sporting event [0, 10].
Example 2:
Input: clips = [[0,1],[1,2]], T = 5
Output: -1
Explanation:
We can't cover [0,5] with only [0,1] and [0,2].
Example 3:
Input: clips = [[0,1],[6,8],[0,2],[5,6],[0,4],[0,3],[6,7],[1,3],[4,7],[1,4],[2,5],[2,6],[3,4],[4,5],[5,7],[6,9]], T = 9
Output: 3
Explanation:
We can take clips [0,4], [4,7], and [6,9].
Example 4:
Input: clips = [[0,4],[2,8]], T = 5
Output: 2
Explanation:
Notice you can have extra video after the event ends.

https://discuss.leetcode.com/topic/244/find-least-number-of-intervals-from-a-that-can-fully-cover-b
Given a list of intervals A and one interval B, find the least
number of intervals from A that can fully cover B.
If cannot find any result, just return 0;
For example:
Given A=[[0,3],[3,4],[4,6],[2,7]] B=[0,6] return 2 since we can use [0,3] [2,7] to cover the B
Given A=[[0,3],[4,7]] B=[0,6] return 0 since we cannot find any interval combination from A to cover the B
 */
class LeastNumOfIntervalsCoverRange
{
public:
    LeastNumOfIntervalsCoverRange(){}

    int SortGreedy(std::vector<std::vector<int>> && clips, int T)
    {
        //O(NlogN) time
        std::sort(clips.begin(), clips.end());
        int N = clips.size();
        int i = 0;
        int count = 0;
        int start = 0;//prev max end
        int end = 0;//cur max end
        while (start < T)
        {
            while (i < N && clips[i][0] <= start)
            {
                end = std::max(end, clips[i][1]);
                ++i;
            }
            if (end == start)
            {
                std::cout << "LeastNumOfIntervalsCoverRange SortGreedy for [" << Debug::ToStr1D<int>()(clips) << "] cover [0:" << T << "]: -1" << std::endl;
                return -1; //end didn't advance
            }
            ++count; //include one interval
            start = end;
        }
        std::cout << "LeastNumOfIntervalsCoverRange SortGreedy for [" << Debug::ToStr1D<int>()(clips) << "] cover [0:" << T << "]: " << count << std::endl;
        return count;
    }
    int HashMap(std::vector<std::vector<int>> && clips, int T)
    {
        //O(max(N,T)) time
        std::unordered_map<int,int> startToMaxEnd;
        for (auto & v : clips)
            startToMaxEnd[v[0]]=std::max(startToMaxEnd[v[0]],v[1]);
        int t = 0;
        int start = -1; //prev max end
        int end = 0; //cur max end
        int count = 0;
        while (t <= T)
        {
            if (end < t)
            {
                std::cout << "LeastNumOfIntervalsCoverRange HashMap for [" << Debug::ToStr1D<int>()(clips) << "] cover [0:" << T << "]: -1" << std::endl;
                return -1;
            }
            if (startToMaxEnd.count(t))
                end = std::max(end, startToMaxEnd[t]);
            if (t >= start)//t reaches prev max end
            {
                ++count;//incluce one interval
                start = end;//update cur max end
                if (start >= T)
                {
                    std::cout << "LeastNumOfIntervalsCoverRange HashMap for [" << Debug::ToStr1D<int>()(clips) << "] cover [0:" << T << "]: " << count << std::endl;
                    return count;
                }
            }
            ++t;
        }
        std::cout << "LeastNumOfIntervalsCoverRange HashMap for [" << Debug::ToStr1D<int>()(clips) << "] cover [0:" << T << "]: -1" << std::endl;
        return -1;
    }


    int SortGreedy2(std::vector<std::pair<int,int>> v, std::pair<int,int> tgt)
    {
        std::sort(v.begin(), v.end(), [](const std::pair<int,int> & a, const std::pair<int,int> & b)
        {
           return a.first != b.first ? a.first < b.first : a.second < b.second;
        });

        int N = v.size();
        int count = 0;
        int i = 0;
        int start = tgt.first;
        int end = tgt.first - 1;
        while (i < N)
        {
            if (v[i].first <= start)//just advance
            {
                end = std::max(end, v[i].second);
                ++i;
            }
            else//include one of prev interval, and also get max end from prev intervals
            {
                start = end;
                ++count;
                if (v[i].first > end //no overlap for intervals after
                    || end >= tgt.second) //already covered, no need more intervals
                    break;
            }
        }
        if (end < tgt.second)
            count = -1;

        std::cout << "LeastNumOfIntervalsCoverRange SortGreedy2 for [" << Debug::ToStr1D<int>()(v) << "], tgt=[" << Debug::ToStr1D<int>()(tgt) << "]: " << count << std::endl;
        return count;
    }
};
/*
LeastNumOfIntervalsCoverRange SortGreedy for [[0,3], [2,7], [3,4], [4,6]] cover [0:6]: 2
LeastNumOfIntervalsCoverRange SortGreedy for [[0,3], [4,7]] cover [0:6]: -1
LeastNumOfIntervalsCoverRange HashMap for [[3,4], [2,7], [0,3], [4,6]] cover [0:6]: 2
LeastNumOfIntervalsCoverRange HashMap for [[0,3], [4,7]] cover [0:6]: -1
LeastNumOfIntervalsCoverRange SortGreedy2 for [[0,3], [2,7], [3,4], [4,6]], tgt=[0, 6]: 2
LeastNumOfIntervalsCoverRange SortGreedy2 for [[0,3], [4,7]], tgt=[0, 6]: -1
LeastNumOfIntervalsCoverRange SortGreedy2 for [[0,3], [2,7], [3,4], [4,6]], tgt=[-1, 6]: -1
 */
#endif
