#ifndef _REMOVE_SURROUNDED_PIECES_IN_MATRIX_H
#define _REMOVE_SURROUNDED_PIECES_IN_MATRIX_H
#include "Debug.h"
/*
Uber
Given a white piece location in matrix, remove all white pieces that are surrounded by black pieces.
 */
class RemoveSurroundedPiecesInMatrix
{
public:
    RemoveSurroundedPiecesInMatrix(){}

    void BFS(std::vector<std::vector<char>> & board)
    {
        Debug::Print2D<char>()(board, false);
        int N = board.size();
        int M = board[0].size();
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
            {
                if (board[i][j] == 'O')
                    BFS(board, i, j);
            }
        std::cout << "RemoveSurroundedPiecesInMatrix for above grid:" << std::endl;
        Debug::Print2D<char>()(board, false);
    }

    void BFS(std::vector<std::vector<char>> & board, int row, int col)
    {
        char piece = board[row][col];
        if (piece == ' ') return;
        int N = board.size();
        int M = board[0].size();
        std::vector<std::vector<int>> dir({{-1,0},{1,0},{0,1},{0,-1}});
        bool surrounded = true;
        std::unordered_set<int> visit;
        std::queue<int> que;
        que.push(row * M + col);
        visit.insert(row * M + col);
        while (!que.empty())
        {
            int curR = que.front() / M;
            int curC = que.front() % M;
            que.pop();
            for (int i = 0; i < 4; ++i)
            {
                int nxtR = curR + dir[i][0];
                int nxtC = curC + dir[i][1];
                if (nxtR >= 0 && nxtR < N && nxtC >= 0 && nxtC < M)
                {
                    if (board[nxtR][nxtC] == ' ')
                    {
                        surrounded = false;
                        break;
                    }
                    if (board[nxtR][nxtC] == piece && !visit.count(nxtR * M + nxtC))//only BFS on same color pieces
                    {
                        visit.insert(nxtR * M + nxtC);
                        que.push(nxtR * M + nxtC);
                    }
                }
            }
            if (!surrounded) break;
        }
        if (surrounded)
        {
            for (auto & i : visit)
                board[i / M][i % M] = ' ';
        }
    }
};
/*
[rY][cX]
Row#0	=  , X, X, O, O
Row#1	= X, O, O, X, X
Row#2	= O, X, O, O, X
Row#3	= X, X, X, X, O
Row#4	= X, X, X, O, X
Row#5	=  , O,  , X,

RemoveSurroundedPiecesInMatrix for above grid:
[rY][cX]
Row#0	=  , X, X,  ,
Row#1	= X,  ,  , X, X
Row#2	=  , X,  ,  , X
Row#3	= X, X, X, X,
Row#4	= X, X, X,  , X
Row#5	=  , O,  , X,
 */
#endif
