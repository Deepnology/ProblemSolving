#ifndef MIN_FIVE_HOURSE_TIME_TRIAL_H
#define MIN_FIVE_HOURSE_TIME_TRIAL_H
/*
Elements of programming interview, Sorting: Schedule time trials

You have 25 hourses and want to find the fastest 3 hourses.
You can race 5 hourses together each time.
What is the minimum number of five-hourse-time-trials needed to find the fastest 3 hourses out of 25 hourses?


			Group:	A		B		C		D		E
					1(1)	1(2)f	1(3)f	1(4)	1(5)
					2f		2f		2(x)	2		2
					3f		3(x)	3(x)	3		3
					4		4		4		4		4	<---this row all eliminated
					5		5		5		5		5	<---this row all eliminated

													^-------this column all eliminated
											^---------------this column all eliminated

1. Take 5 group races to determine rank 1 to 5 in each group.........................................................................................................5
2. The last 2 hourses in each group (bottom 2 rows) can be eliminated
3. Take a group race of the fastest one (top row) in each group......................................................................................................1
4. All the hourses that are in the same groups as the last 2 hourses from 3. (rightmost 2 columns) can be eliminated
5. The fastest hourse from 3. must be the overall fastest hourse
6. We take a final group race with all the 5 hourses that are 1 or 2 ranks away from the overall fastest hourse to determine the second best and the third best......1

7 time trials in total

*/
#endif