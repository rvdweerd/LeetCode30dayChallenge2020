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
		ListNode* next;
		ListNode() : val(0), next(nullptr) {}
		ListNode(int x) : val(x), next(nullptr) {}
		ListNode(int x, ListNode* next) : val(x), next(next) {}
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
		ListNode* ans = Solution().removeElements(head, 2);
	}
}
namespace Jul_day21 // LC79 Word Search
{
	class Solution
	{
	private:
		//std::unordered_set<long long> visited;
		//inline long long Hash(int y, int x)
		//{
		//	return ((((long long)y) << 32) | x);
		//}
		//void Mark(int y, int x)
		//{
		//	visited.insert(Hash(y, x));
		//}
		//void Unmark(int y, int x)
		//{
		//	visited.erase(Hash(y, x));
		//}
		//bool NotVisited(int y, int x)
		//{
		//	return (visited.find(Hash(y, x)) == visited.end());
		//}
		bool dfs(int y, int x, int i, std::vector<std::vector<char>>& board, std::string& word)
		{
			if (i == word.size() - 1) return true;
			std::vector<std::pair<int, int>> availableNeighbors;
			if (y > 0 && board[y - 1][x] == word[i + 1]) availableNeighbors.push_back({ y - 1, x }); // CHECK NORTH
			if (y < board.size() - 1 && board[y + 1][x] == word[i + 1]) availableNeighbors.push_back({ y + 1, x }); // CHECK SOUTH
			if (x > 0 && board[y][x - 1] == word[i + 1]) availableNeighbors.push_back({ y, x - 1 }); // CHECK WEST
			if (x < board[0].size() - 1 && board[y][x + 1] == word[i + 1]) availableNeighbors.push_back({ y, x + 1 }); // CHECK EAST

			for (auto p : availableNeighbors)
			{
				char tmp = board[p.first][p.second];
				board[p.first][p.second] = '0'; // mark
				if (dfs(p.first, p.second, i + 1, board, word)) return true;
				board[p.first][p.second] = tmp; // unmark
			}
			return false;
		}
	public:
		bool exist(std::vector<std::vector<char>>& board, std::string word)
		{
			if (word.size() == 0) return true;
			if (board.size() == 0 || board[0].size() == 0) return false;
			for (int row = 0; row < board.size(); row++)
			{
				for (int col = 0; col < board[0].size(); col++)
				{
					char tmp = board[row][col];
					if (tmp == word[0])
					{
						board[row][col] = '0'; // mark
						if (dfs(row, col, 0, board, word)) return true;
						board[row][col] = tmp; // unmark
					}
				}

			}
			return false;
		}
	};
	void RunExample()
	{
		std::vector<std::vector<char>> board;
		std::string word;
		bool ans;

		board = {
			{'s','e','s'},
			{'s','t','e'},
			{'a','t','s'}
		};
		word = "test";
		ans = Solution().exist(board, word); // TRUE

		board = {
			{'A','B','C','E'},
			{'S','F','C','S'},
			{'A','D','E','E'}
		};
		word = "ABCB";
		ans = Solution().exist(board, word); // FALSE

		board = {
			{'A','B','C','E'},
			{'S','F','E','S'},
			{'A','D','E','E'}
		};
		word = "ABCESEEEFS";
		ans = Solution().exist(board, word); // TRUE

		int k = 0;
	}
}
namespace Jul_day27 // LC Construct Binary Tree from Inorder and Postorder Traversal
{

 
	struct TreeNode {
		int val;
		TreeNode *left;
		TreeNode *right;
		TreeNode() : val(0), left(nullptr), right(nullptr) {}
		TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
		TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
	};
	void PrintPre(TreeNode* tree)
	{
		if (!tree) return;
		std::cout << tree->val << ",";
		PrintPre(tree->left);
		PrintPre(tree->right);
	}
	void PrintIn(TreeNode* tree)
	{
		if (!tree) return;
		PrintIn(tree->left);
		std::cout << tree->val << ",";
		PrintIn(tree->right);
	}
	void PrintPost(TreeNode* tree)
	{
		if (!tree) return;
		PrintPost(tree->left);
		PrintPost(tree->right);
		std::cout << tree->val << ",";
	}
	void Print(TreeNode* tree)
	{
		std::cout << "Pre:  ["; PrintPre(tree); std::cout << "]"<<std::endl;
		std::cout << "In:   ["; PrintIn(tree); std::cout << "]" << std::endl;
		std::cout << "Post: ["; PrintPost(tree); std::cout << "]" << std::endl;
	}
	class Solution {
	private:
		std::stack<TreeNode*> stack;
		inline TreeNode* UnrollRight(TreeNode* n, std::vector<int>& postorder, int& i)
		{
			n->right = new TreeNode(postorder[i]);
			n = n->right;
			stack.push(n);
			i--;
			return n;
		}
		inline TreeNode* UnrollLeft(TreeNode* n, std::vector<int>& postorder, int& i)
		{
			n->left= new TreeNode(postorder[i]);
			n = n->left;
			stack.push(n);
			i--;
			return n;
		}

	public:
		TreeNode* buildTree(std::vector<int>& inorder, std::vector<int>& postorder) 
		{
			int i = postorder.size() - 1; int j = i;
			TreeNode* master = new TreeNode();
			TreeNode* ptr = master;

			if (i == 0) return nullptr;
			ptr = UnrollRight(ptr, postorder, i);
			
			while (i >= 0)
			{
				while (!stack.empty() && stack.top()->val != inorder[j])
				{
					ptr = UnrollRight(ptr, postorder, i);
				}
				while (!stack.empty() && inorder[j] == stack.top()->val)
				{
					ptr = stack.top(); stack.pop();
					j--;
				}
				if (i >= 0)
				{
					ptr = UnrollLeft(ptr, postorder, i);
				}
			}
			ptr = master->right;
			delete master;
			return ptr;
		}
	};
	void RunExample()
	{
		std::vector<int> inorder = {3,2,1,5,7,9,4,6,10,8,11};
		std::vector<int> postorder = {3,2,9,7,5,10,11,8,6,4,1};

		TreeNode* tree = new TreeNode(1, new TreeNode(2, new TreeNode(3), nullptr), new TreeNode(4, new TreeNode(5), new TreeNode(6)));
		tree->right->left->right = new TreeNode(7, nullptr, new TreeNode(9));
		tree->right->right->right = new TreeNode(8, new TreeNode(10), new TreeNode(11));
		Print(tree);

		TreeNode* ans = Solution().buildTree(inorder, postorder);

		TreeNode* tree2 = new TreeNode(1, nullptr, new TreeNode(2));
		Print(tree2);

		inorder = { 1,2 };
		postorder = { 2,1 };
		ans = Solution().buildTree(inorder, postorder);

	}
}
namespace Jul_day28 // LC621 Task Scheduler
{
	class Solution
	{
	public:
		struct Job
		{
			char ch;
			int n;
			int t_last;
		};
		struct cmp
		{
			bool operator()(const Job& left, const Job& right) const
			{
				return (left.n < right.n);

			}
		};
		std::priority_queue<Job, std::vector<Job>, cmp> pqueue;
		std::queue<Job> temp;
		std::map<char, int> map;
	public:
		int leastInterval(std::vector<char>& tasks, int n)
		{
			for (char c : tasks)
			{
				map[c]++;
			}
			for (auto p : map)
			{
				pqueue.push(Job{ p.first, p.second, -1 });
			}
			int t = 0;
			while (!pqueue.empty())
			{
				int incr = INT_MAX;
				int queueSize = pqueue.size();
				bool hit = false;
				auto cur = pqueue.top(); pqueue.pop();
				while (!hit)
				{
					if (cur.t_last < t)
					{
						hit = true;
						//std::cout << "t=" << t << "," << cur.ch << ",";
						// count++;
						if (cur.n > 1)
						{
							pqueue.push({ cur.ch, cur.n - 1, t + n });
						}
						//cur = pqueue.top(); pqueue.pop();
					}
					else
					{
						temp.push(cur);
						incr = std::min(incr, cur.t_last - t);
						if (pqueue.empty()) break;
						cur = pqueue.top(); pqueue.pop();
					}
				}
				while (!temp.empty())
				{
					if (queueSize == temp.size())
					{
						//std::cout << "[..]" << ",";
						t += incr;
					}
					pqueue.push(temp.front());
					temp.pop();
				}
				t++;
				//count++;
			}
			return t;
		}
	};
	void RunExample()
	{
		std::vector<char> tasks;
		int ans = 0;
		


		Solution s;

		tasks = { 'A', 'A', 'A', 'B', 'B', 'B' };
		ans = Solution().leastInterval(tasks, 2); //8


		tasks = { 'A', 'A', 'A', 'A', 'A', 'A', 'B', 'C', 'D', 'E', 'F', 'G' };
		ans = Solution().leastInterval(tasks, 2);  // 16

		tasks = { 'E', 'G', 'A', 'I', 'I', 'D', 'H', 'G', 'D', 'G', 'E', 'A', 'J', 'J', 'G', 'G', 'A', 'C', 'G', 'D', 'B', 'I', 'E', 'D', 'E', 'D', 'D', 'E', 'D', 'H', 'J', 'A', 'J', 'H', 'B', 'I', 'C', 'C', 'E', 'E', 'I', 'C', 'E', 'G', 'E', 'D', 'J', 'J', 'B', 'J', 'B', 'B', 'D', 'F', 'H', 'D', 'D', 'G', 'C', 'A', 'J', 'B', 'B', 'I', 'D', 'B', 'I', 'D', 'C', 'G', 'C', 'D', 'D', 'D', 'D', 'F', 'G', 'G', 'G', 'C', 'G', 'J', 'H', 'F', 'J', 'H', 'B', 'D', 'J', 'I', 'B', 'H', 'C', 'E', 'B', 'A', 'B', 'F', 'B', 'G', 'F', 'C', 'I', 'I', 'J', 'E', 'F', 'A', 'B', 'B', 'E', 'A', 'B', 'H', 'C', 'D', 'F', 'F', 'A', 'F', 'B', 'E', 'G', 'F', 'H', 'G', 'E', 'B', 'B', 'B', 'B', 'H', 'B', 'I', 'A', 'C', 'E', 'C', 'D', 'E', 'C', 'F', 'C', 'J', 'J', 'F', 'D', 'G', 'A', 'C', 'A', 'E', 'E', 'D', 'J', 'I', 'J', 'A', 'E', 'D', 'F', 'J', 'D', 'B', 'B', 'D', 'G', 'J', 'D', 'A', 'G', 'D', 'I', 'H', 'F', 'B', 'F', 'H', 'D', 'D', 'C', 'E', 'E', 'B', 'C', 'D', 'J', 'D', 'J', 'B', 'F', 'I', 'C', 'E', 'H', 'E', 'A', 'C', 'A', 'D', 'G', 'F', 'H', 'B', 'J', 'B', 'D', 'G', 'B', 'G', 'J', 'G', 'D', 'D', 'A', 'A', 'C', 'H', 'B', 'A', 'A', 'F', 'J', 'J', 'F', 'H', 'I', 'I', 'G', 'I', 'E', 'B', 'H', 'E', 'H', 'J', 'E', 'F', 'E', 'D', 'B', 'E', 'A', 'A', 'A', 'H', 'A', 'H', 'A', 'D', 'F', 'C', 'H', 'I', 'E', 'C', 'D', 'I', 'I', 'H', 'A', 'I', 'I', 'I', 'D', 'E', 'C', 'G', 'J', 'F', 'E', 'F', 'A', 'D', 'A', 'I', 'B', 'G', 'C', 'F', 'I', 'G', 'I', 'G', 'B', 'J', 'G', 'D', 'D', 'D', 'I', 'I', 'C', 'J', 'A', 'D', 'H', 'H', 'A', 'H', 'A', 'J', 'B', 'G', 'E', 'E', 'B', 'C', 'G', 'J', 'H', 'G', 'I', 'A', 'F', 'A', 'F', 'D', 'D', 'F', 'J', 'I', 'I', 'B', 'G', 'A', 'B', 'B', 'D', 'H', 'J', 'C', 'J', 'H', 'F', 'F', 'I', 'A', 'E', 'J', 'I', 'H', 'H', 'D', 'B', 'D', 'H', 'D', 'E', 'J', 'D', 'E', 'F', 'D', 'D', 'E', 'F', 'D', 'E', 'F', 'G', 'G', 'D', 'J', 'J', 'J', 'B', 'J', 'F', 'C', 'I', 'H', 'D', 'I', 'C', 'G', 'I', 'I', 'C', 'H', 'I', 'J', 'H', 'F', 'I', 'D', 'D', 'F', 'D', 'G', 'D', 'J', 'I', 'F', 'E', 'J', 'J', 'E', 'E', 'B', 'C', 'B', 'D', 'H', 'I', 'A', 'J', 'F', 'C', 'I', 'D', 'J', 'G', 'F', 'E', 'E', 'B', 'E', 'H', 'C', 'B', 'J', 'E', 'F', 'H', 'E', 'E', 'I', 'E', 'D', 'C', 'H', 'E', 'J', 'G', 'H', 'B', 'C', 'C', 'D', 'B', 'J', 'H', 'I', 'G', 'E', 'H', 'I', 'I', 'H', 'H', 'A', 'H', 'G', 'F', 'D', 'A', 'A', 'G', 'D', 'D', 'F', 'J', 'E', 'I', 'E', 'B', 'D', 'D', 'I', 'I', 'A', 'C', 'A', 'G', 'B', 'G', 'H', 'J', 'H', 'H', 'C', 'E', 'F', 'F', 'E', 'H', 'E', 'A', 'I', 'C', 'B', 'A', 'B', 'C', 'I', 'H', 'B', 'J', 'E', 'G', 'F', 'C', 'F', 'I', 'H', 'I', 'I', 'B', 'B', 'J', 'G', 'E', 'I', 'F', 'E', 'I', 'A', 'G', 'I', 'D', 'A', 'A', 'F', 'D', 'I', 'G', 'J', 'G', 'I', 'I', 'F', 'F', 'H', 'E', 'I', 'D', 'B', 'J', 'A', 'J', 'D', 'C', 'G', 'H', 'G', 'D', 'G', 'H', 'G', 'B', 'C', 'D', 'E', 'F', 'E', 'G', 'A', 'G', 'D', 'C', 'F', 'B', 'I', 'B', 'G', 'F', 'G', 'E', 'E', 'H', 'D', 'G', 'J', 'H', 'J', 'A', 'H', 'I', 'G', 'I', 'E', 'F', 'C', 'F', 'E', 'G', 'A', 'C', 'H', 'I', 'E', 'F', 'F', 'B', 'D', 'D', 'J', 'H', 'H', 'F', 'F', 'A', 'G', 'H', 'D', 'B', 'E', 'B', 'H', 'I', 'E', 'I', 'G', 'D', 'B', 'C', 'D', 'B', 'I', 'I', 'J', 'E', 'J', 'J', 'C', 'G', 'I', 'F', 'G', 'G', 'B', 'I', 'H', 'E', 'H', 'F', 'J', 'E', 'C', 'G', 'D', 'G', 'J', 'E', 'E', 'G', 'J', 'J', 'C', 'A', 'G', 'H', 'C', 'F', 'D', 'A', 'J', 'B', 'B', 'H', 'H', 'A', 'A', 'I', 'A', 'J', 'E', 'H', 'D', 'F', 'B', 'I', 'F', 'B', 'F', 'E', 'G', 'J', 'E', 'H', 'F', 'C', 'E', 'A', 'E', 'A', 'C', 'B', 'F', 'D', 'B', 'I', 'D', 'D', 'H', 'H', 'B', 'I', 'A', 'D', 'H', 'I', 'A', 'G', 'J', 'J', 'G', 'A', 'J', 'B', 'J', 'B', 'F', 'E', 'H', 'J', 'J', 'C', 'C', 'H', 'A', 'D', 'D', 'C', 'F', 'G', 'I', 'J', 'C', 'A', 'E', 'F', 'E', 'F', 'G', 'J', 'F', 'B', 'B', 'G', 'A', 'A', 'F', 'J', 'H', 'H', 'H', 'I', 'J', 'A', 'I', 'F', 'F', 'I', 'F', 'F', 'E', 'G', 'H', 'E', 'E', 'D', 'I', 'C', 'D', 'E', 'E', 'G', 'D', 'D', 'A', 'F', 'B', 'B', 'C', 'J', 'B', 'J', 'A', 'J', 'B', 'I', 'G', 'C', 'D', 'J', 'B', 'J', 'E', 'G', 'E', 'A', 'B', 'H', 'F', 'I', 'J', 'J', 'H', 'J', 'I', 'E', 'B', 'H', 'A', 'J', 'B', 'B', 'F', 'H', 'F', 'G', 'J', 'C', 'E', 'D', 'D', 'G', 'D', 'F', 'A', 'C', 'B', 'B', 'E', 'J', 'F', 'D', 'D', 'F', 'D', 'D', 'F', 'C', 'I', 'F', 'H', 'B', 'E', 'D', 'H', 'B', 'A', 'A', 'G', 'I', 'C', 'I', 'F', 'C', 'H', 'G', 'C', 'G', 'H', 'D', 'C', 'G', 'E', 'C', 'E', 'H', 'C', 'H', 'B', 'C', 'D', 'A', 'G', 'I', 'B', 'F', 'C', 'I', 'I', 'J', 'B', 'J', 'B', 'H', 'H', 'J', 'J', 'C', 'H', 'H', 'D', 'J', 'G', 'B', 'F', 'H', 'B', 'A', 'G', 'B', 'B', 'H', 'D', 'E', 'B', 'I', 'F', 'J', 'F', 'D', 'E', 'D', 'D', 'C', 'F', 'H', 'G', 'H', 'A', 'G', 'F', 'G', 'F', 'I', 'G', 'F', 'I', 'F', 'F', 'J', 'A', 'E', 'G', 'A', 'C', 'I', 'I', 'I', 'C', 'A', 'B', 'E', 'E', 'F', 'J', 'A', 'I', 'H', 'D', 'G', 'D', 'F', 'A', 'B', 'D', 'C', 'B', 'C', 'G', 'A', 'F', 'E', 'G', 'J', 'H', 'F', 'E', 'B', 'E', 'B', 'C', 'A', 'E', 'A', 'D', 'G', 'C', 'B', 'E', 'D', 'J', 'I', 'E', 'E', 'G', 'C', 'J', 'G', 'I', 'F', 'F', 'A', 'C', 'C', 'C', 'A', 'F', 'G', 'H', 'J', 'J', 'H', 'G', 'J', 'A', 'E', 'C', 'I', 'C', 'F', 'B', 'B', 'J', 'G', 'H', 'C', 'A', 'G', 'I', 'B', 'D', 'C', 'H', 'E', 'J', 'E', 'B', 'D', 'J', 'J', 'D', 'H', 'D', 'J', 'I', 'B', 'F', 'B', 'H', 'D', 'J', 'D', 'J', 'F', 'J', 'D', 'F', 'H', 'A', 'G', 'A', 'E', 'E', 'C', 'H', 'H', 'B', 'I', 'H', 'F', 'J', 'E', 'J', 'B', 'B', 'C', 'C', 'B', 'E', 'A', 'D', 'C', 'G', 'J', 'A', 'C', 'D', 'D', 'F', 'E', 'A', 'I', 'J', 'D', 'G', 'D', 'A', 'C', 'G', 'C', 'F', 'B', 'D', 'B', 'I', 'B', 'J', 'D', 'E', 'D', 'I', 'I', 'F', 'A', 'G', 'I', 'J', 'D', 'G', 'C', 'D', 'B', 'C', 'B', 'G', 'J', 'J', 'C', 'B', 'C', 'G', 'D', 'F', 'A', 'J', 'B', 'B', 'H', 'J', 'D', 'B', 'G', 'I', 'A', 'C', 'G', 'J', 'E', 'G', 'E', 'I', 'E', 'C', 'F', 'J', 'C', 'A', 'F', 'D', 'C', 'I', 'J', 'H', 'E', 'F', 'I', 'H', 'D', 'E', 'I', 'J', 'B', 'C', 'E', 'A', 'C', 'J', 'E', 'J', 'H', 'H', 'F', 'E', 'I', 'G', 'E', 'E', 'G', 'C', 'I', 'B', 'E', 'C', 'A', 'C', 'I', 'J', 'J', 'F', 'C', 'B', 'G', 'D', 'A', 'E', 'F', 'C', 'J', 'A', 'A', 'J', 'J', 'E', 'H', 'G', 'G', 'F', 'G', 'G', 'B', 'A', 'G', 'D', 'D', 'I', 'D', 'C', 'F', 'H', 'F', 'E', 'B', 'I', 'F', 'H', 'B', 'H', 'A', 'E', 'I', 'G', 'I', 'F', 'J', 'H', 'G', 'E', 'J', 'H', 'B', 'E', 'B', 'H', 'F', 'G', 'B', 'D', 'B', 'F', 'D', 'D', 'J', 'B', 'D', 'G', 'B', 'G', 'A', 'I', 'B', 'C', 'G', 'D', 'G', 'D', 'A', 'I', 'I', 'C', 'H', 'J', 'I', 'B', 'A', 'G', 'B', 'C', 'E', 'I', 'J', 'D', 'B', 'B', 'C', 'B', 'H', 'B', 'E', 'A', 'H', 'I', 'G', 'F', 'I', 'H', 'F', 'F', 'I', 'E', 'D', 'H', 'F', 'H', 'J', 'I', 'B', 'F', 'E', 'A', 'F', 'B', 'C', 'J', 'B', 'F', 'C', 'B', 'H', 'J', 'C', 'J', 'F', 'C', 'I', 'J', 'E', 'B', 'A', 'I', 'H', 'C', 'H', 'I', 'D', 'C', 'E', 'E', 'F', 'H', 'D', 'G', 'I', 'E', 'D', 'E', 'G', 'E', 'F', 'D', 'I', 'G', 'J', 'H', 'E', 'E', 'D', 'I', 'C', 'E', 'D', 'E', 'D', 'I', 'B', 'E', 'D', 'C', 'F', 'D', 'I', 'J', 'C', 'J', 'F', 'E', 'F', 'E', 'F', 'B', 'A', 'A', 'J', 'E', 'H', 'J', 'J', 'J', 'F', 'C', 'I', 'I', 'H', 'I', 'D', 'E', 'B', 'F', 'E', 'G', 'F', 'H', 'D', 'E', 'B', 'H', 'A', 'E', 'J', 'C', 'J', 'D', 'G', 'F', 'B', 'I', 'I', 'I', 'E', 'D', 'F', 'C', 'F', 'B', 'I', 'F', 'E', 'C', 'I', 'F', 'C', 'F', 'J', 'E', 'F', 'J', 'D', 'I', 'A', 'D', 'A', 'B', 'I', 'H', 'F', 'A', 'D', 'C', 'I', 'G', 'E', 'I', 'A', 'B', 'A', 'A', 'C', 'H', 'C', 'F', 'C', 'D', 'J', 'B', 'D', 'H', 'E', 'C', 'B', 'B', 'I', 'G', 'H', 'G', 'J', 'C', 'D', 'H', 'E', 'I', 'H', 'J', 'A', 'J', 'H', 'H', 'H', 'D', 'D', 'F', 'J', 'B', 'D', 'I', 'G', 'I', 'C', 'C', 'G', 'I', 'A', 'E', 'D', 'A', 'H', 'F', 'F', 'G', 'C', 'E', 'G', 'G', 'E', 'I', 'H', 'C', 'A', 'H', 'D', 'F', 'F', 'J', 'I', 'E', 'C', 'D', 'A', 'C', 'F', 'H', 'H', 'B', 'E', 'F', 'C', 'E', 'C', 'B', 'D', 'B', 'G', 'D', 'G', 'F', 'A', 'D', 'C', 'I', 'E', 'H', 'B', 'G', 'C', 'H', 'G', 'C', 'A', 'H', 'C', 'E', 'I', 'C', 'C', 'E', 'I', 'C', 'C', 'I', 'B', 'C', 'I', 'A', 'H', 'H', 'H', 'H', 'C', 'E', 'G', 'D', 'J', 'B', 'D', 'G', 'C', 'A', 'F', 'B', 'E', 'J', 'B', 'F', 'B', 'G', 'C', 'D', 'D', 'A', 'F', 'F', 'F', 'C', 'E', 'C', 'C', 'C', 'G', 'G', 'E', 'B', 'E', 'E', 'E', 'A', 'D', 'I', 'A', 'C', 'G', 'I', 'G', 'D', 'J', 'B', 'A', 'C', 'C', 'H', 'H', 'A', 'G', 'C', 'G', 'C', 'C', 'E', 'D', 'F', 'A', 'E', 'D', 'H', 'C', 'F', 'I', 'J', 'H', 'B', 'D', 'J', 'A', 'B', 'H', 'D', 'D', 'E', 'D', 'F', 'C', 'J', 'E', 'B', 'A', 'B', 'A', 'E', 'H', 'H', 'C', 'J', 'G', 'A', 'F', 'H', 'D', 'J', 'C', 'E', 'J', 'I', 'A', 'I', 'C', 'H', 'D', 'E', 'E', 'E', 'I', 'H', 'B', 'D', 'H', 'F', 'J', 'J', 'F', 'H', 'J', 'A', 'G', 'H', 'D', 'J', 'D', 'I', 'H', 'I', 'B', 'F', 'E', 'B', 'J', 'D', 'H', 'H', 'F', 'D', 'D', 'F', 'F', 'J', 'F', 'G', 'F', 'C', 'C', 'I', 'D', 'C', 'A', 'H', 'E', 'J', 'C', 'A', 'G', 'D', 'E', 'A', 'J', 'H', 'D', 'B', 'E', 'D', 'F', 'A', 'C', 'C', 'H', 'A', 'I', 'E', 'I', 'J', 'G', 'C', 'H', 'J', 'B', 'J', 'I', 'J', 'D', 'G', 'G', 'A', 'E', 'I', 'A', 'E', 'D', 'H', 'J', 'J', 'H', 'E', 'C', 'F', 'E', 'G', 'A', 'F', 'F', 'J', 'H', 'A', 'B', 'F', 'C', 'B', 'A', 'B', 'E', 'D', 'B', 'J', 'C', 'A', 'A', 'A', 'E', 'D', 'F', 'E', 'I', 'H', 'C', 'I', 'G', 'E', 'G', 'E', 'B', 'F', 'I', 'J', 'A', 'D', 'F', 'B', 'H', 'G', 'J', 'J', 'G', 'J', 'C', 'E', 'G', 'E', 'D', 'I', 'D', 'F', 'D', 'G', 'A', 'A', 'E', 'A', 'I', 'F', 'I', 'C', 'F', 'A', 'H', 'G', 'A', 'D', 'H', 'D', 'H', 'B', 'E', 'E', 'J', 'H', 'I', 'D', 'A', 'J', 'I', 'G', 'A', 'E', 'G', 'F', 'H', 'E', 'F', 'H', 'B', 'G', 'J', 'G', 'B', 'I', 'A', 'G', 'C', 'F', 'B', 'J', 'H', 'I', 'H', 'A', 'F', 'E', 'E', 'E', 'H', 'A', 'J', 'E', 'D', 'H', 'C', 'D', 'D', 'C', 'B', 'H', 'J', 'A', 'C', 'D', 'C', 'E', 'E', 'F', 'I', 'I', 'F', 'C', 'C', 'I', 'E', 'C', 'G', 'J', 'G', 'B', 'F', 'J', 'F', 'C', 'G', 'B', 'I', 'I', 'A', 'E', 'E', 'C', 'C', 'H', 'J', 'F', 'E', 'F', 'J', 'E', 'D', 'J', 'C', 'I', 'B', 'F', 'E', 'I', 'I', 'A', 'B', 'A', 'F', 'F', 'D', 'E', 'J', 'B', 'I', 'H', 'I', 'B', 'C', 'C', 'A', 'J', 'D', 'D', 'C', 'E', 'G', 'A', 'G', 'F', 'D', 'I', 'C', 'F', 'J', 'A', 'E', 'G', 'B', 'D', 'C', 'A', 'C', 'C', 'J', 'I', 'H', 'A', 'E', 'H', 'I', 'G', 'I', 'I', 'H', 'I', 'E', 'D', 'C', 'A', 'E', 'B', 'I', 'I', 'F', 'J', 'G', 'E', 'C', 'C', 'E', 'E', 'G', 'I', 'B', 'B', 'C', 'J', 'F', 'D', 'H', 'E', 'I', 'F', 'D', 'J', 'C', 'B', 'G', 'J', 'D', 'J', 'D', 'H', 'D', 'F', 'B', 'A', 'J', 'H', 'F', 'E', 'G', 'C', 'D', 'C', 'G', 'D', 'F', 'F', 'F', 'G', 'H', 'E', 'F', 'I', 'B', 'I', 'H', 'D', 'B', 'C', 'H', 'J', 'D', 'E', 'G', 'J', 'H', 'I', 'E', 'B', 'B', 'H', 'D', 'B', 'H', 'D', 'A', 'B', 'B', 'D', 'B', 'D', 'H', 'D', 'A', 'B', 'H', 'B', 'A', 'A', 'B', 'A', 'H', 'A', 'E', 'G', 'A', 'C', 'F', 'G', 'D', 'D', 'H', 'A', 'H', 'A', 'E', 'I', 'H', 'C', 'C', 'H', 'E', 'E', 'B', 'C', 'J', 'A', 'I', 'B', 'B', 'J', 'I', 'J', 'I', 'G', 'J', 'C', 'D', 'J', 'I', 'H', 'H', 'G', 'I', 'J', 'H', 'G', 'I', 'G', 'B', 'G', 'D', 'A', 'G', 'C', 'J', 'H', 'D', 'J', 'J', 'B', 'B', 'F', 'E', 'B', 'E', 'I', 'J', 'D', 'G', 'E', 'D', 'E', 'I', 'G', 'E', 'E', 'I', 'G', 'C', 'C', 'E', 'B', 'G', 'E', 'B', 'C', 'F', 'B', 'J', 'E', 'C', 'I', 'E', 'F', 'J', 'I', 'D', 'B', 'J', 'B', 'C', 'A', 'H', 'A', 'J', 'G', 'F', 'G', 'F', 'A', 'F', 'C', 'B', 'J', 'H', 'G', 'E', 'J', 'D', 'I', 'C', 'A', 'F', 'J', 'G', 'I', 'I', 'A', 'C', 'J', 'D', 'G', 'E', 'F', 'C', 'D', 'F', 'D', 'G', 'J', 'F', 'B', 'F', 'J', 'H', 'A', 'I', 'A', 'E', 'D', 'A', 'E', 'B', 'E', 'A', 'I', 'H', 'H', 'B', 'C', 'F', 'C', 'J', 'E', 'F', 'H', 'F', 'C', 'D', 'H', 'J', 'B', 'A', 'E', 'B', 'J', 'C', 'B', 'H', 'D', 'F', 'C', 'E', 'A', 'C', 'A', 'E', 'I', 'D', 'D', 'H', 'E', 'A', 'G', 'J', 'D', 'B', 'C', 'D', 'B', 'F', 'A', 'C', 'I', 'E', 'F', 'B', 'J', 'J', 'B', 'J', 'E', 'E', 'D', 'F', 'A', 'I', 'D', 'C', 'D', 'J', 'J', 'B', 'C', 'H', 'H', 'G', 'B', 'E', 'A', 'F', 'I', 'H', 'C', 'G', 'A', 'C', 'H', 'C', 'D', 'C', 'C', 'I', 'J', 'G', 'I', 'C', 'C', 'A', 'E', 'I', 'F', 'H', 'G', 'A', 'I', 'E', 'H', 'D', 'C', 'H', 'C', 'F', 'D', 'B', 'F', 'F', 'G', 'B', 'F', 'B', 'G', 'E', 'G', 'I', 'G', 'A', 'C', 'H', 'G', 'H', 'D', 'C', 'J', 'A', 'H', 'F', 'J', 'F', 'E', 'D', 'B', 'F', 'B', 'C', 'B', 'H', 'J', 'E', 'H', 'F', 'B', 'A', 'B', 'D', 'A', 'B', 'F', 'A', 'E', 'J', 'D', 'F', 'F', 'F', 'F', 'C', 'A', 'A', 'J', 'E', 'A', 'D', 'E', 'E', 'A', 'C', 'F', 'C', 'F', 'I', 'E', 'J', 'D', 'A', 'D', 'G', 'J', 'B', 'E', 'F', 'F', 'E', 'E', 'H', 'A', 'A', 'G', 'E', 'B', 'J', 'B', 'G', 'C', 'A', 'I', 'H', 'H', 'I', 'E', 'D', 'I', 'A', 'J', 'D', 'F', 'B', 'G', 'B', 'E', 'I', 'H', 'E', 'D', 'D', 'I', 'B', 'D', 'F', 'I', 'H', 'C', 'A', 'G', 'F', 'B', 'E', 'A', 'I', 'J', 'G', 'G', 'F', 'F', 'I', 'C', 'I', 'E', 'H', 'F', 'F', 'C', 'E', 'J', 'F', 'E', 'H', 'C', 'F', 'H', 'I', 'A', 'A', 'J', 'J', 'H', 'J', 'C', 'D', 'G', 'H', 'C', 'F', 'A', 'C', 'G', 'H', 'A', 'G', 'E', 'D', 'E', 'B', 'F', 'C', 'H', 'C', 'H', 'C', 'C', 'J', 'I', 'G', 'F', 'B', 'I', 'E', 'I', 'B', 'J', 'H', 'C', 'F', 'E', 'E', 'A', 'H', 'G', 'G', 'J', 'H', 'C', 'B', 'F', 'D', 'D', 'A', 'H', 'F', 'A', 'C', 'A', 'A', 'G', 'F', 'J', 'E', 'G', 'H', 'D', 'J', 'H', 'G', 'C', 'B', 'H', 'H', 'J', 'J', 'B', 'G', 'G', 'G', 'E', 'G', 'B', 'D', 'A', 'H', 'A', 'I', 'F', 'J', 'B', 'F', 'G', 'H', 'B', 'B', 'F', 'F', 'G', 'A', 'B', 'D', 'I', 'I', 'E', 'G', 'I', 'E', 'G', 'E', 'B', 'H', 'I', 'C', 'B', 'D', 'B', 'E', 'B', 'C', 'G', 'B', 'J', 'G', 'G', 'H', 'B', 'J', 'F', 'D', 'C', 'D', 'D', 'J', 'H', 'C', 'E', 'H', 'B', 'H', 'C', 'D', 'G', 'G', 'A', 'I', 'I', 'I', 'H', 'F', 'G', 'B', 'I', 'C', 'A', 'E', 'C', 'E', 'E', 'F', 'E', 'A', 'G', 'H', 'C', 'I', 'I', 'J', 'J', 'A', 'C', 'I', 'E', 'J', 'I', 'B', 'E', 'B', 'I', 'A', 'H', 'A', 'B', 'J', 'C', 'I', 'C', 'G', 'I', 'D', 'J', 'B', 'J', 'A', 'E', 'G', 'H', 'C', 'D', 'C', 'E', 'H', 'B', 'F', 'J', 'C', 'C', 'C', 'A', 'J', 'G', 'F', 'J', 'H', 'A', 'A', 'D', 'I', 'F', 'I', 'H', 'E', 'J', 'J', 'B', 'B', 'I', 'C', 'E', 'H', 'F', 'F', 'H', 'C', 'A', 'E', 'B', 'H', 'E', 'F', 'H', 'H', 'E', 'G', 'I', 'D', 'E', 'G', 'G', 'J', 'H', 'J', 'E', 'J', 'E', 'B', 'J', 'E', 'E', 'I', 'J', 'C', 'B', 'D', 'I', 'H', 'A', 'H', 'J', 'B', 'J', 'B', 'B', 'G', 'F', 'J', 'H', 'C', 'D', 'H', 'J', 'A', 'F', 'G', 'C', 'D', 'H', 'J', 'E', 'F', 'J', 'D', 'B', 'G', 'C', 'A', 'D', 'I', 'D', 'H', 'C', 'D', 'G', 'I', 'J', 'J', 'G', 'C', 'J', 'B', 'G', 'G', 'I', 'D', 'G', 'E', 'D', 'C', 'B', 'D', 'E', 'F', 'A', 'A', 'F', 'H', 'D', 'F', 'J', 'E', 'A', 'C', 'I', 'J', 'H', 'H', 'J', 'H', 'J', 'C', 'B', 'G', 'I', 'E', 'C', 'H', 'B', 'H', 'C', 'A', 'D', 'B', 'B', 'J', 'I', 'J', 'A', 'F', 'I', 'A', 'B', 'F', 'G', 'F', 'I', 'J', 'G', 'C', 'H', 'H', 'I', 'A', 'C', 'I', 'G', 'H', 'D', 'J', 'G', 'H', 'F', 'B', 'G', 'H', 'A', 'A', 'I', 'C', 'C', 'A', 'J', 'A', 'E', 'C', 'E', 'D', 'C', 'A', 'E', 'J', 'D', 'J', 'A', 'F', 'A', 'D', 'H', 'G', 'H', 'C', 'F', 'D', 'C', 'C', 'B', 'I', 'I', 'B', 'E', 'D', 'G', 'B', 'B', 'F', 'E', 'C', 'B', 'F', 'B', 'H', 'A', 'A', 'G', 'I', 'C', 'J', 'I', 'J', 'C', 'F', 'I', 'J', 'F', 'H', 'E', 'I', 'G', 'I', 'I', 'D', 'G', 'B', 'G', 'C', 'D', 'G', 'G', 'F', 'C', 'A', 'H', 'I', 'C', 'B', 'I', 'A', 'J', 'I', 'H', 'D', 'A', 'F', 'D', 'C', 'F', 'C', 'G', 'D', 'J', 'C', 'H', 'H', 'A', 'C', 'B', 'A', 'C', 'D', 'C', 'D', 'A', 'G', 'E', 'A', 'F', 'A', 'B', 'B', 'D', 'D', 'C', 'F', 'J', 'D', 'F', 'E', 'I', 'F', 'G', 'F', 'F', 'A', 'E', 'A', 'H', 'C', 'E', 'J', 'F', 'E', 'G', 'I', 'D', 'F', 'A', 'G', 'H', 'A', 'F', 'A', 'I', 'C', 'E', 'A', 'A', 'B', 'G', 'H', 'F', 'J', 'D', 'I', 'B', 'B', 'H', 'B', 'B', 'G', 'F', 'I', 'C', 'J', 'F', 'C', 'E', 'G', 'C', 'H', 'E', 'B', 'D', 'D', 'B', 'I', 'E', 'C', 'F', 'G', 'F', 'G', 'D', 'D', 'D', 'G', 'I', 'A', 'A', 'B', 'A', 'D', 'A', 'C', 'H', 'E', 'A', 'J', 'J', 'E', 'I', 'C', 'D', 'H', 'D', 'F', 'J', 'H', 'C', 'J', 'D', 'D', 'D', 'D', 'E', 'E', 'C', 'H', 'J', 'D', 'C', 'B', 'H', 'G', 'D', 'C', 'D', 'D', 'B', 'B', 'C', 'G', 'G', 'I', 'F', 'D', 'C', 'B', 'C', 'A', 'H', 'G', 'D', 'J', 'J', 'A', 'B', 'H', 'D', 'C', 'C', 'G', 'E', 'H', 'I', 'J', 'J', 'A', 'F', 'F', 'C', 'F', 'G', 'C', 'C', 'F', 'E', 'G', 'F', 'F', 'G', 'A', 'A', 'H', 'E', 'J', 'F', 'H', 'F', 'I', 'D', 'J', 'I', 'B', 'D', 'D', 'C', 'B', 'E', 'B', 'B', 'E', 'J', 'F', 'E', 'E', 'H', 'B', 'H', 'J', 'E', 'J', 'H', 'J', 'F', 'A', 'A', 'I', 'D', 'G', 'C', 'J', 'G', 'C', 'A', 'F', 'D', 'C', 'A', 'F', 'F', 'G', 'F', 'J', 'C', 'G', 'B', 'H', 'C', 'C', 'C', 'E', 'F', 'C', 'I', 'B', 'I', 'A', 'D', 'E', 'I', 'I', 'C', 'B', 'F', 'A', 'A', 'D', 'A', 'B', 'I', 'A', 'A', 'H', 'H', 'H', 'H', 'H', 'F', 'I', 'A', 'F', 'D', 'J', 'D', 'J', 'B', 'B', 'B', 'B', 'A', 'A', 'H', 'I', 'G', 'G', 'D', 'H', 'D', 'C', 'C', 'I', 'G', 'A', 'C', 'A', 'B', 'E', 'C', 'D', 'G', 'I', 'A', 'I', 'C', 'J', 'C', 'A', 'I', 'C', 'A', 'C', 'H', 'D', 'H', 'D', 'B', 'C', 'A', 'D', 'C', 'C', 'J', 'J', 'D', 'C', 'F', 'E', 'C', 'H', 'C', 'H', 'H', 'J', 'J', 'G', 'B', 'I', 'E', 'H', 'I', 'G', 'J', 'B', 'A', 'C', 'B', 'C', 'H', 'H', 'J', 'F', 'C', 'J', 'I', 'C', 'C', 'F', 'B', 'J', 'D', 'F', 'F', 'C', 'C', 'C', 'D', 'J', 'D', 'D', 'B', 'F', 'G', 'E', 'C', 'I', 'G', 'D', 'E', 'F', 'D', 'C', 'G', 'I', 'A', 'F', 'I', 'F', 'I', 'A', 'J', 'A', 'F', 'B', 'B', 'D', 'C', 'J', 'J', 'B', 'D', 'C', 'C', 'B', 'J', 'D', 'E', 'D', 'J', 'E', 'E', 'B', 'H', 'G', 'G', 'I', 'J', 'I', 'J', 'F', 'F', 'F', 'F', 'D', 'H', 'G', 'H', 'J', 'D', 'G', 'F', 'C', 'B', 'H', 'E', 'D', 'F', 'F', 'C', 'G', 'D', 'J', 'I', 'E', 'E', 'E', 'E', 'E', 'C', 'E', 'F', 'A', 'B', 'J', 'C', 'J', 'J', 'D', 'E', 'E', 'I', 'G', 'A', 'D', 'B', 'H', 'C', 'A', 'I', 'A', 'G', 'C', 'H', 'A', 'F', 'C', 'D', 'I', 'A', 'E', 'J', 'J', 'J', 'E', 'J', 'I', 'B', 'C', 'C', 'D', 'I', 'F', 'D', 'H', 'B', 'A', 'H', 'F', 'A', 'I', 'E', 'B', 'D', 'E', 'I', 'G', 'J', 'B', 'A', 'C', 'A', 'J', 'C', 'F', 'J', 'I', 'F', 'C', 'C', 'D', 'E', 'J', 'B', 'I', 'D', 'D', 'E', 'H', 'F', 'D', 'C', 'I', 'I', 'H', 'A', 'J', 'F', 'G', 'H', 'J', 'I', 'J', 'F', 'F', 'H', 'F', 'G', 'A', 'A', 'G', 'J', 'D', 'B', 'I', 'I', 'G', 'E', 'B', 'D', 'B', 'A', 'J', 'H', 'I', 'F', 'I', 'B', 'J', 'E', 'J', 'J', 'A', 'F', 'C', 'F', 'C', 'B', 'D', 'H', 'B', 'B', 'B', 'F', 'A', 'E', 'B', 'C', 'H', 'A', 'D', 'G', 'I', 'G', 'E', 'A', 'C', 'F', 'I', 'D', 'F', 'F', 'C', 'J', 'I', 'G', 'F', 'J', 'A', 'E', 'I', 'E', 'F', 'E', 'J', 'H', 'G', 'A', 'E', 'E', 'H', 'A', 'J', 'G', 'J', 'F', 'D', 'J', 'J', 'H', 'I', 'C', 'D', 'E', 'E', 'C', 'B', 'A', 'G', 'D', 'D', 'A', 'I', 'F', 'J', 'H', 'C', 'I', 'A', 'E', 'G', 'D', 'A', 'I', 'E', 'I', 'B', 'H', 'A', 'I', 'C', 'J', 'A', 'D', 'F', 'F', 'B', 'B', 'D', 'I', 'A', 'B', 'D', 'C', 'D', 'J', 'H', 'B', 'F', 'E', 'B', 'C', 'G', 'D', 'B', 'J', 'C', 'C', 'D', 'F', 'E', 'C', 'J', 'I', 'E', 'G', 'B', 'E', 'D', 'G', 'G', 'B', 'D', 'F', 'H', 'E', 'D', 'J', 'F', 'I', 'G', 'A', 'H', 'F', 'E', 'C', 'B', 'C', 'D', 'H', 'B', 'A', 'I', 'F', 'J', 'A', 'C', 'F', 'E', 'H', 'G', 'B', 'C', 'A', 'F', 'F', 'B', 'H', 'D', 'F', 'G', 'C', 'G', 'J', 'H', 'F', 'I', 'F', 'G', 'F', 'A', 'E', 'H', 'D', 'D', 'I', 'E', 'H', 'C', 'B', 'C', 'J', 'F', 'D', 'I', 'F', 'D', 'G', 'G', 'G', 'J', 'I', 'H', 'C', 'C', 'I', 'J', 'F', 'B', 'J', 'C', 'H', 'F', 'E', 'F', 'H', 'J', 'B', 'H', 'D', 'E', 'I', 'H', 'E', 'E', 'D', 'G', 'J', 'F', 'B', 'C', 'C', 'F', 'A', 'F', 'H', 'B', 'B', 'D', 'I', 'G', 'E', 'E', 'C', 'B', 'B', 'F', 'A', 'B', 'J', 'A', 'J', 'J', 'G', 'J', 'G', 'I', 'B', 'F', 'C', 'D', 'I', 'B', 'C', 'H', 'H', 'J', 'J', 'D', 'G', 'G', 'H', 'G', 'H', 'E', 'B', 'A', 'G', 'F', 'B', 'G', 'B', 'I', 'G', 'D', 'A', 'J', 'F', 'F', 'E', 'J', 'H', 'H', 'J', 'J', 'E', 'G', 'J', 'H', 'A', 'E', 'G', 'H', 'B', 'A', 'D', 'E', 'F', 'C', 'B', 'J', 'A', 'I', 'E', 'C', 'B', 'F', 'B', 'J', 'A', 'B', 'I', 'B', 'J', 'H', 'I', 'H', 'E', 'A', 'I', 'H', 'I', 'C', 'D', 'J', 'E', 'A', 'D', 'C', 'B', 'I', 'F', 'B', 'D', 'G', 'C', 'E', 'J', 'G', 'D', 'F', 'F', 'C', 'I', 'H', 'J', 'C', 'I', 'I', 'I', 'G', 'E', 'F', 'J', 'D', 'J', 'C', 'F', 'A', 'F', 'H', 'I', 'G', 'C', 'G', 'I', 'H', 'E', 'D', 'B', 'E', 'I', 'A', 'F', 'F', 'C', 'C', 'A', 'D', 'J', 'E', 'D', 'D', 'G', 'J', 'A', 'A', 'E', 'A', 'D', 'G', 'E', 'I', 'C', 'A', 'J', 'H', 'I', 'B', 'C', 'E', 'H', 'J', 'B', 'C', 'D', 'G', 'A', 'F', 'G', 'F', 'A', 'J', 'G', 'C', 'E', 'J', 'G', 'G', 'H', 'E', 'I', 'A', 'I', 'J', 'I', 'I', 'E', 'E', 'B', 'G', 'B', 'J', 'E', 'E', 'H', 'D', 'E', 'J', 'I', 'B', 'I', 'B', 'C', 'A', 'C', 'I', 'B', 'D', 'E', 'B', 'H', 'F', 'F', 'B', 'D', 'B', 'G', 'I', 'E', 'E', 'D', 'C', 'A', 'J', 'E', 'B', 'B', 'D', 'G', 'C', 'F', 'I', 'J', 'E', 'D', 'C', 'E', 'A', 'E', 'F', 'E', 'A', 'B', 'A', 'H', 'F', 'B', 'I', 'E', 'E', 'B', 'A', 'E', 'D', 'D', 'G', 'H', 'A', 'B', 'I', 'J', 'D', 'I', 'C', 'E', 'B', 'B', 'J', 'G', 'D', 'B', 'I', 'B', 'E', 'J', 'E', 'G', 'I', 'A', 'I', 'E', 'J', 'B', 'H', 'C', 'J', 'J', 'G', 'C', 'B', 'I', 'H', 'D', 'H', 'D', 'A', 'E', 'D', 'H', 'J', 'B', 'J', 'B', 'J', 'B', 'D', 'F', 'D', 'A', 'D', 'C', 'C', 'G', 'A', 'G', 'G', 'F', 'C', 'C', 'C', 'A', 'A', 'G', 'C', 'J', 'B', 'J', 'H', 'G', 'J', 'C', 'G', 'A', 'J', 'J', 'E', 'C', 'F', 'J', 'C', 'J', 'H', 'J', 'C', 'E', 'A', 'D', 'C', 'B', 'C', 'G', 'H', 'E', 'E', 'I', 'C', 'F', 'F', 'B', 'F', 'I', 'F', 'G', 'D', 'B', 'F', 'A', 'E', 'D', 'H', 'A', 'C', 'J', 'F', 'I', 'E', 'F', 'D', 'F', 'C', 'F', 'J', 'D', 'A', 'H', 'E', 'G', 'G', 'B', 'G', 'A', 'H', 'H', 'J', 'D', 'C', 'E', 'J', 'G', 'I', 'D', 'E', 'F', 'J', 'D', 'C', 'F', 'C', 'C', 'C', 'A', 'C', 'J', 'E', 'E', 'G', 'A', 'B', 'H', 'H', 'C', 'F', 'A', 'H', 'B', 'J', 'I', 'I', 'F', 'J', 'I', 'G', 'G', 'J', 'B', 'J', 'I', 'E', 'F', 'J', 'E', 'C', 'C', 'D', 'C', 'G', 'E', 'G', 'F', 'B', 'H', 'G', 'F', 'J', 'H', 'A', 'C', 'I', 'C', 'J', 'G', 'E', 'C', 'J', 'C', 'H', 'F', 'G', 'E', 'C', 'J', 'F', 'B', 'D', 'E', 'A', 'I', 'H', 'D', 'D', 'B', 'E', 'C', 'J', 'I', 'G', 'C', 'F', 'J', 'B', 'G', 'E', 'H', 'H', 'H', 'F', 'F', 'F', 'I', 'I', 'A', 'D', 'A', 'C', 'C', 'G', 'H', 'G', 'A', 'A', 'G', 'F', 'D', 'I', 'F', 'A', 'H', 'C', 'C', 'I', 'G', 'F', 'H', 'A', 'C', 'C', 'C', 'G', 'G', 'G', 'F', 'H', 'B', 'B', 'D', 'E', 'J', 'A', 'I', 'A', 'G', 'C', 'D', 'G', 'B', 'A', 'B', 'I', 'F', 'F', 'D', 'H', 'G', 'J', 'G', 'C', 'I', 'D', 'F', 'B', 'E', 'J', 'A', 'A', 'J', 'I', 'H', 'G', 'F', 'A', 'J', 'J', 'I', 'H', 'B', 'C', 'A', 'J', 'F', 'I', 'B', 'A', 'B', 'G', 'I', 'H', 'F', 'H', 'A', 'E', 'A', 'B', 'A', 'D', 'E', 'G', 'I', 'G', 'A', 'G', 'A', 'G', 'H', 'D', 'D', 'B', 'I', 'D', 'F', 'A', 'H', 'J', 'A', 'C', 'A', 'I', 'D', 'I', 'G', 'I', 'A', 'I', 'A', 'A', 'H', 'J', 'G', 'D', 'J', 'J', 'F', 'E', 'C', 'G', 'G', 'D', 'C', 'B', 'D', 'D', 'E', 'I', 'G', 'A', 'D', 'B', 'E', 'C', 'F', 'E', 'D', 'I', 'J', 'H', 'B', 'J', 'I', 'J', 'H', 'C', 'B', 'E', 'C', 'E', 'G', 'G', 'J', 'E', 'F', 'B', 'A', 'B', 'A', 'E', 'F', 'H', 'E', 'D', 'D', 'B', 'A', 'A', 'D', 'J', 'G', 'F', 'I', 'J', 'I', 'G', 'E', 'E', 'B', 'A', 'B', 'G', 'C', 'H', 'H', 'G', 'E', 'G', 'A', 'A', 'G', 'G', 'I', 'A', 'D', 'J', 'G', 'F', 'H', 'F', 'F', 'C', 'G', 'E', 'C', 'G', 'J', 'B', 'E', 'G', 'G', 'I', 'I', 'C', 'H', 'H', 'H', 'A', 'G', 'J', 'C', 'F', 'F', 'B', 'G', 'B', 'H', 'E', 'D', 'C', 'E', 'E', 'C', 'D', 'B', 'J', 'J', 'J', 'A', 'D', 'F', 'D', 'E', 'H', 'E', 'A', 'H', 'J', 'G', 'A', 'D', 'G', 'A', 'J', 'G', 'E', 'J', 'F', 'D', 'D', 'E', 'H', 'B', 'C', 'D', 'D', 'G', 'B', 'I', 'I', 'E', 'I', 'E', 'E', 'G', 'A', 'I', 'E', 'B', 'C', 'B', 'H', 'B', 'J', 'J', 'A', 'G', 'D', 'C', 'B', 'G', 'E', 'I', 'B', 'F', 'F', 'F', 'A', 'E', 'I', 'J', 'D', 'I', 'I', 'B', 'H', 'A', 'F', 'H', 'J', 'F', 'B', 'I', 'J', 'B', 'B', 'F', 'F', 'J', 'J', 'A', 'A', 'G', 'F', 'C', 'F', 'C', 'B', 'H', 'H', 'J', 'B', 'B', 'I', 'A', 'B', 'B', 'H', 'B', 'H', 'H', 'E', 'I', 'H', 'H', 'C', 'F', 'J', 'E', 'E', 'G', 'J', 'A', 'G', 'J', 'B', 'E', 'E', 'D', 'H', 'B', 'D', 'E', 'F', 'C', 'G', 'H', 'H', 'B', 'E', 'E', 'A', 'B', 'E', 'D', 'D', 'J', 'J', 'F', 'J', 'H', 'A', 'B', 'D', 'C', 'J', 'A', 'I', 'C', 'F', 'C', 'B', 'B', 'E', 'A', 'F', 'G', 'C', 'F', 'A', 'A', 'J', 'A', 'E', 'A', 'E', 'C', 'A', 'E', 'C', 'D', 'E', 'C', 'D', 'J', 'A', 'D', 'F', 'I', 'E', 'E', 'B', 'H', 'J', 'B', 'C', 'F', 'A', 'E', 'J', 'J', 'I', 'B', 'F', 'C', 'C', 'F', 'C', 'I', 'D', 'B', 'A', 'I', 'E', 'E', 'H', 'A', 'C', 'J', 'I', 'C', 'C', 'G', 'H', 'A', 'D', 'G', 'H', 'E', 'G', 'I', 'J', 'C', 'E', 'C', 'C', 'E', 'F', 'I', 'D', 'A', 'B', 'H', 'H', 'E', 'H', 'H', 'H', 'E', 'B', 'E', 'D', 'F', 'I', 'C', 'B', 'B', 'I', 'I', 'I', 'I', 'A', 'F', 'C', 'H', 'H', 'E', 'I', 'G', 'G', 'I', 'B', 'I', 'B', 'E', 'H', 'A', 'G', 'G', 'I', 'I', 'H', 'G', 'D', 'F', 'J', 'A', 'E', 'H', 'G', 'A', 'J', 'I', 'C', 'F', 'A', 'I', 'C', 'B', 'C', 'J', 'H', 'J', 'C', 'E', 'G', 'H', 'H', 'D', 'G', 'J', 'B', 'I', 'E', 'C', 'B', 'F', 'J', 'G', 'I', 'G', 'J', 'F', 'B', 'C', 'A', 'D', 'D', 'C', 'C', 'E', 'J', 'H', 'G', 'G', 'C', 'E', 'G', 'E', 'I', 'B', 'H', 'G', 'D', 'I', 'D', 'J', 'C', 'C', 'F', 'J', 'B', 'A', 'C', 'H', 'J', 'H', 'H', 'I', 'F', 'J', 'C', 'D', 'J', 'G', 'D', 'A', 'C', 'E', 'J', 'F', 'J', 'D', 'I', 'A', 'I', 'A', 'A', 'C', 'C', 'H', 'J', 'J', 'E', 'I', 'B', 'J', 'H', 'D', 'G', 'C', 'J', 'G', 'J', 'G', 'E', 'F', 'J', 'E', 'F', 'C', 'C', 'B', 'G', 'J', 'B', 'B', 'G', 'A', 'C', 'F', 'H', 'B', 'H', 'J', 'B', 'C', 'F', 'D', 'A', 'C', 'H', 'H', 'J', 'A', 'G', 'C', 'D', 'G', 'G', 'E', 'A', 'F', 'G', 'J', 'C', 'D', 'D', 'I', 'G', 'E', 'A', 'A', 'C', 'I', 'I', 'A', 'C', 'J', 'D', 'B', 'F', 'F', 'F', 'F', 'J', 'G', 'F', 'E', 'J', 'I', 'J', 'H', 'H', 'H', 'G', 'H', 'J', 'A', 'F', 'G', 'E', 'E', 'H', 'A', 'A', 'C', 'I', 'C', 'H', 'I', 'H', 'A', 'J', 'F', 'B', 'G', 'F', 'H', 'E', 'H', 'B', 'E', 'H', 'C', 'F', 'G', 'B', 'G', 'H', 'H', 'H', 'G', 'D', 'C', 'H', 'F', 'I', 'F', 'G', 'B', 'A', 'I', 'H', 'J', 'G', 'J', 'I', 'H', 'J', 'A', 'I', 'I', 'F', 'F', 'C', 'B', 'B', 'B', 'G', 'I', 'C', 'D', 'B', 'A', 'B', 'H', 'H', 'C', 'F', 'D', 'J', 'H', 'G', 'D', 'F', 'D', 'H', 'C', 'J', 'H', 'B', 'D', 'E', 'B', 'A', 'E', 'E', 'I', 'C', 'J', 'B', 'C', 'G', 'A', 'D', 'J', 'A', 'D', 'H', 'A', 'A', 'H', 'D', 'H', 'B', 'B', 'G', 'F', 'B', 'I', 'I', 'E', 'H', 'G', 'C', 'H', 'A', 'E', 'E', 'C', 'C', 'C', 'J', 'I', 'A', 'G', 'E', 'E', 'D', 'D', 'G', 'H', 'F', 'F', 'B', 'C', 'D', 'H', 'I', 'B', 'D', 'G', 'A', 'E', 'H', 'B', 'H', 'I', 'I', 'G', 'E', 'C', 'F', 'B', 'G', 'E', 'J', 'E', 'H', 'E', 'E', 'H', 'G', 'C', 'J', 'C', 'F', 'G', 'E', 'F', 'G', 'I', 'J', 'G', 'G', 'H', 'C', 'J', 'H', 'B', 'E', 'H', 'B', 'C', 'G', 'D', 'I', 'I', 'B', 'C', 'A', 'A', 'H', 'B', 'C', 'A', 'H', 'G', 'C', 'J', 'B', 'H', 'B', 'G', 'J', 'H', 'B', 'B', 'E', 'I', 'B', 'E', 'C', 'A', 'G', 'C', 'E', 'C', 'D', 'A', 'C', 'H', 'F', 'J', 'E', 'C', 'F', 'F', 'E', 'F', 'J', 'H', 'D', 'B', 'I', 'I', 'B', 'D', 'G', 'J', 'A', 'D', 'H', 'J', 'C', 'H', 'H', 'D', 'D', 'D', 'D', 'F', 'A', 'E', 'G', 'C', 'J', 'A', 'C', 'A', 'A', 'H', 'H', 'H', 'H', 'D', 'H', 'D', 'H', 'I', 'F', 'D', 'A', 'J', 'D', 'D', 'H', 'E', 'C', 'H', 'J', 'C', 'A', 'A', 'B', 'G', 'H', 'G', 'C', 'C', 'I', 'B', 'J', 'I', 'E', 'A', 'G', 'F', 'D', 'B', 'H', 'J', 'I', 'E', 'J', 'B', 'A', 'D', 'J', 'H', 'H', 'H', 'I', 'G', 'G', 'I', 'F', 'I', 'A', 'F', 'C', 'E', 'G', 'E', 'G', 'C', 'I', 'I', 'B', 'C', 'F', 'E', 'E', 'E', 'H', 'G', 'E', 'C', 'E', 'B', 'D', 'F', 'G', 'B', 'H', 'B', 'J', 'J', 'J', 'A', 'E', 'D', 'F', 'C', 'I', 'D', 'B', 'G', 'J', 'B', 'A', 'D', 'G', 'J', 'H', 'J', 'G', 'H', 'A', 'D', 'F', 'A', 'H', 'A', 'J', 'E', 'E', 'E', 'H', 'B', 'B', 'E', 'E', 'I', 'J', 'I', 'G', 'C', 'H', 'G', 'D', 'F', 'E', 'I', 'D', 'H', 'J', 'J', 'B', 'J', 'F', 'G', 'A', 'F', 'C', 'E', 'A', 'B', 'A', 'F', 'E', 'E', 'F', 'A', 'H', 'D', 'J', 'J', 'C', 'G', 'D', 'I', 'A', 'D', 'C', 'J', 'J', 'J', 'J', 'H', 'F', 'A', 'A', 'F', 'I', 'J', 'J', 'F', 'C', 'C', 'B', 'J', 'E', 'I', 'G', 'F', 'G', 'E', 'B', 'J', 'H', 'D', 'C', 'D', 'E', 'F', 'H', 'E', 'A', 'J', 'F', 'G', 'A', 'B', 'I', 'E', 'A', 'B', 'E', 'G', 'C', 'C', 'A', 'I', 'C', 'H', 'I', 'G', 'G', 'E', 'H', 'I', 'I', 'B', 'A', 'B', 'I', 'B', 'G', 'A', 'E', 'C', 'F', 'F', 'J', 'F', 'C', 'J', 'H', 'E', 'G', 'E', 'J', 'J', 'G', 'F', 'F', 'E', 'J', 'D', 'G', 'H', 'B', 'E', 'I', 'H', 'A', 'G', 'B', 'B', 'D', 'E', 'F', 'G', 'C', 'C', 'A', 'F', 'D', 'A', 'I', 'B', 'I', 'H', 'I', 'G', 'G', 'E', 'D', 'E', 'D', 'A', 'J', 'J', 'G', 'G', 'D', 'F', 'E', 'I', 'B', 'B', 'J', 'F', 'A', 'H', 'D', 'A', 'C', 'H', 'I', 'E', 'C', 'J', 'B', 'H', 'C', 'C', 'D', 'A', 'B', 'I', 'E', 'G', 'J', 'H', 'F', 'E', 'F', 'E', 'F', 'E', 'E', 'J', 'C', 'A', 'G', 'D', 'J', 'B', 'C', 'A', 'F', 'B', 'A', 'E', 'I', 'G', 'G', 'E', 'I', 'A', 'F', 'C', 'A', 'C', 'F', 'G', 'G', 'J', 'H', 'F', 'C', 'J', 'A', 'F', 'J', 'C', 'C', 'F', 'C', 'J', 'F', 'J', 'J', 'G', 'H', 'E', 'J', 'B', 'E', 'D', 'D', 'D', 'F', 'F', 'J', 'I', 'H', 'J', 'F', 'C', 'A', 'B', 'C', 'E', 'A', 'J', 'A', 'A', 'D', 'A', 'H', 'H', 'H', 'F', 'A', 'E', 'B', 'D', 'E', 'J', 'A', 'C', 'E', 'D', 'H', 'B', 'B', 'D', 'A', 'A', 'I', 'D', 'J', 'J', 'H', 'I', 'D', 'I', 'H', 'J', 'J', 'I', 'I', 'I', 'B', 'E', 'C', 'G', 'J', 'A', 'G', 'C', 'A', 'A', 'B', 'G', 'C', 'G', 'I', 'D', 'C', 'H', 'C', 'E', 'F', 'F', 'F', 'D', 'C', 'A', 'H', 'I', 'E', 'B', 'A', 'B', 'F', 'H', 'I', 'D', 'B', 'D', 'H', 'J', 'J', 'A', 'C', 'J', 'D', 'F', 'A', 'H', 'J', 'H', 'C', 'J', 'I', 'B', 'G', 'F', 'F', 'B', 'I', 'D', 'J', 'J', 'E', 'H', 'D', 'E', 'A', 'H', 'A', 'C', 'A', 'J', 'B', 'B', 'B', 'F', 'A', 'C', 'J', 'C', 'H', 'E', 'I', 'B', 'F', 'H', 'D', 'G', 'A', 'G', 'I', 'D', 'B', 'I', 'A', 'G', 'B', 'B', 'I', 'H', 'D', 'A', 'I', 'E', 'E', 'I', 'F', 'C', 'G', 'F', 'F', 'E', 'C', 'H', 'B', 'C', 'A', 'B', 'A', 'F', 'G', 'B', 'C', 'H', 'G', 'I', 'H', 'B', 'C', 'B', 'F', 'E', 'A', 'A', 'F', 'D', 'I', 'I', 'I', 'F', 'I', 'A', 'D', 'G', 'A', 'B', 'E', 'B', 'H', 'D', 'I', 'B', 'D', 'B', 'J', 'E', 'E', 'I', 'D', 'C', 'A', 'I', 'G', 'E', 'J', 'J', 'H', 'H', 'G', 'A', 'B', 'I', 'A', 'A', 'C', 'A', 'H', 'E', 'J', 'E', 'F', 'B', 'D', 'F', 'C', 'F', 'E', 'F', 'A', 'A', 'H', 'D', 'E', 'A', 'F', 'H', 'E', 'J', 'D', 'I', 'J', 'A', 'E', 'J', 'H', 'I', 'C', 'A', 'H', 'E', 'H', 'D', 'I', 'B', 'B', 'C', 'F', 'H', 'H', 'B', 'E', 'E', 'G', 'C', 'E', 'E', 'J', 'A', 'F', 'B', 'C', 'D', 'F', 'B', 'G', 'B', 'B', 'E', 'F', 'E', 'I', 'I', 'F', 'G', 'A', 'F', 'H', 'G', 'J', 'A', 'A', 'H', 'A', 'C', 'C', 'D', 'C', 'G', 'F', 'J', 'C', 'G', 'G', 'C', 'D', 'B', 'A', 'D', 'J', 'F', 'E', 'A', 'H', 'A', 'J', 'J', 'A', 'C', 'A', 'H', 'C', 'C', 'C', 'A', 'G', 'J', 'B', 'E', 'C', 'G', 'D', 'G', 'A', 'G', 'F', 'J', 'D', 'E', 'F', 'D', 'H', 'G', 'C', 'E', 'J', 'A', 'I', 'F', 'F', 'G', 'G', 'A', 'C', 'I', 'E', 'I', 'D', 'G', 'A', 'F', 'E', 'B', 'C', 'D', 'A', 'C', 'F', 'A', 'J', 'E', 'H', 'G', 'F', 'F', 'I', 'I', 'C', 'J', 'G', 'B', 'B', 'E', 'A', 'I', 'D', 'C', 'I', 'C', 'G', 'C', 'F', 'J', 'E', 'B', 'B', 'C', 'G', 'B', 'B', 'J', 'C', 'I', 'E', 'E', 'J', 'A', 'C', 'E', 'F', 'C', 'A', 'H', 'H', 'I', 'C', 'E', 'B', 'J', 'A', 'H', 'B', 'B', 'G', 'H', 'A', 'B', 'D', 'H', 'B', 'F', 'B', 'F', 'E', 'B', 'E', 'I', 'D', 'C', 'A', 'J', 'C', 'H', 'A', 'C', 'B', 'E', 'D', 'H', 'H', 'J', 'H', 'H', 'H', 'E', 'H', 'E', 'A', 'H', 'H', 'J', 'F', 'A', 'H', 'F', 'E', 'D', 'E', 'J', 'C', 'B', 'G', 'G', 'I', 'E', 'I', 'G', 'A', 'C', 'G', 'E', 'F', 'D', 'C', 'B', 'G', 'G', 'J', 'A', 'J', 'E', 'G', 'C', 'H', 'D', 'J', 'G', 'G', 'G', 'I', 'A', 'H', 'B', 'I', 'E', 'G', 'B', 'F', 'D', 'C', 'E', 'C', 'J', 'E', 'J', 'B', 'C', 'H', 'J', 'A', 'H', 'I', 'A', 'B', 'I', 'A', 'H', 'D', 'A', 'F', 'B', 'E', 'D', 'D', 'C', 'A', 'D', 'G', 'A', 'D', 'H', 'B', 'E', 'F', 'I', 'I', 'C', 'G', 'B', 'F', 'F', 'D', 'C', 'B', 'I', 'H', 'C', 'B', 'G', 'B', 'B', 'B', 'J', 'J', 'H', 'B', 'D', 'G', 'H', 'A', 'C', 'A', 'F', 'A', 'J', 'G', 'A', 'C', 'B', 'G', 'A', 'E', 'C', 'C', 'H', 'J', 'C', 'I', 'C', 'E', 'E', 'D', 'B', 'C', 'H', 'E', 'B', 'B', 'I', 'F', 'G', 'E', 'F', 'A', 'B', 'F', 'B', 'J', 'B', 'I', 'J', 'A', 'E', 'I', 'J', 'I', 'I', 'I', 'F', 'J', 'A', 'H', 'I', 'C', 'C', 'G', 'D', 'H', 'H', 'D', 'D', 'B', 'H', 'B', 'A', 'I', 'A', 'E', 'B', 'C', 'E', 'F', 'J', 'A', 'E', 'C', 'H', 'C', 'H', 'A', 'B', 'H', 'G', 'I', 'G', 'G', 'A', 'I', 'B', 'E', 'H', 'G', 'C', 'F', 'C', 'G', 'D', 'H', 'C', 'G', 'H', 'F', 'E', 'C', 'F', 'D', 'C', 'A', 'C', 'H', 'E', 'F', 'I', 'H', 'E', 'H', 'G', 'H', 'G', 'J', 'F', 'D', 'E', 'I', 'H', 'F', 'E', 'I', 'I', 'J', 'C', 'I', 'H', 'E', 'B', 'H', 'I', 'A', 'I', 'G', 'I', 'E', 'F', 'J', 'E', 'E', 'J', 'J', 'A', 'D', 'F', 'G', 'I', 'C', 'G', 'G', 'A', 'F', 'A', 'J', 'A', 'G', 'D', 'H', 'I', 'F', 'G', 'D', 'A', 'H', 'J', 'A', 'A', 'A', 'E', 'E', 'D', 'J', 'A', 'I', 'I', 'E', 'J', 'C', 'E', 'A', 'C', 'D', 'E', 'J', 'H', 'J', 'D', 'B', 'E', 'J', 'F', 'B', 'A', 'B', 'E', 'J', 'E', 'B', 'E', 'E', 'H', 'C', 'J', 'H', 'J', 'F', 'C', 'I', 'A', 'F', 'D', 'F', 'I', 'I', 'F', 'J', 'B', 'J', 'I', 'H', 'A', 'A', 'G', 'H', 'I', 'D', 'C', 'H', 'D', 'E', 'B', 'I', 'I', 'I', 'F', 'E', 'A', 'J', 'I', 'B', 'I', 'A', 'J', 'C', 'C', 'J', 'B', 'I', 'J', 'F', 'F', 'D', 'D', 'C', 'H', 'E', 'A', 'J', 'G', 'G', 'A', 'I', 'I', 'D', 'D', 'F', 'B', 'H', 'G', 'F', 'E', 'F', 'C', 'G', 'C', 'A', 'G', 'H', 'H', 'B', 'G', 'F', 'J', 'F', 'E', 'A', 'H', 'H', 'B', 'C', 'J', 'C', 'F', 'D', 'D', 'B', 'E', 'J', 'H', 'A', 'A', 'E', 'C', 'I', 'E', 'I', 'C', 'D', 'I', 'B', 'G', 'F', 'B', 'H', 'D', 'H', 'I', 'A', 'G', 'D', 'H', 'D', 'E', 'G', 'I', 'A', 'A', 'H', 'G', 'E', 'J', 'C', 'D', 'A', 'E', 'B', 'J', 'G', 'A', 'G', 'F', 'B', 'H', 'A', 'I', 'G', 'F', 'F', 'I', 'G', 'C', 'F', 'G', 'D', 'E', 'G', 'A', 'I', 'H', 'F', 'E', 'J', 'F', 'A', 'E', 'C', 'B', 'H', 'C', 'E', 'B', 'G', 'F', 'I', 'C', 'B', 'H', 'B', 'G', 'G', 'E', 'J', 'E', 'H', 'G', 'F', 'G', 'H', 'I', 'C', 'C', 'I', 'F', 'B', 'A', 'J', 'E', 'B', 'G', 'A', 'J', 'G', 'I', 'A', 'B', 'D', 'B', 'G', 'E', 'E', 'I', 'B', 'A', 'E', 'A', 'J', 'J', 'E', 'C', 'I', 'A', 'E', 'A', 'C', 'I', 'C', 'G', 'C', 'J', 'I', 'H', 'F', 'A', 'C', 'A', 'A', 'G', 'J', 'E', 'J', 'C', 'B', 'H', 'G', 'I', 'H', 'J', 'F', 'G', 'H', 'H', 'C', 'I', 'F', 'A', 'E', 'C', 'F', 'B', 'H', 'B', 'G', 'A', 'D', 'D', 'H', 'D', 'G', 'A', 'F', 'D', 'C', 'A', 'I', 'A', 'E', 'C', 'A', 'G', 'C', 'G', 'A', 'H', 'E', 'G', 'J', 'F', 'H', 'J', 'H', 'G', 'D', 'D', 'G', 'J', 'J', 'H', 'J', 'F', 'E', 'D', 'G', 'C', 'E', 'C', 'D', 'I', 'C', 'E', 'G', 'H', 'I', 'E', 'D', 'A', 'J', 'I', 'J', 'C', 'D', 'E', 'F', 'D', 'H', 'G', 'A', 'D', 'F', 'C', 'B', 'B', 'J', 'B', 'A', 'A', 'E', 'H', 'H', 'I', 'G', 'C', 'D', 'D', 'B', 'F', 'B', 'E', 'I', 'H', 'I', 'D', 'C', 'H', 'F', 'A', 'E', 'E', 'J', 'I', 'B', 'I', 'G', 'B', 'I', 'D', 'D', 'J', 'I', 'B', 'I', 'G', 'G', 'H', 'B', 'D', 'H', 'B', 'E', 'I', 'I', 'C', 'G', 'D', 'G', 'J', 'J', 'B', 'G', 'B', 'D', 'H', 'F', 'F', 'E', 'J', 'F', 'B', 'J', 'C', 'C', 'G', 'F', 'A', 'G', 'C', 'F', 'I', 'E', 'B', 'B', 'J', 'E', 'C', 'A', 'D', 'A', 'I', 'F', 'J', 'F', 'H', 'G', 'I', 'F', 'G', 'C', 'D', 'F', 'G', 'F', 'E', 'D', 'B', 'H', 'H', 'F', 'A', 'E', 'H', 'I', 'B', 'E', 'J', 'B', 'H', 'J', 'F', 'C', 'C', 'B', 'E', 'F', 'A', 'B', 'D', 'D', 'G', 'E', 'D', 'B', 'J', 'F', 'A', 'A', 'I', 'A', 'C', 'E', 'I', 'G', 'H', 'G', 'F', 'I', 'D', 'F', 'E', 'E', 'A', 'H', 'C', 'E', 'J', 'C', 'D', 'A', 'B', 'D', 'H', 'C', 'J', 'J', 'B', 'E', 'E', 'A', 'B', 'I', 'F', 'D', 'H', 'C', 'C', 'G', 'E', 'F', 'I', 'E', 'F', 'B', 'C', 'C', 'B', 'J', 'B', 'H', 'J', 'E', 'G', 'C', 'D', 'G', 'A', 'H', 'J', 'B', 'H', 'B', 'B', 'A', 'B', 'J', 'B', 'C', 'G', 'C', 'I', 'H', 'E', 'H', 'B', 'G', 'B', 'I', 'D', 'E', 'E', 'D', 'B', 'G', 'E', 'D', 'D', 'D', 'J', 'F', 'I', 'I', 'A', 'J', 'H', 'H', 'I', 'C', 'F', 'F', 'G', 'I', 'J', 'H', 'A', 'B', 'C', 'I', 'I', 'G', 'C', 'D', 'F', 'E', 'G', 'I', 'F', 'I', 'G', 'H', 'H', 'G', 'F', 'F', 'C', 'D', 'F', 'C', 'E', 'C', 'A', 'G', 'E', 'G', 'F', 'E', 'A', 'G', 'H', 'G', 'D', 'I', 'B', 'D', 'G', 'B', 'J', 'G', 'H', 'H', 'B', 'E', 'A', 'B', 'D', 'I', 'A', 'J', 'I', 'E', 'B', 'G', 'F', 'G', 'C', 'I', 'G', 'E', 'D', 'E', 'D', 'H', 'I', 'D', 'H', 'E', 'B', 'D', 'G', 'J', 'A', 'F', 'C', 'E', 'G', 'I', 'A', 'C', 'J', 'E', 'E', 'F', 'A', 'F', 'D', 'D', 'B', 'G', 'H', 'E', 'B', 'D', 'H', 'G', 'A', 'A', 'H', 'E', 'F', 'C', 'A', 'G', 'J', 'H', 'H', 'F', 'F', 'F', 'D', 'E', 'B', 'A', 'F', 'B', 'C', 'C', 'I', 'D', 'J', 'J', 'G', 'B', 'A', 'H', 'I', 'J', 'J', 'C', 'F', 'C', 'H', 'H', 'F', 'C', 'F', 'G', 'D', 'B', 'J', 'J', 'C', 'C', 'G', 'A', 'E', 'F', 'D', 'A', 'E', 'G', 'G', 'F', 'B', 'A', 'I', 'F', 'D', 'A', 'G', 'H', 'F', 'G', 'G', 'J', 'A', 'H', 'F', 'E', 'D', 'J', 'D', 'F', 'B', 'D', 'J', 'H', 'I', 'D', 'H', 'D', 'E', 'C', 'G', 'D', 'A', 'B', 'J', 'C', 'J', 'C', 'A', 'D', 'A', 'F', 'D', 'H', 'D', 'A', 'D', 'G', 'F', 'E', 'A', 'I', 'G', 'I', 'C', 'D', 'B', 'A', 'I', 'C', 'A', 'I', 'J', 'A', 'A', 'A', 'H', 'F', 'C', 'F', 'G', 'D', 'I', 'I', 'E', 'I', 'B', 'E', 'I', 'F', 'A', 'H', 'E', 'B', 'A', 'E', 'F', 'C', 'C', 'B', 'H', 'I', 'E', 'F', 'G', 'H', 'J', 'H', 'A', 'C', 'D', 'A', 'I', 'I', 'H', 'I', 'E', 'H', 'F', 'F', 'B', 'D', 'G', 'H', 'I', 'I', 'D', 'D', 'G', 'A', 'J', 'H', 'G', 'I', 'H', 'E', 'J', 'D', 'B', 'D', 'F', 'G', 'H', 'G', 'A', 'H', 'F', 'B', 'F', 'E', 'J', 'A', 'C', 'C', 'I', 'H', 'B', 'B', 'E', 'F', 'B', 'F', 'A', 'I', 'H', 'E', 'B', 'A', 'F', 'C', 'F', 'E', 'G', 'G', 'D', 'D', 'J', 'A', 'J', 'I', 'G', 'E', 'G', 'C', 'B', 'B', 'F', 'E', 'J', 'J', 'D', 'G', 'D', 'A', 'I', 'C', 'F', 'J', 'H', 'D', 'H', 'A', 'G', 'A', 'C', 'C', 'J', 'A', 'F', 'I', 'E', 'F', 'J', 'F', 'E', 'G', 'H', 'H', 'A', 'F', 'F', 'J', 'D', 'H', 'A', 'A', 'D', 'F', 'D', 'A', 'H', 'E', 'I', 'E', 'I', 'G', 'G', 'C', 'I', 'D', 'I', 'I', 'C', 'B', 'A', 'F', 'I', 'J', 'J', 'B', 'B', 'J', 'D', 'H', 'B', 'F', 'J', 'H', 'G', 'H', 'C', 'H', 'F', 'A', 'D', 'I', 'C', 'A', 'C', 'E', 'B', 'H', 'E', 'B', 'E', 'A', 'D', 'F', 'G', 'A', 'D', 'H', 'F', 'A', 'D', 'H', 'G', 'I', 'C', 'B', 'E', 'A', 'H', 'E', 'C', 'I', 'J', 'D', 'B', 'J', 'G', 'D', 'E', 'A', 'H', 'B', 'I', 'D', 'G', 'D', 'I', 'F', 'G', 'J', 'E', 'H', 'H', 'B', 'H', 'E', 'B', 'G', 'B', 'C', 'A', 'A', 'H', 'G', 'G', 'B', 'A', 'H', 'C', 'B', 'E', 'B', 'I', 'F', 'I', 'C', 'F', 'I', 'H', 'F', 'E', 'J', 'G', 'C', 'E', 'I', 'I', 'F', 'C', 'F', 'F', 'F', 'J', 'D', 'B', 'B', 'F', 'C', 'B', 'D', 'G', 'B', 'A', 'G', 'H', 'J', 'A', 'G', 'B', 'F', 'F', 'C', 'J', 'H', 'F', 'E', 'E', 'I', 'A', 'C', 'I', 'E', 'E', 'D', 'B', 'I', 'B', 'E', 'G', 'A', 'D', 'F', 'J', 'B', 'B', 'C', 'E', 'D', 'C', 'E', 'J', 'I', 'A', 'E', 'A', 'J', 'I', 'E', 'G', 'I', 'E', 'G', 'H', 'B', 'H', 'F', 'C', 'A', 'F', 'B', 'F', 'G', 'B', 'J', 'H', 'D', 'B', 'E', 'A', 'D', 'D', 'J', 'H', 'E', 'H', 'G', 'G', 'D', 'I', 'E', 'A', 'C', 'H', 'H', 'G', 'D', 'I', 'J', 'E', 'D', 'C', 'G', 'B', 'E', 'H', 'G', 'B', 'J', 'I', 'F', 'E', 'F', 'I', 'C', 'E', 'C', 'C', 'I', 'H', 'E', 'I', 'J', 'A', 'C', 'D', 'B', 'E', 'J', 'D', 'B', 'F', 'B', 'F', 'D', 'G', 'F', 'B', 'J', 'E', 'C', 'A', 'J', 'F', 'I', 'B', 'J', 'A', 'A', 'C', 'D', 'D', 'I', 'D', 'E', 'J', 'J', 'B', 'C', 'A', 'J', 'D', 'C', 'I', 'D', 'E', 'B', 'D', 'E', 'F', 'D', 'D', 'F', 'C', 'B', 'H', 'C', 'G', 'B', 'I', 'F', 'G', 'E', 'C', 'C', 'H', 'F', 'C', 'B', 'F', 'B', 'J', 'D', 'E', 'A', 'E', 'E', 'C', 'G', 'J', 'G', 'G', 'I', 'F', 'A', 'I', 'J', 'A', 'D', 'F', 'H', 'I', 'H', 'H', 'I', 'H', 'B', 'J', 'F', 'I', 'C', 'I', 'B', 'G', 'B', 'A', 'D', 'H', 'E', 'D', 'C', 'J', 'A', 'J', 'G', 'I', 'G', 'G', 'E', 'B', 'I', 'G', 'F', 'D', 'F', 'B', 'E', 'F', 'H', 'J', 'D', 'F', 'C', 'C', 'F', 'E', 'I', 'F', 'D', 'A', 'C', 'D', 'H', 'J', 'I', 'A', 'A', 'C', 'A', 'I', 'F', 'C', 'C', 'B', 'H', 'J', 'H', 'D', 'D', 'F', 'I', 'A', 'B', 'H', 'I', 'H', 'A', 'A', 'B', 'B', 'I', 'D', 'E', 'F', 'A', 'J', 'H', 'G', 'H', 'H', 'E', 'A', 'E', 'J', 'I', 'E', 'C', 'J', 'D', 'F', 'I', 'C', 'E', 'F', 'E', 'D', 'D', 'I', 'J', 'G', 'E', 'A', 'J', 'J', 'E', 'J', 'H', 'G', 'D', 'H', 'B', 'B', 'I', 'A', 'A', 'A', 'H', 'I', 'I', 'H', 'A', 'F', 'I', 'B', 'J', 'B', 'H', 'I', 'C', 'C', 'C', 'I', 'A', 'A', 'B', 'J', 'B', 'J', 'J', 'C', 'E', 'E', 'G', 'B', 'H', 'A', 'H', 'J', 'C', 'D', 'C', 'I', 'F', 'I', 'J', 'D', 'G', 'I', 'E', 'A', 'H', 'F', 'F', 'D', 'I', 'I', 'H', 'F', 'A', 'I', 'H', 'E', 'C', 'F', 'D', 'C', 'F', 'B', 'D', 'I', 'F', 'I', 'A', 'E', 'B', 'C', 'I', 'C', 'A', 'G', 'C', 'A', 'I', 'E', 'C', 'H', 'I', 'C', 'I', 'F', 'H', 'H', 'G', 'J', 'C', 'J', 'I', 'A', 'J', 'G', 'H', 'H', 'F', 'G', 'C', 'E', 'E', 'D', 'F', 'B', 'H', 'D', 'I', 'C', 'I', 'A', 'G', 'B', 'C', 'J', 'I', 'J', 'H', 'G', 'D', 'E', 'C', 'H', 'I', 'C', 'J', 'G', 'D', 'H', 'C', 'J', 'F', 'H', 'G', 'I', 'J', 'I', 'G', 'H', 'E', 'A', 'E', 'B', 'C', 'G', 'C', 'D', 'B', 'I', 'C', 'I', 'F', 'I', 'I', 'I', 'D', 'C', 'J', 'H', 'F', 'E', 'A', 'A', 'E', 'D', 'A', 'C', 'I', 'B', 'B', 'J', 'J', 'B', 'F', 'J', 'C', 'I', 'B', 'G', 'B', 'H', 'A', 'I', 'B', 'I', 'I', 'I', 'G', 'F', 'A', 'H', 'A', 'H', 'B', 'C', 'G', 'D', 'E', 'B', 'I', 'C', 'J', 'B', 'C', 'C', 'H', 'F', 'J', 'H', 'A', 'G', 'J', 'I', 'B', 'B', 'E', 'F', 'H', 'G', 'G', 'A', 'J', 'D', 'H', 'A', 'J', 'F', 'G', 'G', 'J', 'C', 'B', 'I', 'G', 'J', 'E', 'E', 'J', 'E', 'A', 'F', 'J', 'J', 'C', 'I', 'A', 'H', 'E', 'H', 'C', 'F', 'A', 'J', 'J', 'J', 'B', 'B', 'J', 'J', 'F', 'E', 'I', 'F', 'B', 'J', 'F', 'F', 'A', 'B', 'D', 'F', 'B', 'D', 'I', 'J', 'I', 'D', 'F', 'F', 'D', 'B', 'C', 'D', 'I', 'D', 'B', 'B', 'H', 'H', 'D', 'C', 'E', 'E', 'G', 'A', 'F', 'G', 'A', 'A', 'A', 'F', 'A', 'D', 'J', 'F', 'G', 'B', 'A', 'J', 'E', 'F', 'I', 'J', 'B', 'B', 'F', 'B', 'A', 'D', 'F', 'D', 'E', 'J', 'B', 'E', 'G', 'D', 'I', 'D', 'J', 'D', 'G', 'C', 'J', 'H', 'B', 'D', 'H', 'B', 'C', 'E', 'E', 'B', 'B', 'F', 'C', 'B', 'E', 'F', 'B', 'J', 'B', 'B', 'B', 'J', 'C', 'C', 'J', 'I', 'I', 'E', 'F', 'G', 'E', 'H', 'H', 'H', 'G', 'J', 'D', 'H', 'I', 'J', 'J', 'J', 'F', 'J', 'H', 'E', 'G', 'A', 'D', 'H', 'I', 'A', 'C', 'G', 'E', 'C', 'H', 'A', 'F', 'J', 'A', 'B', 'B', 'D', 'G', 'C', 'A', 'E', 'E', 'F', 'F', 'D', 'J', 'F', 'F', 'C', 'A', 'D', 'C', 'D', 'I', 'D', 'E', 'A', 'H', 'G', 'H', 'E', 'I', 'J', 'D', 'B', 'H', 'A', 'D', 'B', 'A', 'B', 'G', 'G', 'C', 'J', 'D', 'F', 'G', 'I', 'G', 'G', 'J', 'F', 'E', 'I', 'A', 'J', 'H', 'C', 'F', 'C', 'E', 'D', 'I', 'G', 'E', 'B', 'B', 'B', 'G', 'F', 'G', 'J', 'F', 'B', 'A', 'H', 'F', 'E', 'D', 'D', 'F', 'G', 'A', 'J', 'B', 'F', 'B', 'B', 'J', 'G', 'B', 'C', 'C', 'I', 'A', 'I', 'I', 'A', 'G', 'J', 'I', 'G', 'G', 'E', 'B', 'F', 'E', 'J', 'G', 'C', 'G', 'E', 'D', 'B', 'I', 'E', 'I', 'F', 'B', 'C', 'I', 'B', 'G', 'H', 'A', 'I', 'G', 'I', 'F', 'F', 'J', 'C', 'I', 'J', 'C', 'G', 'D', 'E', 'I', 'I', 'A', 'A', 'F', 'J', 'J', 'F', 'E', 'E', 'B', 'C', 'H', 'B', 'I', 'F', 'C', 'C', 'D', 'A', 'J', 'B', 'F', 'H', 'D', 'C', 'J', 'J', 'C', 'B', 'B', 'F', 'D', 'E', 'A', 'G', 'F', 'H', 'F', 'A', 'J', 'F', 'A', 'E', 'I', 'A', 'F', 'C', 'B', 'G', 'J', 'H', 'J', 'F', 'D', 'F', 'A', 'C', 'D', 'C', 'H', 'J', 'F', 'D', 'H', 'G', 'I', 'F', 'J', 'A', 'C', 'B', 'C', 'J', 'H', 'B', 'G', 'G', 'D', 'I', 'J', 'D', 'C', 'B', 'J', 'I', 'B', 'F', 'B', 'E', 'G', 'D', 'E', 'B', 'I', 'G', 'J', 'H', 'A', 'J', 'A', 'G', 'C', 'E', 'J', 'F', 'D', 'J', 'B', 'D', 'J', 'I', 'C', 'J', 'E', 'G', 'A', 'D', 'B', 'G', 'E', 'G', 'H', 'H', 'B', 'G', 'D', 'H', 'A', 'C', 'I', 'B', 'E', 'F', 'A', 'I', 'F', 'A', 'E', 'H', 'A', 'I', 'F', 'A', 'J', 'G', 'A', 'A', 'C', 'J', 'I', 'B', 'A', 'F', 'A', 'I', 'B', 'D', 'C', 'B', 'F', 'A', 'D', 'B', 'A', 'J', 'C', 'I', 'H', 'D', 'G', 'G', 'A', 'D', 'A', 'A', 'I', 'J', 'B', 'D', 'G', 'A', 'J', 'F', 'D', 'I', 'H', 'H', 'H', 'J', 'J', 'H', 'A', 'A', 'B', 'I', 'B', 'F', 'C', 'H', 'J', 'F', 'F', 'I', 'D', 'A', 'D', 'B', 'H', 'H', 'D', 'F', 'I', 'C', 'E', 'F', 'I', 'G', 'J', 'D', 'D', 'D', 'A', 'B', 'I', 'J', 'I', 'B', 'B', 'F', 'D', 'I', 'A', 'C', 'C', 'F', 'C', 'I', 'J', 'G', 'E', 'H', 'F', 'E', 'C', 'D', 'E', 'A', 'H', 'E', 'C', 'E', 'B', 'H', 'D', 'D', 'A', 'F', 'A', 'A', 'C', 'F', 'E', 'F', 'C', 'D', 'B', 'A', 'I', 'J', 'G', 'I', 'H', 'I', 'J', 'F', 'E', 'E', 'F', 'B', 'G', 'I', 'A', 'D', 'G', 'I', 'C', 'E', 'C', 'A', 'J', 'E', 'J', 'E', 'B', 'D', 'C', 'F', 'I', 'A', 'J', 'I', 'C', 'F', 'A', 'F', 'C', 'B', 'D', 'B', 'C', 'G', 'D', 'D', 'E', 'G', 'B', 'C', 'B', 'A', 'D', 'B', 'J', 'F', 'A', 'D', 'C', 'A', 'I', 'F', 'D', 'I', 'I', 'D', 'A', 'G', 'F', 'C', 'A', 'H', 'J', 'J', 'J', 'D', 'I', 'J', 'H', 'I', 'D', 'C', 'D', 'I', 'I', 'H', 'I', 'G', 'D', 'E', 'A', 'A', 'E', 'J', 'C', 'A', 'B', 'C', 'C', 'C', 'B', 'H', 'E', 'F', 'J', 'H', 'J', 'I', 'D', 'G', 'I', 'E', 'B', 'E', 'B', 'B', 'I', 'I', 'I', 'F', 'J', 'D', 'J', 'G', 'H', 'B', 'E', 'F', 'J', 'J', 'E', 'D', 'D', 'F', 'B', 'H', 'H', 'F', 'G', 'B', 'J', 'G', 'H', 'J', 'F', 'E', 'B', 'E', 'F', 'E', 'I', 'A', 'C', 'G', 'C', 'E', 'I', 'E', 'A', 'C', 'B', 'G', 'A', 'F', 'I', 'B', 'A', 'F', 'J', 'J', 'I', 'F', 'E', 'G', 'E', 'E', 'D', 'A', 'C', 'H', 'A', 'D', 'G', 'G', 'J', 'J', 'G', 'H', 'B', 'D', 'J', 'H', 'B', 'J', 'I', 'I', 'I', 'C', 'J', 'H', 'C', 'F', 'D', 'G', 'C', 'G', 'E', 'J', 'C', 'D', 'D', 'H', 'J', 'B', 'C', 'A', 'I', 'B', 'F', 'G', 'D', 'G', 'D', 'B', 'E', 'I', 'H', 'J', 'F', 'C', 'C', 'J', 'A', 'C', 'G', 'D', 'J', 'D', 'E', 'G', 'D', 'G', 'D', 'J', 'E', 'I', 'E', 'C', 'E', 'E', 'G', 'I', 'I', 'H', 'A', 'F', 'D', 'J', 'I', 'E', 'A', 'I', 'F', 'H', 'B', 'F', 'A', 'H', 'A', 'E', 'F', 'J', 'G', 'B', 'G', 'A', 'C', 'A', 'E', 'G', 'F', 'A', 'H', 'E', 'J', 'G', 'F', 'E', 'C', 'A', 'J', 'I', 'F', 'F', 'A', 'F', 'D', 'J', 'G', 'C', 'C', 'A', 'I', 'J', 'B', 'D', 'F', 'E', 'I', 'I', 'F', 'A', 'A', 'I', 'E', 'A', 'F', 'J', 'A', 'J', 'B', 'F', 'B', 'G', 'C', 'G', 'B', 'F', 'B', 'A', 'B', 'B', 'G', 'H', 'A', 'F', 'B', 'H', 'C', 'D', 'H', 'C', 'A', 'B', 'G', 'D', 'F', 'J', 'H', 'E', 'I', 'B', 'C', 'E', 'A', 'J', 'J', 'H', 'J', 'A', 'G', 'F', 'C', 'I', 'C', 'D', 'C', 'A', 'D', 'C', 'E', 'H', 'E', 'E', 'F', 'H', 'F', 'J', 'D', 'C', 'G', 'J', 'G', 'F', 'J', 'E', 'E', 'G', 'D', 'B', 'G', 'B', 'H', 'G', 'B', 'D', 'E', 'G', 'D', 'F', 'F', 'C', 'J', 'J', 'A', 'F', 'H', 'A', 'I', 'I', 'G', 'E', 'A', 'A', 'H', 'D', 'C', 'I', 'H', 'D', 'B', 'C', 'I', 'F', 'H', 'H', 'D', 'H', 'H', 'F', 'D', 'C', 'E', 'A', 'A', 'F', 'I', 'G', 'D', 'G', 'E', 'J', 'B', 'I', 'J', 'A', 'B', 'E', 'D', 'E', 'F', 'D', 'G', 'A', 'I', 'C', 'G', 'I', 'C', 'F', 'F', 'I', 'I', 'E', 'A', 'D', 'J', 'C', 'H', 'C', 'F', 'J', 'G', 'E', 'B', 'J', 'H', 'F', 'B', 'G', 'A', 'D', 'H', 'D', 'D', 'I', 'H', 'H', 'B', 'J', 'G', 'E', 'I', 'E', 'B', 'I', 'I', 'J', 'G', 'G', 'H', 'E', 'E', 'B', 'G', 'A', 'G', 'D', 'J', 'D', 'D', 'J', 'C', 'E', 'A', 'A', 'F', 'A', 'B', 'I', 'H', 'B', 'F', 'G', 'E', 'E', 'G', 'J', 'I', 'I', 'E', 'G', 'H', 'F', 'E', 'J', 'F', 'H', 'J', 'G', 'H', 'H', 'H', 'B', 'D', 'B', 'I', 'A', 'F', 'G', 'C', 'H', 'C', 'E', 'A', 'D', 'E', 'F', 'F', 'D', 'G', 'H', 'J', 'E', 'G', 'H', 'B', 'H', 'B', 'D', 'C', 'H', 'B', 'F', 'C', 'H', 'F', 'D', 'C', 'A', 'J', 'E', 'E', 'A', 'F', 'F', 'C', 'J', 'I', 'G', 'F', 'D', 'J', 'J', 'C', 'I', 'A', 'D', 'I', 'B', 'A', 'E', 'F', 'H', 'A', 'G', 'F', 'H', 'I', 'F', 'E', 'G', 'I', 'G', 'B', 'J', 'A', 'J', 'D', 'A', 'D', 'J', 'F', 'B', 'E', 'G', 'G', 'F', 'A', 'J', 'E', 'J', 'E', 'G', 'G', 'I', 'I', 'B', 'C', 'J', 'B', 'B', 'H', 'B', 'J', 'D', 'E', 'I', 'I', 'E', 'B', 'A', 'F', 'E', 'J', 'J', 'I', 'B', 'A', 'G', 'J', 'D', 'J', 'B', 'J', 'I', 'J', 'J', 'A', 'D', 'G', 'J', 'G', 'D', 'I', 'H', 'D', 'B', 'I', 'H', 'E', 'D', 'H', 'F', 'F', 'C', 'A', 'G', 'I', 'E', 'F', 'J', 'C', 'E', 'D', 'F', 'B', 'D', 'I', 'G', 'A', 'B', 'G', 'D', 'B', 'F', 'G', 'H', 'B', 'H', 'J', 'B', 'J', 'D', 'G', 'B', 'C', 'B', 'H', 'E', 'H', 'G', 'H', 'G', 'G', 'E', 'D', 'I', 'G', 'J', 'C', 'E', 'H', 'E', 'A', 'J', 'G', 'H', 'B', 'A', 'A', 'G', 'D', 'G', 'A', 'F', 'A', 'E', 'J', 'D', 'D', 'C', 'C', 'J', 'D', 'B', 'A', 'C', 'G', 'G', 'I', 'E', 'A', 'I', 'F', 'A', 'G', 'D', 'F', 'E', 'B', 'I', 'H', 'B', 'D', 'H', 'E', 'F', 'A', 'B', 'F', 'J', 'J', 'B', 'I', 'B', 'H', 'F', 'H', 'H', 'J', 'B', 'G', 'J', 'B', 'E', 'C', 'A', 'F', 'C', 'C', 'J', 'B', 'D', 'F', 'G', 'H', 'C', 'D', 'H', 'H', 'E', 'B', 'C', 'I', 'I', 'F', 'E', 'J', 'B', 'F', 'D', 'D', 'J', 'A', 'D', 'G', 'H', 'J', 'E', 'G', 'I', 'A', 'H', 'C', 'E', 'I', 'G', 'B', 'J', 'I', 'J', 'J', 'F', 'A', 'G', 'C', 'D', 'C', 'C', 'J', 'A', 'B', 'D', 'D', 'B', 'A', 'I', 'D', 'H', 'F', 'I', 'G', 'B', 'E', 'I', 'J', 'C', 'F', 'J', 'F', 'D', 'J', 'H', 'F', 'A', 'C', 'J', 'F', 'J', 'H', 'B', 'H', 'B', 'A', 'I', 'A', 'E', 'G', 'I', 'D', 'A', 'D', 'E', 'D', 'F', 'D', 'I', 'H', 'A', 'B', 'I', 'B', 'F', 'H', 'C', 'D', 'G', 'H', 'B', 'G', 'C', 'C', 'A', 'G', 'E', 'H', 'J', 'J', 'B', 'C', 'F', 'I', 'C', 'A', 'A', 'D', 'G', 'E', 'H', 'A', 'G', 'H', 'B', 'E', 'D', 'D', 'H', 'G', 'J', 'G', 'J', 'I', 'I', 'A', 'B', 'H', 'F', 'I', 'A', 'E', 'D', 'F', 'J', 'C', 'I', 'H', 'C', 'B', 'I', 'D', 'A', 'J', 'D', 'G', 'B', 'H', 'J', 'F', 'A', 'I', 'H', 'C', 'F', 'A', 'C', 'A', 'A', 'I', 'D', 'H', 'F', 'E', 'A', 'C', 'A', 'F', 'H', 'D', 'H', 'E', 'D', 'E', 'A', 'E', 'I', 'H', 'E', 'B', 'H', 'J', 'G', 'D', 'A', 'I', 'I', 'G', 'J', 'J', 'C', 'H', 'B', 'D', 'C', 'C', 'I', 'G', 'C', 'G', 'A', 'I', 'I', 'J', 'E', 'C', 'C', 'E', 'G', 'H', 'J', 'H', 'B', 'D', 'C', 'C', 'F', 'I', 'G', 'I', 'C', 'F', 'F', 'B', 'I', 'C', 'C', 'I', 'H', 'I', 'F', 'C', 'I', 'G', 'B', 'B', 'C', 'B', 'C', 'I', 'J', 'J', 'E', 'B', 'D', 'F', 'J', 'J', 'E', 'A', 'E', 'F', 'C', 'B', 'B', 'B', 'H', 'J', 'G', 'B', 'G', 'J', 'H', 'H', 'I', 'F', 'C', 'E', 'D', 'G', 'D', 'B', 'E', 'F', 'I', 'J', 'J', 'G', 'G', 'J', 'E', 'J', 'A', 'G', 'B', 'C', 'I', 'J', 'F', 'B', 'A', 'E', 'A', 'D', 'D', 'E', 'I', 'C', 'D', 'J', 'B', 'E', 'G', 'D', 'G', 'H', 'B', 'J', 'F', 'I', 'E', 'A', 'E', 'B', 'J', 'E', 'B', 'D', 'I', 'E', 'F', 'D', 'B', 'I', 'E', 'I', 'A', 'H', 'B', 'A', 'E', 'C', 'A', 'D', 'F', 'D', 'G', 'F', 'E', 'B', 'F', 'D', 'J', 'F', 'B', 'G', 'E', 'I', 'J', 'A', 'I', 'A', 'H', 'E', 'H', 'I', 'E', 'F', 'C', 'H', 'D', 'C', 'E', 'I', 'A', 'G', 'C', 'B', 'C', 'B', 'D', 'D', 'J', 'B', 'B', 'E', 'D', 'F', 'B', 'I', 'F', 'B', 'I', 'H', 'H', 'E', 'J', 'D', 'J', 'D', 'E', 'B', 'E', 'H', 'C', 'I', 'F', 'H', 'G', 'C', 'J', 'C', 'D', 'H', 'H', 'C', 'F', 'C', 'E', 'E', 'D', 'J', 'H', 'C', 'I', 'H', 'F', 'B', 'I', 'J', 'D', 'I', 'C', 'E', 'J', 'H', 'F', 'J', 'D', 'G', 'J', 'H', 'F', 'J', 'E', 'H', 'H', 'A', 'A', 'C', 'E', 'J', 'F', 'C', 'E', 'I', 'H', 'F', 'A', 'B', 'F', 'F', 'J', 'C', 'J', 'A', 'I', 'E', 'D', 'J', 'F', 'F', 'A', 'C', 'H', 'E', 'C', 'C', 'J', 'C', 'F', 'F', 'C', 'J', 'H', 'C', 'C', 'F', 'D', 'B', 'F', 'D', 'D', 'E', 'I', 'H', 'G', 'J', 'G', 'H', 'B', 'I', 'G', 'I', 'F', 'D', 'I', 'B', 'H', 'E', 'G', 'E', 'J', 'I', 'H', 'F', 'H', 'J', 'G', 'G', 'D', 'B', 'C', 'G', 'B', 'C', 'C', 'D', 'C', 'I', 'I', 'J', 'I', 'H', 'B', 'D', 'J', 'H', 'H', 'D', 'D' };
		ans = Solution().leastInterval(tasks, 80);  // 84260
		
	}
}
namespace Jul_day30_LC139
{
	struct Node
	{
		Node* next[27] = { nullptr };
	};
	class Trie 
	{
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
	class Solution 
	{
	private:
		Trie trie;
		std::vector<int> cache;
	public:
		bool canDesect(std::string s)
		{
			if ((s.size()) == 0) return true;
			if (cache[s.size()-1] == 0) return false;
			std::string test;
			bool subres = false;
			for (size_t i = 0; i < s.size(); i++)
			{
				test += s[i];
				if (trie.test(test) == 2)
				{
					std::cout << test << ",";
					std::string sub = s.substr(i+1, s.size());
					subres = canDesect(sub);
					if (subres) return true;
				}
			}
			std::cout << '\n';
			cache[s.size()-1] = 0;
			return false;

		}
		bool wordBreak(std::string s, std::vector<std::string>& wordDict) 
		{
			cache = std::vector<int>(s.size(), -1);
			for (auto str : wordDict)
			{
				trie.insert(str);
			}
			return canDesect(s);
		}
	};
	void RunExample()
	{
		std::vector<std::string> wordDict;
		std::string s;
		bool ans;
	
		wordDict = { "leet","code"};
		s = "leetcode";
		ans = Solution().wordBreak(s, wordDict);
		std::cout << ans;
		
		wordDict = { "apple","pen"};
		s = "applepenapple";
		ans = Solution().wordBreak(s, wordDict);
		std::cout << ans;

		wordDict = { "cats","dog","sand","and","cat" };
		s = "catsandog";
		ans = Solution().wordBreak(s, wordDict);
		std::cout << ans;

		wordDict = { "a", "aa", "aaa", "aaaa", "aaaaa", "aaaaaa", "aaaaaaa", "aaaaaaaa", "aaaaaaaaa", "aaaaaaaaaa" };
		s = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab";
		ans = Solution().wordBreak(s, wordDict);
		std::cout << ans;
	}
}
namespace Jul_day30
{
	struct Node
	{
		Node* next[27] = { nullptr };
	};
	class Trie
	{
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
	class Solution
	{
	private:
		Trie trie;
		std::vector<int> cache;
		std::vector<std::string> returnVec;
	public:
		bool canDesect(std::string s)
		{
			if ((s.size()) == 0) return true;
			if (cache[s.size() - 1] == 0) return false;
			std::string test;
			bool subres = false;
			for (size_t i = 0; i < s.size(); i++)
			{
				test += s[i];
				if (trie.test(test) == 2)
				{
					std::cout << test << ",";
					std::string sub = s.substr(i + 1, s.size());
					subres = canDesect(sub);
					if (subres) return true;
				}
			}
			cache[s.size() - 1] = 0;
			return false;
		}
		void Segment(std::string s, int tracker)
		{
			std::string test;
			for (size_t i = tracker; i < s.size(); i++)
			{
				test += s[i];
				if (trie.test(test) == 2)
				{
					if (i == s.size()-1)
					{
						returnVec.push_back(s);
					}
					else
					{
						s.insert(i + 1, 1, ' ');
						Segment(s, i + 2);
						s.erase(i + 1, 1);
					}
				}
			}
		}
		std::vector<std::string> wordBreak(std::string s, std::vector<std::string>& wordDict)
		{
			if (wordDict.size() == 0) return {};
			cache = std::vector<int>(s.size(), -1);
			for (auto str : wordDict)
			{
				trie.insert(str);
			}
			if (canDesect(s))
			{
				Segment(s, 0);
			}
			return returnVec;
		}
	};
	void RunExample()
	{
		std::vector<std::string> wordDict;
		std::string s;
		std::vector<std::string> ans;

		wordDict = { "a","aa","aaa" };
		s = "aaaaaaaaaab";
		ans = Solution().wordBreak(s, wordDict);

		wordDict = { "a", "b","cc" };
		s = "abcc";
		ans = Solution().wordBreak(s, wordDict);

		wordDict = { "cats","dog","sand","and","cat" };
		s = "catsanddog";
		ans = Solution().wordBreak(s, wordDict);


		wordDict = { "leet","code" };
		s = "leetcode";
		ans = Solution().wordBreak(s, wordDict);

		wordDict = { "apple","pen" };
		s = "applepenapple";
		ans = Solution().wordBreak(s, wordDict);
	}
}