/*MEMO*/
#ifndef ROTATE_IMAGE_H
#define ROTATE_IMAGE_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, Array: Rotate a 2D array
Leetcode: Rotate Image
// You are given an n x n 2D matrix representing an image.
//
// Rotate the image by 90 degrees (clockwise).
//
// Follow up:
// Could you do this in-place?

Just need to circularly right rotate the quoted pixels.
"11" "12" "13" "14"  15
 21  "22" "23"  24   25
 31   32   33   34   35
 41   42   43   44   45
 51   52   53   54   55

[0,0]<-[4,0]<-[4,4]<-[0,4]
[0,1]<-[3,0]<-[4,3]<-[1,4]
[0,2]<-[2,0]<-[4,2]<-[2,4]
[0,3]<-[1,0]<-[4,1]<-[3,4]
[1,1]<-[3,1]<-[3,3]<-[1,3]
[1,2]<-[2,1]<-[3,2]<-[2,3]

 51   41   31   21  "11"
 52   42   32  "22" "12"
 53   43   33  "23" "13"
 54   44   34   24  "14"
 55   45   35   25   15


Aparajith' method:
_________
		|
 ___	|
|_______|

use 1xN array extra space
*/
class RotateImage
{
public:
	RotateImage(){}
	~RotateImage(){}

	void Clockwise_Iterate(std::vector<std::vector<int>> && matrix)//[rowY][columnX]
	{
		Clockwise_Iterate(matrix);
	}
	void Clockwise_Iterate(std::vector<std::vector<int>> & matrix)//[rowY][columnX]
	{
		if (matrix.empty())
			return;
		std::cout << "RotateImage Clockwise_Iterate Before and After:" << std::endl;
		Debug::Print2D<int>()(matrix, false);

		int N = matrix.size();
		for (int i = 0; i < N / 2; ++i)//for each circle with same radius from outter to inner
		{
			for (int j = i; j < N - 1 - i; ++j)//for each element on the circle with same radius starting from diagonal to middle column
			{
				std::cout << "[" << i << "," << j << "]<-[" << N - 1 - j << "," << i << "]<-[" << N - 1 - i << "," << N - 1 - j << "]<-[" << j << "," << N - 1 - i << "]" << std::endl;
				this->cyclic_roll(matrix[i][j], matrix[N - 1 - j][i], matrix[N - 1 - i][N - 1 - j], matrix[j][N - 1 - i]);//top left, bottom left, bottom right, top right
			}
		}
		Debug::Print2D<int>()(matrix, false);
	}
private:
	void cyclic_roll(int & a, int & b, int & c, int & d)//a <- b <- c <- d <- a
	{
		int tmp = a;
		a = b;
		b = c;
		c = d;
		d = tmp;
	}


public:
	RotateImage(const std::vector<std::vector<int>> & matrix) : m_matrix(matrix) {}
	int Read(int rowY, int colX) const
	{
		return m_matrix[m_matrix.size() - 1 - colX][rowY];//bottom left
	}
	void Write(int rowY, int colX, int val)
	{
		m_matrix[m_matrix.size() - 1 - colX][rowY] = val;
	}
private:
	std::vector<std::vector<int>> m_matrix;

};
/*
RotateImage Clockwise_Iterate Before and After:
[rY][cX]
Row#0	= 11, 12, 13, 14, 15
Row#1	= 21, 22, 23, 24, 25
Row#2	= 31, 32, 33, 34, 35
Row#3	= 41, 42, 43, 44, 45
Row#4	= 51, 52, 53, 54, 55

[0,0]<-[4,0]<-[4,4]<-[0,4]
[0,1]<-[3,0]<-[4,3]<-[1,4]
[0,2]<-[2,0]<-[4,2]<-[2,4]
[0,3]<-[1,0]<-[4,1]<-[3,4]
[1,1]<-[3,1]<-[3,3]<-[1,3]
[1,2]<-[2,1]<-[3,2]<-[2,3]
[rY][cX]
Row#0	= 51, 41, 31, 21, 11
Row#1	= 52, 42, 32, 22, 12
Row#2	= 53, 43, 33, 23, 13
Row#3	= 54, 44, 34, 24, 14
Row#4	= 55, 45, 35, 25, 15

[rY][cX]
Row#0	= 51, 41, 31, 21, 11
Row#1	= 52, 42, 32, 22, 12
Row#2	= 53, 43, 33, 23, 13
Row#3	= 54, 44, 34, 24, 14
Row#4	= 55, 45, 35, 25, 15

Read the above matrix rotated 90: 55, 54, 53, 52, 51, 45, 44, 43, 42, 41, 35, 34, 33, 32, 31, 25, 24, 23, 22, 21, 15, 14, 13, 12, 11

RotateImage Clockwise_Iterate Before and After:
[rY][cX]
Row#0	= 11, 12, 13, 14, 15, 16
Row#1	= 21, 22, 23, 24, 25, 26
Row#2	= 31, 32, 33, 34, 35, 36
Row#3	= 41, 42, 43, 44, 45, 46
Row#4	= 51, 52, 53, 54, 55, 56
Row#5	= 61, 62, 63, 64, 65, 66

[0,0]<-[5,0]<-[5,5]<-[0,5]
[0,1]<-[4,0]<-[5,4]<-[1,5]
[0,2]<-[3,0]<-[5,3]<-[2,5]
[0,3]<-[2,0]<-[5,2]<-[3,5]
[0,4]<-[1,0]<-[5,1]<-[4,5]
[1,1]<-[4,1]<-[4,4]<-[1,4]
[1,2]<-[3,1]<-[4,3]<-[2,4]
[1,3]<-[2,1]<-[4,2]<-[3,4]
[2,2]<-[3,2]<-[3,3]<-[2,3]
[rY][cX]
Row#0	= 61, 51, 41, 31, 21, 11
Row#1	= 62, 52, 42, 32, 22, 12
Row#2	= 63, 53, 43, 33, 23, 13
Row#3	= 64, 54, 44, 34, 24, 14
Row#4	= 65, 55, 45, 35, 25, 15
Row#5	= 66, 56, 46, 36, 26, 16

RotateImage Clockwise_Iterate Before and After:
[rY][cX]
Row#0	= 11, 12, 13, 14, 15, 16, 17
Row#1	= 21, 22, 23, 24, 25, 26, 27
Row#2	= 31, 32, 33, 34, 35, 36, 37
Row#3	= 41, 42, 43, 44, 45, 46, 47
Row#4	= 51, 52, 53, 54, 55, 56, 57
Row#5	= 61, 62, 63, 64, 65, 66, 67
Row#6	= 71, 72, 73, 74, 75, 76, 77

[0,0]<-[6,0]<-[6,6]<-[0,6]
[0,1]<-[5,0]<-[6,5]<-[1,6]
[0,2]<-[4,0]<-[6,4]<-[2,6]
[0,3]<-[3,0]<-[6,3]<-[3,6]
[0,4]<-[2,0]<-[6,2]<-[4,6]
[0,5]<-[1,0]<-[6,1]<-[5,6]
[1,1]<-[5,1]<-[5,5]<-[1,5]
[1,2]<-[4,1]<-[5,4]<-[2,5]
[1,3]<-[3,1]<-[5,3]<-[3,5]
[1,4]<-[2,1]<-[5,2]<-[4,5]
[2,2]<-[4,2]<-[4,4]<-[2,4]
[2,3]<-[3,2]<-[4,3]<-[3,4]
[rY][cX]
Row#0	= 71, 61, 51, 41, 31, 21, 11
Row#1	= 72, 62, 52, 42, 32, 22, 12
Row#2	= 73, 63, 53, 43, 33, 23, 13
Row#3	= 74, 64, 54, 44, 34, 24, 14
Row#4	= 75, 65, 55, 45, 35, 25, 15
Row#5	= 76, 66, 56, 46, 36, 26, 16
Row#6	= 77, 67, 57, 47, 37, 27, 17
*/
#endif