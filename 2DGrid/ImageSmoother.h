#ifndef IMAGE_SMOOTHER_H
#define IMAGE_SMOOTHER_H
#include "Debug.h"
/*
Leetcode: Image Smoother
Given a 2D integer matrix M representing the gray scale of an image, you need to design a smoother to
make the gray scale of each cell becomes the average gray scale (rounding down) of all the 8 surrounding cells and itself.
If a cell has less than 8 surrounding cells, then use as many as you can.
Example 1:
Input:
[[1,1,1],
 [1,0,1],
 [1,1,1]]
Output:
[[0, 0, 0],
 [0, 0, 0],
 [0, 0, 0]]
Explanation:
For the point (0,0), (0,2), (2,0), (2,2): floor(3/4) = floor(0.75) = 0
For the point (0,1), (1,0), (1,2), (2,1): floor(5/6) = floor(0.83333333) = 0
For the point (1,1): floor(8/9) = floor(0.88888889) = 0
*/
class ImageSmoother
{
public:
	ImageSmoother() {}

	std::vector<std::vector<int>> BruteForce(std::vector<std::vector<int>> & m)
	{
		std::vector<std::vector<int>> res;
		int N = m.size();
		if (N == 0) return res;
		int M = m[0].size();
		if (M == 0) return res;
		res.resize(N, std::vector<int>(M));
		std::vector<std::vector<int>> dir({ { -1,0 },{ 1,0 },{ 0,-1 },{ 0,1 },{ -1,-1 },{ -1,1 },{ 1,-1 },{ 1,1 } });
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < M; ++j)
			{
				double sum = m[i][j];
				double count = 1;
				for (int k = 0; k < 8; ++k)
				{
					int ii = i + dir[k][0];
					int jj = j + dir[k][1];
					if (ii >= 0 && ii < N && jj >= 0 && jj < M)
					{
						sum += (double)m[ii][jj];
						count += 1;
					}
				}
				res[i][j] = std::floor(sum / count);
			}
		}
		return res;
	}
};
#endif
