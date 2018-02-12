#ifndef _COUNT_SQUARES_IN_2D_GRID_H
#define _COUNT_SQUARES_IN_2D_GRID_H
#include "Debug.h"
/*

 */
class CountSquaresIn2DGrid
{
public:
    CountSquaresIn2DGrid(){}

    int BruteForce(int N)
    {
        int res = 0;
        for (int len = 1; len <= N; ++len)//enumerate all lengths
            for (int row = 0; row + len - 1 < N; ++row)//enumerate all row begin indices
                for (int col = 0; col + len - 1 < N; ++col)//enumerate all col begin indices
                    ++res;

        std::cout << "CountSquaresIn2DGrid BruteForce for N=" << N << ": " << res << std::endl;
        return res;
    }
    int LinearTime(int N)
    {
        int res = 0;
        for (int len = 1; len <= N; ++len)
            res += len * len;

        std::cout << "CountSquaresIn2DGrid LinearTime for N=" << N << ": " << res << std::endl;
        return res;
    }
};
/*
CountSquaresIn2DGrid BruteForce for N=1: 1
CountSquaresIn2DGrid LinearTime for N=1: 1
CountSquaresIn2DGrid BruteForce for N=2: 5
CountSquaresIn2DGrid LinearTime for N=2: 5
CountSquaresIn2DGrid BruteForce for N=3: 14
CountSquaresIn2DGrid LinearTime for N=3: 14
CountSquaresIn2DGrid BruteForce for N=4: 30
CountSquaresIn2DGrid LinearTime for N=4: 30
CountSquaresIn2DGrid BruteForce for N=5: 55
CountSquaresIn2DGrid LinearTime for N=5: 55
CountSquaresIn2DGrid BruteForce for N=6: 91
CountSquaresIn2DGrid LinearTime for N=6: 91
CountSquaresIn2DGrid BruteForce for N=7: 140
CountSquaresIn2DGrid LinearTime for N=7: 140
CountSquaresIn2DGrid BruteForce for N=8: 204
CountSquaresIn2DGrid LinearTime for N=8: 204
 */
#endif
