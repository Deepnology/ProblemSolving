#ifndef GRAY_CODE_H
#define GRAY_CODE_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, Recursion: Compute a Gray code
Write a function which takes as input a single positive integer n and returns an n-bit Gray code.
Leetcode: Gray Code
// The gray code is a binary numeral system where two successive values differ
// in only one bit.
//
// Given a non-negative integer n representing the "total number of bits" in the
// code, print the sequence of gray code. A gray code sequence must begin with
// 0.
//
// For example, given n = 2, return [0,1,3,2]. Its gray code sequence is:
//
// 00 - 0
// 01 - 1
// 11 - 3
// 10 - 2
//
// Complexity:
// O(2^n) time

For example: n = 4 bit
Gray Code:  0000, 0001, 0011, 0010, 0110, 0111, 0101, 0100, 1100, 1101, 1111, 1110, 1010, 1011, 1001, 1000
Binary   :  0000, 0001, 0010, 0011, 0100, 0101, 0110, 0111, 1000, 1001, 1010, 1011, 1100, 1101, 1110, 1111

Method 1: Reflected/Reversed List
http://www.programering.com/a/MDO0kDMwATM.html
n=1		n=2		n=3
0	0	00	00	000
1	1	01	01	001
    1	11	11	011
    0	10	10	010
            10	110
            11	111
            01	101
            00	100

1. concatenate the original list with a copy of itself in the reverse order
2. pad '0' to the left of the first half (original list)
3. pad '1' to the left of the second half (reflected/reversed list)

Method2: BinaryCode to GrayCode Formula
1011 -> 1110:
1011 -> 1(leftmost bit), 1(leftmost bit XOR 2nd leftmost bit, 1^0=1), 1(2nd leftmost bit XOR 3rd leftmost bit, 0^1=1), 0(3rd leftmost bit XOR 4th leftmost bit, 1^1 =0) = 1110
which is equivalent to (1011 >> 1) ^ 1011 = 1110
GrayCode = (BinaryCode >> 1) ^ BinaryCode

Method3:
http://www.cnblogs.com/lihaozy/archive/2012/12/31/2840437.html
Gray Code:
0 is 0.
The next is to toggle the rightmost bit (LSB).
Then the next is to toggle the left bit of the rightmost '1' bit.
Repeat the previous two steps until the rightmost '1' bit is now at the leftmost position.

Application of Gray Code: tournament tree
A tournament is really a node in a binary tree.
The value in each node contains the ranking of the best ranking team contained in the tournament tree.
It turns out that the gray code of the ranking-1 has a bit pattern that conveniently helps us descend the binary tree to the appropriate place at which to put the team.
"When descending the three, the bits in the gray code of the ranking from least-significant to most-significant indicate which branch to take."
For example: n = 3 bit
Gray Code:  000, 001, 011, 010, 110, 111, 101, 100
Rank:         1,   2,   3,   4,   5,   6,   7,   8 (assign players' ranks along with gray codes)
(reversed binary digit of gray code represents the result tournament index of its corresponding rank)
000 1
100 8
010 4
110 5
001 2
101 7
011 3
111 6
For example: n = 4 bit
Gray Code:  0000, 0001, 0011, 0010, 0110, 0111, 0101, 0100, 1100, 1101, 1111, 1110, 1010, 1011, 1001, 1000
Rank:		   1,    2,    3,    4,    5,    6,    7,    8,    9,   10,   11,   12,   13,   14,   15,   16 (assign players' ranks along with gray codes)
(reversed binary digit of gray code represents the result tournament index of its corresponding rank)
0000  1  
1000 16
0100  8
1100  9
0010  4
1010 13
0110  5
1110 12
0001  2
1001 15
0101  7
1101 10
0011  3
1011 14
0111  6
1111 11
*/
class GrayCode
{
public:
	GrayCode(){}
	~GrayCode(){}

	std::vector<int> ReflectedList(int n)//n is bit count
	{
		std::vector<int> res;
		res.reserve(1 << n);//n bits must have 2^n = 1 << n combinations
		res.push_back(0);//GrayCode 0 must be 0
		for (int i = 0; i < n; ++i)
		{
			int m = res.size();//size of original list
			for (int j = m - 1; j >= 0; --j)//generate the reversed list and push back
				res.push_back(res[j] | (1 << i));//pad a '1' bit to the left side of each binary code in the reversed list
		}
		std::cout << "GrayCode ReflectList for \"" << n << "\" bits: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
	
	std::vector<int> ReflectedListRecur(int n)//n is bit count
	{
		std::vector<int> res = this->recur(n);
		std::cout << "GrayCode ReflectListRecur for \"" << n << "\" bits: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
private:
	std::vector<int> recur(int n)
	{
		if (n == 0)
			return{ 0 };
		if (n == 1)
			return{ 0, 1 };

		std::vector<int> prev = this->recur(n - 1);

		//pad 1 to the reverse order of prev
		int N = prev.size();
		int pad1 = 1 << (n - 1);
		std::vector<int> rev;
		for (int i = N - 1; i >= 0; --i)
			rev.push_back(pad1 + prev[i]);

		//append the reversed ordered padded 1 sequence to the back of prev sequence
		prev.insert(prev.end(), rev.begin(), rev.end());
		return prev;
	}

public:
	std::vector<int> Formula(int n)//n is bit count
	{
		std::vector<int> res;
		res.reserve(1 << n);//n bits must have 2^n = 1 << n combinations
		for (int i = 0; i < (1 << n); ++i)
			res.push_back(i ^ (i >> 1));//GrayCode = BinaryCode ^ (BinaryCode >> 1)
		std::cout << "GrayCode Formula for \"" << n << "\" bits: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

public:
	std::vector<int> GetTournamentPlacement(int n)//n is number of tournament players, should be 1, 2, 4, 8, 16, 32, ...
	{
		int bitCount = (int)log2(n);//bitCount is gray code bit count, which is also depth of tournament tree
		std::vector<int> grayCodeV = this->ReflectedList(bitCount);
		std::vector<int> res(n);//n is size of leaf count
		for (int i = 0; i < n; ++i)
		{
			int rank = i + 1;
			int graycode = grayCodeV[i];
			//compute the reversed binary number of graycode, which will be the index of cur rank in res
			//reversed binary number of graycode represents traversing the tournament tree from top to bottom based on 0(go left) and 1(go right)
			int revNum = 0;
			for (int j = bitCount - 1; j >= 0; --j)
			{
				if ((graycode >> j) & 1)
					//revNum += (int)pow(2, bitCount - j - 1);
					revNum |= (1 << (bitCount - j - 1));
			}
			//std::cout << revNum << "," << rank << std::endl;
			res[revNum] = rank;
		}

		std::cout << "GrayCode GetTournamentPlacement for playersCount=" << n << ": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
};
/*
GrayCode ReflectList for "3" bits: 0, 1, 3, 2, 6, 7, 5, 4
GrayCode ReflectListRecur for "3" bits: 0, 1, 3, 2, 6, 7, 5, 4
GrayCode Formula for "3" bits: 0, 1, 3, 2, 6, 7, 5, 4
GrayCode ReflectList for "3" bits: 0, 1, 3, 2, 6, 7, 5, 4
GrayCode GetTournamentPlacement for playersCount=8: 1, 8, 4, 5, 2, 7, 3, 6
GrayCode ReflectList for "4" bits: 0, 1, 3, 2, 6, 7, 5, 4, 12, 13, 15, 14, 10, 11, 9, 8
GrayCode ReflectListRecur for "4" bits: 0, 1, 3, 2, 6, 7, 5, 4, 12, 13, 15, 14, 10, 11, 9, 8
GrayCode Formula for "4" bits: 0, 1, 3, 2, 6, 7, 5, 4, 12, 13, 15, 14, 10, 11, 9, 8
GrayCode ReflectList for "4" bits: 0, 1, 3, 2, 6, 7, 5, 4, 12, 13, 15, 14, 10, 11, 9, 8
GrayCode GetTournamentPlacement for playersCount=16: 1, 16, 8, 9, 4, 13, 5, 12, 2, 15, 7, 10, 3, 14, 6, 11
*/

/*
Google
Given an integer n (digit count), output all numbers in [0:10^n-1] in an order such that adjacent number's edit distance is 1.

0	00	000
1	01	001
2	02	002
3	03	003
4	04	004
5	05	005
6	06	006
7	07	007
8	08	008
9	09	009
	19	019
	18	018
	17	017
	16	016
	15	015
	14	014
	13	013
	12	012
	11	011
	10	010
	20	110
	21	111
	22	112
	23	113
	24	114
	25	115
	26	116
	27	117
	28	118
	29	119
	39	109
	38	108
	37	107
	36	106
	35	105
	34	104
	33	103
	32	102
	31	101
	30	100
	40
	41
	42
	43
	44
	45
	46
	47
	48
	49
	59
	58
	57
	56
	55
	54
	53
	52
	51
	50
	60
	61
	62
	63
	64
	65
	66
	67
	68
	69
	79
	78
	77
	76
	75
	74
	73
	72
	71
	70
	80
	81
	82
	83
	84
	85
	86
	87
	88
	89
	99
	98
	97
	96
	95
	94
	93
	92
	91
	90
*/
class GrayCodeDecimal
{
public:
	GrayCodeDecimal() {}

	std::vector<std::string> Generate(int n)
	{
		std::vector<std::string> res;
		std::vector<std::string> tmp;
		for (int i = 0; i < 10; ++i)
			tmp.push_back(std::to_string(i));
		res = tmp;//1-digit nums must be [0:9]
		
		//starting from 2-digit nums
		for (int i = 2; i <= n; ++i)
		{
			//append 0 to existing numbers
			for (int j = 0; j < (int)res.size(); ++j)
				res[j] = "0" + res[j];

			for (int j = 1; j < 10; ++j)
			{
				if (j & 1)//append "j + tmp[end:0]"
				{
					for (int k = (int)tmp.size() - 1; k >= 0; --k)
					{
						res.push_back(std::to_string(j) + tmp[k]);
					}
				}
				else//append "j + tmp[0:end]"
				{
					for (int k = 0; k < (int)tmp.size(); ++k)
					{
						res.push_back(std::to_string(j) + tmp[k]);
					}
				}
			}
			tmp = res;
		}

		std::cout << "GrayCodeDecimal Generate for \"" << n << "\"-digit: " << std::endl;
		std::cout << Debug::ToStr1D<std::string>()(res) << std::endl;
		return res;
	}
};
/*
GrayCodeDecimal Generate for "1"-digit:
0, 1, 2, 3, 4, 5, 6, 7, 8, 9
GrayCodeDecimal Generate for "2"-digit:
00, 01, 02, 03, 04, 05, 06, 07, 08, 09, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90
GrayCodeDecimal Generate for "3"-digit:
000, 001, 002, 003, 004, 005, 006, 007, 008, 009, 019, 018, 017, 016, 015, 014, 013, 012, 011, 010, 020, 021, 022, 023, 024, 025, 026, 027, 028, 029, 039, 038, 037, 036, 035, 034, 033, 032, 031, 030, 040, 041, 042, 043, 044, 045, 046, 047, 048, 049, 059, 058, 057, 056, 055, 054, 053, 052, 051, 050, 060, 061, 062, 063, 064, 065, 066, 067, 068, 069, 079, 078, 077, 076, 075, 074, 073, 072, 071, 070, 080, 081, 082, 083, 084, 085, 086, 087, 088, 089, 099, 098, 097, 096, 095, 094, 093, 092, 091, 090, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 189, 188, 187, 186, 185, 184, 183, 182, 181, 180, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 169, 168, 167, 166, 165, 164, 163, 162, 161, 160, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 149, 148, 147, 146, 145, 144, 143, 142, 141, 140, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 129, 128, 127, 126, 125, 124, 123, 122, 121, 120, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 109, 108, 107, 106, 105, 104, 103, 102, 101, 100, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 219, 218, 217, 216, 215, 214, 213, 212, 211, 210, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 239, 238, 237, 236, 235, 234, 233, 232, 231, 230, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 259, 258, 257, 256, 255, 254, 253, 252, 251, 250, 260, 261, 262, 263, 264, 265, 266, 267, 268, 269, 279, 278, 277, 276, 275, 274, 273, 272, 271, 270, 280, 281, 282, 283, 284, 285, 286, 287, 288, 289, 299, 298, 297, 296, 295, 294, 293, 292, 291, 290, 390, 391, 392, 393, 394, 395, 396, 397, 398, 399, 389, 388, 387, 386, 385, 384, 383, 382, 381, 380, 370, 371, 372, 373, 374, 375, 376, 377, 378, 379, 369, 368, 367, 366, 365, 364, 363, 362, 361, 360, 350, 351, 352, 353, 354, 355, 356, 357, 358, 359, 349, 348, 347, 346, 345, 344, 343, 342, 341, 340, 330, 331, 332, 333, 334, 335, 336, 337, 338, 339, 329, 328, 327, 326, 325, 324, 323, 322, 321, 320, 310, 311, 312, 313, 314, 315, 316, 317, 318, 319, 309, 308, 307, 306, 305, 304, 303, 302, 301, 300, 400, 401, 402, 403, 404, 405, 406, 407, 408, 409, 419, 418, 417, 416, 415, 414, 413, 412, 411, 410, 420, 421, 422, 423, 424, 425, 426, 427, 428, 429, 439, 438, 437, 436, 435, 434, 433, 432, 431, 430, 440, 441, 442, 443, 444, 445, 446, 447, 448, 449, 459, 458, 457, 456, 455, 454, 453, 452, 451, 450, 460, 461, 462, 463, 464, 465, 466, 467, 468, 469, 479, 478, 477, 476, 475, 474, 473, 472, 471, 470, 480, 481, 482, 483, 484, 485, 486, 487, 488, 489, 499, 498, 497, 496, 495, 494, 493, 492, 491, 490, 590, 591, 592, 593, 594, 595, 596, 597, 598, 599, 589, 588, 587, 586, 585, 584, 583, 582, 581, 580, 570, 571, 572, 573, 574, 575, 576, 577, 578, 579, 569, 568, 567, 566, 565, 564, 563, 562, 561, 560, 550, 551, 552, 553, 554, 555, 556, 557, 558, 559, 549, 548, 547, 546, 545, 544, 543, 542, 541, 540, 530, 531, 532, 533, 534, 535, 536, 537, 538, 539, 529, 528, 527, 526, 525, 524, 523, 522, 521, 520, 510, 511, 512, 513, 514, 515, 516, 517, 518, 519, 509, 508, 507, 506, 505, 504, 503, 502, 501, 500, 600, 601, 602, 603, 604, 605, 606, 607, 608, 609, 619, 618, 617, 616, 615, 614, 613, 612, 611, 610, 620, 621, 622, 623, 624, 625, 626, 627, 628, 629, 639, 638, 637, 636, 635, 634, 633, 632, 631, 630, 640, 641, 642, 643, 644, 645, 646, 647, 648, 649, 659, 658, 657, 656, 655, 654, 653, 652, 651, 650, 660, 661, 662, 663, 664, 665, 666, 667, 668, 669, 679, 678, 677, 676, 675, 674, 673, 672, 671, 670, 680, 681, 682, 683, 684, 685, 686, 687, 688, 689, 699, 698, 697, 696, 695, 694, 693, 692, 691, 690, 790, 791, 792, 793, 794, 795, 796, 797, 798, 799, 789, 788, 787, 786, 785, 784, 783, 782, 781, 780, 770, 771, 772, 773, 774, 775, 776, 777, 778, 779, 769, 768, 767, 766, 765, 764, 763, 762, 761, 760, 750, 751, 752, 753, 754, 755, 756, 757, 758, 759, 749, 748, 747, 746, 745, 744, 743, 742, 741, 740, 730, 731, 732, 733, 734, 735, 736, 737, 738, 739, 729, 728, 727, 726, 725, 724, 723, 722, 721, 720, 710, 711, 712, 713, 714, 715, 716, 717, 718, 719, 709, 708, 707, 706, 705, 704, 703, 702, 701, 700, 800, 801, 802, 803, 804, 805, 806, 807, 808, 809, 819, 818, 817, 816, 815, 814, 813, 812, 811, 810, 820, 821, 822, 823, 824, 825, 826, 827, 828, 829, 839, 838, 837, 836, 835, 834, 833, 832, 831, 830, 840, 841, 842, 843, 844, 845, 846, 847, 848, 849, 859, 858, 857, 856, 855, 854, 853, 852, 851, 850, 860, 861, 862, 863, 864, 865, 866, 867, 868, 869, 879, 878, 877, 876, 875, 874, 873, 872, 871, 870, 880, 881, 882, 883, 884, 885, 886, 887, 888, 889, 899, 898, 897, 896, 895, 894, 893, 892, 891, 890, 990, 991, 992, 993, 994, 995, 996, 997, 998, 999, 989, 988, 987, 986, 985, 984, 983, 982, 981, 980, 970, 971, 972, 973, 974, 975, 976, 977, 978, 979, 969, 968, 967, 966, 965, 964, 963, 962, 961, 960, 950, 951, 952, 953, 954, 955, 956, 957, 958, 959, 949, 948, 947, 946, 945, 944, 943, 942, 941, 940, 930, 931, 932, 933, 934, 935, 936, 937, 938, 939, 929, 928, 927, 926, 925, 924, 923, 922, 921, 920, 910, 911, 912, 913, 914, 915, 916, 917, 918, 919, 909, 908, 907, 906, 905, 904, 903, 902, 901, 900
*/
#endif