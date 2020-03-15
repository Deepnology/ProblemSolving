#ifndef RECONSTRUCT_ITINERARY_H
#define RECONSTRUCT_ITINERARY_H
#include "Debug.h"
/*
Leetcode: Reconstruct Itinerary
Given a list of airline tickets represented by pairs of departure and arrival airports [from, to], reconstruct the itinerary in order.
All of the tickets belong to a man who departs from JFK.
Thus, the itinerary must begin with JFK.
Note:
If there are multiple valid itineraries, you should return the itinerary that has the smallest lexical order when read as a single string.
For example, the itinerary ["JFK", "LGA"] has a smaller lexical order than ["JFK", "LGB"].
All airports are represented by three capital letters (IATA code).
You may assume all tickets form at least one valid itinerary.
Example 1:
tickets = [["MUC", "LHR"], ["JFK", "MUC"], ["SFO", "SJC"], ["LHR", "SFO"]]
Return ["JFK", "MUC", "LHR", "SFO", "SJC"].
Example 2:
tickets = [["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]
Return ["JFK","ATL","JFK","SFO","ATL","SFO"].
Another possible reconstruction is ["JFK","SFO","ATL","JFK","ATL","SFO"]. But it is larger in lexical order.
*/

//there is only one root but might contain cycles!
class ReconstructItinerary
{
public:
	ReconstructItinerary() {}
	~ReconstructItinerary() {}

	std::vector<std::string> DFS_Recur(const std::vector<std::pair<std::string, std::string>> & tickets)//Hierholzer Algorithm Find Euler Path
	{
		//since itinerary is required to be in the smallest lexical order, and airports can be repeated, use multiset
		std::unordered_map<std::string, std::multiset<std::string>> adjMultiSet;//first: departure, second: a set of arrivals
		for (const auto & p : tickets)
		{
			adjMultiSet[p.first].insert(p.second);
		}
		Debug::Print2D<std::string>()(adjMultiSet);

		std::vector<std::string> resStk;
		this->recur(adjMultiSet, "JFK", resStk);
		std::reverse(resStk.begin(), resStk.end());

		std::cout << "ReconstructItinerary DFS_Recur for \"" << Debug::ToStr1D<std::string>()(tickets) << "\": " << Debug::ToStr1D<std::string>()(resStk) << std::endl;
		return resStk;
	}
private:
	void recur(std::unordered_map<std::string, std::multiset<std::string>> & adjMultiSet, std::string begin, std::vector<std::string> & resStk)
	{
		while (!adjMultiSet[begin].empty())
		{
			std::string next = *adjMultiSet[begin].begin();
			adjMultiSet[begin].erase(adjMultiSet[begin].begin());
			this->recur(adjMultiSet, next, resStk);
		}
		//now visit cur node in reversed preorder
		resStk.push_back(begin);
	}

public:
	std::vector<std::string> DFS_Stack(const std::vector<std::pair<std::string, std::string>> & tickets)//Hierholzer Algorithm Find Euler Path
	{
		//since itinerary is required to be in the smallest lexical order, and airports can be repeated, use multiset
		std::unordered_map<std::string, std::multiset<std::string>> adjMultiSet;//first: departure, second: a set of arrivals
		for (const auto & p : tickets)
		{
			adjMultiSet[p.first].insert(p.second);
		}
		Debug::Print2D<std::string>()(adjMultiSet);

		std::vector<std::string> resStk;
		std::stack<std::string> stk;
		stk.push(std::string("JFK"));
		while (!stk.empty())
		{
			//push all nodes in the rightmost child path to stk
			while (!adjMultiSet[stk.top()].empty())
			{
				std::string top = stk.top();
				stk.push(*(adjMultiSet[top].begin()));
				adjMultiSet[top].erase(adjMultiSet[top].begin());
			}
			//now visit cur node in reversed preorder
			std::string curNode = stk.top();
			stk.pop();
			resStk.push_back(curNode);
		}
		std::reverse(resStk.begin(), resStk.end());

		std::cout << "ReconstructItinerary DFS_Stack for \"" << Debug::ToStr1D<std::string>()(tickets) << "\": " << Debug::ToStr1D<std::string>()(resStk) << std::endl;
		return resStk;
	}
};
/*
ReconstructItinerary DFS_Recur for "[MUC,LHR], [JFK,MUC], [SFO,SJC], [LHR,SFO]": JFK, MUC, LHR, SFO, SJC
Row#0	= MUC: LHR
Row#1	= JFK: MUC
Row#2	= LHR: SFO
Row#3	= SFO: SJC

ReconstructItinerary DFS_Stack for "[MUC,LHR], [JFK,MUC], [SFO,SJC], [LHR,SFO]": JFK, MUC, LHR, SFO, SJC
Row#0	= JFK: ATL, SFO
Row#1	= SFO: ATL
Row#2	= ATL: JFK, SFO

ReconstructItinerary DFS_Recur for "[JFK,SFO], [JFK,ATL], [SFO,ATL], [ATL,JFK], [ATL,SFO]": JFK, ATL, JFK, SFO, ATL, SFO
Row#0	= JFK: ATL, SFO
Row#1	= SFO: ATL
Row#2	= ATL: JFK, SFO

ReconstructItinerary DFS_Stack for "[JFK,SFO], [JFK,ATL], [SFO,ATL], [ATL,JFK], [ATL,SFO]": JFK, ATL, JFK, SFO, ATL, SFO
Row#0	= JFK: ATL, SFO
Row#1	= SFO: ATL, JFK
Row#2	= ATL: SFO

ReconstructItinerary DFS_Recur for "[JFK,SFO], [JFK,ATL], [SFO,ATL], [SFO,JFK], [ATL,SFO]": JFK, ATL, SFO, JFK, SFO, ATL
Row#0	= JFK: ATL, SFO
Row#1	= SFO: ATL, JFK
Row#2	= ATL: SFO

ReconstructItinerary DFS_Stack for "[JFK,SFO], [JFK,ATL], [SFO,ATL], [SFO,JFK], [ATL,SFO]": JFK, ATL, SFO, JFK, SFO, ATL
Row#0	= JFK: SFO, ZTL
Row#1	= SFO: ZTL
Row#2	= ZTL: JFK, SFO

ReconstructItinerary DFS_Recur for "[JFK,SFO], [JFK,ZTL], [SFO,ZTL], [ZTL,JFK], [ZTL,SFO]": JFK, SFO, ZTL, JFK, ZTL, SFO
Row#0	= JFK: SFO, ZTL
Row#1	= SFO: ZTL
Row#2	= ZTL: JFK, SFO

ReconstructItinerary DFS_Stack for "[JFK,SFO], [JFK,ZTL], [SFO,ZTL], [ZTL,JFK], [ZTL,SFO]": JFK, SFO, ZTL, JFK, ZTL, SFO
Row#0	= JFK: SFO, ZTL
Row#1	= SFO: JFK, ZTL
Row#2	= ZTL: SFO

ReconstructItinerary DFS_Recur for "[JFK,SFO], [JFK,ZTL], [SFO,ZTL], [SFO,JFK], [ZTL,SFO]": JFK, SFO, JFK, ZTL, SFO, ZTL
Row#0	= JFK: SFO, ZTL
Row#1	= SFO: JFK, ZTL
Row#2	= ZTL: SFO

ReconstructItinerary DFS_Stack for "[JFK,SFO], [JFK,ZTL], [SFO,ZTL], [SFO,JFK], [ZTL,SFO]": JFK, SFO, JFK, ZTL, SFO, ZTL
Row#0	= JFK: KUL, NRT
Row#1	= NRT: JFK

ReconstructItinerary DFS_Recur for "[JFK,KUL], [JFK,NRT], [NRT,JFK]": JFK, NRT, JFK, KUL
Row#0	= JFK: KUL, NRT
Row#1	= NRT: JFK

ReconstructItinerary DFS_Stack for "[JFK,KUL], [JFK,NRT], [NRT,JFK]": JFK, NRT, JFK, KUL
Row#0	= JFK: KUL, NRT
Row#1	= KUL: JFK

ReconstructItinerary DFS_Recur for "[JFK,KUL], [JFK,NRT], [KUL,JFK]": JFK, KUL, JFK, NRT
Row#0	= JFK: KUL, NRT
Row#1	= KUL: JFK

ReconstructItinerary DFS_Stack for "[JFK,KUL], [JFK,NRT], [KUL,JFK]": JFK, KUL, JFK, NRT
*/
#endif
