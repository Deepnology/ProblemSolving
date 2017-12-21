#ifndef SUFFIX_ARRAY_H
#define SUFFIX_ARRAY_H
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <sstream>
#include "Debug.h"
/*
Elements of programming interview, Searching: Search a sorted array for the first element greater than k, variant
Write a function which tests if p is a prefix of a string in an array of sorted strings. (SuffixArrayNaive::Rank)
http://algs4.cs.princeton.edu/63suffix/
http://algs4.cs.princeton.edu/63suffix/SuffixArray.java.html
http://www.stanford.edu/class/cs97si/suffix-array.pdf
http://stanford.edu/~liszt90/acm/notebook.html
*/

class SuffixArrayNaive
{
	struct Suffix
	{
		Suffix(): text(), original_index(0){}
		Suffix(std::string text, int index) : text(text), original_index(index){}
		~Suffix(){}
		std::string text;
		int original_index;
	};
	std::vector<Suffix> m_suffixes;
public:
	SuffixArrayNaive(const std::string & text)
	{
		/*naively construct a suffix array: O(n^2logn)*/
		int N = text.size();
		m_suffixes.resize(N);
		/*O(n) to collect all suffixes*/
		for (int i = 0; i < N; ++i)
			m_suffixes[i] = Suffix(text.substr(i, N), i);
		/*O(nlogn) m_suffixes comparisons, O(n) for a pair of suffix comparison: O(n^2logn) in total*/
		std::sort(m_suffixes.begin(), m_suffixes.end(),
			[](const Suffix & a, const Suffix & b)->bool{ return a.text < b.text; });

		std::cout << "Construct SuffixArrayNaive for \"" << text << "\":" << std::endl;
		this->PrintSuffixArray(m_suffixes, text);
	}
	int Length() const
	{
		return m_suffixes.size();
	}
	int OriginalIndex(int i) const
	{
		return m_suffixes[i].original_index;
	}
	int LCP(int i) const
	{
		return this->LCP(m_suffixes[i], m_suffixes[i - 1]);
	}
	std::string Select(int i) const
	{
		return m_suffixes[i].text;
	}
	int Rank(const std::string & query) const
	{
		/*O(mlogn): m is length of query, n is length of text*/
		int lo = 0;
		int hi = m_suffixes.size() - 1;
		while (lo <= hi)
		{
			int mid = lo + (hi - lo) / 2;
			int cmp = this->Compare(query, m_suffixes[mid].text);
			if (cmp < 0) hi = mid - 1;
			else if (cmp > 0) lo = mid + 1;
			else return mid;
		}
		return lo;
	}

private:
	void PrintSuffixArray(const std::vector<Suffix> & v, const std::string & text)
	{
		int N = v.size();
		std::cout << "index,	Oindex,	lcp,	rank,	suffix" << std::endl;
		for (int i = 0; i < N; ++i)
		{
			std::ostringstream lcp;
			if (i == 0)
				lcp << "-";
			else
				lcp << this->LCP(i);
			std::cout << i << ",	" << v[i].original_index << ",	" << lcp.str() << ",	"
				<< this->Rank(text.substr(v[i].original_index, N - v[i].original_index)) << ",	" << v[i].text << std::endl;
		}
	}
	int LCP(const Suffix & s, const Suffix & t) const
	{
		int N = std::min(s.text.size(), t.text.size());
		for (int i = 0; i < N; ++i)
			if (s.text[i] != t.text[i])
				return i;
		return N;
	}
	int Compare(const std::string & query, const std::string & suffix) const
	{
		int N = std::min(query.size(), suffix.size());
		for (int i = 0; i < N; ++i)
		{
			if (query[i] < suffix[i]) return -1;
			if (query[i] > suffix[i]) return 1;
		}
		return query.size() - suffix.size();
	}
};


class SuffixArraySimple
{
	const std::string m_A;
	const int N;
	std::vector<std::vector<int> > m_P;
	std::vector<std::pair<std::pair<int, int>, int> > m_L;
	std::vector<int> m_suffixes;
public:
	SuffixArraySimple(const std::string & text) : m_A(text), N(text.size()), m_P(1, std::vector<int>(N, 0)), m_L(N), m_suffixes(N)
	{
		/*construct the suffix array: O(n(log^2)n) with std::sort, O(nlogn) with radix sort*/
		/*init: O(n)*/
		for (int i = 0; i < N; ++i)
			m_P[0][i] = int(m_A[i]);
		//Debug::Print2D<int>()(m_P, false);
		/*outer for loop: O(logn)*/
		for (int skip = 1, level = 1; skip < N; skip *= 2, ++level)
		{
			m_P.push_back(std::vector<int>(N, 0));
			for (int i = 0; i < N; ++i)
				m_L[i] = std::make_pair(
				std::make_pair(m_P[level - 1][i], i + skip < N ? m_P[level - 1][i + skip] : -1000),
				i);
			//std::cout << Debug::ToStr1D<int>()(m_L) << std::endl;
			/*std::sort: O(nlogn)*/
			std::sort(m_L.begin(), m_L.end(), 
				[](const std::pair<std::pair<int, int>, int> & a, const std::pair<std::pair<int, int>, int> & b)->bool
			{
				return a.first.first == b.first.first ? (a.first.second < b.first.second ? 1 : 0) : 
					(a.first.first < b.first.first ? 1 : 0);
			});
			//std::cout << Debug::ToStr1D<int>()(m_L) << std::endl;
			for (int i = 0; i < N; ++i)
				m_P[level][m_L[i].second] = (i > 0 && m_L[i].first == m_L[i - 1].first) ? m_P[level][m_L[i - 1].second] : i;
		}
		//Debug::Print2D<int>()(m_P, false);
		//m_P.back(): key: m_A from first to last, value: sorted order for each char
		for (int i = 0; i < N; ++i)
			m_suffixes[m_P.back()[i]] = i;
		//std::cout << Debug::ToStr1D<int>()(m_suffixes) << std::endl;

		std::cout << "SuffixArraySimple for \"" << m_A << "\":" << std::endl;
		for (int i = 0; i < N; ++i)
			std::cout << i << ":	" << m_A.substr(m_suffixes[i]) << std::endl;
	}
	std::vector<int> GetSuffixArray() const
	{
		return m_suffixes;
	}
	int operator[](int i) const
	{
		return m_suffixes[i];
	}
	int LongestCommonPrefix(int i, int j)
	{
		/*compute LCP of any two suffixes m_A[i]~m_A[N-1] and m_A[j]~m_A[N-1]: O(logn)*/
		if (i == j)
			return N - i;
		int res = 0;
		for (int level = m_P.size() - 1; level >= 0 && i < N && j < N; --level)
			if (m_P[level][i] == m_P[level][j])
			{
				i += 1 << level;
				j += 1 << level;
				res += 1 << level;
			}
		return res;
	}
	int Size() const
	{
		return N;
	}

};

#endif