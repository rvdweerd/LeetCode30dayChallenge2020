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


namespace LC773 // Sliding puzzle
{
	class Solution
	{
		size_t m = 2;
		size_t n = 3;
		std::vector<std::string> GetMoves(std::string& brd)
		{
			char pos0 = brd.back();
			std::vector<std::string> outVec;
			switch (pos0)
			{
			case 0:
				//outVec.resize(2, brd);
				outVec.push_back(brd);
				outVec.push_back(brd);
				std::swap(outVec[0][0], outVec[0][1]);
				std::swap(outVec[1][0], outVec[1][3]);
				outVec[0].pop_back(); outVec[0].push_back(1);
				outVec[1].pop_back(); outVec[1].push_back(3);
				break;
			case 1:
				//outVec.resize(3, brd);
				outVec.push_back(brd);
				outVec.push_back(brd);
				outVec.push_back(brd);
				std::swap(outVec[0][1], outVec[0][0]);
				std::swap(outVec[1][1], outVec[1][2]);
				std::swap(outVec[2][1], outVec[2][4]); 
				outVec[0].pop_back(); outVec[0].push_back(0);
				outVec[1].pop_back(); outVec[1].push_back(2); 
				outVec[2].pop_back(); outVec[2].push_back(4);
				break;
			case 2:
				//outVec.resize(2, brd);
				outVec.push_back(brd);
				outVec.push_back(brd);
				std::swap(outVec[0][2], outVec[0][1]);
				std::swap(outVec[1][2], outVec[1][5]);
				outVec[0].pop_back(); outVec[0].push_back(1);
				outVec[1].pop_back(); outVec[1].push_back(5);
				break;
			case 3:
				//outVec.resize(2, brd);
				outVec.push_back(brd);
				outVec.push_back(brd);
				std::swap(outVec[0][3], outVec[0][0]);
				std::swap(outVec[1][3], outVec[1][4]);
				outVec[0].pop_back(); outVec[0].push_back(0);
				outVec[1].pop_back(); outVec[1].push_back(4);
				break;
			case 4:
				//outVec.resize(3, brd);
				outVec.push_back(brd);
				outVec.push_back(brd);
				outVec.push_back(brd);
				std::swap(outVec[0][4], outVec[0][1]);
				std::swap(outVec[1][4], outVec[1][3]);
				std::swap(outVec[2][4], outVec[2][5]);
				outVec[0].pop_back(); outVec[0].push_back(1);
				outVec[1].pop_back(); outVec[1].push_back(3);
				outVec[2].pop_back(); outVec[2].push_back(5);
				break;
			case 5:
				//outVec.resize(2, brd);
				outVec.push_back(brd);
				outVec.push_back(brd);
				std::swap(outVec[0][5], outVec[0][2]);
				std::swap(outVec[1][5], outVec[1][4]);
				outVec[0].pop_back(); outVec[0].push_back(2);
				outVec[1].pop_back(); outVec[1].push_back(4);
				break;
			default:
				assert(false);
			}
			return std::move(outVec);
		}
	public:
		int slidingPuzzle(std::vector<std::vector<int>>& board) 
		{
			std::string brd;
			char pos0=255;
			for (size_t row = 0; row<board.size();row++)
			{
				for (size_t col=0; col<board[0].size();col++)
				{
					brd.append(1,board[row][col] + 'a');
					if (board[row][col] == 0) pos0 = char(row * n + col);
				}
			}
			brd.append(1, pos0);
			struct Pos
			{
				std::string brd;
				int counter=0;
			};
			std::unordered_set<std::string> visited;
			std::queue<Pos> queue;
			queue.push({ brd,0 });
			while (!queue.empty())
			{
				Pos curPos = queue.front(); queue.pop();
				visited.insert(curPos.brd);
				if (curPos.brd.back() == 5) 
				{ 
					if (curPos.brd == ("bcdefa\x5")) return curPos.counter; 
				}
				for (std::string newBrd : GetMoves(curPos.brd))
				{
					if (visited.find(newBrd) == visited.end())
					{
						queue.push({ newBrd,curPos.counter+1 });
					}
				}
			}
			return -1;
		}
	};
	void RunExample()
	{
		std::vector<std::vector<int>> board;
		int ans;

		board = { {1,2,3},{4,0,5} };
		ans = Solution().slidingPuzzle(board); // 1
		
		board = { {1,2,3},{5,4,0} };
		ans = Solution().slidingPuzzle(board); // -1

		board = { {4,1,2},{5,0,3} };
		ans = Solution().slidingPuzzle(board); // 5

		board = { {3,2,4},{1,5,} };
		ans = Solution().slidingPuzzle(board); // 14

	}
}

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
namespace LC133 // Clone Graph
{

	class Node {
	public:
		int val;
		std::vector<Node*> neighbors;

		Node() {
			val = 0;
			neighbors = std::vector<Node*>();
		}

		Node(int _val) {
			val = _val;
			neighbors = std::vector<Node*>();
		}

		Node(int _val, std::vector<Node*> _neighbors) {
			val = _val;
			neighbors = _neighbors;
		}
	};

	class Solution {
	public:
		std::set<Node*> visited;
		std::map<int,Node*> created;
		void traverse(Node* rt, Node* rt_cpy)
		{
			if (visited.find(rt) == visited.end())
			{
				visited.insert(rt);
				for (Node* n : rt->neighbors)
				{
					if (created.find(n->val) == created.end())
					{
						rt_cpy->neighbors.push_back(new Node(n->val));
						created[n->val] = rt_cpy->neighbors.back();
					}
					else
					{
						rt_cpy->neighbors.push_back(created[n->val]);
					}
					traverse(n, rt_cpy->neighbors.back());
				}
			}
		}

		Node* cloneGraph(Node* node) 
		{
			if (node == nullptr) return nullptr;
			Node* new_root = new Node(node->val);
			Node* new_root_cpy = new_root;
			created[node->val] = new_root_cpy;
			traverse(node, new_root_cpy);
			return new_root;
		}
	};
	void RunExample()
	{
		std::map<int, Node*> nodeMap;
		nodeMap[1] = new Node(1);
		nodeMap[2] = new Node(2);
		nodeMap[3] = new Node(3);
		nodeMap[4] = new Node(4);
		
		Node* root = nodeMap[1]; root->neighbors = {nodeMap[2],nodeMap[4]};
		nodeMap[2]->neighbors = { nodeMap[1],nodeMap[3] };
		nodeMap[3]->neighbors = { nodeMap[2],nodeMap[4] };
		nodeMap[4]->neighbors = { nodeMap[1],nodeMap[3] };		
		Node* root_cpy = Solution().cloneGraph(root);
	}
}
namespace LC1462 // Course Schedule IV
{
	class Solution {
	private:
		
	public:
		std::vector<bool> checkIfPrerequisite(int n, std::vector<std::vector<int>>& prerequisites, std::vector<std::vector<int>>& queries) 
		{
			// Initialize graph
			std::vector<std::vector<int>> nodeMap(n);
			for (auto& p : prerequisites)
			{
				nodeMap[p[0]].push_back(p[1]);
			}

			std::vector<std::vector<int>> isReachable = std::vector<std::vector<int>>(n,std::vector<int>(n,0));
			std::queue<int> queue;
			for (int i = 0; i < n; i++)
			{
				queue.push(i);
				while (!queue.empty())
				{
					int cur = queue.front(); queue.pop();
					for (int neigh : nodeMap[cur])
					{
						if (!isReachable[i][neigh])
						{
							isReachable[i][neigh] = 1;
							queue.push(neigh);
						}
					}
				}
			}
			std::vector<bool> retVec;
			for (auto& p : queries)
			{
				retVec.push_back((isReachable[p[0]][p[1]]));
			}
			return std::move(retVec);
		}
	};
	void RunExample()
	{
		std::vector<std::vector<int>> prereqs;
		std::vector<std::vector<int>> queries;
		int n;
		std::vector<bool> ans;

		prereqs = { {1,2},{1,0},{2,0} };
		queries = { {1,0},{1,2} };
		n = 3;
		ans = Solution().checkIfPrerequisite(n, prereqs, queries); // T,T

		prereqs = {{0, 1}, {1, 2}, {2, 3}, {3, 4}};
		queries = {{0, 4}, {4, 0}, {1, 3}, {3, 0}};
		n = 5;
		ans = Solution().checkIfPrerequisite(n, prereqs, queries); // T,F,T,F

		prereqs = { {3, 4}, {2, 3}, {1, 2}, {0, 1} };
		queries = { {0, 4}, {4, 0}, {1, 3}, {3, 0} };
		n = 5;
		ans = Solution().checkIfPrerequisite(n, prereqs, queries); // T,F,T,F

		prereqs = {{4, 3}, {4, 1}, {4, 0}, {3, 2}, {3, 1}, {3, 0}, {2, 1}, {2, 0}, {1, 0}};
		queries = { {1,4},{4,2},{0,1},{4,0},{0,2},{1,3},{0,1} };
		n = 5;
		ans = Solution().checkIfPrerequisite(n, prereqs, queries); // F,T,F,T,F,F,F

		prereqs = { {1,0} };
		queries = { {0,1},{1,0} };
		n = 2;
		ans = Solution().checkIfPrerequisite(n, prereqs, queries); // F,T

		prereqs = {};
		queries = { {1,0},{0,1} };
		n = 2;
		ans = Solution().checkIfPrerequisite(n, prereqs, queries); // F,F


		prereqs = { {1,0},{2,0} };
		queries = { {0,1},{2,0} };
		n = 3;
		ans = Solution().checkIfPrerequisite(n, prereqs, queries); // F,T


		prereqs = {{15, 12}, {15, 48}, {15, 25}, {15, 14}, {15, 35}, {15, 4}, {15, 31}, {15, 19}, {15, 26}, {15, 27}, {15, 30}, {15, 47}, {15, 29}, {15, 24}, {15, 37}, {15, 42}, {15, 16}, {15, 0}, {15, 13}, {15, 49}, {15, 22}, {15, 36}, {15, 10}, {15, 3}, {15, 21}, {15, 20}, {15, 6}, {15, 40}, {15, 34}, {15, 32}, {15, 38}, {15, 7}, {15, 1}, {15, 43}, {15, 5}, {15, 11}, {15, 23}, {15, 8}, {15, 39}, {15, 28}, {15, 33}, {15, 18}, {15, 46}, {15, 9}, {15, 41}, {15, 45}, {15, 44}, {15, 2}, {12, 48}, {12, 14}, {12, 35}, {12, 4}, {12, 31}, {12, 19}, {12, 26}, {12, 27}, {12, 30}, {12, 47}, {12, 29}, {12, 24}, {12, 37}, {12, 42}, {12, 16}, {12, 0}, {12, 13}, {12, 49}, {12, 22}, {12, 36}, {12, 10}, {12, 3}, {12, 21}, {12, 20}, {12, 6}, {12, 40}, {12, 34}, {12, 7}, {12, 1}, {12, 43}, {12, 17}, {12, 5}, {12, 11}, {12, 23}, {12, 8}, {12, 39}, {12, 28}, {12, 33}, {12, 18}, {12, 46}, {12, 9}, {12, 41}, {12, 45}, {12, 44}, {12, 2}, {48, 25}, {48, 14}, {48, 35}, {48, 31}, {48, 19}, {48, 26}, {48, 27}, {48, 30}, {48, 47}, {48, 24}, {48, 37}, {48, 42}, {48, 16}, {48, 0}, {48, 13}, {48, 36}, {48, 10}, {48, 3}, {48, 21}, {48, 20}, {48, 6}, {48, 40}, {48, 34}, {48, 32}, {48, 38}, {48, 7}, {48, 1}, {48, 43}, {48, 17}, {48, 5}, {48, 11}, {48, 23}, {48, 8}, {48, 39}, {48, 28}, {48, 33}, {48, 18}, {48, 41}, {48, 45}, {48, 44}, {48, 2}, {25, 14}, {25, 35}, {25, 4}, {25, 31}, {25, 19}, {25, 26}, {25, 47}, {25, 29}, {25, 24}, {25, 42}, {25, 16}, {25, 0}, {25, 13}, {25, 49}, {25, 22}, {25, 36}, {25, 10}, {25, 3}, {25, 21}, {25, 20}, {25, 6}, {25, 40}, {25, 34}, {25, 32}, {25, 38}, {25, 7}, {25, 1}, {25, 43}, {25, 17}, {25, 5}, {25, 11}, {25, 23}, {25, 8}, {25, 39}, {25, 28}, {25, 33}, {25, 18}, {25, 9}, {25, 41}, {25, 45}, {25, 44}, {25, 2}, {14, 35}, {14, 4}, {14, 31}, {14, 19}, {14, 26}, {14, 27}, {14, 30}, {14, 29}, {14, 24}, {14, 37}, {14, 42}, {14, 16}, {14, 0}, {14, 13}, {14, 49}, {14, 36}, {14, 10}, {14, 3}, {14, 21}, {14, 20}, {14, 6}, {14, 40}, {14, 34}, {14, 32}, {14, 38}, {14, 7}, {14, 1}, {14, 43}, {14, 17}, {14, 5}, {14, 11}, {14, 23}, {14, 8}, {14, 39}, {14, 28}, {14, 33}, {14, 18}, {14, 46}, {14, 9}, {14, 41}, {14, 45}, {14, 44}, {14, 2}, {35, 4}, {35, 31}, {35, 19}, {35, 26}, {35, 27}, {35, 30}, {35, 47}, {35, 29}, {35, 24}, {35, 37}, {35, 42}, {35, 16}, {35, 0}, {35, 13}, {35, 49}, {35, 22}, {35, 36}, {35, 10}, {35, 3}, {35, 21}, {35, 20}, {35, 6}, {35, 40}, {35, 32}, {35, 38}, {35, 7}, {35, 1}, {35, 43}, {35, 17}, {35, 5}, {35, 11}, {35, 23}, {35, 8}, {35, 39}, {35, 28}, {35, 33}, {35, 18}, {35, 46}, {35, 9}, {35, 41}, {35, 45}, {35, 44}, {35, 2}, {4, 31}, {4, 19}, {4, 26}, {4, 27}, {4, 47}, {4, 29}, {4, 24}, {4, 37}, {4, 42}, {4, 16}, {4, 0}, {4, 13}, {4, 49}, {4, 22}, {4, 36}, {4, 10}, {4, 3}, {4, 21}, {4, 20}, {4, 6}, {4, 40}, {4, 34}, {4, 32}, {4, 7}, {4, 1}, {4, 43}, {4, 17}, {4, 5}, {4, 11}, {4, 23}, {4, 8}, {4, 39}, {4, 28}, {4, 33}, {4, 18}, {4, 46}, {4, 9}, {4, 41}, {4, 45}, {4, 44}, {4, 2}, {31, 19}, {31, 26}, {31, 27}, {31, 30}, {31, 47}, {31, 29}, {31, 24}, {31, 37}, {31, 42}, {31, 16}, {31, 0}, {31, 13}, {31, 49}, {31, 22}, {31, 36}, {31, 10}, {31, 3}, {31, 21}, {31, 20}, {31, 6}, {31, 40}, {31, 34}, {31, 32}, {31, 38}, {31, 7}, {31, 43}, {31, 17}, {31, 11}, {31, 23}, {31, 8}, {31, 39}, {31, 28}, {31, 33}, {31, 18}, {31, 46}, {31, 9}, {31, 41}, {31, 45}, {31, 44}, {31, 2}, {19, 26}, {19, 27}, {19, 30}, {19, 47}, {19, 24}, {19, 37}, {19, 42}, {19, 16}, {19, 0}, {19, 13}, {19, 49}, {19, 22}, {19, 36}, {19, 10}, {19, 3}, {19, 21}, {19, 20}, {19, 6}, {19, 40}, {19, 34}, {19, 32}, {19, 38}, {19, 7}, {19, 17}, {19, 5}, {19, 11}, {19, 23}, {19, 8}, {19, 39}, {19, 28}, {19, 33}, {19, 18}, {19, 46}, {19, 9}, {19, 41}, {19, 45}, {19, 44}, {19, 2}, {26, 27}, {26, 30}, {26, 47}, {26, 29}, {26, 24}, {26, 37}, {26, 42}, {26, 16}, {26, 0}, {26, 13}, {26, 49}, {26, 22}, {26, 36}, {26, 10}, {26, 3}, {26, 21}, {26, 20}, {26, 40}, {26, 34}, {26, 32}, {26, 38}, {26, 7}, {26, 1}, {26, 43}, {26, 17}, {26, 5}, {26, 11}, {26, 23}, {26, 8}, {26, 39}, {26, 28}, {26, 33}, {26, 18}, {26, 46}, {26, 9}, {26, 41}, {26, 45}, {26, 44}, {26, 2}, {27, 30}, {27, 47}, {27, 29}, {27, 37}, {27, 42}, {27, 16}, {27, 0}, {27, 13}, {27, 49}, {27, 22}, {27, 36}, {27, 10}, {27, 3}, {27, 21}, {27, 20}, {27, 40}, {27, 34}, {27, 32}, {27, 38}, {27, 7}, {27, 1}, {27, 43}, {27, 17}, {27, 5}, {27, 11}, {27, 23}, {27, 8}, {27, 39}, {27, 28}, {27, 33}, {27, 18}, {27, 46}, {27, 9}, {27, 41}, {27, 45}, {27, 44}, {27, 2}, {30, 24}, {30, 37}, {30, 42}, {30, 16}, {30, 0}, {30, 13}, {30, 49}, {30, 22}, {30, 10}, {30, 3}, {30, 21}, {30, 20}, {30, 6}, {30, 34}, {30, 32}, {30, 38}, {30, 7}, {30, 1}, {30, 17}, {30, 11}, {30, 23}, {30, 8}, {30, 39}, {30, 28}, {30, 33}, {30, 18}, {30, 9}, {30, 41}, {30, 44}, {30, 2}, {47, 29}, {47, 24}, {47, 42}, {47, 16}, {47, 0}, {47, 13}, {47, 49}, {47, 22}, {47, 10}, {47, 3}, {47, 21}, {47, 20}, {47, 6}, {47, 40}, {47, 34}, {47, 32}, {47, 38}, {47, 7}, {47, 1}, {47, 43}, {47, 17}, {47, 5}, {47, 11}, {47, 23}, {47, 8}, {47, 39}, {47, 33}, {47, 18}, {47, 46}, {47, 9}, {47, 41}, {47, 45}, {47, 44}, {29, 24}, {29, 37}, {29, 42}, {29, 16}, {29, 0}, {29, 13}, {29, 49}, {29, 22}, {29, 36}, {29, 10}, {29, 3}, {29, 21}, {29, 20}, {29, 6}, {29, 40}, {29, 34}, {29, 38}, {29, 7}, {29, 1}, {29, 43}, {29, 17}, {29, 5}, {29, 11}, {29, 23}, {29, 8}, {29, 39}, {29, 28}, {29, 33}, {29, 18}, {29, 46}, {29, 9}, {29, 41}, {29, 45}, {29, 44}, {29, 2}, {24, 37}, {24, 42}, {24, 16}, {24, 0}, {24, 13}, {24, 49}, {24, 22}, {24, 36}, {24, 10}, {24, 3}, {24, 21}, {24, 20}, {24, 6}, {24, 40}, {24, 34}, {24, 32}, {24, 38}, {24, 7}, {24, 1}, {24, 43}, {24, 17}, {24, 5}, {24, 11}, {24, 23}, {24, 8}, {24, 39}, {24, 28}, {24, 33}, {24, 18}, {24, 46}, {24, 9}, {24, 41}, {24, 45}, {24, 2}, {37, 42}, {37, 16}, {37, 0}, {37, 13}, {37, 49}, {37, 22}, {37, 36}, {37, 10}, {37, 3}, {37, 21}, {37, 20}, {37, 6}, {37, 40}, {37, 34}, {37, 32}, {37, 38}, {37, 7}, {37, 1}, {37, 43}, {37, 17}, {37, 5}, {37, 11}, {37, 23}, {37, 8}, {37, 39}, {37, 28}, {37, 33}, {37, 18}, {37, 9}, {37, 41}, {37, 45}, {37, 44}, {37, 2}, {42, 16}, {42, 0}, {42, 13}, {42, 49}, {42, 22}, {42, 36}, {42, 10}, {42, 3}, {42, 21}, {42, 20}, {42, 6}, {42, 40}, {42, 34}, {42, 32}, {42, 38}, {42, 7}, {42, 1}, {42, 43}, {42, 17}, {42, 5}, {42, 23}, {42, 8}, {42, 39}, {42, 28}, {42, 33}, {42, 18}, {42, 46}, {42, 9}, {42, 41}, {42, 45}, {42, 44}, {42, 2}, {16, 0}, {16, 13}, {16, 49}, {16, 22}, {16, 36}, {16, 10}, {16, 3}, {16, 21}, {16, 20}, {16, 6}, {16, 40}, {16, 32}, {16, 38}, {16, 7}, {16, 1}, {16, 43}, {16, 17}, {16, 5}, {16, 11}, {16, 23}, {16, 8}, {16, 39}, {16, 28}, {16, 33}, {16, 18}, {16, 46}, {16, 9}, {16, 41}, {16, 45}, {16, 44}, {16, 2}, {0, 13}, {0, 49}, {0, 22}, {0, 36}, {0, 10}, {0, 3}, {0, 21}, {0, 6}, {0, 40}, {0, 32}, {0, 7}, {0, 1}, {0, 43}, {0, 17}, {0, 5}, {0, 11}, {0, 23}, {0, 8}, {0, 39}, {0, 28}, {0, 33}, {0, 18}, {0, 46}, {0, 9}, {0, 41}, {0, 45}, {0, 44}, {0, 2}, {13, 49}, {13, 22}, {13, 36}, {13, 10}, {13, 3}, {13, 21}, {13, 6}, {13, 40}, {13, 34}, {13, 32}, {13, 38}, {13, 7}, {13, 1}, {13, 17}, {13, 5}, {13, 11}, {13, 23}, {13, 8}, {13, 39}, {13, 28}, {13, 33}, {13, 18}, {13, 46}, {13, 9}, {13, 41}, {13, 45}, {13, 44}, {13, 2}, {49, 22}, {49, 36}, {49, 10}, {49, 3}, {49, 21}, {49, 20}, {49, 6}, {49, 40}, {49, 34}, {49, 32}, {49, 38}, {49, 7}, {49, 43}, {49, 5}, {49, 11}, {49, 23}, {49, 8}, {49, 39}, {49, 28}, {49, 33}, {49, 18}, {49, 46}, {49, 9}, {49, 41}, {49, 45}, {49, 44}, {49, 2}, {22, 36}, {22, 10}, {22, 3}, {22, 21}, {22, 20}, {22, 6}, {22, 40}, {22, 34}, {22, 32}, {22, 38}, {22, 7}, {22, 43}, {22, 17}, {22, 5}, {22, 11}, {22, 23}, {22, 8}, {22, 39}, {22, 28}, {22, 33}, {22, 18}, {22, 46}, {22, 9}, {22, 45}, {22, 44}, {22, 2}, {36, 10}, {36, 3}, {36, 21}, {36, 20}, {36, 6}, {36, 40}, {36, 32}, {36, 38}, {36, 7}, {36, 1}, {36, 43}, {36, 5}, {36, 11}, {36, 23}, {36, 39}, {36, 28}, {36, 33}, {36, 18}, {36, 46}, {36, 9}, {36, 45}, {36, 44}, {36, 2}, {10, 3}, {10, 21}, {10, 20}, {10, 6}, {10, 40}, {10, 32}, {10, 38}, {10, 7}, {10, 1}, {10, 43}, {10, 17}, {10, 5}, {10, 11}, {10, 23}, {10, 8}, {10, 39}, {10, 28}, {10, 33}, {10, 18}, {10, 46}, {10, 9}, {10, 41}, {10, 45}, {10, 44}, {10, 2}, {3, 21}, {3, 20}, {3, 6}, {3, 40}, {3, 34}, {3, 32}, {3, 38}, {3, 7}, {3, 1}, {3, 43}, {3, 17}, {3, 5}, {3, 11}, {3, 23}, {3, 39}, {3, 28}, {3, 33}, {3, 18}, {3, 46}, {3, 9}, {3, 41}, {3, 45}, {3, 44}, {3, 2}, {21, 20}, {21, 6}, {21, 40}, {21, 34}, {21, 38}, {21, 7}, {21, 1}, {21, 17}, {21, 5}, {21, 11}, {21, 23}, {21, 8}, {21, 39}, {21, 28}, {21, 33}, {21, 18}, {21, 9}, {21, 41}, {21, 45}, {21, 44}, {21, 2}, {20, 6}, {20, 40}, {20, 34}, {20, 32}, {20, 38}, {20, 7}, {20, 1}, {20, 43}, {20, 5}, {20, 11}, {20, 23}, {20, 8}, {20, 39}, {20, 28}, {20, 33}, {20, 18}, {20, 46}, {20, 41}, {20, 45}, {20, 44}, {20, 2}, {6, 40}, {6, 34}, {6, 32}, {6, 38}, {6, 7}, {6, 1}, {6, 43}, {6, 17}, {6, 5}, {6, 11}, {6, 23}, {6, 8}, {6, 39}, {6, 28}, {6, 33}, {6, 18}, {6, 46}, {6, 9}, {6, 41}, {6, 45}, {6, 2}, {40, 32}, {40, 38}, {40, 7}, {40, 1}, {40, 43}, {40, 17}, {40, 5}, {40, 11}, {40, 23}, {40, 28}, {40, 33}, {40, 18}, {40, 46}, {40, 9}, {40, 41}, {40, 45}, {40, 44}, {40, 2}, {34, 32}, {34, 38}, {34, 7}, {34, 1}, {34, 43}, {34, 17}, {34, 5}, {34, 11}, {34, 23}, {34, 8}, {34, 39}, {34, 28}, {34, 33}, {34, 18}, {34, 9}, {34, 45}, {34, 44}, {34, 2}, {32, 38}, {32, 7}, {32, 1}, {32, 17}, {32, 11}, {32, 23}, {32, 8}, {32, 39}, {32, 28}, {32, 33}, {32, 18}, {32, 46}, {32, 9}, {32, 41}, {32, 45}, {32, 44}, {32, 2}, {38, 7}, {38, 1}, {38, 43}, {38, 17}, {38, 11}, {38, 23}, {38, 8}, {38, 39}, {38, 28}, {38, 33}, {38, 18}, {38, 46}, {38, 9}, {38, 41}, {38, 45}, {38, 44}, {38, 2}, {7, 43}, {7, 17}, {7, 5}, {7, 11}, {7, 23}, {7, 8}, {7, 28}, {7, 18}, {7, 46}, {7, 9}, {7, 41}, {7, 45}, {7, 44}, {7, 2}, {1, 43}, {1, 17}, {1, 5}, {1, 11}, {1, 8}, {1, 39}, {1, 28}, {1, 33}, {1, 18}, {1, 46}, {1, 9}, {1, 41}, {1, 45}, {1, 44}, {1, 2}, {43, 17}, {43, 5}, {43, 11}, {43, 23}, {43, 8}, {43, 28}, {43, 33}, {43, 18}, {43, 46}, {43, 9}, {43, 41}, {43, 45}, {43, 44}, {43, 2}, {17, 5}, {17, 11}, {17, 23}, {17, 8}, {17, 39}, {17, 28}, {17, 33}, {17, 18}, {17, 46}, {17, 9}, {17, 41}, {17, 45}, {17, 44}, {17, 2}, {5, 11}, {5, 23}, {5, 8}, {5, 39}, {5, 28}, {5, 33}, {5, 18}, {5, 46}, {5, 9}, {5, 41}, {5, 45}, {5, 44}, {5, 2}, {11, 23}, {11, 8}, {11, 39}, {11, 28}, {11, 33}, {11, 18}, {11, 46}, {11, 9}, {11, 41}, {11, 45}, {11, 44}, {11, 2}, {23, 8}, {23, 39}, {23, 28}, {23, 33}, {23, 18}, {23, 46}, {23, 41}, {23, 45}, {23, 2}, {8, 39}, {8, 28}, {8, 33}, {8, 46}, {8, 9}, {8, 41}, {8, 45}, {8, 44}, {8, 2}, {39, 28}, {39, 18}, {39, 46}, {39, 9}, {39, 41}, {39, 45}, {39, 44}, {39, 2}, {28, 33}, {28, 18}, {28, 46}, {28, 9}, {28, 41}, {28, 45}, {28, 44}, {28, 2}, {33, 18}, {33, 46}, {33, 9}, {33, 41}, {33, 44}, {33, 2}, {18, 46}, {18, 9}, {18, 41}, {18, 45}, {18, 44}, {18, 2}, {46, 9}, {46, 41}, {46, 45}, {46, 44}, {46, 2}, {9, 41}, {9, 45}, {9, 44}, {9, 2}, {41, 45}, {41, 44}, {45, 44}, {45, 2}, {44, 2}};
		queries = {{43, 47}, {2, 32}, {20, 49}, {46, 19}, {35, 33}, {49, 42}, {32, 49}, {48, 40}, {21, 49}, {44, 24}, {21, 9}, {45, 13}, {30, 43}, {33, 12}, {41, 18}, {48, 45}, {47, 43}, {26, 32}, {39, 1}, {1, 24}, {29, 7}, {39, 47}, {49, 45}, {9, 8}, {36, 1}, {9, 12}, {34, 5}, {6, 22}, {22, 28}, {14, 27}, {26, 14}, {32, 44}, {1, 30}, {18, 39}, {33, 15}, {49, 44}, {46, 35}, {10, 14}, {37, 35}, {26, 40}, {38, 15}, {43, 47}, {48, 15}, {31, 42}, {44, 15}, {48, 46}, {44, 29}, {22, 23}, {25, 41}, {40, 43}, {32, 41}, {27, 13}, {25, 24}, {17, 15}, {10, 7}, {49, 48}, {2, 37}, {42, 35}, {37, 40}, {47, 43}, {32, 40}, {39, 42}, {29, 24}, {49, 41}, {12, 45}, {48, 15}, {44, 30}, {33, 28}, {0, 25}, {44, 26}, {35, 31}, {39, 32}, {45, 10}, {20, 18}, {18, 14}, {12, 9}, {35, 28}, {44, 36}, {43, 41}, {23, 3}, {44, 45}, {37, 24}, {41, 35}, {22, 5}, {39, 43}, {28, 5}, {25, 10}, {48, 49}, {3, 12}, {29, 43}, {42, 46}, {37, 0}, {39, 34}, {22, 35}, {29, 26}, {17, 41}, {32, 47}, {24, 37}, {23, 46}, {46, 44}, {43, 42}, {4, 3}, {23, 8}, {17, 16}, {29, 11}, {49, 46}, {22, 47}, {22, 8}, {23, 30}, {28, 39}, {48, 32}, {19, 44}, {17, 16}, {36, 48}, {4, 12}, {49, 31}, {19, 25}, {26, 40}, {42, 39}, {39, 44}, {17, 38}, {35, 27}, {47, 42}, {5, 32}, {35, 28}, {32, 22}, {39, 47}, {47, 44}, {34, 35}, {35, 37}, {49, 33}, {23, 39}, {46, 43}, {9, 23}, {39, 27}, {33, 49}, {43, 44}, {42, 26}, {41, 21}, {46, 44}, {3, 29}, {5, 48}, {8, 49}, {46, 47}, {5, 7}, {43, 35}, {21, 18}, {13, 42}, {22, 37}, {18, 7}, {35, 31}, {13, 21}, {23, 9}, {26, 49}, {31, 48}, {13, 42}, {47, 18}, {48, 49}, {19, 3}, {22, 40}, {18, 14}, {7, 24}, {12, 1}, {24, 32}, {42, 28}, {11, 0}, {43, 41}, {36, 46}, {12, 27}, {11, 30}, {48, 44}, {7, 40}, {36, 49}, {35, 30}, {38, 36}, {46, 39}, {29, 23}, {47, 33}, {36, 46}, {19, 24}, {36, 45}, {45, 38}, {5, 3}, {4, 35}, {20, 26}, {6, 14}, {38, 37}, {26, 30}, {30, 39}, {25, 18}, {49, 48}, {35, 31}, {22, 2}, {38, 47}, {35, 21}, {37, 9}, {49, 41}, {49, 36}, {47, 10}, {18, 27}, {42, 49}, {46, 45}, {18, 7}, {20, 10}, {21, 48}, {11, 37}, {18, 36}, {31, 44}, {4, 37}, {38, 11}, {17, 37}, {27, 17}, {30, 48}, {29, 40}, {48, 49}, {30, 37}, {19, 7}, {18, 0}, {7, 40}, {27, 7}, {18, 4}, {41, 32}, {25, 19}, {11, 19}, {47, 44}, {47, 49}, {21, 4}, {38, 25}, {28, 48}, {26, 35}, {47, 34}, {15, 14}, {4, 10}, {32, 24}, {14, 45}, {20, 33}, {30, 11}, {49, 48}, {44, 45}, {21, 27}, {29, 23}, {38, 40}, {38, 39}, {19, 5}, {12, 47}, {26, 46}, {9, 30}, {29, 48}, {9, 11}, {46, 42}, {35, 29}, {45, 29}, {26, 31}, {19, 41}, {46, 47}, {12, 10}, {39, 3}, {18, 42}, {7, 44}, {22, 49}, {43, 49}, {16, 11}, {42, 38}, {2, 34}, {8, 28}, {16, 5}, {20, 43}, {29, 35}, {48, 44}, {38, 24}, {47, 44}, {11, 21}, {38, 46}, {47, 16}, {41, 47}, {43, 12}, {16, 6}, {27, 15}, {14, 1}, {37, 36}, {48, 45}, {13, 28}, {46, 14}, {41, 30}, {24, 36}, {44, 8}, {30, 42}, {33, 22}, {32, 1}, {7, 16}, {45, 43}, {32, 11}, {49, 12}, {32, 38}, {7, 4}, {1, 11}, {45, 48}, {10, 25}, {36, 42}, {49, 35}, {24, 44}, {15, 29}, {39, 10}, {8, 23}, {14, 7}, {27, 32}, {45, 32}, {48, 38}, {41, 21}, {9, 19}, {48, 49}, {22, 42}, {13, 3}, {14, 23}, {49, 29}, {0, 20}, {48, 41}, {43, 47}, {4, 15}, {29, 40}, {49, 48}, {48, 8}, {1, 40}, {41, 21}, {49, 48}, {18, 6}, {32, 49}, {41, 4}, {47, 39}, {48, 47}, {38, 49}, {28, 2}, {36, 18}, {24, 34}, {48, 26}, {19, 12}, {2, 29}, {8, 13}, {44, 19}, {39, 40}, {3, 22}, {2, 10}, {26, 37}, {39, 40}, {44, 18}, {30, 28}, {19, 43}, {38, 20}, {49, 48}, {37, 32}, {48, 26}, {14, 36}, {42, 32}, {24, 18}, {28, 40}, {16, 31}, {5, 7}, {21, 27}, {10, 27}, {43, 23}, {22, 29}, {35, 38}, {47, 45}, {18, 43}, {48, 42}, {34, 31}, {43, 8}, {30, 21}, {48, 49}, {13, 36}, {12, 2}, {17, 35}, {19, 37}, {42, 9}, {43, 14}, {44, 47}, {38, 39}, {43, 37}, {27, 49}, {39, 36}, {32, 40}, {3, 15}, {11, 6}, {24, 11}, {34, 39}, {37, 32}, {47, 49}, {13, 37}, {40, 37}, {47, 46}, {48, 39}, {47, 27}, {27, 37}, {25, 14}, {46, 48}, {18, 8}, {33, 13}, {47, 25}, {49, 46}, {44, 48}, {48, 46}, {48, 49}, {47, 48}, {39, 42}, {13, 28}, {10, 11}, {47, 48}, {46, 48}, {20, 30}, {31, 15}, {47, 15}, {19, 30}, {48, 25}, {23, 33}, {40, 43}, {22, 41}, {48, 49}, {15, 47}, {7, 46}, {39, 16}, {27, 28}, {20, 9}, {48, 47}, {39, 41}, {22, 23}, {31, 39}, {8, 28}, {10, 20}, {24, 23}, {47, 48}, {26, 30}, {30, 24}, {43, 24}, {37, 5}, {0, 47}, {4, 47}, {34, 45}, {20, 27}, {48, 47}, {49, 40}, {11, 42}, {4, 29}, {4, 42}, {49, 46}, {43, 37}, {45, 35}, {40, 6}, {42, 45}, {8, 11}, {12, 48}, {26, 46}, {49, 47}, {7, 21}, {48, 49}, {19, 36}, {22, 16}, {44, 33}, {38, 47}, {21, 39}, {17, 2}, {41, 43}, {0, 46}, {4, 48}, {33, 29}, {43, 44}, {48, 34}, {43, 42}, {43, 6}, {39, 34}, {18, 30}, {35, 31}, {44, 46}, {48, 49}, {31, 22}, {49, 13}, {11, 49}, {44, 17}, {41, 26}, {39, 11}, {49, 46}, {32, 49}, {37, 42}, {47, 48}, {42, 43}, {45, 31}, {15, 42}, {49, 48}, {49, 3}, {47, 35}, {4, 10}, {3, 43}, {34, 25}, {3, 6}, {31, 23}, {46, 42}, {21, 30}, {25, 35}, {26, 49}, {26, 3}, {8, 31}, {49, 15}, {35, 33}, {11, 33}, {43, 34}, {23, 38}, {19, 24}, {39, 30}, {43, 41}, {46, 39}, {48, 39}, {21, 24}, {20, 13}, {2, 39}, {49, 35}, {1, 29}, {9, 33}, {47, 48}, {49, 40}, {32, 23}, {20, 49}, {49, 48}, {38, 40}, {42, 41}, {33, 13}, {48, 15}, {36, 37}, {46, 49}, {25, 36}, {32, 45}, {32, 40}, {7, 40}, {28, 27}, {15, 13}, {43, 49}, {47, 2}, {30, 12}, {36, 28}, {42, 46}, {17, 0}, {38, 32}, {14, 4}, {19, 4}, {23, 26}, {48, 2}, {35, 17}, {23, 30}, {48, 42}, {39, 34}, {34, 17}, {28, 37}, {45, 7}, {48, 49}, {0, 14}, {34, 25}, {27, 8}, {45, 42}, {34, 0}, {41, 27}, {24, 32}, {39, 6}, {46, 38}, {43, 29}, {42, 40}, {44, 45}, {30, 17}, {30, 15}, {20, 23}, {11, 43}, {11, 43}, {34, 22}, {27, 19}, {39, 5}, {47, 45}, {48, 47}, {45, 40}, {49, 14}, {33, 43}, {21, 32}, {46, 45}, {32, 28}, {44, 49}, {35, 19}, {11, 21}};
		n = 50;
		ans = Solution().checkIfPrerequisite(n, prereqs, queries); // F,T



	}
}
