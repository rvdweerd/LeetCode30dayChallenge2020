#pragma once
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

namespace Jun_day1 // LC226 Invert Binary Tree
{
	/**
	* Definition for a binary tree node.*/
	struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
	 };
	class Solution {
	public:
		void Traverse_LeftFirst_pre(TreeNode* tree)
		{
			if (tree == nullptr) return;
			std::cout << tree->val << ", ";
			Traverse_LeftFirst_pre(tree->left);
			Traverse_LeftFirst_pre(tree->right);
			return;
		}
		void Traverse_LeftFirst_in(TreeNode* tree)
		{
			if (tree == nullptr) return;
			Traverse_LeftFirst_in(tree->left);
			std::cout << tree->val << ", ";
			Traverse_LeftFirst_in(tree->right);
			return;
		}
		void Traverse_LeftFirst_post(TreeNode* tree)
		{
			if (tree == nullptr) return;
			Traverse_LeftFirst_post(tree->left);
			Traverse_LeftFirst_post(tree->right);
			std::cout << tree->val << ", ";
			return;
		}
		void Traverse_RightFirst_pre(TreeNode* tree)
		{
			if (tree == nullptr) return;
			std::cout << tree->val << ", ";
			Traverse_RightFirst_pre(tree->right);
			Traverse_RightFirst_pre(tree->left);
			return;
		}
		void Traverse_RightFirst_in(TreeNode* tree)
		{
			if (tree == nullptr) return;
			Traverse_RightFirst_in(tree->right);
			std::cout << tree->val << ", ";
			Traverse_RightFirst_in(tree->left);
			return;
		}
		void Traverse_RightFirst_post(TreeNode* tree)
		{
			if (tree == nullptr) return;
			Traverse_RightFirst_post(tree->right);
			Traverse_RightFirst_post(tree->left);
			std::cout << tree->val << ", ";
			return;
		}
		void PrintAllOrders(TreeNode* root)
		{
			std::cout << "Left first, pre-order:\n";
			Traverse_LeftFirst_pre(root); std::cout << "\n";
			std::cout << "Left first, in-order:\n";
			Traverse_LeftFirst_in(root); std::cout << "\n";
			std::cout << "Left first, post-order:\n";
			Traverse_LeftFirst_post(root); std::cout << "\n";

			std::cout << "--------------------------------\n";
			std::cout << "Right first, pre-order:\n";
			Traverse_RightFirst_pre(root); std::cout << "\n";
			std::cout << "Right first, in-order:\n";
			Traverse_RightFirst_in(root); std::cout << "\n";
			std::cout << "Right first, post-order:\n";
			Traverse_RightFirst_post(root); std::cout << "\n";
		}
		TreeNode* ConstructBSTFromPreOrder(const std::vector<int>& vec)
		{
			TreeNode* root = new TreeNode(vec[0]);
			std::stack<TreeNode*> stack;
			stack.push(root);

			for (size_t i = 1; i < vec.size(); i++)
			{
				if (vec[i] < stack.top()->val)
				{
					stack.top()->left = new TreeNode(vec[i]);
					stack.push(stack.top()->left);
				}
				else
				{
					TreeNode* p = stack.top();
					while (!stack.empty() && vec[i] > stack.top()->val)
					{
						p = stack.top();
						stack.pop();
					}
					p->right = new TreeNode(vec[i]);
					stack.push(p->right);
				}
			}
			
			return root;
		}
		void visitAndInvert(TreeNode* tree)
		{
			if (tree)
			{
				// swap the pointers of the children of this node
				TreeNode* temp = tree->left;
				tree->left = tree->right;
				tree->right = temp;
				// recurively visit the children
				visitAndInvert(tree->left);
				visitAndInvert(tree->right);
			}
		}
		TreeNode* invertTree(TreeNode* root) 
		{
			visitAndInvert(root);
			return root;
		}
	};
	void RunExample()
	{
		TreeNode* bl = new TreeNode(2, new TreeNode(1), new TreeNode(3));
		TreeNode* br = new TreeNode(7, new TreeNode(6), new TreeNode(9));
		TreeNode* root = new TreeNode(4, bl, br); bl = nullptr; br = nullptr;
		TreeNode* root_inv = Solution().invertTree(root);
	}
}
namespace Jun_day5 // LC528 Random Pick With Weight
{
	class Solution {
	private:
		std::random_device rd;
		std::mt19937 rng;
		std::uniform_int_distribution<int> cDistr;
		std::vector<int> distribution;
	public:
		Solution(std::vector<int>& w)
			:
			rng(rd()),
			distribution(w.size())
		{
			//distribution.resize(w.size(),0);
			distribution[0] = w[0];
			for (size_t i = 1; i < w.size(); i++)
			{
				distribution[i] = distribution[i - 1] + w[i];
			}
			cDistr = std::uniform_int_distribution<int>(1, distribution.back());
		}
		int pickIndex() 
		{
			int X = cDistr(rng);
			int l = 0;
			int h = distribution.size()-1;
			while (h >= l)
			{
				int m = l + (h - l) / 2;
				if (distribution[m] < X)
				{
					l = m + 1;
				}
				else
				{
					h = m - 1;
				}
			}
			return l;
		}
	};

	/**
	 * Your Solution object will be instantiated and called as such:
	 * Solution* obj = new Solution(w);
	 * int param_1 = obj->pickIndex();
	 */
	void RunExample()
	{
		std::vector<int> w = { 10,10,50,10,10,10 };
		Solution* obj = new Solution(w);
		int avg = 0;
		for (size_t i = 0; i < 1e7; i++)
		{
			avg += obj->pickIndex();
		}
		float Avg = (float)avg / 1e7f;
	}
}
namespace Jun_day6 // LC406 Queue reconstruction by height
{
	void PrintVec(std::vector<std::vector<int>> vec)
	{
		for (auto v : vec)
		{
			std::cout << "[" << v[0] << "," << v[1] << "],";
		}
		std::cout << "\n======================================\n";
	}
	class Solution {
	public:
		std::vector<std::vector<int>> reconstructQueue_vec(std::vector<std::vector<int>>& people) // vector as data structure is slow (many inserts)
		{
			if (people.size() == 0) return {};
			std::cout << "Original    : "; PrintVec(people);
			std::sort(people.begin(), people.end(), [](std::vector<int> p1, std::vector<int> p2) 
				{ 
					if (p1[0] == p2[0])
					{
						return p1[1] < p2[1];
					}
					else
					{
						return p1[0] > p2[0];
					}
				}
			);
			std::cout << "Initial sort: "; PrintVec(people);
			std::vector<std::vector<int>> sorted; sorted.reserve(people.size());
			sorted.push_back(people[0]);
			for (size_t i = 1; i < people.size(); i++)
			{
				auto it = sorted.begin() + people[i][1];
				sorted.insert(it, people[i]);
			}
			std::cout << "Sorted      : "; PrintVec(sorted);
			std::cout << "===========================================\n";
			return sorted;
		}
		std::vector<std::vector<int>> reconstructQueue(std::vector<std::vector<int>>& people) // linked list implementation
		{
			if (people.size() == 0) return {};
			std::sort(people.begin(), people.end(), [](std::vector<int> p1, std::vector<int> p2)
				{
					if (p1[0] == p2[0])
					{
						return p1[1] < p2[1];
					}
					else
					{
						return p1[0] > p2[0];
					}
				}
			);
			std::list<std::vector<int>> list;
			list.push_back(people[0]);
			for (size_t i = 1; i < people.size(); i++)
			{
				auto it = std::next(list.begin(),people[i][1]);
				list.insert(it, people[i]);
			}
			return { list.begin(),list.end() };
		}
	};
	void RunExample()
	{
		std::vector<std::vector<int>> vec;
		std::vector<std::vector<int>> ans;
		
		vec = { {7, 0}, {4, 4}, {7, 1}, {5, 0}, {6, 1}, {5, 2} };
		ans = Solution().reconstructQueue(vec);

		vec = { {9, 0}, {7, 0}, {1, 9}, {3, 0}, {2, 7}, {5, 3}, {6, 0}, {3, 4}, {6, 2}, {5, 2} };
		ans = Solution().reconstructQueue(vec); // [[3,0],[6,0],[7,0],[5,2],[3,4],[5,3],[6,2],[2,7],[9,0],[1,9]]

	}
}
namespace Jun_day7 // LC Coin Change 2
{
	class Solution {
	private:
	public:
		int changeHelper(int amount, std::vector<int>& coins, size_t i, std::vector<std::vector<int>>& DP)
		{
			if (DP[amount][i] != -1) return DP[amount][i];
			int n = 0;
			if (amount == 0) return 1;
			else if (i == 0)
			{
				return amount % coins[0] == 0 ? 1 : 0;
			}
			else
			{
				for (int p = 0; p <= amount; p += coins[i])
				{
					int increment = changeHelper(amount - p, coins, i - 1,DP);
					//DP[amount][i] = increment;
					n += increment;
				}
			}
			DP[amount][i] = n;
			return n;
		}
		int change(int amount, std::vector<int>& coins) 
		{
			if (amount == 0) return 1;
			if (coins.size() == 0) return 0;
			std::vector<std::vector<int>> DP = std::vector<std::vector<int>>(amount+1, std::vector<int>(coins.size(), -1));
			return changeHelper(amount, coins, coins.size() - 1, DP);
		}
	};
	void RunExample()
	{
		std::vector<int> coins;
		int amount;
		int ans;

		coins = { 1,2,5 };
		amount = 5;
		ans = Solution().change(amount, coins); // 4

		coins = { 2 };
		amount = 3;
		ans = Solution().change(amount, coins); // 0

		coins = { 10 };
		amount = 10;
		ans = Solution().change(amount, coins); // 1

		coins = { 3,5,7,8,9,10,11 };
		amount = 1000;
		ans = Solution().change(amount, coins); // 1

	}
}