#include <algorithm>
#include <iterator>
#include <iostream>
#include <cstring>
#include <vector>
#include <set>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <stack>
#include <queue>

namespace day1
{
	// I learned this optimized solution from Errichto
	class Solution {
	public:
		int singleNumber(std::vector<int>& nums) {
			int x = 0;
			for (const auto v : nums)
			{
				x ^= v;
			}
			return x;
		}
	};
}
namespace day2
{
	std::vector<int> GetDigits(int n)
	{
		std::vector<int> vec;
		for (; n != 0; n /= 10)
		{
			vec.push_back(n % 10);
		}
		return vec;
	}
	int SumSquares(std::vector<int> v)
	{
		int r = 0;
		for (const auto& val : v)
		{
			r += (val * val);
		}
		return r;
	}
	bool IsHappy(int n)
	{
		std::set<int> set;
		int sumSq = 0;
		while (true)
		{
			std::vector<int> vec = GetDigits(n);
			n = SumSquares(vec);
			if (n == 1)
			{
				return true;
			}
			else if (set.find(n) != set.end())
			{
				return false;
			}
			set.insert(n);
		}
	}
}
namespace day3
{
	int maxSubArray(std::vector<int>& nums)
	{
		int MIN = 0;
		int MAX = nums[0];
		int accum = 0;
		int maxRange = nums[0];
		for (int i = 0; i < (int)nums.size(); i++)
		{
			accum += nums[i];
			if (accum <= MIN)
			{
				if (accum - MIN > maxRange)
				{
					maxRange = accum - MIN;
				}
				MIN = accum;
			}
			if (accum > MIN && (accum - MIN > maxRange))
			{
				maxRange = accum - MIN;
			}
		}
		return maxRange;
	}
}
namespace day4
{
	class Solution {
	public:
		void moveZeroes(std::vector<int>& nums)
		{
			for (size_t slow_nz = 0, cur = 0; cur < nums.size(); cur++)
			{
				if (nums[cur] != 0)
				{
					std::swap(nums[slow_nz++], nums[cur]);
				}
			}
		}
	};
}
namespace day5
{
	class Solution {
	public:
		int maxProfit(std::vector<int>& prices) {
			int profit = 0;
			for (size_t i = 1; i < prices.size(); i++)
			{
				if (prices[i] > prices[i - 1]) profit += prices[i] - prices[i - 1];
			}
			return profit;
		}
	};
}
namespace day6
{
	class Solution
	{
	public:
		std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs)
		{
			std::vector<std::vector<std::string>> mainvec;
			std::map<std::string, std::set<std::string>> map;
			for (size_t i = 0; i < strs.size(); i++)
			{
				std::string temp = strs[i];
				std::sort(temp.begin(), temp.end());
				map[temp].insert(strs[i]);
			}
			for (const auto& p : map)
			{
				std::vector<std::string> subvec;
				subvec.insert(subvec.end(), p.second.begin(), p.second.end());
				mainvec.push_back(subvec);
				//mainvec.emplace_back(p.second.begin(),p.second.end());
			}
			return mainvec;
		}
	};
}
namespace day7
{
	class Solution {
	public:
		int countElements(std::vector<int>& arr) {
			int count = 0;
			for (auto v : arr)
			{
				if (std::count(arr.begin(), arr.end(), v + 1) > 0) count++;
			}
			return count;
		}
	};
}
namespace day8
{
	// Definition for singly-linked list.
	struct ListNode {
	    int val;
	    ListNode *next;
	    ListNode(int x) : val(x), next(NULL) {}
	};
	class Solution {
	public:
		ListNode* middleNode(ListNode* head)
		{
			int count = 0;
			for (ListNode* p = head; p != nullptr; p = p->next)
			{
				count++;
			}
			ListNode* ret = head;
			for (int i = 0; i < count / 2; i++)
			{
				ret = ret->next;
			}
			return ret;

		}
	};
}
namespace day9
{
	class Solution {
	public:
		std::string ClearString2(const std::string& str)
		{
			std::string ret_str;
			for (const char& c : str)
			{
				if (c == '#')
				{
					if (ret_str.size() != 0)
					{
						ret_str.erase(ret_str.end() - 1);
					}
				}
				else
				{
					ret_str += c;
				}
			}
			return ret_str;
		}
		bool backspaceCompare(std::string S, std::string T) {
			return ClearString2(S) == ClearString2(T);
		}
		void ClearString(std::string& str)
		{
			auto begin = str.begin();
			auto end = str.end();
			for (auto it = str.begin(); it != end;)
			{

				if (*it == '#')
				{
					if (it != begin)
					{
						it = str.erase(std::prev(it), std::next(it));
					}
					else
					{
						it = str.erase(it);
					}
					end = str.end();
				}
				else
				{
					it++;
				}

			}
		}
	};
}
namespace day10
{
	class MinStack {
	public:
		//** initialize your data structure here. */
		MinStack()
		{
		}
		void push(int x)
		{
			if (x < min) min = x;
			arr[index++] = min;
			arr[index++] = x;
		}
		void pop()
		{
			if (index != 0)
			{
				index -= 2;
			}
			if (index == 0)
			{
				min = INT_MAX;
			}
			else
			{
				min = arr[index - 2];
			}
		}
		int top()
		{
			return arr[index - 1];
		}
		int getMin()
		{
			return arr[index - 2];
		}

	private:
		int arr[20000];
		int min = INT_MAX;
		size_t index = 0;
	};
	/**
	 * Your MinStack object will be instantiated and called as such:
	 * MinStack* obj = new MinStack();
	 * obj->push(x);
	 * obj->pop();
	 * int param_3 = obj->top();
	 * int param_4 = obj->getMin();
	 */
}
namespace day10b
{
	// Node based stack
	class MinStack
	{
	private:
		struct Node
		{
			Node(int val_in)
				:
				val(val_in),
				min_val(val_in)
			{

			}
			int val;
			int min_val;
			Node* next = nullptr;
		};
		Node* root = nullptr;
		int min(int a, int b)
		{
			return a < b ? a : b;
		}
	public:
		/** initialize your data structure here. */
		MinStack()
		{
		}
		~MinStack()
		{
			while (root != nullptr)
			{
				pop();
			}
		}
		void push(int x)
		{
			Node* newNode = new Node(x);
			if (root != nullptr && x > root->min_val)
			{
				newNode->min_val = root->min_val;
			}
			newNode->next = root;
			root = newNode;
		}
		void pop()
		{
			if (root != nullptr)
			{
				Node* tmp = root;
				root = root->next;
				delete tmp;
			}
		}
		int top()
		{
			return root->val;
		}
		int getMin()
		{
			return root->min_val;
		}
	};
	
}
namespace day11 // Diameter of binary tree
{
	// Definition for a binary tree node.
	struct TreeNode 
	{
    int val;
	TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	};
 
	class Solution {
	public:
		int diameterOfBinaryTree(TreeNode* root)
		{
			std::vector<int> nodeSums;
			TraverseTree(root, nodeSums);
			if (nodeSums.size() > 0)
			{
				auto it = std::max_element(nodeSums.begin(), nodeSums.end());
				return *it;// , [](const int a, const int b) {return a > b; });
			}
			return 0;
			// n_left= depth left
			// n_right = depth right
			// add pair to vec
			// same for children
			//return 0;
		}
		int getDepthOfBinaryTree(TreeNode* root)
		{
			d_max = 0;
			setDepthOfBinaryTree(root, 0);
			return d_max;
		}
	private:
		int d_max = 0;
		void setDepthOfBinaryTree(TreeNode* root, int n)
		{
			if (root != nullptr)
			{
				setDepthOfBinaryTree(root->left, n + 1);
				setDepthOfBinaryTree(root->right, n + 1);
			}
			if (n > d_max) d_max = n;
		}
		void TraverseTree(TreeNode* root, std::vector<int>& nodeSums)
		{
			if (root != nullptr)
			{
				nodeSums.emplace_back(getDepthOfBinaryTree(root->left) + getDepthOfBinaryTree(root->right));
				TraverseTree(root->left, nodeSums);
				TraverseTree(root->right, nodeSums);
			}
			return;
		}
	};
}
namespace day12 // Last stone weight
{
	class Solution {
	public:
		int lastStoneWeight(std::vector<int>& stones) {
			std::priority_queue<int> queue(stones.begin(), stones.end());
			while (queue.size() > 1)
			{
				const int s1 = queue.top(); queue.pop();
				const int s2 = queue.top(); queue.pop();
				queue.push(s1 - s2);
			}
			if (queue.empty()) return 0; else return queue.top();
		}
	};
}
namespace day13a // Contiguous Array
{
	class Solution {
		int nSinglePass(std::vector<int>& nums, int& max_len)
		{
			int balance = 0;
			int count = 0;
			for (size_t i = 0; i < nums.size(); i++)
			{
				balance += (nums[i] == 0 ? -1 : 1);
				if (balance == 0)
				{
					count++;
					if ((int)i + 1 > max_len) max_len = i + 1;
				}
			}
			return count;
		}
	public:
		int findMaxLength(std::vector<int>& nums) {
			int tot = 0;
			int max_len = 0;
			int vecsize = nums.size();
			for (int i = 0; i < vecsize; i++)
			{
				tot += nSinglePass(nums, max_len);
				nums.erase(nums.begin());
			}
			return max_len;
		}
	};
}
namespace day13b
{
	class Solution {

	public:
		int findMaxLength(std::vector<int>& nums)
		{
			if (nums.size() < 2) return 0;
			std::unordered_map<int, int> map;
			map[0] = 0;
			int max_len = 0;
			int counter = 0;
			for (size_t i = 0; i < nums.size(); i++)
			{
				counter += (nums[i] == 0 ? -1 : 1);


				auto it = map.find(counter);
				if (it == map.end())
				{
					map[counter] = i + 1;
				}
				else
				{
					const int len = i - it->second + 1;
					if (len > max_len) max_len = len;
				}
			}
			return max_len;
		}
	};
}
namespace day14
{
	class Solution {
	public:
		std::string stringShift(std::string s, std::vector<std::vector<int>>& shift) {
			size_t sz = s.size();
			for (std::vector<int> sh : shift)
			{
				if (sh[0] == 0)
				{
					//std::transform(s.begin(), s.begin() + sh[1], std::back_inserter(s), [](char c) {return c; }); // 
					/*for (int i = 0; i < sh[1]; i++)
					{
						s.push_back(s.front());

					}
					s = s.substr(sh[1]);*/
					s.insert(s.end(), s.begin(), s.begin() + sh[1]);
					s = s.substr(sh[1]);
				}
				else
				{
					s.insert(s.begin(), s.end() - sh[1], s.end());
					s.resize(s.size() - sh[1]);
				}
			}
			return s;
		}
	};
	void RunExample()
	{
		std::vector<std::vector<int>> shift = { {1,1},{1,1},{0,2},{1,3} };
		std::string str13 = "abcdefg";
		std::cout << day14::Solution().stringShift(str13, shift);
	}
}
namespace day15
{
	class Solution {
	public:
		std::vector<int> productExceptSelf(std::vector<int>& nums)
		{
			const size_t len = nums.size();
			//std::vector<int> right(len,0); right[0] = nums[0];
			//std::vector<int> left(len, 0); left[len - 1] = nums.back();
			std::vector<int> right; right.resize(len); right[0] = nums.front();
			std::vector<int> left; left.resize(len); left[len - 1] = nums.back();

			for (size_t i = 1; i < len; i++)
			{
				right[i] = right[i - 1] * nums[i];
				left[len - 1 - i] = left[len - i] * nums[len - 1 - i];
			}
			std::vector<int> out(len, 0);
			out[0] = left[1];
			out[len - 1] = right[len - 2];
			for (size_t i = 1; i < len - 1; i++)
			{
				out[i] = right[i - 1] * left[i + 1];
			}
			return out;
		}
	};
	void RunExample()
	{
		std::vector<int> vec_in = { 1,2,3,4 };
		std::vector<int> vec_out = day15::Solution().productExceptSelf(vec_in);
	}
}
namespace day16
{
	class Solution {
	public:
		bool checkValidString(std::string s)
		{
			if (s.size() < 1) return true;
			if (s.front() == ')' || s.back() == '(') return false;
			std::stack<int> open;
			std::stack<int> stars;
			for (size_t i = 0; i < s.size(); i++)
			{
				if (s[i] == '(')
				{
					open.push(i);
				}
				else if (s[i] == '*')
				{
					stars.push(i);
				}
				else if (s[i] == ')')
				{
					if (!open.empty())
					{
						open.pop();
					}
					else
					{
						if (stars.empty())
						{
							return false;
						}
						else
						{
							stars.pop();
						}
					}
				}
			}
			if (open.empty())
			{
				return true;
			}

			while (!open.empty() && !stars.empty() && open.top() < stars.top())
			{
				open.pop();
				stars.pop();
			}
			if (open.empty())
			{
				return true;
			}
			return false;
		}
	};
	void RunExample()
	{
		std::cout << day16::Solution().checkValidString("*(()*))");//T
		std::cout << day16::Solution().checkValidString(")*()");//F
		std::cout << day16::Solution().checkValidString("**())");//T
		std::cout << day16::Solution().checkValidString("(*))");//T
		std::cout << day16::Solution().checkValidString("(*()");//T
	}
}


int main()
{
	day16::RunExample();

	std::cin.get();
	return 0;
}