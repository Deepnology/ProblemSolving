#ifndef _PRISON_CELL_1D_ARRAY_AFTER_N_DAYS_H
#define _PRISON_CELL_1D_ARRAY_AFTER_N_DAYS_H
#include "Debug.h"
/*
Leetcode: Prison Cells After N Days
There are 8 prison cells in a row, and each cell is either occupied or vacant.
Each day, whether the cell is occupied or vacant changes according to the following rules:
If a cell has two adjacent neighbors that are both occupied or both vacant, then the cell becomes occupied.
Otherwise, it becomes vacant.
(Note that because the prison is a row, the first and the last cells in the row can't have two adjacent neighbors.)
We describe the current state of the prison in the following way: cells[i] == 1 if the i-th cell is occupied, else cells[i] == 0.
Given the initial state of the prison, return the state of the prison after N days (and N such changes described above.)
Example 1:
Input: cells = [0,1,0,1,1,0,0,1], N = 7
Output: [0,0,1,1,0,0,0,0]
Explanation:
The following table summarizes the state of the prison on each day:
Day 0: [0, 1, 0, 1, 1, 0, 0, 1]
Day 1: [0, 1, 1, 0, 0, 0, 0, 0]
Day 2: [0, 0, 0, 0, 1, 1, 1, 0]
Day 3: [0, 1, 1, 0, 0, 1, 0, 0]
Day 4: [0, 0, 0, 0, 0, 1, 0, 0]
Day 5: [0, 1, 1, 1, 0, 1, 0, 0]
Day 6: [0, 0, 1, 0, 1, 1, 0, 0]
Day 7: [0, 0, 1, 1, 0, 0, 0, 0]
Example 2:
Input: cells = [1,0,0,1,0,0,1,0], N = 1000000000
Output: [0,0,1,1,1,1,1,0]
 */
class PrisonCell1DArrayAfterNDays
{
public:
    PrisonCell1DArrayAfterNDays(){}

    std::vector<int> Solve(std::vector<int> && cells, int N)
    {
        std::string before = Debug::ToStr1D<int>()(cells);

        int n = cells.size();
        std::vector<int> first;
        int cycle = 0;
        while (N-- > 0)
        {
            for (int i = 0; i < n; ++i)
            {
                if (i == 0 || i == n-1)//cells[i] becomes vacant
                {
                    cells[i] <<= 1;
                    cells[i] &= 3;//keep only lowest 2 digits
                }
                else//0:0->0, 1:0->1, 2:1->0, 3:1->1
                {
                    if ((cells[i-1]>>1)==0 && (cells[i+1]&1)==0 ||
                        (cells[i-1]>>1)==1 && (cells[i+1]&1)==1)//cells[i] becomes occupied
                    {
                        cells[i] <<= 1;
                        cells[i] |= 1;
                        cells[i] &= 3;//keep only lowest 2 digits
                    }
                    else//cells[i] becomes vacant
                    {
                        cells[i] <<= 1;
                        cells[i] &= 3;//keep only lowest 2 digits
                    }
                }
            }
            for (int i = 0; i < n; ++i)
                cells[i] &= 1;
            if (cycle == 0)
                first = cells;
            else if (first == cells)
            {
                N %= cycle;
                cycle = 0;
            }
            ++cycle;
        }

        std::cout << "PrisonCell1DArrayAfterNDays for [" << before << "]: " << Debug::ToStr1D<int>()(cells) << std::endl;
        return cells;
    }
};
/*
PrisonCell1DArrayAfterNDays for [0, 1, 0, 1, 1, 0, 0, 1]: 0, 0, 1, 1, 0, 0, 0, 0
 */
#endif
