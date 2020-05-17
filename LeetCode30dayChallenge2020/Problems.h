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

namespace LC36 //  Is Valid Sudoko
{
	class Solution {
	public:
		const std::vector<std::vector<int>> quadrants = {
			{0,0,0,1,1,1,2,2,2},
			{0,0,0,1,1,1,2,2,2},
			{0,0,0,1,1,1,2,2,2},
			{3,3,3,4,4,4,5,5,5},
			{3,3,3,4,4,4,5,5,5},
			{3,3,3,4,4,4,5,5,5},
			{6,6,6,7,7,7,8,8,8},
			{6,6,6,7,7,7,8,8,8},
			{6,6,6,7,7,7,8,8,8}
		};
		bool isValidSudoku(std::vector<std::vector<char>>& board) 
		{
			std::vector<std::set<int>> rows(9);
			std::vector<std::set<int>> cols(9);
			std::vector<std::set<int>> quads(9);
			for (size_t r = 0; r < 9; r++)
			{
				for (size_t c = 0; c < 9; c++)
				{
					if (board[r][c] == '.') continue;
					if (!rows[r].insert(board[r][c]).second)
					{
						return false;
					}
					if (!cols[c].insert(board[r][c]).second)
					{
						return false;
					}
					if (!quads[quadrants[r][c]].insert(board[r][c]).second)
					{
						return false;
					}
				}
			}
			return true;
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
		Solution().isValidSudoku(board);
	}
}
namespace LC42 // Trapping Rain Water
{
	class Solution {
	public:
		int trap(std::vector<int>& height) // DP, O(N), requires 2 runs and evaluation run
		{
			std::vector<int> highestL;  highestL.resize(height.size()); 
			std::vector<int> highestR;  highestR.resize(height.size()); 
			int highMark = 0;
			for (size_t i = 1; i < height.size(); i++)
			{
				highestL[i] = std::max(highMark, height[i-1]);
				highMark = highestL[i];
			}
			highMark = 0;
			for (int i = height.size()-2; i>=0; i--)
			{
				highestR[(size_t)i] = std::max(highMark, height[(size_t)i + 1]);
				highMark = highestR[(size_t)i];
			}
			int total = 0;
			for (size_t i = 1; i < height.size(); i++)
			{
				int lowMark = std::min(highestL[i], highestR[i]);
				if (height[i] < lowMark) total += lowMark - height[i];
			}
			return total;
		}
		int trap_Maps(std::vector<int>& height) // O(N * n)?
		{
			std::map<int, int>  resevoir;
			int  total=0;
			int highPoint = 0;
			for (auto v : height)
			{
				for (size_t i = 1; i <= (size_t)v; i++)
				{
					for (auto& p : resevoir)
					{
						if (p.first <= v)
						{
							total += p.second;
							p.second = 0;
						}
					}
					if (resevoir.find(i) == resevoir.end()) resevoir[i] = 0;
				}
				for (size_t i = v+1; i <= (size_t)highPoint; i++)
				{
					resevoir[i]++;
				}
				highPoint = std::max(highPoint, v);
			}
			return total;
		}
	};
	void RunExample()
	{
		std::vector<int> vec;
		int ans;
		vec = { 0,1,0,2,1,0,1,3,2,1,2,1 };
		ans	= Solution().trap(vec); // 6
		vec = { 5,0,5,0,1,0,5 };
		ans = Solution().trap(vec);  //19
		vec = { 0,1,0,2,0,3,4,2,3,1,5,0,2,1,6,2,2,0 };
		ans = Solution().trap(vec); //21
		vec = {  };
		ans = Solution().trap(vec); //0
		vec = { 0,10,0,0};
		ans = Solution().trap(vec); //0
	}
}
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
namespace LC587 // Erect the Fence
{
	struct Vec2
	{
		Vec2(std::vector<int> v1, std::vector<int> v2)
			:
			x(v2[0]-v1[0]),
			y(v2[1]-v1[1])
		{}
		Vec2(std::vector<int> v)
			:
			x(v[0]),
			y(v[1])
		{}
		Vec2(int a, int b)
			:
			x(a),
			y(b)
		{}
		void Print()
		{
			std::cout << "[" << x << "," << y << "], ";
		}
		int operator%(Vec2& v2)
		{
			return (x * v2.y - y * v2.x);
		}
		Vec2 operator-(Vec2& rhs)
		{
			return Vec2(x-rhs.x,y-rhs.y);
		}
		int x;
		int y;
	};
	class Solution {
	private:
		void SweepUpper(std::vector<std::vector<int>>& points, std::stack<std::vector<int>>& stack)
		{
			stack.push(points[0]);
			stack.push(points[1]);
			Vec2 p0(points[0]);
			Vec2 p1(points[1]);

			for (size_t i = 2; i<points.size();i++)
			{
				Vec2 p2 = points[i];
				Vec2 v1 = p1 - p0;
				Vec2 v2 = p2 - p0;

				while (v1 % v2 > 0)
				{
					stack.pop(); stack.pop();
					p1 = p0; 
					if (stack.empty())
					{
						stack.push({ p0.x,p0.y });
						break;
					}
					p0 = stack.top();
					stack.push({p1.x,p1.y});
					v1 = p1 - p0;
					v2 = p2 - p0;
				}
				stack.push(points[i]);
				p0 = p1;
				p1 = points[i];
			}
		}
		void SweepLower(std::vector<std::vector<int>>& points, std::stack<std::vector<int>>& stack)
		{
			stack.push(points[points.size()-1]);
			stack.push(points[points.size()-2]);
			Vec2 p0(points[points.size() - 1]);
			Vec2 p1(points[points.size() - 2]);

			for (int i = points.size()-3; i >= 0; i--)
			{
				Vec2 p2 = points[i];
				Vec2 v1 = p1 - p0;
				Vec2 v2 = p2 - p0;

				while (v1 % v2 > 0)
				{
					stack.pop(); stack.pop();
					p1 = p0;
					if (stack.empty())
					{
						stack.push({ p0.x,p0.y });
						break;
					}
					p0 = stack.top();
					stack.push({ p1.x,p1.y });
					v1 = p1 - p0;
					v2 = p2 - p0;
				}
				stack.push(points[i]);
				p0 = p1;
				p1 = points[i];
			}
		}
	public:
		std::vector<std::vector<int>> outerTrees(std::vector<std::vector<int>>& points) 
		{
			if (points.size() <= 3) return points;
			std::sort(points.begin(), points.end(), [](std::vector<int> v1, std::vector<int> v2) {return (v1 < v2); });
			std::stack<std::vector<int>> stack;
			SweepUpper(points,stack);
			SweepLower(points, stack);

			std::set<std::vector<int>> set;
			while (!stack.empty())
			{
				set.insert(stack.top());
				stack.pop();
			}
			std::vector<std::vector<int>> result(set.begin(), set.end());
			return result;
		}
	};

	void RunExample()
	{
		std::vector<std::vector<int>> vec = { {0,0}, {1,1}, {2,2}, {2,1}, {3,10}, {4,0} ,{3,0} };
		//std::vector<std::vector<int>> vec = { {0,0}, {1,0}, {1,1}, {2,0}, {2,1}, {2,2}, {3,0} };
		//std::vector<std::vector<int>> vec = { {1, 1}, {2, 2}, {2, 0}, {2, 4}, {3, 3}, {4, 2} };
		//std::vector<std::vector<int>> vec = { {0, 2}, {1, 1}, {2, 2}, {2, 4}, {4, 2}, {3, 3} };
		//std::vector<std::vector<int>> vec = { {2,2}, {3,2}, {10,2} };
		std::cout << "Input:  "; for (auto p : vec) Vec2(p).Print(); std::cout << std::endl;
		auto ans = Solution().outerTrees(vec);
		std::cout << "Output: "; for (auto p : ans) Vec2(p).Print(); std::cout << std::endl;
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