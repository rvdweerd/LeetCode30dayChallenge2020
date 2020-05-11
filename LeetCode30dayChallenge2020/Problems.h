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

namespace LC37 // Sudoko solver
{
	class Solution {
	private:
		struct Pos
		{
			size_t i;
			size_t row;
			size_t col;
			char ch;
		};
		std::unordered_map<size_t, std::set<char>> cache;
		void FillCache(std::vector<std::vector<char>>& board)
		{
			for (size_t i = 0; i < 81; i++)
			{
				size_t row = i / 9; size_t col = i % 9;
				if (board[row][col] == '.')
				{
					std::set<char> reducedSet = { '1','2','3' ,'4' ,'5' ,'6' ,'7' ,'8' ,'9' };
					// check row & col
					for (size_t i = 0; i < 9; i++)
					{
						const char ch_r = board[row][i];
						const char ch_c = board[i][col];
						if (ch_r != '.') reducedSet.erase(ch_r);
						if (ch_c != '.') reducedSet.erase(ch_c);
					}
					// check quadrant
					size_t Q_row = row / 3;
					size_t Q_col = col / 3;
					for (size_t i = 0; i < 3; i++)
					{
						for (size_t j = 0; j < 3; j++)
						{
							const char ch = board[Q_row * 3 + i][Q_col * 3 + j];
							if (ch != '.') reducedSet.erase(ch);
						}
					}
					cache[i] = reducedSet;
				}
			}
		}
		std::set<char> GetOptions(size_t row, size_t col, size_t i, std::vector<std::vector<char>>& board)
		{
			std::set<char> reducedSet = cache.find(i)->second;
			// check row & col
			for (size_t i = 0; i < 9; i++)
			{
				const char ch_r = board[row][i] ;
				const char ch_c = board[i][col] ;
				if (ch_r != '.') reducedSet.erase(ch_r);
				if (ch_c != '.') reducedSet.erase(ch_c);
			}
			// check quadrant
			size_t Q_row = row / 3;
			size_t Q_col = col / 3;
			for (size_t i = 0; i < 3; i++)
			{
				for (size_t j = 0; j < 3; j++)
				{
					const char ch = board[Q_row * 3 + i][Q_col * 3 + j];
					if (ch != '.') reducedSet.erase(ch);
				}
			}
			return reducedSet;
		}
	public:
		void solveSudoku(std::vector<std::vector<char>>& board) 
		{
			std::stack<Pos> stack;
			FillCache(board);
			size_t i = 0;
			while (i < 81)
			{
				size_t row = i / 9;
				size_t col = i % 9;
				if (board[row][col] == '.')
				{
					std::set<char> options = GetOptions(row, col, i,board);
					if (options.size() == 0)
					{
						Pos prevPos = stack.top(); stack.pop();
						while (prevPos.ch == '.')
						{
							board[prevPos.row][prevPos.col] = '.'; // backtrack
							prevPos = stack.top(); stack.pop();
						}
						board[prevPos.row][prevPos.col] = prevPos.ch;
						i = prevPos.i+1;
					}
					else
					{
						stack.push({ i, row, col, '.' });
						for (auto c : options)
						{
							stack.push({ i, row, col, c });
						}
						Pos prevPos = stack.top(); stack.pop();
						board[prevPos.row][prevPos.col] = prevPos.ch;
						i++;
					}
				}
				else
				{
					++i;
				}
			}
		}
	};
	void RunExample()
	{
		std::vector<std::vector<char>> board =
		{
			{'5','3','.',	'.','7','.',	'.','.','.'},
			{'6','.','.',	'1','9','5',	'.','.','.'},
			{'.','9','8',	'.','.','.',	'.','6','.'},

			{'8','.','.',	'.','6','.',	'.','.','3'},
			{'4','.','.',	'8','.','3',	'.','.','1'},
			{'7','.','.',	'.','2','.',	'.','.','6'},

			{'.','6','.',	'.','.','.',	'2','8','.'},
			{'.','.','.',	'4','1','9',	'.','.','5'},
			{'.','.','.',	'.','8','.',	'.','7','9'}
		};
		Solution().solveSudoku(board);
	}
}

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
			//std::set<Graph<int>::Node*> circularNodes;
			//for (auto p : graph.nodemap) // p = pairs of { node_name , Node*}
			//{
			//	if (graph.IsCircularNode(p.second))
			//	{
			//		circularNodes.insert(p.second);
			//	}
			//}
			std::set<Graph<int>::Node*> circularNodes = graph.GetCircularNodes();
			for (auto n : circularNodes)
			{
				for (auto e : n->edges_out)
				{
					if (circularNodes.find(e->end) != circularNodes.end()) // if ourward edge points to another cirulcar node
					{
						if (e->end->InDegree() > 1 || !graph.HasRoot())
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
		std::vector<int> findRedundantDirectedConnection_expensive(std::vector<std::vector<int>>& edges) 
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
		Graph<std::string> graph(
			{
				{"B","C"},{"A","B"},{"C","A"},{"B","D"} ,
				{"D","E"},{"E","F"},{"F","D"},{"G","F"},
				{"G","H"},{"H","I"},{"I","J"},{"J","G"},
				{"J","K"},
			}
		);
		auto vec = graph.StronglyConnectedComponents();

	}
}