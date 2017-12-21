#ifndef _MEDIAN_OF_INTEGER_STREAM_H
#define _MEDIAN_OF_INTEGER_STREAM_H
#include <iostream>
#include <istream>
#include <sstream>
#include <string>
#include <queue>
#include <vector>
#include <set>
#include <functional>//std::greater
#include "Debug.h"
/*
Leetcode: Find Median from Data Stream
Elements of programming interview, Heaps: Compute the median of online data
Design an algorithm for computing the running median of a sequence.
The time complexity should be O(logn) per element read in, where n is the number of values read in up to that element.
Google
http://www.careercup.com/question?id=15417986
http://www.ardendertat.com/2011/11/03/programming-interview-questions-13-median-of-integer-stream/
*/
/*
only vector and deque's iterator support operator+ and operator-
list, set, map don't supprot operator+ and operator-
*/
class MedianOfIntegerStream
{
public:
	MedianOfIntegerStream(){}
	~MedianOfIntegerStream(){}

	double MinMaxHeap(int A[], int n)
	{
		std::priority_queue<int, std::vector<int>, std::less<int> > maxHeap;//the smaller half
		std::priority_queue<int, std::vector<int>, std::greater<int> > minHeap;//the bigger half
		std::vector<double> res;
		for (int i = 0; i < n; ++i)
		{
			if (!maxHeap.empty() && A[i] > maxHeap.top())
				minHeap.push(A[i]);
			else
				maxHeap.push(A[i]);

			if (minHeap.size() > maxHeap.size() + 1)
			{
				maxHeap.push(minHeap.top());
				minHeap.pop();
			}
			else if (maxHeap.size() > minHeap.size() + 1)
			{
				minHeap.push(maxHeap.top());
				maxHeap.pop();
			}

			if (minHeap.size() == maxHeap.size())
			{
				res.push_back(0.5 * (minHeap.top() + maxHeap.top()));
			}
			else
			{
				res.push_back(minHeap.size() > maxHeap.size() ? minHeap.top() : maxHeap.top());
			}
		}

		std::cout << "MedianOfIntegerStream MinMaxHeap for \"" << Debug::ToStr1D<int>()(A, n) << "\": " << Debug::ToStr1D<double>()(res) << std::endl;
		return res.back();
	}

	std::vector<double> MinMaxHeap_FromISS(std::istringstream & iss)
	{
		std::string before = iss.str();
		std::priority_queue<int, std::vector<int>, std::less<int> > maxHeap;//the smaller half
		std::priority_queue<int, std::vector<int>, std::greater<int> > minHeap;//the bigger half
		int buf;
		std::vector<double> res;
		while (iss >> buf)
		{
			if (!maxHeap.empty() && buf > maxHeap.top())
				minHeap.push(buf);
			else
				maxHeap.push(buf);

			if (minHeap.size() > maxHeap.size() + 1)
			{
				maxHeap.push(minHeap.top());
				minHeap.pop();
			}
			else if (maxHeap.size() > minHeap.size() + 1)
			{
				minHeap.push(maxHeap.top());
				maxHeap.pop();
			}

			if (minHeap.size() == maxHeap.size())
			{
				res.push_back(0.5 * (minHeap.top() + maxHeap.top()));
			}
			else
			{
				res.push_back(minHeap.size() > maxHeap.size() ? minHeap.top() : maxHeap.top());
			}
		}

		std::cout << "MedianOfIntegerStream MinMaxHeap_FromISS for \"" << before << "\": " << Debug::ToStr1D<double>()(res) << std::endl;
		return res;
	}

};
/*
MedianOfIntegerStream MinMaxHeap for "10, 9, 8, 7, 6, 5, 4, 3, 2, 2, 1, -1, -2, -2": 10, 9.5, 9, 8.5, 8, 7.5, 7, 6.5, 6, 5.5, 5, 4.5, 4, 3.5
MedianOfIntegerStream MinMaxHeap_FromISS for "10 9 8 7 6 5 4 3 2 2 1 -1 -2 -2": 10, 9.5, 9, 8.5, 8, 7.5, 7, 6.5, 6, 5.5, 5, 4.5, 4, 3.5
*/



#endif


