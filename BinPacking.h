#ifndef BIN_PACKING_H
#define BIN_PACKING_H
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Debug.h"
/*
Amazon
http://www.careercup.com/question?id=8695757
https://gist.github.com/hyobyun/5695060
3 kinds of items' bin packing problem:
Given k1 items with size of s1, k2 items with size of s2, k3 items with size of s3.
Given unlimited number of bins with capacity of Cap, which should be big enough to accommodate the largest item among s1, s2, or s3.
Find the min number of bins required to pack all items.

Approach1: Enumerate all
The worst case is to use a single bin to pack a single item, which requires k1+k2+k3 bins.
In this case, enumerate all cases to use k1+k2+k3 bins to pack k1+k2+k3 items, and find the best case with minimum bin numbers.
See also BinPacking2.h

Approach2: DP3D
Keep track of "the min number of bins that have been used" and "the max remaining volume among current used bins" for all possible combinations of the 3 kinds of items.
Compute current "min number of bins that have been used" and "the min occupied bin volume" from previous 3 cases.
O(k1*k2*k3) time

*/
class BinPacking
{
public:
	BinPacking(){}
	~BinPacking(){}

	int MinCount_DP3D(int k1, int s1, int k2, int s2, int k3, int s3, int Cap)
	{
		if ((k1 == 0 && k2 == 0 && k3 == 0) || (s1 == 0 && s2 == 0 && s3 == 0))
			return 0;

		std::vector<std::vector<std::vector<std::pair<int, int>>>> dp(k1 + 1, std::vector<std::vector<std::pair<int, int>>>(k2 + 1, std::vector<std::pair<int, int> >(k3 + 1, std::make_pair(-1, -1))));
		dp[0][0][0].first = 1;//num of bins that have been used
		dp[0][0][0].second = 0;//the occupied volume of the bin that has max remaining volume among current used bins, that is, the "min occupied bin volume"
		/*
		dp[0][0][0]: no item is packed
		dp[k1][k2][k3]: all items are packed
		*/

		for (int i = 0; i <= k1; ++i)
		{
			for (int j = 0; j <= k2; ++j)
			{
				for (int k = 0; k <= k3; ++k)
				{
					if (i == 0 && j == 0 && k == 0)//skip base condiiton
						continue;

					//now we have i of s1 items, j of s2 items, and k of s3 items

					std::vector<std::pair<int, int>> sol(3, std::make_pair(-1, -1));
					std::vector<int> extraBin(3, 0);

					//1. determine if one extra bin is required for each case
					extraBin[0] = (i != 0 && dp[i - 1][j][k].second + s1 > Cap) ? 1 : 0;//see if 1 extra bin is required to add a s1 to the bin with max remaining volume from case dp[i-1][j][k]
					extraBin[1] = (j != 0 && dp[i][j - 1][k].second + s2 > Cap) ? 1 : 0;//see if 1 extra bin is required to add a s2 to the bin with max remaining volume from case dp[i][j-1][k]
					extraBin[2] = (k != 0 && dp[i][j][k - 1].second + s3 > Cap) ? 1 : 0;//see if 1 extra bin is required to add a s3 to the bin with max remaining volume from case dp[i][j][k-1]

					//2. find the current total num of bins used based on the requirement of one extra bin after adding current item
					sol[0].first = i == 0 ? INT_MAX : extraBin[0] ? dp[i - 1][j][k].first + 1 : dp[i - 1][j][k].first;//add a s1 from case dp[i-1][j][k]
					sol[1].first = j == 0 ? INT_MAX : extraBin[1] ? dp[i][j - 1][k].first + 1 : dp[i][j - 1][k].first;//add a s2 from case dp[i][j-1][k]
					sol[2].first = k == 0 ? INT_MAX : extraBin[2] ? dp[i][j][k - 1].first + 1 : dp[i][j][k - 1].first;//add a s3 from case dp[i][j][k-1]

					//3. find the current occupied bin volume after adding current item
					sol[0].second = (i == 0 || extraBin[0]) ? s1 : dp[i - 1][j][k].second + s1;//add a s1 from case dp[i-1][j][k]
					sol[1].second = (j == 0 || extraBin[1]) ? s2 : dp[i][j - 1][k].second + s2;//add a s2 from case dp[i][j-1][k]
					sol[2].second = (k == 0 || extraBin[2]) ? s3 : dp[i][j][k - 1].second + s3;//add a s3 from case dp[i][j][k-1]

					//4. compare all 3 cases
					//update dp[i][j][k] with the case of "smallest total num of bins" or the case of "equal total num of bins with smallest occupied volume of bin"
					for (int x = 0; x < 3; ++x)
						if (x == 0 ||
							sol[x].first < dp[i][j][k].first ||//use less number of bins
							(sol[x].first == dp[i][j][k].first && sol[x].second < dp[i][j][k].second))//use equal number of bins && have a greater remaining volume
						{
							dp[i][j][k].first = sol[x].first;
							dp[i][j][k].second = sol[x].second;
						}
				}
			}
		}

		Debug::Print3D<int>()(dp, false);
		std::cout << "BinPacking MinCount_DP3D for \"[count,size]=[" << k1 << "," << s1 << "],[" << k2 << "," << s2 << "],[" << k3 << "," << s3 << "], Cap=" << Cap << "\": " << dp[k1][k2][k3].first << std::endl;
		return dp[k1][k2][k3].first;
	}
};
/*
[rY][cX][dZ]
Row#0	= [1,0],[1,7],[2,7].	[1,5],[2,5],[3,5].	[1,10],[2,7],[3,7].	[2,5],[3,5],[4,5].
Row#1	= [1,3],[1,10],[2,7].	[1,8],[2,5],[3,5].	[2,3],[2,10],[3,7].	[2,8],[3,5],[4,5].
Row#2	= [1,6],[2,3],[2,10].	[2,3],[2,8],[3,5].	[2,6],[3,3],[3,10].	[3,3],[3,8],[4,5].
Row#3	= [1,9],[2,6],[3,3].	[2,5],[3,3],[3,8].	[2,9],[3,6],[4,3].	[3,5],[4,3],[4,8].
Row#4	= [2,3],[2,9],[3,6].	[2,8],[3,5],[4,3].	[3,3],[3,9],[4,6].	[3,8],[4,5],[5,3].
Row#5	= [2,6],[3,3],[3,9].	[3,3],[3,8],[4,5].	[3,6],[4,3],[4,9].	[4,3],[4,8],[5,5].

BinPacking MinCount_DP3D for "[count,size]=[5,3],[3,5],[2,7], Cap=10": 5
[rY][cX][dZ]
Row#0	= [1,0],[1,4].	[1,3],[2,3].
Row#1	= [1,2],[2,2].	[1,5],[2,4].

BinPacking MinCount_DP3D for "[count,size]=[1,2],[1,3],[1,4], Cap=5": 2
*/
#endif