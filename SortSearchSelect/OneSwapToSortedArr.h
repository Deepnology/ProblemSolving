/*Facebook*/
#ifndef _ONE_SWAP_TO_SORTED_ARR_H
#define _ONE_SWAP_TO_SORTED_ARR_H
#include "Debug.h"
/*
Check if an integer array can be changed to monotone (ascending) array by at most swapping two elements.
https://www.geeksforgeeks.org/sort-an-almost-sorted-array-where-only-two-elements-are-swapped/
 */
class OneSwapToSortedArr
{
public:
    OneSwapToSortedArr(){}

    bool Validate(std::vector<int> && v)
    {
        std::string before = Debug::ToStr1D<int>()(v);
        int N = v.size();
        bool swapped = false;
        for (int i = N-1; i > 0; --i)
        {
            if (v[i-1] > v[i])//swap v[i] with its leftmost greater num
            {
                int j = i-1;
                while (j >= 0 && v[j] > v[i])
                    --j;
                std::swap(v[j+1], v[i]);
                swapped = true;
                break;
            }
        }
        if (!swapped)
        {
            std::cout << "OneSwapToSortedArr Validate for [" << before << "]: 1 (already sorted)" << std::endl;
            return true;
        }
        bool sorted = true;
        for (int i = 0; i < N-1; ++i)
            if (v[i] > v[i+1])
            {
                sorted = false;
                break;
            }
        std::cout << "OneSwapToSortedArr Validate for [" << before << "]: " << sorted << std::endl;
        return sorted;
    }
};
/*
OneSwapToSortedArr Validate for [3, 4, 5, 1, 6]: 0
OneSwapToSortedArr Validate for [1, 3, 7, 4]: 1
OneSwapToSortedArr Validate for [3, 4, 5, 6]: 1 (already sorted)
OneSwapToSortedArr Validate for [2, 5, 3, 4]: 0
OneSwapToSortedArr Validate for [2, 5, 3, 6]: 1
OneSwapToSortedArr Validate for [5, 6, 7, 4]: 0
 */
#endif
