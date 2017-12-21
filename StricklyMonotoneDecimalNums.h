#ifndef STRICKLY_MONOTONE_DECIMAL_NUMS_H
#define STRICKLY_MONOTONE_DECIMAL_NUMS_H
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include "Debug.h"
/*
Elements of programming interview: compute the number of ways to traverse a 2D array, variant
see also UniquePath.h, MonotoneDecimalNums.h, Combinations.h, CombinationSum.h

A decimal number is a sequence of digits, i.e., a sequence over {0,1,2,3,4,5,6,7,8,9}.
The sequence has to be of length 1 or more, and the first element in the sequence cannot be 0.
Call a decimal number D strickly monotone if D[i] < D[i+1], 0 <= i < |D|.
Write a function which takes as input a positive integer k and computes the number of decimal numbers of length k that are strickly monotone.

Initialization:
	1   2   3   4   5   6   7   8   9 (length)
9	1	0	0	0	0	0	0	0	0 (9)
8	2	1	0	0	0	0	0	0	0 (8, 9, 89)
7	3	0	1	0	0	0	0	0	0 (7, 8, 9, 789)
6	4	0	0	1	0	0	0	0	0 (6, 7, 8, 9, 6789)
5	5	0	0	0	1	0	0	0	0 (5, 6, 7, 8, 9, 56789)
4	6	0	0	0	0	1	0	0	0 (4, 5, 6, 7, 8, 9, 456789)
3	7	0	0	0	0	0	1	0	0 (3, 4, 5, 6, 7, 8, 9, 3456789)
2	8	0	0	0	0	0	0	1	0 (2, 3, 4, 5, 6, 7, 8, 9, 23456789)
1	9	0	0	0	0	0	0	0	1 (1, 2, 3, 4, 5, 6, 7, 8, 9, 123456789)
(num)

for length=2:
89,78,79,67,68,69,56,57,58,59
(accumulation: 8:1, 7:3, 6:6, 5:10)
for length=3:
789,678,679,689,567,568,569,578,579,589
(accumulation: 7:1, 6:4, 5:10)
for length=4:
6789,5678,5679,5689,5789
(accumulation: 6:1, 5:5)

	1   2   3   4   5   6   7   8   9 (length)
9	1	0	0	0	0	0	0	0	0
8	2	1	0	0	0	0	0	0	0
7	3	3	1	0	0	0	0	0	0
6	4	6	4	1	0	0	0	0	0
5	5	10	10	5	1	0	0	0	0
4	6	15	20	15	6	1	0	0	0
3	7	21	35	35	21	7	1	0	0
2	8	28	56	70	56	28	8	1	0
1	9	36	84	126	126	84	36	9	1
(num)

DP2D: O(9*9) = O(1) time, O(9*9) = O(1) space

DP2D:
dp[curNumY][curCountX]=num of ways with curCountX+1 digits where each digit is in [0:curNumY+1].
For curNumY in [0:9), for curCountX in [0:9),
if curNumY==curCountX, dp[][]=1 (use up all available digits so has 1 way),
else if curCountX==0, dp[][]=curNumY+1 (has curNumY+1 digits available so has curNum+1 ways for 1 digit),
else, dp[][]=dp[curNumY-1][curCountX-1]+dp[curNumY-1][curCountX] ("less 1 digit less 1 count" + "less 1 digit same count").
Return dp[8][tgtLen-1].

FindAllNoRepeat Recur:
Keep track of startIdx, remainCount, and path,
if remainCount==0, record path and return,
for curNum in [startIdx,9-remainCount+1], push curNum to path, recur(startIdx+1,remainCount-1), pop curNum from path.

*/
class StricklyMonotoneDecimalNums
{
public:
	StricklyMonotoneDecimalNums(){}
	~StricklyMonotoneDecimalNums(){}

	//see also Combinations.h: Count_NoRepeats_DP2D
	int Count_DP2D(int length)
	{
		std::vector<std::vector<int> > dp(9, std::vector<int>(9, 0));

		//init
		for (int rowY = 0; rowY < 9; ++rowY)
		{
			for (int colX = 0; colX < 9; ++colX)
			{
				if (rowY == colX)//9, 89, 789, 6789, ....
				{
					dp[rowY][colX] = 1;
				}
				else if (colX == 0)//9, 8, 7, 6, 5, ..., 1
				{
					dp[rowY][colX] = rowY + 1;
				}
			}
		}

		for (int rowY = 0; rowY < 9; ++rowY)
		{
			for (int colX = 1; colX < rowY; ++colX)//all cols after first before diagonal
			{
				dp[rowY][colX] = dp[rowY - 1][colX - 1] + dp[rowY - 1][colX];//sum of "upper left" and "upper"
			}
		}

		int res = length > 9 ? 0 : dp[8][length - 1];

		Debug::Print2D<int>()(dp, false);
		std::cout << "StricklyMonotoneDecimalNums Count_DP2D for length=\"" << length << "\": " << res << std::endl;
		return res;
	}

	std::vector<std::vector<int> > EnumerateAll_NoRepeats_Recur(int length)
	{
		std::vector<int> path;
		std::vector<std::vector<int> > res;
		if (length <= 9)
			this->recur(length, 1, path, res);
		Debug::Print2D<int>()(res, false);
		std::cout << "StricklyMonotoneDecimalNums EnumerateAll_NoRepeats_Recur for length=\"" << length << "\": see above" << std::endl;
		return res;
	}
private:
	void recur(int count, int begin, std::vector<int> & path, std::vector<std::vector<int> > & res)
	{
		if (count == 0)
		{
			res.push_back(path);
			return;
		}

		int end = 9 - count + 1;
		for (int i = begin; i <= end; ++i)
		{
			path.push_back(i);
			this->recur(count - 1, i + 1, path, res);
			path.pop_back();
		}
	}
};
/*
[rY][cX]
Row#0	= 1, 0, 0, 0, 0, 0, 0, 0, 0
Row#1	= 2, 1, 0, 0, 0, 0, 0, 0, 0
Row#2	= 3, 3, 1, 0, 0, 0, 0, 0, 0
Row#3	= 4, 6, 4, 1, 0, 0, 0, 0, 0
Row#4	= 5, 10, 10, 5, 1, 0, 0, 0, 0
Row#5	= 6, 15, 20, 15, 6, 1, 0, 0, 0
Row#6	= 7, 21, 35, 35, 21, 7, 1, 0, 0
Row#7	= 8, 28, 56, 70, 56, 28, 8, 1, 0
Row#8	= 9, 36, 84, 126, 126, 84, 36, 9, 1

StricklyMonotoneDecimalNums Count_DP2D for length="3": 84
[rY][cX]
Row#0	= 1, 2, 3
Row#1	= 1, 2, 4
Row#2	= 1, 2, 5
Row#3	= 1, 2, 6
Row#4	= 1, 2, 7
Row#5	= 1, 2, 8
Row#6	= 1, 2, 9
Row#7	= 1, 3, 4
Row#8	= 1, 3, 5
Row#9	= 1, 3, 6
Row#10	= 1, 3, 7
Row#11	= 1, 3, 8
Row#12	= 1, 3, 9
Row#13	= 1, 4, 5
Row#14	= 1, 4, 6
Row#15	= 1, 4, 7
Row#16	= 1, 4, 8
Row#17	= 1, 4, 9
Row#18	= 1, 5, 6
Row#19	= 1, 5, 7
Row#20	= 1, 5, 8
Row#21	= 1, 5, 9
Row#22	= 1, 6, 7
Row#23	= 1, 6, 8
Row#24	= 1, 6, 9
Row#25	= 1, 7, 8
Row#26	= 1, 7, 9
Row#27	= 1, 8, 9
Row#28	= 2, 3, 4
Row#29	= 2, 3, 5
Row#30	= 2, 3, 6
Row#31	= 2, 3, 7
Row#32	= 2, 3, 8
Row#33	= 2, 3, 9
Row#34	= 2, 4, 5
Row#35	= 2, 4, 6
Row#36	= 2, 4, 7
Row#37	= 2, 4, 8
Row#38	= 2, 4, 9
Row#39	= 2, 5, 6
Row#40	= 2, 5, 7
Row#41	= 2, 5, 8
Row#42	= 2, 5, 9
Row#43	= 2, 6, 7
Row#44	= 2, 6, 8
Row#45	= 2, 6, 9
Row#46	= 2, 7, 8
Row#47	= 2, 7, 9
Row#48	= 2, 8, 9
Row#49	= 3, 4, 5
Row#50	= 3, 4, 6
Row#51	= 3, 4, 7
Row#52	= 3, 4, 8
Row#53	= 3, 4, 9
Row#54	= 3, 5, 6
Row#55	= 3, 5, 7
Row#56	= 3, 5, 8
Row#57	= 3, 5, 9
Row#58	= 3, 6, 7
Row#59	= 3, 6, 8
Row#60	= 3, 6, 9
Row#61	= 3, 7, 8
Row#62	= 3, 7, 9
Row#63	= 3, 8, 9
Row#64	= 4, 5, 6
Row#65	= 4, 5, 7
Row#66	= 4, 5, 8
Row#67	= 4, 5, 9
Row#68	= 4, 6, 7
Row#69	= 4, 6, 8
Row#70	= 4, 6, 9
Row#71	= 4, 7, 8
Row#72	= 4, 7, 9
Row#73	= 4, 8, 9
Row#74	= 5, 6, 7
Row#75	= 5, 6, 8
Row#76	= 5, 6, 9
Row#77	= 5, 7, 8
Row#78	= 5, 7, 9
Row#79	= 5, 8, 9
Row#80	= 6, 7, 8
Row#81	= 6, 7, 9
Row#82	= 6, 8, 9
Row#83	= 7, 8, 9

StricklyMonotoneDecimalNums EnumerateAll_NoRepeats_Recur for length="3": see above
*/
#endif