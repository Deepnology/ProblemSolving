#ifndef _CANDY_CRUSH_H
#define _CANDY_CRUSH_H
#include "Debug.h"
/*
Leetcode: Candy Crush
This question is about implementing a basic elimination algorithm for Candy Crush.
Given a 2D integer array board representing the grid of candy, different positive integers board[i][j] represent different types of candies.
A value of board[i][j] = 0 represents that the cell at position (i, j) is empty.
The given board represents the state of the game following the player's move.
Now, you need to restore the board to a stable state by crushing candies according to the following rules:

1. If three or more candies of the same type are adjacent vertically or horizontally, "crush" them all at the same time - these positions become empty.
2. After crushing all candies simultaneously, if an empty space on the board has candies on top of itself, then these candies will drop until they hit a candy or bottom at the same time.
(No new candies will drop outside the top boundary.)
3. After the above steps, there may exist more candies that can be crushed.
If so, you need to repeat the above steps.
4. If there does not exist more candies that can be crushed (ie. the board is stable), then return the current board.
You need to perform the above rules until the board becomes stable, then return the current board.
Example:
Input: board =
[[110,5,112,113,114],
 [210,211,5,213,214],
 [310,311,3,313,314],
 [410,411,412,5,414],
 [5,1,512,3,3],
 [610,4,1,613,614],
 [710,1,2,713,714],
 [810,1,2,1,1],
 [1,1,2,2,2],
 [4,1,4,4,1014]]
Output:
[[0,0,0,0,0],
 [0,0,0,0,0],
 [0,0,0,0,0],
 [110,0,0,0,114],
 [210,0,0,0,214],
 [310,0,0,113,314],
 [410,0,0,213,414],
 [610,211,112,313,614],
 [710,311,412,613,714],
 [810,411,512,713,1014]]
 */
class CandyCrush
{
public:
    CandyCrush(){}
    ~CandyCrush(){}

    std::vector<std::vector<int>> Solve(std::vector<std::vector<int>> && board)
    {
        Debug::Print2D<int>()(board, false);

        int N = board.size();
        if (N == 0) return board;
        int M = board[0].size();
        while (true)
        {
            bool found = false;
            for (int i = 0; i < N; ++i)
                for (int j = 0; j < M; ++j)
                {
                    int val = abs(board[i][j]);
                    if (val == 0) continue;
                    if (i+2 < N && abs(board[i+1][j]) == val && abs(board[i+2][j]) == val)
                    {
                        found = true;
                        int ii = i;
                        while (ii < N && abs(board[ii][j]) == val)
                            board[ii++][j] = -val;//mark negative
                    }
                    if (j+2 < M && abs(board[i][j+1]) == val && abs(board[i][j+2]) == val)
                    {
                        found = true;
                        int jj = j;
                        while (jj < M && abs(board[i][jj]) == val)
                            board[i][jj++] = -val;//mark negative
                    }
                }
            if (!found) break;
            for (int j = 0; j < M; ++j)
            {
                //in each col, move positive nums to bottom
                int bottom = N-1;
                for (int i = N-1; i >= 0; --i)
                {
                    if (board[i][j] > 0)
                        board[bottom--][j] = board[i][j];
                }
                while (bottom >= 0)//fill 0s in the remainings of each col
                    board[bottom--][j] = 0;
            }
        }

        std::cout << "CandyCrush for above board:" << std::endl;
        Debug::Print2D<int>()(board, false);
        return board;
    }
};
/*
[rY][cX]
Row#0	= 110, 5, 112, 113, 114
Row#1	= 210, 211, 5, 213, 214
Row#2	= 310, 311, 3, 313, 314
Row#3	= 410, 411, 412, 5, 414
Row#4	= 5, 1, 512, 3, 3
Row#5	= 610, 4, 1, 613, 614
Row#6	= 710, 1, 2, 713, 714
Row#7	= 810, 1, 2, 1, 1
Row#8	= 1, 1, 2, 2, 2
Row#9	= 4, 1, 4, 4, 1014

CandyCrush for above board:
[rY][cX]
Row#0	= 0, 0, 0, 0, 0
Row#1	= 0, 0, 0, 0, 0
Row#2	= 0, 0, 0, 0, 0
Row#3	= 110, 0, 0, 0, 114
Row#4	= 210, 0, 0, 0, 214
Row#5	= 310, 0, 0, 113, 314
Row#6	= 410, 0, 0, 213, 414
Row#7	= 610, 211, 112, 313, 614
Row#8	= 710, 311, 412, 613, 714
Row#9	= 810, 411, 512, 713, 1014
 */
#endif
