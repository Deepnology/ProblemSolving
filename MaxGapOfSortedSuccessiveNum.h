#ifndef MAX_GAP_OF_SORTED_SUCCESSIVE_NUM_H
#define MAX_GAP_OF_SORTED_SUCCESSIVE_NUM_H
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include "Debug.h"
/*
Leetcode: Max Gap
http://blog.csdn.net/u012162613/article/details/41936569
Given an unsorted array, find the maximum difference between the successive elements in its sorted form.
Try to solve it in linear time/space.
Return 0 if the array contains less than 2 elements.
You may assume all elements in the array are non-negative integers and fit in the 32-bit signed integer range.

UseBucketSort:
Keep track of the min and max of each bucket range.
Loop thru all buckets and keep track of the max gap, which is equal to curBucketMin - prevBucketMax.
Since the average bucket range = ceil(range / (N - 1)), the max gap between any 2 successive elements after sorted should be no smaller than the average bucket range.
Since the range between the max and min element of a same bucket is no larger than the average bucket length, we know that the final max gap won't be chosen from 2 elements in the same buckets.
The potential answer of max gap should be chosen from 2 consecutive non-empty buckets.

See also BucketSort.h
*/
class MaxGapOfSortedSuccessiveNum
{
public:
	MaxGapOfSortedSuccessiveNum(){}
	~MaxGapOfSortedSuccessiveNum(){}

	int UseBucketSort(const std::vector<int> & v)
	{
		int N = v.size();
		if (N < 2)
			return 0;

		int minVal = INT_MAX;
		int maxVal = INT_MIN;
		for (const int & val : v)
		{
			minVal = std::min(minVal, val);
			maxVal = std::max(maxVal, val);
		}
		int range = maxVal - minVal;
		int avgBucketRange = range / N + 1;
		int bucketCount = range / avgBucketRange + 1;
		std::vector<std::pair<int, int>> buckets(bucketCount, { -1, -1 });//first: min, second: max
		std::vector<std::vector<int>> Buckets(bucketCount, std::vector<int>());//for debugging
		for (const int & val : v)
		{
			int idx = (val - minVal) / avgBucketRange;
			Buckets[idx].push_back(val);//for debugging
			if (buckets[idx].first == -1)
				buckets[idx].first = val;
			else
				buckets[idx].first = std::min(buckets[idx].first, val);
			buckets[idx].second = std::max(buckets[idx].second, val);
		}

		int maxGap = 0;
		int prevBucket = 0;
		for (int i = 1; i < bucketCount; ++i)
		{
			if (buckets[i].first == -1)
				continue;
			maxGap = std::max(maxGap, buckets[i].first - buckets[prevBucket].second);
			prevBucket = i;
		}

		Debug::Print2D<int>()(Buckets, false);
		std::cout << "min, max, avgBucketRange: " << minVal << ", " << maxVal << ", " << avgBucketRange << std::endl;
		std::cout << "buckets: " << Debug::ToStr1D<int>()(buckets) << std::endl;
		std::cout << "MaxGapOfSortedSuccessiveNum UseBucketSort for \"" << Debug::ToStr1D<int>()(v) << "\": " << maxGap << std::endl;
		return maxGap;
	}
};
/*
[rY][cX]
Row#0	= 3, 5,
Row#1	=  ,  ,
Row#2	=  ,  ,
Row#3	= 24,  ,
Row#4	= 27,  ,
Row#5	= 34,  ,
Row#6	= 41,  ,
Row#7	= 45,  ,
Row#8	=  ,  ,
Row#9	= 58, 62, 61
Row#10	= 67, 64,
Row#11	= 69,  ,
Row#12	= 78,  ,
Row#13	= 81,  ,

min, max, avgBucketRange: 3, 81, 6
buckets: [3,5], [-1,-1], [-1,-1], [24,24], [27,27], [34,34], [41,41], [45,45], [-1,-1], [58,62], [64,67], [69,69], [78,78], [81,81]
MaxGapOfSortedSuccessiveNum UseBucketSort for "41, 67, 34, 3, 69, 24, 78, 58, 62, 64, 5, 45, 81, 27, 61": 19
[rY][cX]
Row#0	= 1,  ,
Row#1	= 2,  ,
Row#2	= 3,  ,
Row#3	= 4, 4,
Row#4	= 5,  ,
Row#5	= 6,  ,
Row#6	= 7, 7, 7
Row#7	= 8, 8,
Row#8	= 9,  ,

min, max, avgBucketRange: 1, 9, 1
buckets: [1,1], [2,2], [3,3], [4,4], [5,5], [6,6], [7,7], [8,8], [9,9]
MaxGapOfSortedSuccessiveNum UseBucketSort for "7, 4, 3, 8, 2, 7, 1, 9, 6, 7, 5, 4, 8": 1
[rY][cX]
Row#0	= 1, 0
Row#1	= 3, 2
Row#2	= 4,
Row#3	= 7, 6
Row#4	= 9, 8
Row#5	= 10,
Row#6	=  ,
Row#7	= 15,
Row#8	= 17, 16
Row#9	= 19, 18

min, max, avgBucketRange: 0, 19, 2
buckets: [0,1], [2,3], [4,4], [6,7], [8,9], [10,10], [-1,-1], [15,15], [16,17], [18,19]
MaxGapOfSortedSuccessiveNum UseBucketSort for "15, 1, 9, 3, 19, 7, 0, 18, 4, 10, 8, 2, 6, 17, 16": 5
*/
#endif