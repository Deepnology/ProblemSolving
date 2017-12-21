#ifndef SHUFFLE_ARRAY_H
#define SHUFFLE_ARRAY_H
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdlib.h>//srand, rand
#include <time.h>//time
#include "Debug.h"
/*
Leetcode: Shuffle an Array
http://www.geeksforgeeks.org/shuffle-a-given-array/
http://www.keithschwarz.com/interesting/code/?dir=random-shuffle
Cracking the coding interview: Hard

Given an array, write a program to generate a random permutation of array elements.
AKA "shuffle a deck of cards", "randomize a given array"

*/
class ShuffleArray
{
public:
	ShuffleArray(){}
	~ShuffleArray(){}

	void OnlineIterate(std::vector<int> & cards)
	{
		std::string before = Debug::ToStr1D<int>()(cards);
		int N = cards.size();
		srand((unsigned int)time(NULL));

		for (int i = 1; i < N; ++i)
		{
			/*pick a random index j in [0 : i] and swap its val with cards[i]*/
			int j = rand() % (i + 1);
			std::swap(cards[i], cards[j]);
		}
		std::cout << "ShuffleArray OnlineIterate for \"" << before << "\": " << Debug::ToStr1D<int>()(cards) << std::endl;
	}

	void OnlineRecur(std::vector<int> & cards)
	{
		std::string before = Debug::ToStr1D<int>()(cards);
		srand((unsigned int)time(NULL));
		this->solveRecur(cards, 1);
		std::cout << "ShuffleArray OnlineRecur for \"" << before << "\": " << Debug::ToStr1D<int>()(cards) << std::endl;
	}
private:
	void solveRecur(std::vector<int> & cards, int cur)
	{
		int N = cards.size();
		if (cur == N)
			return;
		/*pick a random index j in [0 : cur] and swap its val with cards[i]*/
		int j = rand() % (cur + 1);
		std::swap(cards[cur], cards[j]);
		this->solveRecur(cards, cur + 1);
	}

public:
	void OfflineIterate(std::vector<int> & cards)
	{
		std::string before = Debug::ToStr1D<int>()(cards);
		int N = cards.size();
		srand((unsigned int)time(NULL));

		for (int i = 0; i < N; ++i)
		{
			/*pick a random index j in [i : N-1] and swap its val with cards[i]*/
			int j = rand() % (N - i) + i;
			std::swap(cards[i], cards[j]);
		}
		std::cout << "ShuffleArray OfflineIterate for \"" << before << "\": " << Debug::ToStr1D<int>()(cards) << std::endl;
	}
};
/*
ShuffleArray OnlineIterate for "0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15": 5, 0, 7, 13, 6, 11, 8, 3, 15, 9, 10, 14, 12, 4, 1, 2
ShuffleArray OnlineRecur for "0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15": 5, 0, 7, 13, 6, 11, 8, 3, 15, 9, 10, 14, 12, 4, 1, 2
ShuffleArray OfflineIterate for "0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15": 12, 9, 8, 6, 4, 11, 3, 13, 15, 1, 2, 10, 7, 5, 14, 0
*/
#endif