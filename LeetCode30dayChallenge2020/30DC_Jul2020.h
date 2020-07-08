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