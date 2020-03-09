#ifndef LONELY_PIXEL_H
#define LONELY_PIXEL_H
#include "Debug.h"
/*
Leetcode: Lonely Pixel
Given a picture consisting of black and white pixels, find the number of black lonely pixels.
The picture is represented by a 2D char array consisting of 'B' and 'W', which means black and white pixels respectively.
A black lonely pixel is character 'B' that located at a specific position where the same row and same column don't have any other black pixels.
Example:
Input:
[['W', 'W', 'B'],
 ['W', 'B', 'W'],
 ['B', 'W', 'W']]
Output: 3
Explanation: All the three 'B's are black lonely pixels.

Leetcode: Lonely Pixel II
Given a picture consisting of black and white pixels, and a positive integer N, find the number of black pixels located at some specific row R and column C that align with all the following rules:
1. Row R and column C both contain exactly N black pixels.
2. For all rows that have a black pixel at column C, they should be exactly the same as row R
The picture is represented by a 2D char array consisting of 'B' and 'W', which means black and white pixels respectively.
Example:
Input:                                            
[['W', 'B', 'W', 'B', 'B', 'W'],    
 ['W', 'B', 'W', 'B', 'B', 'W'],    
 ['W', 'B', 'W', 'B', 'B', 'W'],    
 ['W', 'W', 'B', 'W', 'B', 'W']] 
N = 3
Output: 6
Explanation: All the bold 'B' are the black pixels we need (all 'B's at column 1 and 3).
        0    1    2    3    4    5         column index                                            
0    [['W', 'B', 'W', 'B', 'B', 'W'],    
1     ['W', 'B', 'W', 'B', 'B', 'W'],    
2     ['W', 'B', 'W', 'B', 'B', 'W'],    
3     ['W', 'W', 'B', 'W', 'B', 'W']]    
row index
Take 'B' at row R = 0 and column C = 1 as an example:
Rule 1, row R = 0 and column C = 1 both have exactly N = 3 black pixels. 
Rule 2, the rows have black pixel at column C = 1 are row 0, row 1 and row 2. They are exactly the same as row R = 0.

*/
class LonelyPixel
{
public:
	LonelyPixel() {}

	int CountLonelyB(const std::vector<std::vector<char>> & picture)
	{
		int N = picture.size();
		if (N == 0) return 0;
		int M = picture[0].size();
		if (M == 0) return 0;
		std::vector<int> col(M, 0);
		std::vector<int> row(N, 0);
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < M; ++j)
			{
				if (picture[i][j] == 'B')
				{
					++row[i];
					++col[j];
				}
			}
		}
		int res = 0;
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < M; ++j)
			{
				if (picture[i][j] == 'B' && row[i] == 1 && col[j] == 1)
					++res;
			}
		}

		Debug::Print2D<char>()(picture, false);
		std::cout << "LonelyPixel CountLonelyB for the above picture: " << res << std::endl;
		return res;
	}

	int CountLonelyB(const std::vector<std::vector<char>> & picture, int n)
	{
		int N = picture.size();
		if (N == 0) return 0;
		int M = picture[0].size();
		if (M == 0) return 0;
		std::unordered_map<int, std::unordered_set<int>> row;
		std::unordered_map<int, std::unordered_set<int>> col;
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < M; ++j)
			{
				if (picture[i][j] == 'B')
				{
					row[i].insert(j);
					col[j].insert(i);
				}
			}
		}
		int res = 0;
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < M; ++j)
			{
				if (picture[i][j] == 'B' && row[i].size() == n && col[j].size() == n)//rule 1
				{
					bool valid = true;//rule 2
					for (const int & r : col[j])
					{
						if (r != i && row[r] != row[i])
						{
							valid = false;
							break;
						}
					}
					if (valid) ++res;
				}
			}
		}

		Debug::Print2D<char>()(picture, false);
		std::cout << "LonelyPixel CountLonelyB for the above picture and n=\"" << n << "\": " << res << std::endl;
		return res;
	}
};
/*
[rY][cX]
Row#0	= W, W, B
Row#1	= W, B, W
Row#2	= B, W, W

LonelyPixel CountLonelyB for the above picture: 3
[rY][cX]
Row#0	= W, B, W, B, B, W
Row#1	= W, B, W, B, B, W
Row#2	= W, B, W, B, B, W
Row#3	= W, W, B, W, B, W

LonelyPixel CountLonelyB for the above picture and n="3": 6
*/
#endif
