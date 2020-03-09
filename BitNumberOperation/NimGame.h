#ifndef	NIM_GAME_H
#define NIM_GAME_H
#include <iostream>
#include <string>
#include "Debug.h"
/*
Leetcode: Nim Game
You are playing the following Nim Game with your friend: There is a heap of stones on the table, each time one of you take turns to remove 1 to 3 stones.
The one who removes the last stone will be the winner. You will take the first turn to remove the stones.
Both of you are very clever and have optimal strategies for the game.
Write a function to determine whether you can win the game given the number of stones in the heap.
For example, if there are 4 stones in the heap, then you will never win the game: no matter 1, 2, or 3 stones you remove, the last stone will always be removed by your friend.
Hint:
If there are 5 stones in the heap, could you figure out a way to remove the stones such that you will always be the winner?

n in [1,3]: starting player must win
n==4: after starting player take 1 to 3, n will be in [1,3] (hence his opponent must win), so starting player must loose
n in [5,7]: starting player can take 1 to 3 to make n==4 (hence his opponent must loose), so starting player must win
n==8: after starting player take 1 to 3, n will be in [5,7] (hence his opponent must win), so starting player must loose
...
*/
class NimGame
{
public:
	NimGame() {}
	~NimGame() {}

	bool CanWin(int n)
	{
		bool res = n % 4 > 0;

		std::cout << "NimGame CanWin for \"" << n << "\": " << res << std::endl;
		return res;
	}
};
/*
NimGame CanWin for "345345": 1
*/
#endif
