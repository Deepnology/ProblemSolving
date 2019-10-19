#ifndef DICE_COMBINATION_SUM_H
#define DICE_COMBINATION_SUM_H
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include "Debug.h"
/*
Leetcode: Number of Dice Rolls With Target Sum
http://www.geeksforgeeks.org/dice-throw-problem/
Given n dices with m faces, numbered from 1 to m.
Count the number of ways to get sum X.
X is the summation of values on each face when all the dices are thrown.

DP2D: O(diceCount*faceCount*targetSum) time, O(targetSum*diceCount) space
*/
class DiceCombinationSum
{
public:
	DiceCombinationSum(){}
	~DiceCombinationSum(){}

	int NumOfWays_DP2D(int diceCount, int faceCount, int targetSum)
	{
		if (diceCount == 0 || faceCount < 2 || targetSum == 0 || diceCount * faceCount < targetSum)
			return 0;

		std::vector<std::vector<int> > dp(targetSum + 1, std::vector<int>(diceCount + 1, 0));
		for (int sum = 1; sum <= faceCount && sum <= targetSum; ++sum)
			dp[sum][1] = 1;//only 1 way for 1 dice

		for (int sum = 1; sum <= targetSum; ++sum)
		{
			for (int dice = 2; dice <= diceCount; ++dice)
			{
				for (int face = 1; face <= faceCount && face < sum; ++face)
				{
					dp[sum][dice] += dp[sum - face][dice - 1];
					dp[sum][dice] %= 1000000007;
				}
			}
		}

		Debug::Print2D<int>()(dp, false);
		std::cout << "DiceCombinationSum NumOfWays_DP2D for \"diceCount=" << diceCount << "\", \"faceCount=\"" << faceCount << "\", \"targetSum=" << targetSum << "\": " << dp[targetSum][diceCount] << std::endl;
		return dp[targetSum][diceCount];
	}

	int NumOfWays_Recur(int diceCount, int faceCount, int targetSum)
    {
	    int res = recur(diceCount, faceCount, targetSum, 0, 0);
        std::cout << "DiceCombinationSum NumOfWays_Recur for \"diceCount=" << diceCount << "\", \"faceCount=\"" << faceCount << "\", \"targetSum=" << targetSum << "\": " << res << std::endl;
	    return res;
    }
    int recur(int diceCount, int faceCount, int targetSum, int curDice, int curSum)
    {
        if (curDice == diceCount)
        {
            if (curSum == targetSum)
                return 1;
            return 0;
        }
        int res = 0;
        for (int face = 1; face <= faceCount && face <= targetSum-curSum; ++face)
        {
            res += recur(diceCount, faceCount, targetSum, curDice+1, curSum+face);
        }
        return res;
    }
};
/*
[rY][cX]
Row#0	= 0, 0, 0
Row#1	= 0, 1, 0
Row#2	= 0, 1, 1
Row#3	= 0, 1, 2
Row#4	= 0, 1, 3
Row#5	= 0, 1, 4
Row#6	= 0, 1, 5
Row#7	= 0, 0, 6
Row#8	= 0, 0, 5
Row#9	= 0, 0, 4
Row#10	= 0, 0, 3

DiceCombinationSum NumOfWays_DP2D for "diceCount=2", "faceCount="6", "targetSum=10": 3
[rY][cX]
Row#0	= 0, 0, 0
Row#1	= 0, 1, 0
Row#2	= 0, 1, 1
Row#3	= 0, 1, 2
Row#4	= 0, 1, 3
Row#5	= 0, 1, 4

DiceCombinationSum NumOfWays_DP2D for "diceCount=2", "faceCount="6", "targetSum=5": 4
[rY][cX]
Row#0	= 0, 0, 0
Row#1	= 0, 1, 0

DiceCombinationSum NumOfWays_DP2D for "diceCount=2", "faceCount="6", "targetSum=1": 0

DiceCombinationSum NumOfWays_Recur for "diceCount=2", "faceCount="6", "targetSum=10": 3
DiceCombinationSum NumOfWays_Recur for "diceCount=2", "faceCount="6", "targetSum=5": 4
DiceCombinationSum NumOfWays_Recur for "diceCount=2", "faceCount="6", "targetSum=1": 0
*/
#endif