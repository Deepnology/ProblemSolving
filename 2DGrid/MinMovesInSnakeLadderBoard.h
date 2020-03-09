#ifndef _MIN_MOVES_IN_SNAKE_LADDER_BOARD_H
#define _MIN_MOVES_IN_SNAKE_LADDER_BOARD_H
#include "Debug.h"
/*
Leetcode: Snakes And Ladders
On an N x N board, the numbers from 1 to N*N are written boustrophedonically starting from the bottom left of the board,
 and alternating direction each row.
For example, for a 6 x 6 board, the numbers are written as follows:
You start on square 1 of the board (which is always in the last row and first column).
Each move, starting from square x, consists of the following:
You choose a destination square S with number x+1, x+2, x+3, x+4, x+5, or x+6, provided this number is <= N*N.
(This choice simulates the result of a standard 6-sided die roll: ie., there are always at most 6 destinations.)
If S has a snake or ladder, you move to the destination of that snake or ladder.  Otherwise, you move to S.
A board square on row r and column c has a "snake or ladder" if board[r][c] != -1.  The destination of that snake or ladder is board[r][c].
Note that you only take a snake or ladder at most once per move:
if the destination to a snake or ladder is the start of another snake or ladder, you do not continue moving.
(For example, if the board is `[[4,-1],[-1,3]]`, and on the first move your destination square is `2`,
 then you finish your first move at `3`, because you do not continue moving to `4`.)
Return the least number of moves required to reach square N*N.  If it is not possible, return -1.
Example 1:
Input: [
[-1,-1,-1,-1,-1,-1],
[-1,-1,-1,-1,-1,-1],
[-1,-1,-1,-1,-1,-1],
[-1,35,-1,-1,13,-1],
[-1,-1,-1,-1,-1,-1],
[-1,15,-1,-1,-1,-1]]
Output: 4
Explanation:
At the beginning, you start at square 1 [at row 5, column 0].
You decide to move to square 2, and must take the ladder to square 15.
You then decide to move to square 17 (row 3, column 5), and must take the snake to square 13.
You then decide to move to square 14, and must take the ladder to square 35.
You then decide to move to square 36, ending the game.
It can be shown that you need at least 4 moves to reach the N*N-th square, so the answer is 4.
 */
class MinMovesInSnakeLadderBoard
{
public:
    MinMovesInSnakeLadderBoard(){}
    ~MinMovesInSnakeLadderBoard(){}

    int toIdx(int r, int c, int N)
    {
        //input row is from top to bottom; input col is from left to right. Now convert to
        //row: count from bottom to top
        //col: even row from bottom to top: count from left to right; otherwise: count from right to left
        return (N-1-r)*N + ((N-1-r)%2==1?N-1-c:c) + 1;
    }
    std::vector<int> toRC(int idx, int N)
    {
        //restore row and col from the above equation
        int r = N-1-((idx-1)/N);
        int c = (N-1-r)%2==1? N-1-(idx-1)%N : (idx-1)%N;
        return {r,c};
    }


    //start: bottom left corner(idx=1); destination: top left or top right corner(idx=N*N)
    //idx of board:
    //36,35,34,33,32,31
    //25,26,27,28,29,30
    //24,23,22,21,20,19
    //13,14,15,16,17,18
    //12,11,10,9,8,7
    //1,2,3,4,5,6
    //-1: non snake nor ladder
    //otherwise: a snake or ladder to the the target idx
    //each move consists of a jump of curIdx+[1:6] and if the destination is a snake or ladder, jump to that destination idx
    int BFS(std::vector<std::vector<int>> && board)
    {
        Debug::Print2D<int>()(board, false);
        std::cout << "MinMovesInSnakeLadderBoard BFS for above board: ";

        int N = board.size();
        std::unordered_set<int> visit;
        std::queue<int> que;
        que.push((N-1)*N+0);//bottom left corner
        visit.insert((N-1)*N+0);//bottom left corner
        int step = 0;
        while (!que.empty())
        {
            int count = que.size();
            while (count-- > 0)
            {
                int curR = que.front() / N;
                int curC = que.front() % N;
                que.pop();
                int curIdx = toIdx(curR, curC, N);
                if (curIdx == N*N)
                {
                    std::cout << step << std::endl;
                    return step;
                }
                for (int i = 1; i <= 6; ++i)
                {
                    int nxtIdx = curIdx + i;
                    if (nxtIdx > N*N) continue;
                    std::vector<int> nxt = toRC(nxtIdx, N);

                    if (!visit.count(nxt[0]*N+nxt[1]))
                    {
                        visit.insert(nxt[0]*N+nxt[1]);
                        if (board[nxt[0]][nxt[1]] == -1)
                            que.push(nxt[0]*N+nxt[1]);
                        else//board[nxt[0]][nxt[1]] is snake or ladder: jump to destination
                        {
                            nxtIdx = board[nxt[0]][nxt[1]];//jump to destination
                            nxt = toRC(nxtIdx, N);
                            que.push(nxt[0]*N+nxt[1]);
                        }
                    }
                }
            }
            ++step;
        }
        std::cout << -1 << std::endl;
        return -1;
    }
};
/*
[rY][cX]
Row#0	= -1, -1, -1, -1, -1, -1
Row#1	= -1, -1, -1, -1, -1, -1
Row#2	= -1, -1, -1, -1, -1, -1
Row#3	= -1, 35, -1, -1, 13, -1
Row#4	= -1, -1, -1, -1, -1, -1
Row#5	= -1, 15, -1, -1, -1, -1

MinMovesInSnakeLadderBoard BFS for above board: 4
 */
#endif
