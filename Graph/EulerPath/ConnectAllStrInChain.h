#ifndef CONNECT_ALL_STR_IN_CHAIN_H
#define CONNECT_ALL_STR_IN_CHAIN_H
#include "Debug.h"
/*
http://stackoverflow.com/questions/17706124/given-an-array-of-strings-return-true-if-each-string-could-be-connected-to-othe
http://www.careercup.com/question?id=6362892580421632
http://stackoverflow.com/questions/9268709/detecting-when-matrix-multiplication-is-possible/9268893#9268893
Given an array of strings.
A chain of two strings can be connected if the last char of one string matches the first char of the other.
Determine if all the strings can be connected in one chain.
Example:
"abc", "cde", "cad", "def", "eac" can be connected in a chain:
"abc"->"cde"->"eac"->"cad"->"def"
Solution:
Create a directed graph from the strings.
The vertices of the graph are the 26 letters.
The edge between two letters represents an existing string with starting and ending letters, respectively.
If an Eulerian path exists in the directed graph, all the string can be connected in a chain.

*/
class ConnectAllStrInChain
{
public:
	ConnectAllStrInChain(){}
	~ConnectAllStrInChain(){}

	//use Hierholzer Algorithm to find Euler Path and Euler Circuit in a single connect component
	bool ExistFindEulerPathInConnectedDiGraph(const std::vector<std::string> & strs)
	{
		//note: the order of adj vertices in DiG doesn't matter for Hierholzer Algorithm
		std::unordered_map<char, std::unordered_set<char>> DiG;
		for (auto & s : strs)
        {
            DiG[s.front()].insert(s.back());
            if (DiG.count(s.back()) == 0) DiG.insert({s.back(),{}});//insert end vertex of edge
        }
		bool anyEulerPath = false;
        bool allEulerPaths = true;
		std::cout << "ConnectAllStrInChain HierholzerFindEulerPathInConnectedDiGraph for \"" << Debug::ToStr1D<std::string>()(strs) << "\": " << std::endl;
		for (auto & p : DiG)
		{
			//find Euler Path starting with each vertex
			std::string res = DFSStk(DiG, p.first);
			int numEdges = res.size()-1;//the result Euler Path must contain all edges from the DiG
			bool containAllEdges = (numEdges==strs.size());
			for (int i = 0; i < numEdges; ++i)
			{
				if (!DiG.count(res[i]) || !DiG[res[i]].count(res[i+1]))
				{
					containAllEdges = false;
					break;
				}
			}
			anyEulerPath |= containAllEdges;
			allEulerPaths &= containAllEdges;
			std::cout << "EulerPath@" << p.first << " [" << res << "]: " << containAllEdges << std::endl;
		}
		std::cout << "AnyEulerPath: " << anyEulerPath << ", AllEulerPaths(EulerCircuit): " << allEulerPaths << std::endl;
		return anyEulerPath;
	}
	std::string DFSStk(std::unordered_map<char,std::unordered_set<char>> DiG, char cur) //Hierholzer Algorithm: same as ReconstructItinerary
	{
		/*
		Hierholzer Algorithm:
		Keep going one path until stuck, then retreat and push the vertices along the route to a stack until it reaches a vertex that has alternative paths, then go along that path and repeat the process.
		The assumption for this to work is there is guaranteed to exist one Euler path.
		 */
		std::stack<char> stk;
		stk.push(cur);
		std::string res;
		while (!stk.empty())
		{
			while(!DiG[stk.top()].empty())
			{
				char top = stk.top();
				stk.push(*DiG[top].begin());
				DiG[top].erase(DiG[top].begin());

			}
			cur = stk.top();
			stk.pop();
			res.push_back(cur);
		}
		std::reverse(res.begin(), res.end());
		return res;
	}



	/*
	 	Eulerian directed trail:
		iff at most 1 vertex has (out-degree) - (in-degree) = 1, at most 1 vertex has (in-degree) - (out-degree) = 1, every other vertex has equal in-degree and out-degree, and all of its vertices with nonzero degree belong to a single connected component
		a) same as above
		b) 0 or 1 vertex has (out-degree) - (in-degree) = 1.
		c) 0 or 1 vertex has (in-degree) - (out-degree) = 1.
		d) Every other vertex has equal in-dgree and out-degree.
	 */
	bool ExistEulerPathInDigraph(const std::vector<std::string> & strs)
	{
		int N = 26;
		std::vector<std::vector<int> > adjMatrix(N, std::vector<int>(N, 0));//adjacency matrix for directed graph

		int strCount = strs.size();
		for (int i = 0; i < strCount; ++i)
		{
			std::string str = strs[i];
			adjMatrix[str.front() - 'a'][str.back() - 'a'] = 1;
		}

		std::vector<int> visitIndex(N, -1);
		int visitCount = -1;
		std::vector<int> componentLabel(N, -1);
		int curComponentLabel = -1;
		std::vector<std::pair<int, int> > degree(N, std::make_pair(0, 0));//first: in-degree, second: out-degree
		for (int i = 0; i < N; ++i)
		{
			if (visitIndex[i] == -1)
			{
				++curComponentLabel;
				this->UndirectedDFS_Directed_AdjacencyMatrix(adjMatrix, i, visitCount, visitIndex, curComponentLabel, componentLabel, degree);
			}
		}
		//1. determine if all non-zero degree vertices in the graph are weakly connected
		bool isWeaklyConnected = true;
		bool firstNonZeroDegree = true;
		int weakComponentLabel = -1;
		for (int i = 0; i < N; ++i)
		{
			if (degree[i].first + degree[i].second > 0)
			{
				if (firstNonZeroDegree)
				{
					firstNonZeroDegree = false;
					weakComponentLabel = componentLabel[i];
				}
				else
				{
					if (componentLabel[i] != weakComponentLabel)
					{
						isWeaklyConnected = false;
						break;
					}
				}
			}
		}
		//2. count vertices with diff in/out degree and vertices with difference btw in/out degree equals to 1
		int diffInOutDegreeCount = 0;
		int inDegreeOneMoreCount = 0;
		int outDegreeOneMoreCount = 0;
		for (int i = 0; i < N; ++i)
		{
			if (degree[i].first != degree[i].second)
			{
				++diffInOutDegreeCount;
				if (degree[i].first - degree[i].second == 1)
					++inDegreeOneMoreCount;
				if (degree[i].second - degree[i].first == 1)
					++outDegreeOneMoreCount;
			}
		}

		bool res;
		if (isWeaklyConnected &&
			(inDegreeOneMoreCount == 0 || inDegreeOneMoreCount == 1) &&
			(outDegreeOneMoreCount == 0 || outDegreeOneMoreCount == 1) &&
			(inDegreeOneMoreCount + outDegreeOneMoreCount == diffInOutDegreeCount))
			res = true;
		else
			res = false;
		//Debug::Print2D<int>()(adjMatrix, false);
		//std::cout << Debug::ToStr1D<int>()(degree) << std::endl;
		//std::cout << "WeaklyConnected: " << isWeaklyConnected << "; InDegreeOneMoreCount: " << inDegreeOneMoreCount << "; OutDegreeOneMoreCount: " << outDegreeOneMoreCount << "; DiffInOutDegreeCount: " << diffInOutDegreeCount << std::endl;
		std::cout << "ConnectAllStrInChain for \"" << Debug::ToStr1D<std::string>()(strs) << "\": " << res << std::endl;
		return res;
	}
	void UndirectedDFS_Directed_AdjacencyMatrix(const std::vector<std::vector<int> > & adjMatrix, int v, int & visitCount, std::vector<int> & visitIndex, 
		int & curComponentLabel, std::vector<int> & componentLabel, std::vector<std::pair<int, int> > & degree)
	{
		int N = adjMatrix.size();
		visitIndex[v] = ++visitCount;
		componentLabel[v] = curComponentLabel;
		for (int i = 0; i < N; ++i)
		{
			if (adjMatrix[v][i] > 0)//out-degree of vertex v, in-degree of vertex i
				++degree[i].first;
			if (adjMatrix[i][v] > 0)//in-degree of vertex v, out-degree of vertex i
				++degree[i].second;
			if (adjMatrix[v][i] > 0 && i != v)//out-degree of vertex v
			{
				if (visitIndex[i] == -1)
					this->UndirectedDFS_Directed_AdjacencyMatrix(adjMatrix, i, visitCount, visitIndex, curComponentLabel, componentLabel, degree);
			}
			if (adjMatrix[i][v] > 0 && i != v)//in-degree of vertex v (since adjMatrix is directed, we also need to check reversed edge when running undirected DFS)
			{
				if (visitIndex[i] == -1)
					this->UndirectedDFS_Directed_AdjacencyMatrix(adjMatrix, i, visitCount, visitIndex, curComponentLabel, componentLabel, degree);
			}
		}
	}
};
/*
		a-->c<->e
		    |
			v
			d-->f

ConnectAllStrInChain for "abc, cde, cad, def, eac": 1
ConnectAllStrInChain HierholzerFindEulerPathInConnectedDiGraph for "abc, cde, cad, def, eac":
EulerPath@d [df]: 0
EulerPath@e [ecdfe]: 0
EulerPath@c [cecdf]: 0
EulerPath@f [f]: 0
EulerPath@a [acecdf]: 1
AnyEulerPath: 1, AllEulerPaths(EulerCircuit): 0



 		a-->c<->d
		    |
			v
			e-->f

ConnectAllStrInChain HierholzerFindEulerPathInConnectedDiGraph for "abc, cdd, cae, eef, dac":
EulerPath@e [ef]: 0
EulerPath@d [dcefd]: 0
EulerPath@c [cdcef]: 0
EulerPath@f [f]: 0
EulerPath@a [acdcef]: 1
AnyEulerPath: 1, AllEulerPaths(EulerCircuit): 0



		c-->e
		| /
		vv
		d-->f-->b

ConnectAllStrInChain for "fcb, cde, cad, def, ead": 0
ConnectAllStrInChain HierholzerFindEulerPathInConnectedDiGraph for "fcb, cde, cad, def, ead":
EulerPath@d [dfb]: 0
EulerPath@e [edfb]: 0
EulerPath@c [cdedfb]: 0
EulerPath@b [b]: 0
EulerPath@f [fb]: 0
AnyEulerPath: 0, AllEulerPaths(EulerCircuit): 0



		a<-->k--->l
		| ^   ^   |
		|  \   \  |
		|    \  \ |
		v      \ \v
		b--->c--->f<--
		|         |   |
		v          ---
		d

ConnectAllStrInChain for "bd, fk, ab, kl, cf, ff, fa, ak, ka, lf, bc": 1
ConnectAllStrInChain HierholzerFindEulerPathInConnectedDiGraph for "bd, fk, ab, kl, cf, ff, fa, ak, ka, lf, bc":
EulerPath@c [cfklffakabcd]: 0
EulerPath@l [lfkabcffakdl]: 0
EulerPath@a [abcfklffakad]: 0
EulerPath@k [klfkabcffakd]: 0
EulerPath@f [fklffakabcfd]: 0
EulerPath@d [d]: 0
EulerPath@b [bcfklffakabd]: 1
AnyEulerPath: 1, AllEulerPaths(EulerCircuit): 0
*/
#endif