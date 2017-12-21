#ifndef GENERIC_PARTITION_H
#define gENERIC_PARTITION_H
#include "Debug.h"
/*
Bloomberg
Given an integer array and given an euqivalence function.
Partition the array such that integers with same results appear together (classification).
ex:
bool f(int a, int b)
{
	return a % 2 == b % 2;
}
bool f2(int a, int b)
{
	return a % 3 == b % 3;
}
*/
class GenericPartition
{
public:
	GenericPartition() {}

	void GroupSame(std::vector<int> & v, std::function<bool(int a, int b)> f)
	{
		std::string before = Debug::ToStr1D<int>()(v);
		int N = v.size();
		int begin = 0;
		int end = N - 1;
		while (begin < N)
			begin = Partition(v, begin, end, f);

		std::cout << "GenericPartition GroupSame for \"" << before << "\": " << Debug::ToStr1D<int>()(v) << std::endl;
	}
private:
	int Partition(std::vector<int> & v, int begin, int end, std::function<bool(int a, int b)> f)
	{
		int pivot = (begin + end) / 2;
		int pivotVal = v[pivot];
		std::swap(v[pivot], v[end]);
		int i = begin;
		int j = end - 1;
		while (i <= j)
		{
			if (f(v[i], pivotVal))
				++i;
			else if (!f(v[j], pivotVal))
				--j;
			else
				std::swap(v[i++], v[j--]);
		}
		std::swap(v[i], v[end]);
		++i;
		//now completed [begin:i), and i points to the first element of second group
		std::cout << begin << "," << end << ": completed [" << begin << ":" << i << "): \"" << Debug::ToStr1D<int>()(v) << "\"" << std::endl;
		return i;
	}
};
/*
0,0: completed [0:1): "1"
GenericPartition GroupSame for "1": 1
0,1: completed [0:2): "1, 1"
GenericPartition GroupSame for "1, 1": 1, 1
0,1: completed [0:1): "1, 2"
1,1: completed [1:2): "1, 2"
GenericPartition GroupSame for "1, 2": 1, 2
0,2: completed [0:3): "1, 1, 1"
GenericPartition GroupSame for "1, 1, 1": 1, 1, 1
0,2: completed [0:1): "2, 1, 1"
1,2: completed [1:3): "2, 1, 1"
GenericPartition GroupSame for "1, 2, 1": 2, 1, 1
0,2: completed [0:2): "2, 2, 1"
2,2: completed [2:3): "2, 2, 1"
GenericPartition GroupSame for "1, 2, 2": 2, 2, 1
0,2: completed [0:2): "1, 1, 2"
2,2: completed [2:3): "1, 1, 2"
GenericPartition GroupSame for "1, 1, 2": 1, 1, 2
0,2: completed [0:1): "2, 3, 1"
1,2: completed [1:2): "2, 3, 1"
2,2: completed [2:3): "2, 3, 1"
GenericPartition GroupSame for "1, 2, 3": 2, 3, 1
0,9: completed [0:5): "1, 9, 3, 7, 5, 6, 4, 8, 2, 10"
5,9: completed [5:10): "1, 9, 3, 7, 5, 6, 4, 10, 2, 8"
GenericPartition GroupSame for "1, 2, 3, 4, 5, 6, 7, 8, 9, 10": 1, 9, 3, 7, 5, 6, 4, 10, 2, 8
0,9: completed [0:3): "8, 2, 5, 4, 10, 6, 7, 1, 9, 3"
3,9: completed [3:7): "8, 2, 5, 4, 10, 1, 7, 6, 9, 3"
7,9: completed [7:10): "8, 2, 5, 4, 10, 1, 7, 6, 3, 9"
GenericPartition GroupSame for "1, 2, 3, 4, 5, 6, 7, 8, 9, 10": 8, 2, 5, 4, 10, 1, 7, 6, 3, 9
0,8: completed [0:5): "1, 7, 3, 9, 5, 6, 2, 8, 4"
5,8: completed [5:9): "1, 7, 3, 9, 5, 6, 4, 8, 2"
GenericPartition GroupSame for "1, 2, 3, 4, 5, 6, 7, 8, 9": 1, 7, 3, 9, 5, 6, 4, 8, 2
0,8: completed [0:3): "8, 2, 5, 4, 9, 6, 7, 1, 3"
3,8: completed [3:6): "8, 2, 5, 3, 9, 6, 7, 1, 4"
6,8: completed [6:9): "8, 2, 5, 3, 9, 6, 7, 4, 1"
GenericPartition GroupSame for "1, 2, 3, 4, 5, 6, 7, 8, 9": 8, 2, 5, 3, 9, 6, 7, 4, 1

0,19: completed [0:4): "2, 8, 8, 8, 10, 7, 4, 10, 3, 4, 1, 3, 10, 1, 1, 6, 10, 9, 10, 6"
4,19: completed [4:9): "2, 8, 8, 8, 9, 6, 6, 3, 3, 4, 1, 4, 10, 1, 1, 7, 10, 10, 10, 10"
9,19: completed [9:20): "2, 8, 8, 8, 9, 6, 6, 3, 3, 4, 1, 4, 10, 1, 10, 7, 10, 10, 10, 1"
GenericPartition GroupSame for "9, 4, 10, 6, 8, 7, 8, 10, 3, 8, 1, 3, 10, 1, 1, 6, 10, 2, 10, 4": 2, 8, 8, 8, 9, 6, 6, 3, 3, 4, 1, 4, 10, 1, 10, 7, 10, 10, 10, 1
0,19: completed [0:6): "10, 4, 4, 1, 7, 10, 2, 8, 5, 8, 2, 8, 8, 6, 5, 9, 5, 8, 9, 8"
6,19: completed [6:17): "10, 4, 4, 1, 7, 10, 2, 8, 5, 8, 2, 8, 8, 8, 5, 5, 8, 6, 9, 9"
17,19: completed [17:20): "10, 4, 4, 1, 7, 10, 2, 8, 5, 8, 2, 8, 8, 8, 5, 5, 8, 6, 9, 9"
GenericPartition GroupSame for "9, 8, 2, 1, 8, 7, 2, 8, 5, 10, 4, 8, 8, 6, 5, 9, 5, 4, 10, 8": 10, 4, 4, 1, 7, 10, 2, 8, 5, 8, 2, 8, 8, 8, 5, 5, 8, 6, 9, 9
0,19: completed [0:10): "1, 1, 10, 10, 4, 7, 10, 10, 1, 4, 5, 2, 5, 3, 8, 6, 9, 2, 8, 8"
10,19: completed [10:17): "1, 1, 10, 10, 4, 7, 10, 10, 1, 4, 5, 2, 5, 8, 8, 2, 8, 6, 3, 9"
17,19: completed [17:20): "1, 1, 10, 10, 4, 7, 10, 10, 1, 4, 5, 2, 5, 8, 8, 2, 8, 6, 9, 3"
GenericPartition GroupSame for "9, 1, 10, 10, 6, 7, 10, 8, 3, 4, 5, 2, 5, 1, 10, 4, 1, 2, 8, 8": 1, 1, 10, 10, 4, 7, 10, 10, 1, 4, 5, 2, 5, 8, 8, 2, 8, 6, 9, 3
0,19: completed [0:4): "7, 4, 10, 1, 3, 9, 8, 8, 2, 8, 8, 3, 5, 6, 8, 8, 9, 8, 9, 9"
4,19: completed [4:11): "7, 4, 10, 1, 3, 9, 9, 9, 6, 9, 3, 8, 5, 2, 8, 8, 8, 8, 8, 8"
11,19: completed [11:20): "7, 4, 10, 1, 3, 9, 9, 9, 6, 9, 3, 8, 5, 2, 8, 8, 8, 8, 8, 8"
GenericPartition GroupSame for "7, 6, 8, 9, 3, 9, 8, 8, 2, 1, 10, 3, 5, 4, 8, 8, 9, 8, 9, 8": 7, 4, 10, 1, 3, 9, 9, 9, 6, 9, 3, 8, 5, 2, 8, 8, 8, 8, 8, 8
0,19: completed [0:5): "2, 5, 5, 8, 5, 3, 7, 7, 9, 10, 3, 9, 1, 4, 3, 6, 4, 7, 6, 7"
5,19: completed [5:13): "2, 5, 5, 8, 5, 7, 7, 7, 4, 10, 4, 7, 1, 3, 3, 6, 9, 3, 6, 9"
13,19: completed [13:20): "2, 5, 5, 8, 5, 7, 7, 7, 4, 10, 4, 7, 1, 3, 3, 6, 9, 3, 6, 9"
GenericPartition GroupSame for "6, 4, 10, 7, 7, 3, 8, 7, 9, 5, 3, 9, 1, 5, 3, 2, 4, 7, 6, 5": 2, 5, 5, 8, 5, 7, 7, 7, 4, 10, 4, 7, 1, 3, 3, 6, 9, 3, 6, 9
0,19: completed [0:5): "9, 3, 3, 6, 9, 7, 5, 8, 2, 1, 5, 10, 7, 1, 2, 10, 2, 8, 8, 5"
5,19: completed [5:11): "9, 3, 3, 6, 9, 7, 10, 1, 10, 1, 7, 2, 5, 8, 2, 5, 2, 8, 8, 5"
11,19: completed [11:20): "9, 3, 3, 6, 9, 7, 10, 1, 10, 1, 7, 2, 5, 8, 2, 5, 2, 8, 8, 5"
GenericPartition GroupSame for "9, 1, 3, 2, 5, 7, 5, 8, 6, 9, 5, 10, 7, 1, 2, 10, 2, 8, 8, 3": 9, 3, 3, 6, 9, 7, 10, 1, 10, 1, 7, 2, 5, 8, 2, 5, 2, 8, 8, 5
0,19: completed [0:4): "8, 2, 8, 8, 10, 9, 9, 9, 4, 4, 10, 9, 7, 10, 7, 7, 7, 6, 9, 1"
4,19: completed [4:10): "8, 2, 8, 8, 9, 9, 9, 9, 6, 9, 10, 1, 7, 10, 7, 7, 7, 4, 10, 4"
10,19: completed [10:20): "8, 2, 8, 8, 9, 9, 9, 9, 6, 9, 10, 1, 7, 10, 4, 7, 7, 4, 10, 7"
GenericPartition GroupSame for "9, 2, 8, 1, 10, 8, 9, 9, 4, 8, 10, 9, 7, 10, 7, 7, 7, 6, 9, 4": 8, 2, 8, 8, 9, 9, 9, 9, 6, 9, 10, 1, 7, 10, 4, 7, 7, 4, 10, 7
0,19: completed [0:10): "10, 7, 10, 4, 10, 4, 7, 7, 7, 10, 3, 3, 5, 8, 2, 2, 3, 9, 6, 9"
10,19: completed [10:14): "10, 7, 10, 4, 10, 4, 7, 7, 7, 10, 2, 8, 5, 2, 9, 3, 3, 9, 6, 3"
14,19: completed [14:20): "10, 7, 10, 4, 10, 4, 7, 7, 7, 10, 2, 8, 5, 2, 9, 3, 3, 9, 6, 3"
GenericPartition GroupSame for "6, 9, 8, 3, 3, 9, 7, 7, 7, 10, 10, 4, 5, 10, 2, 2, 3, 7, 10, 4": 10, 7, 10, 4, 10, 4, 7, 7, 7, 10, 2, 8, 5, 2, 9, 3, 3, 9, 6, 3
0,19: completed [0:8): "10, 1, 7, 1, 1, 4, 1, 10, 6, 2, 5, 3, 3, 5, 5, 9, 3, 6, 9, 8"
8,19: completed [8:13): "10, 1, 7, 1, 1, 4, 1, 10, 5, 2, 5, 8, 5, 3, 6, 9, 3, 6, 9, 3"
13,19: completed [13:20): "10, 1, 7, 1, 1, 4, 1, 10, 5, 2, 5, 8, 5, 3, 6, 9, 3, 6, 9, 3"
GenericPartition GroupSame for "10, 9, 3, 3, 3, 2, 8, 1, 6, 10, 5, 1, 1, 5, 5, 9, 7, 6, 1, 4": 10, 1, 7, 1, 1, 4, 1, 10, 5, 2, 5, 8, 5, 3, 6, 9, 3, 6, 9, 3
0,19: completed [0:5): "6, 6, 9, 6, 9, 2, 2, 5, 8, 5, 1, 7, 2, 7, 10, 7, 8, 10, 8, 7"
5,19: completed [5:13): "6, 6, 9, 6, 9, 2, 2, 5, 8, 5, 8, 8, 2, 7, 10, 7, 7, 10, 1, 7"
13,19: completed [13:20): "6, 6, 9, 6, 9, 2, 2, 5, 8, 5, 8, 8, 2, 7, 10, 7, 7, 10, 1, 7"
GenericPartition GroupSame for "6, 10, 2, 5, 7, 2, 2, 6, 8, 9, 1, 7, 9, 7, 6, 7, 8, 10, 8, 5": 6, 6, 9, 6, 9, 2, 2, 5, 8, 5, 8, 8, 2, 7, 10, 7, 7, 10, 1, 7

*/
#endif
