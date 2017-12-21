#ifndef MEASURE_WITH_DEFECTIVE_JUGS_H
#define MEASURE_WITH_DEFECTIVE_JUGS_H
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <iostream>
#include <string>
#include "Debug.h"
/*
Elements of programming interview, DynamicProgramming: Measure with defective jugs
You have three measuring jogs, A, B, and C.
The measuring marks have worn out, making it impossible to measure exact volumes.
Specifically, each time you measure with A, all you can be sure of is that you have a volume that is in the range [230,240] ml.
(The next time you use A, you may get a different volume--all that you know with certainty is that the quantity  will be in [230,240] ml)
Jugs B and C can be used to measure a volume in [290,310] ml and in [500,515] ml, respectively.
Your receipe for chocolate chip cookies calls for at least 2100 ml and no more than 2300 ml of milk.

Write a program that determines a sequence of steps by which the required amount of milk can be obtained using the worn-out jogs.
The milk is being added to a large mixing bowl, and hence cannot be removed from the bowl.
Furthermore, it is not possible to pour one jug's contents into another.
Your scheme should always work, i.e., return between 2100 and 2300 ml of milk, independent of how much is chosen in each individual step, as long as that quantity satisfies the given constraints.

See also Subsets.h
*/
class MeasureWithDefectiveJugs
{
public:
	MeasureWithDefectiveJugs(){}
	~MeasureWithDefectiveJugs(){}

	std::vector<std::vector<std::pair<int, int>>> FindAllUnique_AllowRepeats_FromNoDupArr_FixRecur(const std::vector<std::pair<int, int>> & v, int L, int H)
	{
		std::vector<std::vector<std::pair<int, int>>> res;
		std::vector<std::pair<int, int>> path;
		this->FixRecur_AllowRepeats_FromNoDupArray(v, L, H, 0, 0, 0, path, res);
		std::cout << "MeasureWithDefectiveJugs FindAllUnique_AllowRepeats_FromNoDupArr_FixRecur for \"" << L << "," << H << " from " << Debug::ToStr1D<int>()(v) << "\": " << std::endl;
		Debug::Print2D<int>()(res, false);
		return res;
	}
private:
	void FixRecur_AllowRepeats_FromNoDupArray(const std::vector<std::pair<int, int>> & v, int L, int H, int curL, int curH, int begin
		, std::vector<std::pair<int, int>> & path, std::vector<std::vector<std::pair<int, int>>> & res)
	{
		if (curL >= L && curH <= H)
			res.push_back(path);

		int N = v.size();
		for (int i = begin; i < N; ++i)
		{
			if (curL + v[i].first > H)
				continue;
			path.push_back(v[i]);
			this->FixRecur_AllowRepeats_FromNoDupArray(v, L, H, curL + v[i].first, curH + v[i].second, i, path, res);
			path.pop_back();
		}
	}

public:
	std::vector<std::vector<std::pair<int, int>>> FindAllUnique_AllowRepeats_FromNoDupArr_InExcludeRecur(const std::vector<std::pair<int, int>> & v, int L, int H)
	{
		std::vector<std::vector<std::pair<int, int>>> res;
		std::vector<std::pair<int, int>> path;
		this->InExcludeRecur_AllowRepeats_FromNoDupArray(v, L, H, 0, 0, 0, path, res);
		std::cout << "MeasureWithDefectiveJugs FindAllUnique_AllowRepeats_FromNoDupArr_InExcludeRecur for \"" << L << "," << H << " from " << Debug::ToStr1D<int>()(v) << "\": " << std::endl;
		Debug::Print2D<int>()(res, false);
		return res;
	}
private:
	void InExcludeRecur_AllowRepeats_FromNoDupArray(const std::vector<std::pair<int, int>> & v, int L, int H, int curL, int curH, int begin
		, std::vector<std::pair<int, int>> & path, std::vector<std::vector<std::pair<int, int> > > & res)
	{
		if (curL >= L && curH <= H)
		{
			res.push_back(path);
			return;
		}

		int N = v.size();
		if (begin == N)
			return;

		if (curL + v[begin].first <= H)
		{
			path.push_back(v[begin]);
			this->InExcludeRecur_AllowRepeats_FromNoDupArray(v, L, H, curL + v[begin].first, curH + v[begin].second, begin, path, res);
			path.pop_back();
		}
		this->InExcludeRecur_AllowRepeats_FromNoDupArray(v, L, H, curL, curH, begin + 1, path, res);
	}


	struct PairEqual
	{
		bool operator()(const std::pair<int, int> & a, const std::pair<int, int> & b) const
		{
			return a.first == b.first && a.second == b.second;
		}
	};
	struct PairHash
	{
		unsigned int operator()(const std::pair<int, int> & p) const
		{
			return std::hash<int>()(p.first) ^ std::hash<int>()(p.second);
		}
	};
public:
	bool CheckFeasible(const std::vector<std::pair<int, int>> & v, int L, int H)
	{
		std::unordered_set<std::pair<int, int>, PairHash, PairEqual> dp;
		bool res = this->checkFeasibleRecur(v, L, H, dp);
		std::cout << "MeasureWithDefectiveJugs CheckFeasible for \"" << L << "," << H << " from " << Debug::ToStr1D<int>()(v) << "\": " << res << std::endl;
		return res;
	}
private:
	bool checkFeasibleRecur(const std::vector<std::pair<int, int>> & v, int curL, int curH, std::unordered_set<std::pair<int, int>, PairHash, PairEqual> & dp)
	{
		if (curL > curH || dp.count({ curL, curH }) != 0 || (curL < 0 && curH < 0))
			return false;

		//checks the volume for each jog to see if it is possible
		for (const auto & p : v)
		{
			if ((p.first >= curL && p.second <= curH) || //base case: p is contained int [curL,curH]
				this->checkFeasibleRecur(v, curL - p.first, curH - p.second, dp))
				return true;
		}

		//marks this as impossible
		dp.insert({ curL, curH });
		return false;
	}
};
/*
MeasureWithDefectiveJugs FindAllUnique_AllowRepeats_FromNoDupArr_FixRecur for "2100,2300 from [230,240], [290,310], [500,515]":
[rY][cX]
Row#0	= [230,240], [230,240], [230,240], [230,240], [230,240], [230,240], [230,240], [230,240], [290,310]
Row#1	= [230,240], [230,240], [230,240], [230,240], [230,240], [230,240], [230,240], [290,310], [290,310]
Row#2	= [230,240], [230,240], [230,240], [230,240], [230,240], [230,240], [230,240], [500,515],
Row#3	= [230,240], [230,240], [230,240], [230,240], [230,240], [230,240], [290,310], [500,515],
Row#4	= [230,240], [230,240], [230,240], [230,240], [230,240], [500,515], [500,515],  ,
Row#5	= [230,240], [230,240], [230,240], [230,240], [290,310], [500,515], [500,515],  ,
Row#6	= [230,240], [230,240], [230,240], [290,310], [290,310], [290,310], [290,310], [290,310],
Row#7	= [230,240], [230,240], [230,240], [500,515], [500,515], [500,515],  ,  ,
Row#8	= [230,240], [230,240], [290,310], [290,310], [290,310], [290,310], [500,515],  ,
Row#9	= [230,240], [290,310], [290,310], [290,310], [500,515], [500,515],  ,  ,
Row#10	= [230,240], [500,515], [500,515], [500,515], [500,515],  ,  ,  ,
Row#11	= [290,310], [290,310], [290,310], [290,310], [500,515], [500,515],  ,  ,

MeasureWithDefectiveJugs FindAllUnique_AllowRepeats_FromNoDupArr_InExcludeRecur for "2100,2300 from [230,240], [290,310], [500,515]":
[rY][cX]
Row#0	= [230,240], [230,240], [230,240], [230,240], [230,240], [230,240], [230,240], [230,240], [290,310]
Row#1	= [230,240], [230,240], [230,240], [230,240], [230,240], [230,240], [230,240], [290,310], [290,310]
Row#2	= [230,240], [230,240], [230,240], [230,240], [230,240], [230,240], [230,240], [500,515],
Row#3	= [230,240], [230,240], [230,240], [230,240], [230,240], [230,240], [290,310], [500,515],
Row#4	= [230,240], [230,240], [230,240], [230,240], [230,240], [500,515], [500,515],  ,
Row#5	= [230,240], [230,240], [230,240], [230,240], [290,310], [500,515], [500,515],  ,
Row#6	= [230,240], [230,240], [230,240], [290,310], [290,310], [290,310], [290,310], [290,310],
Row#7	= [230,240], [230,240], [230,240], [500,515], [500,515], [500,515],  ,  ,
Row#8	= [230,240], [230,240], [290,310], [290,310], [290,310], [290,310], [500,515],  ,
Row#9	= [230,240], [290,310], [290,310], [290,310], [500,515], [500,515],  ,  ,
Row#10	= [230,240], [500,515], [500,515], [500,515], [500,515],  ,  ,  ,
Row#11	= [290,310], [290,310], [290,310], [290,310], [500,515], [500,515],  ,  ,

MeasureWithDefectiveJugs CheckFeasible for "2100,2300 from [230,240], [290,310], [500,515]": 1
*/
#endif