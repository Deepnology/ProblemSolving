#ifndef COUNT_NUMS_W_SAME_HALF_DIGIT_SUM_H
#define COUNT_NUMS_W_SAME_HALF_DIGIT_SUM_H
#include "Debug.h"
/*
Bloomberg
http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=283087&extra=page%3D2%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3046%5D%5Bvalue%5D%3D14%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311
Count numbers with 6 digits whose first 3 digits' sum equal to last 3 digits' sum.
Numbers are in [100000:999999].
Need to take care of leading 0s.
Ex: 102012, 123213
=>
Use a unordered_map<sum, array of 3 digits' combinations>
Find all combinations of 3 digits, then insert into unordered_map.
Foreach sum in unordered_map: enumerate all possible pairs of 3 digits' combinations
Ex: sum==3, 003 030 300 120 102 012 021 210 201 111
where nums w/o leading 0s have 6 choices, nums w/ or w/o leading 0s have 10 choices
so 6*10 in total
*/
class CountNumsWSameHalfDigitSum
{
public:
	CountNumsWSameHalfDigitSum() {}

};
#endif
