#ifndef MAX_NUM_BY_SWAP_2_DIGITS_H
#define MAX_NUM_BY_SWAP_2_DIGITS_H
#include "Debug.h"
/*
Leetcode: Maximum Swap
Given a non-negative integer, you could swap two digits at most once to get the maximum valued number.
Return the maximum valued number you could get.
Example 1:
Input: 2736
Output: 7236
Explanation: Swap the number 2 and the number 7.
Example 2:
Input: 9973
Output: 9973
Explanation: No swap.
*/
class MaxNumBySwap2Digits
{
public:
	MaxNumBySwap2Digits() {}

	int Linear(int num)
	{
		std::string str = std::to_string(num);
		std::vector<int> lastIdx(10, -1);//rightmost idx of digits [0:9]
		int N = str.size();
		for (int i = 0; i < N; ++i)//from MSD to LSD
			lastIdx[str[i] - '0'] = i;
		for (int i = 0; i < N; ++i)//from MSD to LSD
		{
			for (int j = 9; j >= 0; --j)//from 9 to 0
			{
				if (lastIdx[j] != -1 && j >(str[i] - '0') //there exists a bigger digit
					&& lastIdx[j] > i)//the bigger digit is on the right side of i
				{
					char c = str[i];
					str[i] = '0' + j;
					str[lastIdx[j]] = c;
                    std::cout << "MaxNumBySwap2Digits for \"" << num << "\": " << stoi(str) << std::endl;
					return stoi(str);
				}
			}
		}

		std::cout << "MaxNumBySwap2Digits for \"" << num << "\": " << num << std::endl;
		return num;
	}

    int OnePass(int num)//better
    {
        std::string str = std::to_string(num);
        int N = str.size();
        int maxDigit = -1;
        int maxIdx;
        int leftIdx = -1;
        int rightIdx;
        for (int i = N-1; i >= 0; --i)
        {
            if (str[i]-'0' > maxDigit)
            {
                maxDigit = str[i]-'0';
                maxIdx = i;
            }
            else if (str[i]-'0' < maxDigit)
            {
                leftIdx = i;
                rightIdx = maxIdx;//must record rightIdx here
            }
        }
        if (leftIdx == -1)
        {
            std::cout << "MaxNumBySwap2Digits OnePass for \"" << num << "\": " << num << std::endl;
            return num;
        }

        std::swap(str[leftIdx], str[rightIdx]);
        std::cout << "MaxNumBySwap2Digits OnePass for \"" << num << "\": " << stoi(str) << std::endl;
        return stoi(str);
    }
};
/*
MaxNumBySwap2Digits for "2736": 7236
MaxNumBySwap2Digits for "9973": 9973
MaxNumBySwap2Digits for "98368": 98863
MaxNumBySwap2Digits OnePass for "2736": 7236
MaxNumBySwap2Digits OnePass for "9973": 9973
MaxNumBySwap2Digits OnePass for "98368": 98863
 */
#endif
