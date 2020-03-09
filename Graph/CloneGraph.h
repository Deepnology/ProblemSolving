#ifndef CLONE_GRAPH_H_
#define CLONE_GRAPH_H_
/*
Leetcode: Clone Graph
Elements of programming interview, Graph: Clone a graph (BFS)
// Clone an undirected graph. Each node in the graph contains a label and a
// list of its neighbors.
//
// Note:
// Nodes are labeled uniquely.
//
// We use # as a separator for each node, and , as a separator for node label
// and each neighbor of the node.
// As an example, consider the serialized graph {0,1,2#1,2#2,2}.
//
// The graph has a total of three nodes, and therefore contains three parts
// as separated by #.
//
// First node is labeled as 0. Connect node 0 to both nodes 1 and 2.
// Second node is labeled as 1. Connect node 1 to node 2.
// Third node is labeled as 2. Connect node 2 to node 2 (itself), thus
// forming a self-cycle.
//
// Complexity:
// BFS or DFS, O(V+E) time, O(E) space
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <algorithm>

class CloneGraph
{
public:
	CloneGraph(){}
	~CloneGraph(){}

	struct UndirectedGraphNode
	{
		UndirectedGraphNode(int x) : label(x) {}
		int label;
		std::vector<UndirectedGraphNode *> neighbors;
	};

	//1. DFS
	UndirectedGraphNode * DFS(UndirectedGraphNode * node)
	{
		if (node == NULL)
			return NULL;

		std::unordered_map<UndirectedGraphNode *, UndirectedGraphNode *> table;//key: original node, value: new node
		
		UndirectedGraphNode * res = this->dfsCloneNodeRecur(node, table);
		std::cout << "CloneGraph DFS: " << this->toString(res) << std::endl;
		return res;
	}
private:
	UndirectedGraphNode * dfsCloneNodeRecur(UndirectedGraphNode * cur, std::unordered_map<UndirectedGraphNode *, UndirectedGraphNode *> & table)
	{
		if (table.count(cur) == 0)
		{
			table[cur] = new UndirectedGraphNode(cur->label);//clone this node (value), put it in table together with the original node (key)
			for (auto node : cur->neighbors)
			{
				table[cur]->neighbors.push_back(this->dfsCloneNodeRecur(node, table));//clone all the neighbor nodes of the original node (key), put it in the new node's neighbors
			}
		}
		return table[cur];//return the cloned new node (value)
	}


public:
	//2. BFS
	UndirectedGraphNode * BFS(UndirectedGraphNode * node)
	{
		if (node == NULL)
			return NULL;

		std::unordered_map<UndirectedGraphNode *, UndirectedGraphNode *> table;//key: original node, value: new node
		table[node] = new UndirectedGraphNode(node->label);
		std::queue<UndirectedGraphNode *> queue;
		queue.push(node);

		while (!queue.empty())
		{
			UndirectedGraphNode * cur = queue.front();
			queue.pop();

			for (auto nebr : cur->neighbors)
			{
				if (table.count(nebr) == 0)
				{
					table[nebr] = new UndirectedGraphNode(nebr->label);
					queue.push(nebr);
				}
				table[cur]->neighbors.push_back(table[nebr]);
			}
		}

		std::cout << "CloneGraph BFS: " << this->toString(table[node]) << std::endl;
		return table[node];
	}


	std::string toString(UndirectedGraphNode * node)
	{
		std::unordered_set<UndirectedGraphNode *> vs;//keep track of visited nodes
		std::queue<UndirectedGraphNode *> qs;//for BFS
		std::ostringstream oss;
		qs.push(node);
		vs.insert(node);
		while (!qs.empty())//BFS
		{
			node = qs.front();
			qs.pop();

			oss << node->label << " ";//now visit the node

			for (auto nebr : node->neighbors)
			{
				if (vs.count(nebr) == 0)
				{
					vs.insert(nebr);
					qs.push(nebr);
				}
			}
		}

		return oss.str();
	}

	static void DeleteGraph(UndirectedGraphNode * node)
	{
		std::vector<UndirectedGraphNode *> tmp;

		std::unordered_set<UndirectedGraphNode *> visited;
		std::queue<UndirectedGraphNode *> queue;
		queue.push(node);
		visited.insert(node);
		while (!queue.empty())
		{
			node = queue.front();
			queue.pop();

			tmp.push_back(node);//now visit the node

			for (auto nebr : node->neighbors)
			{
				if (visited.count(nebr) == 0)
				{
					visited.insert(nebr);
					queue.push(nebr);
				}
			}
		}

		//now delete tmp
		for (std::vector<UndirectedGraphNode *>::iterator i = tmp.begin(); i != tmp.end(); ++i)
		{
			delete *i;
			*i = 0;
		}
	}
};
/*
CloneGraph DFS: 0 1 2
CloneGraph BFS: 0 1 2
*/
#endif