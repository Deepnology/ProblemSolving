#ifndef _MIN_STEPS_TO_OPEN_4_DIGIT_LOCK_H
#define _MIN_STEPS_TO_OPEN_4_DIGIT_LOCK_H
#include "Debug.h"
/*
Leetcode: Open the lock
You have a lock in front of you with 4 circular wheels.
Each wheel has 10 slots: '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'.
The wheels can rotate freely and wrap around: for example we can turn '9' to be '0', or '0' to be '9'.
Each move consists of turning one wheel one slot.
The lock initially starts at '0000', a string representing the state of the 4 wheels.
You are given a list of deadends dead ends, meaning if the lock displays any of these codes,
 the wheels of the lock will stop turning and you will be unable to open it.
Given a target representing the value of the wheels that will unlock the lock,
 return the minimum total number of turns required to open the lock, or -1 if it is impossible.
Example 1:
Input: deadends = ["0201","0101","0102","1212","2002"], target = "0202"
Output: 6
Explanation:
A sequence of valid moves would be "0000" -> "1000" -> "1100" -> "1200" -> "1201" -> "1202" -> "0202".
Note that a sequence like "0000" -> "0001" -> "0002" -> "0102" -> "0202" would be invalid,
because the wheels of the lock become stuck after the display becomes the dead end "0102".
Example 2:
Input: deadends = ["8888"], target = "0009"
Output: 1
Explanation:
We can turn the last wheel in reverse to move from "0000" -> "0009".
Example 3:
Input: deadends = ["8887","8889","8878","8898","8788","8988","7888","9888"], target = "8888"
Output: -1
Explanation:
We can't reach the target without getting stuck.
Example 4:
Input: deadends = ["0000"], target = "8888"
Output: -1
 */
class MinStepsToOpen4DigitLock
{
public:
    MinStepsToOpen4DigitLock(){}

    void Test(const std::vector<std::string> & deadends, std::string target)
    {
        int bfs2 = BFS_2Directions(deadends, target);
        int bfs = BFS(deadends, target);
        std::cout << "MinStepsToOpen4DigitLock for deadends=[" << Debug::ToStr1D<std::string>()(deadends) << "], target=" << target << ": " << bfs2 << "," << bfs << std::endl;
    }

    int BFS_2Directions(const std::vector<std::string> & deadends, std::string target)
    {
        std::unordered_set<std::string> dead(deadends.begin(), deadends.end());
        if (dead.count("0000") || dead.count(target)) return -1;
        std::unordered_set<std::string> visit;
        std::unordered_set<std::string> fward;
        std::unordered_set<std::string> bward;
        fward.insert("0000");
        bward.insert(target);
        visit.insert("0000");
        visit.insert(target);
        int dist = 0;
        while (!fward.empty() && !bward.empty())
        {
            if (bward.size() < fward.size())
                std::swap(fward, bward);
            std::unordered_set<std::string> nxtLevel;
            for (auto &cur : fward)
            {
                for (int i = 0; i < 4; ++i)
                {
                    std::string nxt = cur;
                    nxt[i] = (cur[i] - '0' + 1) % 10 + '0';
                    if (bward.count(nxt)) return dist + 1;
                    if (!dead.count(nxt) && !visit.count(nxt))
                    {
                        visit.insert(nxt);
                        nxtLevel.insert(nxt);
                    }
                    std::string pre = cur;
                    pre[i] = (cur[i] - '0' - 1 + 10) % 10 + '0';
                    if (bward.count(pre)) return dist + 1;
                    if (!dead.count(pre) && !visit.count(pre))
                    {
                        visit.insert(pre);
                        nxtLevel.insert(pre);
                    }
                }
            }
            ++dist;
            std::swap(fward, nxtLevel);
            //fward = nxtLevel;
        }
        return -1;
    }

    int BFS(const std::vector<std::string> & deadends, std::string target)
    {
        std::unordered_set<std::string> dead(deadends.begin(), deadends.end());
        if (dead.count("0000") || dead.count(target)) return -1;
        std::unordered_set<std::string> visit;
        std::queue<std::string> que;
        que.push("0000");
        visit.insert("0000");
        int dist = 0;
        while (!que.empty())
        {
            int levelCount = que.size();
            while (levelCount-->0)
            {
                std::string cur = que.front(); que.pop();
                if (cur == target) return dist;
                for (int i = 0; i < 4; ++i)
                {
                    std::string nxt = cur;
                    nxt[i] = (cur[i]-'0'+1) % 10 + '0';
                    if (!dead.count(nxt) && !visit.count(nxt))
                    {
                        visit.insert(nxt);
                        que.push(nxt);
                    }
                    std::string pre = cur;
                    pre[i] = (cur[i]-'0'-1+10) % 10 + '0';
                    if (!dead.count(pre) && !visit.count(pre))
                    {
                        visit.insert(pre);
                        que.push(pre);
                    }
                }
            }
            ++dist;
        }
        return -1;
    }
};
/*
MinStepsToOpen4DigitLock for deadends=[8887, 8889, 8878, 8898, 8788, 8988, 7888, 9888], target=8888: -1,-1
 */
#endif
