#ifndef TREE_FROM_PARENT_CHILD_PAIRS_H
#define TREE_FROM_PARENT_CHILD_PAIRS_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include "Debug.h"
/*
Google
http://www.careercup.com/question?id=5074387359236096
http://programming4interviews.wordpress.com/2012/07/16/form-a-tree-from-given-child-parent-pairs/
http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=51
http://www.careercup.com/question?id=5692203355602944
http://www.careercup.com/question?id=5656914679562240
http://www.careercup.com/question?id=5717669093310464
http://www.careercup.com/question?id=5648527329853440

Given a list of parent-child pairs. Construct the tree and return DFS or BFS traversal.
1. construct a directed graph from parent-child pairs
2. detect if cycle presents in the digraph, return fail if found cycle
3. perform DFS traversal with stack, or BFS traversal with queue, return the traversal

See also FlattenNestedListIterator.h, BinaryTreePreOrderTraversal.h
*/
class TreeFromParentChildPairs
{
public:
	TreeFromParentChildPairs(){}
	~TreeFromParentChildPairs(){}


	std::vector<std::string> TraverseDFS(const std::list<std::pair<std::string, std::string>> & parentChildPairs)
	{
		std::unordered_map<std::string, std::unordered_set<std::string>> adjSet;//digraph
		std::unordered_set<std::string> root;
		this->GetParentChildrenMap(parentChildPairs, adjSet, root);

		std::cout << "roots: " << Debug::ToStr1D<std::string>()(root) << std::endl;
		Debug::Print2D<std::string>()(adjSet);

		/*detect cycle in digraph, see also CyclicGraph.h*/
		bool hasCycle = false;
		std::unordered_map<std::string, int> visit;
		std::unordered_map<std::string, int> completion;
		int visitCount = -1;
		int completionCount = -1;
		for (const auto & pair : adjSet)
		{
			if (visit.count(pair.first) == 0)
			{
				if (this->DFS_HasCycle(adjSet, "", pair.first, visitCount, completionCount, visit, completion))
				{
					hasCycle = true;
					break;
				}
			}
		}
		if (hasCycle)
		{
			std::cout << "TreeFromParentChildPairs TraverseDFS for \"" << Debug::ToStr1D<std::string>()(parentChildPairs) << "\": " << std::endl << "Cycle Found in DiGraph!" << std::endl;
			return std::vector<std::string>();
		}
		/**/

		/*
		//approach 1
		std::vector<std::string> resStk;
		while (!root.empty())
		{
			//DFS traversal using stack for each root (since there is no cycle and traversal is from root and adj vertices are removed after visited, we don't need to keep track of visited vertices)
			std::stack<std::string> stk;
			stk.push(*root.begin());
			root.erase(root.begin());
			while (!stk.empty())
			{
				//push all nodes in the rightmost child path to stk
				while (!adjSet[stk.top()].empty())
				{
					std::string top = stk.top();
					stk.push(*adjSet[top].begin());//note: cannot access std::prev(unordered_map::end())
					adjSet[top].erase(adjSet[top].begin());
				}
				//now visit cur node in reversed preorder
				std::string curNode = stk.top();
				stk.pop();
				resStk.push_back(curNode);
			}
		}
		std::reverse(resStk.begin(), resStk.end());
		*/

		//approach 2
		std::vector<std::string> resStk;
		while (!root.empty())
		{
			//DFS traversal using stack for each root (since there is no cycle and traversal is from root and adj vertices are removed after visited, we don't need to keep track of visited vertices)
			std::stack<std::string> stk;
			stk.push(*root.begin());
			root.erase(root.begin());
			while (!stk.empty())
			{
				std::string curNode = stk.top();
				stk.pop();
				for (auto itr = adjSet[curNode].begin(); itr != adjSet[curNode].end(); ++itr)
					stk.push(*itr);
				resStk.push_back(curNode);
			}
		}


		std::cout << "TreeFromParentChildPairs TraverseDFS for \"" << Debug::ToStr1D<std::string>()(parentChildPairs) << "\": " << std::endl << Debug::ToStr1D<std::string>()(resStk) << std::endl;
		return resStk;
	}

	std::vector<std::string> TraverseBFS(const std::list<std::pair<std::string, std::string>> & parentChildPairs)//BFS is much easier
	{
		std::unordered_map<std::string, std::unordered_set<std::string>> adjSet;//digraph
		std::unordered_set<std::string> root;
		this->GetParentChildrenMap(parentChildPairs, adjSet, root);

		std::cout << "roots: " << Debug::ToStr1D<std::string>()(root) << std::endl;
		Debug::Print2D<std::string>()(adjSet);

		/*detect cycle in digraph, see also CyclicGraph.h*/
		bool hasCycle = false;
		std::unordered_map<std::string, int> visit;
		std::unordered_map<std::string, int> completion;
		int visitCount = -1;
		int completionCount = -1;
		for (const auto & pair : adjSet)
		{
			if (visit.count(pair.first) == 0)
			{
				if (this->DFS_HasCycle(adjSet, "", pair.first, visitCount, completionCount, visit, completion))
				{
					hasCycle = true;
					break;
				}
			}
		}
		if (hasCycle)
		{
			std::cout << "TreeFromParentChildPairs TraverseBFS for \"" << Debug::ToStr1D<std::string>()(parentChildPairs) << "\": " << std::endl << "Cycle Found in DiGraph!" << std::endl;
			return std::vector<std::string>();
		}
		/**/

		std::vector<std::string> res;
		while (!root.empty())
		{
			//BFS traversal with queue for each root (since there is no cycle and traversal is from root, we don't need to keep track of visited vertices)
			std::queue<std::string> que;
			que.push(*root.begin());
			root.erase(root.begin());
			while (!que.empty())
			{
				std::string curNode = que.front();
				que.pop();
				res.push_back(curNode);
				for (std::unordered_set<std::string>::const_iterator i = adjSet[curNode].begin(); i != adjSet[curNode].end(); ++i)
				{
					que.push(*i);
				}
			}
		}
		std::cout << "TreeFromParentChildPairs TraverseBFS for \"" << Debug::ToStr1D<std::string>()(parentChildPairs) << "\": " << std::endl << Debug::ToStr1D<std::string>()(res) << std::endl;
		return res;
	}
private:
	void GetParentChildrenMap(const std::list<std::pair<std::string,std::string>> & parentChildPairs, //input
		std::unordered_map<std::string, std::unordered_set<std::string>> & adjSet, //output
		std::unordered_set<std::string> & root)//output
	{
		for (std::list<std::pair<std::string, std::string>>::const_iterator itr = parentChildPairs.begin(); itr != parentChildPairs.end(); ++itr)
		{
			std::unordered_map<std::string, std::unordered_set<std::string>>::iterator foundParent = adjSet.find(itr->first);
			if (foundParent != adjSet.end())//found parent
			{
				//insert child to existing parent
				foundParent->second.insert(itr->second);
			}
			else//not found parent
			{
				//insert parent to root
				root.insert(itr->first);

				//insert new (parent, child) pair
				adjSet.insert({ itr->first, std::unordered_set<std::string>({ itr->second }) });
			}

			std::unordered_map<std::string, std::unordered_set<std::string>>::iterator foundChild = adjSet.find(itr->second);
			if (foundChild != adjSet.end())//found child
			{
				//remove child from root
				root.erase(itr->second);
			}
			else//not found child
			{
				//insert new (child, null) pair
				adjSet.insert({ itr->second, std::unordered_set<std::string>() });
			}
		}
	}

	bool DFS_HasCycle(std::unordered_map<std::string, std::unordered_set<std::string>> & digraph, const std::string & parent, const std::string & child
		, int & visitCount, int & completionCount
		, std::unordered_map<std::string, int> & visit, std::unordered_map<std::string, int> & completion)
	{
		visit[child] = ++visitCount;
		for (const std::string & s : digraph[child])
		{
			if (visit.count(s) == 0)
			{
				if (this->DFS_HasCycle(digraph, child, s, visitCount, completionCount, visit, completion))
					return true;
			}
			else
			{
				if (completion.count(s) == 0)
				{
					//(child, s) is a back edge in a directed graph
					std::cout << "Found Back Edge: " << child << "->" << s << std::endl;
					return true;
				}
			}
		}
		completion[child] = ++completionCount;
		return false;
	}
};
/*
roots: lifeform, Brand
Row#0	= RS5:
Row#1	= lifeform: animal, plant, fungi
Row#2	= BMW: M4, xDrive
Row#3	= animal: mammal, bird, fish
Row#4	= mammal: cat, human, whale
Row#5	= plant:
Row#6	= bird: eagle
Row#7	= lion:
Row#8	= cat: panther, lion, tiger
Row#9	= fish: lionfish
Row#10	= Brand: Japan, America, German
Row#11	= fungi:
Row#12	= tiger:
Row#13	= panther:
Row#14	= lionfish:
Row#15	= eagle:
Row#16	= human:
Row#17	= whale:
Row#18	= Mercedes: 4Matic, C63Amg
Row#19	= 4Matic: CLA45Amg
Row#20	= TT:
Row#21	= CLA45Amg:
Row#22	= M4:
Row#23	= C63Amg:
Row#24	= WRX: sti
Row#25	= Ford: Mustang
Row#26	= Mustang:
Row#27	= xDrive: 435i
Row#28	= 435i:
Row#29	= Audi: Quattro
Row#30	= Quattro: TT, RS5
Row#31	= Subaru: WRX
Row#32	= sti:
Row#33	= Japan: Subaru
Row#34	= America: Ford
Row#35	= German: Audi, Mercedes, BMW

TreeFromParentChildPairs TraverseDFS for "[animal,mammal], [animal,bird], [lifeform,animal], [cat,lion], [mammal,cat], [animal,fish], [lifeform,plant], [lifeform,fungi], [cat,tiger], [cat,panther], [fish,lionfish], [bird,eagle], [mammal,human], [mammal,whale], [Mercedes,4Matic], [4Matic,CLA45Amg], [Mercedes,C63Amg], [Ford,Mustang], [BMW,M4], [BMW,xDrive], [xDrive,435i], [Audi,Quattro], [Quattro,RS5], [Quattro,TT], [Subaru,WRX], [WRX,sti], [Japan,Subaru], [America,Ford], [German,Audi], [German,Mercedes], [German,BMW], [Brand,German], [Brand,America], [Brand,Japan]":
Brand, Japan, Subaru, WRX, sti, America, Ford, Mustang, German, Audi, Quattro, TT, RS5, Mercedes, 4Matic, CLA45Amg, C63Amg, BMW, M4, xDrive, 435i, lifeform, animal, mammal, cat, panther, lion, tiger, human, whale, bird, eagle, fish, lionfish, plant, fungi
roots: lifeform, Brand
Row#0	= RS5:
Row#1	= lifeform: animal, plant, fungi
Row#2	= BMW: M4, xDrive
Row#3	= animal: mammal, bird, fish
Row#4	= mammal: cat, human, whale
Row#5	= plant:
Row#6	= bird: eagle
Row#7	= lion:
Row#8	= cat: panther, lion, tiger
Row#9	= fish: lionfish
Row#10	= Brand: Japan, America, German
Row#11	= fungi:
Row#12	= tiger:
Row#13	= panther:
Row#14	= lionfish:
Row#15	= eagle:
Row#16	= human:
Row#17	= whale:
Row#18	= Mercedes: 4Matic, C63Amg
Row#19	= 4Matic: CLA45Amg
Row#20	= TT:
Row#21	= CLA45Amg:
Row#22	= M4:
Row#23	= C63Amg:
Row#24	= WRX: sti
Row#25	= Ford: Mustang
Row#26	= Mustang:
Row#27	= xDrive: 435i
Row#28	= 435i:
Row#29	= Audi: Quattro
Row#30	= Quattro: TT, RS5
Row#31	= Subaru: WRX
Row#32	= sti:
Row#33	= Japan: Subaru
Row#34	= America: Ford
Row#35	= German: Audi, Mercedes, BMW

TreeFromParentChildPairs TraverseBFS for "[animal,mammal], [animal,bird], [lifeform,animal], [cat,lion], [mammal,cat], [animal,fish], [lifeform,plant], [lifeform,fungi], [cat,tiger], [cat,panther], [fish,lionfish], [bird,eagle], [mammal,human], [mammal,whale], [Mercedes,4Matic], [4Matic,CLA45Amg], [Mercedes,C63Amg], [Ford,Mustang], [BMW,M4], [BMW,xDrive], [xDrive,435i], [Audi,Quattro], [Quattro,RS5], [Quattro,TT], [Subaru,WRX], [WRX,sti], [Japan,Subaru], [America,Ford], [German,Audi], [German,Mercedes], [German,BMW], [Brand,German], [Brand,America], [Brand,Japan]":
lifeform, animal, plant, fungi, mammal, bird, fish, cat, human, whale, eagle, lionfish, panther, lion, tiger, Brand, Japan, America, German, Subaru, Ford, Audi, Mercedes, BMW, WRX, Mustang, Quattro, 4Matic, C63Amg, M4, xDrive, sti, TT, RS5, CLA45Amg, 435i
roots: Brand
Row#0	= Mercedes: 4Matic, C63Amg
Row#1	= 4Matic: CLA45Amg
Row#2	= xDrive: 435i
Row#3	= BMW: M4, xDrive
Row#4	= TT: German
Row#5	= CLA45Amg:
Row#6	= C63Amg:
Row#7	= M4:
Row#8	= WRX: sti
Row#9	= Ford: Mustang
Row#10	= Mustang:
Row#11	= 435i:
Row#12	= Audi: Quattro
Row#13	= Quattro: TT, RS5
Row#14	= RS5:
Row#15	= Subaru: WRX
Row#16	= sti:
Row#17	= Japan: Subaru
Row#18	= America: Ford
Row#19	= German: Audi, Mercedes, BMW
Row#20	= Brand: Japan, America, German

Found Back Edge: Quattro->TT
TreeFromParentChildPairs TraverseDFS for "[Mercedes,4Matic], [4Matic,CLA45Amg], [Mercedes,C63Amg], [Ford,Mustang], [BMW,M4], [BMW,xDrive], [xDrive,435i], [Audi,Quattro], [Quattro,RS5], [Quattro,TT], [Subaru,WRX], [WRX,sti], [Japan,Subaru], [America,Ford], [German,Audi], [German,Mercedes], [German,BMW], [Brand,German], [Brand,America], [Brand,Japan], [TT,German]":
Cycle Found in DiGraph!
Row#0	= MUC: LHR
Row#1	= JFK: MUC
Row#2	= LHR: SFO
Row#3	= SFO: SJC

*/
#endif