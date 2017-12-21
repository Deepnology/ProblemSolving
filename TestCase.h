#ifndef TEST_CASE__H_
#define TEST_CASE__H_
#include <string>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <deque>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <set>
#include <algorithm>
#include <functional>
#include <chrono>
#include <cmath>
#include <random>
namespace TestCase
{
	namespace Private
	{
		static int CurrentTimeSeconds()
		{
			auto now = std::chrono::high_resolution_clock::now().time_since_epoch();
			return (int)std::chrono::duration_cast<std::chrono::seconds>(now).count();
		}
		static std::mt19937 Generator(Private::CurrentTimeSeconds());
	}
	static char RandChar()
	{
		std::uniform_int_distribution<int> distributation(0, 94);
		return ' ' + distributation(Private::Generator);//chars from ' ' to '~', see ASCII table
	}
	static std::string RandStr(unsigned count)
	{
		std::uniform_int_distribution<int> distributation(0, 94);
		std::string res;
		for (unsigned i = 0; i < count; ++i)
			res.push_back(' ' + distributation(Private::Generator));
		return res;
	}
	static std::string RandStr(unsigned count, char low, char high)
	{
		std::uniform_int_distribution<int> distributation(low - ' ', high - ' ');
		std::string res;
		for (unsigned i = 0; i < count; ++i)
			res.push_back(' ' + distributation(Private::Generator));
		return res;
	}
	static std::string RandSortedStr(unsigned count, char low, char high)
	{
		std::uniform_int_distribution<int> distributation(low - ' ', high - ' ');
		std::string res;
		for (unsigned i = 0; i < count; ++i)
			res.push_back(' ' + distributation(Private::Generator));
		std::sort(res.begin(), res.end());
		return res;
	}
	static std::string RandRotatedSortedStr(unsigned count, char low, char high)
	{
		std::string res = RandSortedStr(count, low, high);
		if (!res.empty())
		{
			std::uniform_int_distribution<int> distributation(0, res.size() - 1);
			std::rotate(res.begin(), res.begin() + distributation(Private::Generator), res.end());
		}
		return res;
	}
	static std::string RandUniqueStr(unsigned count)
	{
		if (count > 95)
		{
			std::cout << "Warning! Invalid TestCase::RandUniqueStr for \"" << count << "\"!" << std::endl;
			return std::string();
		}
		std::uniform_int_distribution<int> distributation(0, 94);
		std::unordered_set<int> set;
		std::string res;
		for (unsigned i = 0; i < count; ++i)
		{
			int next;
			do
			{
				next = distributation(Private::Generator);
			} while (set.find(next) != set.end());
			set.insert(next);
			res.push_back(' ' + next);
		}
		return res;
	}
	template<class T>
	static T RandNum(T low, T high)
	{
		return T();
	}
	template<>
	static int RandNum(int low, int high)
	{
		std::uniform_int_distribution<int> distributation(low, high);
		return distributation(Private::Generator);
	}
	template<>
	static unsigned long long RandNum(unsigned long long low, unsigned long long high)
	{
		std::uniform_int_distribution<unsigned long long> distributation(low, high);
		return distributation(Private::Generator);
	}
	template<>
	static double RandNum(double low, double high)
	{
		std::uniform_real_distribution<double> distributation(low, high);
		return distributation(Private::Generator);
	}
	template<class T>
	static std::vector<T> RandVec(unsigned count, T low, T high)
	{
		return std::vector<T>();
	}
	template<>
	std::vector<int> RandVec<int>(unsigned count, int low, int high)
	{
		std::uniform_int_distribution<int> distributation(low, high);
		std::vector<int> res;
		for (unsigned i = 0; i < count; ++i)
			res.emplace_back(distributation(Private::Generator));
		return res;
	}
	template<>
	std::vector<double> RandVec<double>(unsigned count, double low, double high)
	{
		std::uniform_real_distribution<double> distributation(low, high);
		std::vector<double> res;
		for (unsigned i = 0; i < count; ++i)
			res.emplace_back(distributation(Private::Generator));
		return res;
	}
	template<class T>
	static std::vector<T> RandUniqueVec(unsigned count, T low, T high)
	{
		return std::vector<T>();
	}
	template<>
	std::vector<int> RandUniqueVec<int>(unsigned count, int low, int high)
	{
		if ((int)count > high - low + 1)
		{
			std::cout << "Warning! Invalid TestCase::RandUniqueVec<int> for \"" << count << ", " << low << ", " << high << "\"!" << std::endl;
			return std::vector<int>();
		}
		std::uniform_int_distribution<int> distributation(low, high);
		std::unordered_set<int> set;
		std::vector<int> res;
		for (unsigned i = 0; i < count; ++i)
		{
			int next;
			do
			{
				next = distributation(Private::Generator);
			} while (set.find(next) != set.end());
			set.insert(next);
			res.emplace_back(next);
		}
		return res;
	}
	template<>
	std::vector<double> RandUniqueVec<double>(unsigned count, double low, double high)
	{
		std::uniform_real_distribution<double> distributation(low, high);
		std::unordered_set<double> set;
		std::vector<double> res;
		for (unsigned i = 0; i < count; ++i)
		{
			double next;
			do
			{
				next = distributation(Private::Generator);
			} while (set.find(next) != set.end());
			set.insert(next);
			res.emplace_back(next);
		}
		return res;
	}
	template<class T>
	static std::vector<T> RandUniqueSortedVec(unsigned count, T low, T high)
	{
		std::vector<T> res = RandUniqueVec<T>(count, low, high);
		std::sort(res.begin(), res.end());
		return res;
	}
	template<class T>
	static std::vector<T> RandSortedVec(unsigned count, T low, T high)
	{
		std::vector<T> res = RandVec<T>(count, low, high);
		std::sort(res.begin(), res.end());
		return res;
	}
	template<class T>
	static std::vector<T> RandRotatedSortedVec(unsigned count, T low, T high)
	{
		std::vector<T> res = RandSortedVec<T>(count, low, high);
		if (!res.empty())
		{
			std::uniform_int_distribution<int> distributation(0, res.size() - 1);
			std::rotate(res.begin(), res.begin() + distributation(Private::Generator), res.end());
		}
		return res;
	}
	template<class T, class U = T>
	static std::vector<std::pair<T, U> > RandVecPair(unsigned count, T low, T high, U low2, U high2)
	{
		return std::vector<std::pair<T, U> >();
	}
	template<class T, class U = T>
	static std::vector<std::pair<T, U> > RandVecPair(unsigned count, T low, T high)
	{
		return RandVecPair<T>(count, low, high, low, high);
	}
	template<>
	std::vector<std::pair<int, int> > RandVecPair(unsigned count, int low, int high, int low2, int high2)
	{
		std::uniform_int_distribution<int> distributation(low, high);
		std::uniform_int_distribution<int> distributation2(low2, high2);
		std::vector<std::pair<int, int> > res;
		for (unsigned i = 0; i < count; ++i)
			res.push_back({ distributation(Private::Generator), distributation2(Private::Generator) });
		return res;
	}
	template<>
	std::vector<std::pair<double, double> > RandVecPair(unsigned count, double low, double high, double low2, double high2)
	{
		std::uniform_real_distribution<double> distributation(low, high);
		std::uniform_real_distribution<double> distributation2(low2, high2);
		std::vector<std::pair<double, double> > res;
		for (unsigned i = 0; i < count; ++i)
			res.push_back({ distributation(Private::Generator), distributation2(Private::Generator) });
		return res;
	}
	template<>
	std::vector<std::pair<double, int> > RandVecPair(unsigned count, double low, double high, int low2, int high2)
	{
		std::uniform_real_distribution<double> distributation(low, high);
		std::uniform_int_distribution<int> distributation2(low2, high2);
		std::vector<std::pair<double, int> > res;
		for (unsigned i = 0; i < count; ++i)
			res.push_back({ distributation(Private::Generator), distributation2(Private::Generator) });
		return res;
	}
	template<>
	std::vector<std::pair<int, double> > RandVecPair(unsigned count, int low, int high, double low2, double high2)
	{
		std::uniform_int_distribution<int> distributation(low, high);
		std::uniform_real_distribution<double> distributation2(low2, high2);
		std::vector<std::pair<int, double> > res;
		for (unsigned i = 0; i < count; ++i)
			res.push_back({ distributation(Private::Generator), distributation2(Private::Generator) });
		return res;
	}
}
#endif