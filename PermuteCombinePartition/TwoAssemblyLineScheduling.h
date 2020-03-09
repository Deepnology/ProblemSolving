#ifndef TWO_ASSEMBLY_LINE_SCHEDULING_H
#define TWO_ASSEMBLY_LINE_SCHEDULING_H
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include "Debug.h"
/*
http://www.geeksforgeeks.org/dynamic-programming-set-34-assembly-line-scheduling/
A car factory has two assembly lines, each with n stations.
Each station takes some process time.
A car in one line can be transfered with a transfer time to the next station in another line.
Each line has an entry time and an exit time.
Find out the minimum time it requires to build a car.

DP1D: O(n) time, O(n) space
*/
class TwoAssemblyLineScheduling
{
public:
	TwoAssemblyLineScheduling(){}
	~TwoAssemblyLineScheduling(){}

	//stationTime[0][i]: station time in first line at station index i
	//stationTime[1][i]: station time in second line at station index i
	//transferTime[0][i]: transfer time from first to second line at station index i
	//transferTime[1][i]: transfer time from second to first line at station index i
	int DP1D(const std::vector<std::vector<int> > & stationTime, const std::vector<std::vector<int> > & transferTime, 
		const std::vector<int> & entryTime, const std::vector<int> & exitTime)
	{
		int N = stationTime[0].size();
		std::vector<int> T1(N);
		std::vector<int> T2(N);

		//base cases init
		T1[0] = entryTime[0] + stationTime[0][0];
		T2[0] = entryTime[1] + stationTime[1][0];

		for (int i = 1; i < N; ++i)
		{
			T1[i] = std::min(T1[i - 1] + stationTime[0][i], //advance one station in line 1
				T2[i - 1] + transferTime[1][i] + stationTime[0][i]);//transferred from line 2 to line 1 and advance one station in line 1

			T2[i] = std::min(T2[i - 1] + stationTime[1][i], //advance one station in line 2
				T1[i - 1] + transferTime[0][i] + stationTime[1][i]);//transferred from line 1 to line 2 and advance one station in line 2
		}
		int res = std::min(T1[N - 1] + exitTime[0], T2[N - 1] + exitTime[1]);

		std::cout << "StationTime:" << std::endl;
		Debug::Print2D<int>()(stationTime, false);
		std::cout << "TransferTime:" << std::endl;
		Debug::Print2D<int>()(transferTime, false);
		std::cout << "EntryTime: " << Debug::ToStr1D<int>()(entryTime) << ", ExitTime: " << Debug::ToStr1D<int>()(exitTime) << std::endl;
		std::cout << Debug::ToStr1D<int>()(T1) << std::endl;
		std::cout << Debug::ToStr1D<int>()(T2) << std::endl;
		std::cout << "TwoAssemblyLineScheduling DP1D: " << res << std::endl;
		return res;
	}
};
/*
StationTime:
[rY][cX]
Row#0	= 4, 5, 3, 2
Row#1	= 2, 10, 1, 4

TransferTime:
[rY][cX]
Row#0	= 0, 7, 4, 5
Row#1	= 0, 9, 2, 8

EntryTime: 10, 12, ExitTime: 18, 7
14, 19, 22, 24
14, 24, 24, 28
TwoAssemblyLineScheduling DP1D: 35
*/
#endif