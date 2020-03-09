#ifndef MAX_BIPARTITE_MATCHING_H
#define MAX_BIPARTITE_MATCHING_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <algorithm>
#include <functional>
#include "Debug.h"
/*
http://www.geeksforgeeks.org/maximum-bipartite-matching/
A matching in a Bipartite Graph is a set of the edges chosen in such a way that no two edges share an endpoint.
A maximum matching is a matching of maximum size (maximum number of edges).
In other words, a matching is maximum if any edge is added to it, it is no longer a matching.
There can be more than one maximum matchings for a given Bipartite Graph.

Application:
There are M applicants and N jobs.
Each applicant has a subset of jobs that he/she is interested in.
Each job opening can only accept one applicant and a job applicant can be appointed for only one job.
Find an assignment of jobs to applicants in such that as many applicants as possible get jobs.

See also MaxFlowInFlowNetwork.h
*/
class MaxBipartiteMatching
{
public:
	MaxBipartiteMatching(){}
	~MaxBipartiteMatching(){}

	int MaxApplicantJobMatching_BipartiteMatrix(const std::vector<std::vector<int> > & bpMatrix)
	{
		int M = bpMatrix.size();//M applicants
		int N = bpMatrix[0].size();//N jobs
		std::vector<int> applicantIndex(N, -1);//index: job, value: applicant index which the job is assigned to
		int matches = 0;
		for (int applicant = 0; applicant < M; ++applicant)
		{
			std::vector<int> visit(N, 0);//index: job, value: visited or not by curApplicant
			if (this->dFS_FindNextJobToApplicant(bpMatrix, applicant, visit, applicantIndex))
				++matches;
		}
		Debug::Print2D<int>()(bpMatrix, false);
		std::cout << Debug::ToStr1D<int>()(applicantIndex) << std::endl;
		std::cout << "MaxBipartiteMatching MaxApplicantJobMatching_BipartiteMatrix: " << matches << std::endl;
		return matches;
	}
private:
	bool dFS_FindNextJobToApplicant(const std::vector<std::vector<int> > & bpMatrix, int curApplicant, std::vector<int> & visit, std::vector<int> & applicantIndex)
	{
		int M = bpMatrix.size();//M applicants
		int N = bpMatrix[0].size();//N jobs
		//find the next available job to assign to curApplicant
		//(enumerate all adj vertices)
		for (int job = 0; job < N; ++job)
		{
			if (bpMatrix[curApplicant][job] != 0 && !visit[job])//curApplicant interests in job and curApplicant hasn't visited job
			{
				visit[job] = 1;
				if (applicantIndex[job] == -1 ||//job has not yet been assigned to any applicant
					this->dFS_FindNextJobToApplicant(bpMatrix, applicantIndex[job], visit, applicantIndex))//if applicantIndex[job] is interested in ANOTHER JOB and ABLE to assign it to applicantIndex[job]
				{
					applicantIndex[job] = curApplicant;//now assign job to curApplicant
					return true;
				}
			}
		}
		return false;
	}
};
/*
[rY][cX]
Row#0	= 0, 1, 1, 0, 0, 0
Row#1	= 1, 0, 0, 1, 0, 0
Row#2	= 0, 0, 1, 0, 0, 0
Row#3	= 0, 0, 1, 1, 0, 0
Row#4	= 0, 0, 0, 0, 0, 0
Row#5	= 0, 0, 0, 0, 0, 1

1, 0, 2, 3, -1, 5
MaxBipartiteMatching MaxApplicantJobMatching_BipartiteMatrix: 5
*/
#endif