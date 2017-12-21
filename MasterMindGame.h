#ifndef MASTER_MIND_GAME_H
#define MASTER_MIND_GAME_H
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include "Debug.h"
/*
Leetcode: Bulls and Cows
Cracking the coding interview: Moderate
The computer has four slots containing balls that are red(R), yellow(Y), green(G) or blud(B).
For example, the solution is RGGB.
You, the user, are trying to guess the solution.
You might guess YRGB.
When you guess the correct color for the correct slot, you get a "hit".
If you guess a color that exits but is in the wrong slot, you get a "pseudo-hit".
For example, the guess YRGB has 2 hits and 1 pseudo hit.
Given a solution and a guess, determine the number of hits and pseudo hits.
*/
class MasterMindGame
{
public:
	MasterMindGame(){}
	~MasterMindGame(){}

	std::pair<int, int> Estimate(const std::string & guess, const std::string & solution)
	{
		std::pair<int, int> res;//first: hits, second: pseudo-hits
		int N = guess.size();
		if (N != (int)solution.size())
			return res;
		std::vector<int> ballCount(4, 0);//4 slots for RGBY

		//count hits
		for (int i = 0; i < N; ++i)
		{
			if (guess[i] == solution[i])
				++res.first;
			else
				++ballCount[this->ColorToIndex(solution[i])];//keep track of extra count of RGBY in solution that is non-hit
		}

		//count pseudo-hits
		for (int i = 0; i < N; ++i)//for each guess[i], if non-hit and has extra count in solution: increment pseudo-hit and cancel one count
		{
			int index = this->ColorToIndex(guess[i]);
			if (index >= 0 && ballCount[index] > 0 && guess[i] != solution[i])
			{
				++res.second;
				--ballCount[index];
			}
		}

		std::cout << "MasterMindGame Estimate for \"" << guess << "\", \"" << solution << "\": " << res.first << ", " << res.second << std::endl;
		return res;
	}

private:
	int ColorToIndex(char c)
	{
		switch (c)
		{
		case 'B':
			return 0;
		case 'G':
			return 1;
		case 'R':
			return 2;
		case 'Y':
			return 3;
		default:
			return -1;
		}
	}

public:
	std::string BullsAndCows(const std::string & secret, const std::string & guess)
	{
		int N = secret.size();
		int hits = 0;
		int pseudoHits = 0;
		std::vector<int> extraSecret(10, 0);//10 slots for 0~9

		for (int i = 0; i < N; ++i)
		{
			if (secret[i] == guess[i])
				++hits;
			else
				++extraSecret[secret[i] - '0'];//keep track of extra count in secret that is non-hit
		}

		for (int i = 0; i < N; ++i)//for each guess[i], if non-hit and has extra count in secret: increment pseudo-hit and cancel one count
		{
			if (guess[i] != secret[i] && extraSecret[guess[i] - '0'] > 0)
			{
				++pseudoHits;
				--extraSecret[guess[i] - '0'];
			}
		}

		std::string res;
		res += std::to_string(hits) + "A" + std::to_string(pseudoHits) + "B";
		std::cout << "MasterMindGame BullsAndCows for \"" << guess << "\", \"" << secret << "\": " << res << std::endl;
		return res;
	}
};
/*
MasterMindGame Estimate for "RGBY", "GGRR": 1, 1
MasterMindGame Estimate for "RGGB", "YRGB": 2, 1
MasterMindGame BullsAndCows for "7810", "1807": 1A3B
MasterMindGame BullsAndCows for "0111", "1123": 1A1B
*/
#endif