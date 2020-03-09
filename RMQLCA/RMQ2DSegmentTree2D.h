#ifndef	RMQ_2D_SEGMENT_TREE_2D_H
#define RMQ_2D_SEGMENT_TREE_2D_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include "Debug.h"
/*
http://apps.topcoder.com/forums/;jsessionid=36D7C3AF2DB0E8FB9F42AD6A8FB039C2?module=Thread&threadID=814836&start=0&mc=4#1862528
http://e-maxx.ru/algo/segment_tree
http://www.careercup.com/question?id=5746897784406016

modified from RangeMinQuerySegmentTree.h

Given a 2D array of integers, we want to query a range minimum of a sub-rectangle.
Perform 2D divide and conquer to construct a 2D segment tree and query/update a range minimum
rowY and colX: index used in segment tree 2D array (always starting from 0 which is the root)
topRowY, bottomRowY, leftColX, and rightColX: index used in input 2D array (always starting from 0, N-1, 0, M-1)

See also Search2dSortedMatrix.h
See RangeSumQuerySegmentTree2D.h for easier understanding
*/
class RMQ2DSegmentTree2D
{
public:
	RMQ2DSegmentTree2D(){}
	~RMQ2DSegmentTree2D(){}

	//1. Construct (preprocess): O(n*m) time
	std::vector<std::vector<int> > Construct(const std::vector<std::vector<int> > & A)
	{
		int N = A.size();
		int M = A[0].size();
		
		int treeHeightRowY = (int)ceil(log2(N)) + 1;//treeHeight = ceil(log2(N)) + 1
		int treeMaxSizeRowY = (int)pow(2, treeHeightRowY) - 1;//treeMaxSize = 2^treeHeight - 1

		int treeHeightColX = (int)ceil(log2(M)) + 1;//treeHeight = ceil(log2(M)) + 1
		int treeMaxSizeColX = (int)pow(2, treeHeightColX) - 1;//treeMaxSize = 2^treeHeight - 1

		std::vector<std::vector<int> > segmentTree(treeMaxSizeRowY, std::vector<int>(treeMaxSizeColX));
		this->rowYRecur(A, 0, N - 1, segmentTree, 0);

		Debug::Print2D<int>()(A, false);
		std::cout << "RMQ2DSegmentTree2D Construct for the above 2D board:" << std::endl;
		Debug::Print2D<int>()(segmentTree, false);
		return segmentTree;
	}
private:
	void rowYRecur(const std::vector<std::vector<int> > & A, int topRowY, int bottomRowY, //matrix var
		std::vector<std::vector<int> > & segmentTree, int rowY) //segmentTree var
	{
		if (topRowY != bottomRowY)
		{
			int midRowY = topRowY + (bottomRowY - topRowY) / 2;
			this->rowYRecur(A, topRowY, midRowY, segmentTree, rowY * 2 + 1);
			this->rowYRecur(A, midRowY + 1, bottomRowY, segmentTree, rowY * 2 + 2);
		}
		int M = A[0].size();
		this->colXRecur(rowY, topRowY, bottomRowY, A, 0, M - 1, segmentTree, 0);
	}
	void colXRecur(const int & rowY, const int & topRowY, const int & bottomRowY, //fixed segmentTree and matrix row var
		const std::vector<std::vector<int> > & A, int leftColX, int rightColX, //matrix var
		std::vector<std::vector<int> > & segmentTree, int colX) //segmentTree var
	{
		if (leftColX == rightColX)
		{
			if (topRowY == bottomRowY)
				segmentTree[rowY][colX] = A[topRowY][leftColX];
			else
				segmentTree[rowY][colX] = std::min(segmentTree[rowY * 2 + 1][colX], segmentTree[rowY * 2 + 2][colX]);
		}
		else
		{
			int midColX = leftColX + (rightColX - leftColX) / 2;
			this->colXRecur(rowY, topRowY, bottomRowY, A, leftColX, midColX, segmentTree, colX * 2 + 1);
			this->colXRecur(rowY, topRowY, bottomRowY, A, midColX + 1, rightColX, segmentTree, colX * 2 + 2);
			segmentTree[rowY][colX] = std::min(segmentTree[rowY][colX * 2 + 1], segmentTree[rowY][colX * 2 + 2]);
		}
	}


	//2. Query range: O(logn * logm) time
public:
	int QueryRange(const std::vector<std::vector<int> > & segmentTree,
		int tgtTopRowY, int tgtBottomRowY, int rowYCount, int tgtLeftColX, int tgtRightColX, int colXCount)
	{
		int min = this->queryRowYRecur(segmentTree, 0, 0, rowYCount - 1, colXCount, tgtTopRowY, tgtBottomRowY, tgtLeftColX, tgtRightColX);
		
		std::cout << "RMQ2DSegmentTree2D QueryRange for \"(" << tgtTopRowY << "," << tgtLeftColX << "),(" << tgtBottomRowY << "," << tgtRightColX << ")\": " << min << std::endl;
		return min;
	}
private:
	int queryRowYRecur(const std::vector<std::vector<int> > & segmentTree, int rowY, //segmentTree var
		int topRowY, int bottomRowY, //matrix var
		const int & colXCount, const int & tgtTopRowY, const int & tgtBottomRowY, const int & tgtLeftColX, const int & tgtRightColX) //fixed matrix var
	{
		if (tgtTopRowY > bottomRowY || tgtBottomRowY < topRowY)
			return INT_MAX;
		
		if (tgtTopRowY <= topRowY && tgtBottomRowY >= bottomRowY)
			return this->queryColXRecur(rowY, segmentTree, 
			0, 0, colXCount - 1, 
			tgtLeftColX, tgtRightColX);

		int midRowY = topRowY + (bottomRowY - topRowY) / 2;
		int topMin = this->queryRowYRecur(segmentTree, rowY * 2 + 1, topRowY, midRowY, colXCount, tgtTopRowY, tgtBottomRowY, tgtLeftColX, tgtRightColX);
		int bottomMin = this->queryRowYRecur(segmentTree, rowY * 2 + 2, midRowY + 1, bottomRowY, colXCount, tgtTopRowY, tgtBottomRowY, tgtLeftColX, tgtRightColX);
		return std::min(topMin, bottomMin);
	}
	int queryColXRecur(const int & rowY, //fixed segmentTree row var
		const std::vector<std::vector<int> > & segmentTree, int colX, //segmentTree var
		int leftColX, int rightColX, //matrix var
		const int & tgtLeftColX, const int & tgtRightColX) //fixed matrix var
	{
		if (tgtLeftColX > rightColX || tgtRightColX < leftColX)
			return INT_MAX;

		if (tgtLeftColX <= leftColX && tgtRightColX >= rightColX)
			return segmentTree[rowY][colX];

		int midColX = leftColX + (rightColX - leftColX) / 2;
		int leftMin = this->queryColXRecur(rowY, segmentTree, colX * 2 + 1, leftColX, midColX, tgtLeftColX, tgtRightColX);
		int rightMin = this->queryColXRecur(rowY, segmentTree, colX * 2 + 2, midColX + 1, rightColX, tgtLeftColX, tgtRightColX);
		return std::min(leftMin, rightMin);
	}



	//3. Update value: O(logn * logm) time
public:
	void UpdateValue(std::vector<std::vector<int> > & A, int tgtRowY, int tgtColX, int tgtVal, std::vector<std::vector<int> > & segmentTree)
	{
		A[tgtRowY][tgtColX] = tgtVal;
		int N = A.size();
		int M = A[0].size();
		this->updateRowYRecur(segmentTree, 0, 0, N - 1, M, tgtRowY, tgtColX, tgtVal);
		std::cout << "RMQ2DSegmentTree2D UpdateValue for (rowY,colX),val = \"(" << tgtRowY << "," << tgtColX << ")," << tgtVal << "\": " << std::endl;
		Debug::Print2D<int>()(segmentTree, false);
	}
private:
	void updateRowYRecur(std::vector<std::vector<int> > & segmentTree, int rowY, //segmentTree var
		int topRowY, int bottomRowY, //matrix var
		const int & colXCount, const int & tgtRowY, const int & tgtColX, const int & tgtVal) //fixed matrix var
	{
		if (topRowY != bottomRowY)
		{
			int midRowY = topRowY + (bottomRowY - topRowY) / 2;
			if (tgtRowY <= midRowY)
				this->updateRowYRecur(segmentTree, rowY * 2 + 1, topRowY, midRowY, colXCount, tgtRowY, tgtColX, tgtVal);
			else
				this->updateRowYRecur(segmentTree, rowY * 2 + 2, midRowY + 1, bottomRowY, colXCount, tgtRowY, tgtColX, tgtVal);
		}
		
		this->updateColXRecur(rowY, topRowY, bottomRowY, segmentTree, 0, 0, colXCount - 1, tgtRowY, tgtColX, tgtVal);
	}
	void updateColXRecur(const int & rowY, const int & topRowY, const int & bottomRowY, //fixed row var
		std::vector<std::vector<int> > & segmentTree, int colX, //segmentTree var
		int leftColX, int rightColX, //matrix var
		const int & tgtRowY, const int & tgtColX, const int & tgtVal) //fixed matrix var
	{
		if (leftColX == rightColX)
		{
			if (topRowY == bottomRowY)
				segmentTree[rowY][colX] = tgtVal;
			else
				segmentTree[rowY][colX] = std::min(segmentTree[rowY * 2 + 1][colX], segmentTree[rowY * 2 + 2][colX]);
		}
		else
		{
			int midColX = leftColX + (rightColX - leftColX) / 2;
			if (tgtColX <= midColX)
				this->updateColXRecur(rowY, topRowY, bottomRowY, segmentTree, colX * 2 + 1, leftColX, midColX, tgtRowY, tgtColX, tgtVal);
			else
				this->updateColXRecur(rowY, topRowY, bottomRowY, segmentTree, colX * 2 + 2, midColX + 1, rightColX, tgtRowY, tgtColX, tgtVal);
			segmentTree[rowY][colX] = std::min(segmentTree[rowY][colX * 2 + 1], segmentTree[rowY][colX * 2 + 2]);
		}
	}
};
/*
[rY][cX]
Row#0	= 23, 18, 7, 45, 42, 26
Row#1	= 37, 22, 32, 24, 25, 38
Row#2	= 3, 32, 12, 7, 31, 27
Row#3	= 2, 24, 51, 23, 21, 5
Row#4	= 78, 14, 23, 12, 13, 9
Row#5	= 45, 19, 21, 6, 18, 4
Row#6	= 24, 16, 36, 1, 33, 17
Row#7	= 15, 21, 8, 34, 55, 28

RMQ2DSegmentTree2D Construct for the above 2D board:
[rY][cX]
Row#0	= 1, 2, 1, 2, 7, 1, 4, 2, 14, 0, 0, 1, 13, 0, 0
Row#1	= 2, 2, 5, 2, 7, 7, 5, 2, 18, 0, 0, 7, 21, 0, 0
Row#2	= 1, 8, 1, 14, 8, 1, 4, 15, 14, 0, 0, 1, 13, 0, 0
Row#3	= 7, 7, 24, 18, 7, 24, 26, 23, 18, 0, 0, 24, 25, 0, 0
Row#4	= 2, 2, 5, 2, 12, 7, 5, 2, 24, 0, 0, 7, 21, 0, 0
Row#5	= 4, 14, 4, 14, 21, 6, 4, 45, 14, 0, 0, 6, 13, 0, 0
Row#6	= 1, 8, 1, 15, 8, 1, 17, 15, 16, 0, 0, 1, 33, 0, 0
Row#7	= 7, 7, 26, 18, 7, 42, 26, 23, 18, 0, 0, 45, 42, 0, 0
Row#8	= 22, 22, 24, 22, 32, 24, 38, 37, 22, 0, 0, 24, 25, 0, 0
Row#9	= 3, 3, 7, 3, 12, 7, 27, 3, 32, 0, 0, 7, 31, 0, 0
Row#10	= 2, 2, 5, 2, 51, 21, 5, 2, 24, 0, 0, 23, 21, 0, 0
Row#11	= 9, 14, 9, 14, 23, 12, 9, 78, 14, 0, 0, 12, 13, 0, 0
Row#12	= 4, 19, 4, 19, 21, 6, 4, 45, 19, 0, 0, 6, 18, 0, 0
Row#13	= 1, 16, 1, 16, 36, 1, 17, 24, 16, 0, 0, 1, 33, 0, 0
Row#14	= 8, 8, 28, 15, 8, 34, 28, 15, 21, 0, 0, 34, 55, 0, 0

RMQ2DSegmentTree2D QueryRange for "(0,0),(7,5)": 1
RMQ2DSegmentTree2D QueryRange for "(4,0),(7,2)": 8
RMQ2DSegmentTree2D QueryRange for "(0,1),(5,5)": 4
RMQ2DSegmentTree2D UpdateValue for (rowY,colX),val = "(6,3),-9":
[rY][cX]
Row#0	= -9, 2, -9, 2, 7, -9, 4, 2, 14, 0, 0, -9, 13, 0, 0
Row#1	= 2, 2, 5, 2, 7, 7, 5, 2, 18, 0, 0, 7, 21, 0, 0
Row#2	= -9, 8, -9, 14, 8, -9, 4, 15, 14, 0, 0, -9, 13, 0, 0
Row#3	= 7, 7, 24, 18, 7, 24, 26, 23, 18, 0, 0, 24, 25, 0, 0
Row#4	= 2, 2, 5, 2, 12, 7, 5, 2, 24, 0, 0, 7, 21, 0, 0
Row#5	= 4, 14, 4, 14, 21, 6, 4, 45, 14, 0, 0, 6, 13, 0, 0
Row#6	= -9, 8, -9, 15, 8, -9, 17, 15, 16, 0, 0, -9, 33, 0, 0
Row#7	= 7, 7, 26, 18, 7, 42, 26, 23, 18, 0, 0, 45, 42, 0, 0
Row#8	= 22, 22, 24, 22, 32, 24, 38, 37, 22, 0, 0, 24, 25, 0, 0
Row#9	= 3, 3, 7, 3, 12, 7, 27, 3, 32, 0, 0, 7, 31, 0, 0
Row#10	= 2, 2, 5, 2, 51, 21, 5, 2, 24, 0, 0, 23, 21, 0, 0
Row#11	= 9, 14, 9, 14, 23, 12, 9, 78, 14, 0, 0, 12, 13, 0, 0
Row#12	= 4, 19, 4, 19, 21, 6, 4, 45, 19, 0, 0, 6, 18, 0, 0
Row#13	= -9, 16, -9, 16, 36, -9, 17, 24, 16, 0, 0, -9, 33, 0, 0
Row#14	= 8, 8, 28, 15, 8, 34, 28, 15, 21, 0, 0, 34, 55, 0, 0

RMQ2DSegmentTree2D UpdateValue for (rowY,colX),val = "(7,2),-5":
[rY][cX]
Row#0	= -9, -5, -9, 2, -5, -9, 4, 2, 14, 0, 0, -9, 13, 0, 0
Row#1	= 2, 2, 5, 2, 7, 7, 5, 2, 18, 0, 0, 7, 21, 0, 0
Row#2	= -9, -5, -9, 14, -5, -9, 4, 15, 14, 0, 0, -9, 13, 0, 0
Row#3	= 7, 7, 24, 18, 7, 24, 26, 23, 18, 0, 0, 24, 25, 0, 0
Row#4	= 2, 2, 5, 2, 12, 7, 5, 2, 24, 0, 0, 7, 21, 0, 0
Row#5	= 4, 14, 4, 14, 21, 6, 4, 45, 14, 0, 0, 6, 13, 0, 0
Row#6	= -9, -5, -9, 15, -5, -9, 17, 15, 16, 0, 0, -9, 33, 0, 0
Row#7	= 7, 7, 26, 18, 7, 42, 26, 23, 18, 0, 0, 45, 42, 0, 0
Row#8	= 22, 22, 24, 22, 32, 24, 38, 37, 22, 0, 0, 24, 25, 0, 0
Row#9	= 3, 3, 7, 3, 12, 7, 27, 3, 32, 0, 0, 7, 31, 0, 0
Row#10	= 2, 2, 5, 2, 51, 21, 5, 2, 24, 0, 0, 23, 21, 0, 0
Row#11	= 9, 14, 9, 14, 23, 12, 9, 78, 14, 0, 0, 12, 13, 0, 0
Row#12	= 4, 19, 4, 19, 21, 6, 4, 45, 19, 0, 0, 6, 18, 0, 0
Row#13	= -9, 16, -9, 16, 36, -9, 17, 24, 16, 0, 0, -9, 33, 0, 0
Row#14	= -5, -5, 28, 15, -5, 34, 28, 15, 21, 0, 0, 34, 55, 0, 0

RMQ2DSegmentTree2D UpdateValue for (rowY,colX),val = "(5,4),-2":
[rY][cX]
Row#0	= -9, -5, -9, 2, -5, -9, 4, 2, 14, 0, 0, -9, -2, 0, 0
Row#1	= 2, 2, 5, 2, 7, 7, 5, 2, 18, 0, 0, 7, 21, 0, 0
Row#2	= -9, -5, -9, 14, -5, -9, 4, 15, 14, 0, 0, -9, -2, 0, 0
Row#3	= 7, 7, 24, 18, 7, 24, 26, 23, 18, 0, 0, 24, 25, 0, 0
Row#4	= 2, 2, 5, 2, 12, 7, 5, 2, 24, 0, 0, 7, 21, 0, 0
Row#5	= -2, 14, -2, 14, 21, -2, 4, 45, 14, 0, 0, 6, -2, 0, 0
Row#6	= -9, -5, -9, 15, -5, -9, 17, 15, 16, 0, 0, -9, 33, 0, 0
Row#7	= 7, 7, 26, 18, 7, 42, 26, 23, 18, 0, 0, 45, 42, 0, 0
Row#8	= 22, 22, 24, 22, 32, 24, 38, 37, 22, 0, 0, 24, 25, 0, 0
Row#9	= 3, 3, 7, 3, 12, 7, 27, 3, 32, 0, 0, 7, 31, 0, 0
Row#10	= 2, 2, 5, 2, 51, 21, 5, 2, 24, 0, 0, 23, 21, 0, 0
Row#11	= 9, 14, 9, 14, 23, 12, 9, 78, 14, 0, 0, 12, 13, 0, 0
Row#12	= -2, 19, -2, 19, 21, -2, 4, 45, 19, 0, 0, 6, -2, 0, 0
Row#13	= -9, 16, -9, 16, 36, -9, 17, 24, 16, 0, 0, -9, 33, 0, 0
Row#14	= -5, -5, 28, 15, -5, 34, 28, 15, 21, 0, 0, 34, 55, 0, 0

RMQ2DSegmentTree2D QueryRange for "(0,0),(7,5)": -9
RMQ2DSegmentTree2D QueryRange for "(4,0),(7,2)": -5
RMQ2DSegmentTree2D QueryRange for "(0,1),(5,5)": -2
*/
#endif