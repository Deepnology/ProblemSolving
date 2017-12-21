#ifndef MERGE_2_HEAPS_H
#define MERGE_2_HEAPS_H
#include "Debug.h"
/*
Merge 2 minHeaps/maxHeaps using minHeapify/maxHeapify
*/
class Merge2Heaps
{
public:
	Merge2Heaps() {}

	std::vector<int> UseMinHeapify(const std::vector<int> & v1, const std::vector<int> & v2)
	{
		std::vector<int> res(v1.begin(), v1.end());
		for (const auto & i : v2)
			res.push_back(i);
		MinHeapify(res);

		std::cout << "Merge2Heaps UseMinHeapify for \"" << Debug::ToStr1D<int>()(v1) << "\", \"" << Debug::ToStr1D<int>()(v2) << "\": " << std::endl << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
private:
	void MinHeapify(std::vector<int> & v)
	{
		int N = v.size();
		for (int i = N / 2; i >= 0; --i)
			SiftDownRecur(v, i, N - 1);
	}
	void SiftDownRecur(std::vector<int> & v, int begin, int end)
	{
		int leftChild = 2 * begin + 1;
		int rightChild = 2 * begin + 2;
		int minChild;
		if (rightChild <= end)
		{
			minChild = v[leftChild] < v[rightChild] ? leftChild : rightChild;
		}
		else if (leftChild <= end)
		{
			minChild = leftChild;
		}
		else
			return;
		if (v[begin] > v[minChild])
		{
			std::swap(v[begin], v[minChild]);
			SiftDownRecur(v, minChild, end);
		}
	}
};
/*
Merge2Heaps UseMinHeapify for "2, 5, 6, 8", "1, 7, 9":
1, 2, 6, 8, 5, 7, 9
*/
#endif
