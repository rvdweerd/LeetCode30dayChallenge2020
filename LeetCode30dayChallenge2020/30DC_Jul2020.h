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
namespace Jul_day4 // Ugly Number
{
	class Solution {
	public:
		int nthUglyNumber(int n) 
		{
			static size_t p2 = 0, p3 = 0, p5 = 0;
			static std::vector<int> DP(1,1); DP.reserve(n);
			while (DP.size() < n)
			{
				DP.push_back(std::min(DP[p2] * 2, std::min(DP[p3] * 3, DP[p5] * 5)));
				if (DP[p2] * 2 == DP.back() ) p2++;
				if (DP[p3] * 3 == DP.back() ) p3++;
				if (DP[p5] * 5 == DP.back() ) p5++;
				
			}
			return DP[n-1];
		}
	};
	void RunExample()
	{
		int ans = Solution().nthUglyNumber(1690);
	}
}
namespace Jul_day8_duplicates
{
	class Solution {
	public:
		std::vector<std::vector<int>> ans;
		void Check3Sum(std::unordered_map<int,int>& map, int sum, int n, std::vector<int> sofar)
		{
			if (n == 1)
			{
				for (auto it = map.begin(); it != map.end(); it++)
				{
					if (it->second > 0)
					{
						it->second--;
						sofar.push_back(it->first);
						Check3Sum(map, sum + it->first, 2, sofar);
						it->second++;
						sofar.pop_back();
					}
				}
			}
			else
			{
				auto it = map.find(-sum);
				if (it != map.end() && it->second>0)
				{
					sofar.push_back(-sum);
					ans.push_back(sofar);
				}
			}
		}
		std::vector<std::vector<int>> threeSum(std::vector<int>& nums) 
		{
			std::unordered_map<int,int> map;
			for (auto v : nums)
			{
				map[v]++;
			}
			for (auto it = map.begin();it!=map.end();it++)
			{
				it->second--;				
				Check3Sum(map, it->first, 1, { it->first });
				it->second++;
			}
			return std::move(ans);
		}
	};
	void RunExample()
	{
		std::vector<int> nums = { -1,0,1,2,-1,-4 };
		auto ans = Solution().threeSum(nums);
	}
}
namespace Jul_day8 // 3Sum
{
	class Solution {
	public:
		std::vector<std::vector<int>> threeSum(std::vector<int>& nums)
		{
			if (nums.size() < 3) return {};
			std::vector<std::vector<int>> ans;
			std::sort(nums.begin(), nums.end());
			for (int i = 0; i < nums.size() - 2; i++)
			{
				if (i > 0 && nums[i] == nums[i - 1]) continue;
				if (nums[i] > 0) break;
				int l = i + 1; int r = nums.size() - 1;
				while (l < r)
				{
					const int total = nums[l] + nums[r];
					if (total == -nums[i])
					{
						ans.push_back({ nums[i],nums[l],nums[r] });
						while (l < r && nums[l+1] == nums[l]) l++; 
						while (l < r && nums[r-1] == nums[r]) r--;
						l++; r--;
					}
					else if (total < -nums[i])
					{
						while (l < r && nums[l + 1] == nums[l]) l++;
						l++;
					}
					else
					{
						while (l < r && nums[r - 1] == nums[r]) r--;
						r--;
					}
				}
			}
			return std::move(ans);
		}
	};
	void RunExample()
	{
		std::vector<int> nums = { -1,0,1,2,-1,-4 };
		auto ans = Solution().threeSum(nums);
	}
}
namespace Jul_day9 // LC662 Maximum width of binary tree
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
		struct Data
		{
			int l = INT_MAX;
			int r = INT_MIN;
		};
		std::unordered_map<int, Data> map;
		int max_w = 0;
		void traverse(TreeNode* node, int d, int pos)
		{
			if (pos > 1300000000) pos = 1;
			if (!node) return;
			const int L_min = std::min(map[d].l, pos);
			const int R_max = std::max(map[d].r, pos);
			//map[d].l = std::min(map[d].l,pos);
			//map[d].r = std::max(map[d].r,pos);

			map[d].l = L_min;
			map[d].r = R_max;
			max_w = std::max(max_w, R_max - L_min);
			traverse(node->left, d + 1, 2 * pos);
			traverse(node->right, d + 1, 2 * pos + 1);
		}
		int widthOfBinaryTree(TreeNode* root)
		{
			traverse(root, 0, 0);
			int ans = 0;
			//for (auto p:map)
			//{
			//    ans=std::max(ans,p.second.r-p.second.l);
			// }
			//return ans+1;
			return max_w + 1;
		}
	};
	void RunExample()
	{
		TreeNode* root = new TreeNode(1, nullptr, new TreeNode(3));
		root->right->left = new TreeNode(5);
		root->right->right = new TreeNode(3);
		//TreeNode* root = new TreeNode(1, nullptr, new TreeNode(3));
		//root->right->right = new TreeNode(10, new TreeNode(0),nullptr);
		int ans = Solution().widthOfBinaryTree(root);
	}
}
namespace Jul_day10 // Flatten a Multilevel Doubly Linked List
{
	class Node {
	public:
		int val;
		Node* prev;
		Node* next;
		Node* child;
	};
	class Solution {
	public:
		void connectChild(Node* node)
		{
			Node* pReconnect = node->next;
			node->next = node->child;
			node->child = nullptr;
			node->next->prev = node;
			Node* pLastChild = traverse(node->next);
			pLastChild->next = pReconnect;
			if (pReconnect) pReconnect->prev = pLastChild;
		}
		Node* traverse(Node* node)
		{
			if (!node) return nullptr;
			while (true)
			{
				while (node->child == nullptr && node->next != nullptr) node = node->next;
				if (node->child) connectChild(node);
				if (node->next == nullptr) break;
			}
			return node;
		}

		Node* flatten(Node* head)
		{
			traverse(head);
			return head;
		}
	};
}
namespace Jul_day11
{
	class Solution {
	public:
		void fill(std::vector<std::vector<int>>& vec, const std::vector<int>& nums, std::vector<int> sofar, int i)
		{
			if (i == nums.size())
			{
				vec.push_back(sofar);
				return;
			}
			fill(vec, nums, sofar, i + 1);
			sofar.push_back(nums[i]);
			fill(vec, nums, sofar, i + 1);
		}
		std::vector<std::vector<int>> subsets(const std::vector<int>& nums)
		{
			std::vector<std::vector<int>> retVec;
			fill(retVec, nums, {}, 0);
			return std::move(retVec);
		}
	};
	void RunExample()
	{
		auto ans = Solution().subsets({ 1,2,3 });
	}
}
namespace Jul_day12 // Reverse bits
{
	class Solution {
	private:
		std::vector<uint32_t> masks{1u};
	public:
		Solution()
		{
			//masks.push_back(1u);
			for (size_t i = 0; i < 32-1; i++)
			{
				masks.push_back(masks[i] << 1);
			}
		}
		uint32_t reverseBits(uint32_t n) 
		{
			uint32_t ans = 0;
			for (size_t i = 1; n>0; n>>=1, i++)
			{
				if (n & 1) ans |= masks[32-i];
			}
			return ans;
		}
	};
	void RunExample()
	{
		auto ans = Solution().reverseBits(43261596u);
		ans = Solution().reverseBits(4294967293u);
		ans = Solution().reverseBits(0u);

	}
}
namespace Jul_day17 //LC347 Top K Frequent Elements
{
	class Solution
	{
	public:
		std::vector<int> topKFrequent(std::vector<int>& nums, int k)
		{
			std::unordered_map<int, int> map;
			for (auto v : nums)
			{
				map[v]++;
			}
			std::multimap<int, int> mm;
			for (auto it = map.begin(); it != map.end(); ++it)
			{
				mm.insert({ it->second,it->first });
			}
			std::vector<int> vec;
			for (size_t i =0 ; i < k; i++)
			{
				vec.push_back(std::prev(mm.end(), i+1)->second);
			}
			return vec;
		}
	};
	void RunExample()
	{
		std::vector<int> vec;
		std::vector<int> ans;

		vec = { 1,1,1,2,2,3 };
		ans = Solution().topKFrequent(vec,2);

		vec = { 1 };
		ans = Solution().topKFrequent(vec, 1);

		vec = {  };
		ans = Solution().topKFrequent(vec, 0);
	}
}