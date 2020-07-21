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
namespace Jul_day18_ineff
{
	class Solution {
	private:	
		bool canFinish(int numCourses, std::vector<std::vector<int>>& prerequisites)
		{
			Graph<int> graphT(prerequisites);
			Graph<int> graph = graphT.GetInverse();
			auto g = graph.StronglyConnectedComponents();
			for (auto v : g)
			{
				if (v.size() > 1) return false;
			}
			return true;
		}
		void dfs(int i)
		{
			visited.insert(i);
			for (int v : nodeList[i])
			{
				if (visited.find(v) == visited.end())
				{
					dfs(v);
				}
				//arr[current_last] = i;
				//current_last--;
			}
			arr[current_last++] = i;
			//current_last++;
		}
		int current_last;
		std::set<int> visited;
		std::vector<int> arr;
		std::map<int, std::vector<int>> nodeList;
	public:
		std::vector<int> findOrder(int numCourses, std::vector<std::vector<int>>& prerequisites) 
			// Performs topological sort by following DFS (with outer loop) to end nodes that are not visited yet
			// (can be improvedd by integrating Kosaraju into the main loop instead of pre-check)
		{	
			if (!canFinish(numCourses, prerequisites)) return {};
			arr.resize(numCourses, 0);
			current_last = 0;// numCourses - 1;
			for (auto vec : prerequisites)
			{
				nodeList[vec[0]].push_back(vec[1]);
			}

			for (int i = 0; i < numCourses; i++)
			{
				if (visited.find(i) == visited.end())
				{
					dfs(i);
				}
			}
			return arr;
		}
	};
	void RunExample()
	{
		std::vector<std::vector<int>> vec;
		std::vector<int> ans;

		vec = { {1,0},{2,0},{3,1},{3,2} ,{1,2} };
		ans = Solution().findOrder(4, vec); // 0,2,1,3

		vec = { {1,0},{2,0},{2,1},{4,1},{3,2},{3,4} };
		ans = Solution().findOrder(5, vec); // 0,1,4,2,3 or 0,1,2,4,3

	}
}
namespace Jul_day18
{
	class Solution {
	
	public:
		std::vector<int> findOrder(int numCourses, std::vector<std::vector<int>>& prerequisites)
		{
			std::vector<std::vector<int>> out(numCourses);
			std::vector<int> inDegree(numCourses,0);
			std::vector<int> arr; arr.reserve(numCourses);
			std::stack<int> stack;			
			for (const auto& vec : prerequisites)
			{
				inDegree[vec[0]]++;
				out[vec[1]].push_back(vec[0]);
			}
			for (size_t i = 0; i<numCourses; i++)
			{
				if (inDegree[i]==0) stack.push(i);
			}
			while (!stack.empty())
			{
				const int orphanNode = stack.top(); stack.pop();
				arr.push_back(orphanNode);
				for (int n : out[orphanNode])
				{
					if (--inDegree[n] == 0)
					{
						stack.push(n);
					}
				}
			}
			if (arr.size() == numCourses) return arr;
			else return {};
		}
	};
	void RunExample()
	{
		std::vector<std::vector<int>> vec;
		std::vector<int> ans;

		vec = { {1,0} };
		ans = Solution().findOrder(2, vec); // 0,1

		vec = {  };
		ans = Solution().findOrder(1, vec); // 0

		vec = {  };
		ans = Solution().findOrder(2, vec); // 1,0 or 0,1

		vec = { {1,0},{2,0},{3,1},{3,2} ,{1,2} };
		ans = Solution().findOrder(4, vec); // 0,2,1,3

		vec = { {0,4}, {1,0},{0,2},{3,1},{3,2} ,{2,1} };
		ans = Solution().findOrder(5, vec); // {}

		vec = { {1,0},{2,0},{2,1},{4,1},{3,2},{3,4} };
		ans = Solution().findOrder(5, vec); // 0,1,4,2,3 or 0,1,2,4,3

	}
}
namespace Jul_day18_kosaraju
{
	class Solution {

	private: 
		// Graph representation
		std::vector<std::vector<int>> out;
		std::vector<std::vector<int>> in;
		// SCC data
		std::vector<std::vector<int>> allSCC;
		std::vector<int> curSCC;
		int countSCC=0;
		// Bookkeeping data for Kosaraju
		std::stack<int> fTimesStack;
		int t = 0;
		std::vector<int> visited;
		bool AbortIfCircFound = false;
		bool CircFound = false;
	private:
		void dfs(int n, int mode) // [mode = 1]:Traverse normal, [mode = -1]:Traverse inverted
		{
			if (AbortIfCircFound && CircFound) return;
			visited[n]=mode;
			if (mode == 1)
			{
				for (int vert : out[n])
				{
					if (visited[vert] != mode)
					{
						dfs(vert, mode);
					}
				}
			}
			else if (mode == -1)
			{
				curSCC.push_back(n);
				if (curSCC.size() > 1) CircFound = true;
				for (int vert : in[n])
				{
					if (visited[vert] != mode)
					{
						dfs(vert, mode);
					}
				}
			}
			else assert(false);
			fTimesStack.push(n);
		}
	public:
		int nSCC(int nVerts, std::vector<std::vector<int>>& edges)
		{
			// Initialize graph
			out.resize(nVerts);
			in.resize(nVerts);
			for (const auto& vec : edges)
			{
				out[vec[1]].push_back(vec[0]);
				in[vec[0]].push_back(vec[1]);
			}

			// Kosaraju 1st pass (on G)
			visited.resize(nVerts, 0);
			for (int i = nVerts - 1; i >= 0; i--)
			{
				if (visited[i] != 1)
				{
					dfs(i,1);
				}
			}
			// Kosaraju 2nd pass (on inv(G))
			while (!fTimesStack.empty())
			{
				int i = fTimesStack.top(); fTimesStack.pop();
				if (visited[i] != -1)
				{
					dfs(i,-1);
					allSCC.push_back(curSCC);
					countSCC++;
					curSCC.clear();
				}
			}
			return countSCC;
		}
		bool hasCirculants(int nVerts, std::vector<std::vector<int>>& edges)
		{
			// Initialize graph
			out.resize(nVerts);
			in.resize(nVerts);
			for (const auto& vec : edges)
			{
				out[vec[1]].push_back(vec[0]);
				in[vec[0]].push_back(vec[1]);
			}

			// Kosaraju 1st pass (on G)
			visited.resize(nVerts, 0);
			for (int i = nVerts - 1; i >= 0; i--)
			{
				if (visited[i] != 1)
				{
					dfs(i, 1);
				}
			}
			// Kosaraju 2nd pass (on inv(G))
			AbortIfCircFound = true;
			while (!fTimesStack.empty())
			{
				int i = fTimesStack.top(); fTimesStack.pop();
				if (visited[i] != -1)
				{
					dfs(i, -1);
					if (CircFound) return true;
					//allSCC.push_back(curSCC);
					//countSCC++;
					curSCC.clear();
				}
			}
			return false;
		}
	};
	void RunExample()
	{
		std::vector<std::vector<int>> vec;
		std::vector<int> ans;

		vec = { {7,1},{4,7},{1,4},{9,7},{9,3},{3,6},{6,9},{8,6},{2,8},{5,2},{8,5},{1,0} };
		int nSCC = Solution().nSCC(10,vec); // 4 Strongly Connected Components
		bool circFound = Solution().hasCirculants(10, vec);
	}
}
namespace Jul_day19 // LC67 Add Binary
{
	class Solution {
	private:
		std::vector<int> base;
		std::string ToBin(unsigned int n, int min_digits = 0)
		{
			std::string bin_str;
			for (int count = 0; n != 0 || count < min_digits; n >>= 1, count++)
			{
				bin_str.push_back(bool(n & 0b1) ? '1' : '0');
			}
			std::reverse(bin_str.begin(), bin_str.end());
			return bin_str;
		}
		int ToInt(std::string bin_str)
		{
			int total = 0;
			size_t base_index = 0;
			while (bin_str.size() > 0)
			{
				total += (bin_str.back() - '0') * base[base_index++];
				bin_str.pop_back();
			}
			return total;
		}
	public:
		Solution()
		{
			base.resize(32);
			base[0] = 1;
			for (size_t i = 1; i < 31; i++)
			{
				base[i] = 2 * base[i - 1];
			}
		}
		std::string addBinary2(std::string a, std::string b)
		{
			if (a.size() < 33 && b.size() < 33) return ToBin(ToInt(a) + ToInt(b), 1);
			else return "Can't process >32 bit input";
		}
		std::string addBinary(std::string a, std::string b)
		{
			std::string out;
			char remain = 0;
			char ch_a, ch_b;
			int i_a = a.size() - 1;
			int i_b = b.size() - 1;
			while (i_a >= 0 || i_b >= 0)
			{
				if (i_a >= 0) ch_a = a[i_a--] - '0'; else ch_a = 0;
				if (i_b >= 0) ch_b = b[i_b--] - '0'; else ch_b = 0;
				if (ch_a + ch_b == 0)
				{
					out += ('0' + remain);
					remain = 0;
				}
				else if (ch_a + ch_b == 1)
				{
					if (remain == 0) out += '1';
					else out += '0';
				}
				else
				{
					if (remain == 0)
					{
						out += '0';
						remain = 1;
					}
					else
					{
						out += '1';
					}
				}
			}
			if (remain == 1) out += '1';
			std::reverse(out.begin(), out.end());
			return out;
		}
	};
	void RunExample()
	{
		Solution s;

		std::string a; 
		std::string b; 
		std::string ans; 

		a = "0";
		b = "0";
		ans = s.addBinary2(a, b);
		ans = s.addBinary(a, b); // 0

		a = "10100000100100110110010000010101111011011001101110111111111101000000101111001110001111100001101";
		b = "110101001011101110001111100110001010100001101011101010000011011011001011101111001100000011011110011";
		ans = s.addBinary(a, b); // "110111101100010011000101110110100000011101000101011001000011011000001100011110011010010011000000000"
		ans = s.addBinary2(a, b);

		a = "11";
		b = "1";
		ans = s.addBinary2(a, b);
		ans = s.addBinary(a, b); // 100

		a = "1010";
		b = "1011";
		ans = s.addBinary2(a, b);
		ans = s.addBinary(a, b); // 10101
	}
}
namespace Jul_day20 // LC203 Remove Linked List Elements
{
	struct ListNode {
		int val;
		ListNode *next;
		ListNode() : val(0), next(nullptr) {}
		ListNode(int x) : val(x), next(nullptr) {}
		ListNode(int x, ListNode *next) : val(x), next(next) {}
	};

	class Solution {
	public:
		ListNode* removeElements(ListNode* head, int val)
		{
			if (!head) return nullptr;
			while (head && head->val == val)
			{
				ListNode* tmp = head;
				head = head->next;
				delete tmp;
			}
			ListNode* pRunner = head;
			while (pRunner)
			{
				if (pRunner->next && pRunner->next->val == val)
				{
					ListNode* tmp = pRunner->next;
					pRunner->next = pRunner->next->next;
					delete tmp;
				}
				pRunner = pRunner->next;
			}
			return head;
		}
	};
	void RunExample()
	{
		ListNode* head = new ListNode(1);
		ListNode* ans = Solution().removeElements(head,2);
	}

	namespace Jul_day21
	{
		class Solution {
		private:
			struct Pos
			{
				int y;
				int x;
				int i;
			}
			long long Hash(Pos& p)
			{
				return ((((long long)p.y) << 32) | p.x);
			}
		public:
			bool exist(vector<vector<char>>& board, string word)
			{
				for (int row = 0; row < board.size(); row++)
				{
					for (int col = 0; col < board[0].size(); col++)
					{
						if (board[row][col] == word[0])
						{
							std::set<long long> visited;
							std::stack<Pos> stack;
							stack.push({ row,col,1 });
							while (!stack.emtpy())
							{
								Pos curPos = stack.top(); stack.pop();
								visited.insert(Hash(curPos));
								if (row > 0 &&)

							}
						}
					}
				}
			}
		};

	}