#ifndef	RANGE_SUM_QUERY_SEGMENT_TREE_2D_H
#define RANGE_SUM_QUERY_SEGMENT_TREE_2D_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include "Debug.h"
/*
Leetcode: Range Sum Query 2D - Mutable
Given a 2D integer matrix, find the sum of the elements inside the rectangle defined by its upper left corner (row1, col1) and lower right corner (row2, col2). The integers in matrix can be modified.
Given matrix = [
[3, 0, 1, 4, 2],
[5, 6, 3, 2, 1],
[1, 2, 0, 1, 5],
[4, 1, 0, 1, 7],
[1, 0, 3, 0, 5]
]
sumRegion(2, 1, 4, 3) -> 8
update(3, 2, 2)
sumRegion(2, 1, 4, 3) -> 10
Note:
The matrix is only modifiable by the update function.
You may assume the number of calls to update and sumRegion function is distributed evenly.
Hide Tags Segment Tree Binary Indexed Tree
Hide Similar Problems (M) Range Sum Query 2D - Immutable (M) Range Sum Query - Mutable

rowRecur: keep track of topRowY and bottomRowY of matrix, keep track of rowY (topChild=rowY*2+1, bottomChild=rowY*2+2) of segmentTree
colRecur: keep fixed rowY, topRowY, bottomRowY from rowRecur. keep track of leftColX and rightColX of matrix, keep track of colX (leftChild=colX*2+1, rightChild=colX*2+2) of segmentTree
when seeing a leaf (topRowY==bottomRowY && leftColX==rightColX), return segmentTree[rowY][colX]=matrix[topRowY][leftColX]
otherwise, it must be a parent node with 2 leaves, return segmentTree[rowY][colX]=topChildSum+bottomChildSum or segmentTree[rowY][colX]=leftChildSum+rightChildSum
*/
class RangeSumQuerySegmentTree2D
{
	std::vector<std::vector<int>> segmentTree;
	int N; // number of rows of input matrix
	int M; // number of cols of input matrix
	//matrix's variable names: topRowY, bottomRowY, leftColX, rightColX, tgtTopRowY, tgtBottomRowY, tgtLeftColX, tgtRightColX
	//segmentTree's variable names: colX, rowY
public:
	//1. Construct (preprocess): O(n*m) time
	explicit RangeSumQuerySegmentTree2D(const std::vector<std::vector<int>> & matrix)
	{
		N = matrix.size();
		M = matrix[0].size();
		int treeHeightRow = (int)ceil(log2(N)) + 1;
		int NN = (int)pow(2, treeHeightRow) - 1; //segmentTree row max size
		int treeHeightCol = (int)ceil(log2(M)) + 1;
		int MM = (int)pow(2, treeHeightCol) - 1; //segmentTree col max size
		segmentTree.resize(NN, std::vector<int>(MM, 0));

		this->rowYRecur(matrix, 0, N - 1, 0);

		Debug::Print2D<int>()(matrix, false);
		std::cout << "RangeSumQuerySegmentTree2D segmentTree for above matrix:" << std::endl;
		Debug::Print2D<int>()(segmentTree, false);
	}
	~RangeSumQuerySegmentTree2D() {}
private:
	void rowYRecur(const std::vector<std::vector<int>> & matrix, int topRowY, int bottomRowY, //matrix var
		int rowY) //segmentTree var
	{
		if (topRowY != bottomRowY)
		{
			int midRowY = topRowY + (bottomRowY - topRowY) / 2;
			this->rowYRecur(matrix, topRowY, midRowY, rowY * 2 + 1);
			this->rowYRecur(matrix, midRowY + 1, bottomRowY, rowY * 2 + 2);
		}
		int M = matrix[0].size();
		this->colXRecur(rowY, topRowY, bottomRowY, matrix, 0, M - 1, 0);
	}
	void colXRecur(int rowY, int topRowY, int bottomRowY, // fixed row var
		const std::vector<std::vector<int>> & matrix, int leftColX, int rightColX, //matrix var
		int colX) //segmentTree var
	{
		if (leftColX == rightColX)
		{
			if (topRowY == bottomRowY)
				segmentTree[rowY][colX] = matrix[topRowY][leftColX]; //leaf
			else
				segmentTree[rowY][colX] = segmentTree[rowY * 2 + 1][colX] + segmentTree[rowY * 2 + 2][colX]; //topChild + bottomChild
		}
		else
		{
			int midColX = leftColX + (rightColX - leftColX) / 2;
			this->colXRecur(rowY, topRowY, bottomRowY, matrix, leftColX, midColX, colX * 2 + 1);
			this->colXRecur(rowY, topRowY, bottomRowY, matrix, midColX + 1, rightColX, colX * 2 + 2);
			segmentTree[rowY][colX] = segmentTree[rowY][colX * 2 + 1] + segmentTree[rowY][colX * 2 + 2]; //leftChild + rightChild
		}
	}

public:
	//2. Query range: O(logn * logm) time
	int QueryRange(int tgtTopRowY, int tgtBottomRowY, int tgtLeftColX, int tgtRightColX)
	{
		int sum = this->queryRowYRecur(0, 0, N - 1, tgtTopRowY, tgtBottomRowY, tgtLeftColX, tgtRightColX);

		std::cout << "RangeSumQuerySegmentTree2D QueryRange for \"(" << tgtTopRowY << "," << tgtLeftColX << "),(" << tgtBottomRowY << "," << tgtRightColX << ")\": " << sum << std::endl;
		return sum;
	}
private:
	int queryRowYRecur(int rowY, //segmentTree var
		int topRowY, int bottomRowY, //matrix var
		int tgtTopRowY, int tgtBottomRowY, int tgtLeftColX, int tgtRightColX) //fixed matrix var
	{
		if (tgtTopRowY > bottomRowY || tgtBottomRowY < topRowY)
			return 0;

		if (tgtTopRowY <= topRowY && tgtBottomRowY >= bottomRowY)
			return this->queryColXRecur(rowY, 0, 0, M - 1, tgtLeftColX, tgtRightColX);

		int midRowY = topRowY + (bottomRowY - topRowY) / 2;
		int topSum = this->queryRowYRecur(rowY * 2 + 1, topRowY, midRowY, tgtTopRowY, tgtBottomRowY, tgtLeftColX, tgtRightColX);
		int bottomSum = this->queryRowYRecur(rowY * 2 + 2, midRowY + 1, bottomRowY, tgtTopRowY, tgtBottomRowY, tgtLeftColX, tgtRightColX);
		return topSum + bottomSum;
	}
	int queryColXRecur(int rowY, //fixed segmentTree var
		int colX, //segmentTree var
		int leftColX, int rightColX, //matrix var
		int tgtLeftColX, int tgtRightColX) //fixed matrix var
	{
		if (tgtLeftColX > rightColX || tgtRightColX < leftColX)
			return 0;

		if (tgtLeftColX <= leftColX && tgtRightColX >= rightColX)
			return segmentTree[rowY][colX]; //leaf

		int midColX = leftColX + (rightColX - leftColX) / 2;
		int leftSum = this->queryColXRecur(rowY, colX * 2 + 1, leftColX, midColX, tgtLeftColX, tgtRightColX);
		int rightSum = this->queryColXRecur(rowY, colX * 2 + 2, midColX + 1, rightColX, tgtLeftColX, tgtRightColX);
		return leftSum + rightSum; //leftChild + rightChild
	}

public:
	//3. Update value: O(logn * logm) time
	void UpdateValue(int tgtRowY, int tgtColX, int tgtVal)
	{
		this->updateRowYRecur(0, 0, N - 1, tgtRowY, tgtColX, tgtVal);

		std::cout << "RangeSumQuerySegmentTree2D UpdateValue for (rowY,colX),val = \"(" << tgtRowY << "," << tgtColX << ")," << tgtVal << "\": " << std::endl;
		Debug::Print2D<int>()(segmentTree, false);
	}
private:
	void updateRowYRecur(int rowY, //segmentTree var
		int topRowY, int bottomRowY, //matrix var
		int tgtRowY, int tgtColX, int tgtVal) //fixed matrix var
	{
		if (topRowY != bottomRowY)
		{
			int midRowY = topRowY + (bottomRowY - topRowY) / 2;
			if (tgtRowY <= midRowY)
				this->updateRowYRecur(rowY * 2 + 1, topRowY, midRowY, tgtRowY, tgtColX, tgtVal);
			else
				this->updateRowYRecur(rowY * 2 + 2, midRowY + 1, bottomRowY, tgtRowY, tgtColX, tgtVal);
		}

		this->updateColXRecur(rowY, topRowY, bottomRowY, 0, 0, M - 1, tgtRowY, tgtColX, tgtVal);
	}
	void updateColXRecur(int rowY, int topRowY, int bottomRowY, //fixed segmentTree & matrix row var
		int colX, //segmentTree var
		int leftColX, int rightColX, //matrix var
		int tgtRowY, int tgtColX, int tgtVal) //fixed matrix var
	{
		if (leftColX == rightColX)
		{
			if (topRowY == bottomRowY)
				segmentTree[rowY][colX] = tgtVal; //leaf
			else
				segmentTree[rowY][colX] = segmentTree[rowY * 2 + 1][colX] + segmentTree[rowY * 2 + 2][colX]; //topChild + bottomChild
		}
		else
		{
			int midColX = leftColX + (rightColX - leftColX) / 2;
			if (tgtColX <= midColX)
				this->updateColXRecur(rowY, topRowY, bottomRowY, colX * 2 + 1, leftColX, midColX, tgtRowY, tgtColX, tgtVal);
			else
				this->updateColXRecur(rowY, topRowY, bottomRowY, colX * 2 + 2, midColX + 1, rightColX, tgtRowY, tgtColX, tgtVal);
			segmentTree[rowY][colX] = segmentTree[rowY][colX * 2 + 1] + segmentTree[rowY][colX * 2 + 2]; //leftChild + rightChild
		}
	}
};
/*
[rY][cX]
Row#0	= 3, 0, 1, 4, 2
Row#1	= 5, 6, 3, 2, 1
Row#2	= 1, 2, 0, 1, 5
Row#3	= 4, 1, 0, 1, 7
Row#4	= 1, 0, 3, 0, 5

RangeSumQuerySegmentTree2D segmentTree for above matrix:
[rY][cX]
Row#0	= 58, 30, 28, 23, 7, 8, 20, 14, 9, 0, 0, 0, 0, 0, 0
Row#1	= 36, 21, 15, 17, 4, 7, 8, 9, 8, 0, 0, 0, 0, 0, 0
Row#2	= 22, 9, 13, 6, 3, 1, 12, 5, 1, 0, 0, 0, 0, 0, 0
Row#3	= 27, 18, 9, 14, 4, 6, 3, 8, 6, 0, 0, 0, 0, 0, 0
Row#4	= 9, 3, 6, 3, 0, 1, 5, 1, 2, 0, 0, 0, 0, 0, 0
Row#5	= 13, 5, 8, 5, 0, 1, 7, 4, 1, 0, 0, 0, 0, 0, 0
Row#6	= 9, 4, 5, 1, 3, 0, 5, 1, 0, 0, 0, 0, 0, 0, 0
Row#7	= 10, 4, 6, 3, 1, 4, 2, 3, 0, 0, 0, 0, 0, 0, 0
Row#8	= 17, 14, 3, 11, 3, 2, 1, 5, 6, 0, 0, 0, 0, 0, 0
Row#9	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#10	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#11	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#12	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#13	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#14	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

RangeSumQuerySegmentTree2D QueryRange for "(2,1),(4,3)": 8
RangeSumQuerySegmentTree2D UpdateValue for (rowY,colX),val = "(3,2),2":
[rY][cX]
Row#0	= 60, 32, 28, 23, 9, 8, 20, 14, 9, 0, 0, 0, 0, 0, 0
Row#1	= 36, 21, 15, 17, 4, 7, 8, 9, 8, 0, 0, 0, 0, 0, 0
Row#2	= 24, 11, 13, 6, 5, 1, 12, 5, 1, 0, 0, 0, 0, 0, 0
Row#3	= 27, 18, 9, 14, 4, 6, 3, 8, 6, 0, 0, 0, 0, 0, 0
Row#4	= 9, 3, 6, 3, 0, 1, 5, 1, 2, 0, 0, 0, 0, 0, 0
Row#5	= 15, 7, 8, 5, 2, 1, 7, 4, 1, 0, 0, 0, 0, 0, 0
Row#6	= 9, 4, 5, 1, 3, 0, 5, 1, 0, 0, 0, 0, 0, 0, 0
Row#7	= 10, 4, 6, 3, 1, 4, 2, 3, 0, 0, 0, 0, 0, 0, 0
Row#8	= 17, 14, 3, 11, 3, 2, 1, 5, 6, 0, 0, 0, 0, 0, 0
Row#9	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#10	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#11	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#12	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#13	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#14	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

RangeSumQuerySegmentTree2D QueryRange for "(2,1),(4,3)": 10
RangeSumQuerySegmentTree2D UpdateValue for (rowY,colX),val = "(2,3),7":
[rY][cX]
Row#0	= 66, 32, 34, 23, 9, 14, 20, 14, 9, 0, 0, 0, 0, 0, 0
Row#1	= 42, 21, 21, 17, 4, 13, 8, 9, 8, 0, 0, 0, 0, 0, 0
Row#2	= 24, 11, 13, 6, 5, 1, 12, 5, 1, 0, 0, 0, 0, 0, 0
Row#3	= 27, 18, 9, 14, 4, 6, 3, 8, 6, 0, 0, 0, 0, 0, 0
Row#4	= 15, 3, 12, 3, 0, 7, 5, 1, 2, 0, 0, 0, 0, 0, 0
Row#5	= 15, 7, 8, 5, 2, 1, 7, 4, 1, 0, 0, 0, 0, 0, 0
Row#6	= 9, 4, 5, 1, 3, 0, 5, 1, 0, 0, 0, 0, 0, 0, 0
Row#7	= 10, 4, 6, 3, 1, 4, 2, 3, 0, 0, 0, 0, 0, 0, 0
Row#8	= 17, 14, 3, 11, 3, 2, 1, 5, 6, 0, 0, 0, 0, 0, 0
Row#9	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#10	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#11	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#12	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#13	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#14	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

RangeSumQuerySegmentTree2D QueryRange for "(2,1),(4,3)": 16
*/
#endif
