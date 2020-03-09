#ifndef FLATTEN_2D_VECTOR_H
#define FLATTEN_2D_VECTOR_H
#include <iostream>
#include <string>
#include <vector>
#include "Debug.h"
/*
Leetcode: Flatten 2D Vector
Implement an iterator to flatten a 2d vector.
For example,
Given 2d vector =
[
[1,2],
[3],
[4,5,6]
]
By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1,2,3,4,5,6].
Hint:
How many variables do you need to keep track?
Two variables is all you need. Try with x and y.
Beware of empty rows. It could be the first few rows.
To write correct code, think about the invariant to maintain. What is it?
The invariant is x and y must always point to a valid point in the 2d vector. Should you maintain your invariant ahead of time or right when you need it?
Not sure? Think about how you would implement hasNext(). Which is more complex?
Common logic in two different places should be refactored into a common method.
Follow up:
As an added challenge, try to code it using only iterators in C++ or iterators in Java.

*/
class Flatten2DVector
{
	std::vector<std::vector<int>>::const_iterator rowEndItr;
	std::vector<std::vector<int>>::const_iterator rowItr;//current row itr
	std::vector<int>::const_iterator colItr;//current col itr
public:
	explicit Flatten2DVector(const std::vector<std::vector<int>> & v)
	{
		rowItr = v.cbegin();
		rowEndItr = v.cend();
		while (rowItr != rowEndItr && rowItr->empty())
			++rowItr;
		if (rowItr != rowEndItr)
			colItr = rowItr->cbegin();

		std::cout << "Flatten2DVector: (" << (rowItr - v.cbegin()) << ", " << (colItr - rowItr->cbegin()) << ")" << std::endl;
		Debug::Print2D<int>()(v, false);
	}
	~Flatten2DVector() {}
	
	bool hasNext() const // O(1) time
	{
		bool res;
		if (rowItr == rowEndItr)
			res = false;
		else
			res = true;

		std::cout << "Flatten2DVector hasNext: " << res << std::endl;
		return res;
	}
	int next() // amortized O(1) time
	{
		int res = *colItr;
		++colItr;
		if (colItr == rowItr->cend())
		{
			++rowItr;
			while (rowItr != rowEndItr && rowItr->empty())
				++rowItr;
			if (rowItr != rowEndItr)
				colItr = rowItr->cbegin();
		}

		std::cout << "Flatten2DVector next: " << res << std::endl;
		return res;
	}

};
/*
Flatten2DVector: (0, 0)
[rY][cX]
Row#0	= 1, 2,
Row#1	=  ,  ,
Row#2	=  ,  ,
Row#3	= 3,  ,
Row#4	= 4, 5, 6
Row#5	=  ,  ,

Flatten2DVector hasNext: 1
Flatten2DVector next: 1
Flatten2DVector hasNext: 1
Flatten2DVector next: 2
Flatten2DVector hasNext: 1
Flatten2DVector next: 3
Flatten2DVector hasNext: 1
Flatten2DVector next: 4
Flatten2DVector hasNext: 1
Flatten2DVector next: 5
Flatten2DVector hasNext: 1
Flatten2DVector next: 6
Flatten2DVector hasNext: 0
*/
#endif
