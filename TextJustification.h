#ifndef TEXT_JUSTFICATION_H
#define TEXT_JUSTFICATION_H
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, Strings: Justify text
https://github.com/anson627/leetcode/blob/master/TextJustification/TextJustification.cpp
// Given an array of words and a length L, format the text such that each line
// has exactly L characters and is fully (left and right) justified.
//
// You should pack your words in a greedy approach; that is, pack as many words
// as you can in each line. Pad extra spaces ' ' when necessary so that each
// line has exactly L characters.
//
// Extra spaces between words should be distributed as evenly as possible. If
// the number of spaces on a line do not divide evenly between words, the empty
// slots on the left will be assigned more spaces than the slots on the right.
//
// For the last line of text, it should be left justified and no extra space is
// inserted between words.
//
// For example,
// words: ["This", "is", "an", "example", "of", "text", "justification."]
// L: 16.
//
// Return the formatted lines as:
// [
//    "This    is    an",
//    "example  of text",
//    "justification.  "
// ]
// Note: Each word is guaranteed not to exceed L in length.
//
// Corner Cases:
// A line other than the last line might contain only one word. What should
// you do in this case?
// In this case, that line should be left-justified.
//
// Complexity:
// O(n) time

Algorithm
Compute the spaces that are needed to pad for each line.
For non-"one word line" and non-"the last line": distribute the pad spaces into intervals of words and print the line.
For "one word line" and "the last line": pad all extra spaces to the end and print the line.

See also NeatPrintWordWrap.h
*/
class TextJustification
{
public:
	TextJustification(){}
	~TextJustification(){}

    std::vector<std::string> Greedy_Break(std::vector<std::string> && words, int L)
    {
        std::string before = Debug::ToStr1D<std::string>()(words);
        std::vector<std::string> res;
        int N = words.size();
        int curBegin = 0;
        int curEnd = 0;
        while (curEnd < N)
        {
            while (words[curEnd].size() > L)
            {
                res.push_back(words[curEnd].substr(0, L));
                words[curEnd] = words[curEnd].substr(L);
            }

            int totalSpace = L;
            for (; curEnd < N; ++curEnd)
            {
                int nxtSpace = totalSpace - words[curEnd].size() - (totalSpace == L ? 0 : 1);
                if (nxtSpace < 0)
                    break;
                totalSpace = nxtSpace;
            }
            //now curEnd points to the begin of the next line
            //[ words[curBegin],words[curEnd] )
            int intervals = curEnd - curBegin - 1;//number of intervals in between individual words

            std::ostringstream oss;
            if (intervals != 0 && curEnd != N)//non-"one word line" && non-"the last line"
            {
                int avgSpace = totalSpace / intervals + 1;
                int remainSpace = totalSpace % intervals;
                for (; curBegin < curEnd; ++curBegin)
                {
                    oss << words[curBegin];
                    if (curBegin != curEnd - 1)
                    {
                        oss << std::string(avgSpace, ' ');
                        if (remainSpace > 0)
                        {
                            oss << " ";
                            --remainSpace;
                        }
                    }
                }
                //now curBegin points to curEnd which is the begin of the next line
            }
            else//"one word line" or "the last line"
            {
                for (; curBegin < curEnd; ++curBegin)
                {
                    oss << words[curBegin];
                    if (curBegin != curEnd - 1)
                        oss << " ";//the default 1 space
                }
                //now curBegin points to curEnd which is the begin of the next line
                oss << std::string(totalSpace, ' ');
            }
            res.push_back(oss.str());


        }//end while

        std::cout << "TextJustification Greedy_Break for " << L << ", \"" << before << "\":" << std::endl;
        std::ostringstream oss1;
        for (int i = 0; i < (int)res.size(); ++i)
        {
            oss1 << "\"" << res[i] << "\"";
            if (i != res.size() - 1)
                oss1 << "," << std::endl;
        }
        std::cout << oss1.str() << std::endl;

        return res;
    }

	std::vector<std::string> Greedy(const std::vector<std::string> & words, int L)
	{
		std::vector<std::string> res;
		int N = words.size();
		int curBegin = 0;
		int curEnd = 0;
		while (curEnd < N)
		{
			int totalSpace = L;//the total spaces to fill the line
			for (; curEnd < N; ++curEnd)
			{
				int nxtSpace = totalSpace - words[curEnd].size() - (totalSpace == L ? 0 : 1);//when totalSpace != L we need to subtract 1 default space to count the extra spaces to insert
				if (nxtSpace < 0)//can't include word[curEnd]
					break;
				totalSpace = nxtSpace;//can include word[curEnd]
			}
			//now curEnd points to the begin of the next line
			//[ words[curBegin],words[curEnd] )
			int intervals = curEnd - curBegin - 1;//number of intervals in between individual words
			
			std::ostringstream oss;
			if (intervals != 0 && curEnd != N)//non-"one word line" && non-"the last line"
			{
				int avgSpace = totalSpace / intervals + 1;//avg of space len (totalSpace/interval) + default one space (1)
				int remainSpace = totalSpace % intervals;//remaining spaces
				for (; curBegin < curEnd; ++curBegin)
				{
					oss << words[curBegin];
					//pad spaces in interval
					if (curBegin != curEnd - 1)
					{
						oss << std::string(avgSpace, ' ');
						if (remainSpace > 0)
						{
							oss << " ";
							--remainSpace;
						}
					}
				}
				//now curBegin points to curEnd which is the begin of the next line
			}
			else//"one word line" or "the last line"
			{
				for (; curBegin < curEnd; ++curBegin)
				{
					oss << words[curBegin];
					if (curBegin != curEnd - 1)
						oss << " ";//the default 1 space
				}
				//now curBegin points to curEnd which is the begin of the next line
				oss << std::string(totalSpace, ' ');//pad all the extra spaces to the end
			}
			res.push_back(oss.str());
		}//end while

		std::cout << "TextJustification Greedy for " << L << ", \"" << Debug::ToStr1D<std::string>()(words) << "\":" << std::endl;
		std::ostringstream oss1;
		for (int i = 0; i < (int)res.size(); ++i)
		{
			oss1 << "\"" << res[i] << "\"";
			if (i != res.size() - 1)
				oss1 << "," << std::endl;
		}
		std::cout << oss1.str() << std::endl;

		return res;
	}
};
/*
TextJustification Greedy_Break for 4, "This, is, an, example, of, text, justification.":
"This",
"is  ",
"an  ",
"exam",
"ple ",
"of  ",
"text",
"just",
"ific",
"atio",
"n.  "
TextJustification Greedy_Break for 4, "Text, justification, is, an, example, of, this.":
"Text",
"just",
"ific",
"atio",
"n is",
"an  ",
"exam",
"ple ",
"of  ",
"this",
".   "
TextJustification Greedy_Break for 2, "aaa, bb, cc, ddddd, eee, f, gg, h, i, jjj":
"aa",
"a ",
"bb",
"cc",
"dd",
"dd",
"d ",
"ee",
"e ",
"f ",
"gg",
"h ",
"i ",
"jj",
"j "
TextJustification Greedy_Break for 3, "Geeks, for, Geeks, presents, word, wrap, problem":
"Gee",
"ks ",
"for",
"Gee",
"ks ",
"pre",
"sen",
"ts ",
"wor",
"d  ",
"wra",
"p  ",
"pro",
"ble",
"m  "
TextJustification Greedy_Break for 4, "The, quick, brown, fox, jumped, over, the, lazy, dogs.":
"The ",
"quic",
"k   ",
"brow",
"n   ",
"fox ",
"jump",
"ed  ",
"over",
"the ",
"lazy",
"dogs",
".   "
TextJustification Greedy_Break for 6, "I, have, inserted, a, large, number, of, new, examples, from, the, papers, for, the, Mathematical, Tripos, during, the, last, twenty, years,, which, should, be, useful, to, Cambridge, students.":
"I have",
"insert",
"ed   a",
"large ",
"number",
"of new",
"exampl",
"es    ",
"from  ",
"the   ",
"papers",
"for   ",
"the   ",
"Mathem",
"atical",
"Tripos",
"during",
"the   ",
"last  ",
"twenty",
"years,",
"which ",
"should",
"be    ",
"useful",
"to    ",
"Cambri",
"dge   ",
"studen",
"ts.   "
TextJustification Greedy for 16, "This, is, an, example, of, text, justification.":
"This    is    an",
"example  of text",
"justification.  "
TextJustification Greedy for 14, "This, is, an, example, of, text, justification.":
"This   is   an",
"example     of",
"text          ",
"justification."
TextJustification Greedy for 16, "Text, justification, is, an, example, of, this.":
"Text            ",
"justification is",
"an   example  of",
"this.           "
TextJustification Greedy for 14, "Text, justification, is, an, example, of, this.":
"Text          ",
"justification ",
"is  an example",
"of this.      "
TextJustification Greedy for 6, "aaa, bb, cc, ddddd, eee, f, gg, h, i, jjj":
"aaa bb",
"cc    ",
"ddddd ",
"eee  f",
"gg h i",
"jjj   "
TextJustification Greedy for 15, "Geeks, for, Geeks, presents, word, wrap, problem":
"Geeks for Geeks",
"presents   word",
"wrap problem   "
TextJustification Greedy for 11, "The, quick, brown, fox, jumped, over, the, lazy, dogs.":
"The   quick",
"brown   fox",
"jumped over",
"the    lazy",
"dogs.      "
TextJustification Greedy for 36, "I, have, inserted, a, large, number, of, new, examples, from, the, papers, for, the, Mathematical, Tripos, during, the, last, twenty, years,, which, should, be, useful, to, Cambridge, students.":
"I  have  inserted  a large number of",
"new examples from the papers for the",
"Mathematical  Tripos during the last",
"twenty years, which should be useful",
"to Cambridge students.              "
TextJustification Greedy for 65, "Permission, is, hereby, granted,, free, of, charge,, to, any, person, obtaining, a, copy, of, this, software, and, associated, documentation, files, (the, "Software"),, to, deal, in, the, Software, without, restriction,, including, without, limitation, the, rights, to, use,, copy,, modify,, merge,, publish, distribute,, sublicense,, and/or, sell, copies, of, the, Software,, and, to, permit, persons, to, whom, the, Software, is, furnished, to, do, so,, subject, to, the, following, conditions:":
"Permission  is  hereby  granted,  free  of  charge, to any person",
"obtaining  a  copy  of this software and associated documentation",
"files   (the   "Software"),  to  deal  in  the  Software  without",
"restriction,  including  without  limitation  the  rights to use,",
"copy,  modify, merge, publish distribute, sublicense, and/or sell",
"copies  of  the  Software,  and  to  permit  persons  to whom the",
"Software  is  furnished  to  do  so,  subject  to  the  following",
"conditions:                                                      "
*/
#endif