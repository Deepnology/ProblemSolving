#ifndef INVERSE_PERMUTATION_ARRAY_H
#define INVERSE_PERMUTATION_ARRAY_H
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include "Debug.h"
/*
Elements of programming interview, Array: Permute the elements of an array

Given an integer array representing a permutation.
Rearragne the array to represent the inverse permutation using only constant additional storage.

An inverse permutation is a permutation in which each number and the number of the place which it occupies are exchanged.
For example,
p1 = [3,8,5,10,9,4,6,1,7,2]
p2 = [8,10,1,6,3,7,9,2,5,4]
are inverse permutations, since the positions of 1,2,3,4,5,6,7,8,9, and 10 in p1 are p2
, and the positions of 1,2,3,4,5,6,7,8,9, and 10 in p2 are likewise p1.

v[v[i]-1] <- v[i]

Perform a DFS from begin: find the target index which is "current value - 1", then move "current index + 1" to target index, and so on.
O(n) time, O(1) space

See also ApplyPermutationOrder.h, SortByPermutationOrder.h
*/
class InversePermutationArray
{
public:
	InversePermutationArray(){}
	~InversePermutationArray(){}

	void InPlace(std::vector<int> && v)
	{
		std::string before = Debug::ToStr1D<int>()(v);
		int N = v.size();
		
		int cur = 0;//start from begin
		int tgt = v[cur] - 1;
		do
		{
			int nxt = v[tgt] - 1;
			v[tgt] = cur + 1;
			std::cout << "update index_" << tgt << ": " << cur + 1 << std::endl;
			cur = tgt;
			tgt = nxt;
			
		} while (cur != 0);//stop DFS when it goes back to begin

		std::cout << "InversePermutationArray InPlace for \"" << before << "\": " << Debug::ToStr1D<int>()(v) << std::endl;
	}
};
/*
update index_2: 1
update index_4: 3
update index_8: 5
update index_6: 9
update index_5: 7
update index_3: 6
update index_9: 4
update index_1: 10
update index_7: 2
update index_0: 8
InversePermutationArray InPlace for "3, 8, 5, 10, 9, 4, 6, 1, 7, 2": 8, 10, 1, 6, 3, 7, 9, 2, 5, 4
update index_0: 1
InversePermutationArray InPlace for "1, 2, 3, 4": 1, 2, 3, 4
update index_3: 1
update index_0: 4
InversePermutationArray InPlace for "4, 3, 2, 1": 4, 3, 2, 1
update index_2: 1
update index_0: 3
InversePermutationArray InPlace for "3, 4, 1, 2": 3, 4, 1, 2
update index_2: 1
update index_1: 3
update index_3: 2
update index_0: 4
InversePermutationArray InPlace for "3, 4, 2, 1": 4, 3, 1, 2
*/
#endif