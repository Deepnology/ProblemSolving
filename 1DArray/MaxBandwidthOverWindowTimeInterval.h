#ifndef MAX_BANDWIDTH_OVER_WINDOW_TIME_INTERVAL_H
#define MAX_BANDWIDTH_OVER_WINDOW_TIME_INTERVAL_H
#include <vector>
#include <deque>
#include <algorithm>
#include <string>
#include <iostream>
#include "Debug.h"
/*
Elements of programming interview, StacksAndQueues: Compute the maximum of a sliding window
You are given bandwidth usage at various times and a window length.
Compute for each time, the max bandwidth over the window length time interval which ends at that time.
The input is specified by an array, where each entry is a pair of timestamp and corresponding bandwidth.
Output: an array of pairs of timestamp and its corresponding max bandwidth within the window length ending at that timestamp.

timestamp idx:	-3 -2 -1  0  1  2  3  4  5  6  7  8  9
bandwidth:		          1     2  3     1  2     2  1
window of len3:	 |----1---|
					   |----2---|
					      |----3---|
							    |----3---|
								   |----3---|
								         |----2---|
										    |----2---|
max bandwidth winthin win:1     2  3     3  3     2  2

ByQueueWithMax: O(n) time, O(windowLen) space
maintain a "QueueWithMax" to keep track "all the entries within current time window" along with their max bandwidth
pop out QueueWithMax.front() when QueueWithMax.front() is out of current time window
QueueWithMax.Max() should be the entry that has max bandwidth within current time window

See also QueueWithMin.h, AllStockSpans.h, SubArrWLessEqualMinMaxDiff.h
*/
class MaxBandwidthOverWindowTimeInterval
{
public:
	MaxBandwidthOverWindowTimeInterval(){}
	~MaxBandwidthOverWindowTimeInterval(){}

	std::vector<std::pair<int, int> > ByQueueWithMax(const std::vector<std::pair<int, int> > & v, int windowLen)//first: timestamp idx, second: bandwidth
	{
		int N = v.size();
		std::vector<std::pair<int, int> > res;//first: timestamp idx, second: bandwidth

		/*Simulate "QueueWithMax" by a que and a sortedQue*/
		std::deque<std::pair<int, int> > que;//first: timestamp idx, second: bandwidth
		std::deque<std::pair<std::pair<int, int>, int> > sortedQue;//first: (timestamp idx,bandwidth) pair, second: count
		/*
		sortedQue is used to keep track of the pair that has max bandwidth, which should be its front pair, among all pairs in que
		the front is bigger, and the back is smaller
		QueueWithMax.Max() corresponds to sortedQue.front()
		*/

		for (int i = 0; i < N; ++i)
		{
			/*1. Enqueue QueueWithMax with v[i]*/
			if (que.empty())
				sortedQue.push_back(std::make_pair(v[i], 1));
			else
			{
				while (!sortedQue.empty() && sortedQue.back().first.second < v[i].second)
					sortedQue.pop_back();
				if (!sortedQue.empty() && sortedQue.back().first.second == v[i].second)
					++sortedQue.back().second;
				else
					sortedQue.push_back(std::make_pair(v[i], 1));
			}
			que.push_back(v[i]);
			/*End Enqueue QueueWithMax*/

			/*2. Remove QueueWithMax.front() until all entries in QueueWithMax are within current time window*/
			while (v[i].first - que.front().first > windowLen)
			{
				/*Dequeue QueueWithMax*/
				auto front = que.front();
				if (front.first == sortedQue.front().first.first && front.second == sortedQue.front().first.second)
				{
					--sortedQue.front().second;
					if (sortedQue.front().second == 0)
						sortedQue.pop_front();
				}
				que.pop_front();
				/*End Dequeue QueueWithMax*/
			}

			/*3. Record the QueueWithMax.Max() for current timestamp*/
			res.push_back(std::make_pair(v[i].first, sortedQue.front().first.second));
		}

		std::cout << "MaxBandwidthOverWindowTimeInterval ByQueueWithMax for \"" << windowLen << "\" in \"" << Debug::ToStr1D<int>()(v) << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
};
/*
MaxBandwidthOverWindowTimeInterval ByQueueWithMax for "3" in "[0,1], [2,2], [3,3], [5,1], [6,2], [8,2], [9,1]": [0,1], [2,2], [3,3], [5,3], [6,3], [8,2], [9,2]
*/
#endif