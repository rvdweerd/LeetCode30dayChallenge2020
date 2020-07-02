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
#include <algorithm>
#include <numeric>
#include "Vec3.h"
#include "Vec2.h"

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
namespace LC84 // Largest rectangle in histogram
{
	class Solution {
	public:
		int largestRectangleArea(std::vector<int>& heights)
		{
			int max = 0;
			std::stack<std::pair<int, size_t>> stack;
			stack.push({ heights[0],0 });
			for (size_t i = 1; i < heights.size(); i++)
			{
				if (stack.empty() || heights[i] > stack.top().first)
				{
					stack.push({ heights[i],i });
				}
				else
				{
					size_t last = i;
					while (!stack.empty() && heights[i] < stack.top().first)
					{
						auto p = stack.top(); stack.pop();
						max = std::max(max, int(p.first * (i - p.second)));
						last = p.second;
						//std::cout << "i="<<i<< ", Popped: {" << p.first << "," << p.second << "}, max compare: " << int(p.first * (i - p.second)) << ", new max: " << max << "\n";
					}
					stack.push({ heights[i],last });
				}
			}
			//std::cout << "unwrapping\n";
			while (!stack.empty())
			{
				auto p = stack.top(); stack.pop();
				max = std::max(max, int(p.first * (heights.size() - p.second)));
				//std::cout << "Popped: {" << p.first << "," << p.second << "}, max compare: " << int(p.first * (heights.size() - p.second)) << ", new max: " << max << "\n";
			}
			return max;
		}
	};
	void RunExample()
	{
		std::vector<int> vec;
		int ans;

		vec = { 2,1,5,6,2,3 };
		ans = Solution().largestRectangleArea(vec);
	}
}
namespace LC85 // Maximal rectangle
{
	class Solution {
	private:
		int largestRectangleArea(std::vector<int>& heights)
		{
			int max = 0;
			std::stack<std::pair<int, size_t>> stack;
			stack.push({ heights[0],0 });
			for (size_t i = 1; i < heights.size(); i++)
			{
				if (stack.empty() || heights[i] > stack.top().first)
				{
					stack.push({ heights[i],i });
				}
				else
				{
					size_t last = i;
					while (!stack.empty() && heights[i] < stack.top().first)
					{
						auto p = stack.top(); stack.pop();
						max = std::max(max, int(p.first * (i - p.second)));
						last = p.second;
						//std::cout << "i="<<i<< ", Popped: {" << p.first << "," << p.second << "}, max compare: " << int(p.first * (i - p.second)) << ", new max: " << max << "\n";
					}
					stack.push({ heights[i],last });
				}
			}
			//std::cout << "unwrapping\n";
			while (!stack.empty())
			{
				auto p = stack.top(); stack.pop();
				max = std::max(max, int(p.first * (heights.size() - p.second)));
				//std::cout << "Popped: {" << p.first << "," << p.second << "}, max compare: " << int(p.first * (heights.size() - p.second)) << ", new max: " << max << "\n";
			}
			return max;
		}
	public:
		int maximalRectangle(std::vector<std::vector<char>>& matrix) 
		{
			int max = 0;
			//std::vector<std::vector<int>> histograms;
			std::vector<int> h(matrix[0].size(), 0);
			for (auto r : matrix)
			{
				for (size_t col = 0; col < r.size(); col++)
				{
					if (r[col] == '0')
					{
						h[col] = 0;
					}
					else
					{
						h[col]++;
					}
				}
				max = std::max(max, largestRectangleArea(h));
			}
			return max;
		}
	};
	void RunExample()
	{
		std::vector<std::vector<char>> matrix;
		int ans;

		matrix =
		{
			{'1', '0', '1', '0', '0'},
			{'1', '0', '1', '1', '1'},
			{'1', '1', '1', '1', '1'},
			{'1', '0', '0', '1', '0'}
		};
		ans = Solution().maximalRectangle(matrix);	
	}
}
namespace LC416 // Partition equal subset sum
{
	class Solution 
	{
	private:
		int maxRemain;
		const int maxElementValue = 100;
		const int maxArraySize = 200;
		bool CanEliminateRemainder(const std::vector<int>& nums, int index, int remainder, std::vector<std::vector<bool>>& cache,std::string path="")
		{
			//static std::unordered_set<long long> cache;
			//std::cout << "Call with [i=" << index << ", remainder=" << remainder << "], path: "<<path<<"\n";
			//if (cache.find( (index << 32) | remainder) != cache.end())
			if (remainder < 0 || remainder > maxRemain) return false;
			if (cache[index][remainder] == false)
			{
				return false;
			}
			if (remainder==0)
			{
				//std::cout << "\nWinning path: " << path<<"\n\n";
				return true;
			}

			if ((size_t)index < nums.size() - 1 )
			{
				if (remainder >= nums[(size_t)index])
				{
					if (CanEliminateRemainder(nums, index + 1, remainder - nums[(size_t)index], cache, path + '1')) return true;
					cache[index + 1][remainder - nums[(size_t)index]] = false;
				}
				if (CanEliminateRemainder(nums, index + 1, remainder, cache, path+'0')) return true;
				cache[index + 1][remainder] = false;
			}
			return false;
		}
	public:
		bool canPartition(const std::vector<int>& nums) 
		{
			int total = std::accumulate(nums.begin(), nums.end(), 0);
			if (total % 2 == 1) return false;
			std::vector<std::vector<bool>> cache(nums.size(), std::vector<bool>(maxElementValue * nums.size() / 2 + 1, true));
			maxRemain = nums.size() / 2 * maxElementValue;
			return CanEliminateRemainder(nums, 0, total / 2,cache);
		}
	};
	

	void RunExample()
	{
		std::vector<int> vec;
		bool ans;

		vec = { 1,5,11,5 };
		ans = Solution().canPartition(vec); // true

		vec = { 100,100,100,100,100,100,100,100 };
		ans = Solution().canPartition(vec); // true

		vec = { 3,3,3,4,5 };
		ans = Solution().canPartition(vec);  // true

		vec = { 28, 63, 95, 30, 39, 16, 36, 44, 37, 100, 61, 73, 32, 71, 100, 2, 37, 60, 23, 71, 53, 70, 69, 82, 97, 43, 16, 33, 29, 5, 97, 32, 29, 78, 93, 59, 37, 88, 89, 79, 75, 9, 74, 32, 81, 12, 34, 13, 16, 15, 16, 40, 90, 70, 17, 78, 54, 81, 18, 92, 75, 74, 59, 18, 66, 62, 55, 19, 2, 67, 30, 25, 64, 84, 25, 76, 98, 59, 74, 87, 5, 93, 97, 68, 20, 58, 55, 73, 74, 97, 49, 71, 42, 26, 8, 87, 99, 1, 16, 79 };
		ans = Solution().canPartition(vec); //true
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
namespace LC655 // Print Binary Tree
{
	/**
	* Definition for a binary tree node.*/
	struct TreeNode {
		int val;
		TreeNode* left;
		TreeNode* right;
		TreeNode() : val(0), left(nullptr), right(nullptr) {}
		TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
		TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
	};
	class Solution {
	private:
		struct Entry
		{
			int val;
			size_t d;
			std::vector<int> pos;
		};
		int l = 0, r = 0;
		size_t d = 0, maxDepth = 0;
		std::vector<Entry> entries;
		std::vector<int> path;
	private:
		void GetNodePositions(TreeNode* root)
		{
			if (root)
			{
				std::cout << root->val << ", d=" << d << ", l=" << l << ", r=" << r << "\n";
				entries.push_back({ root->val,d,path });
				d++; l++; path.push_back(-1);
				GetNodePositions(root->left);
				l--; r++; path.pop_back(); path.push_back(1);
				GetNodePositions(root->right);
				r--; d--; path.pop_back();
			}
			else
			{
				maxDepth = std::max(maxDepth, d - 1);
			}
		}
		std::vector<size_t> MakePaddingVector(size_t depth)
		{
			std::vector<size_t> vec_out;
			size_t max = 1;
			if (maxDepth > 1) max = (size_t)std::pow(2, maxDepth - 1);
			for (size_t i = 0; i < maxDepth; i++)
			{
				vec_out.push_back(max);
				max /= 2;
			}
			return vec_out;
		}
	public:
		std::vector<std::vector<std::string>> printTree(TreeNode* root)
		{
			GetNodePositions(root);
			std::vector<std::vector<std::string>> bstStringArray(maxDepth + 1, std::vector<std::string>((int)std::pow(2, maxDepth + 1) - 1, ""));
			std::vector<size_t> padding = MakePaddingVector(maxDepth);
			size_t midPoint = bstStringArray[0].size() / 2;
			for (auto e : entries)
			{
				size_t row = e.d;
				size_t col = midPoint;
				for (size_t i = 0; i < e.pos.size(); i++)
				{
					col += e.pos[i] * padding[i];
				}
				bstStringArray[row][col] = std::to_string(e.val);
			}
			return bstStringArray;
		}
	};

	void RunExample()
	{
		TreeNode* root = new TreeNode(32, nullptr, new TreeNode(30));
		root->right->left = new TreeNode(10, nullptr, new TreeNode(15));
		root->right->left->right->right = new TreeNode(45);
		auto ans = Solution().printTree(root);

		for (auto e : ans)
		{
			for (auto s : e)
			{
				if (s == "") std::cout << "  ";
				std::cout << s << ",";
			}
			std::cout << "\n";
		}

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
namespace LC797 // All paths from source to target
{
	class Solution {
	public:
		std::vector<std::vector<int>> allPaths;
		void Step(std::vector<std::vector<int>>& graph, int i, std::vector<int> path)
		{
			path.push_back(i);
			for (auto v : graph[i])
			{
				Step(graph, v, path);
			}
			if (i == graph.size() - 1) allPaths.push_back(path);
		}
		std::vector<std::vector<int>> allPathsSourceTarget(std::vector<std::vector<int>>& graph) 
		{
			Step(graph, 0, {});
			return allPaths;
		}
	};

	void RunExample()
	{
		std::vector<std::vector<int>> vec;
		std::vector<std::vector<int>> ans;

		vec = { {1, 2} ,{3},{3},{} };
		ans = Solution().allPathsSourceTarget(vec);
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
namespace LC912
{
	class Solution {
	public:
		std::vector<int> MergeSort(std::vector<int> arr)
		{
			std::vector<int> out(arr.size());
			if (arr.size() == 1) return arr;
			else
			{
				int m = arr.size() / 2;
				std::vector<int> sorted_left = MergeSort(std::vector<int>(arr.begin(), arr.begin() + m));
				std::vector<int> sorted_right = MergeSort(std::vector<int>(arr.begin() + m, arr.end()));
				for (size_t i = 0, j = 0; i < sorted_left.size() || j < sorted_right.size();)
				{
					if (i >= sorted_left.size())
					{
						out[i+j] = (sorted_right[j]);
						j++;
					}
					else if (j >= sorted_right.size())
					{
						out[i+j] = (sorted_left[i]);
						i++;
					}
					else if (sorted_left[i] > sorted_right[j])
					{
						out[i + j] = sorted_right[j];
						j++;
					}
					else
					{
						out[i + j] = sorted_left[i];
						i++;
					}
				}

			}
			return out;
		}
		std::vector<int> sortArray(std::vector<int>& nums) 
		{
			return MergeSort(nums);
		}
	};
	void RunExample()
	{
		//std::vector<int> vec = { 5,4,1,7,2,6,8,3 };
		std::vector<int> vec;
		std::vector<int> merged;
		
		vec = { 2,-2,2,-2,-1 };
		merged = Solution().sortArray(vec);

		vec = { 3,2,1 }; 
		merged = Solution().sortArray(vec);

		vec = { 0 };
		merged = Solution().sortArray(vec);

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
namespace Karatsuba
{
	class Solution
	{
	private:
		int nDigits(int n)
		{
			if (n < 10) return 1;
			else return 1 + nDigits(n / 10);
		}
	public:
		int KaratsubaMultiplication(int x, int y)
		{
			int n = nDigits(x);
			assert(n == nDigits(y));
			if (n == 1) return (x * y);
			std::string strX = std::to_string(x);
			std::string strA = strX.substr(0,n / 2);
			std::string strB = strX.substr(n/2);
			int a = std::stoi(strA);
			int b = std::stoi(strB);

			std::string strY = std::to_string(y);
			std::string strC = strY.substr(0, n / 2);
			std::string strD = strY.substr(n / 2);
			int c = std::stoi(strC);
			int d = std::stoi(strD);

			std::string strPn = "1" + std::string( n,'0' );
			int Pn = std::stoi(strPn);
			std::string strPn_2 = "1" + std::string( n / 2, '0');
			int Pn_2 = std::stoi(strPn_2);

			return (Pn * KaratsubaMultiplication(a, c) + Pn_2 * (KaratsubaMultiplication(a, d) + KaratsubaMultiplication(b, c)) + KaratsubaMultiplication(b, d));
		}
	};
	void RunExample()
	{
		int x = 5678;
		int y = 1234;
		int z = Solution().KaratsubaMultiplication(x, y);
	}
}
namespace Knapsack
{
	class Solution
	{
	public:
		int Pack(std::vector<std::vector<int>>& inventory, int index, int capacity, int value, std::string path)
		{
			if (index == inventory.size())
			{
				std::cout << "Value: " << value << ", Path: " << path <<"\n";
				return value;
			}
			if (capacity-inventory[index][0] >= 0)
			{
				return std::max(
					Pack(inventory, index + 1, capacity - inventory[index][0], value + inventory[index][1], path + '1'),
					Pack(inventory, index + 1, capacity , value , path + '0')
				);
			}
			return Pack(inventory, index + 1, capacity, value, path + '0');

		}
		int maxValueRecursive(std::vector<std::vector<int>>& inventory, int S)
		{
			std::cout << "\nRecursive outcomes (max values) and paths:\n";
			return Pack(inventory, 0, S, 0,"");
		}
		int maxValueDP(std::vector<std::vector<int>>& inventory, int S)
		{
			// Create DP table, initialized with 0s
			std::vector<std::vector<int>> DP(inventory.size(), std::vector<int>(S + 1, 0));
			// Iterate through table and fill with local maxima
			for (int i = 0; i < (int)inventory.size(); i++) // DP table axis 1: number of items to choose from
			{
				for (int j = 1; j <= S ; j++) // DP table axis 2: max allowable weight
				{
					if (j >= inventory[i][0]) // current item can fit, see if adding it would lead to better outcome
					{
						if (i == 0) DP[i][j] = inventory[i][1];
						else DP[i][j] = std::max(DP[i-1][j] , inventory[i][1] + DP[i-1][j-inventory[i][0]]);
					}
					else // current item does not fit, move on without it
					{
						if (i == 0) DP[i][j] = 0; 
						else DP[i][j] = DP[i - 1][j];
					}
				}
			}
			// Loop back through the DP table to build the list of items in the optimal knapsack
			std::vector<int> itemsIncluded;
			int j = S;
			for (int i = inventory.size() - 1; i > 0; i--)
			{
				if (DP[i - 1][j] < DP[i][j])
				{
					itemsIncluded.push_back(i);
					j = j - inventory[i][0];
				}
			}
			if (itemsIncluded.size()==0) itemsIncluded.push_back(0);
			else
			{
				int i = itemsIncluded.back();
				if (j-inventory[i][0] >=0 && DP[0][j-inventory[i][0]] > 0) itemsIncluded.push_back(0);
			}
			// Present the results
			std::cout << "\nInventory:\n";
			int i = 0;
			for (auto v : inventory)
			{
				std::cout << "i=" << i++ << ", s_i=" << v[0] << ", v_i=" << v[1] << "\n";
			}
			std::cout << "Picking items: ";
			for (auto v : itemsIncluded)
			{
				std::cout << v << ", ";
			}
			std::cout << "\nYield the optimal set with Value: " << DP[inventory.size() - 1][S]<<"\n" ;
			// Return max
			return DP[inventory.size()-1][S];
		}
	};
	void RunExample()
	{
		std::vector<std::vector<int>> vec;
		int ans;

		// Test recursive solution
		vec = { {2,1},{5,2},{10,5},{3,1} }; // {size,value}
		ans = Solution().maxValueRecursive(vec, 10); // max size. ans: 5
		
		vec = { {1,1},{3,4},{4,5},{5,7} }; // {size,value}
		ans = Solution().maxValueRecursive(vec, 7); // max size/ ans: 9

		// Test DP solution
		vec = { {2,1},{5,2},{10,5},{3,1} }; // {size,value}
		ans = Solution().maxValueDP(vec, 10); // max size. ans: 5

		vec = { {1,1},{3,4},{4,5},{5,7} }; // {size,value}
		ans = Solution().maxValueDP(vec, 7); // max size/ ans: 9


	}
}
namespace TriangleIntersect
	//	This function calculates intersection points (vectors in R3) of two triangles (each defined by 3 vertices in R3)
	//	Algorithm implmemented based on paper "A Fast Triangle-Triangle Intersection Test" by Tomas Moeller
	//
{
	template <typename T> int sgn(T val) {
		return (T(0) < val) - (val < T(0));
	}
	std::pair<Vec3,Vec3> TrianglesIntersect(Vec3& v1_0, Vec3& v1_1, Vec3& v1_2, const Vec3& v2_0, const Vec3& v2_1, const Vec3& v2_2)
	{
		// Plane equation for Plane2
		Vec3 N2 = (v2_1 - v2_0) % (v2_2 - v2_0);
		//N2 /= N2.Len();
		float d2 = -N2 * v2_0;

		// Plane equation for Plane1
		Vec3 N1 = (v1_1 - v1_0) % (v1_2 - v1_0);
		//N1 /= N1.Len();
		float d1 = -N1 * v1_0;

		// signed distances from T1 vertices to Plane2
		float d_v1_0 = N2 * v1_0 + d2;
		float d_v1_1 = N2 * v1_1 + d2;
		float d_v1_2 = N2 * v1_2 + d2;
		
		// Test: triangle 1 is coplanar
		assert(!(d_v1_0 == 0 && d_v1_1 == 0 && d_v1_2 == 0));

		// Test: triangle 1 is not fully on 1 side of P2
		bool NoT1VertexOnPlane2 = (d_v1_0 != 0 && d_v1_1 != 0 && d_v1_2 != 0);
		bool T1DistancesHaveSameSign = (d_v1_0 > 0 && d_v1_1 > 0 && d_v1_2 > 0) || (d_v1_0 < 0 && d_v1_1 < 0 && d_v1_2 < 0);
		assert(!(NoT1VertexOnPlane2 && T1DistancesHaveSameSign));
		
		// Ensure that v1_0 is solitary (two other vertices are on other side of T2)
		if (sgn(d_v1_0) == sgn(d_v1_1))
		{
			std::swap(d_v1_0, d_v1_2);
			//std::swap(v1_0, v1_2); NEED TO IMPLEMENT MOVE CONSTRUCTOR FOR Vec3 FOR THIS TO WORK
			Vec3 tmp = v1_0;
			v1_0 = v1_2;
			v1_2 = tmp;
			
			// Plane equation for Plane2
			N2 = (v2_1 - v2_0) % (v2_2 - v2_0);
			//N2 /= N2.Len();
			d2 = -N2 * v2_0;
			// Plane equation for Plane1
			N1 = (v1_1 - v1_0) % (v1_2 - v1_0);
			//N1 /= N1.Len();
			d1 = -N1 * v1_0;
			// signed distances from T1 vertices to Plane2
			//d_v1_0 = N2 * v1_0 + d2;
			//d_v1_1 = N2 * v1_1 + d2;
			//d_v1_2 = N2 * v1_2 + d2;
		}
		else if (sgn(d_v1_0) == sgn(d_v1_2))
		{
			std::swap(d_v1_0, d_v1_1);
			Vec3 tmp = v1_0;
			v1_0 = v1_1;
			v1_1 = tmp;

			// Plane equation for Plane2
			N2 = (v2_1 - v2_0) % (v2_2 - v2_0);
			//N2 /= N2.Len();
			d2 = -N2 * v2_0;
			// Plane equation for Plane1
			N1 = (v1_1 - v1_0) % (v1_2 - v1_0);
			//N1 /= N1.Len();
			d1 = -N1 * v1_0;
			// signed distances from T1 vertices to Plane2
			//d_v1_0 = N2 * v1_0 + d2;
			//d_v1_1 = N2 * v1_1 + d2;
			//d_v1_2 = N2 * v1_2 + d2;
		}

		// Intersection line L = O + t*D (O = any point on line, D = direction), this represents the nullspace Ax=0)
		Vec3 D = N1 % N2;
		D /= D.Len();
		// Particular point on line (Ax=b, particular solution)
		// Find largest entry of D
		Vec3 O;
		if (abs(D.x) >= abs(D.y) && abs(D.x) >= abs(D.z)) // D.x largest component
		{
			float a = N1.y, b = N1.z;
			float c = N2.y, d = N2.z;
			float det = 1 / (a * d - b * c);
			float O_y = det * (d * (-d1) - b * (-d2));
			float O_z = det * (-c * (-d1) + a * (-d2));
			O = { 0,O_y,O_z };
		}
		else if (abs(D.y) >= abs(D.x) && abs(D.y) >= abs(D.z)) // D.y largest component
		{
			float a = N1.x, b = N1.z;
			float c = N2.x, d = N2.z;
			float det = 1 / (a * d - b * c);
			float O_x = det * (d * (-d1) - b * (-d2));
			float O_z = det * (-c * (-d1) + a * (-d2));
			O = { O_x,0,O_z };
		} 
		else // D.z largest component
		{
			float a = N1.x, b = N1.y;
			float c = N2.x, d = N2.y;
			float det = 1 / (a * d - b * c);
			float O_x = det * (d * (-d1) - b * (-d2));
			float O_y = det * (-c * (-d1) + a * (-d2));
			O = { O_x,O_y,0 };
		}
		//assert(N1 * (O + D * 20) == -d1);
		//assert(N2 * (O + D * 10) == -d2);
		float test2_1 = N2 * (O + D * 10);
		float test2_2 = test2_1 + d2;
		if (test2_2 != -d2)
		{
			int k = 0;
		}

		// Project vertices of T1 onto Intersection Line L
		Vec3 p_v1_0 = D * (D * (v1_0 - O)) / (D * D) + O;
		Vec3 p_v1_1 = D * (D * (v1_1 - O)) / (D * D) + O;
		Vec3 p_v1_2 = D * (D * (v1_2 - O)) / (D * D) + O;

		// Interpolation to find t1
		float S = abs((p_v1_1 - p_v1_0).Len());
		float a = abs((p_v1_0 - v1_0).Len());
		float b = abs((p_v1_1 - v1_1).Len());
		float p = a * S / (b + a);
		Vec3 t1 = p_v1_1 + (p_v1_0 - p_v1_1)*p;

		// Interpolation to find t2
		S = abs((p_v1_2 - p_v1_0).Len());
		a = abs((p_v1_0 - v1_0).Len());
		b = abs((p_v1_2 - v1_2).Len());
		p = a * S / (b + a);
		Vec3 t2 = p_v1_2 + (p_v1_0 - p_v1_2) * p;
		return { t1,t2 };
	}
	void RunExample()
	{
		//Vec3 v1_0 = { -1,1,0 }, v1_1 = { 2,-2,-1 }, v1_2 = { 2,-2,1 }; // Triangle 1
		//Vec3 v2_0 = { 1,1,-1 }, v2_1 = { 1,-2,0 }, v2_2 = { 1,1,1 };  // Triangle 2
		Vec3 v1_0 = { 0.5f,-0.5f,2.0f }, v1_1 = { -0.5f,-0.5f,2.0f }, v1_2 = { 0.0f,0.5f,2.0f }; // Triangle 1
		Vec3 v2_0 = { 0.35f,-0.215f,2.57f }, v2_1 = { -0.34f,-0.615f,2.0f }, v2_2 = { 0.0f,0.415f,1.715f };  // Triangle 2
		
		std::pair<Vec3,Vec3> ans = TrianglesIntersect(v1_1, v1_0, v1_2, v2_0, v2_1, v2_2);
		ans = TrianglesIntersect(v1_0, v1_1, v1_2, v2_0, v2_1, v2_2);
		ans = TrianglesIntersect(v1_0, v1_1, v1_2, v2_0, v2_2, v2_1);
		ans = TrianglesIntersect(v1_0, v1_1, v1_2, v2_2, v2_1, v2_0);
		ans = TrianglesIntersect(v1_2, v1_1, v1_0, v2_2, v2_1, v2_0);


	}
}