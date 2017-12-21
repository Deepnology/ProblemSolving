#ifndef BUCKET_SORT_H
#define BUCKET_SORT_H
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "Debug.h"
/*
http://www.geeksforgeeks.org/bucket-sort-2/
http://blog.csdn.net/u012162613/article/details/41936569
AKA Bin Sort
Bucket sort is mainly useful when input is uniformly distributed over a range.
Partition the array into a finite number (we choose n+1) of buckets, and then sort each bucket individually.
This gives a time of O(n+m), where n is the number of items and m is the number of distinct items.
Bucket sort can be seen as a generalization of counting sort; 
in fact, if each bucket has size 1 then bucket sort degenerates to counting sort.

See also MaxGapOfSortedSuccessiveNum.h
*/
class BucketSort
{
public:
	BucketSort(){}
	~BucketSort(){}

	void GO(int A[], int n, int min, int max)
	{
		std::string before = Debug::ToStr1D<int>()(A, n);

		//1. prepare a buckets array which can hold some number of buckets
		//the average bucket range is range / n + 1
		//the total bucket count needed is range / avgBucketRange + 1
		int range = max - min;
		int avgBucketRange = range / n + 1;
		int bucketCount = range / avgBucketRange + 1;
		std::vector<std::vector<int>> buckets(bucketCount, std::vector<int>());

		//2. assign each number from A to its target bucket
		for (int i = 0; i < n; ++i)
		{
			int idx = (A[i] - min) / avgBucketRange;
			buckets[idx].push_back(A[i]);
		}

		//3. sort each bucket
		for (int i = 0; i < bucketCount; ++i)
		{
			std::sort(buckets[i].begin(), buckets[i].end());
		}

		//4. concatenate all the sorted buckets back to A
		int idx = 0;
		for (int i = 0; i < bucketCount; ++i)
		{
			int M = buckets[i].size();
			for (int j = 0; j < M; ++j)
			{
				A[idx++] = buckets[i][j];
			}
		}

		Debug::Print2D<int>()(buckets, false);
		std::cout << "AvgBucketRange: " << avgBucketRange << std::endl;
		std::cout << "BucketSort for \"" << before << "\" is: " << Debug::ToStr1D<int>()(A, n) << std::endl;
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
Row#9	= 58, 61, 62
Row#10	= 64, 67,
Row#11	= 69,  ,
Row#12	= 78,  ,
Row#13	= 81,  ,

AvgBucketRange: 6
BucketSort for "41, 67, 34, 3, 69, 24, 78, 58, 62, 64, 5, 45, 81, 27, 61" is: 3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 81
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

AvgBucketRange: 1
BucketSort for "7, 4, 3, 8, 2, 7, 1, 9, 6, 7, 5, 4, 8" is: 1, 2, 3, 4, 4, 5, 6, 7, 7, 7, 8, 8, 9
*/
#endif