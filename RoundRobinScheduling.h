#ifndef _ROUND_ROBIN_SCHEDULING_H
#define _ROUND_ROBIN_SCHEDULING_H
#include "Debug.h"
/*
Round Robin
1. Practical approach to support time-sharing
2. Run process for a time slice (quantum), then move to back of FIFO queue
3. Preempted if still running at end of time slice

Algorithm:
1. Pick the first process in the queue (if it is not empty). Add it to the output list.
2. Execute it for a given quantum of time (or less if its remaining time is less than one quantum)
 and subtract this quantum from the remaining time of this process.
3. If new processes have arrived, add them to the end of the queue.
4. If the last executed process is not finished (that is, its remaining time is not 0),
 add it to the end of the waiting queue.
5. Go to step 1 if there are any processes left.

Advantages:
1. Low response time, good interactivity
2. Fair allocation of CPU across processes
3. Low average waiting time when job lengths vary widely
Disadvantages:
1. Poor average waiting time when jobs have similar lengths
 => Average waiting time is even worse than FCFS!
2. Performance depends on length of time slice
 => Too high: degenerate to FCFS
 => Too low: too many context switches, costly


arrival time = the timestamp when arrival
burst time = required time to complete the task
execution time = already executed time
completion time = the timestamp when execution time == burst time
turnaround time = completion time - arrival time
waiting time = time spent in waiting queue since arrival
response time = time spent in waiting queue since arrival to first execution
 */
class RoundRobinScheduling
{
public:
    RoundRobinScheduling(){}

    //   0             1           2               3                4                5             6              7
    //<pid, arrival time, burst time, execution time, completion time, turnaround time, waiting time, response time>
    std::deque<std::vector<int>> UseDeque(std::deque<std::vector<int>> &tasks, int quantum)
    {
        std::sort(tasks.begin(), tasks.end(), [](const std::vector<int> &a, const std::vector<int> &b)
        {
            return a[1] < b[1];
        });

        std::deque<std::vector<int>> que;
        std::deque<std::vector<int>> res;
        int curTime = 0;

        std::ostringstream oss;
        oss << "Quantum: " << quantum << std::endl;

        while (!que.empty() || !tasks.empty())
        {
            if (que.empty())
            {
                auto nxt = tasks.front();
                tasks.pop_front();
                que.push_back(nxt);
                curTime = nxt[1];
            }

            oss << "[" << curTime << ":";

            auto cur = que.front();
            que.pop_front();
            int remainingTime = cur[2] - cur[3];

            if (remainingTime > quantum)//execute it with quantum, push back cur task to que later
            {
                cur[3] += quantum;
                curTime += quantum;

                for (auto &v : que)
                {
                    v[6] += quantum;//waiting time
                    if (v[3] == 0)
                        v[7] += quantum;//response time
                }
            }
            else//execute it with min(remainingTime, quantum), push back cur task to res
            {
                cur[3] += std::min(remainingTime, quantum);
                curTime += std::min(remainingTime, quantum);
                cur[4] = curTime;//completion time
                cur[5] = cur[4] - cur[1];//turnaround time = completion time - arrival time
                res.push_back(cur);

                for (auto &v : que)
                {
                    v[6] += std::min(remainingTime, quantum);//waiting time
                    if (v[3] == 0)
                        v[7] += std::min(remainingTime, quantum);//response time
                }
            }
            oss << curTime << "]=" << "P" << cur[0] << ",";

            while (!tasks.empty() && curTime >= tasks.front()[1])
            {
                auto nxt = tasks.front();
                tasks.pop_front();
                nxt[6] += curTime - nxt[1];//waiting time
                nxt[7] += curTime - nxt[1];//response time
                que.push_back(nxt);
            }

            if (cur[3] < cur[2])//not finished
                que.push_back(cur);
        }

        std::cout << oss.str() << std::endl;
        return res;
    }

    void Test()
    {
        {
            std::deque<std::vector<int>> tasks(
                    {
                            {1, 0, 9, 0, 0, 0, 0, 0},
                            {2, 1, 5, 0, 0, 0, 0, 0},
                            {3, 2, 3, 0, 0, 0, 0, 0},
                            {4, 3, 4, 0, 0, 0, 0, 0},
                    });
            std::deque<std::vector<int>> res = UseDeque(tasks, 2);
            Debug::Print2D<int>()(res, false);
        }
        {
            std::deque<std::vector<int>> tasks(
                    {
                            {1, 0, 5, 0, 0, 0, 0, 0},
                            {2, 1, 3, 0, 0, 0, 0, 0},
                            {3, 3, 6, 0, 0, 0, 0, 0},
                            {4, 5, 1, 0, 0, 0, 0, 0},
                            {5, 6, 4, 0, 0, 0, 0, 0},
                    });
            std::deque<std::vector<int>> res = UseDeque(tasks, 3);
            Debug::Print2D<int>()(res, false);
        }
        {
            std::deque<std::vector<int>> tasks(
                    {
                            {1, 1, 4, 0, 0, 0, 0, 0},
                            {2, 2, 3, 0, 0, 0, 0, 0},
                            {3, 3, 5, 0, 0, 0, 0, 0},
                            {4, 4, 7, 0, 0, 0, 0, 0},
                    });
            std::deque<std::vector<int>> res = UseDeque(tasks, 2);
            Debug::Print2D<int>()(res, false);
        }
        {
            std::deque<std::vector<int>> tasks(
                    {
                            {1, 0, 8, 0, 0, 0, 0, 0},
                            {2, 1, 4, 0, 0, 0, 0, 0},
                            {3, 2, 9, 0, 0, 0, 0, 0},
                            {4, 3, 5, 0, 0, 0, 0, 0},
                    });
            std::deque<std::vector<int>> res = UseDeque(tasks, 1);
            Debug::Print2D<int>()(res, false);
        }
        {
            std::deque<std::vector<int>> tasks(
                    {
                            {0, 0, 250, 0, 0, 0, 0, 0},
                            {1, 50, 170, 0, 0, 0, 0, 0},
                            {2, 130, 75, 0, 0, 0, 0, 0},
                            {3, 190, 100, 0, 0, 0, 0, 0},
                            {4, 210, 130, 0, 0, 0, 0, 0},
                            {5, 350, 50, 0, 0, 0, 0, 0},
                    });
            std::deque<std::vector<int>> res = UseDeque(tasks, 100);
            Debug::Print2D<int>()(res, false);
        }
        {
            std::deque<std::vector<int>> tasks(
                    {
                            {1, 0, 7, 0, 0, 0, 0, 0},
                            {2, 2, 4, 0, 0, 0, 0, 0},
                            {3, 4, 1, 0, 0, 0, 0, 0},
                            {4, 5, 4, 0, 0, 0, 0, 0},
                    });
            std::deque<std::vector<int>> res = UseDeque(tasks, 3);
            Debug::Print2D<int>()(res, false);
        }
        {
            std::deque<std::vector<int>> tasks(
                    {
                            {1, 0, 7, 0, 0, 0, 0, 0},
                            {2, 2, 4, 0, 0, 0, 0, 0},
                            {3, 4, 1, 0, 0, 0, 0, 0},
                            {4, 5, 4, 0, 0, 0, 0, 0},
                    });
            std::deque<std::vector<int>> res = UseDeque(tasks, 1);
            Debug::Print2D<int>()(res, false);
        }
        {
            std::deque<std::vector<int>> tasks(
                    {
                            {1, 0, 7, 0, 0, 0, 0, 0},
                            {2, 2, 4, 0, 0, 0, 0, 0},
                            {3, 4, 1, 0, 0, 0, 0, 0},
                            {4, 5, 4, 0, 0, 0, 0, 0},
                    });
            std::deque<std::vector<int>> res = UseDeque(tasks, 10);
            Debug::Print2D<int>()(res, false);
        }
        {
            std::deque<std::vector<int>> tasks(
                    {
                            {0, 0, 5, 0, 0, 0, 0, 0},
                            {1, 1, 3, 0, 0, 0, 0, 0},
                            {2, 2, 8, 0, 0, 0, 0, 0},
                            {3, 3, 6, 0, 0, 0, 0, 0},
                    });
            std::deque<std::vector<int>> res = UseDeque(tasks, 3);
            Debug::Print2D<int>()(res, false);
        }
        {
            std::deque<std::vector<int>> tasks(
                    {
                            {1, 0, 3, 0, 0, 0, 0, 0},
                            {2, 0, 4, 0, 0, 0, 0, 0},
                            {3, 0, 3, 0, 0, 0, 0, 0},
                    });
            std::deque<std::vector<int>> res = UseDeque(tasks, 1);
            Debug::Print2D<int>()(res, false);
        }
        {
            std::deque<std::vector<int>> tasks(
                    {
                            {1, 0, 53, 0, 0, 0, 0, 0},
                            {2, 0, 17, 0, 0, 0, 0, 0},
                            {3, 0, 68, 0, 0, 0, 0, 0},
                            {4, 0, 24, 0, 0, 0, 0, 0},
                    });
            std::deque<std::vector<int>> res = UseDeque(tasks, 20);
            Debug::Print2D<int>()(res, false);
        }
        {
            std::deque<std::vector<int>> tasks(
                    {
                            {1, 0, 3, 0, 0, 0, 0, 0},
                            {2, 2, 6, 0, 0, 0, 0, 0},
                            {3, 4, 4, 0, 0, 0, 0, 0},
                            {4, 6, 5, 0, 0, 0, 0, 0},
                            {5, 8, 2, 0, 0, 0, 0, 0},
                    });
            std::deque<std::vector<int>> res = UseDeque(tasks, 2);
            Debug::Print2D<int>()(res, false);
        }
        {
            std::deque<std::vector<int>> tasks(
                    {
                            {1, 5, 5, 0, 0, 0, 0, 0},
                            {2, 4, 6, 0, 0, 0, 0, 0},
                            {3, 3, 7, 0, 0, 0, 0, 0},
                            {4, 1, 9, 0, 0, 0, 0, 0},
                            {5, 2, 2, 0, 0, 0, 0, 0},
                            {6, 6, 3, 0, 0, 0, 0, 0},
                    });
            std::deque<std::vector<int>> res = UseDeque(tasks, 3);
            Debug::Print2D<int>()(res, false);
        }
    }
};
/*
Quantum: 2
[0:2]=P1,[2:4]=P2,[4:6]=P3,[6:8]=P1,[8:10]=P4,[10:12]=P2,[12:13]=P3,[13:15]=P1,[15:17]=P4,[17:18]=P2,[18:20]=P1,[20:21]=P1,
[rY][cX]
Row#0	= 3, 2, 3, 3, 13, 11, 8, 2
Row#1	= 4, 3, 4, 4, 17, 14, 10, 5
Row#2	= 2, 1, 5, 5, 18, 17, 12, 1
Row#3	= 1, 0, 9, 9, 21, 21, 12, 0

Quantum: 3
[0:3]=P1,[3:6]=P2,[6:9]=P3,[9:11]=P1,[11:12]=P4,[12:15]=P5,[15:18]=P3,[18:19]=P5,
[rY][cX]
Row#0	= 2, 1, 3, 3, 6, 5, 2, 2
Row#1	= 1, 0, 5, 5, 11, 11, 6, 0
Row#2	= 4, 5, 1, 1, 12, 7, 6, 6
Row#3	= 3, 3, 6, 6, 18, 15, 9, 3
Row#4	= 5, 6, 4, 4, 19, 13, 9, 6

Quantum: 2
[1:3]=P1,[3:5]=P2,[5:7]=P3,[7:9]=P1,[9:11]=P4,[11:12]=P2,[12:14]=P3,[14:16]=P4,[16:17]=P3,[17:19]=P4,[19:20]=P4,
[rY][cX]
Row#0	= 1, 1, 4, 4, 9, 8, 4, 0
Row#1	= 2, 2, 3, 3, 12, 10, 7, 1
Row#2	= 3, 3, 5, 5, 17, 14, 9, 2
Row#3	= 4, 4, 7, 7, 20, 16, 9, 5

Quantum: 1
[0:1]=P1,[1:2]=P2,[2:3]=P1,[3:4]=P3,[4:5]=P2,[5:6]=P4,[6:7]=P1,[7:8]=P3,[8:9]=P2,[9:10]=P4,[10:11]=P1,[11:12]=P3,[12:13]=P2,[13:14]=P4,[14:15]=P1,[15:16]=P3,[16:17]=P4,[17:18]=P1,[18:19]=P3,[19:20]=P4,[20:21]=P1,[21:22]=P3,[22:23]=P1,[23:24]=P3,[24:25]=P3,[25:26]=P3,
[rY][cX]
Row#0	= 2, 1, 4, 4, 13, 12, 8, 0
Row#1	= 4, 3, 5, 5, 20, 17, 12, 2
Row#2	= 1, 0, 8, 8, 23, 23, 15, 0
Row#3	= 3, 2, 9, 9, 26, 24, 15, 1

Quantum: 100
[0:100]=P0,[100:200]=P1,[200:300]=P0,[300:375]=P2,[375:475]=P3,[475:545]=P1,[545:645]=P4,[645:695]=P0,[695:745]=P5,[745:775]=P4,
[rY][cX]
Row#0	= 2, 130, 75, 75, 375, 245, 170, 170
Row#1	= 3, 190, 100, 100, 475, 285, 185, 185
Row#2	= 1, 50, 170, 170, 545, 495, 325, 50
Row#3	= 0, 0, 250, 250, 695, 695, 445, 0
Row#4	= 5, 350, 50, 50, 745, 395, 345, 345
Row#5	= 4, 210, 130, 130, 775, 565, 435, 335

Quantum: 3
[0:3]=P1,[3:6]=P2,[6:9]=P1,[9:10]=P3,[10:13]=P4,[13:14]=P2,[14:15]=P1,[15:16]=P4,
[rY][cX]
Row#0	= 3, 4, 1, 1, 10, 6, 5, 5
Row#1	= 2, 2, 4, 4, 14, 12, 8, 1
Row#2	= 1, 0, 7, 7, 15, 15, 8, 0
Row#3	= 4, 5, 4, 4, 16, 11, 7, 5

Quantum: 1
[0:1]=P1,[1:2]=P1,[2:3]=P2,[3:4]=P1,[4:5]=P2,[5:6]=P3,[6:7]=P1,[7:8]=P4,[8:9]=P2,[9:10]=P1,[10:11]=P4,[11:12]=P2,[12:13]=P1,[13:14]=P4,[14:15]=P1,[15:16]=P4,
[rY][cX]
Row#0	= 3, 4, 1, 1, 6, 2, 1, 1
Row#1	= 2, 2, 4, 4, 12, 10, 6, 0
Row#2	= 1, 0, 7, 7, 15, 15, 8, 0
Row#3	= 4, 5, 4, 4, 16, 11, 7, 2

Quantum: 10
[0:7]=P1,[7:11]=P2,[11:12]=P3,[12:16]=P4,
[rY][cX]
Row#0	= 1, 0, 7, 7, 7, 7, 0, 0
Row#1	= 2, 2, 4, 4, 11, 9, 5, 5
Row#2	= 3, 4, 1, 1, 12, 8, 7, 7
Row#3	= 4, 5, 4, 4, 16, 11, 7, 7

Quantum: 3
[0:3]=P0,[3:6]=P1,[6:9]=P2,[9:12]=P3,[12:14]=P0,[14:17]=P2,[17:20]=P3,[20:22]=P2,
[rY][cX]
Row#0	= 1, 1, 3, 3, 6, 5, 2, 2
Row#1	= 0, 0, 5, 5, 14, 14, 9, 0
Row#2	= 3, 3, 6, 6, 20, 17, 11, 6
Row#3	= 2, 2, 8, 8, 22, 20, 12, 4

Quantum: 1
[0:1]=P1,[1:2]=P2,[2:3]=P3,[3:4]=P1,[4:5]=P2,[5:6]=P3,[6:7]=P1,[7:8]=P2,[8:9]=P3,[9:10]=P2,
[rY][cX]
Row#0	= 1, 0, 3, 3, 7, 7, 4, 0
Row#1	= 3, 0, 3, 3, 9, 9, 6, 2
Row#2	= 2, 0, 4, 4, 10, 10, 6, 1

Quantum: 20
[0:20]=P1,[20:37]=P2,[37:57]=P3,[57:77]=P4,[77:97]=P1,[97:117]=P3,[117:121]=P4,[121:134]=P1,[134:154]=P3,[154:162]=P3,
[rY][cX]
Row#0	= 2, 0, 17, 17, 37, 37, 20, 20
Row#1	= 4, 0, 24, 24, 121, 121, 97, 57
Row#2	= 1, 0, 53, 53, 134, 134, 81, 0
Row#3	= 3, 0, 68, 68, 162, 162, 94, 37

Quantum: 2
[0:2]=P1,[2:4]=P2,[4:5]=P1,[5:7]=P3,[7:9]=P2,[9:11]=P4,[11:13]=P3,[13:15]=P5,[15:17]=P2,[17:19]=P4,[19:20]=P4,
[rY][cX]
Row#0	= 1, 0, 3, 3, 5, 5, 2, 0
Row#1	= 3, 4, 4, 4, 13, 9, 5, 1
Row#2	= 5, 8, 2, 2, 15, 7, 5, 5
Row#3	= 2, 2, 6, 6, 17, 15, 9, 0
Row#4	= 4, 6, 5, 5, 20, 14, 9, 3

Quantum: 3
[1:4]=P4,[4:6]=P5,[6:9]=P3,[9:12]=P2,[12:15]=P4,[15:18]=P1,[18:21]=P6,[21:24]=P3,[24:27]=P2,[27:30]=P4,[30:32]=P1,[32:33]=P3,
[rY][cX]
Row#0	= 5, 2, 2, 2, 6, 4, 2, 2
Row#1	= 6, 6, 3, 3, 21, 15, 12, 12
Row#2	= 2, 4, 6, 6, 27, 23, 17, 5
Row#3	= 4, 1, 9, 9, 30, 29, 20, 0
Row#4	= 1, 5, 5, 5, 32, 27, 22, 10
Row#5	= 3, 3, 7, 7, 33, 30, 23, 3
 */
#endif
