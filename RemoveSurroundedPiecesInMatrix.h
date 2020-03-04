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

    void BFS(std::vector<std::vector<char>> & board, int row, int col)
    {
        Debug::Print2D<char>()(board, false);
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
            std::cout << curR << "," << curC << std::endl;
            if (curR == 0 || curR == N-1 || curC == 0 || curC == M-1)
            {
                surrounded = false;
                break;
            }
            for (int i = 0; i < 4; ++i)
            {
                int nxtR = curR + dir[i][0];
                int nxtC = curC + dir[i][1];
                if (nxtR >= 0 && nxtR < N && nxtC >= 0 && nxtC < M)
                {
                    if (board[nxtR][nxtC] == ' ' ||
                            board[nxtR][nxtC] == piece && (nxtR == 0 || nxtR == N-1 || nxtC == 0 || nxtC == M-1))
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

        std::cout << "RemoveSurroundedPiecesInMatrix for [" << row << "," << col << "]:" << std::endl;
        Debug::Print2D<char>()(board, false);
    }
};
#endif
