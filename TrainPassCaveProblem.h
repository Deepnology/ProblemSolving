#ifndef _TRAIN_PASS_CAVE_PROBLEM_H
#define _TRAIN_PASS_CAVE_PROBLEM_H
/*
Bloomberg
https://instant.1point3acres.com/thread/211917
A train is going to pass a cave from left to right where the cave is 1000m long.
You are located 200m to left exit in the cave.
The speed of train is 2 times of a human.
Which direction should you run?

 train    d     Exit  200  human                  800             Exit
 []_[]-----------|-----------|--------------------------------------|

Suppose the distance from train to left exit of cave is d.
If human run to left, the time that train reaches left exit should be equal to the time that human reaches left exit.
d/2 = 200/1, d=400
If human run to right, the time that train reaches right exit should be equal to the time that human reaches right exit.
(d+1000)/2 = 800/1, d=600
=>
If d<400, human will die no matter he runs to left or to right.
If 400<=d<=600, human should run to left.
If d>600, human can choose either way to run.
=> always choose to run to left

What if human is at 400m to left exit?
d/2 = 400/1, d=800
(d+1000)/2 = 600/1, d=200
=>
If d<200, human will die.
If 200<=d<=800, human should run to right.
If d>800, human can choose either way to run.
=> always choose to run to right

Generalize the question, in what range of d should human run to left and in what range of d should human run to right?
Assume human is x apart from left exit.
d/2 = x/1
(d+1000)/2 = (1000-x)/1
we can cancel out d by subtracting the above 2 equations.
500 = 1000-2x
x=250

So if x<250, human should run to left, x=250 can choose either way, otherwise should run to right.
 */
#endif
