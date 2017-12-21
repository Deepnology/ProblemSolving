#ifndef	MIN_NUM_REPLACE_2_ADJ_DIGITS_W_MAX_OF_2_H
#define MIN_NUM_REPLACE_2_ADJ_DIGITS_W_MAX_OF_2_H
/*
Google
Given a positive integer, replace 2 adjacent digits w/ larger one to find the smallest number that can be obtained.

Iterate from highest index, find first 3 adj digits which meets "high >= mid > low" and replace the high digit and mid digit w/ the high digit.
If nothing found, replace the lowest 2 digits with larger one.
Example:
233614 -> can't find, replace 14 with 4: 23364
177763 -> 7>=7>6, replace 77 with 7: 17763
52231 -> can't find, replace 31 with 3: 5223
654321 -> 6>=5>4, replace 65 with 6: 64321
*/
class MinNumReplace2AdjDigitsWMaxOf2
{

};
#endif
