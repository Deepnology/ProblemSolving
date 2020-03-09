#ifndef FLIP_GAME_H
#define FLIP_GAME_H
#include <vector>
#include <iostream>
#include <string>
#include "Debug.h"
/*
Leetcode: Flip Game
You are playing the following Flip Game with your friend:
Given a string that contains only these two characters: + and -, you and your friend take turns to flip two consecutive "++" into "--".
The game ends when a person can no longer make a move and therefore the other person will be the winner.
Write a function to compute all possible states of the string after one valid move.
For example, given s = "++++", after one move, it may become one of the following states:
[
"--++",
"+--+",
"++--"
]
If there is no valid move, return an empty list [].

Leetcode: Flip Game II
Write a function to determine if the starting player can guarantee a win.
For example, given s = "++++", return true.
The starting player can guarantee a win by flipping the middle "++" to become "+--+".
Follow up:
Derive your algorithm's runtime complexity.

For the time complexity, here is what I thought, let's say the length of the input string s is n, there are at most n - 1 ways to replace "++" to "--" (imagine s is all "+++...")
, once we replace one "++", there are at most (n - 2) - 1 ways to do the replacement, it's a little bit like solving the N-Queens problem
, the time complexity is (n - 1) x (n - 3) x (n - 5) x ..., so it's O(n!!), double factorial.
*/
class FlipGame
{
public:
	FlipGame() {}
	~FlipGame() {}

	//I.
	std::vector<std::string> NextState(const std::string & s)
	{
		std::vector<std::string> res;
		int N = s.size();
		if (N < 2)
			return res;

		for (int i = 0; i < N - 1; ++i)
		{
			if (s[i] == '+' && s[i + 1] == '+')
			{
				std::string s1 = s.substr(0, i);
				std::string s2 = "--";
				std::string s3 = s.substr(i + 2);
				res.push_back(s1 + s2 + s3);
			}
		}

		std::cout << "FlipGame NextState for \"" << s << "\": " << Debug::ToStr1D<std::string>()(res) << std::endl;
		return res;
	}

	//II.
	bool CanWin(const std::string & s)
	{
		std::string ss(s);
		bool res = this->winRecur(ss);

		std::cout << "FlipGame CanWin for \"" << s << "\": " << res << std::endl;
		return res;
	}
private:
	bool winRecur(std::string & s)
	{
		int N = s.size();
		for (int i = 0; i < N - 1; ++i)
		{
			if (s[i] == '+' && s[i + 1] == '+')
			{
				s[i] = '-';
				s[i + 1] = '-';

				bool canWin = !this->winRecur(s);

				s[i] = '+';
				s[i + 1] = '+';

				if (canWin)
					return true;
			}
		}
		return false;
	}

public:
	bool CanWinHashTable(const std::string & s)
	{
		std::string ss(s);
		std::unordered_map<std::string, bool> map;
		bool res = this->winHashTableRecur(ss, map);

		std::cout << "FlipGame CanWinHashTable for \"" << s << "\": " << res << std::endl;
		return res;
	}
private:
	bool winHashTableRecur(std::string & s, std::unordered_map<std::string, bool> & map)
	{
		if (map.find(s) != map.end())
			return map.find(s)->second;

		int N = s.size();
		for (int i = 0; i < N - 1; ++i)
		{
			if (s[i] == '+' && s[i + 1] == '+')
			{
				s[i] = '-';
				s[i + 1] = '-';

				bool canWin = !this->winHashTableRecur(s, map);
				if (canWin)
					map.insert({ s, true });

				s[i] = '+';
				s[i + 1] = '+';

				if (canWin)
					return true;
			}
		}

		map.insert({ s, false });
		return false;
	}
};
/*
FlipGame NextState for "+++": --+, +--
FlipGame NextState for "++++": --++, +--+, ++--
FlipGame NextState for "+++++": --+++, +--++, ++--+, +++--
FlipGame NextState for "+++--++++": --+--++++, +----++++, +++----++, +++--+--+, +++--++--
FlipGame NextState for "+++++++++": --+++++++, +--++++++, ++--+++++, +++--++++, ++++--+++, +++++--++, ++++++--+, +++++++--
FlipGame CanWin for "+++": 1
FlipGame CanWin for "++++": 1
FlipGame CanWin for "+++++": 0
FlipGame CanWin for "+++--++++": 1
FlipGame CanWin for "+++++++++": 0
FlipGame CanWinHashTable for "+++": 1
FlipGame CanWinHashTable for "++++": 1
FlipGame CanWinHashTable for "+++++": 0
FlipGame CanWinHashTable for "+++--++++": 1
FlipGame CanWinHashTable for "+++++++++": 0
*/
#endif
