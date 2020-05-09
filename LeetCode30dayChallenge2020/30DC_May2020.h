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


namespace May_day2
{
	class Solution {
	public:
		int numJewelsInStones(std::string J, std::string S)
		{
			std::unordered_set<char> set;
			for (char c : J)
			{
				set.insert(c);
			}
			int count = 0;
			for (char c : S)
			{
				if (set.find(c) != set.end())
					count++;
			}
			return count;
		}


		int numJewelsInStones2(std::string J, std::string S)
		{
			long long map = 0;
			for (char c : J)
			{
				map |= (long long)1 << (c - 'A' + 1);
			}
			int count = 0;
			for (char c : S)
			{
				count += ((map & (long long)1 << (c - 'A' + 1)) > 0);
			}
			return count;
		}
	};
	void RunExample()
	{
		std::string J = "aA";
		std::string S = "aAAbbbb";
		int ans = Solution().numJewelsInStones(J, S);
	}
}
namespace May_day3
{
	class Solution {
	public:
		bool canConstruct(std::string ransomNote, std::string magazine)
		{
			int count[256] = { 0 };
			for (auto c : magazine) count[c]++;
			for (auto c : ransomNote)
			{
				if (--count[c] < 0) return false;
			}
			return true;
		}
	};
	void RunExample()
	{
		std::string note = "aa";
		std::string magazine = "aAAbbbb";
		int ans = Solution().canConstruct(note, magazine);
	}
}
namespace May_day4
{
	class Solution
	{
		unsigned int HighestBit(unsigned int num)
		{
			unsigned int count = 0;
			while (num != 0)
			{
				count++;
				num >>= 1;
			}
			return count;
		}
	public:
		unsigned int findComplement(unsigned int num)
		{
			unsigned mask = 1;
			while (mask < num)
			{
				mask <<= 1;
				mask++;
			}
			return (num ^ mask);
		}
		unsigned int findComplement2(unsigned int num)
		{
			unsigned int digits = HighestBit(num);
			unsigned int inv = ~num;
			inv <<= (32 - digits);
			inv >>= (32 - digits);
			return inv;
		}
	};
	void RunExample()
	{
		unsigned int ans = Solution().findComplement(5);
	}
}
namespace May_day5
{
	class Solution {
	public:
		int firstUniqChar(std::string s) // simple 2-pass
		{
			size_t arr[26] = { 0 };
			for (size_t i = 0; i < s.size(); ++i) arr[s[i] - 'a']++;
			for (size_t i = 0; i < s.size(); ++i)
			{
				if (arr[s[i] - 'a'] == 1) return i;
			}
			return -1;
		}
		int firstUniqChar2(std::string str) // attempt at single run with linked list (easy removal)
		{
			std::list<char> list;
			std::map<char, std::list<char>::iterator> listIterators;
			std::map<char, std::vector<size_t>> charIndices;
			for (size_t i = 0; i < str.size(); ++i)
			{
				const char ch = str[i];
				auto it = listIterators.find(ch);
				if (it == listIterators.end()) // first encounter, add to linked list and maps
				{
					list.push_back(ch);
					listIterators[ch] = { std::prev(list.end()) };
					charIndices[ch].push_back(i);
				}
				else // encountered before
				{
					if (charIndices[ch].size() == 1) // second encounter
					{
						list.erase(it->second);
						charIndices[ch].push_back(i); // this will ensure character is ignored for rest of execution
					}
				}
			}
			if (list.size() > 0) return (int)charIndices.find(list.front())->second[0];
			else return -1;
		}
		int firstUniqChar3(std::string s)
		{
			std::map<char, size_t> map;
			for (auto c : s) map[c]++;
			for (size_t i = 0; i < s.size(); i++)
			{
				if (map[s[i]] == 1) return i;
			}
			return -1;
		}
	};
	void RunExample()
	{
		//std::string str = "loveleetcode";
		std::string str = "aabbcocopppqlwlwrq";
		int ans = Solution().firstUniqChar(str);
	}
}
namespace May_day6
{
	class Solution {
	public:
		int majorityElement(std:: vector<int>& nums) 
		{
			size_t mid = nums.size() / 2;
			std::unordered_map<int, size_t> map;
			for (size_t i = 0; i < nums.size(); i++)
			{
				if (map[nums[i]]++ == mid) return nums[i];
			}
			return -1;
		}
	};
	void RunExample()
	{
		std::vector<int> nums1 = { 2,2,1,1,1,2,2 };
		int ans1 = Solution().majorityElement(nums1);
		std::vector<int> nums2 = { 3,2,3 };
		int ans2 = Solution().majorityElement(nums2);
		std::vector<int> nums3 = { 2 };
		int ans3 = Solution().majorityElement(nums3);
	}
}
namespace May_day7
{
 struct TreeNode 
	{
	int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
	};

	class Solution 
	{
	public:
		std::pair<int, int> pair1 = { 0,-1 };
		std::pair<int, int> pair2 = { 0,-1 };
		bool isCousins(TreeNode* root, int x, int y)
		{
			TestNodes(root, x, y, 0);
			if (pair1.second == -1 || pair2.second == -1) return false;
			if (pair1.first != pair2.first && pair1.second == pair2.second) return true;
			return false;
		}
		void TestNodes(TreeNode* n, int& val1, int& val2, int depth)
		{
			if (n == nullptr) return;
			if (n->left != nullptr)
			{
				if (n->left->val == val1) pair1 = { n->val,depth };
				if (n->left->val == val2) pair2 = { n->val,depth };
			}
			if (n->right != nullptr)
			{
				if (n->right->val == val1) pair1 = { n->val,depth };
				if (n->right->val == val2) pair2 = { n->val,depth };
			}
			TestNodes(n->left, val1, val2, depth + 1);
			TestNodes(n->right, val1, val2, depth + 1);
		}

	};
	void RunExample()
	{
		TreeNode* tree = new TreeNode(1,new TreeNode(2,nullptr,new TreeNode(4)),new TreeNode(3,nullptr, new TreeNode(5)));
		bool ans = Solution().isCousins(tree,5,4);
	}
}
namespace May_day8
{
	class Solution
	{
	public:
		bool checkStraightLine(std::vector<std::vector<int>>& coordinates)
		{
			if (coordinates.size() <= 2) return true;
			const int basevec0 = coordinates[1][0] - coordinates[0][0];
			const int basevec1 = coordinates[1][1] - coordinates[0][1];
			// v1 - v0
			for (size_t i = 2; i < coordinates.size(); i++)
			{
				if ((basevec0 * (coordinates[i][1] - coordinates[0][1]) - basevec1 * (coordinates[i][0] - coordinates[0][0])  ) != 0) 
					// check if crossproduct = 0 (then basevec and checkvec have the same direction)
				{
					return false;
				}
			}
			return true;
		}
	};
	void RunExample()
	{
		std::vector<std::vector<int>> vec = { {1,1},{2,2},{3,4},{4,5},{5,6},{7,7} };
		bool test = Solution().checkStraightLine(vec);
	}
}
namespace May_day9
{
	class Solution {
	public:
		bool isPerfectSquare(int num) 
		{
			long long numL = (long long)num;
			if (num <= 1) return true;
			long long int lo = 0;
			long long int hi = 1;
			while (hi * hi < numL)
			{
				lo = hi;
				hi = hi + lo/2+1;
			}
			while (lo <= hi)
			{
				long long int mid = lo + (hi - lo) / 2;
				long long int sq = mid * mid;
				if (sq == numL) return true;
				if (sq < numL) lo = mid + 1;
				else hi = mid - 1;
			}
			return false;
		}

	};
	void RunExample()
	{
		bool ans = Solution().isPerfectSquare(2147483647);
		ans = Solution().isPerfectSquare(16);
		ans = Solution().isPerfectSquare(15);
	}
}