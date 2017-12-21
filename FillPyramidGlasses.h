#ifndef FILL_PYRAMID_GLASSES_H
#define FILL_PYRAMID_GLASSES_H
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include "Debug.h"
/*
https://sites.google.com/site/spaceofjameschen/annnocements/calculatehowmanywatercontainedbyjthglasses--amazon
http://www.careercup.com/question?id=22191662
http://www.careercup.com/question?id=12217186
http://www.geeksforgeeks.org/find-water-in-a-glass/
There are some glasses with equal volume 1 litre.
The glasses kept as follows:
               1..................0
            2     3...............1
         4     5     6............2
      7     8     9    10.........3
   11    12    13   14    15......4
16    17    18   19    20    21...5

You can pour water to only top glass.
If you pour more than 1 litre water to 1st glass, water overflows and fills equally both 2nd and 3rd glass.
Glass 5 will get water from both 2nd glass and 3rd glass and so on.
If you have X litre of water and you pour that water in top glass, how much water will be contained by j-th glass in i-th row?

Observations:
1. each row has rowIndex+1 elements
2. total elements in the above pyramid are 6*(6+1)/2 = 21
3. each element's index + rowIndex + 1 = bottom element's index
   each element's index + rowIndex + 1 + 1 = bottom right element's index

See also PascalTriangle.h
*/
class FillPyramidGlasses
{
public:
	FillPyramidGlasses(){}
	~FillPyramidGlasses(){}

	double GetVolume(int rowIdx, int colIdx, double litre)//rowIdx, colIdx are 0-based index
	{
		if (rowIdx < 0 || colIdx < 0 || rowIdx < colIdx)
			return -1.0f;

		std::vector<double> curRow(rowIdx + 1);//bottom row has (rowIdx+1) elements
		std::vector<double> nxtRow(rowIdx + 1);//bottom row has (rowIdx+1) elements
		curRow[0] = litre;

		for (int row = 0; row < rowIdx; ++row)
		{
			for (int col = 0; col <= row; ++col)
			{
				if (curRow[col] > 1.0f)
				{
					nxtRow[col] += (curRow[col] - 1.0f) / 2;//bottom
					nxtRow[col + 1] += (curRow[col] - 1.0f) / 2;//bottom right
				}
			}

			std::cout << "row" << row << ": " << Debug::ToStr1D<double>()(curRow) << std::endl;

			for (int col = 0; col <= row + 1; ++col)
			{
				curRow[col] = nxtRow[col];
				nxtRow[col] = 0;
			}
		}

		std::cout << "row" << rowIdx << ": " << Debug::ToStr1D<double>()(curRow) << std::endl;

		double res = curRow[colIdx] > 1.0f ? 1.0f : curRow[colIdx];
		std::cout << "FillPyramidGlasses for \"" << rowIdx << "-th row, " << colIdx << "-th col, " << litre << " litre\": " << res << std::endl;
		return res;
	}
};
/*
row0: 5, 0, 0, 0, 0
row1: 2, 2, 0, 0, 0
row2: 0.5, 1, 0.5, 0, 0
row3: 0, 0, 0, 0, 0
row4: 0, 0, 0, 0, 0
FillPyramidGlasses for "4-th row, 4-th col, 5 litre": 0
row0: 32, 0, 0, 0, 0, 0
row1: 15.5, 15.5, 0, 0, 0, 0
row2: 7.25, 14.5, 7.25, 0, 0, 0
row3: 3.125, 9.875, 9.875, 3.125, 0, 0
row4: 1.0625, 5.5, 8.875, 5.5, 1.0625, 0
row5: 0.03125, 2.28125, 6.1875, 6.1875, 2.28125, 0.03125
FillPyramidGlasses for "5-th row, 5-th col, 32 litre": 0.03125
*/
#endif