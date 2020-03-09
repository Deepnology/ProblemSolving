#ifndef PRINT_HEADER_H
#define PRINT_HEADER_H
#include <string>
#include <sstream>
#include <iostream>

class PrintHeader
{
public:
	PrintHeader(){}
	~PrintHeader(){}

	void operator()(std::string s)
	{
		int M = s.size();
		int spaces = 4;
		M += spaces * 2 + 2;
		std::ostringstream oss;
		oss << std::endl;
		oss << " ";
		for (int i = 0; i < M; ++i)
			oss << "=";
		oss << std::endl;
		oss << " ";
		oss << "|";
		for (int i = 0; i < spaces; ++i)
			oss << " ";
		oss << s;
		for (int i = 0; i < spaces; ++i)
			oss << " ";
		oss << "|";
		oss << std::endl;
		oss << " ";
		for (int i = 0; i < M; ++i)
			oss << "=";
		oss << std::endl << std::endl;
		std::cout << oss.str();
	}
};

#endif