#ifndef MIN_MATCH_FIND_BEST_AND_RUNNERUP_H
#define MIN_MATCH_FIND_BEST_AND_RUNNERUP_H
/*
Elements of programming interview, Sorting: Find the winner and runner-up

128 players take part in a tennis tournament.
The "x beats y" relationship is transitive, i.e., for all players a, b, and c
, if a beats b and b beats c, then a beats c.

How would you organize a tournament with 128 players to minimize the number of matches needed to find the best and the second best players?

To find the best player, we need
64 matches + 32 matches + 16 matches + 8 matches + 4 matches + 2 matches + 1 match = 127 matches = 128 - 1 matches.

The winner has taken 7 mathes and eliminated 7 players.

To find the second best player, we can organize matches between all the 7 players that were eliminated by the winner, so we need additional 7 - 1 = 6 matches to find the second best.

So the total matches needed are 128 + 7 - 2 = 133.
                                                                                  _    _
Generalizing to k players, k - 1 matches are needed to find the best player, and | logk | - 1 additional matches must be played to find the second best.
               _    _
In total, k + | logk | - 2 matches are needed to find the best player and the runner-up.
*/
#endif