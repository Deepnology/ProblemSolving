#ifndef _UTILIZATION_CHECKS_H
#define _UTILIZATION_CHECKS_H
#include "Debug.h"
/*
Amazon OA
Given an array of integers representing the average utilization at each second, determine the number of instances at the end of time.
average utilization < 25: reduce num of instances to half if the num of instances is greater than 1
25 <= average utilization <= 60: take no action
average utilization > 60: double the num of instances if the new num of instances is <= 2*10^8
 */
class UtilizationChecks
{
public:
    int Solve(const std::vector<int> & v, int numInstances)
    {
        int original = numInstances;
        int N = v.size();
        int i = 0;
        while (i < N)
        {
            if (v[i] < 25 && numInstances > 1)
            {
                numInstances = (int) std::ceil((double) numInstances / 2);
                i += 11;
            }
            else if (v[i] > 60 && 2 * numInstances <= 200000000)
            {
                numInstances *= 2;
                i += 11;
            }
            else
                ++i;
        }
        std::cout << "UtilizationChecks for [" << Debug::ToStr1D<int>()(v) << "], " << original << ": " << numInstances << std::endl;
        return numInstances;
    }
};
#endif
