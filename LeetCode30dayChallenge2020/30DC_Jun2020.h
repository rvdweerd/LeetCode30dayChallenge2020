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