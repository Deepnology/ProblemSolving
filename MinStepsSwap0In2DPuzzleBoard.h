#ifndef _MIN_STEPS_SWAP_0_IN_2D_PUZZLE_BOARD_H
#define _MIN_STEPS_SWAP_0_IN_2D_PUZZLE_BOARD_H
#include "Debug.h"
/*
Leetcode: Sliding Puzzle
On a 2x3 board, there are 5 tiles represented by the integers 1 through 5, and an empty square represented by 0.
A move consists of choosing 0 and a 4-directionally adjacent number and swapping it.
The state of the board is solved if and only if the board is [[1,2,3],[4,5,0]].
Given a puzzle board, return the least number of moves required so that the state of the board is solved.
If it is impossible for the state of the board to be solved, return -1.
Examples:
Input: board = [[1,2,3],[4,0,5]]
Output: 1
Explanation: Swap the 0 and the 5 in one move.
Input: board = [[1,2,3],[5,4,0]]
Output: -1
Explanation: No number of moves will make the board solved.
Input: board = [[4,1,2],[5,0,3]]
Output: 5
Explanation: 5 is the smallest number of moves that solves the board.
An example path:
After move 0: [[4,1,2],[5,0,3]]
After move 1: [[4,1,2],[0,5,3]]
After move 2: [[0,1,2],[4,5,3]]
After move 3: [[1,0,2],[4,5,3]]
After move 4: [[1,2,0],[4,5,3]]
After move 5: [[1,2,3],[4,5,0]]
Input: board = [[3,2,4],[1,5,0]]
Output: 14
 */
class MinStepsSwap0In2DPuzzleBoard
{
public:
    MinStepsSwap0In2DPuzzleBoard(){}

    void Test(const std::vector<std::vector<int>> & board)
    {
        int bfs = BFS(board);
        Debug::Print2D<int>()(board, false);
        std::cout << "MinStepsSwap0In2DPuzzleBoard BFS for above board: " << bfs << std::endl;
    }

    int BFS(const std::vector<std::vector<int>> & board)
    {
        //[0,1,2]
        //[3,4,5]
        std::vector<std::vector<int>> dir(
                {
                        {1,3},
                        {0,2,4},
                        {1,5},
                        {0,4},
                        {1,3,5},
                        {2,4}
                });
        std::unordered_set<std::string> visit;
        std::queue<std::pair<std::string,int>> que;//<state,zero idx>
        auto init = ToState(board);
        que.push(init);
        visit.insert(init.first);
        int dist = 0;
        while (!que.empty())
        {
            int levelCount = que.size();
            while (levelCount-->0)
            {
                auto cur = que.front(); que.pop();
                //std::cout << cur.first << "," << cur.second << std::endl;
                if (cur.first == "123450") return dist;
                for (auto nxt : dir[cur.second])
                {
                    std::string state = cur.first;
                    state[cur.second] = state[nxt];
                    state[nxt] = '0';
                    if (!visit.count(state))
                    {
                        visit.insert(state);
                        que.push({state,nxt});
                    }
                }
            }
            ++dist;
        }
        return -1;
    }
private:
    std::pair<std::string,int> ToState(const std::vector<std::vector<int>> & board)
    {
        std::string res;
        int idx;
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 3; ++j)
            {
                res.push_back(board[i][j]+'0');
                if (board[i][j] == 0) idx = i*3+j;
            }
        return {res,idx};
    }
};
/*
[rY][cX]
Row#0	= 3, 2, 4
Row#1	= 1, 5, 0

MinStepsSwap0In2DPuzzleBoard BFS for above board: 14
 */
#endif
