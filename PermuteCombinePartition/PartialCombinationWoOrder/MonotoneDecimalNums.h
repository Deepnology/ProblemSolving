#ifndef MONOTONE_DECIMAL_NUMS_H
#define MONOTONE_DECIMAL_NUMS_H
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include "Debug.h"
/*
Elements of programming interview: compute the number of ways to traverse a 2D array, variant
see also UniquePath.h, StricklyMonotoneDecimalNums.h, Combinations.h, CombinationSum.h

A decimal number is a sequence of digits, i.e., a sequence over {0,1,2,3,4,5,6,7,8,9}.
The sequence has to be of length 1 or more, and the first element in the sequence cannot be 0.
Call a decimal number D monotone if D[i] <= D[i+1], 0 <= i < |D|.
Write a function which takes as input a positive integer k and computes the number of decimal numbers of length k that are monotone.

Initialization:
	1   2   3   4   5 (length)
9	1	1	1	1	1 (9, 99, 999, 9999, 99999)
8	2                 (8, 9)
7	3                 (7, 8, 9)
6	4                 (6, 7, 8, 9)
5	5                 (5, 6, 7, 8, 9)
4	6                 (4, 5, 6, 7, 8, 9)
3	7                 (3, 4, 5, 6, 7, 8, 9)
2	8                 (2, 3, 4, 5, 6, 7, 8, 9)
1	9                 (1, 2, 3, 4, 5, 6, 7, 8, 9)
(num)

for length=2:
99,88,89,77,78,79,66,67,68,69
(accumulation: 9:1, 8:3, 7:6, 6:10)
for length=3:
999,889,899,888,777,778,788,789,799,779
(accumulation: 9:1, 8:4, 7:10)

	1   2   3   4   5 (length)
9	1	1	1	1	1
8	2	3	4	5	6
7	3	6	10	15	21
6	4	10	20	35	56
5	5	15	35	70	126
4	6	21	56	126	252
3	7	28	84	210	426
2	8	36	120	330	792
1	9	45	165	495	1287
(num)

DP2D: O(9*k) = O(k) time, O(9*k) = O(k) space

DP2D:
dp[curNumY][curCountX]=num of ways with curCountX+1 digits where each digit is in [0:curNumY+1].
For curNumY in [0:9), for curCountX in [0:9),
if curNumY==0, dp[][]=1 (has 1 digit available so has 1 way),
else if curCountX==0, dp[][]=curNumY+1 (has curNumY+1 digits available so has curNum+1 ways for 1 digit),
else, dp[][]=dp[curNumY][curCountX-1]+dp[curNumY-1][curCountX] ("same digit less 1 count" + "less 1 digit same count").
Return dp[8][tgtLen-1].

FindAllAllowRepeat Recur:
Keep track of startIdx, remainCount, and path,
if remainCount==0, record path and return,
for curNum in [startIdx,9], push curNum to path, recur(startIdx,remainCount-1), pop curNum from path.

*/
class MonotoneDecimalNums
{
public:
	MonotoneDecimalNums(){}
	~MonotoneDecimalNums(){}

	//see also Combinations.h: Count_AllowRepeats_DP2D
	int Count_DP2D(int length)
	{
		std::vector<std::vector<int> > dp(9, std::vector<int>(length, 0));

		for (int rowY = 0; rowY < 9; ++rowY)
		{
			for (int colX = 0; colX < length; ++colX)
			{
				if (rowY == 0)//9, 99, 999, 9999, ....
				{
					dp[rowY][colX] = 1;
				}
				else if (colX == 0)//9, 8, 7, 6, 5, ..., 1
				{
					dp[rowY][colX] = rowY + 1;
				}
				else
				{
					dp[rowY][colX] = dp[rowY - 1][colX] + dp[rowY][colX - 1];//sum of "upper" and "left"
				}
			}
		}

		Debug::Print2D<int>()(dp, false);
		std::cout << "MonotoneDecimalNums Count_DP2D for length=\"" << length << "\": " << dp[8][length - 1] << std::endl;
		return dp[8][length - 1];
	}

	std::vector<std::vector<int> > EnumerateAll_AllowRepeats_Recur(int length)
	{
		std::vector<int> path;
		std::vector<std::vector<int> > res;
		this->recur(length, 1, path, res);
		Debug::Print2D<int>()(res, false);
		std::cout << "MonotoneDecimalNums EnumerateAll_Recur for length=\"" << length << "\": see above" << std::endl;
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

		for (int i = begin; i <= 9; ++i)
		{
			path.push_back(i);
			this->recur(count - 1, i, path, res);
			path.pop_back();
		}
	}
};
/*
[rY][cX]
Row#0	= 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
Row#1	= 2, 3, 4, 5, 6, 7, 8, 9, 10, 11
Row#2	= 3, 6, 10, 15, 21, 28, 36, 45, 55, 66
Row#3	= 4, 10, 20, 35, 56, 84, 120, 165, 220, 286
Row#4	= 5, 15, 35, 70, 126, 210, 330, 495, 715, 1001
Row#5	= 6, 21, 56, 126, 252, 462, 792, 1287, 2002, 3003
Row#6	= 7, 28, 84, 210, 462, 924, 1716, 3003, 5005, 8008
Row#7	= 8, 36, 120, 330, 792, 1716, 3432, 6435, 11440, 19448
Row#8	= 9, 45, 165, 495, 1287, 3003, 6435, 12870, 24310, 43758

MonotoneDecimalNums Count_DP2D for length="10": 43758
[rY][cX]
Row#0	= 1, 1, 1
Row#1	= 1, 1, 2
Row#2	= 1, 1, 3
Row#3	= 1, 1, 4
Row#4	= 1, 1, 5
Row#5	= 1, 1, 6
Row#6	= 1, 1, 7
Row#7	= 1, 1, 8
Row#8	= 1, 1, 9
Row#9	= 1, 2, 2
Row#10	= 1, 2, 3
Row#11	= 1, 2, 4
Row#12	= 1, 2, 5
Row#13	= 1, 2, 6
Row#14	= 1, 2, 7
Row#15	= 1, 2, 8
Row#16	= 1, 2, 9
Row#17	= 1, 3, 3
Row#18	= 1, 3, 4
Row#19	= 1, 3, 5
Row#20	= 1, 3, 6
Row#21	= 1, 3, 7
Row#22	= 1, 3, 8
Row#23	= 1, 3, 9
Row#24	= 1, 4, 4
Row#25	= 1, 4, 5
Row#26	= 1, 4, 6
Row#27	= 1, 4, 7
Row#28	= 1, 4, 8
Row#29	= 1, 4, 9
Row#30	= 1, 5, 5
Row#31	= 1, 5, 6
Row#32	= 1, 5, 7
Row#33	= 1, 5, 8
Row#34	= 1, 5, 9
Row#35	= 1, 6, 6
Row#36	= 1, 6, 7
Row#37	= 1, 6, 8
Row#38	= 1, 6, 9
Row#39	= 1, 7, 7
Row#40	= 1, 7, 8
Row#41	= 1, 7, 9
Row#42	= 1, 8, 8
Row#43	= 1, 8, 9
Row#44	= 1, 9, 9
Row#45	= 2, 2, 2
Row#46	= 2, 2, 3
Row#47	= 2, 2, 4
Row#48	= 2, 2, 5
Row#49	= 2, 2, 6
Row#50	= 2, 2, 7
Row#51	= 2, 2, 8
Row#52	= 2, 2, 9
Row#53	= 2, 3, 3
Row#54	= 2, 3, 4
Row#55	= 2, 3, 5
Row#56	= 2, 3, 6
Row#57	= 2, 3, 7
Row#58	= 2, 3, 8
Row#59	= 2, 3, 9
Row#60	= 2, 4, 4
Row#61	= 2, 4, 5
Row#62	= 2, 4, 6
Row#63	= 2, 4, 7
Row#64	= 2, 4, 8
Row#65	= 2, 4, 9
Row#66	= 2, 5, 5
Row#67	= 2, 5, 6
Row#68	= 2, 5, 7
Row#69	= 2, 5, 8
Row#70	= 2, 5, 9
Row#71	= 2, 6, 6
Row#72	= 2, 6, 7
Row#73	= 2, 6, 8
Row#74	= 2, 6, 9
Row#75	= 2, 7, 7
Row#76	= 2, 7, 8
Row#77	= 2, 7, 9
Row#78	= 2, 8, 8
Row#79	= 2, 8, 9
Row#80	= 2, 9, 9
Row#81	= 3, 3, 3
Row#82	= 3, 3, 4
Row#83	= 3, 3, 5
Row#84	= 3, 3, 6
Row#85	= 3, 3, 7
Row#86	= 3, 3, 8
Row#87	= 3, 3, 9
Row#88	= 3, 4, 4
Row#89	= 3, 4, 5
Row#90	= 3, 4, 6
Row#91	= 3, 4, 7
Row#92	= 3, 4, 8
Row#93	= 3, 4, 9
Row#94	= 3, 5, 5
Row#95	= 3, 5, 6
Row#96	= 3, 5, 7
Row#97	= 3, 5, 8
Row#98	= 3, 5, 9
Row#99	= 3, 6, 6
Row#100	= 3, 6, 7
Row#101	= 3, 6, 8
Row#102	= 3, 6, 9
Row#103	= 3, 7, 7
Row#104	= 3, 7, 8
Row#105	= 3, 7, 9
Row#106	= 3, 8, 8
Row#107	= 3, 8, 9
Row#108	= 3, 9, 9
Row#109	= 4, 4, 4
Row#110	= 4, 4, 5
Row#111	= 4, 4, 6
Row#112	= 4, 4, 7
Row#113	= 4, 4, 8
Row#114	= 4, 4, 9
Row#115	= 4, 5, 5
Row#116	= 4, 5, 6
Row#117	= 4, 5, 7
Row#118	= 4, 5, 8
Row#119	= 4, 5, 9
Row#120	= 4, 6, 6
Row#121	= 4, 6, 7
Row#122	= 4, 6, 8
Row#123	= 4, 6, 9
Row#124	= 4, 7, 7
Row#125	= 4, 7, 8
Row#126	= 4, 7, 9
Row#127	= 4, 8, 8
Row#128	= 4, 8, 9
Row#129	= 4, 9, 9
Row#130	= 5, 5, 5
Row#131	= 5, 5, 6
Row#132	= 5, 5, 7
Row#133	= 5, 5, 8
Row#134	= 5, 5, 9
Row#135	= 5, 6, 6
Row#136	= 5, 6, 7
Row#137	= 5, 6, 8
Row#138	= 5, 6, 9
Row#139	= 5, 7, 7
Row#140	= 5, 7, 8
Row#141	= 5, 7, 9
Row#142	= 5, 8, 8
Row#143	= 5, 8, 9
Row#144	= 5, 9, 9
Row#145	= 6, 6, 6
Row#146	= 6, 6, 7
Row#147	= 6, 6, 8
Row#148	= 6, 6, 9
Row#149	= 6, 7, 7
Row#150	= 6, 7, 8
Row#151	= 6, 7, 9
Row#152	= 6, 8, 8
Row#153	= 6, 8, 9
Row#154	= 6, 9, 9
Row#155	= 7, 7, 7
Row#156	= 7, 7, 8
Row#157	= 7, 7, 9
Row#158	= 7, 8, 8
Row#159	= 7, 8, 9
Row#160	= 7, 9, 9
Row#161	= 8, 8, 8
Row#162	= 8, 8, 9
Row#163	= 8, 9, 9
Row#164	= 9, 9, 9

MonotoneDecimalNums EnumerateAll_Recur for length="3": see above
*/
#endif