#ifndef _RAND10_FROM_RAND7_H
#define _RAND10_FROM_RAND7_H
#include "Debug.h"
/*
Leetcode: Implement Rand10() using Rand7()
Given a function rand7 which generates a uniform random integer in the range 1 to 7
 , write a function rand10 which generates a uniform random integer in the range 1 to 10.
Do NOT use system's Math.random().
Example 1:
Input: 1
Output: [7]
Example 2:
Input: 2
Output: [8,4]
Example 3:
Input: 3
Output: [8,1,10]
 Note:
rand7 is predefined.
Each testcase has one argument: n, the number of times that rand10 is called.
 Follow up:
What is the expected value for the number of calls to rand7() function?
Could you minimize the number of calls to rand7()?
 */
class Rand10FromRand7
{
public:
    Rand10FromRand7(){}

    int Rand10() // return [1:10]
    {
        //rand7() -> rand49() -> rand40() -> rand10()
        int res;
        while ((res = 7 * (Rand7()-1) + Rand7()-1) >= 40) {}
        res = res % 10 + 1;
        return res;
    }

    void Roll(int times)
    {
        std::vector<std::pair<int,int> > res;
        for (int i = 1; i <= 10; ++i)
            res.push_back(std::make_pair(i, 0));
        for (int i = 0; i < times; ++i)
            ++res[Rand10() - 1].second;

        std::cout << "Rand10FromRand7 Roll \"" << times << "\"-times: " << Debug::ToStr1D<int>()(res) << std::endl;
    }

private:
    int Rand7() // return [1:7]
    {
        return rand() % 7 + 1;
    }
};

class Rand11FromRand3
{
public:
    Rand11FromRand3(){}

    int Rand11() // return [1:11]
    {
        //rand3() -> rand27() -> rand22() -> rand11()
        int res;
        while ((res = 3 * 3 * (Rand3()-1) + 3 * (Rand3()-1) + Rand3()-1) >= 22) {}
        res = res % 11 + 1;
        return res;
    }

    void Roll(int times)
    {
        std::vector<std::pair<int,int> > res;
        for (int i = 1; i <= 11; ++i)
            res.push_back(std::make_pair(i, 0));
        for (int i = 0; i < times; ++i)
            ++res[Rand11() - 1].second;

        std::cout << "Rand11FromRand3 Roll \"" << times << "\"-times: " << Debug::ToStr1D<int>()(res) << std::endl;
    }
private:
    int Rand3() // return [1:3]
    {
        return rand() % 3 + 1;
    }
};
/*
Rand10FromRand7 Roll "1000"-times: [1,77], [2,110], [3,119], [4,94], [5,103], [6,106], [7,106], [8,89], [9,94], [10,102]
Rand11FromRand3 Roll "1000"-times: [1,93], [2,88], [3,91], [4,112], [5,94], [6,68], [7,118], [8,88], [9,84], [10,85], [11,79]
 */
#endif
