#ifndef ALL_SUB_ARRAY_PARTITIONS_H
#define ALL_SUB_ARRAY_PARTITIONS_H
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "Debug.h"
/*
A sub-array partition of an array is to insert (at least 0, at most N-1) break points in between elements of an array so that the array can be partitioned into one or more sub-arrays.
Write a program to generate all possible sub-array partitions of a given integer array.

See also Combinations.h, MinEqualSumSubArrPartition.h
*/
class AllSubArrayPartitions
{
public:
	AllSubArrayPartitions(){}
	~AllSubArrayPartitions(){}

	void Generate(const std::vector<int> & v)
	{
		int N = v.size();

		/*
		1. find out all break point sets among N numbers
		a break point can be 1 to N-1
		*/
		std::vector<int> path;
		std::vector<std::vector<int> > breakPoints;
		for (int i = 0; i < N; ++i)
		{
			this->FixRecur_NoRepeats(N - 1, i, 1, path, breakPoints);//generate all possible combinations of numBreak numbers out of breakIdx[1...N-1]
		}
		std::cout << "all break point sets for \"" << N << "\" numbers (all possible combinations out of 1..." << N - 1 << "):" << std::endl;
		Debug::Print2D<int>()(breakPoints);

		/*2. for each break point set, partition v into separated vectors*/
		std::vector<std::vector<std::vector<int> > > res;
		int M = breakPoints.size();
		for (int i = 0; i < M; ++i)
		{
			res.push_back(this->InsertBreakPoints(breakPoints[i], v));
		}

		std::cout << "AllSubArrayPartitions for \"" << Debug::ToStr1D<int>()(v) << "\": " << std::endl;
		Debug::Print3D<int>()(res, false);
	}

private:
	//see also Combinations.h
	void FixRecur_NoRepeats(int n, int count, int begin, std::vector<int> & path, std::vector<std::vector<int> > & res)
	{
		if (count == 0)
		{
			res.push_back(path);
			return;
		}

		int end = n - count + 1;
		for (int cur = begin; cur <= end; ++cur)
		{
			path.push_back(cur);
			this->FixRecur_NoRepeats(n, count - 1, cur + 1, path, res);//cur+1 for NoRepeats
			path.pop_back();
		}
	}

	std::vector<std::vector<int> > InsertBreakPoints(const std::vector<int> & breakPoints, const std::vector<int> & v)
	{
		std::vector<std::vector<int> > res;
		res.push_back(std::vector<int>());
		int N = v.size();
		int i = 0;
		int M = breakPoints.size();
		int j = 0;
		while (i < N)
		{
			res.back().push_back(v[i]);
			++i;
			/*create a new vector when the next index is a break point*/
			if (j < M && breakPoints[j] == i)
			{
				res.push_back(std::vector<int>());
				++j;
			}
		}
		return res;
	}
};
/*
all break point sets for "6" numbers (all possible combinations out of 1...5):
[cX][rY]
Row#0	=  , 1, 2, 3, 4, 5, 1, 1, 1, 1, 2, 2, 2, 3, 3, 4, 1, 1, 1, 1, 1, 1, 2, 2, 2, 3, 1, 1, 1, 1, 2, 1
Row#1	=  ,  ,  ,  ,  ,  , 2, 3, 4, 5, 3, 4, 5, 4, 5, 5, 2, 2, 2, 3, 3, 4, 3, 3, 4, 4, 2, 2, 2, 3, 3, 2
Row#2	=  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  , 3, 4, 5, 4, 5, 5, 4, 5, 5, 5, 3, 3, 4, 4, 4, 3
Row#3	=  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  , 4, 5, 5, 5, 5, 4
Row#4	=  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  , 5

AllSubArrayPartitions for "1, 2, 3, 4, 5, 6":
[rY][cX][dZ]
Row#0	= 1,2,3,4,5,6.	 , , , , , .	 , , , , , .	 , , , , , .	 , , , , , .	 , , , , , .
Row#1	= 1, , , , , .	2,3,4,5,6, .	 , , , , , .	 , , , , , .	 , , , , , .	 , , , , , .
Row#2	= 1,2, , , , .	3,4,5,6, , .	 , , , , , .	 , , , , , .	 , , , , , .	 , , , , , .
Row#3	= 1,2,3, , , .	4,5,6, , , .	 , , , , , .	 , , , , , .	 , , , , , .	 , , , , , .
Row#4	= 1,2,3,4, , .	5,6, , , , .	 , , , , , .	 , , , , , .	 , , , , , .	 , , , , , .
Row#5	= 1,2,3,4,5, .	6, , , , , .	 , , , , , .	 , , , , , .	 , , , , , .	 , , , , , .
Row#6	= 1, , , , , .	2, , , , , .	3,4,5,6, , .	 , , , , , .	 , , , , , .	 , , , , , .
Row#7	= 1, , , , , .	2,3, , , , .	4,5,6, , , .	 , , , , , .	 , , , , , .	 , , , , , .
Row#8	= 1, , , , , .	2,3,4, , , .	5,6, , , , .	 , , , , , .	 , , , , , .	 , , , , , .
Row#9	= 1, , , , , .	2,3,4,5, , .	6, , , , , .	 , , , , , .	 , , , , , .	 , , , , , .
Row#10	= 1,2, , , , .	3, , , , , .	4,5,6, , , .	 , , , , , .	 , , , , , .	 , , , , , .
Row#11	= 1,2, , , , .	3,4, , , , .	5,6, , , , .	 , , , , , .	 , , , , , .	 , , , , , .
Row#12	= 1,2, , , , .	3,4,5, , , .	6, , , , , .	 , , , , , .	 , , , , , .	 , , , , , .
Row#13	= 1,2,3, , , .	4, , , , , .	5,6, , , , .	 , , , , , .	 , , , , , .	 , , , , , .
Row#14	= 1,2,3, , , .	4,5, , , , .	6, , , , , .	 , , , , , .	 , , , , , .	 , , , , , .
Row#15	= 1,2,3,4, , .	5, , , , , .	6, , , , , .	 , , , , , .	 , , , , , .	 , , , , , .
Row#16	= 1, , , , , .	2, , , , , .	3, , , , , .	4,5,6, , , .	 , , , , , .	 , , , , , .
Row#17	= 1, , , , , .	2, , , , , .	3,4, , , , .	5,6, , , , .	 , , , , , .	 , , , , , .
Row#18	= 1, , , , , .	2, , , , , .	3,4,5, , , .	6, , , , , .	 , , , , , .	 , , , , , .
Row#19	= 1, , , , , .	2,3, , , , .	4, , , , , .	5,6, , , , .	 , , , , , .	 , , , , , .
Row#20	= 1, , , , , .	2,3, , , , .	4,5, , , , .	6, , , , , .	 , , , , , .	 , , , , , .
Row#21	= 1, , , , , .	2,3,4, , , .	5, , , , , .	6, , , , , .	 , , , , , .	 , , , , , .
Row#22	= 1,2, , , , .	3, , , , , .	4, , , , , .	5,6, , , , .	 , , , , , .	 , , , , , .
Row#23	= 1,2, , , , .	3, , , , , .	4,5, , , , .	6, , , , , .	 , , , , , .	 , , , , , .
Row#24	= 1,2, , , , .	3,4, , , , .	5, , , , , .	6, , , , , .	 , , , , , .	 , , , , , .
Row#25	= 1,2,3, , , .	4, , , , , .	5, , , , , .	6, , , , , .	 , , , , , .	 , , , , , .
Row#26	= 1, , , , , .	2, , , , , .	3, , , , , .	4, , , , , .	5,6, , , , .	 , , , , , .
Row#27	= 1, , , , , .	2, , , , , .	3, , , , , .	4,5, , , , .	6, , , , , .	 , , , , , .
Row#28	= 1, , , , , .	2, , , , , .	3,4, , , , .	5, , , , , .	6, , , , , .	 , , , , , .
Row#29	= 1, , , , , .	2,3, , , , .	4, , , , , .	5, , , , , .	6, , , , , .	 , , , , , .
Row#30	= 1,2, , , , .	3, , , , , .	4, , , , , .	5, , , , , .	6, , , , , .	 , , , , , .
Row#31	= 1, , , , , .	2, , , , , .	3, , , , , .	4, , , , , .	5, , , , , .	6, , , , , .
*/
#endif