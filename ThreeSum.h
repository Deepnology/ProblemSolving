/*Facebook*/
#ifndef _THREE_SUM_H
#define _THREE_SUM_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, Greedy: The 3-sum problem
Leetcode: 3Sum
Given an array S of n integers, are there elements a, b, c in S such that a + b + c = 0?
Find all unique triplets in the array which gives the sum of zero.
Note: The solution set must not contain duplicate triplets.
For example, given array S = [-1, 0, 1, 2, -1, -4],
A solution set is:
[
  [-1, 0, 1],
  [-1, -1, 2]
]
*/
class ThreeSum
{
public:
	ThreeSum(){}
	~ThreeSum(){}

	std::vector<std::vector<int>> FindAll_SortGreedy(std::vector<int> && num, int target) //O(N^2) time
	{
		int N = num.size();
		std::sort(std::begin(num), std::end(num));
		std::vector<std::vector<int>> res;

		for (int i = 0; i < N - 2; ++i)
		{
			if (i > 0 && num[i - 1] == num[i])
				continue;//skip repeats

			//start, end are on the right side of index
			int start = i + 1;
			int end = N - 1;
			while (start < end)
			{
				int sum = num[i] + num[start] + num[end];
				if (sum < target)
					++start;
				else if (sum > target)
					--end;
				else
				{
					res.push_back(std::vector<int>({num[i], num[start], num[end]}));
					do
					{
						++start;
					} while (start < end && num[start - 1] == num[start]);//skip repeats
					do
					{
						--end;
					} while (start < end && num[end] == num[end + 1]);//skip repeats
				}
			}
		}

		std::cout << "ThreeSum FindAll_SortGreedy for " << target << " in \"" << Debug::ToStr1D<int>()(num) << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}


    std::vector<std::vector<int>> FindAll_WithoutSort(std::vector<int> && num, int target) //O(N^2) time
    {
        int N = num.size();

        //1. partition num to group same entries together
        std::unordered_map<int,int> count;//<entry,freq>
        for (int i = 0; i < N; ++i)
            ++count[num[i]];
        int i = 0;
        for (const auto & p : count)
        {
            int curCount = p.second;
            while (curCount--)
                num[i++] = p.first;
        }

        //2. fix each num[i], perform two sum on num[i+1:N-1]
        std::vector<std::vector<int>> res;
        for (i = 0; i < N-2; ++i)
        {
            if (i > 0 && num[i] == num[i-1]) continue;

            //now fix num[i], find two sum for target-num[i] in num[i+1:N-1]
            int tgt = target - num[i];
            std::unordered_set<int> visit;
            std::unordered_set<int> used;
            for (int j = i+1; j < N; ++j)
            {
                if (visit.count(tgt-num[j]) && !used.count(tgt-num[j]))//find a "tgt-num[j]" from already visited nums
                {
                    std::vector<int> v({num[i], num[j], tgt-num[j]});
                    std::sort(v.begin(), v.end());
                    res.push_back(v);
                    used.insert(num[j]);
                    used.insert(tgt-num[j]);
                }
                visit.insert(num[j]);
            }
        }

        std::cout << "ThreeSum FindAll_WithoutSort for " << target << " in \"" << Debug::ToStr1D<int>()(num) << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
        return res;
    }

	std::vector<std::vector<int>> FindAllAllowRepeatOnce(std::vector<int> && num, int target)
	{
		int N = num.size();
		std::sort(std::begin(num), std::end(num));
		std::vector<std::vector<int>> res;

		for (int i = 0; i < N - 1; ++i)
		{
			if (i > 0 && num[i - 1] == num[i]) continue;
			int start = i;
			int end = N - 1;
			while (start <= end)
			{
				int sum = num[i] + num[start] + num[end];
				if (sum < target)
					++start;
				else if (sum > target)
					--end;
				else
				{
					if (i == start && start == end) break;
					res.push_back(std::vector<int>({num[i], num[start], num[end]}));
					do
					{
						++start;
					} while (start <= end && num[start - 1] == num[start]);
					do
					{
						--end;
					} while (start <= end && num[end] == num[end + 1]);
				}
			}
		}

		std::cout << "ThreeSum FindAllAllowRepeatOnce for " << target << " in \"" << Debug::ToStr1D<int>()(num) << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
	std::vector<std::vector<int>> FindAllAllowRepeatTwice(std::vector<int> && num, int target)
	{
		int N = num.size();
		std::sort(std::begin(num), std::end(num));
		std::vector<std::vector<int>> res;

		for (int i = 0; i < N; ++i)
		{
			if (i > 0 && num[i - 1] == num[i]) continue;
			int start = i;
			int end = N - 1;
			while (start <= end)
			{
				int sum = num[i] + num[start] + num[end];
				if (sum < target)
					++start;
				else if (sum > target)
					--end;
				else
				{
					res.push_back(std::vector<int>({num[i], num[start], num[end]}));
					do
					{
						++start;
					} while (start <= end && num[start - 1] == num[start]);
					do
					{
						--end;
					} while (start <= end && num[end] == num[end + 1]);
				}
			}
		}

		std::cout << "ThreeSum FindAllAllowRepeatTwice for " << target << " in \"" << Debug::ToStr1D<int>()(num) << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}


};
/*
ThreeSum FindAll_SortGreedy for 0 in "-4, -1, -1, 0, 1, 2": [-1,-1,2], [-1,0,1]
ThreeSum FindAll_WithoutSort for 0 in "-4, 2, 1, 0, -1, -1": [-1,-1,2], [-1,0,1]
ThreeSum FindAllAllowRepeatOnce for 0 in "-4, -1, -1, 0, 1, 2": [-4,2,2], [-1,-1,2], [-1,0,1]
ThreeSum FindAllAllowRepeatTwice for 0 in "-4, -1, -1, 0, 1, 2": [-4,2,2], [-1,-1,2], [-1,0,1], [0,0,0]
ThreeSum FindAllAllowRepeatOnce for 3 in "1":
ThreeSum FindAllAllowRepeatTwice for 3 in "1": [1,1,1]
ThreeSum FindAllAllowRepeatOnce for 3 in "1, 1": [1,1,1]
ThreeSum FindAllAllowRepeatTwice for 3 in "1, 1": [1,1,1]
ThreeSum FindAllAllowRepeatOnce for 3 in "1, 1, 1": [1,1,1]
ThreeSum FindAllAllowRepeatTwice for 3 in "1, 1, 1": [1,1,1]
ThreeSum FindAllAllowRepeatOnce for 3 in "1, 1, 1, 1": [1,1,1]
ThreeSum FindAllAllowRepeatTwice for 3 in "1, 1, 1, 1": [1,1,1]
ThreeSum FindAllAllowRepeatOnce for 14 in "2, 5, 6, 7, 8, 8, 8": [2,5,7], [2,6,6]
ThreeSum FindAllAllowRepeatTwice for 14 in "2, 5, 6, 7, 8, 8, 8": [2,5,7], [2,6,6]
ThreeSum FindAllAllowRepeatOnce for 9 in "1, 3, 3, 4, 6, 7, 7": [1,1,7], [1,4,4], [3,3,3]
ThreeSum FindAllAllowRepeatTwice for 9 in "1, 3, 3, 4, 6, 7, 7": [1,1,7], [1,4,4], [3,3,3]
ThreeSum FindAllAllowRepeatOnce for 19 in "0, 1, 3, 3, 3, 7, 7":
ThreeSum FindAllAllowRepeatTwice for 19 in "0, 1, 3, 3, 3, 7, 7":
ThreeSum FindAllAllowRepeatOnce for 6 in "0, 1, 2, 2, 4, 4, 7": [0,2,4], [1,1,4], [2,2,2]
ThreeSum FindAllAllowRepeatTwice for 6 in "0, 1, 2, 2, 4, 4, 7": [0,2,4], [1,1,4], [2,2,2]
ThreeSum FindAllAllowRepeatOnce for 3 in "3, 4, 4, 6, 6, 6, 6":
ThreeSum FindAllAllowRepeatTwice for 3 in "3, 4, 4, 6, 6, 6, 6":
ThreeSum FindAllAllowRepeatOnce for 6 in "1, 3, 4, 6, 7, 7, 7": [1,1,4]
ThreeSum FindAllAllowRepeatTwice for 6 in "1, 3, 4, 6, 7, 7, 7": [1,1,4]
ThreeSum FindAllAllowRepeatOnce for 13 in "0, 1, 2, 4, 7, 7, 8": [1,4,8], [2,4,7]
ThreeSum FindAllAllowRepeatTwice for 13 in "0, 1, 2, 4, 7, 7, 8": [1,4,8], [2,4,7]
ThreeSum FindAllAllowRepeatOnce for 3 in "0, 2, 4, 4, 6, 7, 7":
ThreeSum FindAllAllowRepeatTwice for 3 in "0, 2, 4, 4, 6, 7, 7":
ThreeSum FindAllAllowRepeatOnce for 10 in "0, 1, 1, 2, 2, 2, 5": [0,5,5]
ThreeSum FindAllAllowRepeatTwice for 10 in "0, 1, 1, 2, 2, 2, 5": [0,5,5]
ThreeSum FindAllAllowRepeatOnce for 5 in "2, 2, 4, 6, 6, 7, 8":
ThreeSum FindAllAllowRepeatTwice for 5 in "2, 2, 4, 6, 6, 7, 8":
*/

#endif