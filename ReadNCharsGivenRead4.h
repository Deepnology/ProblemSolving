#ifndef READ_N_CHARS_GIVEN_READ4_H
#define READ_N_CHARS_GIVEN_READ4_H
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include "Debug.h"
/*
Leetcode: Read N chars given read4, I, II
I.
http://leetcode0.blogspot.tw/2015/03/read-n-characters-given-read4.html
The API: int read4(char *buf) reads 4 characters at a time from a file.
The return value is the actual number of characters read. For example, it returns 3 if there is only 3 characters left in the file.
By using the read4 API, implement the function int read(char *buf, int n) that reads n characters from the file.
Note:
The read function will only be called once for each test case.

II. call multiple times
http://leetcode0.blogspot.tw/2015/03/read-n-characters-given-read4-ii-call.html
The API: int read4(char *buf) reads 4 characters at a time from a file.
The return value is the actual number of characters read.
For example, it returns 3 if there is only 3 characters left in the file.
By using the read4 API, implement the function int read(char *buf, int n) that reads n characters from the file.
Note:
The read function may be called multiple times.

Algorithm
Keep track of a buffer with size 4 of prev read in chars.
Keep track of the count of prev read in chars in the buffer from begin.
Keep track of the count of prev read out chars in the buffer from begin.
*/
class ReadNCharsGivenRead4I
{
public:
	explicit ReadNCharsGivenRead4I(const std::string & text) : testText(text), testCharIdx(0)
	{}
	~ReadNCharsGivenRead4I(){}
private:
	const std::string testText;
	int testCharIdx;//points to the next char to be read

	//read a max of 4 chars into buf, return the number of actual read chars
	int Read4(std::string & buf)
	{
		int N = testText.size();
		int i = 0;
		for (; i < 4 && testCharIdx < N; ++i, ++testCharIdx)
		{
			buf[i] = testText[testCharIdx];
		}
		return i;
	}

public:
	//read a max of N chars into buf, return the number of actual read chars
	int ReadN(std::string & buf, int N)
	{
		int count = 0;
		std::string cache4(4, ' ');
		while (count < N)
		{
			//read 4 chars into cache4
			int countReadIn = Read4(cache4);

			//1. compute countReadOut to read out from cache4
			int countReadOut = std::min(countReadIn, N - count);

			//2. write countReadOut chars from cache4 into buf
			for (int i = 0; i < countReadOut; ++i)
				buf[count++] = cache4[i];

			if (countReadIn < 4)
				break;
		}

		return count;
	}



	void Test(int N)
	{
		std::cout << "ReadNCharsGivenRead4I for \"" << N << "\", \"" << testText << "\":" << std::endl;
		int n = testText.size();
		std::string tgt(N, ' ');
		int countReadIn = this->ReadN(tgt, N);//get called for once
		std::cout << countReadIn << ":	" << tgt << std::endl;
	}
};
class ReadNCharsGivenRead4II
{
public:
	explicit ReadNCharsGivenRead4II(const std::string & text) : testText(text), testCharIdx(0)
		, cache4(4, ' '), countReadIn(0), countReadOut(0)
	{}
	~ReadNCharsGivenRead4II(){}
private:
	const std::string testText;
	int testCharIdx;//points to the next char to be read

	//read a max of 4 chars into buf, return the number of actual read chars
	int Read4(std::string & buf)
	{
		int N = testText.size();
		int i = 0;
		for (; i < 4 && testCharIdx < N; ++i, ++testCharIdx)
		{
			buf[i] = testText[testCharIdx];
		}
		return i;
	}

public:
	//read a max of N chars into buf, return the number of actual read chars
	int ReadN(std::string & buf, int N)
	{
		int count = 0;

		//1. read the reamining chars in cache4 into buf
		int remaining = std::min(countReadIn - countReadOut, N);
		for (int i = 0; i < remaining; ++i)
			buf[count++] = cache4[countReadOut++];

		while (count < N)
		{
			//read 4 chars into cache4
			countReadIn = Read4(cache4);

			//1. compute countReadOut to read out from cache4
			countReadOut = std::min(countReadIn, N - count);

			//2. write countReadOut chars from cache4 into buf
			for (int i = 0; i < countReadOut; ++i)
				buf[count++] = cache4[i];

			if (countReadIn < 4)
				break;
		}

		return count;
	}
	std::string cache4;
	int countReadIn;//number of chars that was read in to cache from Read4, which is [0:countReadIn-1] in cache4
	int countReadOut;//number of chars that was read out from cache to buf, which is [0:countReadOut-1] in cache4

	//[countReadOut:countReadIn-1] are the remaining chars in cache4
	//that should be read in to buff first in the next call of ReadN





	void Test(int N)
	{
		std::cout << "ReadNCharsGivenRead4II for \"" << N << "\", \"" << testText << "\":" << std::endl;
		int n = testText.size();
		std::string tgt(N, ' ');
		int count = 0;
		while (count < n)
		{
			int countReadIn = this->ReadN(tgt, N);//get called for multiple times
			std::cout << countReadIn << ":	" << tgt << std::endl;
			count += countReadIn;
		}
	}
};
/*
ReadNCharsGivenRead4I for "25", "(+1Ig$|~Wm#vCRZB3$i6luR''R.".D":
25:	(+1Ig$|~Wm#vCRZB3$i6luR''
ReadNCharsGivenRead4I for "26", "[W%W3$rpyt0?slR9lfsny1QUhyQ#>b":
26:	[W%W3$rpyt0?slR9lfsny1QUhy
ReadNCharsGivenRead4I for "30", "I/d?58Xg4^ce>}76GCUzI0ci\cTZQ3":
30:	I/d?58Xg4^ce>}76GCUzI0ci\cTZQ3
ReadNCharsGivenRead4I for "3", ""MKlq~#zvpP},%VHv>;)p:M#Bv/5?@":
3:	"MK
ReadNCharsGivenRead4I for "35", "6J\P#_#DM%?K(*:w=9I(0E4Itn6Buu":
30:	6J\P#_#DM%?K(*:w=9I(0E4Itn6Buu     
ReadNCharsGivenRead4II for "1", "}#jFn`|@u5,th*9(H|x\107eT9_0dW":
1:	}
1:	#
1:	j
1:	F
1:	n
1:	`
1:	|
1:	@
1:	u
1:	5
1:	,
1:	t
1:	h
1:	*
1:	9
1:	(
1:	H
1:	|
1:	x
1:	\
1:	1
1:	0
1:	7
1:	e
1:	T
1:	9
1:	_
1:	0
1:	d
1:	W
ReadNCharsGivenRead4II for "11", "GpU5,R${U]4G"g~'+>{G|t!XpBupo4":
11:	GpU5,R${U]4
11:	G"g~'+>{G|t
8:	!XpBupo4G|t
ReadNCharsGivenRead4II for "20", "sm@-m4zC8Dind@(R$Gv6+G~9&]UK9y":
20:	sm@-m4zC8Dind@(R$Gv6
10:	+G~9&]UK9yind@(R$Gv6
ReadNCharsGivenRead4II for "34", "O"()AvkSQ+U`.1'Ni/1XY%:xELU(Y<":
30:	O"()AvkSQ+U`.1'Ni/1XY%:xELU(Y<    
ReadNCharsGivenRead4II for "14", "aF8JrN[y'<Avd9`@/XBxhnsQldDHH}":
14:	aF8JrN[y'<Avd9
14:	`@/XBxhnsQldDH
2:	H}/XBxhnsQldDH
*/
#endif