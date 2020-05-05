#pragma once
#include <iostream>
#include <cstring>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <queue>
#include "GraphClass.h"

namespace LC685 // Redundant connections
{
	class Solution {
	public:
		std::vector<int> findRedundantDirectedConnection(std::vector<std::vector<int>>& edges) 
		{
			// Build graph
			Graph<int> graph(edges);
			std::set<std::vector<int>> removableEdges;

			// Case A: Is there a circuit? 
			std::set<Graph<int>::Node*> circularNodes;
			for (auto p : graph.nodemap) // p = pairs of { node_name , Node*}
			{
				if (graph.IsCircularNode(p.second))
				{
					circularNodes.insert(p.second);
				}
			}
			for (auto n : circularNodes)
			{
				for (auto e : n->edges_out) 
				{
					if (circularNodes.find(e->end) != circularNodes.end()) // if ourward edge points to another cirulcar node
					{
						if (e->end->InDegree() > 1 || !graph.HasRoot() )
						{
							removableEdges.insert({ e->start->name,e->end->name });
						}
					}
				}
			}
			// Case B: No circuit, but is there a node with InDegree > 1? THEN: any incoming edges of this node can be removed
			if (removableEdges.size() == 0) // Move to Case B
			{
				for (auto p : graph.nodemap) // p = pairs of { node_name , Node*}
				{
					if (p.second->InDegree() > 1)
					{
						for (auto e : p.second->edges_in) // e = all incoming edges
						{
							removableEdges.insert({ e->start->name,e->end->name });
						}
					}
				}
			}
			// Result processing
			if (removableEdges.size() == 0) return {};
			else if (removableEdges.size() == 1) return  *removableEdges.begin();
			else // find last occurence of a removable edge in the input 2D array of edges (our function parameter)
			{
				for (size_t i = edges.size() - 1; i >= 0; --i)
				{
					if (removableEdges.find(edges[i]) != removableEdges.end())
					{
						return edges[i];
					}
				}

			}
			
			
			
			return {};
		}
	};

	void RunExample()
	{
		std::vector<std::vector<int>> edges1 = { {1,2},{1,3},{2,3} }; // ans: [2,3]
		auto ans1 = Solution().findRedundantDirectedConnection(edges1);
		std::vector<std::vector<int>> edges2 = { {1,2},{2,3},{3,4},{4,1},{1,5} }; // ans: [4,1]
		auto ans2 = Solution().findRedundantDirectedConnection(edges2);
		std::vector<std::vector<int>> edges3 = { {2,1},{3,1},{4,2},{1,4} }; //  ans: [2,1]
		auto ans3 = Solution().findRedundantDirectedConnection(edges3);
		std::vector<std::vector<int>> edges4 = { {5,2},{2,3},{3,4},{4,5},{5,1} }; //  ans: [4,5]
		auto ans4 = Solution().findRedundantDirectedConnection(edges4);

	}
}