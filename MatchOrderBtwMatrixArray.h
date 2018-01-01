#ifndef MATCH_ORDER_BTW_MATRIX_ARRAY_H
#define MATCH_ORDER_BTW_MATRIX_ARRAY_H
#include "Debug.h"
/*
Amazon
Bob's fruit company is running a promotion in which customers receive prizes for purchasing a secret combination of items.
The combination will change each day, so Bob wants to use a code list to make it easy to change the combination.
The code list contains group of fruits.
Both the order of the groups within the code list and the order of the fruits within the groups matter.
However, between the groups of fruits, any number, and type of fruit is allowable.
The term "anything" is used to allow for any type of fruit to appear in that location within the group.

Considder the following secret code list: [[apple,apple],[banana,anything,banana]].
Based on the above secret code list, a customer who made either of the following purchases would win the prize:
orange, apple, apple, banana, orange, banana
apple, apple, orange, orange, banana, apple, banana, banana

Write an algorithm to output 1 if the customer is a winner else output 0.
*/
class MatchOrderBtwMatrixArray
{
public:
	MatchOrderBtwMatrixArray() {}
	bool BruteForce(const std::vector<std::vector<std::string>> & matrix, const std::vector<std::string> & v)
	{
		bool res = bruteforce(matrix, v);
		Debug::Print2D<std::string>()(matrix, false);
		std::cout << "MatchOrderBtwMatrixArray BruteForce for \"" << Debug::ToStr1D<std::string>()(v) << "\": " << res << std::endl;
		return res;
	}
private:
	bool bruteforce(const std::vector<std::vector<std::string>> & matrix, const std::vector<std::string> & v)
	{
		int N = v.size();
		for (int i = 0; i < N; ++i)
		{
			//at each position i, try if v[i:M] can match all items in matrix
			bool mismatch = false;
			int ii = i;
			int M1 = matrix.size();
			for (int j = 0; j < M1; ++j)
			{
				int M2 = matrix[j].size();
				for (int k = 0; k < M2; ++k)
				{
					if (matrix[j][k] == "anything" || (ii < N && matrix[j][k] == v[ii]))
						++ii;
					else
					{
						mismatch = true;
						break;
					}
				}
				if (mismatch) break;
			}
			if (!mismatch) return true;
		}
		return false;
	}

};
/*
[rY][cX]
Row#0	= apple, apple,
Row#1	= banana, anything, banana

MatchOrderBtwMatrixArray BruteForce for "orange, apple, apple, banana, orange, banana": 1
[rY][cX]
Row#0	= apple, apple,
Row#1	= banana, anything, banana

MatchOrderBtwMatrixArray BruteForce for "banana, orange, banana, apple, apple": 0
[rY][cX]
Row#0	= apple, apple,
Row#1	= banana, anything, banana

MatchOrderBtwMatrixArray BruteForce for "apple, banana, apple, banana, orange, banana": 0
[rY][cX]
Row#0	= apple, apple,
Row#1	= apple, apple, banana

MatchOrderBtwMatrixArray BruteForce for "apple, apple, apple, banana": 0
[rY][cX]
Row#0	= orange,  ,
Row#1	= apple, apple,
Row#2	= banana, orange, apple
Row#3	= banana,  ,

MatchOrderBtwMatrixArray BruteForce for "orange, apple, apple, banana, orange, apple, banana": 1
[rY][cX]
Row#0	= apple, apricot,
Row#1	= banana, anything, guava
Row#2	= papaya, anything,

MatchOrderBtwMatrixArray BruteForce for "banana, orange, guava, apple, apricot, papaya, kiwi": 0
*/
#endif
