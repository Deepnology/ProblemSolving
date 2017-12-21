/*SuffixArray*/
#ifndef MIN_LEXICOGRAPHIC_STR_ROTATION_H
#define MIN_LEXICOGRAPHIC_STR_ROTATION_H
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Debug.h"
#include "SuffixArray.h"
/*
http://www.stanford.edu/class/cs97si/suffix-array.pdf
https://icpcarchive.ecs.baylor.edu/index.php?option=onlinejudge&page=show_problem&problem=756
http://www.careercup.com/question?id=14711684
Some time the programmers have very strange ways to hide their passwords. 
See for example how Billy "Hacker" Geits hide his password. 
Billy chooses a string S composed of small Latin letters with length L. 
Then he makes all L- 1 one-letter left cyclic shifts of the string and takes as a password one prefix of the lexicographically first of the obtained strings (including S). 
For example let consider the string alabala. 
The cyclic one-letter left shifts (including the initial string) are:
alabala
labalaa
abalaal
balaala
alaalab
laalaba
aalabal  <---  the lexicographical first
and lexicographically first of them is the string aalabal. 
The first letter of this string is in position 6 in the initial string (the positions in the string are counted from 0).

Write a program that for given string S finds the start position of the smallest lexicographically one-letter left cyclic shift of this string. 
If the smallest lexicographically left shift appears more than once then the program have to output the smallest initial position.

Consider a string of length n (1 <= n <= 100000).
Determine its "minimum lexicographic rotation".

Usually, when having to handle problems that involve string rotations, one would rather concatenate the string with itself in order to simplify the task.
After, the minimal sequence of length n is requested.

see also RotateArray.h, RotatedStr.h, CircularQueueByArray.h
*/
class MinLexicographicStrRotation
{
public:
	MinLexicographicStrRotation(){}
	~MinLexicographicStrRotation(){}

	std::string SuffixArray(const std::string & s)
	{
		if (s.size() <= 1)
			return 0;
		std::string concatenation = s + s;
		SuffixArraySimple suffixes(concatenation);//O(nlogn) or O(n(log^2)n)
		int M = s.size();
		int N = concatenation.size();
		int minimal = -1;
		//the first suffix from sorted begin whose length is >= M should be the answer
		for (int i = 0; i < suffixes.Size(); ++i)
		{
			if (minimal == -1 && (int)concatenation.substr(suffixes[i]).size() >= M)
			{
				minimal = i;
				break;
			}
		}
		
		std::cout << "MinLexicographicStrRotation SuffixArray for \"" << s << "\": " << concatenation.substr(suffixes[minimal], M) << std::endl;
		return concatenation.substr(suffixes[minimal], M);
	}

	std::string Iterate(const std::string & s)//O(n) time
	{
		std::string concat = s + s;
		int N = concat.size();
		int minBegin = -1;//1. keep track of minBegin
		int equalCount = 0;//2. keep track of the current equal elements in [minBegin,minBegin+equalCount) and [i-equalCount,i)
		//the current element i has to compare with the next element of [minBegin,minBegin+equalCount)
		for (int i = 0; i < N; ++i)
		{
			if (minBegin == -1)
			{
				minBegin = i;
				
				this->Print(concat, i, minBegin, equalCount);
			}
			else if (concat[i] < concat[minBegin])//cur is smaller than minBegin
			{
				this->Print(concat, i, minBegin, equalCount);

				minBegin = i;
				equalCount = 0;
			}
			else if (concat[i] == concat[minBegin + equalCount])//cur is equal to the next of [minBegin,minBegin+equalCount)
			{
				this->Print(concat, i, minBegin, equalCount);

				++equalCount;
			}
			else if (concat[i] < concat[minBegin + equalCount])//cur is smaller than the next of [minBegin,minBegin+equalCount)
			{
				this->Print(concat, i, minBegin, equalCount);

				minBegin = i - equalCount;//update minBegin to i-equalCount (the leftmost equal element of cur)
				equalCount = 0;//reset
				if (concat[i] == concat[minBegin])
					equalCount = 1;
			}
			else//cur is greater than the next of [minBegin,minBegin+equalCount)
			{
				this->Print(concat, i, minBegin, equalCount);

				equalCount = 0;//reset
			}
		}

		std::cout << "MinLexicographicStrRotation Iterate for \"" << s << "\": " << concat.substr(minBegin, s.size()) << std::endl;
		return concat.substr(minBegin, s.size());
	}

private:
	void Print(const std::string & concat, int i, int minBegin, int equalCount)
	{
		std::ostringstream oss;
		for (int j = 0; j < i; ++j)
			oss << " ";
		oss << "|";
		std::cout << oss.str() << std::endl;
		std::cout << concat << std::endl;
		oss.str(std::string());
		for (int j = 0; j < minBegin; ++j)
			oss << " ";
		if (equalCount == 0)
			oss << "^";
		else
		{
			for (int j = 0; j < equalCount; ++j)
				oss << "-";
			oss << "^";
		}
		std::cout << oss.str() << std::endl;
	}
};
/*
SuffixArraySimple for "alabalaalabala":
0:	a
1:	aalabala--------------->first suffix whose length >= 7
2:	abala
3:	abalaalabala
4:	ala
5:	alaalabala
6:	alabala
7:	alabalaalabala
8:	bala
9:	balaalabala
10:	la
11:	laalabala
12:	labala
13:	labalaalabala
MinLexicographicStrRotation SuffixArray for "alabala": aalabal
SuffixArraySimple for "baabaabaabaa":
0:	a
1:	aa
2:	aabaa
3:	aabaabaa--------------->first suffix whose length >= 6
4:	aabaabaabaa
5:	abaa
6:	abaabaa
7:	abaabaabaa
8:	baa
9:	baabaa
10:	baabaabaa
11:	baabaabaabaa
MinLexicographicStrRotation SuffixArray for "baabaa": aabaab
SuffixArraySimple for "bcabdadabbcabdadab":
0:	ab
1:	abbcabdadab--------------->first suffix whose length >= 9
2:	abdadab
3:	abdadabbcabdadab
4:	adab
5:	adabbcabdadab
6:	b
7:	bbcabdadab
8:	bcabdadab
9:	bcabdadabbcabdadab
10:	bdadab
11:	bdadabbcabdadab
12:	cabdadab
13:	cabdadabbcabdadab
14:	dab
15:	dabbcabdadab
16:	dadab
17:	dadabbcabdadab
MinLexicographicStrRotation SuffixArray for "bcabdadab": abbcabdad

|
alabalaalabala
^
 |
alabalaalabala
^
  |
alabalaalabala
^
   |
alabalaalabala
-^
    |
alabalaalabala
  ^
     |
alabalaalabala
  -^
      |
alabalaalabala
  ^
       |
alabalaalabala
  -^
        |
alabalaalabala
      -^
         |
alabalaalabala
      ^
          |
alabalaalabala
      -^
           |
alabalaalabala
      ^
            |
alabalaalabala
      -^
             |
alabalaalabala
      ^
MinLexicographicStrRotation Iterate for "alabala": aalabal
|
baabaabaabaa
^
 |
baabaabaabaa
^
  |
baabaabaabaa
 ^
   |
baabaabaabaa
 -^
    |
baabaabaabaa
 ^
     |
baabaabaabaa
 -^
      |
baabaabaabaa
 --^
       |
baabaabaabaa
 ---^
        |
baabaabaabaa
 ----^
         |
baabaabaabaa
 -----^
          |
baabaabaabaa
 ------^
           |
baabaabaabaa
 -------^
MinLexicographicStrRotation Iterate for "baabaa": aabaab
|
bcabdadabbcabdadab
^
 |
bcabdadabbcabdadab
^
  |
bcabdadabbcabdadab
^
   |
bcabdadabbcabdadab
  ^
    |
bcabdadabbcabdadab
  ^
     |
bcabdadabbcabdadab
  ^
      |
bcabdadabbcabdadab
  -^
       |
bcabdadabbcabdadab
  ^
        |
bcabdadabbcabdadab
  -^
         |
bcabdadabbcabdadab
  --^
          |
bcabdadabbcabdadab
       ^
           |
bcabdadabbcabdadab
       ^
            |
bcabdadabbcabdadab
       -^
             |
bcabdadabbcabdadab
       --^
              |
bcabdadabbcabdadab
       ^
               |
bcabdadabbcabdadab
       -^
                |
bcabdadabbcabdadab
       ^
                 |
bcabdadabbcabdadab
       -^
MinLexicographicStrRotation Iterate for "bcabdadab": abbcabdad
*/


#endif