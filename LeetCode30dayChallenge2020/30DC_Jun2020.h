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
#include <regex>

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
namespace Jun_day7 // LC518 Coin Change 2
{
	class Solution {
	private:
	public:
		int changeHelper_Recursive(int amount, std::vector<int>& coins, size_t i, std::vector<std::vector<int>>& cache)
		{
			if (cache[amount][i] != -1) return cache[amount][i];
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
					n += changeHelper_Recursive(amount - p, coins, i - 1, cache);
				}
			}
			cache[amount][i] = n;
			return n;
		}
		int change(int amount, std::vector<int>& coins) 
		{
			if (amount == 0) return 1;
			if (coins.size() == 0) return 0;
			
			// Recursive solution with memoization
			//std::vector<std::vector<int>> cache = std::vector<std::vector<int>>(amount+1, std::vector<int>(coins.size(), -1));
			//return changeHelper_Recursive(amount, coins, coins.size() - 1, cache);

			// DP table soluton (O(n*amount))
			std::vector<std::vector<int>> DP = std::vector<std::vector<int>>(coins.size()+1, std::vector<int>(amount+1));
			for (size_t row = 1; row <= coins.size(); row++) DP[row][0] = 1;
			for (size_t row = 1; row <= coins.size(); row++)
			{
				for (size_t col = 1; col <= (size_t)amount; col++)
				{
					if (col >= (size_t)coins[row - 1])
					{
						DP[row][col] = DP[row - 1][col] + DP[row][col - coins[row - 1]];
					}
					else
					{
						DP[row][col] = DP[row - 1][col];
					}
				}
			}
			return DP.back().back();
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
		ans = Solution().change(amount, coins); // 1952879228
	}
}
namespace Jun_day8
{
	class Solution {
	public:
		bool isPowerOfTwo_shifts(int n)
		{
			if (n <= 0) return false;
			while ( (n & 1) != 1)
			{
				n >>= 1;
			}
			return n == 1;
		}
		bool isPowerOfTwo(int n)
		{
			return (n>0 && ( (n-1) & n ) == 0 );
		}
	};
	void RunExample()
	{
		bool ans;
		ans = Solution().isPowerOfTwo(0); // false
		ans = Solution().isPowerOfTwo(1);
		ans = Solution().isPowerOfTwo(16); 
		ans = Solution().isPowerOfTwo(218); //false
		
	}
}
namespace Jun_day9
{
	class Solution {
	public:
		bool isSubsequence(std::string s, std::string t) 
		{
			if (s.size() == 0) return true;
			if (t.size() == 0) return false;
			for (size_t it1 = 0, it2 = 0; it2 < t.size(); it2++)
			{
				if (s[it1] == t[it2])
				{
					if (it1 == s.size() - 1) return true;
					else it1++;
				}
			}
			return false;
		}
	};
	void RunExample()
	{
		std::string s;
		std::string t;
		bool ans;

		s = "abc";
		t = "ahbgdc";
		ans = Solution().isSubsequence(s, t);

		s = "axc";
		t = "ahbgdc";
		ans = Solution().isSubsequence(s, t);


	}
}
namespace Jun_day11 // LC Sort Colors
{
	class Solution 
	{
	public:
		void sortColors(std::vector<int>& nums) 
		{
			int LL = -1; // pointer to LastLow entry
			int FH = nums.size(); // pointer to LastHigh entry
			int D = 0; // director pointer, traverses the array
			while (D < FH )
			{
				if (nums[D] == 2) // director observes a high entry
				{
					std::swap(nums[D], nums[FH - 1]);
					FH--;
					//while (nums[FH-1]==2) FH--;
				}
				else if (nums[D] == 0) // director observes a low entry
				{
					if (nums[LL + 1] > 0)
					{
						std::swap(nums[LL+1],nums[D]);
					}
					LL++;
					D++;
				}
				else // (nums[D] == 1) no swaps, director continues
				{
					D++;
				}
			}

		}
	};
	void RunExample()
	{
		std::vector<int> vec;
		
		vec = { 2,0,2,1,1,2 };
		Solution().sortColors(vec);

		vec = { 2,0,2,1,0,2,1,2,2,0,1,0 };
		Solution().sortColors(vec);

		vec = { 0,0,0 };
		Solution().sortColors(vec);

		vec = { 1,1,1 };
		Solution().sortColors(vec);

		vec = { 2,2,2 };
		Solution().sortColors(vec);

		vec = { };
		Solution().sortColors(vec);

		vec = { 1 };
		Solution().sortColors(vec);
		
		vec = { 2 };
		Solution().sortColors(vec);
	}
}
namespace Jun_day13 // LC368 largest divisible subset
{
	class Solution 
	{
		std::map<size_t, std::vector<int>> map;
	public:
		void findN(std::vector<int>& nums, int i, std::vector<int>& path) // helper function for the recursive solution 
		{
			if (i >= (int)nums.size()) return;
			bool isDiv = true;
			for (auto v : path)
			{
				if (nums[i] % v != 0)
				{
					isDiv = false;
					break;
				}
			}
			
			if (isDiv)
			{
				path.push_back(nums[i]);
				findN(nums, i + 1, path);
				map.insert({ path.size(), path });
				path.pop_back();
			}
			findN(nums, i + 1, path);
			map.insert({ path.size(), path });
			
			return;
		}
		int nDivisibleSubset(std::vector<int>& nums) // recursive solution (not optimal)
		{
			std::sort(nums.begin(), nums.end());
			std::vector<int> p = {};
			findN(nums, 0, p);
			return 0;
		}
		std::vector<int> largestDivisibleSubset(std::vector<int>& nums) // Iterative (DP) solution
		{
			if (nums.size() <= 1) return nums;
			std::pair<int, int> max = { 1,0 }; // pointer to maximum solution. first entry: max, second entry: highest value in nums that is part of solution
			std::sort(nums.begin(), nums.end());
			std::vector<std::pair<int, int>> DP(nums.size(), { 1,-1 }); // first entry: max # of entries, seccond entry: link to first smaller modular value
			for (int i = 1; i < (int)nums.size(); i++) 
			{
				for (int j = i-1; j >=0 ; j--) // loop trough the DP table, from high to low entries
				{
					if (nums[i] % nums[j] == 0) 
					{
						if (DP[j].first >= DP[i].first) // there is a previous entry in DP with a equal or higher maximum 
						{
							DP[i].first = DP[j].first + 1;
							DP[i].second = j; // point to the previous entry (in order to reconstruct path to maximum later)
							if (DP[i].first > max.first) // update pointer to maximum solution
							{
								max.first = DP[i].first;
								max.second = i;
							}
							if (DP[j].second != -1) j = DP[j].second;
						}
					}
				}
			}
			std::vector<int> ans;
			do
			{
				ans.push_back(nums[max.second]);
				max.second = DP[max.second].second;
			} while (max.second != -1);

			return ans;

		}
	};
	void RunExample()
	{
		std::vector<int> vec;
		std::vector<int> ans;
		int n = 0;
		//vec = { 1,2,3 };
		////ans = Solution().largestDivisibleSubset(vec);
		//n = Solution().nDivisibleSubset(vec);

		//vec = { 1,2,4,8 };
		////ans = Solution().largestDivisibleSubset(vec);
		//n = Solution().nDivisibleSubset(vec);

		//vec = { 1,2,3,6,9,12,5,10,20 };
		//ans = Solution().largestDivisibleSubset(vec);
		//n = Solution().nDivisibleSubset(vec);
		
		//vec = { 3,6,10,12,20 };
		//ans = Solution().largestDivisibleSubset(vec);
		//ans = Solution().largestDivisibleSubset(vec);

		//vec = { 4,8,10,240 };
		//ans = Solution().largestDivisibleSubset(vec);
		//ans = Solution().largestDivisibleSubset(vec);

		//vec = { 7,18,54,70,90,140 };
		vec = { 832,33,531,416,335,298,365,352,582,936,366,305,930,530,97,349,71,295,840,108,299,804,925,627,953,571,658,732,429,136,563,462,666,330,796,315,695,500,896,982,217,200,912,98,297,612,169,943,628,593,959,904,219,240,857,789,897,940,569,384,502,382,401,184,716,230,29,963,211,597,515,122,163,86,215,105,889,842,49,847,267,87,954,407,245,975,719,746,709,471,281,238,186,510,618,149,73,214,663,194,260,825,631,474,519,668,329,718,765,947,156,353,490,962,679,560,59,387,31,692,976,568,201,273,159,730,819,418,906,801,892,672,559,866,389,675,812,744,164,737,57,195,115,933,158,909,598,359,853,314,983,11,395,153,781,301,838,625,704,256,351,996,225,644,521,509,674,417,272,622,937,723,632,331,228,412,181,435,469,157,368,524,38,132,325,420,127,731,771,604,505,634,67,374,894,3,448,878,686,641,316,207,76,363,795,235,770,446,820,493,177,816,615,410,117,944,829,190,831,289,516,964,170,134,671,885,682,119,402,82,485,901,375,68,858,739,56,974,683,884,815,872,715,104,290,348,588,834,788,472,466,867,550,779,65,802,459,440,870,753,608,808,623,642,44,437,865,758,540,506,691,958,854,546,39,595,369,504,63,311,722,441,786,899,338,651,874,946,811,848,939,284,824,309,653,133,514,460,678,54,399,759,468,61,480,783,266,900,400,237,403,534,213,914,473,198,380,373,288,154,844,535,409,249,285,168,69,345,647,851,846,264,102,246,106,648,576,212,438,981,987,379,360,667,95,172,101,580,891,385,747,161,927,361,818,657,171,342,232,734,714,362,425,475,28,41,551,142,131,51,229,9,607,326,522,687,792,845,665,358,91,720,155,565,99,26,650,539,780,589,950,935,372,227,424,750,833,554,841,552,60,757,430,916,140,790,426,776,96,199,923,806,949,755,711,659,911,611,310,774,265,880,690,706,761,286,255,756,204,444,478,601,529,669,241,784,566,528,208,270,511,236,271,378,58,453,467,233,250,567,296,932,989,367,626,35,162,887,572,603,564,797,280,406,970,689,408,431,638,489,85,50,357,803,47,555,793,422,763,110,869,861,253,320,538,347,405,769,64,875,630,537,328,553,166,948,303,160,800,507,920,922,90,693,636,17,455,183,210,856,762,656,174,873,579,176,688,640,1,938,902,341,740,581,427,111,972,443,22,791,304,574,575,725,477,700,817,381,479,248,121,411,547,182,871,599,203,13,224,541,724,178,775,388,4,251,321,52,88,100,279,614,839,84,151,735,40,752,773,376,77,476,708,396,988,961,24,231,445,609,952,965,986,414,451,881,42,257,32,334,130,596,527,94,333,317,244,960,710,852,862,421,81,37,452,274,187,268,520,491,778,18,743,620,145,72,370,118,748,633,997,436,143,573,495,180,34 };
		//ans = Solution().largestDivisibleSubset(vec);
		ans = Solution().largestDivisibleSubset(vec);

	}
}
namespace Jun_day14 // LC787 Cheapest Flights with K stops
{
	class Solution {
	private:
		std::unordered_map<int, std::vector<std::vector<int>>> gMap; // Graph representation in a map
		void FillGraph(const std::vector<std::vector<int>>& flights)
		{
			for (auto v : flights)
			{
				gMap[v[0]].push_back({ v[1],v[2] });
			}
		}
	public:
		int findCheapestPrice(int n, const std::vector<std::vector<int>>& flights, int src, int dst, int K) 
		// Dijkstra's algo
		{
			FillGraph(flights);
			struct GreaterPathCost // This is the comparator for the priotity queue definition
			{
				bool operator()(const std::pair<std::vector<int>, int>& lhs, const std::pair<std::vector<int>, int>& rhs) const
				{
					return (lhs.second > rhs.second);
				}
			};
			std::priority_queue <
					std::pair<std::vector<int>, int>,
					std::vector<std::pair<std::vector<int>, int>>,
					GreaterPathCost
				> pqueue;
			std::set<int> visited;
			pqueue.push({ {src},0 });
			
			while (!pqueue.empty())
			{
				std::pair<std::vector<int>, int> current = pqueue.top(); pqueue.pop();
				if (current.first.back() == dst && (int)current.first.size() - 2 <= K) // Terminator condition for success
				{
					return current.second;
				}
				else
				{
					visited.insert(current.first.back());
				}
				std::vector<std::vector<int>> destinations = gMap[current.first.back()];
				for (std::vector<int> d : destinations)
				{
					if (visited.find(d[0]) == visited.end() || (int)current.first.size()-1 <= K) // destination not yet visited, or stopovers left
					{
						current.first.push_back(d[0]); current.second += d[1]; // add new destination to path...
						pqueue.push(current); 
						current.first.pop_back(); current.second -= d[1]; // ...and remove it for next flight option(s)
					}
				}
			}
			return -1;
		}
	};
	void RunExample()
	{
		std::vector<std::vector<int>> flights;
		int ans;

		//flights = { {0,1,100},{1,2,100},{0,2,500} };
		//ans = Solution().findCheapestPrice(3, flights, 0, 2, 1);

		//flights = { {0,1,100},{1,2,10},{0,2,500},{0,3,1000},{2,3,10},{1,3,50} };
		//ans = Solution().findCheapestPrice(3, flights, 0, 3, 0);

		flights = { {0,1,1},{0,2,5},{1,2,1},{2,3,1}};
		ans = Solution().findCheapestPrice(4, flights, 0, 3, 1); // 6

		flights = { {0,1,1},{0,2,5},{1,2,1},{2,3,1},{3,4,1}	};
		ans = Solution().findCheapestPrice(5, flights, 0, 4, 2); //7

		flights = { {2,0,83},{0,2,97},{0,3,59},{2,3,32},{3,1,16},{1,3,16} };
		ans = Solution().findCheapestPrice(4, flights, 3, 0, 3); //-1
	}
}
namespace Jun_day16 // LC468 Validate IP Address
{
	class Solution {
	public:
		std::string validIPAddress(std::string IP) 
		{
			std::regex ipv_4("(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])"), ipv_6("((([0-9a-fA-F]){1,4})\\:){7}([0-9a-fA-F]){1,4}");
			if (regex_match(IP, ipv_4)) 
				return "IPv4";
			else if (regex_match(IP, ipv_6)) 
				return "IPv6";
			return "Neither"; 
		}
	};
	void RunExample()
	{
		std::string address;
		std::string ans;

		address = "2001:0db8:85a3:0:0:8A2E:0370:7334";
		ans = Solution().validIPAddress(address);

	}
}
namespace Jun_day17 // LC Surrounded Regions
{
	class Solution {
	private:
		struct Pos
		{
			size_t y;
			size_t x;
		};
		void ProcessIfEnclosedArea(std::vector<std::vector<char>>& board, size_t row, size_t col, std::vector<std::vector<bool>>& visited)
		{
			bool hitsBorder = false;
			std::stack<Pos> flipStack;
			std::queue<Pos> queue;
			queue.push({ row,col });
			visited[row][col] = 1;
			while (!queue.empty())
			{
				Pos curPos = queue.front(); queue.pop();
				flipStack.push(curPos);
				if (curPos.x == 0 || curPos.x == board[0].size() - 1 || curPos.y == 0 || curPos.y == board.size() - 1) hitsBorder = true;
				else
				{
					if (visited[curPos.y + 1][curPos.x] == 0 && board[curPos.y + 1][curPos.x] == 'O')
					{
						queue.push({ curPos.y + 1,curPos.x });
						visited[curPos.y + 1][curPos.x] = 1;
					}
					if (visited[curPos.y - 1][curPos.x] == 0 && board[curPos.y - 1][curPos.x] == 'O')
					{
						queue.push({ curPos.y - 1,curPos.x });
						visited[curPos.y - 1][curPos.x] = 1;
					}
					if (visited[curPos.y][curPos.x + 1] == 0 && board[curPos.y][curPos.x + 1] == 'O')
					{
						queue.push({ curPos.y,curPos.x + 1 });
						visited[curPos.y][curPos.x + 1] = 1;
					}
					if (visited[curPos.y][curPos.x - 1] == 0 && board[curPos.y][curPos.x - 1] == 'O')
					{
						queue.push({ curPos.y,curPos.x - 1 });
						visited[curPos.y][curPos.x - 1] = 1;
					}
				}
			}
			if (!hitsBorder)
			{
				while (!flipStack.empty())
				{
					board[flipStack.top().y][flipStack.top().x] = 'X';
					flipStack.pop();
				}
			}
		}

	public:
		void solve(std::vector<std::vector<char>>& board) 
		{
			if (board.size() == 0) return;
			size_t m = board.size();
			size_t n = board[0].size();
			std::vector<std::vector<bool>> visited(m,std::vector<bool>(n,0));
			for (size_t row = 1; row < m; row++)
			{
				for (size_t col = 1; col < n; col++)
				{
					if (!visited[row][col] && board[row][col] == 'O')
					{
						ProcessIfEnclosedArea(board, row, col, visited);
					}
				}
			}
			return;
		}
	};
	void Print(std::vector<std::vector<char>>& vec)
	{
		for (auto v : vec)
		{
			for (auto ch : v)
			{
				std::cout << ch<<'.';
			}
			std::cout << '\n';
		}
	}
	void RunExample()
	{
		std::vector<std::vector<char>> vec;
		vec = { 
			{'X','X','X','X'},
			{'O','X','X','X'},
			{'X','X','O','O'},
			{'X','O','X','X'},
			{'X','X','X','X'}
		};
		//Solution().solve(vec);

		vec = {
			{'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'X', 'O', 'O', 'O', 'O', 'O', 'X', 'O', 'O', 'O', 'O', 'O'}, 
			{'O', 'O', 'O', 'O', 'O', 'O', 'O', 'X', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'}, 
			{'X', 'O', 'O', 'X', 'O', 'X', 'O', 'O', 'O', 'O', 'X', 'O', 'O', 'X', 'O', 'O', 'O', 'O', 'O', 'O'}, 
			{'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'X', 'X', 'O'}, 
			{'O', 'X', 'X', 'O', 'O', 'O', 'O', 'O', 'O', 'X', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'}, 
			{'O', 'O', 'O', 'O', 'X', 'O', 'O', 'O', 'O', 'O', 'O', 'X', 'O', 'O', 'O', 'O', 'O', 'X', 'X', 'O'}, 
			{'O', 'O', 'O', 'O', 'O', 'O', 'O', 'X', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'}, 
			{'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'X', 'O', 'O', 'O', 'O', 'O', 'O'}, 
			{'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'X', 'O'}, 
			{'O', 'O', 'O', 'O', 'O', 'X', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'}, 
			{'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'X', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'}, 
			{'O', 'O', 'O', 'O', 'X', 'O', 'O', 'O', 'O', 'X', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'}, 
			{'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'X', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'}, 
			{'X', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'X', 'X', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'}, 
			{'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'X', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'}, 
			{'O', 'O', 'O', 'O', 'X', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'X', 'O', 'O', 'O', 'O', 'O', 'X'}, 
			{'O', 'O', 'O', 'O', 'O', 'X', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'X', 'O', 'X', 'O', 'O'}, 
			{'O', 'X', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'}, 
			{'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'X', 'X', 'O', 'O', 'O', 'X', 'O', 'O', 'X', 'O', 'O', 'X'}, 
			{'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'}};
		Print(vec); std::cout << "====================================\n";
		Solution().solve(vec);
		Print(vec); std::cout << "====================================\n";
	}
}
namespace Jun_day18
{
	class Solution 
	{
	public:
		int hIndex_lin(std::vector<int> & series) 
		{
			int n = series.size();
			if (!n) return 0;
			for (int i = 0; i < n; i++) 
			{
				if (series[i] >= n - i) return n - i;
			}
			return 0;
		}
	};
	void RunExample()
	{
		std::vector<int> series;
		int h;

		series = { 0,0 };
		h = Solution().hIndex_lin(series); //0

		series = { 0,1 };
		h = Solution().hIndex_lin(series); //1

		series = { 0,1,3,5,6 };
		h = Solution().hIndex_lin(series); //3
		
		series = { 1,3,3 };
		h = Solution().hIndex_lin(series); // 2

		series = { 0,1,3,3,3 };
		h = Solution().hIndex_lin(series); // 3


		series = { 1 }; 
		h = Solution().hIndex_lin(series); // 1
		
		series = { 0 };
		h = Solution().hIndex_lin(series); // 0

		series = { 100 };
		h = Solution().hIndex_lin(series); // 1

		series = { 1,2 };
		h = Solution().hIndex_lin(series); // 1
	}
}
namespace Jun_day19
{
	class Solution {
	public:
		const int MOD = 1e9 + 7, MOD1 = 1e9 + 9;
		const int D = 257;

		std::string Get(std::string& str, int len)
		{
			std::set<std::pair<int, int>> set;
			long long int curr_1 = 0, curr_2 = 0;
			long long int off_1 = 1, off_2 = 1;
			for (int i = 0; i < len - 1; i++)
			{
				off_1 = off_1 * D % MOD;
				off_2 = off_2 * D % MOD1;
			}

			for (int i = 0; i < len; i++)
			{
				curr_1 = (curr_1 * D + str[i]) % MOD;
				curr_2 = (curr_2 * D + str[i]) % MOD1;
			}
			set.insert({ curr_1,curr_2 });
			for (int i = 0, j = len; j < str.size(); i++, j++)
			{
				curr_1 = (D * (curr_1 - off_1 * str[i]) + str[j]) % MOD;
				curr_2 = (D * (curr_2 - off_2 * str[i]) + str[j]) % MOD1;
				if (curr_1 < 0)
					curr_1 += MOD;
				if (curr_2 < 0)
					curr_2 += MOD1;
				if (set.find({ curr_1,curr_2 }) != set.end())
					return str.substr(i + 1, len);

				set.insert({ curr_1,curr_2 });
			}
			return "";
		}


		std::string longestDupSubstring(std::string S) {
			int le = 0, ri = S.size();

			while (le < ri)
			{
				int m = le + (ri - le + 1) / 2;
				if (Get(S, m).size() != 0)
				{
					le = m;
				}
				else
					ri = m - 1;
			}
			return Get(S, le);
		}
	};
}
namespace Jun_day20
{
	class Solution
	{
	public:
		std::string getPermutation(int n, int k) 
		{
			int pTab[10] = { 1 };
			for (int i = 1; i <= 9; i++) {
				pTab[i] = i * pTab[i - 1];
			}
			std::string res;
			std::vector<char> numSet = { '1', '2', '3', '4', '5', '6', '7', '8', '9' };
			while (n > 0) {
				int tmp = (k - 1) / pTab[n - 1];
				res += numSet[tmp];
				numSet.erase(numSet.begin() + tmp);
				k = k - tmp * pTab[n - 1];
				n--;
			}
			return res;
		}
	};
	void RunExample()
	{
		std::string ans;
		ans = Solution().getPermutation(4, 9);
	}
}
namespace Jun_day21 // LC174 Dungeon Game
{
	class Solution 
	{
	public:
		int calculateMinimumHP(std::vector<std::vector<int>>& dungeon) 
		{
			//if (dungeon[0].size() == 1) return std::max(1, 1 - dungeon[0][0]);
			//std::vector<std::vector<int>> DP(dungeon.size(), std::vector<int>(dungeon[0].size(), 0));
			size_t m = dungeon.size();
			size_t n = dungeon[0].size();


			dungeon.back().back() = std::max(1, 1 - dungeon.back().back());
			for (int col = n - 2; col >= 0; --col) // Fill bottom row
			{
				int target = dungeon[m - 1][(size_t)col + 1];
				dungeon[m - 1][(size_t)col] = std::max(1, target - dungeon[m - 1][(size_t)col]);
			}
			for (int row = m - 2; row >= 0; --row) // Fill right column
			{
				int target = dungeon[(size_t)row + 1][n - 1];
				dungeon[(size_t)row][n-1] = std::max(1, target - dungeon[(size_t)row][n-1]);
			}
			for (int row = m - 2; row >= 0; --row) // Fill remaining Upper Left of Matrix
			{
				for (int col = n - 2; col >= 0; --col)
				{
					int target = std::min(dungeon[row+1][col],dungeon[row][col+1]);
					dungeon[(size_t)row][(size_t)col] = std::max(1, target - dungeon[(size_t)row][(size_t)col]);
				}
			}
			return dungeon[0][0];
		}
	};
	void RunExample()
	{
		std::vector<std::vector<int>> dun;
		int ans;

		dun = { {-2,-3,3},{-5,-10,1},{10,30,-5} };
		ans = Solution().calculateMinimumHP(dun);

		dun = { {-2} };
		ans = Solution().calculateMinimumHP(dun);

		dun = { {-2},{-2},{-1} };
		ans = Solution().calculateMinimumHP(dun);
	}
}
namespace Jun_day23// LC222 Count complete treenodes
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
		int countNodes(TreeNode* root) 
		{
			int leafCount = 0;
			int nodeCount = 1;
			std::stack<std::pair<TreeNode*, int>> stack;
			stack.push({ root,0 });
			while (!stack.empty())
			{
				auto p = stack.top(); stack.pop();
				if (p.first->left == nullptr && p.first->right == nullptr)
				{
					leafCount++;
				}
				else if (p.first->left != nullptr && p.first->right == nullptr)
				{
					return leafCount + (int)std::pow(2,p.second+1);
				}
				else
				{
					nodeCount += 2;
					stack.push({ p.first->right,p.second + 1 });
					stack.push({ p.first->left,p.second + 1 });
				}
			}
			return nodeCount;
		}
	};
	void RunExample()
	{
		TreeNode* root = new TreeNode(1, new TreeNode(2), new TreeNode(3));
		root->left->left = new TreeNode(4); root->left->right = new TreeNode(5);
		root->right->left = new TreeNode(6); //root->right->right = new TreeNode(7);
		int ans = Solution().countNodes(root);
	}
}
namespace Jun_day24 // LC96 Unique binary search trees
{
	class Solution 
	{
	public:
		int F(int x)
		{
			// DP: uses rotation of the tail & recursive calls with memoization
			// F(i) = F(0)F(i-1) + F(1)F(i-2) + ... + F(i-1)F(0)
			static std::map<int, int> map;
			if (x <= 1) return 1;
			else
			{
				auto it = map.find(x);
				if (it == map.end())
				{
					int ans = 0;
					for (size_t i = 0; i < x; i++)
					{
						ans += F(i) * F(x - 1 - i);
					}
					//std::cout << ".";
					map[x] = ans;
					return ans;
				}
				else
				{
					//std::cout << "R";
					return it->second;
				}
			}
		}
		int numTrees(int n) 
		{
			if (n == 0) return 0;
			return F(n);
		}
	};
	void RunExample()
	{
		int ans;
		ans = Solution().numTrees(5); //42
		ans = Solution().numTrees(1); //1
		ans = Solution().numTrees(0); //0
	}
}
namespace Jun_day25 // LC287 Find Duplicate Number
{
	class Solution
	{
	public:
		int findDuplicate_cycle(const std::vector<int>& nums)
		{
			//std::cout << "===============================\n";
			size_t p1 = 0;
			size_t p2 = 0;
			while (true)
			{
				p1 = nums[p1];
				p2 = nums[nums[p2]];
				//std::cout << "p1:" << p1 << ",p2:" << p2 << '\n';
				if (p1 == p2) break;
			}
			p1 = 0;
			//std::cout << "--------------------------\n";
			while (true)
			{
				p1 = nums[p1];
				p2 = nums[p2];
				//std::cout << "p1:" << p1 << ",p2:" << p2 << '\n';
				if (p1 == p2) break;
			}
			return p1;
		}
		int findDuplicate_bitmask(const std::vector<int>& nums)
		{
			int mask = 0;
			for (int n : nums)
			{
				int bit = 1 << n;
				if (bit & mask) return n;
				mask |= bit;
			}
		}
		int findDuplicate(const std::vector<int>& nums)
		{
			std::unordered_set<int> set;
			for (int n : nums)
			{
				auto it = set.find(n);
				if (it == set.end()) set.insert(n);
				else return *it;
			}
		}
	};
	void RunExample()
	{
		std::vector<int> v;
		int ans;

		v = { 1,3,4,2,2 };
		ans = Solution().findDuplicate(v); // 2
		v = { 3,1,3,4,2 };
		ans = Solution().findDuplicate(v); // 3
		v = {2,5,9,6,9,3,8,9,7,1};
		ans = Solution().findDuplicate(v); // 9
	}
}
namespace Jun_day26 // LC129 Sum root to leaf numbers
{

 //Definition for a binary tree node.
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
		int ans = 0;
		void Dive(TreeNode* node, std::string str)
		{
			if (node == nullptr)
			{
				//ans += std::stoi(str);
			}
			else if (node->left == nullptr && node->right == nullptr)
			{
				str += std::to_string(node->val);
				ans += std::stoi(str);
			}
			else
			{
				str += std::to_string(node->val);
				Dive(node->left, str);
				Dive(node->right, str);
			}
		}
		int sumNumbers(TreeNode* root) 
		{
			Dive(root, "");
			return ans;
		}
	};
	void RunExample()
	{
		TreeNode* root = nullptr;
		int ans;

		root = new TreeNode(4, new TreeNode(2, new TreeNode(1), new TreeNode(3)), new TreeNode(9));
		ans = Solution().sumNumbers(root);

	}
}
namespace Jun_day27 // LC279 Perfect Squares
{
	class Solution {
	public:
		std::pair<int,int> remainderLowestSquare_bins(int num)
		{
			long long numL = (long long)num;
			if (numL <= 1) return { num,0 };
			long long int lo = 0;
			long long int hi = 1;
			while (hi * hi < numL)
			{
				lo = hi;
				hi = hi + lo / 2 + 1;
			}
			while (lo <= hi)
			{
				long long int mid = lo + (hi - lo) / 2;
				long long int sq = mid * mid;
				if (sq == numL) return {mid, 0};
				if (sq < numL) lo = mid + 1;
				else hi = mid - 1;
			}
			return { lo - 1,num - (lo - 1) * (lo - 1) };
		}
		std::pair<int, int> remainderLowestSquare_sqrt(int num)
		{
			int root = sqrt(num);
			return {root,num-root};
		}
		int numSquares(int n) 
		{
			static int filled = 1;
			static std::vector<int> cntPerfectSquares(10000, -1 );
			cntPerfectSquares[0]=0;
			if (n <= 3) return n;
			if (n >= cntPerfectSquares.size()) cntPerfectSquares.resize(n+1, -1);
			if (cntPerfectSquares[n] != -1) return cntPerfectSquares[n];

			auto p = remainderLowestSquare_sqrt(n);
			for (int i = filled; i <= n; i++)
			{
				int min = INT_MAX;
				for (int j = 1; j * j <= i; j++)
				{
					min = std::min(min, 1 + cntPerfectSquares[i-j*j]);
				}
				cntPerfectSquares[i]=min;
			}
			filled = n;
			return cntPerfectSquares[n];
		}
	};
	void RunExample()
	{
		int ans;
		Solution obj;
		ans = obj.numSquares(12);//3
		ans = obj.numSquares(13);//2
		ans = obj.numSquares(32);//2
		ans = obj.numSquares(22);//3
		ans = obj.numSquares(10001);//2
		ans = obj.numSquares(9999);//4
	}
}
namespace Jun_day28_stack
{
	class Solution {
	private:
		std::unordered_map<	std::string, std::map<std::string,int> > map;
		int numTickets = 0;
		std::vector<std::vector<std::string>> validRoutes;
	public:
		std::vector<std::string> findItinerary(std::vector<std::vector<std::string>>& tickets) 
		{
			for (auto vec : tickets)
			{
				map[vec[0]][vec[1]]++;
				numTickets++;
			}
			struct routeData
			{
				std::vector<std::string> routeVec;
				std::unordered_map<	std::string, std::map<std::string, int>> usedTickets;
			};
			std::stack<routeData> stack; 
			{
				routeData init; init.routeVec = { "JFK" };
				stack.push(init);
			}
			while (!stack.empty())
			{
				if (stack.size() > 100)
				{
					int k = 0;
				}
				routeData curRoute = stack.top(); stack.pop();
				if (curRoute.routeVec.size() == numTickets + 1) return curRoute.routeVec;
				std::string current = curRoute.routeVec.back();
				//for (const auto& dest : map[current])
				for (auto it = map[current].rbegin(); it!=map[current].rend();it++)
				{
					if (curRoute.usedTickets[current][it->first] < it->second) // flights available
					{
						curRoute.routeVec.push_back(it->first);
						curRoute.usedTickets[current][it->first]++;
						stack.push(curRoute);
						curRoute.routeVec.pop_back();
						curRoute.usedTickets[current][it->first]--;
					}
				}
			}
			return {};
		}
	};
	void RunExample()
	{
		std::vector<std::vector<std::string>> tickets;
		std::vector<std::string> ans;
		
		tickets = { {"JFK" ,"B"} ,{"JFK","B"},{"B","C"},{"B","D"},{"D","JFK"} };
		ans = Solution().findItinerary(tickets);

		tickets = { {"JFK","SFO"} ,{"JFK","ATL"},{"SFO","ATL"},{"ATL","JFK"},{"ATL","SFO"} };
		ans = Solution().findItinerary(tickets);

		tickets = { {"AXA","EZE"},{"EZE","AUA"},{"ADL","JFK"},{"ADL","TIA"},{"AUA","AXA"},{"EZE","TIA"},{"EZE","TIA"},{"AXA","EZE"},{"EZE","ADL"},{"ANU","EZE"},{"TIA","EZE"},{"JFK","ADL"},{"AUA","JFK"},{"JFK","EZE"},{"EZE","ANU"},{"ADL","AUA"},{"ANU","AXA"},{"AXA","ADL"},{"AUA","JFK"},{"EZE","ADL"},{"ANU","TIA"},{"AUA","JFK"},{"TIA","JFK"},{"EZE","AUA"},{"AXA","EZE"},{"AUA","ANU"},{"ADL","AXA"},{"EZE","ADL"},{"AUA","ANU"},{"AXA","EZE"},{"TIA","AUA"},{"AXA","EZE"},{"AUA","SYD"},{"ADL","JFK"},{"EZE","AUA"},{"ADL","ANU"},{"AUA","TIA"},{"ADL","EZE"},{"TIA","JFK"},{"AXA","ANU"},{"JFK","AXA"},{"JFK","ADL"},{"ADL","EZE"},{"AXA","TIA"},{"JFK","AUA"},{"ADL","EZE"},{"JFK","ADL"},{"ADL","AXA"},{"TIA","AUA"},{"AXA","JFK"},{"ADL","AUA"},{"TIA","JFK"},{"JFK","ADL"},{"JFK","ADL"},{"ANU","AXA"},{"TIA","AXA"},{"EZE","JFK"},{"EZE","AXA"},{"ADL","TIA"},{"JFK","AUA"},{"TIA","EZE"},{"EZE","ADL"},{"JFK","ANU"},{"TIA","AUA"},{"EZE","ADL"},{"ADL","JFK"},{"ANU","AXA"},{"AUA","AXA"},{"ANU","EZE"},{"ADL","AXA"},{"ANU","AXA"},{"TIA","ADL"},{"JFK","ADL"},{"JFK","TIA"},{"AUA","ADL"},{"AUA","TIA"},{"TIA","JFK"},{"EZE","JFK"},{"AUA","ADL"},{"ADL","AUA"},{"EZE","ANU"},{"ADL","ANU"},{"AUA","AXA"},{"AXA","TIA"},{"AXA","TIA"},{"ADL","AXA"},{"EZE","AXA"},{"AXA","JFK"},{"JFK","AUA"},{"ANU","ADL"},{"AXA","TIA"},{"ANU","AUA"},{"JFK","EZE"},{"AXA","ADL"},{"TIA","EZE"},{"JFK","AXA"},{"AXA","ADL"},{"EZE","AUA"},{"AXA","ANU"},{"ADL","EZE"},{"AUA","EZE"} };
		ans = Solution().findItinerary(tickets);

		tickets = {{"INN", "TIA"}, {"BIM", "BRU"}, {"VIE", "LST"}, {"OOL", "BAH"}, {"MEL", "CRL"}, {"CNS", "ADL"}, {"AUA", "OOL"}, {"HBA", "ASD"}, {"INN", "FPO"}, {"NAS", "BZE"}, {"DRW", "BRU"}, {"NAS", "BAK"}, {"ADL", "ASD"}, {"HBA", "OOL"}, {"BZE", "BAH"}, {"TBI", "FPO"}, {"CRL", "AUA"}, {"BGI", "TIA"}, {"TCB", "ELH"}, {"AUA", "AXA"}, {"MHH", "TBI"}, {"CNS", "BNE"}, {"INN", "GGT"}, {"DRW", "EZE"}, {"CRL", "SYD"}, {"BNE", "AXA"}, {"CNS", "ADL"}, {"BGI", "SYD"}, {"CNS", "VIE"}, {"GGT", "BNE"}, {"ELH", "BNE"}, {"BNE", "DAC"}, {"DRW", "CNS"}, {"PER", "CRL"}, {"ADL", "ASD"}, {"MHH", "ANU"}, {"ELH", "NAS"}, {"TIA", "ADL"}, {"DAC", "AUA"}, {"ADL", "DAC"}, {"CRL", "OOL"}, {"DAC", "NAS"}, {"BNE", "GGT"}, {"BAH", "DAC"}, {"SYD", "GGT"}, {"CRL", "ADL"}, {"TCB", "VIE"}, {"TBI", "BAK"}, {"BRU", "BNE"}, {"GGT", "ASD"}, {"MEL", "BZE"}, {"TBI", "BAK"}, {"ANU", "CNS"}, {"BIM", "MEL"}, {"ELH", "AUA"}, {"GGT", "SYD"}, {"AXA", "MHH"}, {"GGT", "ANU"}, {"CRL", "DAC"}, {"VIE", "BAH"}, {"JFK", "LST"}, {"TIA", "CRL"}, {"MHH", "DAC"}, {"OOL", "BZE"}, {"VIE", "ELH"}, {"DRW", "INN"}, {"EZE", "INN"}, {"ASD", "TBI"}, {"BAK", "BNE"}, {"BNE", "INN"}, {"BZE", "NAS"}, {"VIE", "CRL"}, {"ADL", "SYD"}, {"INN", "DRW"}, {"BRU", "BZE"}, {"BNE", "FPO"}, {"BIM", "DAC"}, {"JFK", "MEL"}, {"BAK", "BNE"}, {"BAK", "BZE"}, {"JFK", "ASD"}, {"BNE", "DRW"}, {"EZE", "ELH"}, {"ASD", "BGI"}, {"SYD", "TCB"}, {"AUA", "MHH"}, {"INN", "AUA"}, {"SYD", "OOL"}, {"ASD", "CRL"}, {"BNE", "BRU"}, {"MEL", "BGI"}, {"BIM", "CNS"}, {"BIM", "ASD"}, {"ASD", "MEL"}, {"SYD", "DAC"}, {"OOL", "VIE"}, {"ASD", "BNE"}, {"OOL", "DAC"}, {"LST", "TIA"}, {"AUA", "MEL"}, {"ASD", "DAC"}, {"ANU", "PER"}, {"DAC", "TBI"}, {"ASD", "BNE"}, {"BAK", "MEL"}, {"CBR", "OOL"}, {"BNE", "ADL"}, {"AXA", "ELH"}, {"CBR", "DRW"}, {"ADL", "LST"}, {"BAK", "INN"}, {"FPO", "SYD"}, {"DAC", "BNE"}, {"TBI", "EZE"}, {"AXA", "DAC"}, {"DAC", "EZE"}, {"NAS", "DRW"}, {"FPO", "DRW"}, {"BAH", "BNE"}, {"MEL", "BZE"}, {"LST", "CRL"}, {"EZE", "LST"}, {"TBI", "NAS"}, {"CBR", "BAK"}, {"NAS", "DAC"}, {"JFK", "ANU"}, {"TIA", "BNE"}, {"CRL", "NAS"}, {"SYD", "ELH"}, {"OOL", "BIM"}, {"AUA", "ASD"}, {"BZE", "EZE"}, {"BAK", "BRU"}, {"HBA", "BZE"}, {"BNE", "SYD"}, {"DAC", "TIA"}, {"BRU", "TCB"}, {"ANU", "OOL"}, {"ELH", "VIE"}, {"CRL", "DRW"}, {"ANU", "VIE"}, {"PER", "BIM"}, {"BIM", "JFK"}, {"DAC", "VIE"}, {"FPO", "TCB"}, {"AUA", "CNS"}, {"CRL", "FPO"}, {"BAK", "DAC"}, {"EZE", "ANU"}, {"NAS", "DRW"}, {"BZE", "HBA"}, {"BNE", "BAK"}, {"AXA", "AUA"}, {"VIE", "PER"}, {"DAC", "AUA"}, {"BIM", "MEL"}, {"DAC", "ASD"}, {"DAC", "CRL"}, {"MHH", "HBA"}, {"BRU", "EZE"}, {"GGT", "BNE"}, {"BZE", "AXA"}, {"BZE", "CRL"}, {"TBI", "CBR"}, {"CRL", "BGI"}, {"ASD", "JFK"}, {"DAC", "BIM"}, {"ELH", "BGI"}, {"MEL", "TBI"}, {"OOL", "ASD"}, {"CNS", "BZE"}, {"TIA", "ELH"}, {"ASD", "BNE"}, {"BNE", "ASD"}, {"TIA", "LST"}, {"AUA", "AXA"}, {"CRL", "DAC"}, {"BAK", "BIM"}, {"BGI", "BNE"}, {"ELH", "BZE"}, {"ANU", "GGT"}, {"ASD", "CBR"}, {"OOL", "BIM"}, {"TBI", "INN"}, {"BRU", "ELH"}, {"CRL", "TIA"}, {"PER", "ASD"}, {"TIA", "DAC"}, {"ADL", "AUA"}, {"TCB", "AUA"}, {"HBA", "BNE"}, {"BNE", "TIA"}, {"INN", "ANU"}, {"TBI", "ADL"}, {"ELH", "AXA"}, {"BGI", "ANU"}, {"TIA", "BAK"}, {"PER", "TBI"}, {"EZE", "MHH"}, {"BZE", "NAS"}, {"JFK", "BNE"}, {"BRU", "ASD"}, {"AUA", "CBR"}, {"NAS", "JFK"}, {"ELH", "BIM"}, {"BNE", "TBI"}, {"BAK", "CNS"}, {"BNE", "GGT"}, {"OOL", "PER"}, {"BNE", "BRU"}, {"MEL", "PER"}, {"BAH", "MEL"}, {"TCB", "CRL"}, {"CNS", "OOL"}, {"BZE", "VIE"}, {"ASD", "CRL"}, {"LST", "BZE"}, {"ANU", "BRU"}, {"AUA", "BRU"}, {"ASD", "BGI"}, {"AUA", "TCB"}, {"TCB", "CRL"}, {"SYD", "CRL"}, {"BRU", "HBA"}, {"DRW", "ASD"}, {"TCB", "FPO"}, {"TIA", "CRL"}, {"BZE", "CNS"}, {"ELH", "TCB"}, {"OOL", "CRL"}, {"CRL", "ELH"}, {"MEL", "ASD"}, {"ASD", "BIM"}, {"CRL", "JFK"}, {"DAC", "BNE"}, {"HBA", "JFK"}, {"NAS", "OOL"}, {"DAC", "CRL"}, {"ELH", "CNS"}, {"ASD", "ELH"}, {"DRW", "ELH"}, {"FPO", "BAK"}, {"OOL", "BAK"}, {"ELH", "OOL"}, {"ADL", "OOL"}, {"BNE", "INN"}, {"DAC", "TIA"}, {"INN", "NAS"}, {"BAH", "BNE"}, {"BAH", "JFK"}, {"AUA", "BIM"}, {"PER", "TIA"}, {"BZE", "ADL"}, {"BAK", "BNE"}, {"JFK", "PER"}, {"JFK", "AXA"}, {"GGT", "FPO"}, {"FPO", "MHH"}, {"ASD", "HBA"}, {"BNE", "INN"}, {"LST", "ANU"}, {"AXA", "BZE"}, {"JFK", "ANU"}, {"ASD", "LST"}, {"VIE", "EZE"}, {"ELH", "TBI"}, {"DAC", "TBI"}, {"DRW", "JFK"}, {"CRL", "TCB"}, {"TBI", "ASD"}, {"FPO", "AXA"}, {"NAS", "BAH"}, {"EZE", "DRW"}, {"AXA", "BAK"}, {"BIM", "JFK"}, {"JFK", "ASD"}, {"BZE", "HBA"}, {"LST", "DAC"}, {"AXA", "AUA"}, {"GGT", "TBI"}, {"CRL", "ELH"}, {"VIE", "BAH"}, {"BGI", "DAC"}, {"LST", "GGT"}, {"BNE", "GGT"}, {"CNS", "NAS"}, {"BNE", "BAK"}, {"ANU", "ELH"}, {"DRW", "AUA"}, {"ANU", "AUA"}};
		ans = Solution().findItinerary(tickets);
	}
}
namespace Jun_day28 // LC332 Reconstruct Itinerary
{
	class Solution {
	private:
		std::unordered_map<	std::string, std::map<std::string, int> > map;
		int numTickets = 0;
		std::vector<std::string> validRoute = {"JFK"};
	public:
		void dfs()
		{
			if (validRoute.size() == numTickets + 1) return;
			auto current = validRoute.back();
			for (auto it = map[current].begin(); it != map[current].end(); it++)
			{
				if (it->second > 0)
				{
					validRoute.push_back(it->first);
					it->second--;
					dfs();
					if (validRoute.size() == numTickets + 1) return;
					validRoute.pop_back();
					it->second++;
				}
			}
		}
		std::vector<std::string> findItinerary(std::vector<std::vector<std::string>>& tickets)
		{
			for (const auto& vec : tickets)
			{
				map[vec[0]][vec[1]]++;
				numTickets++;
			}
			dfs();
			return validRoute;
		}
	};
	void RunExample()
	{
		std::vector<std::vector<std::string>> tickets;
		tickets.reserve(500);
		std::vector<std::string> ans;

		tickets = { {"JFK" ,"B"} ,{"JFK","B"},{"B","C"},{"B","D"},{"D","JFK"} };
		ans = Solution().findItinerary(tickets);
		tickets.clear();

		tickets = { {"JFK","SFO"} ,{"JFK","ATL"},{"SFO","ATL"},{"ATL","JFK"},{"ATL","SFO"} };
		ans = Solution().findItinerary(tickets);

		tickets = { {"AXA","EZE"},{"EZE","AUA"},{"ADL","JFK"},{"ADL","TIA"},{"AUA","AXA"},{"EZE","TIA"},{"EZE","TIA"},{"AXA","EZE"},{"EZE","ADL"},{"ANU","EZE"},{"TIA","EZE"},{"JFK","ADL"},{"AUA","JFK"},{"JFK","EZE"},{"EZE","ANU"},{"ADL","AUA"},{"ANU","AXA"},{"AXA","ADL"},{"AUA","JFK"},{"EZE","ADL"},{"ANU","TIA"},{"AUA","JFK"},{"TIA","JFK"},{"EZE","AUA"},{"AXA","EZE"},{"AUA","ANU"},{"ADL","AXA"},{"EZE","ADL"},{"AUA","ANU"},{"AXA","EZE"},{"TIA","AUA"},{"AXA","EZE"},{"AUA","SYD"},{"ADL","JFK"},{"EZE","AUA"},{"ADL","ANU"},{"AUA","TIA"},{"ADL","EZE"},{"TIA","JFK"},{"AXA","ANU"},{"JFK","AXA"},{"JFK","ADL"},{"ADL","EZE"},{"AXA","TIA"},{"JFK","AUA"},{"ADL","EZE"},{"JFK","ADL"},{"ADL","AXA"},{"TIA","AUA"},{"AXA","JFK"},{"ADL","AUA"},{"TIA","JFK"},{"JFK","ADL"},{"JFK","ADL"},{"ANU","AXA"},{"TIA","AXA"},{"EZE","JFK"},{"EZE","AXA"},{"ADL","TIA"},{"JFK","AUA"},{"TIA","EZE"},{"EZE","ADL"},{"JFK","ANU"},{"TIA","AUA"},{"EZE","ADL"},{"ADL","JFK"},{"ANU","AXA"},{"AUA","AXA"},{"ANU","EZE"},{"ADL","AXA"},{"ANU","AXA"},{"TIA","ADL"},{"JFK","ADL"},{"JFK","TIA"},{"AUA","ADL"},{"AUA","TIA"},{"TIA","JFK"},{"EZE","JFK"},{"AUA","ADL"},{"ADL","AUA"},{"EZE","ANU"},{"ADL","ANU"},{"AUA","AXA"},{"AXA","TIA"},{"AXA","TIA"},{"ADL","AXA"},{"EZE","AXA"},{"AXA","JFK"},{"JFK","AUA"},{"ANU","ADL"},{"AXA","TIA"},{"ANU","AUA"},{"JFK","EZE"},{"AXA","ADL"},{"TIA","EZE"},{"JFK","AXA"},{"AXA","ADL"},{"EZE","AUA"},{"AXA","ANU"},{"ADL","EZE"},{"AUA","EZE"} };
		ans = Solution().findItinerary(tickets);

		tickets = { {"INN", "TIA"}, {"BIM", "BRU"}, {"VIE", "LST"}, {"OOL", "BAH"}, {"MEL", "CRL"}, {"CNS", "ADL"}, {"AUA", "OOL"}, {"HBA", "ASD"}, {"INN", "FPO"}, {"NAS", "BZE"}, {"DRW", "BRU"}, {"NAS", "BAK"}, {"ADL", "ASD"}, {"HBA", "OOL"}, {"BZE", "BAH"}, {"TBI", "FPO"}, {"CRL", "AUA"}, {"BGI", "TIA"}, {"TCB", "ELH"}, {"AUA", "AXA"}, {"MHH", "TBI"}, {"CNS", "BNE"}, {"INN", "GGT"}, {"DRW", "EZE"}, {"CRL", "SYD"}, {"BNE", "AXA"}, {"CNS", "ADL"}, {"BGI", "SYD"}, {"CNS", "VIE"}, {"GGT", "BNE"}, {"ELH", "BNE"}, {"BNE", "DAC"}, {"DRW", "CNS"}, {"PER", "CRL"}, {"ADL", "ASD"}, {"MHH", "ANU"}, {"ELH", "NAS"}, {"TIA", "ADL"}, {"DAC", "AUA"}, {"ADL", "DAC"}, {"CRL", "OOL"}, {"DAC", "NAS"}, {"BNE", "GGT"}, {"BAH", "DAC"}, {"SYD", "GGT"}, {"CRL", "ADL"}, {"TCB", "VIE"}, {"TBI", "BAK"}, {"BRU", "BNE"}, {"GGT", "ASD"}, {"MEL", "BZE"}, {"TBI", "BAK"}, {"ANU", "CNS"}, {"BIM", "MEL"}, {"ELH", "AUA"}, {"GGT", "SYD"}, {"AXA", "MHH"}, {"GGT", "ANU"}, {"CRL", "DAC"}, {"VIE", "BAH"}, {"JFK", "LST"}, {"TIA", "CRL"}, {"MHH", "DAC"}, {"OOL", "BZE"}, {"VIE", "ELH"}, {"DRW", "INN"}, {"EZE", "INN"}, {"ASD", "TBI"}, {"BAK", "BNE"}, {"BNE", "INN"}, {"BZE", "NAS"}, {"VIE", "CRL"}, {"ADL", "SYD"}, {"INN", "DRW"}, {"BRU", "BZE"}, {"BNE", "FPO"}, {"BIM", "DAC"}, {"JFK", "MEL"}, {"BAK", "BNE"}, {"BAK", "BZE"}, {"JFK", "ASD"}, {"BNE", "DRW"}, {"EZE", "ELH"}, {"ASD", "BGI"}, {"SYD", "TCB"}, {"AUA", "MHH"}, {"INN", "AUA"}, {"SYD", "OOL"}, {"ASD", "CRL"}, {"BNE", "BRU"}, {"MEL", "BGI"}, {"BIM", "CNS"}, {"BIM", "ASD"}, {"ASD", "MEL"}, {"SYD", "DAC"}, {"OOL", "VIE"}, {"ASD", "BNE"}, {"OOL", "DAC"}, {"LST", "TIA"}, {"AUA", "MEL"}, {"ASD", "DAC"}, {"ANU", "PER"}, {"DAC", "TBI"}, {"ASD", "BNE"}, {"BAK", "MEL"}, {"CBR", "OOL"}, {"BNE", "ADL"}, {"AXA", "ELH"}, {"CBR", "DRW"}, {"ADL", "LST"}, {"BAK", "INN"}, {"FPO", "SYD"}, {"DAC", "BNE"}, {"TBI", "EZE"}, {"AXA", "DAC"}, {"DAC", "EZE"}, {"NAS", "DRW"}, {"FPO", "DRW"}, {"BAH", "BNE"}, {"MEL", "BZE"}, {"LST", "CRL"}, {"EZE", "LST"}, {"TBI", "NAS"}, {"CBR", "BAK"}, {"NAS", "DAC"}, {"JFK", "ANU"}, {"TIA", "BNE"}, {"CRL", "NAS"}, {"SYD", "ELH"}, {"OOL", "BIM"}, {"AUA", "ASD"}, {"BZE", "EZE"}, {"BAK", "BRU"}, {"HBA", "BZE"}, {"BNE", "SYD"}, {"DAC", "TIA"}, {"BRU", "TCB"}, {"ANU", "OOL"}, {"ELH", "VIE"}, {"CRL", "DRW"}, {"ANU", "VIE"}, {"PER", "BIM"}, {"BIM", "JFK"}, {"DAC", "VIE"}, {"FPO", "TCB"}, {"AUA", "CNS"}, {"CRL", "FPO"}, {"BAK", "DAC"}, {"EZE", "ANU"}, {"NAS", "DRW"}, {"BZE", "HBA"}, {"BNE", "BAK"}, {"AXA", "AUA"}, {"VIE", "PER"}, {"DAC", "AUA"}, {"BIM", "MEL"}, {"DAC", "ASD"}, {"DAC", "CRL"}, {"MHH", "HBA"}, {"BRU", "EZE"}, {"GGT", "BNE"}, {"BZE", "AXA"}, {"BZE", "CRL"}, {"TBI", "CBR"}, {"CRL", "BGI"}, {"ASD", "JFK"}, {"DAC", "BIM"}, {"ELH", "BGI"}, {"MEL", "TBI"}, {"OOL", "ASD"}, {"CNS", "BZE"}, {"TIA", "ELH"}, {"ASD", "BNE"}, {"BNE", "ASD"}, {"TIA", "LST"}, {"AUA", "AXA"}, {"CRL", "DAC"}, {"BAK", "BIM"}, {"BGI", "BNE"}, {"ELH", "BZE"}, {"ANU", "GGT"}, {"ASD", "CBR"}, {"OOL", "BIM"}, {"TBI", "INN"}, {"BRU", "ELH"}, {"CRL", "TIA"}, {"PER", "ASD"}, {"TIA", "DAC"}, {"ADL", "AUA"}, {"TCB", "AUA"}, {"HBA", "BNE"}, {"BNE", "TIA"}, {"INN", "ANU"}, {"TBI", "ADL"}, {"ELH", "AXA"}, {"BGI", "ANU"}, {"TIA", "BAK"}, {"PER", "TBI"}, {"EZE", "MHH"}, {"BZE", "NAS"}, {"JFK", "BNE"}, {"BRU", "ASD"}, {"AUA", "CBR"}, {"NAS", "JFK"}, {"ELH", "BIM"}, {"BNE", "TBI"}, {"BAK", "CNS"}, {"BNE", "GGT"}, {"OOL", "PER"}, {"BNE", "BRU"}, {"MEL", "PER"}, {"BAH", "MEL"}, {"TCB", "CRL"}, {"CNS", "OOL"}, {"BZE", "VIE"}, {"ASD", "CRL"}, {"LST", "BZE"}, {"ANU", "BRU"}, {"AUA", "BRU"}, {"ASD", "BGI"}, {"AUA", "TCB"}, {"TCB", "CRL"}, {"SYD", "CRL"}, {"BRU", "HBA"}, {"DRW", "ASD"}, {"TCB", "FPO"}, {"TIA", "CRL"}, {"BZE", "CNS"}, {"ELH", "TCB"}, {"OOL", "CRL"}, {"CRL", "ELH"}, {"MEL", "ASD"}, {"ASD", "BIM"}, {"CRL", "JFK"}, {"DAC", "BNE"}, {"HBA", "JFK"}, {"NAS", "OOL"}, {"DAC", "CRL"}, {"ELH", "CNS"}, {"ASD", "ELH"}, {"DRW", "ELH"}, {"FPO", "BAK"}, {"OOL", "BAK"}, {"ELH", "OOL"}, {"ADL", "OOL"}, {"BNE", "INN"}, {"DAC", "TIA"}, {"INN", "NAS"}, {"BAH", "BNE"}, {"BAH", "JFK"}, {"AUA", "BIM"}, {"PER", "TIA"}, {"BZE", "ADL"}, {"BAK", "BNE"}, {"JFK", "PER"}, {"JFK", "AXA"}, {"GGT", "FPO"}, {"FPO", "MHH"}, {"ASD", "HBA"}, {"BNE", "INN"}, {"LST", "ANU"}, {"AXA", "BZE"}, {"JFK", "ANU"}, {"ASD", "LST"}, {"VIE", "EZE"}, {"ELH", "TBI"}, {"DAC", "TBI"}, {"DRW", "JFK"}, {"CRL", "TCB"}, {"TBI", "ASD"}, {"FPO", "AXA"}, {"NAS", "BAH"}, {"EZE", "DRW"}, {"AXA", "BAK"}, {"BIM", "JFK"}, {"JFK", "ASD"}, {"BZE", "HBA"}, {"LST", "DAC"}, {"AXA", "AUA"}, {"GGT", "TBI"}, {"CRL", "ELH"}, {"VIE", "BAH"}, {"BGI", "DAC"}, {"LST", "GGT"}, {"BNE", "GGT"}, {"CNS", "NAS"}, {"BNE", "BAK"}, {"ANU", "ELH"}, {"DRW", "AUA"}, {"ANU", "AUA"} };
		ans = Solution().findItinerary(tickets);
	}
}
namespace Jun_day30 // LC212 Word search II
{
	struct Node
	{
		Node* next[27] = { nullptr };
	};
	class Trie {
	public:
		Node* root;
	public:
		/** Initialize your data structure here. */
		Trie()
			:
			root(new Node)
		{}
		void VisitAndDelete(Node* n)
		{
			for (size_t i = 0; i < 26; ++i)
			{
				if (n->next[i])
				{
					VisitAndDelete(n->next[i]);
				}
			}
			delete n;
			n = nullptr;
		}
		~Trie()
		{
			VisitAndDelete(root);
			//delete root;
			root = nullptr;
		}
		/** Inserts a word into the trie. */
		void insert(std::string word)
		{
			Node* pRunner = root;
			for (size_t i = 0; i < word.size(); ++i)
			{
				if (!pRunner->next[word[i] - 'a'])
				{
					pRunner->next[word[i] - 'a'] = new Node;
				}
				pRunner = pRunner->next[word[i] - 'a'];
			}
			pRunner->next[26] = root;
		}
		/** Returns if the word is in the trie. */
		bool search(std::string word)
		{
			Node* pRunner = root;
			for (size_t i = 0; i < word.size(); ++i)
			{
				if (pRunner->next[word[i] - 'a'])
				{
					pRunner = pRunner->next[word[i] - 'a'];
				}
				else return false;
			}
			if (pRunner->next[26]) return true;
			return false;
		}
		/** Returns if there is any word in the trie that starts with the given prefix. */
		bool startsWith(std::string prefix)
		{
			Node* pRunner = root;
			for (size_t i = 0; i < prefix.size(); ++i)
			{
				if (pRunner->next[prefix[i] - 'a'])
				{
					pRunner = pRunner->next[prefix[i] - 'a'];
				}
				else return false;
			}
			return true;
		}
		int test(std::string str)
		{
			Node* pRunner = root;
			for (size_t i = 0; i < str.size(); ++i)
			{
				if (pRunner->next[str[i] - 'a'])
				{
					pRunner = pRunner->next[str[i] - 'a'];
				}
				else return 0; // no prefix match
			}
			if (pRunner->next[26]) return 2; // word match
			return 1; // prefix match
		}
	};
	class Solution {
	private: // data members
		Trie* trie;
		std::unordered_set<long long> visited;
		std::unordered_set<std::string> matchedWords;
		std::string wrd;
	private: // data structures
		struct Pos
		{
			int row;
			int col;
		};
	private: // methods
		static constexpr long long hash(const Pos& p)
		{
			return ((long long)p.row << 32 | p.col);
		}
		void dfs(const Pos curpos,std::vector<std::vector<char>>& board, std::vector<std::string>& words)
		{
			long long curposHash = hash(curpos);
			const auto it = visited.insert(curposHash);
			if (!it.second) // position already visited
			{
				//wrd.pop_back();
				return;
			}
			wrd += board[curpos.row][curpos.col];
			switch (trie->test(wrd))
			{
			case 0: // wrd is not in Trie; backtrack
				visited.erase(it.first);
				wrd.pop_back();
				return;
				break;
			case 2: // wrd is match in Trie; add wrd to matchedWords 
				matchedWords.insert(wrd);
			default: // wrd is prefix in Trie OR match in Trie; continue
				if (curpos.row > 0) // Try NORTH
				{
					dfs({ curpos.row - 1,curpos.col }, board, words);
				}
				if (curpos.row < board.size() - 1) // Try SOUTH
				{
					dfs({ curpos.row + 1,curpos.col }, board, words);
				}
				if (curpos.col > 0) // Try WEST
				{
					dfs({ curpos.row,curpos.col - 1 }, board, words);
				}
				if (curpos.col < board[0].size() - 1) // Try EAST
				{
					dfs({ curpos.row,curpos.col + 1 }, board, words);
				}
				break;
			}
			wrd.pop_back();
			visited.erase(it.first);
			return;
		}
	public: // interface
		Solution()
			:
			trie(new Trie())
		{}
		std::vector<std::string> findWords(std::vector<std::vector<char>>& board, std::vector<std::string>& words) 
		{
			if (words.size() == 0) return {};
			if (board.size() == 0 || board[0].size() == 0) return {};
			// Initialize and fill Trie
			for (auto s : words)
			{
				trie->insert(s);
			}
			// DFS
			for (int row = 0; row < board.size(); row++)
			{
				for (int col = 0; col < board[0].size(); col++)
				{
					Pos curpos({ row, col });
					visited.clear();
					wrd.clear();
					dfs(curpos,board,words);
				}
			}
			return { matchedWords.begin(),matchedWords.end() };
		}
	};
	void RunExample()
	{
		std::vector<std::vector<char>> board;
		std::vector<std::string> words;
		std::vector<std::string> ret;
		
		board = {
			{'o','a','a','n'},
			{'e','t','a','e'},
			{'i','h','k','r'},
			{'i','f','l','v'}
		};
		words = { "oathh","oathkree","oate","oatae" };
		ret = Solution().findWords(board, words);
		
		words = { "oathkr","oate","oatae" }; //PROBLEM
		ret = Solution().findWords(board, words);
		
		words = { "oet","oat" }; //PROBLEM
		ret = Solution().findWords(board, words);

		board = { 
			{'o'},
			{'a'},
			{'t'}
		};
		words = { "oat", "oa"};
		ret = Solution().findWords(board, words);

		board = {
			{'b', 'a', 'a', 'b', 'a', 'b'}, 
			{'a', 'b', 'a', 'a', 'a', 'a'}, 
			{'a', 'b', 'a', 'a', 'a', 'b'}, 
			{'a', 'b', 'a', 'b', 'b', 'a'}, 
			{'a', 'a', 'b', 'b', 'a', 'b'}, 
			{'a', 'a', 'b', 'b', 'b', 'a'}, 
			{'a', 'a', 'b', 'a', 'a', 'b'}};
		words = { 
			"bbaabaabaaaaabaababaaaaababb", 
			"aabbaaabaaabaabaaaaaabbaaaba", 
			"babaababbbbbbbaabaababaabaaa", 
			"bbbaaabaabbaaababababbbbbaaa", 
			"babbabbbbaabbabaaaaaabbbaaab", 
			"bbbababbbbbbbababbabbbbbabaa", 
			"babababbababaabbbbabbbbabbba", 
			"abbbbbbaabaaabaaababaabbabba", 
			"aabaabababbbbbbababbbababbaa", 
			"aabbbbabbaababaaaabababbaaba", 
			"ababaababaaabbabbaabbaabbaba", 
			"abaabbbaaaaababbbaaaaabbbaab", 
			"aabbabaabaabbabababaaabbbaab", 
			"baaabaaaabbabaaabaabababaaaa", 
			"aaabbabaaaababbabbaabbaabbaa", 
			"aaabaaaaabaabbabaabbbbaabaaa", 
			"abbaabbaaaabbaababababbaabbb", 
			"baabaababbbbaaaabaaabbababbb", 
			"aabaababbaababbaaabaabababab", 
			"abbaaabbaabaabaabbbbaabbbbbb", 
			"aaababaabbaaabbbaaabbabbabab", 
			"bbababbbabbbbabbbbabbbbbabaa", 
			"abbbaabbbaaababbbababbababba",
			"bbbbbbbabbbababbabaabababaab", 
			"aaaababaabbbbabaaaaabaaaaabb", 
			"bbaaabbbbabbaaabbaabbabbaaba", 
			"aabaabbbbaabaabbabaabababaaa", 
			"abbababbbaababaabbababababbb", 
			"aabbbabbaaaababbbbabbababbbb", 
			"babbbaabababbbbbbbbbaabbabaa" };
		ret = Solution().findWords(board, words);
	}
}