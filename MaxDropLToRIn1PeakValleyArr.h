/*Facebook*/
#ifndef _MAX_DROP_L_TO_R_IN_1_PEAK_VALLEY_ARR_H
#define _MAX_DROP_L_TO_R_IN_1_PEAK_VALLEY_ARR_H
#include "Debug.h"
/*
Given an array with distinct integers in which there is either only 1 peak OR only 1 valley.
Find the max drop from left to right.
either only 1 peak OR only 1 valley: means the array is either A shape or V shape
 */
class MaxDropLToRIn1PeakValleyArr
{
public:
    MaxDropLToRIn1PeakValleyArr(){}

    int BinarySearch(const std::vector<int> & v)
    {
        int N = v.size();
        int res = 0;
        if (N < 2) {res = 0;}
        else if (v[0] < v[1]) {res = v[BinarySearchPeak(v, 0, N-1)]  - v[N-1];}//peak-last
        else if (v[0] > v[1]) {res = v[0] - v[BinarySearchValley(v, 0, N-1)];}//first-valley

        std::cout << "MaxDropLToRIn1PeakValleyArr for [" << Debug::ToStr1D<int>()(v) << "]: " << res << std::endl;
        return res;
    }
    int BinarySearchPeak(const std::vector<int> & v, int left, int right)
    {
        int res = -1;
        while (right - left  > 1)//keep 3 entries in between [left:right]
        {
            int mid = left + (right - left) / 2;
            if (v[mid] > v[mid-1] && v[mid] > v[mid+1])
            {
                res = mid;
                break;
            }
            else if (v[mid] > v[mid-1])//since we want to find local max, abandon left since which contains a smaller element
                left = mid;
            else
                right = mid;
        }
        //now 2 entries in between [left:right] inclusive
        if (res == -1)
            res = v[left] > v[right] ? left : right;
        return res;
    }
    int BinarySearchValley(const std::vector<int> & v, int left, int right)
    {
        int res = -1;
        while (right - left  > 1)//keep 3 entries in between [left:right]
        {
            int mid = left + (right - left) / 2;
            if (v[mid] < v[mid-1] && v[mid] < v[mid+1])
            {
                res = mid;
                break;
            }
            else if (v[mid] < v[mid-1])//since we want to find local min, abandon left since which contains a larger element
                left = mid;
            else
                right = mid;
        }
        //now 2 entries in between [left:right] inclusive
        if (res == -1)
            res = v[left] < v[right] ? left : right;
        return res;
    }
};
/*
MaxDropLToRIn1PeakValleyArr for [1, 3, 5, 7, 9, 8, 6, 4, 2, 0]: 9
MaxDropLToRIn1PeakValleyArr for [9, 8, 6, 4, 2, 0, 1, 3, 5, 7]: 9
 */
#endif
