#ifndef CHESS_HASH_FUNC_H
#define CHESS_HASH_FUNC_H
/*
Elements of programming interview, HashTable: Implement a hash function for chess
Design a hash function for chess game states.
Your function should take a state and the hash code for that state, and a move, and efficiently compute the hash code for the updated state.

In a chessboard, there are 8x8 grids.
Each grid has 13 states, which can be: blank, white pawn, white rook, ..., white king, bkack pawn, ..., black king.
Create a HashCodeTable of 8x8x13, and generate 8x8x13 unique random numbers for each position.
These 8x8x13 unique random numbers are constants in the program.
The hash code for the state (config) of a chessboard will be the XOR of 8x8 random numbers of each state at each position.
Update for a movement of black king from a position to another:
1. XOR current code with the random number at black king's FROM corresponding position, black king index (to remove black king)
2. XOR current code with the random number at black king's FROM corresponding position, blank index (to add blank)
3. XOR current code with the random number at black king's TO corresponding position, blank index (to remove blank)
4. XOR current code with the random number at black king's TO corresponding position, black king index (to add black king)


For example, consider a simpler game played on a 2x2 board, with at most two pieces, P and Q present on the board.
At most one piece can be present at a board position.
Denote the board positions by (0,0), (0,1), (1,0), (1,1).
Use the following 7-bit random codes for each individual position.
(0,0): 1100111 for blank, 1011000 for P, 1100010 for Q
(0,1): 1111100 for blank, 1000001 for P, 0001111 for Q
(1,0): 1100101 for blank, 1101101 for P, 0011101 for Q
(1,1): 0100001 for blank, 0101100 for P, 1001011 for Q
Consider the state: P is present at (0,0) and Q at (1,1) with the remaining positions blank.
The hash code for this is state is 1011000 XOR 1111100 XOR 1100101 XOR 1001011 = 0001010.
Now compute the code for the state where Q moves to (0,1).
We XOR the code for the current state with 1001011 (remove Q from (1,1)), 0100001 (add blank at (1,1)), 1111100 (remove blank from (0,1)), and 0001111 (add Q at (0,1)).
(Remember that XOR 2 same numbers will cancel that number!)

See also GeneralTowerOfHanoi.h
*/
#endif