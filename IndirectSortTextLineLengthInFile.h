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
#endif