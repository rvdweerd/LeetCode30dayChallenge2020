#pragma once
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cstring>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <queue>
#include "GraphClass.h"
#include <limits>

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
		std::cout << "Input:  "; for (auto p : vec) Vec2(p).Print(); //std::cout << std::endl;
		auto ans = Solution().outerTrees(vec);
		std::cout << "Output: "; for (auto p : ans) Vec2(p).Print(); //std::cout << std::endl;
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
namespace LC765 // Couples holding hands
{
	int minSwapsCouples(std::vector<int>& row)
	{
		std::map<int, size_t> map;
		for (size_t i=0; i<row.size();i++)
		{
			map[row[i]] = i;
		}
		int count = 0;
		//size_t i = 0;
		for (size_t i = 0; i < row.size()-1; i+=2)
		{
			if (row[i]/2 != row[i+1] / 2)
			{
				int spouse = row[i] % 2 == 0 ? row[i] + 1 : row[i] - 1;
				auto j = map.find(spouse)->second;
				int temp = row[i+1];
				row[i+1] = row[j];
				row[j] = temp;
				map[spouse] = i+1;
				map[temp] = j;
				count++;
			}
		}
		return count;
	}
	void RunExample()
	{
		std::vector<int> row;
		int ans;
		row = { 4,1,5,3,2,0 }; //2
		ans = minSwapsCouples(row);
		row = { 5,3,4,2,1,0 }; //1
		ans = minSwapsCouples(row);
		row = { 5, 4, 2, 6, 3, 1, 0, 7 };
		ans = minSwapsCouples(row); //2
		row = { 0,2,4,6,7,1,3,5};
		ans = minSwapsCouples(row); //3
		row = { 3,2,0,1 };
		ans = minSwapsCouples(row); //0
		row = { 1,4,0,5,8,7,6,3,2,9 };
		ans = minSwapsCouples(row); //3
	}
}
namespace LC846 // Hand of Straights
{
	class Solution {
	public:
		bool isNStraightHand(std::vector<int>& hand, int W) 
		{
			std::map<int, size_t> map;
			for (int v : hand) map[v]++;
			for (auto p : map)
			{
				if (p.second < 0) return false;
				while (p.second > 0)
				{
					for (int i = p.first; i < p.first + W; i++)
					{
						auto it = map.find(i);
						if (it == map.end() || it->second <=0) return false;
						it->second--;
					}
					p.second--;
				}
			}
			return true;
		}
	};
	void RunExample()
	{
		std::vector<int> hand;
		bool ans;
		hand = { 1,2,3,6,2,3,4,7,8 };
		ans = Solution().isNStraightHand(hand,3);//true
		hand = { 1,2,3,4,5 };
		ans = Solution().isNStraightHand(hand, 4);//false
		hand = { 1,2,3,1,2,3 };
		ans = Solution().isNStraightHand(hand, 3); //true


	}
}
namespace LC1263 // Box Pusher
{
	using ULL = unsigned long long;
	auto Pos2PBPos = [](size_t pusherPos_0, size_t ballPos_0)->ULL { return (ULL(pusherPos_0) << 32 | ballPos_0); };
	struct PBData
	{
		//using ULL = unsigned long long;
		ULL PBPos;
		int n = 0;
		std::vector<ULL> path;
	};
	struct Field
	{
		Field(std::string filename)
		{
			std::ifstream in(filename);
			std::string str;
			while (std::getline(in, str))
			{
				for (size_t i = 0; i < str.size(); i++)
				{
					char ch = str[i];
					vec0.push_back(ch);
					map.insert({ vec0.size() - 1,ch });
					if (ch != '.' && ch != '#') startpositions[ch] = vec0.size() - 1;
				}
				height++;
			}
			size = vec0.size();
			width = size / height;
			vec = vec0;
			vec[startpositions['b']] = '.';
			vec[startpositions['O']] = '.';
		}
		Field(std::vector<std::vector<char>>& grid)
		{
			height = grid.size();
			width = grid[0].size();
			for (size_t y = 0; y < height; y++)
			{
				for (size_t x = 0; x < width; x++)
				{
					char ch = 0;
					if (grid[y][x] == 'S') ch = 'b';
					else if (grid[y][x] == 'T') ch = 'X';
					else if (grid[y][x] == 'B') ch = 'O';
					else ch = grid[y][x];
					vec0.push_back(ch);
					map.insert({ vec0.size() - 1,ch });
					if (ch != '.' && ch != '#') startpositions[ch] = vec0.size() - 1;
				}
			}
			size = vec0.size();
			vec = vec0;
			vec[startpositions['b']] = '.';
			vec[startpositions['O']] = '.';
		}
		std::vector<char> vec0;
		std::vector<char> vec;
		size_t width = 0;
		size_t height = 0;
		size_t size = 0;
		std::unordered_map<size_t, char> map;
		std::unordered_map<char, size_t> startpositions;
	};
	class Maze
	{
	public:
		Maze(std::string filename)
			:
			field(filename),
			ballPos_0(field.startpositions['O']),
			pusherPos_0(field.startpositions['b']),
			goalPos(field.startpositions['X'])
		{
			PBPos_0 = Pos2PBPos(pusherPos_0, ballPos_0);
		}
		Maze(std::vector<std::vector<char>>& grid)
			:
			field(grid),
			ballPos_0(field.startpositions['O']),
			pusherPos_0(field.startpositions['b']),
			goalPos(field.startpositions['X'])
		{
			PBPos_0 = Pos2PBPos(pusherPos_0, ballPos_0);

		}
		std::vector<size_t> GetReachablePushPositions(ULL PBPos)
		{
			size_t pusherPos = PBPos >> 32;
			size_t ballPos = (PBPos << 32) >> 32;

			std::vector<size_t> returnvec;
			for (size_t y = 0; y < field.height; y++)
			{
				for (size_t x = 0; x < field.width; x++)
				{
					size_t pos = y * field.width + x;
					if (IsReachableByPusher(PBPos, pos)) returnvec.push_back(pos);
				}
			}
			return returnvec;
		}
		std::vector<size_t> GetReachableBallPushPositions(ULL PBPos)
		{
			size_t pusherPos = PBPos >> 32;
			size_t ballPos = (PBPos << 32) >> 32;

			std::vector<size_t> ballNeighbors = GetAccessibleNeighbors(PBPos, ballPos);
			std::vector<size_t> returnvec;
			std::copy_if(ballNeighbors.begin(), ballNeighbors.end(), std::back_inserter(returnvec), [this, &PBPos](size_t p) {return IsReachableByPusher(PBPos, p); });
			return returnvec;
		}
		std::vector<size_t> GetNewBallPositions(ULL PBPos)
		{
			size_t pusherPos = PBPos >> 32;
			size_t ballPos = (PBPos << 32) >> 32;

			std::vector<size_t> pushPositions = GetReachableBallPushPositions(PBPos);
			std::vector<size_t> returnvec;
			size_t ballX = ballPos % field.width;
			size_t ballY = ballPos / field.width;
			for (auto p : pushPositions)
			{
				auto CanPlace = [this, &pusherPos](size_t p)->bool {return (field.vec[p] == '.' || field.vec[p] == 'X' || p == pusherPos); };
				int delta = ballPos - p;
				int test = ballPos + delta;
				if (test >= 0)
				{
					if (delta == 1 && ballX != field.width - 1 && CanPlace(ballPos + delta)) returnvec.push_back(ballPos + delta);
					if (delta == -1 && ballX != 0 && CanPlace(ballPos + delta)) returnvec.push_back(ballPos + delta);
					if (delta == field.width && ballY != field.height - 1 && CanPlace(ballPos + delta)) returnvec.push_back(ballPos + delta);
					if (delta == -(int)field.width && ballY != 0 && CanPlace(ballPos + delta)) returnvec.push_back(ballPos + delta);
				}
			}
			return returnvec;
		}
		std::vector<ULL> GetNewPBPositions(ULL PBPos)
		{
			size_t pusherPos = PBPos >> 32;
			size_t ballPos = (PBPos << 32) >> 32;

			std::vector<size_t> pushPositions = GetReachableBallPushPositions(PBPos);
			std::vector<ULL> returnvec;
			size_t ballX = ballPos % field.width;
			size_t ballY = ballPos / field.width;
			for (auto p : pushPositions)
			{
				auto CanPlace = [this, &pusherPos](size_t p)->bool {return (field.vec[p] == '.' || field.vec[p] == 'X' || p == pusherPos); };
				int delta = ballPos - p;
				int test = ballPos + delta;
				if (test >= 0)
				{
					if (delta == 1 && ballX != field.width - 1 && CanPlace(ballPos + delta)) // push ball East
					{
						returnvec.push_back(Pos2PBPos(ballPos, ballPos + delta));
					}
					if (delta == -1 && ballX != 0 && CanPlace(ballPos + delta)) // push ball West
					{
						returnvec.push_back(Pos2PBPos(ballPos, ballPos + delta));
					}
					if (delta == field.width && ballY != field.height - 1 && CanPlace(ballPos + delta)) // push ball South
					{
						returnvec.push_back(Pos2PBPos(ballPos, ballPos + delta));
					}
					if (delta == -(int)field.width && ballY != 0 && CanPlace(ballPos + delta)) // push ball North
					{
						returnvec.push_back(Pos2PBPos(ballPos, ballPos + delta));
					}
				}
			}
			return returnvec;
		}
		std::vector<size_t> GetAccessibleNeighbors(ULL PBPos, size_t pos)
		{
			size_t pusherPos = PBPos >> 32;
			size_t ballPos = (PBPos << 32) >> 32;

			size_t x = pos % field.width;
			size_t y = pos / field.width;
			std::vector<size_t> returnvec;
			auto CanStand = [&](size_t p)->bool
			{
				return ((field.vec[p] == '.' || p == pusherPos || field.vec[p] == 'X') && p != ballPos);
			};
			// North
			if (y != 0 && CanStand(pos - field.width)) returnvec.push_back(pos - field.width);
			// East
			if (x != field.width - 1 && CanStand(pos + 1)) returnvec.push_back(pos + 1);
			// South
			if (y != field.height - 1 && CanStand(pos + field.width)) returnvec.push_back(pos + field.width);
			// West
			if (x != 0 && CanStand(pos - 1)) returnvec.push_back(pos - 1);
			return returnvec;
		}
		bool IsReachableByPusher(ULL PBPos, size_t fieldPos)
		{
			size_t pusherPos = PBPos >> 32;
			size_t ballPos = (PBPos << 32) >> 32;

			if (fieldPos == pusherPos) return true;
			else if (field.vec[fieldPos] != '.') return false;
			//std::vector<char> localField = field.vec;
			std::set<size_t> visited; visited.insert(pusherPos);
			std::queue<size_t> queue;
			queue.push(pusherPos);
			while (!queue.empty())
			{
				size_t currPos = queue.front(); queue.pop();
				if (currPos == fieldPos) return true;
				//auto test = GetAccessibleNeighbors(currPos);
				for (size_t p : GetAccessibleNeighbors(PBPos, currPos))
				{
					if (visited.find(p) == visited.end())
					{
						if (p == fieldPos) return true;
						queue.push(p);
						visited.insert(p);
					}
				}
			}
			return false;
		}
		void PrintPositionsOnMaze(std::vector<size_t> vec)
		{
			for (size_t y = 0; y < field.height; y++)
			{
				for (size_t x = 0; x < field.width; x++)
				{
					size_t pos = y * field.width + x;
					if (std::find(vec.begin(), vec.end(), pos) != vec.end()) std::cout << '$';
					else std::cout << field.vec[pos];
				}
				std::cout << '\n';
			}
			for (auto v : vec) std::cout << v << ", ";
			std::cout << "\n\n";
		}
		void PrintPBPosOnMaze(ULL PBPos)
		{
			std::vector<char> vec_local = field.vec;
			size_t pusherPos = PBPos >> 32;
			size_t ballPos = (PBPos << 32) >> 32;
			vec_local[pusherPos] = 'b';
			vec_local[ballPos] = 'O';

			for (size_t y = 0; y < field.height; y++)
			{
				for (size_t x = 0; x < field.width; x++)
				{
					size_t pos = y * field.width + x;
					std::cout << vec_local[pos];
				}
				std::cout << '\n';
			}
		}
		size_t GetPusherPos_0()
		{
			return pusherPos_0;
		}
		ULL GetPBPos_0()
		{
			return PBPos_0;
		}
		PBData NumberOfPushesToGoal()
		{
			std::set<ULL> visited; visited.insert(PBPos_0);
			std::queue<PBData> queue; queue.push({ PBPos_0 });
			while (!queue.empty())
			{
				PBData cur_pbdata = queue.front(); queue.pop();
				for (ULL pbpos : GetNewPBPositions(cur_pbdata.PBPos))
				{
					if (visited.find(pbpos) == visited.end())
					{
						PBData new_pbdata = cur_pbdata;
						new_pbdata.n++;
						new_pbdata.path.push_back(pbpos);
						new_pbdata.PBPos = pbpos;
						if (size_t((pbpos << 32) >> 32) == goalPos)
						{
							return new_pbdata;
						}
						queue.push(new_pbdata);
						visited.insert(pbpos);
					}
				}
			}
			return { PBPos_0,-1,{} };
		}
	private:
		Field field;
		size_t ballPos_0;
		size_t pusherPos_0;
		ULL PBPos_0;
		const size_t goalPos;
	};
	class Solution {
	public:
		int minPushBox(std::vector<std::vector<char>>& grid)
		{
			Maze maze(grid);
			PBData endstate = maze.NumberOfPushesToGoal();
			return endstate.n;
		}
	};
	void RunExample()
	{
		//Maze maze("maze2.txt");
		std::vector<std::vector<char>> grid1 =
		{
			{'#', '#', '#', '#', '#', '#'},
			{'#', 'T', '#', '#', '#', '#'},
			{'#', '.', '.', 'B', '.', '#'},
			{'#', '.', '#', '#', '.', '#'},
			{'#', '.', '.', '.', 'S', '#'},
			{'#', '#', '#', '#', '#', '#'} };

		std::vector<std::vector<char>> grid2 =
		{ {'#', '#', '#', '#', '#', '#'},
		{'#', 'T', '#', '#', '#', '#'},
		{'#', '.', '.', 'B', '.', '#'},
		{'#', '#', '#', '#', '.', '#'},
		{'#', '.', '.', '.', 'S', '#'},
		{'#', '#', '#', '#', '#', '#'} };

		std::vector<std::vector<char>> grid3 =
		{ {'#', '#', '#', '#', '#', '#'},
		{'#', 'T', '.', '.', '#', '#'},
		{'#', '.', '#', 'B', '.', '#'},
		{'#', '.', '.', '.', '.', '#'},
		{'#', '.', '.', '.', 'S', '#'},
		{'#', '#', '#', '#', '#', '#'} };

		std::vector<std::vector<char>> grid4 =
		{ {'#', '#', '#', '#', '#', '#', '#'},
		{'#', 'S', '#', '.', 'B', 'T', '#'},
		{'#', '#', '#', '#', '#', '#', '#'} };

		Maze maze(grid1);
		maze.PrintPBPosOnMaze(maze.GetPBPos_0());


		//std::cout << "Reachable Pusher Neighbors:\n";
		//maze.PrintPositionsOnMaze(maze.GetAccessibleNeighbors(maze.GetPBPos_0(),maze.GetPusherPos_0()));
		//std::cout << "All Reachable Pusher Positions:\n";
		//maze.PrintPositionsOnMaze(maze.GetReachablePushPositions( maze.GetPBPos_0() ));
		//std::cout << "Reachable Ball Push Positions: \n";
		//maze.PrintPositionsOnMaze(maze.GetReachableBallPushPositions(maze.GetPBPos_0() ));
		//std::cout << "Possible new ball positions: \n";
		//maze.PrintPositionsOnMaze(maze.GetNewBallPositions(maze.GetPBPos_0() ));
		//
		//std::cout << "new PBPositions:\n";
		//std::vector<ULL> vec = maze.GetNewPBPositions(maze.GetPBPos_0());
		//for (ULL pbpos : vec)
		//{
		//	std::cout << "pusher:" << (pbpos >> 32) << ",ball:" << ((pbpos << 32) >> 32) << '\n';
		//}
		//for (ULL pbpos : vec)
		//{
		//	maze.PrintPBPosOnMaze(pbpos);
		//}
		std::cout << "b = Box Pusher\n";
		std::cout << "O = Box Position\n";
		std::cout << "X = Target box position\n\n";

		std::cout << "Minimum number of box pushes to goal: ";
		PBData endstate = maze.NumberOfPushesToGoal();
		if (endstate.n == -1) std::cout << "[No solution]";
		else
		{
			std::cout << endstate.n << '\n';
			std::cout << "Press [Enter] to show shortest path...";
		}
		std::cin.get();
		system("cls");

		for (ULL p : endstate.path)
		{
			maze.PrintPBPosOnMaze(p);
			std::cin.get();
			system("cls");
		}
	}
}
namespace LC1344 // Angle between hands of a clock
{
	class Solution {
	public:
		double angleClock(int hour, int minutes)
		{
			double phi_m = minutes / 60.0 * 360.0;
			double phi_h = (hour%12 + minutes / 60.0) / 12.0 * 360.0;
			double diff = std::abs(phi_m - phi_h);
			if (diff > 180.0) return 360.0-diff;
			else return diff;
			//return std::abs(phi_m - phi_h);
			//return std::abs(std::fmod(phi_m - phi_h+180.0 ,180.0f));

		}
	};
	void RunExample()
	{
		double ans;
		ans = Solution().angleClock(1, 57);  //76.5
		ans = Solution().angleClock(12, 30);  //165
		ans = Solution().angleClock(3, 30); //75
		ans = Solution().angleClock(8, 7); // 158.5
		ans = Solution().angleClock(3, 15);
		ans = Solution().angleClock(4, 50);
		ans = Solution().angleClock(12, 0);
		ans = Solution().angleClock(7, 45);

	}
}