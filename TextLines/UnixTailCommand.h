#ifndef UNIX_TAIL_COMMAND_H
#define UNIX_TAIL_COMMAND_H
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview
The UNIX tail command displays the last part of a file.
For this problem, assume that tail takes two arguments: a filename, and the number of lines, starting from the last line, that are to be printed.

The natural approach to this problem is to read the input one line at a time.
Each line can be stored in a queue.
When the queue size is equal to the number of desired lines, each additional line is inserted at the tail, and the line at the head is deleted.
The drawback of this approach is that it entails reading the entire file which could be huge.

The OS provides the ability to perform random access on a file, essentially allowing us to treat the file as an array of characters, albeit with much slower access times.
In the code below, we use library functions to process the file in reverse order starting the end of the file.
We store the characters in a string, stopping when the specified number of lines have been read.
*/
class UnixTailCommand
{
public:
	UnixTailCommand(){}
	~UnixTailCommand(){}

	//returns the last N lines in filename
	std::string tail(const std::string & filename, int N)
	{
		std::fstream file_ptr(filename.c_str());
		file_ptr.seekg(0, std::ios::end);//now file_ptr points to the end
		int file_size = (int)file_ptr.tellg();
		std::cout << "file_size = " << file_size << " characters" << std::endl;
		int newline_count = 0;
		std::string last_N_lines;

		//read file in reverse looking for '\n'
		for (int i = 0; i < file_size; ++i)
		{
			file_ptr.seekg(-1 - i, std::ios::end);//seek the (end-1-i) position
			char c;
			file_ptr.get(c);
			if (c == '\n')
			{
				++newline_count;
				if (newline_count > N)
					break;
			}
			last_N_lines.push_back(c);

			//if (c == '\n')
			//	std::cout << "new line" << std::endl;
			//else
			//	std::cout << c << std::endl;
		}
		std::reverse(last_N_lines.begin(), last_N_lines.end());

		std::cout << "UnixTailCommand for last " << N << " lines in \"" << filename << "\": " << std::endl;
		std::cout << last_N_lines << std::endl;
		return last_N_lines;
	}
};
#endif