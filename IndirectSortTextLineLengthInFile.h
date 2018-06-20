#ifndef INDIRECT_SORT_TEXT_LINE_LENGTH_IN_FILE_H
#define INDIRECT_SORT_TEXT_LINE_LENGTH_IN_FILE_H
#include <vector>
#include <istream>
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, Sorting: Implement a variable-length sort
Most sorting algorithm rely on a basic swap step.
When records are of different lengths, the swap step becomes nontrivial.
Sort lines of a text file that has one million lines such that the average length of a line is 100 characters but the longest line is one million characters long.
We can indirectly sort the lines by length to avoid swapping operations of copying lines by sorting pointers to lines.
*/
class IndirectSortTextLineLengthInFile
{
public:
	IndirectSortTextLineLengthInFile(){}
	~IndirectSortTextLineLengthInFile(){}

	void Sort(const std::string & filename)
	{
		//1. read all text lines into a vector buffer
		std::ifstream ifs(filename.c_str());
		std::vector<std::string> buf;
		std::string line;
		while (std::getline(ifs, line))
			buf.emplace_back(line);

		//2. sort the strings by length in vector indirectly
		std::vector<const std::string *> ptrs;
		for (auto & str : buf)
			ptrs.emplace_back(&str);
		std::sort(ptrs.begin(), ptrs.end(), [](const std::string * a, const std::string * b)->bool
		{
			return a->length() < b->length();
		});

		//3. write back the text file in sorted order of lines
		std::ofstream ofs(filename.c_str());
		for (const std::string * ptr : ptrs)
			ofs << *ptr << std::endl;

		std::cout << "IndirectSortTextLineLengthInFile for \"" << Debug::ToStr1D<std::string>()(buf) << "\":" << std::endl;
		std::ostringstream oss;
		for (const std::string * ptr : ptrs)
			oss << *ptr << std::endl;
		std::cout << oss.str() << std::endl;
	}

	void Test()
	{
		std::ofstream ofs("indirectsort.txt");
		ofs << "abcde" << std::endl;
		ofs << "xyz" << std::endl;
		ofs << "ijklmn" << std::endl;
		ofs << "w" << std::endl;
		ofs << "pqr" << std::endl;
		ofs << "mnopqrs" << std::endl;
		ofs << "fg" << std::endl;
		ofs << "h" << std::endl;
		ofs << "stuv" << std::endl;
		ofs.close();
		this->Sort("indirectsort.txt");
		std::remove("indirectsort.txt");
	}
};
/*
IndirectSortTextLineLengthInFile for "abcde, xyz, ijklmn, w, pqr, mnopqrs, fg, h, stuv":
w
h
fg
xyz
pqr
stuv
abcde
ijklmn
mnopqrs
*/

/*
Amazon OA
Sort log file lines.
Each line contains an id (a mix of lowercase chars and digits) and followed by either all words or all numbers separated by single spaces.
Lines with numbers should be rearrange to the end of the log with original order kept.
Lines with words should be rearrange to the begin of the log based on the lexicographical order of the words.
If there is a tie, order by the lexicographical order of their ids.
 */
class IndirectSortTextLinesInLogFile
{
public:
	IndirectSortTextLinesInLogFile(){}

	std::vector<std::string> Sort(const std::vector<std::string> & log)
	{
		std::vector<std::string> res;
		int N = log.size();
		std::vector<const std::string *> v;
		for (auto & s : log)
			v.push_back(&s);
		std::sort(v.begin(), v.end(), [](const std::string * a, const std::string * b)->bool
		{
			int i = 0; int A = a->size();
			while (i < A && (*a)[i] != ' ')
				++i;
			std::string id1 = a->substr(0, i);
			std::string txt1 = a->substr(i+1);
			while (i < A && (*a)[i] == ' ')
				++i;
			int type1 = i == A ? 0 : isdigit((*a)[i]) ? 1 : 2;
			int j = 0; int B = b->size();
			while (j < B && (*b)[j] != ' ')
				++j;
			std::string id2 = b->substr(0, j);
			std::string txt2 = b->substr(j+1);
			while (j < B && (*b)[j] == ' ')
				++j;
			int type2 = j == B ? 0 : isdigit((*b)[j]) ? 1 : 2;

            //std::cout << id1 << "," << txt1 << ";" << id2 << "," << txt2 << std::endl;
			if (type1 <= 1 && type2 <= 1)
                return false;//!!!!!!!!!!!!!!!!!
            else if (type1 <= 1)
                return false;
            else if (type2 <= 1)
                return true;
            else if (txt1 == txt2)
                return id1 < id2;
            else
                return txt1 < txt2;
		});
        for (auto & ptr : v)
            res.push_back(*ptr);

        std::cout << "IndirectSortTextLinesInLogFile for [" << Debug::ToStr1D<std::string>()(log) << "]: " << std::endl << Debug::ToStr1D<std::string>()(res) << std::endl;
		return res;
	}
};
/*
IndirectSortTextLinesInLogFile for [zz 93 1, a2da abd fjdks lkdf, b3ds gfi skl, sji akdk jige, d1ka 123 345 943 32, dkj dks jdf, d0k 8342 372 83, dki dks jdf]:
a2da abd fjdks lkdf, sji akdk jige, dki dks jdf, dkj dks jdf, b3ds gfi skl, zz 93 1, d1ka 123 345 943 32, d0k 8342 372 83
 */
#endif