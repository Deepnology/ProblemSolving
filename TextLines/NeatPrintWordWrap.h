#ifndef NEAT_PRINT_WORD_WRAP_H
#define NEAT_PRINT_WORD_WRAP_H
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <limits.h>
#include "Debug.h"
/*
Elements of programming interview, DynamicProgramming: The pretty printing problem
A collection of dynamic programming
Google
http://stackoverflow.com/questions/2979498/algorithm-for-neatly-printing-a-paragraph-on-a-printer
http://www.careercup.com/question?id=9816662
Consider the problem of laying out text using a fixed width font.
Each line can hold no more than L characters.
Words on a line are to be separated by exactly one blank.
Therefore, we may be left with whitespace at the end of a line (since the next word will not fit in the remaining space).
This whitespace is visually unappealing.

Define the messiness (cost) of the end-of-line whitespace as follows.
The messiness of a line ending with b blank characters is 2^b.
The total messiness of a sequence of lines is the sum of the messinesses of all the lines.
A sequence of words can be split across lines in different ways with different messiness.

Given text, i.e., a string of words separated by single blanks, decompose the text into lines such that no word is split across lines and the messiness of the decomposition is minimized.
Each line can hold no more than L characters.
How would you change your algorithm if the messiness is the sum of the messinesses of all but the last line?

For the input sequence of "aaa, bb, cc, ddddd, eee, f, gg, h, i, jjj" and line size of 6:
Layout1.
			cost:
aaa---		2^3=8
bb cc-		2^1=2
ddddd-		2^1=2
eee f-		2^1=2
gg h i		2^0=1	total cost of all but last line: 15
jjj---		2^3=8
-------------------
total cost:	20

Layout2.
			cost:
aaa bb		2^0=1
cc----		2^4=16
ddddd-		2^1=2
eee f-		2^1=2
gg h i		2^0=1	total cost of all but last line: 22
jjj---		2^3=8
-------------------
total cost:	30

DP1D: O(n * lineSize) time, O(n) space

Algorithm
Keep track of min total cost of each word.
For each word, view it as the end of a line, compute current line cost to accomodate it and accumulate prev min total cost,
and for all prev words of current word that can be accommodated within the line, update the min total cost if accommodating that word within the line results in a smaller total cost.

Variant: Suppose the messiness of a line ending with b blank characters is defined to be b.
Can you solve the messiness minimization problem in O(n) time and O(1) space?
Use Greedy algorithm. See also TextJustification.h
*/
class NeatPrintWordWrap
{
public:
	NeatPrintWordWrap(){}
	~NeatPrintWordWrap(){}

	int MinCostOnlyDP1D(const std::vector<std::string> & strs, int lineSize)
	{
		int N = strs.size();
		std::vector<unsigned long long> dp(N, std::numeric_limits<unsigned long long>::max());
		//dp[i]: accumulated min total cost for strs[0:i]
		for (int lnEnd = 0; lnEnd < N; ++lnEnd)
		{
			int len = lineSize - strs[lnEnd].size();
			//use a new line to accomodate only strs[lnEnd], compute its cost (1<<len) and then accumulate w/ prev min total cost (dp[lnEnd-1])
			dp[lnEnd] = std::min(dp[lnEnd], (lnEnd - 1 < 0 ? 0 : dp[lnEnd - 1]) + ((unsigned long long)1 << len));//(dp[lnEnd-1]: min total cost w/o accomodating strs[lnEnd])

			//for all prev words that can be accomodated within this line, try to accomodate them in cur line
			for (int lnStart = lnEnd - 1; lnStart >= 0; --lnStart)
			{
				len -= (strs[lnStart].size() + 1);
				if (len < 0)
					break;
				//if accommodating strs[lnStart] within cur line result in a smaller total cost
				dp[lnEnd] = std::min(dp[lnEnd], (lnStart - 1 < 0 ? 0 : dp[lnStart - 1]) + ((unsigned long long)1 << len));//(dp[lnStart-1]: min total cost w/o accomodating strs[lnStart])
			}
		}

		/*
		the minCost of all but the last line:
		greedy approach: find the min of all the accumulated-min-cost among the words where a line size can accommodate from the end of text
		*/
		unsigned long long minCostWoLastLine = N >= 2 ? dp[N - 2] : 0;
		int len = lineSize - strs[N - 1].size();//try to accomodate words as many as possible in the last line from end of text
		for (int i = N - 2; i >= 0; --i)
		{
			len -= (strs[i].size() + 1);
			if (len < 0)
				break;
			minCostWoLastLine = std::min(minCostWoLastLine, (i - 1 < 0 ? 0 : dp[i - 1]));
		}

		std::cout << "NeatPrintWordWrap MinCostOnlyDP1D for lineSize=\"" << lineSize << "\", \"" << Debug::ToStr1D<std::string>()(strs) << "\": " << dp[N - 1] << ", minCostWoLastLine: " << minCostWoLastLine << std::endl;
		std::cout << Debug::ToStr1D<unsigned long long>()(dp) << std::endl;
		return (int)dp[N - 1];
	}

	int MinCost_DP1D(const std::vector<std::string> & strs, int lineSize)
	{
		int N = strs.size();
		std::vector<unsigned long long> dp(N, std::numeric_limits<unsigned long long>::max());
		//dp[i]: accumulated min total cost for strs[0:i]
		std::vector<std::vector<int> > bk(N, std::vector<int>(N, 0));//for printing only
		//bk[i]: accumulated min total cost newline break points for strs[0:i]

		for (int lnEnd = 0; lnEnd < N; ++lnEnd)//for each word, view it as the end of a line
		{
			int len = lineSize - strs[lnEnd].size();
			bk[lnEnd][lnEnd] = 1;/*mark strs[lnEnd] as a newline break point*/
			
			//compute cur line cost to accommodate only strs[lnEnd] and accumulate prev min total cost
			if ((lnEnd - 1 < 0 ? 0 : dp[lnEnd - 1]) + ((unsigned long long)1 << len) < dp[lnEnd])
			{
				dp[lnEnd] = (lnEnd - 1 < 0 ? 0 : dp[lnEnd - 1]) + ((unsigned long long)1 << len);
				if (lnEnd - 1 >= 0)
				{
					for (int i = 0; i < lnEnd; ++i)/*copy bk[lnEnd-1] to bk[lnEnd]*/
						bk[lnEnd][i] = bk[lnEnd - 1][i];
				}
			}
			
			std::vector<int> tmp;/*for bk[] only, keep track of prev min total cost bk[lnStart-1] config*/
			for (int lnStart = lnEnd - 1; lnStart >= 0; --lnStart)//for all previous words that can be accommodated within the line, update dp[lnEnd]
			{
				len -= (strs[lnStart].size() + 1);//subtrack string length and one space
				if (len < 0)/*now copy tmp to bk[lnEnd]*/
				{
					if (tmp.empty())
					{
						bk[lnEnd][lnStart + 1] = 1;/*exclude prev included strs[lnStart+1] to cur line*/
					}
					else
					{
						int s = tmp.size();
						for (int i = 0; i < s; ++i)
							bk[lnEnd][i] = tmp[i];
					}
					break;
				}
				bk[lnEnd][lnStart] = 0;/*now include strs[lnStart] to cur line*/
				if ((lnStart - 1 < 0 ? 0 : dp[lnStart - 1]) + ((unsigned long long)1 << len) < dp[lnEnd])//if accommodating strs[lnStart] within the line result in a smaller total cost
				{
					dp[lnEnd] = (lnStart - 1 < 0 ? 0 : dp[lnStart - 1]) + ((unsigned long long)1 << len);
					
					if (lnStart - 1 >= 0)/*copy bk[lnStart-1] config to tmp*/
					{
						tmp.clear();
						for (int i = 0; i < lnStart; ++i)
							tmp.push_back(bk[lnStart - 1][i]);
					}
				}
			}
		}

		/*
		the minCost of all but the last line:
		greedy approach: find the min of all the accumulated-min-cost among the words where a line size can accommodate from the end of text
		*/
		unsigned long long minCostWoLastLine = N >= 2 ? dp[N - 2] : 0;
		int idx = N >= 2 ? N - 2 : 0;
		int len = lineSize - strs[N - 1].size();
		for (int i = N - 2; i >= 0; --i)
		{
			len -= (strs[i].size() + 1);
			if (len < 0)
				break;
			if ((i - 1 < 0 ? 0 : dp[i - 1]) < minCostWoLastLine)
			{
				minCostWoLastLine = (i - 1 < 0 ? 0 : dp[i - 1]);
				if (i - 1 >= 0)
					idx = i - 1;
			}
		}
		std::vector<int> bkWoLastLine = bk[idx];/*copy bk[idx] to bkWoLastLine*/
		for (int i = idx + 1; i < N; ++i)/*remove all newline break points in strs[idx+1:N-2], add a newline break point at strs[N-1]*/
		{
			if (i == N - 1)
				bkWoLastLine[i] = 1;
			else
				bkWoLastLine[i] = 0;
		}

		std::cout << "NeatPrintWordWrap MinCost_DP1D for lineSize=\"" << lineSize << "\", \"" << Debug::ToStr1D<std::string>()(strs) << "\": " << dp[N - 1] << ", minCostWoLastLine: " << minCostWoLastLine << std::endl;
		std::cout << Debug::ToStr1D<unsigned long long>()(dp) << std::endl;
		//Debug::Print2D<int>()(bk, false);
		this->Print(strs, lineSize, bk[N - 1], true);
		this->Print(strs, lineSize, bkWoLastLine, false);
		return (int)dp[N - 1];
	}

private:
	void Print(const std::vector<std::string> & strs, int lineSize, const std::vector<int> & bkv, bool countLastLine)
	{
		std::cout << Debug::ToStr1D<int>()(bkv) << std::endl;
		int N = strs.size();
		int curSize = 0;
		unsigned long long cost = 0;
		std::ostringstream oss;
		for (int i = 0; i < N; ++i)
		{
			oss << strs[i];
			curSize += strs[i].size();
			if (bkv[i])
			{
				if (i != N - 1 || countLastLine)
				{
					int numBlank = lineSize - curSize;
					while (numBlank--)
						oss << "-";
					oss << "	" << ((unsigned long long)1 << (lineSize - curSize));
				}

				oss << std::endl;

				if (i != N - 1 || countLastLine)
					cost += ((unsigned long long)1 << (lineSize - curSize));

				curSize = 0;
			}
			else
			{
				oss << " ";
				++curSize;
			}
		}
		std::cout << oss.str() << "minCost: " << cost << std::endl;
	}

};

/*
line size: 36
I have inserted a large number of---		2^3=8
new examples from the papers for the		2^0=1
Mathematical Tripos during the last-		2^1=2
twenty years, which should be useful		2^0=1		total cost of all but last line: 12
to Cambridge students.--------------		2^14=16384
-------------------------------------------------------
total cost									16396


line size: 16
This is an------		2^6=64
example of text-		2^1=2	total cost of all but last line: 66
justification.--		2^2=4
---------------------------------------
total cost:				70


line size: 14
This is-------		2^7=128
an example----		2^4=16
of text-------		2^7=128		total cost of all but last line: 272
justification.		2^0=1
---------------------------------------
total cost:			273
*/
/*
NeatPrintWordWrap MinCost_DP1D for lineSize="16", "This, is, an, example, of, text, justification.": 70, minCostWoLastLine: 66
4096, 512, 64, 576, 128, 66, 70
0, 0, 1, 0, 0, 1, 1
This is an------	64
example of text-	2
justification.--	4
minCost: 70
0, 0, 1, 0, 0, 1, 1
This is an------	64
example of text-	2
justification.
minCost: 66
NeatPrintWordWrap MinCost_DP1D for lineSize="14", "This, is, an, example, of, text, justification.": 273, minCostWoLastLine: 272
1024, 128, 16, 144, 32, 272, 273
0, 1, 0, 1, 0, 1, 1
This is-------	128
an example----	16
of text-------	128
justification.	1
minCost: 273
0, 1, 0, 1, 0, 1, 1
This is-------	128
an example----	16
of text-------	128
justification.
minCost: 272
NeatPrintWordWrap MinCost_DP1D for lineSize="16", "Text, justification, is, an, example, of, this.": 4368, minCostWoLastLine: 4105
4096, 4104, 4097, 6152, 4112, 4105, 4368
1, 1, 0, 0, 1, 0, 1
Text------------	4096
justification---	8
is an example---	8
of this.--------	256
minCost: 4368
1, 0, 1, 0, 0, 1, 1
Text------------	4096
justification is	1
an example of---	8
this.
minCost: 4105
NeatPrintWordWrap MinCost_DP1D for lineSize="14", "Text, justification, is, an, example, of, this.": 1092, minCostWoLastLine: 1028
1024, 1026, 5122, 1538, 1028, 1554, 1092
1, 1, 0, 0, 1, 0, 1
Text----------	1024
justification-	2
is an example-	2
of this.------	64
minCost: 1092
1, 1, 0, 0, 1, 0, 1
Text----------	1024
justification-	2
is an example-	2
of this.
minCost: 1028
NeatPrintWordWrap MinCost_DP1D for lineSize="6", "aaa, bb, cc, ddddd, eee, f, gg, h, i, jjj": 20, minCostWoLastLine: 15
8, 1, 10, 12, 20, 14, 24, 18, 15, 20
1, 0, 1, 1, 0, 1, 0, 1, 0, 1
aaa---	8
bb cc-	2
ddddd-	2
eee f-	2
gg h--	4
i jjj-	2
minCost: 20
1, 0, 1, 1, 0, 1, 0, 0, 1, 1
aaa---	8
bb cc-	2
ddddd-	2
eee f-	2
gg h i	1
jjj
minCost: 15
NeatPrintWordWrap MinCost_DP1D for lineSize="15", "Geeks, for, Geeks, presents, word, wrap, problem": 13, minCostWoLastLine: 5
1024, 64, 1, 66, 5, 130, 13
0, 0, 1, 0, 1, 0, 1
Geeks for Geeks	1
presents word--	4
wrap problem---	8
minCost: 13
0, 0, 1, 0, 1, 0, 1
Geeks for Geeks	1
presents word--	4
wrap problem
minCost: 5
NeatPrintWordWrap MinCost_DP1D for lineSize="11", "The, quick, brown, fox, jumped, over, the, lazy, dogs.": 50, minCostWoLastLine: 17
256, 4, 68, 8, 40, 9, 48, 17, 50
0, 1, 0, 1, 1, 0, 1, 0, 1
The quick--	4
brown fox--	4
jumped-----	32
over the---	8
lazy dogs.-	2
minCost: 50
0, 1, 0, 1, 0, 1, 0, 1, 1
The quick--	4
brown fox--	4
jumped over	1
the lazy---	8
dogs.
minCost: 17
NeatPrintWordWrap MinCost_DP1D for lineSize="36", "I, have, inserted, a, large, number, of, new, examples, from, the, papers, for, the, Mathematical, Tripos, during, the, last, twenty, years,, which, should, be, useful, to, Cambridge, students.": 76, minCostWoLastLine: 12
34359738368, 1073741824, 2097152, 524288, 8192, 64, 8, 655360, 24576, 8704, 4160, 96, 24, 9, 4672, 608, 88, 28, 11, 4800, 736, 344, 60, 32, 12, 2784, 472, 76
0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1
I have inserted a large number of---	8
new examples from the papers for----	16
the Mathematical Tripos during the--	4
last twenty years, which should-----	32
be useful to Cambridge students.----	16
minCost: 76
0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1
I have inserted a large number of---	8
new examples from the papers for the	1
Mathematical Tripos during the last-	2
twenty years, which should be useful	1
to Cambridge students.
minCost: 12
NeatPrintWordWrap MinCost_DP1D for lineSize="14", "I, have, inserted, a, large, number, of, new, examples, from, the, papers, for, the, Mathematical, Tripos, during, the, last, twenty, years,, which, should, be, useful, to, Cambridge, students.": 693, minCostWoLastLine: 661
8192, 256, 320, 272, 448, 276, 480, 450, 484, 452, 548, 468, 453, 549, 553, 809, 555, 825, 619, 833, 621, 837, 625, 869, 657, 629, 661, 693
0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1
I have--------	256
inserted------	64
a large-------	128
number of-----	32
new examples--	4
from the------	64
papers for the	1
Mathematical--	4
Tripos during-	2
the last------	64
twenty years,-	2
which should--	4
be useful to--	4
Cambridge-----	32
students.-----	32
minCost: 693
0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1
I have--------	256
inserted------	64
a large-------	128
number of-----	32
new examples--	4
from the------	64
papers for the	1
Mathematical--	4
Tripos during-	2
the last------	64
twenty years,-	2
which should--	4
be useful to--	4
Cambridge-----	32
students.
minCost: 661
NeatPrintWordWrap MinCost_DP1D for lineSize="16", "I, have, inserted, a, large, number, of, new, examples, from, the, papers, for, the, Mathematical, Tripos, during, the, last, twenty, years,, which, should, be, useful, to, Cambridge, students.": 455, minCostWoLastLine: 327
32768, 1024, 2, 1088, 514, 6, 642, 522, 8, 530, 264, 10, 328, 268, 284, 1308, 292, 1372, 548, 294, 556, 310, 572, 438, 311, 566, 327, 455
0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1
I have inserted-	2
a large number--	4
of new examples-	2
from the--------	256
papers for the--	4
Mathematical----	16
Tripos during---	8
the last twenty-	2
years, which----	16
should be useful	1
to Cambridge----	16
students.-------	128
minCost: 455
0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1
I have inserted-	2
a large number--	4
of new examples-	2
from the--------	256
papers for the--	4
Mathematical----	16
Tripos during---	8
the last twenty-	2
years, which----	16
should be useful	1
to Cambridge----	16
students.
minCost: 327
NeatPrintWordWrap MinCost_DP1D for lineSize="19", "I, have, inserted, a, large, number, of, new, examples, from, the, papers, for, the, Mathematical, Tripos, during, the, last, twenty, years,, which, should, be, useful, to, Cambridge, students.": 46, minCostWoLastLine: 45
262144, 8192, 16, 4, 4112, 48, 20, 5, 64, 24, 9, 80, 56, 26, 64, 27, 128, 68, 43, 144, 70, 44, 145, 86, 52, 45, 87, 46
0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1
I have inserted a--	4
large number of----	16
new examples from--	4
the papers for the-	2
Mathematical Tripos	1
during the last----	16
twenty years, which	1
should be useful to	1
Cambridge students.	1
minCost: 46
0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1
I have inserted a--	4
large number of----	16
new examples from--	4
the papers for the-	2
Mathematical Tripos	1
during the last----	16
twenty years, which	1
should be useful to	1
Cambridge students.
minCost: 45
NeatPrintWordWrap MinCost_DP1D for lineSize="25", "I, have, inserted, a, large, number, of, new, examples, from, the, papers, for, the, Mathematical, Tripos, during, the, last, twenty, years,, which, should, be, useful, to, Cambridge, students.": 554, minCostWoLastLine: 160
16777216, 524288, 1024, 256, 4, 3072, 1280, 320, 12, 1536, 576, 322, 76, 16, 354, 80, 4450, 610, 362, 88, 738, 426, 152, 96, 746, 490, 160, 554
0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1
I have inserted a--------	256
large number of new------	64
examples from the papers-	2
for the Mathematical-----	32
Tripos during the last---	8
twenty years, which------	64
should be useful to------	64
Cambridge students.------	64
minCost: 554
0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1
I have inserted a large--	4
number of new examples---	8
from the papers for the--	4
Mathematical Tripos------	64
during the last twenty---	8
years, which should be---	8
useful to Cambridge------	64
students.
minCost: 160
NeatPrintWordWrap MinCost_DP1D for lineSize="65", "Permission, is, hereby, granted,, free, of, charge,, to, any, person, obtaining, a, copy, of, this, software, and, associated, documentation, files, (the, "Software"),, to, deal, in, the, Software, without, restriction,, including, without, limitation, the, rights, to, use,, copy,, modify,, merge,, publish, distribute,, sublicense,, and/or, sell, copies, of, the, Software,, and, to, permit, persons, to, whom, the, Software, is, furnished, to, do, so,, subject, to, the, following, conditions:": 191232, minCostWoLastLine: 1352
36028797018963968, 4503599627370496, 35184372088832, 68719476736, 2147483648, 268435456, 1048576, 131072, 8192, 64, 4294967296, 2684354560, 402653184, 285212672, 135266304, 1310720, 262144, 9216, 72, 139460608, 68419584, 393216, 278528, 262656, 140288, 17408, 9232, 1096, 2490368, 294912, 156672, 17536, 13328, 9264, 2120, 1128, 2494464, 311296, 189440, 156800, 14352, 2376, 1192, 1130, 222208, 193536, 189696, 156864, 30736, 16400, 14368, 2632, 2408, 1320, 1200, 194048, 190720, 47120, 32784, 18448, 16528, 14432, 4680, 2760, 1352, 191232
0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1
Permission is hereby granted, free of charge, to any-------------	8192
person obtaining a copy of this software and associated----------	1024
documentation files (the "Software"), to deal in-----------------	131072
the Software without restriction, including without--------------	16384
limitation the rights to use, copy, modify, merge,---------------	32768
publish distribute, sublicense, and/or sell copies of the--------	256
Software, and to permit persons to whom the Software is----------	1024
furnished to do so, subject to the following conditions:---------	512
minCost: 191232
0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1
Permission is hereby granted, free of charge, to any person------	64
obtaining a copy of this software and associated documentation---	8
files (the "Software"), to deal in the Software without----------	1024
restriction, including without limitation the rights to use,-----	32
copy, modify, merge, publish distribute, sublicense, and/or------	64
sell copies of the Software, and to permit persons to whom-------	128
the Software is furnished to do so, subject to the following-----	32
conditions:
minCost: 1352
*/
#endif