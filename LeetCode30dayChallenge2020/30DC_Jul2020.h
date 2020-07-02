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

namespace Jul_day2
{
	struct TreeNode {
		int val;
		TreeNode *left;
		TreeNode *right;
		TreeNode() : val(0), left(nullptr), right(nullptr) {}
		TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
		TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
	};
	class Solution {
	private:
		std::vector<std::vector<int>> vec;
	public:
		void traverse(TreeNode* n, size_t d) {
			if (!n)	return;
			traverse(n->left, d + 1u);
			traverse(n->right, d + 1u);
			if (vec.size() <= d) vec.resize(d+1u);
			vec[d].push_back(n->val);
		}
		std::vector<std::vector<int>> levelOrderBottom(TreeNode* root) {
			traverse(root, 0u);
			return { vec.crbegin(),vec.crend() };
		}
	};
	void RunExample()
	{
		TreeNode* root = new TreeNode(3, new TreeNode(9), new TreeNode(20));
		root->right->left = new TreeNode(15);
		root->right->right = new TreeNode(7);
		auto ans = Solution().levelOrderBottom(root);
		for (auto v : ans)
		{
			for (auto val : v)
			{
				std::cout << val << ",";
			}
			std::cout << "\n";
		}
	}
}