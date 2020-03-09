#ifndef _REDIRECT_COUT_H
#define _REDIRECT_COUT_H
#include <boost/iostreams/stream_buffer.hpp>
#include <boost/iostreams/device/null.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <boost/thread/once.hpp>
/*
http://stackoverflow.com/questions/15443901/declaring-static-data-members-of-normal-class-and-class-template
1. global variables marked as const, or global non-const variables marked as static:
they have internal linkage
, which means if you put their definition in a header file "#include"d by multiple translation units
, each translation unit will receive a private copy of those variables.

2. global non-const non-static variables, or static data members of a class:
they have external linkage
, which means if you put their definition a header file "#include"d by multiple translation units
, you will end up with multiple definitions of the same symbol in the corresponding object files.
In this case, your program will violate the "One Definition Rule", which will cause a linking error.
*/
namespace redirect_cout
{
	namespace detail
	{
		static std::streambuf * m_cout_buf = nullptr;
		static boost::once_flag m_once_flag = BOOST_ONCE_INIT;
		static boost::iostreams::stream_buffer<boost::iostreams::null_sink> m_null_buf = boost::iostreams::null_sink();
		inline void backup()
		{
			m_cout_buf = std::cout.rdbuf();
		}
		static std::ofstream m_ofstream;
	}
	inline void to_null_sink()
	{
		boost::call_once(detail::backup, detail::m_once_flag);
		std::cout.rdbuf(&detail::m_null_buf);
	}
	inline void to_cout()
	{
		if (detail::m_cout_buf != nullptr && detail::m_cout_buf != std::cout.rdbuf())
			std::cout.rdbuf(detail::m_cout_buf);
	}
	inline void to_file(std::string file)
	{
		boost::call_once(detail::backup, detail::m_once_flag);
		detail::m_ofstream.clear();
		detail::m_ofstream.close();
		detail::m_ofstream.open(file);
		std::cout.rdbuf(detail::m_ofstream.rdbuf());
	}
}

#endif