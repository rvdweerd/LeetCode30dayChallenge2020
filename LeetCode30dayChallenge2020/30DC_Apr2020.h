#pragma once
#include <algorithm>
#include <iterator>
#include <iostream>
#include <cstring>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <queue>

namespace Apr20_day1
{
	// I learned this optimized solution from Errichto
	class Solution {
	public:
		int singleNumber(std::vector<int>& nums) {
			int x = 0;
			for (const auto v : nums)
			{
				x ^= v;
			}
			return x;
		}
	};
}
namespace Apr20_day2
{
	std::vector<int> GetDigits(int n)
	{
		std::vector<int> vec;
		for (; n != 0; n /= 10)
		{
			vec.push_back(n % 10);
		}
		return vec;
	}
	int SumSquares(std::vector<int> v)
	{
		int r = 0;
		for (const auto& val : v)
		{
			r += (val * val);
		}
		return r;
	}
	bool IsHappy(int n)
	{
		std::set<int> set;
		int sumSq = 0;
		while (true)
		{
			std::vector<int> vec = GetDigits(n);
			n = SumSquares(vec);
			if (n == 1)
			{
				return true;
			}
			else if (set.find(n) != set.end())
			{
				return false;
			}
			set.insert(n);
		}
	}
}
namespace Apr20_day3
{
	int maxSubArray(std::vector<int>& nums)
	{
		int MIN = 0;
		int MAX = nums[0];
		int accum = 0;
		int maxRange = nums[0];
		for (int i = 0; i < (int)nums.size(); i++)
		{
			accum += nums[i];
			if (accum <= MIN)
			{
				if (accum - MIN > maxRange)
				{
					maxRange = accum - MIN;
				}
				MIN = accum;
			}
			if (accum > MIN && (accum - MIN > maxRange))
			{
				maxRange = accum - MIN;
			}
		}
		return maxRange;
	}
}
namespace Apr20_day4
{
	class Solution {
	public:
		void moveZeroes(std::vector<int>& nums)
		{
			for (size_t slow_nz = 0, cur = 0; cur < nums.size(); cur++)
			{
				if (nums[cur] != 0)
				{
					std::swap(nums[slow_nz++], nums[cur]);
				}
			}
		}
	};
}
namespace Apr20_day5
{
	class Solution {
	public:
		int maxProfit(std::vector<int>& prices) {
			int profit = 0;
			for (size_t i = 1; i < prices.size(); i++)
			{
				if (prices[i] > prices[i - 1]) profit += prices[i] - prices[i - 1];
			}
			return profit;
		}
	};
}
namespace Apr20_day6
{
	class Solution
	{
	public:
		std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs)
		{
			std::vector<std::vector<std::string>> mainvec;
			std::map<std::string, std::set<std::string>> map;
			for (size_t i = 0; i < strs.size(); i++)
			{
				std::string temp = strs[i];
				std::sort(temp.begin(), temp.end());
				map[temp].insert(strs[i]);
			}
			for (const auto& p : map)
			{
				std::vector<std::string> subvec;
				subvec.insert(subvec.end(), p.second.begin(), p.second.end());
				mainvec.push_back(subvec);
				//mainvec.emplace_back(p.second.begin(),p.second.end());
			}
			return mainvec;
		}
	};
}
namespace Apr20_day7
{
	class Solution {
	public:
		int countElements(std::vector<int>& arr) {
			int count = 0;
			for (auto v : arr)
			{
				if (std::count(arr.begin(), arr.end(), v + 1) > 0) count++;
			}
			return count;
		}
	};
}
namespace Apr20_day8
{
	// Definition for singly-linked list.
	struct ListNode {
		int val;
		ListNode* next;
		ListNode(int x) : val(x), next(NULL) {}
	};
	class Solution {
	public:
		ListNode* middleNode(ListNode* head)
		{
			int count = 0;
			for (ListNode* p = head; p != nullptr; p = p->next)
			{
				count++;
			}
			ListNode* ret = head;
			for (int i = 0; i < count / 2; i++)
			{
				ret = ret->next;
			}
			return ret;

		}
	};
}
namespace Apr20_day9
{
	class Solution {
	public:
		std::string ClearString2(const std::string& str)
		{
			std::string ret_str;
			for (const char& c : str)
			{
				if (c == '#')
				{
					if (ret_str.size() != 0)
					{
						ret_str.erase(ret_str.end() - 1);
					}
				}
				else
				{
					ret_str += c;
				}
			}
			return ret_str;
		}
		bool backspaceCompare(std::string S, std::string T) {
			return ClearString2(S) == ClearString2(T);
		}
		void ClearString(std::string& str)
		{
			auto begin = str.begin();
			auto end = str.end();
			for (auto it = str.begin(); it != end;)
			{

				if (*it == '#')
				{
					if (it != begin)
					{
						it = str.erase(std::prev(it), std::next(it));
					}
					else
					{
						it = str.erase(it);
					}
					end = str.end();
				}
				else
				{
					it++;
				}

			}
		}
	};
}
namespace Apr20_day10
{
	class MinStack {
	public:
		//** initialize your data structure here. */
		MinStack()
		{
		}
		void push(int x)
		{
			if (x < min) min = x;
			arr[index++] = min;
			arr[index++] = x;
		}
		void pop()
		{
			if (index != 0)
			{
				index -= 2;
			}
			if (index == 0)
			{
				min = INT_MAX;
			}
			else
			{
				min = arr[index - 2];
			}
		}
		int top()
		{
			return arr[index - 1];
		}
		int getMin()
		{
			return arr[index - 2];
		}

	private:
		int arr[20000];
		int min = INT_MAX;
		size_t index = 0;
	};
	/**
	 * Your MinStack object will be instantiated and called as such:
	 * MinStack* obj = new MinStack();
	 * obj->push(x);
	 * obj->pop();
	 * int param_3 = obj->top();
	 * int param_4 = obj->getMin();
	 */
}
namespace Apr20_day10b
{
	// Node based stack
	class MinStack
	{
	private:
		struct Node
		{
			Node(int val_in)
				:
				val(val_in),
				min_val(val_in)
			{

			}
			int val;
			int min_val;
			Node* next = nullptr;
		};
		Node* root = nullptr;
		int min(int a, int b)
		{
			return a < b ? a : b;
		}
	public:
		/** initialize your data structure here. */
		MinStack()
		{
		}
		~MinStack()
		{
			while (root != nullptr)
			{
				pop();
			}
		}
		void push(int x)
		{
			Node* newNode = new Node(x);
			if (root != nullptr && x > root->min_val)
			{
				newNode->min_val = root->min_val;
			}
			newNode->next = root;
			root = newNode;
		}
		void pop()
		{
			if (root != nullptr)
			{
				Node* tmp = root;
				root = root->next;
				delete tmp;
			}
		}
		int top()
		{
			return root->val;
		}
		int getMin()
		{
			return root->min_val;
		}
	};

}
namespace Apr20_day11 // Diameter of binary tree
{
	// Definition for a binary tree node.
	struct TreeNode
	{
		int val;
		TreeNode* left;
		TreeNode* right;
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	};

	class Solution {
	public:
		int diameterOfBinaryTree(TreeNode* root)
		{
			std::vector<int> nodeSums;
			TraverseTree(root, nodeSums);
			if (nodeSums.size() > 0)
			{
				auto it = std::max_element(nodeSums.begin(), nodeSums.end());
				return *it;// , [](const int a, const int b) {return a > b; });
			}
			return 0;
			// n_left= depth left
			// n_right = depth right
			// add pair to vec
			// same for children
			//return 0;
		}
		int getDepthOfBinaryTree(TreeNode* root)
		{
			d_max = 0;
			setDepthOfBinaryTree(root, 0);
			return d_max;
		}
	private:
		int d_max = 0;
		void setDepthOfBinaryTree(TreeNode* root, int n)
		{
			if (root != nullptr)
			{
				setDepthOfBinaryTree(root->left, n + 1);
				setDepthOfBinaryTree(root->right, n + 1);
			}
			if (n > d_max) d_max = n;
		}
		void TraverseTree(TreeNode* root, std::vector<int>& nodeSums)
		{
			if (root != nullptr)
			{
				nodeSums.emplace_back(getDepthOfBinaryTree(root->left) + getDepthOfBinaryTree(root->right));
				TraverseTree(root->left, nodeSums);
				TraverseTree(root->right, nodeSums);
			}
			return;
		}
	};
}
namespace Apr20_day12 // Last stone weight
{
	class Solution {
	public:
		int lastStoneWeight(std::vector<int>& stones) {
			std::priority_queue<int> queue(stones.begin(), stones.end());
			while (queue.size() > 1)
			{
				const int s1 = queue.top(); queue.pop();
				const int s2 = queue.top(); queue.pop();
				queue.push(s1 - s2);
			}
			if (queue.empty()) return 0; else return queue.top();
		}
	};
}
namespace Apr20_day13a // Contiguous Array
{
	class Solution {
		int nSinglePass(std::vector<int>& nums, int& max_len)
		{
			int balance = 0;
			int count = 0;
			for (size_t i = 0; i < nums.size(); i++)
			{
				balance += (nums[i] == 0 ? -1 : 1);
				if (balance == 0)
				{
					count++;
					if ((int)i + 1 > max_len) max_len = i + 1;
				}
			}
			return count;
		}
	public:
		int findMaxLength(std::vector<int>& nums) {
			int tot = 0;
			int max_len = 0;
			int vecsize = nums.size();
			for (int i = 0; i < vecsize; i++)
			{
				tot += nSinglePass(nums, max_len);
				nums.erase(nums.begin());
			}
			return max_len;
		}
	};
}
namespace Apr20_day13b
{
	class Solution {

	public:
		int findMaxLength(std::vector<int>& nums)
		{
			if (nums.size() < 2) return 0;
			std::unordered_map<int, int> map;
			map[0] = 0;
			int max_len = 0;
			int counter = 0;
			for (size_t i = 0; i < nums.size(); i++)
			{
				counter += (nums[i] == 0 ? -1 : 1);


				auto it = map.find(counter);
				if (it == map.end())
				{
					map[counter] = i + 1;
				}
				else
				{
					const int len = i - it->second + 1;
					if (len > max_len) max_len = len;
				}
			}
			return max_len;
		}
	};
}
namespace Apr20_day14
{
	class Solution {
	public:
		std::string stringShift(std::string s, std::vector<std::vector<int>>& shift) {
			size_t sz = s.size();
			for (std::vector<int> sh : shift)
			{
				if (sh[0] == 0)
				{
					//std::transform(s.begin(), s.begin() + sh[1], std::back_inserter(s), [](char c) {return c; }); // 
					/*for (int i = 0; i < sh[1]; i++)
					{
						s.push_back(s.front());

					}
					s = s.substr(sh[1]);*/
					s.insert(s.end(), s.begin(), s.begin() + sh[1]);
					s = s.substr(sh[1]);
				}
				else
				{
					s.insert(s.begin(), s.end() - sh[1], s.end());
					s.resize(s.size() - sh[1]);
				}
			}
			return s;
		}
	};
	void RunExample()
	{
		std::vector<std::vector<int>> shift = { {1,1},{1,1},{0,2},{1,3} };
		std::string str13 = "abcdefg";
		std::cout << Apr20_day14::Solution().stringShift(str13, shift);
	}
}
namespace Apr20_day15
{
	class Solution {
	public:
		std::vector<int> productExceptSelf(std::vector<int>& nums)
		{
			const size_t len = nums.size();
			//std::vector<int> right(len,0); right[0] = nums[0];
			//std::vector<int> left(len, 0); left[len - 1] = nums.back();
			std::vector<int> right; right.resize(len); right[0] = nums.front();
			std::vector<int> left; left.resize(len); left[len - 1] = nums.back();

			for (size_t i = 1; i < len; i++)
			{
				right[i] = right[i - 1] * nums[i];
				left[len - 1 - i] = left[len - i] * nums[len - 1 - i];
			}
			std::vector<int> out(len, 0);
			out[0] = left[1];
			out[len - 1] = right[len - 2];
			for (size_t i = 1; i < len - 1; i++)
			{
				out[i] = right[i - 1] * left[i + 1];
			}
			return out;
		}
	};
	void RunExample()
	{
		std::vector<int> vec_in = { 1,2,3,4 };
		std::vector<int> vec_out = Apr20_day15::Solution().productExceptSelf(vec_in);
	}
}
namespace Apr20_day16
{
	class Solution {
	public:
		bool checkValidString(std::string s)
		{
			if (s.size() < 1) return true;
			if (s.front() == ')' || s.back() == '(') return false;
			std::stack<int> open;
			std::stack<int> stars;
			for (size_t i = 0; i < s.size(); i++)
			{
				if (s[i] == '(')
				{
					open.push(i);
				}
				else if (s[i] == '*')
				{
					stars.push(i);
				}
				else if (s[i] == ')')
				{
					if (!open.empty())
					{
						open.pop();
					}
					else
					{
						if (stars.empty())
						{
							return false;
						}
						else
						{
							stars.pop();
						}
					}
				}
			}
			if (open.empty())
			{
				return true;
			}

			while (!open.empty() && !stars.empty() && open.top() < stars.top())
			{
				open.pop();
				stars.pop();
			}
			if (open.empty())
			{
				return true;
			}
			return false;
		}
	};
	void RunExample()
	{
		std::cout << Apr20_day16::Solution().checkValidString("*(()*))");//T
		std::cout << Apr20_day16::Solution().checkValidString(")*()");//F
		std::cout << Apr20_day16::Solution().checkValidString("**())");//T
		std::cout << Apr20_day16::Solution().checkValidString("(*))");//T
		std::cout << Apr20_day16::Solution().checkValidString("(*()");//T
	}
}
namespace Apr20_day17
{
	class Solution
	{
	public:
		int numIslands(std::vector<std::vector<char>>& grid)
		{
			if (grid.size() == 0) return 0;
			int count = 0;
			for (size_t x = 0; x < grid[0].size(); x++)
			{
				for (size_t y = 0; y < grid.size(); y++)
				{
					if (grid[y][x] == '1')
					{
						count++;
						gridBFS(grid, x, y);
					}
				}
			}
			return count;
		};
	private:
		struct Pos
		{
			size_t x;
			size_t y;
		};
		void gridBFS(std::vector<std::vector<char>>& grid, size_t x, size_t y)
		{
			Pos startpos = { x,y };
			std::queue<Pos> queue; queue.push(startpos);
			grid[startpos.y][startpos.x] = '0';
			while (!queue.empty())
			{
				const Pos curpos = queue.front(); queue.pop();
				x = curpos.x;
				y = curpos.y;
				// check WEST
				if (x > 0 && grid[y][x - 1] == '1')
				{
					grid[y][x - 1] = '0';
					queue.push({ x - 1,y });
				}
				// check NORTH
				if (y > 0 && grid[y - 1][x] == '1')
				{
					grid[y - 1][x] = '0';
					queue.push({ x,y - 1 });
				}
				// check EAST
				if (x < grid[0].size() - 1 && grid[y][x + 1] == '1')
				{
					grid[y][x + 1] = '0';
					queue.push({ x + 1,y });
				}
				// check NORTH
				if (y < grid.size() - 1 && grid[y + 1][x] == '1')
				{
					grid[y + 1][x] = '0';
					queue.push({ x,y + 1 });
				}
			}
		}
	};
	void RunExample()
	{
		std::vector<std::vector<char>> grid = {
			{'1','0','1','1','0','1','1'}//,
			//{'1','1','0','0','0'},
			//{'0','0','1','0','0'},
			//{'0','0','0','1','1'},
		};
		std::cout << Apr20_day17::Solution().numIslands(grid);
	}
}
namespace Apr20_day18 // DP in simple case where you only move east and south
{
	class Solution {
	public:
		//int minPathSum2(std::vector<std::vector<int>>& grid)
		//{
		//	const size_t width = grid[0].size();
		//	const size_t height = grid.size();
		//	std::vector<int> arr(width * height, 0);

		//	for (size_t i = width - 1; i >= 0; i--)
		//	{
		//		for (size_t j = height - 1; j >= 0; j--)
		//		{

		//		}
		//	}
		//}
		int minPathSum(std::vector<std::vector<int>>& grid)
		{
			if (grid.size() == 0 && grid[0].size() == 0) return 0;
			size_t width = grid[0].size();
			size_t height = grid.size();
			for (size_t x = 0; x < width; x++)
			{
				for (size_t y = 0; y < height; y++)
				{
					if (x != 0 && y != 0) grid[y][x] = std::min(grid[y - 1][x], grid[y][x - 1]) + grid[y][x];
					else if (x == 0 && y != 0) grid[y][x] = grid[y - 1][x] + grid[y][x];
					else if (x != 0 && y == 0) grid[y][x] = grid[y][x - 1] + grid[y][x];
				}
			}
			return grid[height - 1][width - 1];
		}
	};
	void RunExample()
	{
		std::vector<std::vector<int>> vec = {
			{1, 2, 1},
			{3, 1, 2},
			{5, 5, 1}
		};

		std::vector<std::vector<int>> vec2 = {
			{5 , 4 , 2 , 9 , 6 , 0 , 3 , 5 , 1 , 4 , 9 , 8 , 4 , 9 , 7 , 5 , 1} ,
			{3 , 4 , 9 , 2 , 9 , 9 , 0 , 9 , 7 , 9 , 4 , 7 , 8 , 4 , 4 , 5 , 8} ,
			{6 , 1 , 8 , 9 , 8 , 0 , 3 , 7 , 0 , 9 , 8 , 7 , 4 , 9 , 2 , 0 , 1} ,
			{4 , 0 , 0 , 5 , 1 , 7 , 4 , 7 , 6 , 4 , 1 , 0 , 1 , 0 , 6 , 2 , 8} ,
			{7 , 2 , 0 , 2 , 9 , 3 , 4 , 7 , 0 , 8 , 9 , 5 , 9 , 0 , 1 , 1 , 0} ,
			{8 , 2 , 9 , 4 , 9 , 7 , 9 , 3 , 7 , 0 , 3 , 6 , 5 , 3 , 5 , 9 , 6} ,
			{8 , 9 , 9 , 2 , 6 , 1 , 2 , 5 , 8 , 3 , 7 , 0 , 4 , 9 , 8 , 8 , 8} ,
			{5 , 8 , 5 , 4 , 1 , 5 , 6 , 6 , 3 , 3 , 1 , 8 , 3 , 9 , 6 , 4 , 8} ,
			{0 , 2 , 2 , 3 , 0 , 2 , 6 , 7 , 2 , 3 , 7 , 3 , 1 , 5 , 8 , 1 , 3} ,
			{4 , 4 , 0 , 2 , 0 , 3 , 8 , 4 , 1 , 3 , 3 , 0 , 7 , 4 , 2 , 9 , 8} ,
			{5 , 9 , 0 , 4 , 7 , 5 , 7 , 6 , 0 , 8 , 3 , 0 , 0 , 6 , 6 , 6 , 8} ,
			{0 , 7 , 1 , 8 , 3 , 5 , 1 , 8 , 7 , 0 , 2 , 9 , 2 , 2 , 7 , 1 , 5} ,
			{1 , 0 , 0 , 0 , 6 , 2 , 0 , 0 , 2 , 2 , 8 , 0 , 9 , 7 , 0 , 8 , 0} ,
			{1 , 1 , 7 , 2 , 9 , 6 , 5 , 4 , 8 , 7 , 8 , 5 , 0 , 3 , 8 , 1 , 5} ,
			{8 , 9 , 7 , 8 , 1 , 1 , 3 , 0 , 1 , 2 , 9 , 4 , 0 , 1 , 5 , 3 , 1} ,
			{9 , 2 , 7 , 4 , 8 , 7 , 3 , 9 , 2 , 4 , 2 , 2 , 7 , 8 , 2 , 6 , 7} ,
			{3 , 8 , 1 , 6 , 0 , 4 , 8 , 9 , 8 , 0 , 2 , 5 , 3 , 5 , 5 , 7 , 5} ,
			{1 , 8 , 2 , 5 , 7 , 7 , 1 , 9 , 9 , 8 , 9 , 2 , 4 , 9 , 5 , 4 , 0} ,
			{3 , 4 , 4 , 1 , 5 , 3 , 3 , 8 , 8 , 6 , 3 , 5 , 3 , 8 , 7 , 1 , 3}
		};
		int sol = Solution().minPathSum(vec);
	}
}
namespace Apr20_day18b // With Dijkstra in case you want to move in all directions
{
	class Solution {
	public:
		struct Pos
		{
			bool operator==(const Pos& rhs)
			{
				return (x == rhs.x && y == rhs.y);
			}
			bool operator!=(const Pos& rhs)
			{
				return !(*this == rhs);
			}
			int x;
			int y;
		};
		int minPathSum(std::vector<std::vector<int>>& grid)
		{
			auto cmp = [](std::pair<std::vector<Pos>, int> left, std::pair<std::vector<Pos>, int> right) {return left.second > right.second; };
			std::pair<std::vector<Pos>, int> path;
			std::priority_queue <
				std::pair<std::vector<Pos>, int>,
				std::vector<std::pair<std::vector<Pos>, int>>,
				decltype(cmp) > queue(cmp);
			std::map<int, std::pair<std::vector<Pos>, int>> fixed;

			const int height = grid.size();
			const int width = grid[0].size();
			Pos start = { 0,0 };
			Pos finish = { width - 1 ,height - 1 };
			path.first.push_back(start); path.second = grid[start.y][start.x];
			fixed[start.y * width + start.x] = path;

			while (start != finish)
			{
				if (path.first.back().x != width - 1 && fixed.find(start.y * width + start.x + 1) == fixed.end()) // CHECK EAST
				{
					path.first.push_back({ start.x + 1,start.y }); path.second += grid[start.y][start.x + 1];
					queue.push(path);
					path.first.pop_back(); path.second -= grid[start.y][start.x + 1];
				}
				//if (path.first.back().x != 0 && fixed.find(start.y * width + start.x-1) == fixed.end()) // CHECK WEST
				//{
				//	path.first.push_back({ start.x - 1,start.y }); path.second += grid[start.y][start.x - 1];
				//	queue.push(path);
				//	path.first.pop_back(); path.second -= grid[start.y][start.x - 1];
				//}
				if (path.first.back().y != height - 1 && fixed.find((start.y + 1) * width + start.x) == fixed.end()) // CHECK SOUTH
				{
					path.first.push_back({ start.x ,start.y + 1 }); path.second += grid[start.y + 1][start.x];
					queue.push(path);
					path.first.pop_back(); path.second -= grid[start.y + 1][start.x];
				}
				//if (path.first.back().y != 0 && fixed.find((start.y-1) * width + start.x) == fixed.end()) // CHECK NORTH
				//{
				//	path.first.push_back({ start.x ,start.y - 1 }); path.second += grid[start.y - 1][start.x];
				//	queue.push(path);
				//	path.first.pop_back(); path.second -= grid[start.y - 1][start.x];
				//}
				path = queue.top(); queue; queue.pop();
				start = path.first.back();
				fixed[start.y * width + start.x] = path;
			}
			return path.second;
		}
	};
	void RunExample()
	{
		std::vector<std::vector<int>> vec = {
			{7, 1, 3, 5, 8, 9, 9, 2, 1, 9, 0, 8, 3, 1, 6, 6, 9, 5},
			{9, 5, 9, 4, 0, 4, 8, 8, 9, 5, 7, 3, 6, 6, 6, 9, 1, 6},
			{8, 2, 9, 1, 3, 1, 9, 7, 2, 5, 3, 1, 2, 4, 8, 2, 8, 8},
			{6, 7, 9, 8, 4, 8, 3, 0, 4, 0, 9, 6, 6, 0, 0, 5, 1, 4},
			{7, 1, 3, 1, 8, 8, 3, 1, 2, 1, 5, 0, 2, 1, 9, 1, 1, 4},
			{9, 5, 4, 3, 5, 6, 1, 3, 6, 4, 9, 7, 0, 8, 0, 3, 9, 9},
			{1, 4, 2, 5, 8, 7, 7, 0, 0, 7, 1, 2, 1, 2, 7, 7, 7, 4},
			{3, 9, 7, 9, 5, 8, 9, 5, 6, 9, 8, 8, 0, 1, 4, 2, 8, 2},
			{1, 5, 2, 2, 2, 5, 6, 3, 9, 3, 1, 7, 9, 6, 8, 6, 8, 3},
			{5, 7, 8, 3, 8, 8, 3, 9, 9, 8, 1, 9, 2, 5, 4, 7, 7, 7},
			{2, 3, 2, 4, 8, 5, 1, 7, 2, 9, 5, 2, 4, 2, 9, 2, 8, 7},
			{0, 1, 6, 1, 1, 0, 0, 6, 5, 4, 3, 4, 3, 7, 9, 6, 1, 9}
		};

		std::vector<std::vector<int>> vec2 = {
			{5 , 4 , 2 , 9 , 6 , 0 , 3 , 5 , 1 , 4 , 9 , 8 , 4 , 9 , 7 , 5 , 1} ,
			{3 , 4 , 9 , 2 , 9 , 9 , 0 , 9 , 7 , 9 , 4 , 7 , 8 , 4 , 4 , 5 , 8} ,
			{6 , 1 , 8 , 9 , 8 , 0 , 3 , 7 , 0 , 9 , 8 , 7 , 4 , 9 , 2 , 0 , 1} ,
			{4 , 0 , 0 , 5 , 1 , 7 , 4 , 7 , 6 , 4 , 1 , 0 , 1 , 0 , 6 , 2 , 8} ,
			{7 , 2 , 0 , 2 , 9 , 3 , 4 , 7 , 0 , 8 , 9 , 5 , 9 , 0 , 1 , 1 , 0} ,
			{8 , 2 , 9 , 4 , 9 , 7 , 9 , 3 , 7 , 0 , 3 , 6 , 5 , 3 , 5 , 9 , 6} ,
			{8 , 9 , 9 , 2 , 6 , 1 , 2 , 5 , 8 , 3 , 7 , 0 , 4 , 9 , 8 , 8 , 8} ,
			{5 , 8 , 5 , 4 , 1 , 5 , 6 , 6 , 3 , 3 , 1 , 8 , 3 , 9 , 6 , 4 , 8} ,
			{0 , 2 , 2 , 3 , 0 , 2 , 6 , 7 , 2 , 3 , 7 , 3 , 1 , 5 , 8 , 1 , 3} ,
			{4 , 4 , 0 , 2 , 0 , 3 , 8 , 4 , 1 , 3 , 3 , 0 , 7 , 4 , 2 , 9 , 8} ,
			{5 , 9 , 0 , 4 , 7 , 5 , 7 , 6 , 0 , 8 , 3 , 0 , 0 , 6 , 6 , 6 , 8} ,
			{0 , 7 , 1 , 8 , 3 , 5 , 1 , 8 , 7 , 0 , 2 , 9 , 2 , 2 , 7 , 1 , 5} ,
			{1 , 0 , 0 , 0 , 6 , 2 , 0 , 0 , 2 , 2 , 8 , 0 , 9 , 7 , 0 , 8 , 0} ,
			{1 , 1 , 7 , 2 , 9 , 6 , 5 , 4 , 8 , 7 , 8 , 5 , 0 , 3 , 8 , 1 , 5} ,
			{8 , 9 , 7 , 8 , 1 , 1 , 3 , 0 , 1 , 2 , 9 , 4 , 0 , 1 , 5 , 3 , 1} ,
			{9 , 2 , 7 , 4 , 8 , 7 , 3 , 9 , 2 , 4 , 2 , 2 , 7 , 8 , 2 , 6 , 7} ,
			{3 , 8 , 1 , 6 , 0 , 4 , 8 , 9 , 8 , 0 , 2 , 5 , 3 , 5 , 5 , 7 , 5} ,
			{1 , 8 , 2 , 5 , 7 , 7 , 1 , 9 , 9 , 8 , 9 , 2 , 4 , 9 , 5 , 4 , 0} ,
			{3 , 4 , 4 , 1 , 5 , 3 , 3 , 8 , 8 , 6 , 3 , 5 , 3 , 8 , 7 , 1 , 3}
		};


		int sol = Solution().minPathSum(vec2);
	}
}
namespace Rod
{
	int maxrev2(std::vector<int>& p, int n)
	{
		std::vector<std::vector<int>> table(n, std::vector<int>(n, -1));
		table[0][0] = 0;
		for (int l = 1; l <= n; l++)
		{
			for (int j = 0; j < l; j++)
			{
				if (j == 0) table[l][j] = p[l];
				//else table[l][j] = std::max(table[0].begin(), table[0].end());
			}
		}
		return 0;
	}
	int maxrev(std::vector<int>& p, int n)
	{
		std::map<int, int> map;
		if (n == 0) return 0;
		int q = -1000;
		for (int i = 1; i <= n; i++)
		{
			if (map.find(i) == map.end())
			{
				int res = p[i - 1] + maxrev(p, n - i);//
				if (res > q) std::cout << i << ", ";
				q = std::max(q, res);
				//q = std::max(q, p[i - 1] + maxrev(p, n - i));
				map[i] = q;
			}
			else
			{
				q = map[i];
			}
		}
		return q;
	}
	int maxRevRec(const std::vector<int>& p, int n, std::vector<int>& memo)
	{
		if (memo[n] != -1) return memo[n];
		int q = -1;
		for (int i = 1; i <= n; i++)
		{
			int rhs = p[i - 1] + maxRevRec(p, n - i, memo);
			if (rhs > p[n - 1] && memo[50] == 1) std::cout << "split at: n=" << n << ", i=" << i << "\n";
			q = std::max(q, rhs);
			memo[15]++;
		}
		memo[n] = q; memo[50]--;
		return q;
	}
	int maxRevBottomUp(const std::vector<int>& p, int n)
	{
		std::vector<int> arr(10, 0);
		for (int i = 0; i < n; i++)
		{
			int q = -1;
			for (int j = 0; j < i; j++)
			{
				q = std::max(q, p[j] + arr[i - j]);
				arr[j + 1] = q;
			}
		}
		return arr[n];
	}

	void rod()
	{
		std::vector<int> p = { 1,5,8,9,10,17,17,20,24,30,33,35 };
		for (int n = 1; n <= 9; n++)
		{
			std::vector<int> memo(100, -1);
			memo[0] = 0; memo[50] = n;
			//int max = maxRevRec(p, n, memo);
			int max = maxRevBottomUp(p, n);
			std::cout << "MaxRev for a rod size " << n << " is :" << max << std::endl;
		}
	}
}
namespace Apr20_day19 // BS to find pivot, then BS on the right subrange
{
	class Solution {
	private:
		int binsearch(std::vector<int>& vec, int val, int lo, int hi)
		{
			//int len = vec.size();
			//int hi = len - 1;
			//int lo = 0;
			while (lo <= hi)
			{
				int m = lo + (hi - lo) / 2;
				if (vec[m] == val) return m;
				else if (val < vec[m]) // look left
				{
					hi = m - 1;
				}
				else // look right
				{
					lo = m + 1;
				}
			}
			return -1;
		}
		int findpivot(std::vector<int>& v)
		{
			int len = v.size();
			if (len <= 1) return 0;
			int hi = len - 1;
			int lo = 0;
			int m = lo + (hi - lo) / 2;

			while (true)
			{
				if (v[m] < v[lo]) // pivot is left
				{
					if (m - lo == 1) return m;
					hi = m;
					m = lo + (hi - lo) / 2;
				}
				else // pivot is right
				{
					if (hi - m == 1)
					{
						if (v[hi] >= v[m]) return 0;
						else return hi;
					}
					lo = m;
					m = lo + (hi - lo) / 2;
				}
			}
		}
	public:
		int search(std::vector<int>& nums, int target)
		{
			if (nums.empty()) return -1;
			int i = findpivot(nums);
			if (i == 0) return binsearch(nums, target, 0, nums.size() - 1);
			else if (target > nums.back()) // look left of pivot
			{
				return binsearch(nums, target, 0, i - 1);
			}
			else // look right of pivot (pivot position inclusive)
			{
				return binsearch(nums, target, i, nums.size() - 1);
			}
		}
	};
	void RunExample()
	{
		std::vector<int> v = { 4,5,6,7,0,1,2 };
		int i = Solution().search(v, 2);
	}

}
namespace Apr20_day20
{
	struct TreeNode {
		int val;
		TreeNode* left;
		TreeNode* right;
		TreeNode(int x)
			:
			val(x),
			left(NULL),
			right(NULL) {}
	};
	class Solution
	{
	public:
		TreeNode* bstFromPreorder(std::vector<int>& preorder)
		{
			if (preorder.size() == 0) return nullptr;
			TreeNode* root = new TreeNode(preorder.front());
			if (preorder.size() > 1)
			{
				for (size_t i = 1; i < preorder.size(); i++)
				{
					TreeNode* pt = root;
					int val = preorder[i];
					while ((val < pt->val && pt->left != nullptr) || (val > pt->val && pt->right != nullptr))
					{
						if (val < pt->val) pt = pt->left;
						else pt = pt->right;
					}
					if (val < pt->val) pt->left = new TreeNode(val);
					else pt->right = new TreeNode(val);
				}
			}
			return root;
		}

	};
	void RunExample()
	{
		std::vector<int> vec = { 8,5,1,7,10,12 };
		TreeNode* tn = Apr20_day20::Solution().bstFromPreorder(vec);
	}
}
namespace Apr20_day21
{
	/**
	* // This is the BinaryMatrix's API interface.
	* // You should not implement it, or speculate about its implementation
	* class BinaryMatrix {
	*   public:
	*     int get(int x, int y);
	*     vector<int> dimensions();
	* };
	*/
	class BinaryMatrix
	{
	public:
		void push(std::vector<int> vec)
		{
			if (M.size() == 0)
			{
				M.push_back(vec);
				n++;
				m = vec.size();
			}
			else
			{
				if (vec.size() == m)
				{
					M.push_back(vec);
					n++;
				}
			}
		}
		int get(int x, int y)
		{
			return M[x][y];
		}
		std::vector<size_t> dimensions()
		{
			return { n,m };
		}
	private:
		std::vector<std::vector<int>> M;
		size_t n = 0;
		size_t m = 0;
	};
	class Solution
	{
	public:
		int leftMostColumnWithOne(BinaryMatrix& binaryMatrix)
		{
			// Approach: start topright, follow the ones until bottom of matrix is reached
			// Note: challenge definitions: 
			//  ->  (nxm) matrix means m width, n height (contrary to lin.alg. convention)
			//  ->  m[x][y] means element on row x (vertical), position y (horizontal)
			// ->   So, my pointer ptr is defined as pair<x,y>
			const std::vector<size_t> dimension = binaryMatrix.dimensions();
			const int n = dimension[0];
			const int m = dimension[1];
			std::cout << "n=" << n << std::endl;	std::cout << "m=" << m << std::endl;

			std::pair<int, int> ptr = { 0,m - 1 };
			for (; ptr.first < n;)
			{
				if (binaryMatrix.get(ptr.first, ptr.second) == 1) // element is 1, move left
				{
					if (ptr.second == 0)
					{
						return 0;
					}
					ptr.second--;
				}
				else // element is 0, move down
				{
					ptr.first++;
				}
			}
			if (ptr.second == m - 1) return -1;
			return ptr.second + 1;
		}
		int leftMostColumnWithOne2(BinaryMatrix& binaryMatrix)
		{
			// Approach: start topright, follow the ones until bottom of matrix is reached
			// Note: challenge definitions: 
			//  ->  (nxm) matrix means m width, n height (contrary to lin.alg. convention)
			//  ->  m[x][y] means element on row x (vertical), position y (horizontal)
			// ->   So, my pointer ptr is defined as pair<x,y>

			const std::vector<size_t> dimension = binaryMatrix.dimensions();
			const int n = dimension[0];
			const int m = dimension[1];
			std::vector<int> markers(n, (int)1e9);
			for (size_t row = 0; row < (size_t)n; row++)
			{
				markers[row] = binsearch(binaryMatrix, row, m);
			}
			auto it = std::min_element(markers.begin(), markers.end());
			if (*it >= m) return -1;
			else return *it;
		}
		int binsearch(BinaryMatrix& M, int row, int width)
		{
			if (width < 1) return 0;
			int lo = 0;
			int hi = width - 1;
			int m = lo + (hi - lo) / 2;
			while (lo <= hi)
			{
				if (M.get(row, m) == 1)
				{
					hi = m - 1;
				}
				else
				{
					lo = m + 1;
				}
				m = lo + (hi - lo) / 2;
			}
			return m;
		}
	};
	void RunExample()
	{
		BinaryMatrix M;
		//M.push({ 0,0,0,1 });
		//M.push({ 0,0,1,1 });
		//M.push({ 0,0,0,1 });
		//M.push({ 0,0,0,1 });
		M.push({ 0,0 });
		M.push({ 0,0 });
		int k = Solution().leftMostColumnWithOne2(M);
	}

}
namespace Apr20_day22
{
	class Solution
	{
	public:
		int subarraySum(std::vector<int>& nums, int k)
		{
			size_t count = 0;
			std::unordered_map<int, size_t> map;
			map[0]++;
			map[nums[0]]++;
			if (nums[0] == k) count++;
			for (size_t i = 1; i < nums.size(); i++)
			{
				nums[i] = nums[i - 1] + nums[i];
				auto it = map.find(nums[i] - k);
				if (it != map.end())
				{
					count += it->second;
				}
				map[nums[i]]++;
			}
			return count;
		}
	};
	void RunExample()
	{
		std::vector<int> nums = { -1,-1,3,1,-1,2 };
		//std::vector<int> nums = { 1,1,2,3,2,1 };
		int ans = Solution().subarraySum(nums, 1);
		std::cout << ans;
	}
}
namespace Apr20_day23
{
	class Solution {
	public:
		int rangeBitwiseAnd(int m, int n) {
			int count = 0;
			std::cout << "m     : "; printBitRep(m);
			std::cout << "n     : "; printBitRep(n);
			while (m != n)
			{
				m >>= 1;
				n >>= 1;
				count++;
			}
			int ans = m << count;
			std::cout << "------------------------------------------------------------------------\n";
			std::cout << "answer: "; printBitRep(ans);
			return ans;
		}
		int rangeBitwiseAnd2(int m, int n) {
			int count = 0;
			int k = m;
			for (int i = m; i <= n; i++)
			{
				k &= i;
				std::cout << "numbers: "; printBitRep(i);
			}
			std::cout << "------------------------------------------------------------------------\n";
			std::cout << "answer : "; printBitRep(k);
			return k;
		}
		void printBitRep(int k)
		{
			int size = sizeof(k);
			int bits = 8 * size;
			std::string str;
			for (int i = bits - 1; i >= 0; i--)
			{
				int mask = 1 << i;
				if ((k & mask) == mask) str.append("1"); else str.append("0");
				if (i % 8 == 0 && i != 0) str.append(".");
			}
			std::cout << "Bin rep: " << str << " for int value = " << k << '\n';
		}
	};
	void RunExample()
	{
		Solution().rangeBitwiseAnd2(32, 35); std::cout << std::endl;
		Solution().rangeBitwiseAnd2(5, 7); std::cout << std::endl;
		Solution().rangeBitwiseAnd2(100012, 100015); std::cout << std::endl;
		Solution().rangeBitwiseAnd(std::numeric_limits<int>::max() / 2, std::numeric_limits<int>::max()); std::cout << std::endl;

	}
}
namespace Apr20_day24
{
	/**
	 * Your LRUCache object will be instantiated and called as such:
	 * LRUCache* obj = new LRUCache(capacity);
	 * int param_1 = obj->get(key);
	 * obj->put(key,value);
	 */
	class LRUCache {
	public:
		LRUCache(int capacity)
			:
			capacity(capacity)
		{}
		int get(int key)
		{
			auto it = map.find(key);
			if (it == map.end())
			{
				return -1;
			}
			else
			{
				turn++;
				it->second.second = turn;
				return it->second.first;
			}
		}
		void put(int key, int value)
		{
			auto it = map.find(key);
			if (it == map.end()) // no entry yet
			{
				if (map.size() < capacity) // enough room, add entry
				{
					turn++;
					map[key] = { value,turn };
				}
				else // map is full, 
				{
					int minfreq = std::numeric_limits<int>::max();
					auto minEntry = map.begin();
					for (auto it = map.begin(); it != map.end(); ++it)
					{
						if (it->second.second < minfreq)
						{
							minfreq = it->second.second;
							minEntry = it;
						}
					}
					map.erase(minEntry);
					turn++;
					map[key] = { value,turn };
				}
			}
			else // adjust existing entry
			{
				turn++;
				it->second = { value,turn };
			}
		}
	private:
		size_t capacity;
		int turn = 0;
		std::unordered_map<int, std::pair<int, int>> map; // valuetype: { value , last extracted }
	};
	void RunExample()
	{
		LRUCache* cache = new LRUCache(2);
		cache->put(2, 1);
		cache->put(1, 1);
		cache->put(2, 3);
		cache->put(4, 1);
		cache->get(1);
		cache->get(2);
	}
}
namespace Apr20_day24b
{
	class LRUCache
	{
		class Node
		{
		public:
			Node(int key, int val) : key(key), val(val) {}
			Node(int key, int val, Node* l, Node* r)
				:
				key(key),
				val(val),
				left(l),
				right(r)
			{}
			//private:
			int key;
			int val;
			Node* left = nullptr;
			Node* right = nullptr;
		};

	private:
		size_t capacity;
		std::unordered_map<int, Node*> cache;
		Node* listfront = nullptr;
		Node* listback = nullptr;
	public:
		LRUCache(int capacity)
			:
			capacity(capacity)
		{}
		int get(int key)
		{
			auto it = cache.find(key);
			if (it != cache.end())
			{
				int val = it->second->val;
				movetoback(key, val);
				return val;
			}
			else
			{
				return -1;
			}
		}
		void put(int key, int val)
		{
			if (cache.find(key) == cache.end())
			{
				pushback(key, val);
			}
			else // value already in cache, but move to back
			{
				movetoback(key, val);

			}
			if (cache.size() > capacity)
			{
				Node* tmp = listfront;
				cache.erase(listfront->key);
				listfront = listfront->right;
				listfront->left = nullptr;
				delete tmp;
				tmp = nullptr;
			}
		}
	private:
		void movetoback(int key, int val)
		{
			Node* tomove = cache[key];
			if (tomove->left == nullptr && tomove->right == nullptr)
			{
				tomove->val = val;
				return;
			}
			if (tomove->left == nullptr) // moving the listfront
			{
				tomove->right->left = nullptr;
				listfront = tomove->right;
			}
			else if (tomove->right == nullptr)
			{
				tomove->left->right = nullptr;
				listback = listback->left;
			}
			else
			{
				tomove->left->right = tomove->right;
				tomove->right->left = tomove->left;
			}
			tomove->right = nullptr;
			tomove->left = listback;
			tomove->val = val;
			listback->right = tomove;
			listback = tomove;

		}
		void pushback(int key, int val)
		{
			Node* tmp = listback;
			listback = new Node(key, val);
			if (tmp == nullptr)
			{
				listfront = listback;
			}
			else
			{
				tmp->right = listback;
				listback->left = tmp;
				tmp = nullptr;
			}
			cache[key] = listback;
		}
	};
	void RunExample()
	{
		LRUCache* cache = new LRUCache(2);
		cache->put(2, 1);
		cache->put(1, 1);
		cache->put(2, 3);
		cache->put(4, 1);
		cache->get(1);
		cache->get(2);
		/*cache->put(1, 1);
		cache->put(2, 2);
		cache->put(3, 3);
		cache->put(4, 4);
		cache->get(4);
		cache->get(3);
		cache->get(2);
		cache->get(1);
		cache->put(5, 5);
		cache->get(1);
		cache->get(2);
		cache->get(3);
		cache->get(4);
		cache->get(5);*/
	}
}
namespace Apr20_day25
{
	class Solution
	{
	public:
		bool canJump(std::vector<int>& nums)
		{
			//return canJumpRecursive(nums, 0);
			//return canJumpStack(nums);
			int lastpos = nums.size() - 1;
			for (int i = nums.size() - 1; i >= 0; i--)
			{
				if (i + nums[i] >= lastpos) lastpos = i;
			}
			return (lastpos == 0);
		}
		bool canJumpStack(std::vector<int>& nums)
		{
			int count = 0;
			std::unordered_set<int> visited;
			std::stack<int> stack;
			stack.push(0);
			while (!stack.empty())
			{
				int i = stack.top(); stack.pop(); count++;
				if (i == nums.size() - 1)
				{
					return true;
				}
				int num = nums[i];
				for (int add = i + 1; add <= num + i && add < (int)nums.size(); add++)
				{
					if (visited.find(add) == visited.end())
					{
						stack.push(add);
						visited.insert(add);
					}
				}
			}
			return false;
		}
		bool canJumpRecursive(std::vector<int>& nums, int start)
		{
			if (nums.size() == 1) return true;
			if (start == nums.size() - 1) return true;
			else
			{

				for (int i = 1; i <= nums[start] && i <= (int)nums.size() - 1 - start; i++)
				{
					if (canJumpRecursive(nums, start + i)) return true;
				}
			}
			return false;
		}
	};
	void RunExample()
	{
		std::vector<int> vec = { 2,3,1,1,4 }; // true
		bool lukt = Solution().canJump(vec);
		vec = { 3,2,1,0,4 }; // fals
		lukt = Solution().canJump(vec);
		vec = { 2,0 }; // true
		lukt = Solution().canJump(vec);
		vec = { 1,2,3 }; // true
		lukt = Solution().canJump(vec);
		vec = { 10,9,8,7,7,5,4,3,2,1,0,0 }; // true
		lukt = Solution().canJump(vec);
		vec = { 2, 0, 6, 9, 8, 4, 5, 0, 8, 9, 1, 2, 9, 6, 8, 8, 0, 6, 3, 1, 2, 2, 1, 2, 6, 5, 3, 1, 2, 2, 6, 4, 2, 4, 3, 0, 0, 0, 3, 8, 2, 4, 0, 1, 2, 0, 1, 4, 6, 5, 8, 0, 7, 9, 3, 4, 6, 6, 5, 8, 9, 3, 4, 3, 7, 0, 4, 9, 0, 9, 8, 4, 3, 0, 7, 7, 1, 9, 1, 9, 4, 9, 0, 1, 9, 5, 7, 7, 1, 5, 8, 2, 8, 2, 6, 8, 2, 2, 7, 5, 1, 7, 9, 6 };
		lukt = Solution().canJump(vec);

	}
}
namespace Apr20_day26
{
	class Solution {
	public:
		void printDP(const std::vector<std::vector<size_t>>& DPP)
		{
			for (size_t i = 0; i < DPP.size(); i++)
			{
				for (size_t j = 0; j < DPP[0].size(); j++)
				{
					std::cout << DPP[i][j] << ", ";
				}
				std::cout << std::endl;
			}
		}
		int longestCommonSubsequence(std::string text1, std::string text2)
		{
			const size_t len1 = text1.size();
			const size_t len2 = text2.size();
			if (len1 == 0 || len2 == 0) return 0;
			std::vector<std::vector<size_t>> DP(len1 + 1, std::vector<size_t>(len2 + 1, 0));
			for (size_t i = 1; i <= len1; i++)
			{
				for (size_t j = 1; j <= len2; j++)
				{
					if (i == 2 && j == 1)
					{
						int k = 0;
					}
					if (text1[i - 1] == text2[j - 1])
					{

						DP[i][j] = std::min(
							std::max(DP[i - 1][j], DP[i][j - 1] + 1),
							DP[i - 1][j - 1] + 1);
					}
					else
					{
						DP[i][j] = std::max(DP[i - 1][j], DP[i][j - 1]);
					}
				}
			}
			printDP(DP);
			return DP[len1][len2];
		}

	};

	void RunExample()
	{
		//std::string str1 = "oxcpqrsvwf";
		//std::string str2 = "shmtulqrypy";
		std::string str1 = "ab";
		std::string str2 = "bab";
		//std::string str1 = "pmjghexybyrgzczy";
		//std::string str2 = "hafcdqbgncrcbihkd";
		//std::string str1 = "ghbrgc";
		//std::string str2 = "hcbgcrcbh";
		//std::string str1 = "bmvcnwrmxccxabkxcvgbozmpspsbnazglyxkpibgzq";
		//std::string str2 = "bmpmlsoylonkvmqyxmnqzconqobacrcbibgzgx";
		int ans = Solution().longestCommonSubsequence(str1, str2);
		std::cout << "ans = " << ans;
	}

}
namespace Apr20_day27
{
	class Solution
	{
	public:
		void PrintM(std::vector<std::vector<char>>& matrix)
		{
			for (auto r : matrix)
			{
				for (auto c : r)
				{
					std::cout << c;
				}
				std::cout << std::endl;
			}
			std::cout << "-------------------" << std::endl;
		}
		int maximalSquare(std::vector<std::vector<char>>& matrix)
		{
			if (matrix.size() == 0) return 0;
			bool hasa1 = false;
			int countouter = 0;
			int countinner = 0;
			do	// approach: sweep the field (1 stay 1 if surrounded by 1's, else decay to zero); 
				//number of sweeps to zero matrix == dimension of largest 1x1 square
			{
				countouter++;
				countinner = 0;
				for (size_t i = 0; i < matrix.size(); i++)
				{
					for (size_t j = 0; j < matrix[0].size(); j++)
					{

						if (matrix[i][j] == '1')
						{
							hasa1 = true;
							if (i == matrix.size() - 1 || j == matrix[0].size() - 1)
							{
								matrix[i][j] = '0';
							}
							else if (matrix[i + 1][j] == '0' || matrix[i][j + 1] == '0' || matrix[i + 1][j + 1] == '0')
							{
								matrix[i][j] = '0';
							}
							else countinner++;
						}
					}
				}
			} while (countinner > 0);
			if (countouter == 1)
			{
				if (hasa1) return 1; else return 0;
			}
			return countouter * countouter;
		}
	};
	void RunExample()
	{
		std::vector<std::vector<char>> M = {
			{'1','0','0','0','0'},
			{'0','1','1','1','0'},
			{'0','1','1','1','0'},
			{'0','1','1','1','0'},
			{'0','0','0','0','0'} };

		std::cout << "ans =" << Solution().maximalSquare(M);
	}
}
namespace Apr20_day27DP
{
	class Solution
	{
	public:
		void PrintM(const std::vector<std::vector<char>>& matrix)
		{
			for (auto r : matrix)
			{
				for (auto c : r)
				{
					std::cout << c;
				}
				std::cout << std::endl;
			}
			std::cout << "-------------------" << std::endl;
		}
		void PrintM(const std::vector<std::vector<int>>& matrix)
		{
			for (auto r : matrix)
			{
				for (auto c : r)
				{
					std::cout << c;
				}
				std::cout << std::endl;
			}
			std::cout << "-------------------" << std::endl;
		}
		int maximalSquare(std::vector<std::vector<char>>& matrix)
		{
			//PrintM(matrix);
			if (matrix.size() == 0) return 0;
			std::vector<std::vector<int>> DP(matrix.size(), std::vector<int>(matrix[0].size(), 0));
			int maxside = 0;
			for (size_t i = 0; i < matrix.size(); i++)
			{
				for (size_t j = 0; j < matrix[0].size(); j++)
				{
					if (matrix[i][j] == '1')
					{
						if (j == 0 || i == 0)
						{
							DP[i][j] = 1;
							if (DP[i][j] > maxside) maxside = DP[i][j];
						}
						else
						{
							DP[i][j] = std::min({ DP[i - 1][j - 1],DP[i][j - 1],DP[i - 1][j] }) + 1;
							if (DP[i][j] > maxside) maxside = DP[i][j];
							//PrintM(DP);

						}
					}
				}
			}
			//PrintM(DP);
			return maxside * maxside;
		}
	};
	void RunExample()
	{
		std::vector<std::vector<char>> M = {
			{'1'} };

		std::cout << "ans =" << Solution().maximalSquare(M);
	}
}
namespace Apr20_day28
{
	/**
	 * Your FirstUnique object will be instantiated and called as such:
	 * FirstUnique* obj = new FirstUnique(nums);
	 * int param_1 = obj->showFirstUnique();
	 * obj->add(value);
	 */
	class FirstUnique {
	private:
		std::unordered_map<int, std::pair<size_t, std::list<int>::iterator>> map;
		std::vector<int> uniques;
		std::list<int> list;

	public:
		FirstUnique(std::vector<int>& nums)
		{
			for (const auto& v : nums)
			{
				int count = ++map[v].first;
				if (count == 1)
				{
					uniques.push_back(v);
				}
				else if (count == 2)
				{
					uniques.erase(std::remove(uniques.begin(), uniques.end(), v), uniques.end());
				}
			}
			for (const auto& v : uniques)
			{
				list.push_back(v);
			}
			for (auto it = list.begin(); it != list.end(); it++)
			{
				map[*it].second = it;
			}
		}

		int showFirstUnique() const
		{
			if (list.size() > 0)
				return list.front();
			else return -1;

		}
		void add(int value)
		{
			auto it = map.find(value);
			if (it == map.end()) // not in the queue
			{
				list.push_back(value);
				map[value] = { 1,std::prev(list.end()) };
			}
			else // already in the queue
			{
				if (it->second.first == 1) // was unique, no longer with this addition
				{
					list.erase(it->second.second);
				}
				map[value].first++;
				map[value].second = list.end();
			}
		}
	};
	class FirstUnique2
	{
	private:
		std::unordered_map<int, int> map;
		std::queue<int> queue;

	public:
		FirstUnique2(std::vector<int>& nums)
		{
			for (const int& v : nums)
			{
				map[v]++;
				queue.push(v);
			}
		}
		int showFirstUnique()
		{
			while (!queue.empty() && map[queue.front()] > 1)
			{
				queue.pop();
			}
			if (queue.empty()) return -1;
			else return queue.front();
		}
		void add(int value)
		{
			if (++map[value] == 1)
			{
				queue.push(value);
			}
		}
	};
	void RunExample()
	{
		std::vector<int> vec = { 2,3,5 };
		FirstUnique2* firstUnique = new FirstUnique2(vec);
		firstUnique->showFirstUnique(); // return 2
		firstUnique->add(5);            // the queue is now [2,3,5,5]
		firstUnique->showFirstUnique(); // return 2
		firstUnique->add(2);            // the queue is now [2,3,5,5,2]
		firstUnique->showFirstUnique(); // return 3
		firstUnique->add(3);            // the queue is now [2,3,5,5,2,3]
		firstUnique->showFirstUnique(); // return -1	
	}
}
namespace Apr20_day29
{
	struct TreeNode {
		int val;
		TreeNode* left;
		TreeNode* right;
		TreeNode() : val(0), left(nullptr), right(nullptr) {}
		TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
		TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
	};
	class Solution {
		//int max = std::numeric_limits<int>::min();
	public:
		int maxPathSum(TreeNode* root)
		{
			int max = INT_MIN;
			MSS(root, max);
			return max;
		}
		int MSS(TreeNode* node, int& max) // max segment sum
		{
			if (!node) return 0;
			const int maxleft = std::max(MSS(node->left, max), 0);
			const int maxright = std::max(MSS(node->right, max), 0);
			max = std::max(max, node->val + maxleft + maxright);
			return node->val + std::max(maxleft, maxright);
		}
	};
	void RunExample()
	{
		TreeNode* root = new TreeNode(-1);
		root->left = new TreeNode(-1);
		root->right = new TreeNode(2, new TreeNode(-1, nullptr, new TreeNode(3)), new TreeNode(1));
		//root->left = new TreeNode(-1);
		//TreeNode* root = new TreeNode(1, new TreeNode(2), new TreeNode(3
		int m = Solution().maxPathSum(root);
	}
}
namespace Apr20_day30
{
	struct TreeNode {
		int val;
		TreeNode* left;
		TreeNode* right;
		TreeNode() : val(0), left(nullptr), right(nullptr) {}
		TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
		TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
	};

	class Solution {
	public:
		bool isValidSequence(TreeNode* root, std::vector<int>& arr)
		{
			//size_t index = 0;
			return isValidSubSeq(root, arr, 0);
		}
		bool isValidSubSeq(TreeNode* node, std::vector<int>& arr, size_t index)
		{
			if (!node) return false;
			if (node->val == arr[index])
			{
				if (index == arr.size() - 1)
				{
					if (node->left == nullptr && node->right == nullptr)
					{
						return true;
					}
					else return false;
				}
				else
				{
					return (isValidSubSeq(node->left, arr, index + 1) || isValidSubSeq(node->right, arr, index + 1));
				}
			}
			else
			{
				return false;
			}
		}

	};
	void RunExample()
	{
		Solution s;
		TreeNode* root = new TreeNode(0, new TreeNode(1), new TreeNode(0));
		root->left->left = new TreeNode(0, nullptr, new TreeNode(1));
		root->left->right = new TreeNode(1, new TreeNode(0), new TreeNode(0));
		root->right->left = new TreeNode(0, nullptr, nullptr);
		std::vector<int> arr1 = { 0, 1, 0, 1 };
		bool test1 = s.isValidSequence(root, arr1); // true
		std::vector<int> arr2 = { 0, 0, 1 };
		bool test2 = s.isValidSequence(root, arr2); // false
		std::vector<int> arr3 = { 0, 1, 1 };
		bool test3 = s.isValidSequence(root, arr3); // false
		std::vector<int> arr4 = { 0, 1, 1, 0 };
		bool test4 = s.isValidSequence(root, arr4); // true
	}
	void RunExample2()
	{
		TreeNode* root = new TreeNode(1);
		std::vector<int> arr1 = { 0 };
		bool test1 = Solution().isValidSequence(root, arr1); // true

	}
}

