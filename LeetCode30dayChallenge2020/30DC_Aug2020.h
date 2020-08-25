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
#include <string>
#include "GraphClass.h"
#include <algorithm>
#include <random>

namespace Aug_day5
{
	class WordDictionary
	{
		struct Node
		{
			Node()
				:
				vec(27)
			{}
			std::vector<Node*> vec;
		};
		Node* root = new Node;
	public:
		void addWord(std::string&& word)
		{
			Node* ptr = root;
			for (char ch : word)
			{
				if (ptr->vec[ch - 'a']) ptr = ptr->vec[ch - 'a'];
				else
				{
					Node* newNode = new Node;
					ptr->vec[ch - 'a'] = newNode;
					ptr = ptr->vec[ch - 'a'];
				}
			}
			ptr->vec[26] = root;
		}
		bool match(std::string& word)
		{
			return matchRemaining(word,0,root);
		}
		bool matchRemaining(std::string& word, size_t n,Node* ptr)
		{
			for (size_t i = n; i < word.size(); i++)
			{
				if (word[i] == '.')
				{
					for (size_t index = 0; index < 26; index++)
					{
						if (ptr->vec[index])
						{
							if (matchRemaining(word, i+1, ptr->vec[index])) return true;
						}
					}
					return false;
				}
				else if (ptr->vec[word[i] - 'a']) ptr = ptr->vec[word[i] - 'a'];
				else return false;
			}
			if (ptr->vec[26]) return true;
			return false;
		}
		/** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
		bool search(std::string&& word) 
		{
			return matchRemaining(word,0,root);
		}
	};
	void RunExample()
	{
		WordDictionary dict;
		dict.addWord("a");
		bool a = false;
		a = dict.search("a");
		a = dict.search("aa");
		a = dict.search(".");
		a = dict.search(".a");
		a = dict.search("a.");
		a = dict.search("..");

		return;

	}
}
namespace Aug_day6
{
	class Solution {
		int tmp;
		int n;
	public:
		std::vector<int> findDuplicates(std::vector<int>& nums)
		{
			std::vector<int> out;
			for (size_t i = 0; i < nums.size(); i++)
			{
				if (nums[i] > 0)
				{
					n = nums[i];
					nums[i] = 0;
					while (nums[n - 1] > 0)
					{
						tmp = nums[n - 1];
						nums[n - 1] = -1;
						n = tmp; 
					}
					if (nums[n - 1]--==-1) out.push_back(n);
				}
			}
			return std::move(out);
		}
	};
	void RunExample()
	{
		std::vector<int> nums;
		std::vector<int> ans;
		nums = { 4,3,2,7,8,2,3,1 };
		ans = Solution().findDuplicates(nums); //{2,3}

		nums = { 1,1 };
		ans = Solution().findDuplicates(nums); // {1}

		nums = { 1 };
		ans = Solution().findDuplicates(nums); // {}

		nums = { };
		ans = Solution().findDuplicates(nums); // {}
	}
}
namespace Aug_day7
{
	struct TreeNode 
	{
		int val;
		TreeNode* left;
		TreeNode* right;
		TreeNode() : val(0), left(nullptr), right(nullptr) {}
		TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
		TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
	};
	class Solution {
		std::map<int, std::map<int, std::set<int, std::less<int>>, std::greater<int>>, std::less<int>> grid;
		void Traverse(TreeNode* node, int X, int Y)
		{
			if (node)
			{
				grid[X][Y].insert(node->val);
				Traverse(node->left, X - 1, Y - 1);
				Traverse(node->right, X + 1, Y - 1);
			}
		}
	public:
		std::vector<std::vector<int>> verticalTraversal(TreeNode* root) {
			Traverse(root, 0, 0);
			//std::cout<<grid.size();
			std::vector<std::vector<int>> out;
			for (auto x_map : grid)
			{
				std::vector<int> subvec;
				for (auto y_map : x_map.second)
				{
					for (int v : y_map.second)
					{
						subvec.push_back(v);
					}
				}
				out.push_back(subvec);
			}


			return out;
		}
	};
	void RunExample()
	{
		TreeNode* root = new TreeNode(3);
		root->left = new TreeNode(9);
		root->right = new TreeNode(20, new TreeNode(15), new TreeNode(7));
		//root->left = new TreeNode(-1);
		//TreeNode* root = new TreeNode(1, new TreeNode(2), new TreeNode(3
		auto ans = Solution().verticalTraversal(root);
	}
}
namespace Aug_day8
{
	struct TreeNode
	{
		int val;
		TreeNode* left;
		TreeNode* right;
		TreeNode() : val(0), left(nullptr), right(nullptr) {}
		TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
		TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
	};
#include <iterator>
	class Solution 
	{
	private:
		std::unordered_map<int,std::multiset<int>> remainders;
		int count = 0;
		int sum;
		void Traverse(TreeNode* node, int d)
		{
			if (node)
			{
				if (sum - node->val == 0)
				{
					count++;
				}
				count += remainders[d].count(node->val);
				
				std::transform(remainders[d].begin(), remainders[d].end(), std::inserter(remainders[d + 1], remainders[d + 1].end()), [node](int v) {return v - node->val; });
				remainders[d+1].insert(sum - node->val);
							
				Traverse(node->left,d+1);
				Traverse(node->right,d+1);
				remainders[d + 1].clear();
			}
		}
		int ans;
		void helper(TreeNode* root, int sum, std::vector<int>& curr)
		{
			if (!root)
				return;
			curr.push_back(root->val);
			int temp = 0;
			for (int i = curr.size() - 1; i >= 0; i--)
			{

				temp += curr[i];
				if (temp == sum)
					ans++;


			}
			helper(root->left, sum, curr);
			helper(root->right, sum, curr);
			curr.pop_back();
		}
	public:
		int pathSum(TreeNode* root, int sum) {
			ans = 0;
			std::vector<int> curr;
			helper(root, sum, curr);
			return ans;
		}
		int pathSum2(TreeNode* root, int s) 
		{
			sum = s;
			Traverse(root,0);
			return count;
		}
	};
	void RunExample()
	{
		TreeNode* root1 = new TreeNode(10);
		root1->left = new TreeNode(5);
		root1->right = new TreeNode(-3, nullptr, new TreeNode(11));
		root1->left->left = new TreeNode(3, new TreeNode(3), new TreeNode(-2));
		root1->left->right = new TreeNode(2, nullptr, new TreeNode(1));
		auto ans1 = Solution().pathSum(root1, 8); //3

		TreeNode* root2 = new TreeNode(-2,nullptr,new TreeNode(-3));
		auto ans2 = Solution().pathSum(root2, -5); //1

		TreeNode* root3 = new TreeNode(0, new TreeNode(1), new TreeNode(1));
		auto ans3 = Solution().pathSum(root3, 1); //4

		TreeNode* root4 = new TreeNode(1);
		auto ans4 = Solution().pathSum(root4, 1); //1

		TreeNode* root5 = new TreeNode(0); root5->left = root3;
		auto ans5 = Solution().pathSum(root5, 1); //6

		TreeNode* root6 = new TreeNode(1);
		root6->left = new TreeNode(-2, new TreeNode(1), nullptr);
		root6->left->left->left = new TreeNode(-1);
		auto ans6 = Solution().pathSum(root6, 0); //2

		TreeNode* root7 = new TreeNode(1);
		root7->left = new TreeNode(-2, new TreeNode(1), new TreeNode(3));
		root7->left->left->left = new TreeNode(-1);
		root7->right = new TreeNode(-3, new TreeNode(-2), nullptr);
		auto ans7 = Solution().pathSum(root7, -2); //4


	}
}
namespace Aug_day9
{
	class Solution {
	private:
		struct Pos
		{
			size_t y;
			size_t x;
			int count;
		};
		std::queue<Pos> queue;
		int nOranges = 0;
		int time = 0;
		void Initialize(std::vector<std::vector<int>>& grid)
		{
			for (size_t row = 0; row < grid.size(); row++)
			{
				for (size_t col = 0; col < grid[0].size(); col++)
				{
					if (grid[row][col] > 0)
					{
						nOranges++;
						if (grid[row][col] == 2)
						{
							queue.push({row,col,0});
						}
					}

				}
			}
		}
		void ContaminateNeighbors(Pos& pos, std::vector<std::vector<int>>& grid)
		{
			bool success = false;
			if (pos.y > 0 && grid[pos.y - 1][pos.x] == 1)
			{
				queue.push({ pos.y - 1,pos.x,pos.count + 1 });
				grid[pos.y - 1][pos.x] = 2;
				success = true;
			}
			if (pos.y < grid.size() - 1 && grid[pos.y + 1][pos.x] == 1)
			{
				queue.push({ pos.y + 1,pos.x,pos.count + 1 });
				grid[pos.y + 1][pos.x] = 2;
				success = true;
			}
			if (pos.x > 0 && grid[pos.y][pos.x - 1] == 1)
			{
				queue.push({ pos.y,pos.x - 1,pos.count + 1 });
				grid[pos.y][pos.x-1] = 2;
				success = true;
			}
			if (pos.x < grid[0].size() - 1 && grid[pos.y][pos.x + 1] == 1)
			{
				queue.push({ pos.y,pos.x + 1,pos.count + 1 });
				grid[pos.y][pos.x + 1] = 2;
				success = true;
			}
			if (!success) time = pos.count;
		}
	public:
		int orangesRotting(std::vector<std::vector<int>>& grid) 
		{
			Initialize(grid);
			while (!queue.empty())
			{
				Pos curPos = queue.front(); queue.pop();
				nOranges--;
				ContaminateNeighbors(curPos, grid);
			}
			if (nOranges == 0) return time;
			return -1;
		}
	};
	void RunExample()
	{
		std::vector<std::vector<int>> grid;
		int ans;

		grid = { {2,1,1},{1,1,0},{0,1,1} };
		ans = Solution().orangesRotting(grid); //4

		grid = { {2,1,1},{0,1,1},{1,0,1} };
		ans = Solution().orangesRotting(grid); //-1

		grid = { {0,2} };
		ans = Solution().orangesRotting(grid); //0
	}
}