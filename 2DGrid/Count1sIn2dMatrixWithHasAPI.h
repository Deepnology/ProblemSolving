#ifndef _COUNT_1S_IN_2D_MATRIX_WITH_HAS_API_H
#define _COUNT_1S_IN_2D_MATRIX_WITH_HAS_API_H
#include "Debug.h"
/*
Bloomberg
Given a matrix with only 0 and 1.
Given an API Has1(vector<int>& upperLeft, vector<int>& lowerRight) that returns True if the rectangle in between upperLeft and lowerRight contains 1(s), other returns False.
Write a function to count number of 1s in the matrix using the Has1 API.

              |  |
              |  |
              |  |
--------------+--+--------------
              |  |
--------------+--+--------------
              |  |
              |  |
              |  |

I=============|=I|I============I
I             | I|I            I
I             | I|I            I
I-------------+-I+I------------I
I=============|=I|I============I
--------------+--+--------------
I=============|=I|I============I
I             | I|I            I
I=============|=I|I============I

Leetcode: Number of Ships in a Rectangle
 */
class Count1sIn2dMatrixWithHasAPI //in 2D coordinate where upper left is origin
{
public:
    Count1sIn2dMatrixWithHasAPI(){}
    bool Has1(const std::vector<std::vector<int>> & A, const std::vector<int> & upperLeft, const std::vector<int> & lowerRight)// assume this function is constant time
    {
        int N = A.size();
        if (N == 0) return false;
        int M = A[0].size();
        if (upperLeft[0] < 0 || upperLeft[0] >= N || upperLeft[1] < 0 || upperLeft[1] >= M) return false;
        if (lowerRight[0] < 0 || lowerRight[0] >= N || lowerRight[1] < 0 || lowerRight[1] >= M) return false;
        if (upperLeft[0] > lowerRight[0] || upperLeft[1] > lowerRight[1]) return false;
        for (int i = upperLeft[0]; i <= lowerRight[0]; ++i)
            for (int j = upperLeft[1]; j <= lowerRight[1]; ++j)
                if (A[i][j])
                    return true;
        return false;
    }

    int Count(const std::vector<std::vector<int>> & A)
    {
        int N = A.size();
        if (N == 0) return 0;
        int M = A[0].size();

        int resBinarySearch = BinarySearch(A, 0, N-1, 0, M-1);
        int resBruteForce = BruteForce(A, 0, N-1, 0, M-1);

        Debug::Print2D<int>()(A, false);
        std::cout << "Count1sIn2dMatrixWithHasAPI BinarySearch for above matrix: " << resBinarySearch << ", " << resBruteForce << std::endl;
        return resBinarySearch;
    }

    int BinarySearch(const std::vector<std::vector<int>> & A, int upperRow, int lowerRow, int leftCol, int rightCol)// O(logN * logM) time
    {
        if (upperRow > lowerRow || leftCol > rightCol) return 0;
        if (!Has1(A, {upperRow, leftCol}, {lowerRow, rightCol})) return 0;
        if (upperRow == lowerRow && leftCol == rightCol) return 1;
        int midRow = upperRow + (lowerRow-upperRow) / 2;
        int midCol = leftCol + (rightCol-leftCol) / 2;
        int res = BinarySearch(A, upperRow, midRow, leftCol, midCol) + // upper left quad
                  BinarySearch(A, midRow+1, lowerRow, midCol+1, rightCol) + // lower right quad
                  BinarySearch(A, upperRow, midRow, midCol+1, rightCol) + // upper right quad
                  BinarySearch(A, midRow+1, lowerRow, leftCol, midCol); // lower left quad
        return res;
    }
    int BruteForce(const std::vector<std::vector<int>> & A, int upperRow, int lowerRow, int leftCol, int rightCol)// O(N*M) time
    {
        int res = 0;
        for (int i = upperRow; i <= lowerRow; ++i)
            for (int j = leftCol; j <= rightCol; ++j)
                res += A[i][j];
        return res;
    }
};
class Count1sIn2dMatrixWithHasAPI_2 //in 2D coordinate where lower left is origin (Leetcode)
{
public:
    Count1sIn2dMatrixWithHasAPI_2(){}
private:
    bool Has1(const std::vector<std::vector<int>> & A, const std::vector<int> & topRight, const std::vector<int> & bottomLeft)// assume this function is constant time
    {
        int N = A.size();
        if (N == 0) return false;
        int M = A[0].size();
        if (topRight[0] < 0 || topRight[0] >= M || topRight[1] < 0 || topRight[1] >= N) return false;
        if (bottomLeft[0] < 0 || bottomLeft[0] >= M || bottomLeft[1] < 0 || bottomLeft[1] >= N) return false;
        if (bottomLeft[0] > topRight[0] || bottomLeft[1] < topRight[1]) return false;
        for (int i = bottomLeft[0]; i <= topRight[0]; ++i)
            for (int j = topRight[1]; j <= bottomLeft[1]; ++j)
                if (A[i][j])
                    return true;
        return false;
    }
public:
    int Count(const std::vector<std::vector<int>> & A, std::vector<int> topRight, std::vector<int> bottomLeft)
    {
        return recur(A, topRight, bottomLeft);
    }
private:
    int recur(const std::vector<std::vector<int>> & A, std::vector<int> topR, std::vector<int> bottomL)
    {
        if (topR[0] < bottomL[0] || topR[1] < bottomL[1]) return 0;
        if (!Has1(A, topR, bottomL)) return 0;
        if (topR[0] == bottomL[0] && topR[1] == bottomL[1]) return 1;
        int midX = (topR[0] + bottomL[0]) / 2;
        int midY = (topR[1] + bottomL[1]) / 2;
        return recur(A, topR, {midX+1, midY+1}) //upper right
               + recur(A, {midX, midY}, bottomL) //bottom left
               + recur(A, {midX, topR[1]}, {bottomL[0], midY+1}) //upper left
               + recur(A, {topR[0], midY}, {midX+1, bottomL[1]}); //bottom right
    }

};
/*
[rY][cX]
Row#0	= 1, 1, 1, 0, 0, 0, 1
Row#1	= 1, 0, 0, 1, 0, 0, 1
Row#2	= 0, 1, 0, 0, 1, 0, 0
Row#3	= 0, 1, 0, 0, 1, 0, 1
Row#4	= 0, 1, 1, 0, 0, 1, 0
Row#5	= 1, 0, 1, 1, 1, 0, 0

Count1sIn2dMatrixWithHasAPI BinarySearch for above matrix: 19, 19
[rY][cX]
Row#0	= 0, 1, 0, 0, 1, 0
Row#1	= 0, 1, 0, 0, 1, 0
Row#2	= 1, 1, 1, 0, 1, 1

Count1sIn2dMatrixWithHasAPI BinarySearch for above matrix: 9, 9
[rY][cX]
Row#0	= 0, 1, 0, 1

Count1sIn2dMatrixWithHasAPI BinarySearch for above matrix: 2, 2
[rY][cX]
Row#0	= 1, 1
Row#1	= 0, 0
Row#2	= 0, 0
Row#3	= 1, 0
Row#4	= 1, 1

Count1sIn2dMatrixWithHasAPI BinarySearch for above matrix: 5, 5
[rY][cX]
Row#0	= 1, 0, 1, 1, 0, 1, 0
Row#1	= 0, 0, 1, 1, 0, 0, 0
Row#2	= 0, 1, 0, 0, 0, 0, 1

Count1sIn2dMatrixWithHasAPI BinarySearch for above matrix: 8, 8
[rY][cX]
Row#0	= 1, 1, 0, 0, 1, 1
Row#1	= 1, 1, 1, 1, 0, 1
Row#2	= 1, 1, 0, 1, 1, 0

Count1sIn2dMatrixWithHasAPI BinarySearch for above matrix: 13, 13
[rY][cX]
Row#0	= 1, 0, 1, 0
Row#1	= 0, 1, 1, 1
Row#2	= 0, 0, 1, 1
Row#3	= 1, 0, 0, 1
Row#4	= 1, 1, 1, 1

Count1sIn2dMatrixWithHasAPI BinarySearch for above matrix: 13, 13
[rY][cX]
Row#0	= 0, 0
Row#1	= 0, 0

Count1sIn2dMatrixWithHasAPI BinarySearch for above matrix: 0, 0
[rY][cX]
Row#0	= 0, 0, 0
Row#1	= 0, 1, 1
Row#2	= 1, 0, 1
Row#3	= 0, 0, 0
Row#4	= 1, 1, 0
Row#5	= 0, 1, 0
Row#6	= 1, 0, 0

Count1sIn2dMatrixWithHasAPI BinarySearch for above matrix: 8, 8
[rY][cX]
Row#0	= 1
Row#1	= 1
Row#2	= 1

Count1sIn2dMatrixWithHasAPI BinarySearch for above matrix: 3, 3
[rY][cX]
Row#0	= 0, 1

Count1sIn2dMatrixWithHasAPI BinarySearch for above matrix: 1, 1
 */
#endif
