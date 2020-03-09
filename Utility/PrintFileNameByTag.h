#ifndef PRINT_FILE_NAME_BY_TAG_H
#define PRINT_FILE_NAME_BY_TAG_H
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <boost/filesystem.hpp>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/regex.hpp>
#include "Debug.h"
/*
Print File Name By Tag
*/
class PrintFileNameByTag
{
	std::unordered_map<std::string, std::set<std::string>> tagToFileNames;
public:
	explicit PrintFileNameByTag(const std::string path = std::string(
#ifdef _WIN32
            "./Collections/"
#else
			"../"
#endif
	))
	{
		tagToFileNames.insert({ "Recur", std::set<std::string>() });
		tagToFileNames.insert({ "Greedy", std::set<std::string>() });
		tagToFileNames.insert({ "DP", std::set<std::string>() });
		tagToFileNames.insert({ "SuffixArray", std::set<std::string>() });

		boost::filesystem::path p(path);
		boost::filesystem::directory_iterator end_dir_itr;
		for (boost::filesystem::directory_iterator itr(p); itr != end_dir_itr; ++itr)
		{
			if (boost::filesystem::is_regular_file(itr->path()))
			{
				//std::cout << itr->path().filename() << std::endl;
				std::string firstline;
				std::fstream f(itr->path().string());
				getline(f, firstline);
				//std::cout << firstline << std::endl;

				std::string::const_iterator cbegin = firstline.cbegin();
				boost::match_results<std::string::const_iterator> matched_packet;
				boost::match_flag_type flags_packet = boost::match_default;
				while (boost::regex_search(cbegin, firstline.cend(), matched_packet, boost::regex("(?<=\\*).*?(?=\\*)")))
				{
					if (!matched_packet[0].str().empty())
					{
						//std::cout << matched_packet[0].str() << std::endl;
						tagToFileNames[matched_packet[0].str()].insert(itr->path().filename().string());
					}
					cbegin = matched_packet[0].second;
					flags_packet |= boost::match_prev_avail;
					flags_packet |= boost::match_not_bob;
				}
			}
		}

		this->Print();
	}
	~PrintFileNameByTag(){}

	void Print()
	{
		std::ostringstream oss;
		int count = 0;
		for (std::unordered_map<std::string, std::set<std::string>>::const_iterator i = tagToFileNames.begin(); i != tagToFileNames.end(); ++i)
		{
			oss << "Row#" << count++ << "_" << i->first << ":" << std::endl;
			int M = i->second.size();
			int cnt = 0;
			for (std::set<std::string>::const_iterator j = i->second.begin(); j != i->second.end(); ++j)
			{
				oss << *j;
				if (++cnt != M)
					oss << ", ";
			}
			oss << std::endl;
		}
		std::cout << oss.str() << std::endl;
	}
};
#endif