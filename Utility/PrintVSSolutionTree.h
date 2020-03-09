#ifndef PRINT_VS_SOLUTION_TREE_H
#define PRINT_VS_SOLUTION_TREE_H
#include <map>
#include <set>
#include <string>
#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/regex.hpp>
#include "Debug.h"
class PrintVSSolutionTree
{
	std::map<std::string, std::set<std::string>> tree;//first: filter, second: a set of file names
	int filenameCount;
public:
	explicit PrintVSSolutionTree(const std::string path = std::string("./Collections.vcxproj.filters")) : tree(), filenameCount(0)
	{
		boost::filesystem::path p(path);
		if (boost::filesystem::is_regular_file(p))
		{
			std::fstream f(p.string());
			std::string line;
			std::string filename;
			std::string filters;
			while (getline(f, line))
			{
				//std::cout << "line: " << line << std::endl;

				boost::match_results<std::string::const_iterator> matched_packet;
				if (boost::regex_search(line.cbegin(), line.cend(), matched_packet, boost::regex("(?<=<ClInclude Include=\"Collections\\\\).*?(?=\">)")))
				{
					if (!matched_packet[0].str().empty())
					{
						//std::cout << matched_packet[0].str() << std::endl;
						filename = matched_packet[0].str();
						++filenameCount;
					}
				}
				else if (boost::regex_search(line.cbegin(), line.cend(), matched_packet, boost::regex("(?<=<Filter>Header Files\\\\).*?(?=</Filter>)")))
				{
					if (!matched_packet[0].str().empty())
					{
						//std::cout << matched_packet[0].str() << std::endl;
						filters = matched_packet[0].str();
						auto itr = tree.find(filters);
						if (itr == tree.end())
							tree.insert({ filters, { filename } });
						else
							itr->second.insert(filename);
					}
				}

			}

			this->PrintSolutionTree();
			this->PrintSolutionReview();
		}
	}
	~PrintVSSolutionTree(){}

private:
	void PrintSolutionTree()
	{
		std::ofstream ofs;
		ofs.open("SolutionTree.txt");
		std::streambuf * backup = std::cout.rdbuf();
		std::streambuf * psbuf = ofs.rdbuf();
		std::cout.rdbuf(psbuf);

		std::cout << "Total files: " << filenameCount << std::endl;
		Debug::Print2D<std::string>()(tree);

		std::cout.rdbuf(backup);
		ofs.close();
	}
	void PrintSolutionReview()
	{
		std::ofstream ofs2;
		ofs2.open("SolutionReview.h");
		for (const auto & p : tree)
		{
			for (const auto & filename : p.second)
			{
				ofs2 << "//===" << p.first << ": " << filename << "===" << std::endl;
				std::string path = "./Collections/" + filename;
				if (boost::filesystem::is_regular_file(path))
				{
					std::fstream f(path);
					std::string line;
					bool recording = false;
					while (getline(f, line))
					{
						if (!recording)
						{
							boost::match_results<std::string::const_iterator> matched_packet;
							if (boost::regex_search(line.cbegin(), line.cend(), matched_packet, boost::regex("^class\\s")))
							{
								recording = true;
								ofs2 << line << std::endl;
							}
						}
						else
						{
							ofs2 << line << std::endl;
							boost::match_results<std::string::const_iterator> matched_packet;
							if (boost::regex_search(line.cbegin(), line.cend(), matched_packet, boost::regex("^\\};")))
							{
								recording = false;
							}
						}
					}
				}

				ofs2 << std::endl;
			}
		}

		ofs2.close();
	}
};
#endif