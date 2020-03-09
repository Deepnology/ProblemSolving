#ifndef _MAX_PRICE_CUTTING_2_H
#define _MAX_PRICE_CUTTING_2_H
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include "Debug.h"
/*
AIG Quantitative Testing
Given an array of rod lengths, a value of costPerCut, a value of salePrice per unit length.
You can cut all the rods as many times as you want, then you want to sell all those rods with same lengths and maximize the profit.
totalProfit = totalUniformRods * saleLength * salePrice - totalCuts * costPerCut
where
 totalUniformRods: the number of rods with same lengths
 saleLength: the uniform length of all sellable rods
 salePrice: the price per sellable rod
 totalCuts: the number of cuts made
 costPerCut: the cost per cut

Return the max profit you can make by cutting and selling the rods.
 */
class MaxPriceCutting2
{
public:
    MaxPriceCutting2(){}
    ~MaxPriceCutting2(){}

    int DFSRecur(int costPerCut, int salePrice, std::vector<int> && lengths) // 8/11 test cases passed
    {
        std::sort(lengths.begin(), lengths.end());
        int maxLen = lengths.back();
        int maxProfit = 0;
        for (int curLen = maxLen; curLen > 0; --curLen)
        {
            int cur = std::lower_bound(lengths.begin(), lengths.end(), curLen) - lengths.begin();
            maxProfit = std::max(maxProfit, recur(lengths, cur, curLen, costPerCut, salePrice));
        }
        std::cout << "MaxPriceCutting2 DFSRecur for \"" << Debug::ToStr1D<int>()(lengths) << "\", costPerCut=" << costPerCut << ", salePrice=" << salePrice << ": " << maxProfit << std::endl;
        return maxProfit;
    }
    int recur(std::vector<int> & lengths, int cur, int len, int costPerCut, int salePrice)
    {
        int N = lengths.size();
        if (cur == N) return 0;
        //now lengths[cur] must be >= len
        int numRods = lengths[cur] / len;
        int numCuts = numRods - (lengths[cur]%len==0 ? 1 : 0);
        int curPrice = salePrice * numRods * len - costPerCut * numCuts;
        return curPrice + recur(lengths, cur+1, len, costPerCut, salePrice);
    }
};
#endif
