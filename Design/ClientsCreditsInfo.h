#ifndef CLIENTS_CREDITS_INFO_H
#define CLIENTS_CREDITS_INFO_H
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <algorithm>
#include <string>
#include <iostream>
#include "Debug.h"
/*
Elements of programming interview, BST: Add credits
Consider a server that a large number of clients connect to.
Each client is identified by unique string.
Each client has a certain number of "credits", which is a nonnegative integer value.
The server needs to maintain a data structure to which clients can be added, removed, queried, or updated.
In addition, the server needs to be able to add C credits to all clients simultaneously.

-insert(s, c), which add client s with credit c, overwriting any existing entry for s: O(logn) time
-remove(s), which removes client s: O(logn) time
-lookup(s), which returns the number of credits associated with client s, or -1 if s is not present: O(1) time
-addAll(C), the effect of which is to increment the number of credits for each client currently present by C: O(1) time
-max(), which returns any one client with the highest number of credits: O(1) time
*/
class ClientsCreditsInfo
{
	int m_offset = 0;
	std::unordered_map<std::string, int> m_credit;//key: name, val: credit
	std::map<int, std::unordered_set<std::string> > m_clients;//key: credit, val: a set of names
public:
	ClientsCreditsInfo(){}
	~ClientsCreditsInfo(){}

	void Insert(const std::string & s, int c)//O(logn) time
	{
		this->Remove(s);
		m_credit.emplace(s, c - m_offset);
		m_clients[c - m_offset].emplace(s);
		std::cout << "ClientsCreditsInfor Insert for \"" << s << "\": " << true << std::endl;
	}
	bool Remove(const std::string & s)//O(logn) time
	{
		auto iter = m_credit.find(s);
		if (iter != m_credit.end())
		{
			m_clients[iter->second].erase(s);
			if (m_clients[iter->second].empty())
				m_clients.erase(iter->second);
			m_credit.erase(iter);
			std::cout << "ClientsCreditsInfo Remove for \"" << s << "\": " << true << std::endl;
			return true;
		}
		std::cout << "ClientsCreditsInfo Remove for \"" << s << "\": " << false << std::endl;
		return false;
	}
	int Lookup(const std::string & s) const//O(1) time
	{
		auto iter = m_credit.find(s);
		int res = iter == m_credit.end() ? -1 : iter->second + m_offset;
		std::cout << "ClientsCreditsInfo Lookup for \"" << s << "\": " << res << std::endl;
		return res;
	}
	void AddAll(int C)//O(1) time
	{
		m_offset += C;
		std::cout << "ClientsCreditsInfo AddAll for \"" << C << "\": " << m_offset << std::endl;
	}
	std::string Max() const//O(1) time
	{
		auto iter = m_clients.crbegin();
		std::string found = (iter == m_clients.crend() || iter->second.empty()) ? "" : *(iter->second.cbegin());
		std::cout << "ClientsCreditsInfo Max: " << found << std::endl;
		return found;
	}

	void Print()
	{
		std::cout << "ClientsCreditsInfo: " << Debug::ToStr1D<std::string, int>()(m_credit) << std::endl;
		Debug::Print2D<int, std::string>()(m_clients);
	}
};
#endif