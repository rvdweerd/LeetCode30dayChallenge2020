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

namespace May_day1 // LC278 First Bad Version
{
	// The API isBadVersion is defined for you.
	bool isBadVersion(int version)
	{
		return true; // don't have the implementation
	}
	class Solution {
		//std::unordered_map<int,bool> map;
	public:
		int firstBadVersion(int n) {
			int lo = 1;
			int hi = n;
			while (lo <= hi)
			{
				const int m = lo + (hi - lo) / 2;
				if (isBadVersion(m)) // pivot on the left
				{

					if (m == 1) return m;
					if (!isBadVersion(m - 1)) return m;
					hi = m - 1;
				}
				else // pivot on the right
				{
					if (m >= n - 1) return n;
					if (isBadVersion(m + 1)) return  m + 1;
					lo = m + 1;
				}
			}
			return 0;
		}
	};
}
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
namespace May_day10
{
	class Solution {
	public:
		int findJudge0(int N, std::vector<std::vector<int>>& trust) 
		{
			std::unordered_map<int, size_t> map_candidates;
			std::unordered_set<int> map_disqualified;
			if ((int)trust.size() < N - 1) return -1;
			map_candidates.insert({ 1,0 });
			for (auto v : trust)
			{
				// Trusting person is disqualified to be judge
				// -> Add to discualified set
				map_disqualified.insert(v[0]);
				// -> Remove from candidate list
				auto it_c0 = map_candidates.find(v[0]);
				if (it_c0 != map_candidates.end()) map_candidates.erase(it_c0);
				
				// Trusted person is a candidate, if not disqualified earlier
				auto it_d1 = map_disqualified.find(v[1]);
				if (it_d1 == map_disqualified.end())
				{
					map_candidates[v[1]]++;
				}
			}
			for (auto c : map_candidates)
			{
				if (c.second == N - 1) return c.first;
			}
			return -1;
		}
		int findJudge(int N, std::vector<std::vector<int>>& trust)
		{
			std::unordered_map<int, std::pair<size_t,size_t>> map_candidates;
			if ((int)trust.size() < N - 1) return -1;
			map_candidates.insert({ 1,  {0,0} });
			for (auto v : trust)
			{
				map_candidates[v[0]].first++;
				map_candidates[v[1]].second++;
			}
			for (auto c : map_candidates)
			{
				if (c.second.first == 0 && c.second.second == N - 1) return c.first;
			}
			return -1;
		}
	};
	void RunExample()
	{
		std::vector<std::vector<int>> vec = { {1, 3}, {1, 4}, {2, 3}, {2, 4}, {4, 3} };
		int ans = Solution().findJudge(4,vec); // 3
		vec = { {1,2},{2,3} };
		ans = Solution().findJudge(3, vec); // -1
		vec = { {1,3},{2,3},{3,1} };
		ans = Solution().findJudge(3, vec); // -1
		vec = { {1,3},{2,3} };
		ans = Solution().findJudge(3, vec); // 3
		vec = { {1,2} };
		ans = Solution().findJudge(2, vec); // 2
		vec = { {1,2} };
		ans = Solution().findJudge(0, vec); // -1
		vec = { {1,2} };
		ans = Solution().findJudge(1, vec); // -1
		vec = {  };
		ans = Solution().findJudge(1, vec); // 1


	}
}
namespace May_day11 // LC733 Flood Fill
{
	class Solution {
	private:
		struct Point
		{
			int row=0;
			int col=0;
		};
		
	public:
		std::vector<std::vector<int>> floodFill_cpy(std::vector<std::vector<int>>& image, int sr, int sc, int newColor) 
		{
			std::vector<std::vector<int>> floodedImage = image;
			if (image[sr][sc] == newColor) return image;
			std::queue<Point> queue;
			int oldColor = image[sr][sc];
			queue.push({ sr,sc });
			while (!queue.empty())
			{
				Point currentPos = queue.front(); queue.pop();
				floodedImage[currentPos.row][currentPos.col] = newColor;
				if (currentPos.row > 0 && floodedImage[currentPos.row - 1][currentPos.col] == oldColor) // Check NORTH
				{
					queue.push({ currentPos.row - 1, currentPos.col }); 
					floodedImage[currentPos.row-1][currentPos.col] = newColor;
				}
				if (currentPos.row < int(image.size() - 1) && floodedImage[currentPos.row + 1][currentPos.col] == oldColor) // Check SOUTH
				{
					queue.push({ currentPos.row + 1,currentPos.col }); 
					floodedImage[currentPos.row + 1][currentPos.col] = newColor;
				}
				if (currentPos.col < int(image[0].size() - 1) && floodedImage[currentPos.row][currentPos.col + 1] == oldColor)
				{
					queue.push({ currentPos.row, currentPos.col +1}); // East
					floodedImage[currentPos.row ][currentPos.col+1] = newColor;
				}
				if (currentPos.col > 0 && floodedImage[currentPos.row][currentPos.col - 1] == oldColor)
				{
					queue.push({ currentPos.row, currentPos.col - 1 }); // West
					floodedImage[currentPos.row ][currentPos.col-1] = newColor;
				}
			}
			return floodedImage;
		}
		std::vector<std::vector<int>> floodFill(std::vector<std::vector<int>>& image, int sr, int sc, int newColor)
		{
			//std::vector<std::vector<int>> floodedImage = image;
			if (image[sr][sc] == newColor) return image;
			std::queue<Point> queue;
			int oldColor = image[sr][sc];
			queue.push({ sr,sc });
			while (!queue.empty())
			{
				Point currentPos = queue.front(); queue.pop();
				image[currentPos.row][currentPos.col] = newColor;
				if (currentPos.row > 0 && image[currentPos.row - 1][currentPos.col] == oldColor) // Check NORTH
				{
					queue.push({ currentPos.row - 1, currentPos.col });
					image[currentPos.row - 1][currentPos.col] = newColor;
				}
				if (currentPos.row < int(image.size() - 1) && image[currentPos.row + 1][currentPos.col] == oldColor) // Check SOUTH
				{
					queue.push({ currentPos.row + 1,currentPos.col });
					image[currentPos.row + 1][currentPos.col] = newColor;
				}
				if (currentPos.col < int(image[0].size() - 1) && image[currentPos.row][currentPos.col + 1] == oldColor)
				{
					queue.push({ currentPos.row, currentPos.col + 1 }); // East
					image[currentPos.row][currentPos.col + 1] = newColor;
				}
				if (currentPos.col > 0 && image[currentPos.row][currentPos.col - 1] == oldColor)
				{
					queue.push({ currentPos.row, currentPos.col - 1 }); // West
					image[currentPos.row][currentPos.col - 1] = newColor;
				}
			}
			return image;
		}

	};
	void RunExample()
	{
		std::vector<std::vector<int>> image = { {1, 1, 1}, {1, 1, 0}, {1, 0, 1} };
		std::vector<std::vector<int>> flooded = Solution().floodFill(image, 1, 1, 2);
		image = { {0, 0, 0}, {0, 1, 0}};
		flooded = Solution().floodFill(image, 1, 1, 2);
	}
}
namespace May_day12 // LC540 Single Element in a Sorted Array
{
	class Solution {
	public:
		int singleNonDuplicate(std::vector<int>& nums) 
		{
			if (nums.size() == 1) return nums[0];
			size_t lo = 0;
			size_t hi = nums.size()-1;
			while (lo <= hi)
			{
				if (((hi - lo) / 2) % 2 == 0) //even number of pairs in range
				{
					const size_t mid = lo + (hi - lo) / 2;
					if (nums[mid] > nums[mid - 1] && nums[mid] < nums[mid + 1]) return nums[mid];
					if (nums[mid - 1] == nums[mid])
					{
						hi = mid;
					}
					else
					{
						lo = mid;
					}
				}
				else // uneven number of pairs in range
				{
					if (nums[hi] != nums[hi - 1]) return nums[hi];
					if (nums[lo] != nums[lo + 1]) return nums[lo];
					const size_t mid = lo + (hi - lo) / 2;
					if (nums[mid] == nums[mid + 1])
					{
						hi = mid - 1;
					}
					else
					{
						lo = mid + 1;
					}
				}
			}
			return -1;
		}
	};
	void RunExample()
	{
		std::vector<int> vec = { 3,3,7,7,10,11,11 };
		int ans = Solution().singleNonDuplicate(vec);
	}
}
namespace May_day13 // LC402 Remove K Digits
{
	
	class Solution {
	public:
		std::string oneRun(std::string num)
		{
			std::string result;
			for (size_t i = 0; i < num.size() - 1; i++)
			{
				char c1 = num[i];
				char c2 = num[i + 1];
				if (c2 >= c1)
				{
					result += c1;
				}
				else
				{
					if (i == 0)
						while (num[i+1] == '0') i++;
					result += num.substr(i + 1);
					break;
				}
			}
			if (result.size() == 0) return "0";
			else return result;
		}

		std::string removeKdigits(std::string num, int k) 
		{
			for (size_t i = 0; i < (size_t)k; ++i) num = oneRun(num);
			return num;
		}
	};
	void RunExample()
	{
		//std::string num = "1432219";
		
		std::string reduced;
		reduced = Solution().removeKdigits("1432219", 3);
		reduced = Solution().removeKdigits("10", 1);
		reduced = Solution().removeKdigits("10", 2);
		reduced = Solution().removeKdigits("531", 1);
		reduced = Solution().removeKdigits("315", 1);
		reduced = Solution().removeKdigits("112", 1);

		
	}
}
namespace May_day14 // LC208 Implement a Trie (prefix Tree)
{
	class Trie {
	private:
		
		struct Node
		{
			Node()
				:
				letters(27, nullptr)
			{}
			std::vector<Node*> letters;
		};
		Node* root;
	public:
		/** Initialize your data structure here. */
		Trie()
			:
			root(new Node)
		{}
		~Trie()
		{
			DeleteNode(root);
		}
		void DeleteNode(Node* node)
		{
			for (Node* n : node->letters)
			{
				if (n && n!=root) DeleteNode(n);
			}
			delete node;
			node = nullptr;
		}
		/** Inserts a word into the trie. */
		void insert(std::string word) 
		{
			Node* ptr = root;
			for (auto c : word)
			{
				if (ptr->letters[c - 'a'])
				{
					ptr = ptr->letters[c - 'a'];
				}
				else
				{
					ptr->letters[c - 'a'] = new Node();
					ptr = ptr->letters[c - 'a'];
				}
			}
			ptr->letters[26] = root;
		}

		/** Returns if the word is in the trie. */
		bool search(std::string word) 
		{
			Node* ptr = root;
			for (auto c : word)
			{
				if (ptr->letters[c - 'a']) ptr = ptr->letters[c - 'a'];
				else return false;
			}
			if (ptr->letters[26]) return true;
			else return false;
		}

		/** Returns if there is any word in the trie that starts with the given prefix. */
		bool startsWith(std::string prefix) 
		{
			Node* ptr = root;
			for (auto c : prefix)
			{
				if (ptr->letters[c - 'a']) ptr = ptr->letters[c - 'a'];
				else return false;
			}
			return true;
		}
	};

	/**
	 * Your Trie object will be instantiated and called as such:
	 * Trie* obj = new Trie();
	 * obj->insert(word);
	 * bool param_2 = obj->search(word);
	 * bool param_3 = obj->startsWith(prefix);
	 */

	void RunExample()
	{
		{
			Trie* trie = new Trie();
			//Trie trie;
			trie->insert("apple");
			trie->search("apple");   // returns true
			trie->search("app");     // returns false
			trie->startsWith("app"); // returns true
			trie->insert("app");
			trie->search("app");     // returns true

			trie->insert("oqerbfqrepuqeroghqeprughqepruhqeprg");
			//trie.insert("abs");
			delete trie;
		}
	}
}
namespace May_day15 // LC918 Maximum Sum Circular Subarray
{
	class Solution {
	public:
		int maxSubArray(std::vector<int>& A)
		{
			int currentSum = 0;
			int maxSum = A[0];// INT_MIN;
			for (auto v : A)
			{
				currentSum = std::max(v, currentSum+v);
				maxSum = std::max(maxSum, currentSum);
			}
			return maxSum;
		}
		int minSubArray(std::vector<int>& A, int i , int j )
		{
			int currentSum = 0;
			int minSum = 0;// A[0];// INT_MAX;
			for (int k = i; k < j; k++)
			{
				currentSum = std::min(A[k], currentSum + A[k]);
				minSum = std::min(minSum, currentSum);
			}
			return minSum;
		}
		int maxSubarraySumCircular(std::vector<int>& A) 
		{
			// Sum
			int S = 0;
			for (auto v : A) S += v;

			// Max sub array, not split
			int max_nosplit = maxSubArray(A);

			// Max sub array, split1
			int minSubArr_nosplit1 = minSubArray(A,0,A.size()-1);
			int max_split1 = S - minSubArr_nosplit1;
			
			// Max sub array, split2
			int minSubArr_nosplit2 = minSubArray(A, 1, A.size());
			int max_split2 = S - minSubArr_nosplit2;

			//auto old_count = A.size();
			//A.reserve(2 * old_count);
			//std::copy_n(A.begin(), old_count, std::back_inserter(A));
			return std::max(max_nosplit,std::max(max_split1,max_split2));
		}
	};
	void RunExample()
	{
		// TEST max subarr with band
		std::vector<int> vec;
		int ans;
		vec = { 5,-3, 5 };
		ans = Solution().maxSubarraySumCircular(vec); // 10
		vec = { -2 };
		ans = Solution().maxSubarraySumCircular(vec); // -2
		vec = { 3,-1,2,-1 };
		ans = Solution().maxSubarraySumCircular(vec); //4
		vec = { 3,-2,2,-3 };
		ans = Solution().maxSubarraySumCircular(vec); //3
		vec = { -2,-3,-1 };
		ans = Solution().maxSubarraySumCircular(vec); //-1
		vec = { -2,4,-5,4,-5,9,4 };
		ans = Solution().maxSubarraySumCircular(vec); // 15
		vec={52, 183, 124, 154, -170, -191, -240, 107, -178, 171, 75, 186, -125, 61, -298, 284, 21, -73, -294, 253, 146, 248, -248, 127, 26, 289, 118, -22, -300, 26, -116, -113, -44, 29, 252, -278, 47, 254, -106, 246, -275, 42, 257, 15, 96, -298, -69, -104, -239, -95, -4, 76, -202, 156, -14, -178, 188, -84, 78, -195, -125, 28, 109, 125, -25, -53, 58, 287, 55, -296, 198, 281, 53, -160, 146, 298, 25, -41, -3, 27, -242, 169, 287, -281, 19, 91, 213, 115, 211, -218, 124, -25, -272, 278, 296, -177, -166, -192, 97, -49, -25, 168, -81, 6, -94, 267, 293, 146, -1, -258, 256, 283, -156, 197, 28, 78, 267, -151, -230, -66, 100, -94, -66, -123, 121, -214, -182, 187, 65, -186, 215, 273, 243, -99, -76, 178, 59, 190, 279, 300, 217, 67, -117, 170, 163, 153, -37, -147, -251, 296, -176, 117, 68, 258, -159, -300, -36, -91, -60, 195, -293, -116, 208, 175, -100, -97, 188, 79, -270, 80, 100, 211, 112, 264, -217, -142, 5, 105, 171, -264, -247, 138, 275, 227, -86, 30, -219, 153, 10, -66, 267, 22, -56, -70, -234, -66, 89, 182, 110, -146, 162, -48, -201, -240, -225, -15, -275, 129, -117, 28, 150, 84, -264, 249, -85, 70, -140, -259, 26, 162, 5, -203, 143, 184, 101, 140, 207, 131, 177, 274, -178, -79, 14, -36, 104, 52, 31, 257, 273, -52, 74, 276, 104, -133, -255, 188, -252, 229, 200, -74, -39, -250, 142, -201, -196, -43, -40, 255, -149, -299, -197, -175, -96, -155, -196, -24, 12, 79, 71, -144, -59, -120, 227, -256, -163, -297, 116, 286, -283, -31, -221, -41, 121, -170, 160, 205, 8, 88, 25, -272, -107, 292, -180, 299, 94, -97, -81, -134, 37, 238};
		ans = Solution().maxSubarraySumCircular(vec); // 5803
		
		// TEST normal max subarrays
		std::vector<int> vec1 = { 3,-1,2,-1 };
		int ans2 = Solution().maxSubArray(vec1); //4
		vec1 = {-1,-2,-3};
		ans2 = Solution().maxSubArray(vec1); //-1
		vec1 = { -1,-2,-3,0 };
		ans2 = Solution().maxSubArray(vec1); //0
		vec1 = { 3, -2, 2, -3 };
		ans2 = Solution().maxSubArray(vec1); //3
		vec1 = { -2, 1 };
		ans2 = Solution().maxSubArray(vec1); //1
	}
}
namespace May_day16 // LC328 Odd Even Linked List
{
	/**
	* Definition for singly-linked list.
	**/
	struct ListNode {
		int val;
		ListNode *next;
		ListNode() : val(0), next(nullptr) {}
		ListNode(int x) : val(x), next(nullptr) {}
		ListNode(int x, ListNode *next) : val(x), next(next) {}
	};
	class Solution {
	public:
		ListNode* oddEvenList(ListNode* head) 
		{
			if (!head || head->next == nullptr || head->next->next == nullptr) return head;
			//ListNode* newLeftHead = head;
			ListNode* newRightHead = head->next;
			ListNode* pLeftRunner = head;
			ListNode* pRightRunner = head->next;
			while (pRightRunner->next)
			{
				pLeftRunner->next = pRightRunner->next;
				pLeftRunner = pLeftRunner->next;

				if (pLeftRunner->next)
				{
					pRightRunner->next = pLeftRunner->next;
					pRightRunner = pRightRunner->next;
				}
				else
				{
					pRightRunner->next = nullptr;
					break;
				}
			}
			pLeftRunner->next = newRightHead;
			return head;// newLeftHead;
		}
	};
	void RunExample()
	{
		ListNode* list = new ListNode(2, new ListNode(1, new ListNode(3, new ListNode(5, new ListNode(6, new ListNode(4, new ListNode(7)))))));
		ListNode* reordered_list = Solution().oddEvenList(list);
	}
}
namespace May_day17 // LC438  Find all anagrams in a string
{
	class Solution {
	public:
		std::vector<int> findAnagrams(std::string s, std::string p) 
		{
			// Initialize
			std::vector<int> returnvec;
			std::unordered_map<char, size_t> letterBox;
			for (auto c : p) letterBox[c]++;
			std::queue<char> queue;
			
			// Visit all letters in the search string
			for (size_t i = 0; i < s.size(); i++)
			{
				auto it = letterBox.find(s[i]);
				if (it != letterBox.end()) // picket letter is in originals
				{
					if (it->second > 0)  // picket letter is still available in letterbox
					{
						queue.push(s[i]);
						letterBox[s[i]]--;
						if (queue.size() == p.size()) // we have a match
						{
							returnvec.push_back(i-p.size()+1);
							letterBox[queue.front()]++; 
							queue.pop();
						}
					}
					else // ran out of picket letter in letterbox, unwind queue until we this letter is found & put back in the queue
					{
						while (queue.front() != s[i])
						{
							letterBox[queue.front()]++;
							queue.pop();
						}
						queue.pop(); queue.push(s[i]);
					}
				}
				else  // picket letter not in originals, fully unwind queue & move on
				{
					while (!queue.empty()) 
					{
						letterBox[queue.front()]++; 
						queue.pop();
					}
				}
			}
			return returnvec;
		}
	};
	void RunExample()
	{
		std::vector<int> ans;
		ans = Solution().findAnagrams("cbaebabacd", "abc"); // [0,6]
		ans = Solution().findAnagrams("abab", "ab"); //[0,1,2]
		ans = Solution().findAnagrams("abaacbabc", "abc"); // [3,4,6]

	}
}
namespace May_day18 // LC567  Permutation in a string
{
	class Solution {
	public:
		bool checkInclusion(std::string s1, std::string s2) // int array for character frequencies (12ms)
		{
			if (s1.size() > s2.size()) return false;
			int signature[26] = { 0 };
			int freq0[26] = { 0 };
			int delta[26] = { 0 };
			for (size_t i = 0; i < s1.size(); i++)
			{
				signature[s1[i] - 'a']++;
				freq0[s2[i] - 'a']++;
			}
			int  deficit=0;
			int excess=0;
			for (size_t i = 0; i < 26; i++)
			{
				int d = freq0[i] - signature[i];
				delta[i] += d;
				if (d > 0) excess+=d;
				if (d < 0)  deficit-=d;
			}
			if (deficit == 0 && excess == 0) return true;
			for (size_t i = 0, j = i + s1.size(); j < s2.size(); i++, j++)
			{
				char c_out = s2[i];
				char c_in = s2[j];
				if (delta[c_out - 'a']-- > 0) excess--; else deficit++;
				if (delta[c_in - 'a']++ < 0) deficit--; else excess++;
				if (deficit == 0 && excess == 0) return true;
			}
			return false;
		}
		bool checkInclusion0(std::string p, std::string s) // Map+queue based solution (28ms)(Code reused from LC438)
		{
			// Initialize
			std::unordered_map<char, size_t> letterBox;
			for (auto c : p) letterBox[c]++;
			std::queue<char> queue;

			// Visit all letters in the search string
			for (size_t i = 0; i < s.size(); i++)
			{
				auto it = letterBox.find(s[i]);
				if (it != letterBox.end()) // picket letter is in originals
				{
					if (it->second > 0)  // picket letter is still available in letterbox
					{
						queue.push(s[i]);
						letterBox[s[i]]--;
						if (queue.size() == p.size()) // we have a match
						{
							return true;
						}
					}
					else // ran out of picket letter in letterbox, unwind queue until we this letter is found & put back in the queue
					{
						while (queue.front() != s[i])
						{
							letterBox[queue.front()]++;
							queue.pop();
						}
						queue.pop(); queue.push(s[i]);
					}
				}
				else  // picket letter not in originals, fully unwind queue & move on
				{
					while (!queue.empty())
					{
						letterBox[queue.front()]++;
						queue.pop();
					}
				}
			}
			return false;
		}
		bool checkInclusion1(std::string s1, std::string s2) // Checking all permutations, brute force solution (TLE)
		{
			if (s1.size() > s2.size()) return false;
			std::unordered_set<std::string> set;
			std::sort(s1.begin(), s1.end());
			do
			{
				set.insert(s1);
			} while (std::next_permutation(s1.begin(), s1.end()));
			for (size_t i = 0; i <= s2.size() - s1.size(); i++)
			{
				std::string check = s2.substr(i, s1.size());
				if (set.find(s2.substr(i,s1.size())) != set.end()) return true;
			}
			return false;
		}
	};
	void RunExample()
	{
		bool   res;
		res = Solution().checkInclusion("abc", "bbbca"); // true
		res = Solution().checkInclusion("a", "ab"); // true
		res = Solution().checkInclusion("trinitrophenylmethylnitramine", "dinitrophenylhydrazinetrinitrophenylmethylnitramine");
		res = Solution().checkInclusion("adc", "dcda"); // true
		res = Solution().checkInclusion("ab", "eidbaooo"); //  true
		res = Solution().checkInclusion("ab", "eidboaoo"); // false
	}
}
namespace May_day19 // LC901 Online Stock Plan
{
	class StockSpanner { // Stack based
		struct Node
		{
			Node(int p, size_t s)
				:
				price(p),
				span(s)
			{
			}
			int price;
			size_t span;
		};
		std::stack<Node> stack;
	public:
		void Clear()
		{
			while (!stack.empty()) stack.pop();
			stack.push({ INT_MAX, 0 });
		}
		StockSpanner()
		{
			stack.push({ INT_MAX, 0 }); 
		}
		int next(int price)
		{
			size_t count = 1;
			while (price >= stack.top().price)
			{
				count+=stack.top().span;
				stack.pop();
			}
			stack.push({ price,count });
			return count;
		}
	};
	class StockSpanner1 { // Vector based
		struct Node
		{
			Node(int p,size_t s)
				:
				price(p),
				span(s)
			{
			}
			int price;
			size_t span;
		};
		std::vector<Node> history;
	public:
		void Clear()
		{
			history.clear();
			history.reserve(1000);
			history.emplace_back(INT_MAX, 0);
		}
		StockSpanner1() 
		{
			history.reserve(1000);
			history.emplace_back(INT_MAX, 0);
		}
		size_t SeekTrace(size_t i, int price)
		{
			size_t count = 0;
			if (history[i].price <= price)
			{
				count += history[i].span + SeekTrace(i - history[i].span, price);
			}
			return count;
		}
		int next(int price)
		{
			if (price < history.back().price || history.size() == 1)
			{
				history.emplace_back(price, 1);
				return 1;
			}
			else
			{
				size_t n = 1+SeekTrace(history.size() - 1, price);
				history.emplace_back(price, n);
				return n;
			}
		}
	};
	/**
	 * Your StockSpanner object will be instantiated and called as such:
	 * StockSpanner* obj = new StockSpanner();
	 * int param_1 = obj->next(price);
	 */
	void Run(const std::vector<int>& testvec, StockSpanner& S)
	{
		for (int n : testvec) std::cout << S.next(n) << ", "; std::cout << std::endl;
		S.Clear();
	}
	void RunExample()
	{
		auto S = StockSpanner();
		std::vector<int> testvec;
		testvec = { 100,80,60,70,60,75,85 }; Run(testvec, S);
		testvec = { 1,1,1,2,1,4,6 }; Run(testvec,S);				
	}
}
namespace May_day20 // LC230 Kth Smallest Element in a BST  
{
	/**
	* Definition for a binary tree node.*/
	struct TreeNode 
	{
		int val;
		TreeNode *left;
		TreeNode *right;
		TreeNode() : val(0), left(nullptr), right(nullptr) {}
		TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
	};
	class Solution {
	public:
		void VisitChildren(TreeNode* node,int& count,int& ans)
		{
			std::cout << "PRE-ORDER : "<<node->val<<", " << count << ", "<<ans<<"\n---------\n"; // PRE-ORDER
			if (count < 0) return; 
			if (node->left)
			{
				VisitChildren(node->left,count,ans);
			}
			count--;
			std::cout << "IN-ORDER  : "<< node->val<<", "<<count<< ", " << ans << "\n---------\n"; // IN-ORDER
			if (count == 0) {
				ans = node->val; count--;
			}
			if (count < 0) return;
			if (node->right) 
			{

				VisitChildren(node->right,count,ans);
			};
			std::cout << "POST-ORDER: " << node->val << ", " << count << ", " << ans << "\n---------\n"; // IN-ORDER
			if (count < 0) return;
		}
		int kthSmallest(TreeNode* root, int k) 
		{
			int ans = 0;
			VisitChildren(root,k,ans);
			return ans;
		}
	};
	void RunExample()
	{
		TreeNode* root = new TreeNode(5, new TreeNode(3),new TreeNode(6));
		root->left->left = new TreeNode(2, new TreeNode(1), nullptr);
		root->left->right = new TreeNode(4);
		root->right = new TreeNode(6);
		//TreeNode* root = new TreeNode(5);
		int ans;
		
		ans = Solution().kthSmallest(root, 6);
		int k = 0;
	}
}
namespace May_day21 // LC1277 Count Square Submatrices with All Ones
{
	class Solution {
	public:
		int countSquares(std::vector<std::vector<int>>& matrix) 
		{
			int count = 0;
			for (size_t row = 0; row < matrix.size(); row++)
			{
				for (size_t col = 0; col < matrix[0].size(); col++)
				{
					if (row != 0 && col != 0 && matrix[row][col] > 0)
					{
						const int L = matrix[row][col - 1];
						const int U = matrix[row-1][col];
						const int D = matrix[row - 1][col - 1];
						const int minLUD = std::min(L, std::min(U, D));
						matrix[row][col] += minLUD;

					}
					count += matrix[row][col];
				}
			}
			return count;
		}
	};
	void RunExample()
	{
		std::vector<std::vector<int>> matrix;
		int ans;
		matrix =
		{	{0,1,1,1},
			{1,1,1,1},
			{0,1,1,1}
		};
		ans = Solution().countSquares(matrix);
		
		matrix =
		{	{1,0,1},
			{1,1,0},
			{1,1,0}
		};
		ans = Solution().countSquares(matrix);

		matrix =
		{ {1}
		};
		ans = Solution().countSquares(matrix);
	}
}
namespace May_day22  // LC451 Sort characters by frequency
{
	static int fastio = []() {
		#define endl '\n'
		std::ios::sync_with_stdio(false);
		std::cin.tie(NULL);
		std::cout.tie(0);
		return 0;
	}();
	class Solution
	{
	public:
		std::string frequencySort(std::string s)
		{
			std::vector<std::pair<int, char>> freq('z' + 1, { 0,0 });
			for (char c : s)
			{
				freq[c] = { freq[c].first + 1,c };
			}
			std::sort(freq.rbegin(), freq.rend());
			std::string str_out;
			for (auto p : freq)
			{
				str_out.append(p.first, p.second);
			}
			return str_out;
		}

		std::string frequencySort_map(std::string s)
		{
			std::unordered_map<char, size_t> map;
			for (char c : s)
			{
				map[c]++;
			}
			std::multimap<size_t, char> mm;
			for (auto p : map)
			{
				mm.insert({ p.second,p.first });
			}
			std::string str_out;
			for (auto it = mm.rbegin(); it != mm.rend(); ++it)
			{
				str_out.append(it->first, it->second);
			}
			return str_out;
		}
	};
	void RunExample()
	{
		std::string str = "abaacc";
		std::string out = Solution().frequencySort(str);
	}
}
namespace May_day23  // LC986 Interval list intersections
{
	//using vec = std::vector<std::vector<int>>;
	//typedef std::vector<std::vector<int>> vec;
	class Solution
	{
	public:
		std::vector<std::vector<int>> intervalIntersection(std::vector<std::vector<int>>& A, std::vector<std::vector<int>>& B) 
		{
			std::vector<std::vector<int>> vec_out;
			for (size_t iA = 0, iB = 0; iA<A.size() && iB<B.size() ;)
			{
				int start = std::max(A[iA][0], B[iB][0]);
				int end = std::min(A[iA][1], B[iB][1]);
				if (end >= start)
				{
					vec_out.push_back({ start,end });
				}
				if (end == A[iA][1]) iA++;
				else iB++;
			}
			return vec_out;
		}
	};
	void RunExample()
	{
		typedef std::vector<std::vector<int>> vec;
		vec A = { {0, 2}, {5, 10}, {13, 23}, {24, 25} };
		vec B = { {1, 5}, {8, 12}, {15, 24}, {25, 26} };
		vec C = Solution().intervalIntersection(A, B);
	}
}
namespace May_day24 // LC1008 Construct Binary Search Tree from Preorder Traversal
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
		std::stack<TreeNode*> stack;
		TreeNode* bstFromPreorder(std::vector<int>& preorder)
		{
			TreeNode* root = new TreeNode(preorder[0]);
			stack.push(root);
			TreeNode* ptr = root;
			for (size_t i = 1; i < preorder.size(); i++)
			{
				if (preorder[i] < stack.top()->val)
				{
					ptr->left = new TreeNode(preorder[i]);
					ptr = ptr->left;
					stack.push(ptr);
				}
				else
				{
					while (!stack.empty() && preorder[i] > stack.top()->val)
					{
						ptr = stack.top();
						stack.pop();
					}
					ptr->right = new TreeNode(preorder[i]);
					ptr = ptr->right;
					stack.push(ptr);
				}
			}
			return root;
		}
		TreeNode* bstFromPreorder_ForLoop(std::vector<int>& preorder) 
		{
			TreeNode* root = new TreeNode(preorder[0]);
			for (size_t i = 1; i < preorder.size(); i++)
			{
				int val = preorder[i];
				TreeNode* runner = root;
				while (val < runner->val && runner->left || val > runner->val && runner->right)
				{
					if (val < runner->val) runner = runner->left;
					else runner = runner->right;
				}
				if (val < runner->val) runner->left = new TreeNode(val);
				else runner->right = new TreeNode(val);
			}
			return root;
		}
	private:
		struct Entry
		{
			int val;
			size_t d;
			std::vector<int> pos;
		};
		int l = 0, r = 0;
		size_t d = 0;
		size_t maxDepth = 0;
		std::vector<Entry> entries;
		std::vector<int> path;
		void GetNodePositions(TreeNode* root)
		{
			if (root)
			{
				std::cout << root->val << ", d=" << d << ", l=" << l << ", r=" << r << "\n";
				entries.push_back({ root->val,d,path });
				d++; l++; path.push_back(-1);
				GetNodePositions(root->left);
				l--; r++; path.pop_back(); path.push_back(1);
				GetNodePositions(root->right);
				r--; d--; path.pop_back();
			}
			else
			{
				maxDepth = std::max(maxDepth, d-1);
			}
		}
		std::vector<size_t> MakePaddingVector(size_t depth)
		{
			std::vector<size_t> vec_out;
			size_t max = 1;
			if (maxDepth > 1) max = (size_t)std::pow(2, maxDepth - 1);
			for (size_t i = 0; i < maxDepth; i++)
			{
				vec_out.push_back(max);
				max /= 2;
			}
			return vec_out;
		}
	public:
		std::vector<std::vector<std::string>> printTree(TreeNode* root)
		{
			GetNodePositions(root);
			std::vector<std::vector<std::string>> bstStringArray(maxDepth+1,std::vector<std::string>((int)std::pow(2,maxDepth+1)-1,""));
			std::vector<size_t> padding = MakePaddingVector(maxDepth); 
			size_t midPoint = bstStringArray[0].size() / 2;
			for (auto e : entries)
			{
				size_t row = e.d;
				size_t col = midPoint;
				for (size_t i = 0; i < e.pos.size(); i++)
				{
					col += e.pos[i] * padding[i];
				}
				bstStringArray[row][col] = std::to_string(e.val);
			}
			return bstStringArray;
		}
	};

	void RunExample()
	{
		//std::vector<int> vec;
		//vec = {8,5,1,7,10,12};
		//TreeNode* root = Solution().bstFromPreorder(vec);
		//auto ans = Solution().printTree(root);
		
		/*TreeNode* root = new TreeNode(3, nullptr, new TreeNode(30));
		root->right->left = new TreeNode(10, nullptr, new TreeNode(15));
		root->right->left->right->right = new TreeNode(45);
		auto ans = Solution().printTree(root);*/

		TreeNode* root = new TreeNode(1);
		auto ans = Solution().printTree(root);

	}
}
namespace May_day25 // LC1035 Uncrossed Lines
{
	class Solution
	{
	public:
		int maxUncrossedLines_FAULTY(std::vector<int>& A, std::vector<int>& B)
		{
			// Horrific rabbit hole before the DP insight. Does not guarantee optimum
			std::map<int, std::vector<int>> entriesB;
			for (int i = 0; i < (int)B.size(); i++) entriesB[B[i]].push_back(i);

			std::multimap<int, std::pair<int, int>> map;
			for (int i = 0; i < (int)A.size(); i++)
			{
				auto it = entriesB.find(A[i]);
				if (it != entriesB.end())
				{
					for (auto v : it->second)
					{
						map.insert({ i, { (int)v,0 } });
					}
				}
			}
			std::multimap<int, std::multimap<int, std::pair<int, int>>::iterator> processQueue;
			for (auto it = map.begin(); it != map.end(); ++it)
			{
				int count = 0;
				for (auto it_inner = map.begin(); it_inner != map.end(); ++it_inner)
				{
					if (it_inner->second.first > it->second.first && it_inner->first > it->first)
					{
						count++;
					}
				}
				it->second.second = count;
				processQueue.insert({ it->second.second,it });
			}
			int count = 0;
			int maxCount = 0;
			int matchB = -1;
			int iMin = -1;
			for (size_t i = 0; i < processQueue.size(); i++)
			{
				for (auto it = std::next(processQueue.rbegin(),i); it != processQueue.rend(); it++)
				{
					auto k = it->second->first;
					auto l = it->second->second.first;
					if (it->second->second.first > matchB && it->second->first > iMin)
					{
						count++;
						matchB = it->second->second.first; std::cout << matchB << ",";
						iMin = it->second->first;
					}
				}
				maxCount = std::max(count, maxCount);
				count = 0; matchB = -1; iMin = -1;
				std::cout << "maxcount: "<<maxCount << "\n";
			}
			return maxCount;
		}
		int maxUncrossedLines(std::vector<int>& A, std::vector<int>& B)
		{
			//  DP approach
			std::vector<std::vector<int>> DP(B.size() + 1, std::vector<int>(A.size() + 1, 0));
			for (int i = (int)A.size() - 1; i >= 0; i--)
			{
				for (int j = (int)B.size() - 1; j >= 0; j--)
				{
					DP[j][i] = std::max(DP[j + 1][i], DP[j][i + 1]);
					if (A[i] == B[j] && (DP[j][i + 1] == DP[j + 1][i]) && DP[j][i+1]  == DP[j+1][i+1] )
					{
						DP[j][i]++;
					}
				}
			}
			/*for (auto vec : DP)
			{
				for (auto v : vec)
				{
					std::cout << v << ",";
				}
				std::cout << "\n";
			}*/
			return DP[0][0];
		}
	};
	void RunExample()
	{
		std::vector<int> A, B;
		int ans;

		A = { 1,4,3,2 };
		B = { 1,2,4,3 };
		ans = Solution().maxUncrossedLines(A, B); //3

		A = { 1,3,2,4 };
		B = { 2,3,1,3 };
		ans = Solution().maxUncrossedLines(A, B); //2

		A = { 5,1,5 };
		B = { 1,5,1 };
		ans = Solution().maxUncrossedLines(A, B); //2

		A = { 1,3,7,1,7,5 };
		B = { 1,9,2,5,1 };
		ans = Solution().maxUncrossedLines(A, B); //2

		A = { 1,2,1,3 };
		B = { 1,2,1,3 };
		ans = Solution().maxUncrossedLines(A, B); //4

		A = { 4, 1, 2, 5, 1, 5, 3, 4, 1, 5 };
		B = {3, 1, 1, 3, 2, 5, 2, 4, 1, 3, 2, 2, 5, 5, 3, 5, 5, 1, 2, 1};
		ans = Solution().maxUncrossedLines(A, B); //7

		A = { 3, 2, 5, 3, 2, 3, 1, 2, 2, 5, 2, 5, 4, 4, 5 };
		B = { 3, 2, 3, 3, 5, 5, 1, 3, 3, 1, 5, 2, 5, 5, 3, 2, 4, 2, 1, 2 };
		ans = Solution().maxUncrossedLines(A, B); //10

		A = { 5,3,3,5,5,3,5,3,5,5 };
		B = { 2,5,5,1,4,5,3,3,2,2,3,2,3,3,1 };
		ans = Solution().maxUncrossedLines(A, B); //5

	}
}
namespace May_day27 // LC Possible BiPartition
{
	class Solution {
	public:
		bool possibleBipartition(int N, std::vector<std::vector<int>>& dislikes) 
		{
			if (dislikes.size() == 0) return true;
			Graph<int> graph;
			std::unordered_set<int> set;
			for (auto p : dislikes)
			{
				if (p[0] <= N && p[1] <= N)
				{
					set.insert(p[0]);
					set.insert(p[1]);
					graph.AddEdge(p[0], p[1], 0);
					graph.AddEdge(p[1], p[0], 0);
				}
			}
			//graph.PrintAdjacencyMap();
			//for (auto n : graph.nodemap)
			{
				if (!graph.IsDisjoint(graph.nodemap[dislikes[0][0]],set ) ) return false; // cycle with uneven #nodes
			}
			return true;
		}
	};
	void RunExample()
	{
		std::vector<std::vector<int>> dislikes;
		dislikes.reserve(1000);
		bool ans;

		dislikes = {};
		ans = Solution().possibleBipartition(1, dislikes);

		dislikes = { {1, 2}, {3, 4}, {4, 5}, {3, 5} };
		ans = Solution().possibleBipartition(5, dislikes); // false


		dislikes = { {1,2} ,{1,3},{2,4} }; // true
		ans = Solution().possibleBipartition(4,dislikes);

		dislikes = { {1,2} ,{1,3},{2,3} }; // false
		ans = Solution().possibleBipartition(3, dislikes);

		dislikes = { {1,2} ,{2,3},{3,4},{4,5},{1,5} }; // false
		ans = Solution().possibleBipartition(5, dislikes);

		dislikes = { {4, 7}, {4, 8}, {5, 6}, {1, 6}, {3, 7}, {2, 5}, {5, 8}, {1, 2}, {4, 9}, {6, 10}, {8, 10}, {3, 6}, {2, 10}, {9, 10}, {3, 9}, {2, 3}, {1, 9}, {4, 6}, {5, 7}, {3, 8}, {1, 8}, {1, 7}, {2, 4} };
		ans = Solution().possibleBipartition(10, dislikes);

		
		dislikes = { {44, 117}, {90, 187}, {62, 64}, {10, 170}, {23, 60}, {3, 170}, {65, 187}, {85, 168}, {131, 149}, {153, 160}, {76, 100}, {34, 153}, {20, 136}, {135, 139}, {17, 46}, {58, 152}, {110, 138}, {138, 145}, {1, 122}, {8, 107}, {64, 88}, {107, 163}, {38, 149}, {130, 170}, {46, 97}, {92, 116}, {54, 104}, {124, 187}, {11, 92}, {48, 152}, {90, 152}, {29, 63}, {10, 75}, {23, 95}, {36, 101}, {55, 139}, {2, 53}, {1, 53}, {140, 153}, {19, 174}, {20, 32}, {62, 75}, {62, 149}, {23, 53}, {35, 190}, {4, 35}, {55, 161}, {138, 151}, {85, 177}, {104, 122}, {30, 64}, {148, 152}, {63, 83}, {14, 153}, {29, 95}, {104, 115}, {10, 153}, {34, 138}, {106, 149}, {35, 41}, {2, 99}, {144, 174}, {52, 159}, {46, 197}, {25, 159}, {85, 118}, {101, 140}, {47, 64}, {62, 104}, {12, 159}, {54, 92}, {112, 174}, {177, 187}, {18, 107}, {1, 33}, {75, 102}, {20, 176}, {137, 170}, {2, 38}, {60, 75}, {88, 135}, {2, 128}, {153, 178}, {35, 132}, {69, 135}, {75, 124}, {96, 199}, {44, 159}, {96, 144}, {28, 174}, {29, 88}, {25, 104}, {53, 83}, {39, 159}, {38, 135}, {83, 125}, {150, 187}, {94, 158}, {4, 100}, {30, 86}, {158, 171}, {170, 184}, {8, 104}, {85, 143}, {159, 162}, {20, 200}, {12, 29}, {92, 199}, {64, 99}, {75, 176}, {20, 196}, {96, 111}, {104, 126}, {79, 158}, {166, 170}, {93, 96}, {126, 158}, {35, 167}, {25, 55}, {29, 81}, {7, 149}, {57, 152}, {81, 159}, {74, 85}, {46, 122}, {38, 55}, {129, 170}, {114, 117}, {117, 163}, {65, 109}, {2, 30}, {108, 153}, {55, 105}, {90, 159}, {64, 134}, {85, 197}, {35, 90}, {127, 149}, {104, 111}, {101, 126}, {75, 106}, {2, 82}, {29, 42}, {8, 170}, {104, 132}, {153, 186}, {83, 146}, {81, 107}, {140, 152}, {149, 160}, {29, 126}, {42, 170}, {53, 104}, {24, 153}, {23, 99}, {35, 169}, {78, 96}, {101, 129}, {104, 176}, {64, 157}, {100, 190}, {2, 186}, {64, 98}, {43, 100}, {94, 96}, {46, 51}, {10, 83}, {75, 99}, {20, 171}, {37, 86}, {85, 191}, {118, 135}, {63, 170}, {23, 164}, {118, 185}, {86, 194}, {20, 118}, {27, 117}, {92, 182}, {105, 138}, {27, 107}, {92, 172}, {100, 143}, {10, 20}, {5, 101}, {7, 85}, {80, 170}, {104, 183}, {1, 13}, {117, 119}, {86, 112}, {75, 189}, {96, 106}, {109, 168}, {23, 76}, {20, 178}, {4, 20}, {152, 181}, {23, 199}, {85, 184}, {22, 35}, {64, 160}, {23, 42}, {99, 170}, {23, 189}, {7, 158}, {29, 173}, {83, 160}, {138, 192}, {109, 127}, {31, 64}, {20, 91}, {27, 96}, {101, 169}, {46, 113}, {45, 104}, {64, 78}, {29, 106}, {15, 159}, {1, 143}, {90, 104}, {74, 187}, {21, 75}, {36, 149}, {55, 155}, {35, 113}, {80, 109}, {101, 133}, {96, 97}, {30, 75}, {23, 69}, {72, 109}, {21, 64}, {153, 197}, {50, 101}, {36, 104}, {40, 170}, {29, 37}, {20, 167}, {83, 190}, {35, 189}, {68, 149}, {1, 102}, {6, 83}, {26, 83}, {83, 93}, {135, 142}, {16, 104}, {75, 196}, {35, 131}, {109, 120}, {78, 83}, {29, 73}, {121, 185}, {169, 170}, {26, 158}, {98, 153}, {29, 99}, {51, 138}, {104, 165}, {53, 109}, {68, 75}, {109, 128}, {17, 101}, {64, 123}, {158, 186}, {117, 192}, {92, 125}, {17, 109}, {143, 149}, {100, 177}, {85, 195}, {25, 187}, {91, 107}, {109, 180}, {83, 193}, {61, 109}, {89, 170}, {112, 138}, {117, 155}, {60, 170}, {84, 159}, {23, 193}, {101, 120}, {149, 196}, {32, 96}, {117, 133}, {100, 195}, {75, 88}, {33, 158}, {96, 154}, {67, 185}, {87, 170}, {56, 149}, {107, 197}, {96, 146}, {35, 127}, {33, 83}, {109, 192}, {69, 86}, {2, 184}, {44, 104}, {140, 149}, {97, 117}, {138, 190}, {1, 44}, {40, 46}, {104, 193}, {6, 86}, {29, 33}, {109, 199}, {29, 121}, {155, 159}, {29, 91}, {1, 50}, {1, 119}, {83, 129}, {76, 159}, {76, 83}, {70, 153}, {1, 105}, {15, 83}, {55, 121}, {33, 187}, {16, 101}, {30, 117}, {86, 118}, {34, 104}, {35, 74}, {101, 146}, {64, 140}, {23, 78}, {104, 198}, {26, 170}, {159, 168}, {27, 86}, {96, 156}, {79, 187}, {51, 92}, {149, 173}, {94, 149}, {135, 189}, {28, 170}, {26, 86}, {174, 198}, {101, 116}, {179, 185}, {8, 29}, {57, 101}, {49, 86}, {55, 88}, {29, 197}, {135, 169}, {26, 149}, {96, 160}, {19, 83}, {20, 67}, {61, 138}, {121, 152}, {19, 109}, {74, 185}, {35, 200}, {64, 102}, {126, 170}, {35, 115}, {46, 67}, {96, 99}, {100, 180}, {23, 71}, {29, 144}, {45, 86}, {55, 179}, {20, 24}, {79, 185}, {86, 160}, {148, 170}, {59, 170}, {185, 193}, {20, 143}, {13, 170}, {1, 65}, {23, 146}, {85, 147}, {36, 170}, {91, 187}, {36, 185}, {104, 129}, {23, 65}, {23, 136}, {134, 149}, {56, 100}, {107, 160}, {79, 107}, {117, 164}, {61, 152}, {97, 138}, {36, 158}, {55, 146}, {125, 187}, {44, 85}, {32, 86}, {109, 151}, {159, 189}, {116, 117}, {18, 29}, {137, 153}, {88, 153}, {64, 176}, {23, 58}, {20, 168}, {85, 178}, {7, 23}, {113, 153}, {35, 47}, {110, 170}, {153, 189}, {148, 159}, {18, 174}, {46, 89}, {28, 86}, {52, 138}, {83, 150}, {23, 129}, {12, 170}, {95, 158}, {98, 174}, {20, 81}, {117, 196}, {135, 181}, {1, 22}, {17, 92}, {96, 134}, {41, 86}, {51, 187}, {37, 152}, {64, 145}, {109, 145}, {30, 138}, {12, 158}, {114, 152}, {125, 174}, {108, 170}, {127, 158}, {92, 108}, {48, 109}, {18, 55}, {104, 195}, {3, 153}, {93, 104}, {97, 109}, {47, 149}, {55, 94}, {1, 196}, {42, 187}, {20, 157}, {96, 198}, {4, 55}, {2, 67}, {13, 83}, {82, 138}, {92, 178}, {49, 83}, {152, 199}, {55, 93}, {47, 96}, {1, 200}, {83, 133}, {2, 151}, {31, 109}, {20, 70}, {55, 123}, {145, 187}, {12, 149}, {75, 177}, {35, 76}, {48, 100}, {20, 53}, {109, 164}, {60, 92}, {20, 190}, {55, 180}, {75, 151}, {35, 82}, {44, 170}, {74, 96}, {101, 179}, {109, 116}, {92, 147}, {68, 170}, {47, 75}, {29, 169}, {101, 114}, {179, 187}, {118, 174}, {55, 195}, {153, 192}, {58, 158}, {40, 92}, {92, 156}, {21, 109}, {107, 173}, {37, 138}, {2, 136}, {108, 152}, {7, 100}, {92, 98}, {29, 32}, {1, 60}, {19, 55}, {73, 101}, {83, 161}, {87, 109}, {104, 110}, {100, 156}, {128, 185}, {23, 182}, {100, 113}, {74, 117}, {23, 172}, {157, 185}, {9, 152}, {63, 85}, {10, 159}, {174, 177}, {95, 152}, {64, 89}, {150, 174}, {133, 174}, {136, 158}, {135, 190}, {30, 101}, {95, 185}, {19, 64}, {2, 24}, {55, 73}, {90, 153}, {22, 83}, {65, 153}, {75, 133}, {46, 50}, {9, 92}, {55, 160}, {93, 109}, {35, 166}, {68, 152}, {4, 149}, {55, 59}, {153, 168}, {96, 193}, {1, 88}, {46, 178}, {85, 154}, {14, 158}, {117, 129}, {56, 109}, {100, 144}, {169, 185}, {158, 161}, {140, 187}, {92, 112}, {55, 124}, {11, 159}, {138, 194}, {85, 200}, {71, 185}, {5, 153}, {139, 149}, {91, 100}, {64, 137}, {100, 178}, {56, 159}, {23, 108}, {27, 85}, {43, 159}, {29, 180}, {21, 23}, {92, 150}, {52, 75}, {99, 117}, {86, 196}, {35, 60}, {96, 167}, {103, 107}, {135, 150}, {101, 119}, {85, 141}, {28, 117}, {104, 151}, {3, 109}, {66, 85}, {17, 75}, {85, 126}, {27, 135}, {42, 85}, {159, 173}, {104, 189}, {53, 101}, {109, 136}, {1, 7}, {102, 187}, {76, 138}, {168, 187}, {56, 64}, {170, 195}, {34, 100}, {94, 109}, {1, 162}, {63, 92}, {159, 197}, {69, 101}, {20, 184}, {55, 182}, {2, 62}, {29, 54}, {62, 92}, {101, 127}, {100, 155}, {46, 131}, {63, 64}, {14, 104}, {185, 188}, {20, 140}, {97, 185}, {92, 139}, {9, 149}, {86, 177}, {22, 64}, {145, 152}, {83, 140}, {96, 119}, {105, 159}, {45, 158}, {42, 92}, {55, 114}, {109, 129}, {21, 85}, {37, 107}, {138, 167}, {85, 130}, {41, 104}, {92, 124}, {16, 86}, {137, 138}, {23, 67}, {8, 83}, {53, 159}, {33, 96}, {19, 35}, {75, 142}, {107, 157}, {23, 57}, {20, 93}, {104, 118}, {35, 42}, {20, 139}, {1, 69}, {2, 77}, {94, 170}, {34, 85}, {31, 55}, {78, 85}, {46, 93}, {75, 89}, {4, 107}, {92, 184}, {53, 174}, {42, 174}, {170, 171}, {104, 171}, {123, 153}, {83, 178}, {30, 107}, {86, 132}, {170, 181}, {104, 177}, {148, 153}, {1, 11}, {126, 152}, {115, 149}, {46, 171}, {12, 64}, {68, 101}, {79, 149}, {45, 101}, {55, 162}, {48, 64}, {29, 34}, {163, 174}, {7, 138}, {23, 44}, {39, 86}, {23, 150}, {13, 86}, {20, 119}, {117, 143}, {154, 187}, {1, 112}, {157, 170}, {71, 135}, {19, 101}, {122, 159}, {8, 158}, {51, 153}, {39, 138}, {63, 153}, {187, 200}, {76, 187}, {96, 168}, {31, 96}, {138, 169}, {1, 181}, {46, 81}, {61, 135}, {109, 141}, {2, 178}, {35, 164}, {86, 113}, {55, 157}, {85, 93}, {101, 147}, {23, 79}, {9, 75}, {1, 38}, {2, 172}, {159, 179}, {29, 194}, {23, 198}, {88, 138}, {1, 189}, {23, 37}, {83, 189}, {52, 85}, {17, 29}, {64, 112}, {54, 75}, {72, 83}, {23, 154}, {55, 198}, {17, 174}, {1, 148}, {87, 185}, {59, 107}, {187, 193}, {165, 170}, {76, 174}, {107, 168}, {29, 105}, {108, 135}, {27, 153}, {1, 142}, {5, 109}, {109, 134}, {86, 136}, {84, 104}, {35, 112}, {7, 107}, {159, 181}, {20, 49}, {64, 130}, {140, 158}, {23, 68}, {55, 176}, {141, 185}, {9, 86}, {23, 181}, {104, 113}, {35, 39}, {67, 149}, {1, 66}, {75, 192}, {6, 185}, {50, 86}, {107, 139}, {29, 72}, {15, 107}, {184, 187}, {101, 139}, {187, 198}, {45, 185}, {153, 183}, {174, 178}, {117, 120}, {21, 83}, {7, 96}, {117, 176}, {159, 178}, {96, 121}, {35, 116}, {57, 83}, {51, 117}, {43, 96}, {27, 170}, {153, 188}, {46, 47}, {20, 38}, {64, 191}, {83, 192}, {22, 159}, {56, 107}, {7, 20}, {20, 61}, {55, 62}, {153, 171}, {84, 152}, {73, 85}, {63, 174}, {83, 177}, {2, 160}, {14, 83}, {116, 149}, {24, 109}, {2, 145}, {135, 156}, {35, 145}, {34, 149}, {46, 156}, {85, 157}, {92, 95}, {46, 106}, {53, 117}, {69, 75}, {149, 151}, {46, 199}, {44, 83}, {83, 88}, {96, 112}, {109, 146}, {8, 92}, {134, 187}, {46, 169}, {138, 182}, {23, 118}, {46, 54}, {146, 158}, {9, 64}, {83, 137}, {61, 64}, {85, 188}, {153, 172}, {109, 198}, {25, 64}, {158, 188}, {29, 48}, {51, 86}, {85, 166}, {117, 141}, {17, 153}, {104, 142}, {129, 185}, {49, 92}, {152, 198}, {83, 123}, {21, 101}, {170, 186}, {122, 135}, {7, 86}, {1, 139}, {46, 87}, {62, 109}, {60, 101}, {2, 176}, {58, 85}, {108, 149}, {128, 149}, {37, 101}, {117, 178}, {46, 57}, {109, 195}, {18, 100}, {55, 181}, {23, 192}, {104, 167}, {153, 181}, {101, 105}, {23, 190}, {117, 150}, {153, 166}, {34, 158}, {1, 79}, {2, 119}, {49, 85}, {45, 135}, {55, 192}, {20, 102}, {8, 135}, {154, 170}, {29, 196}, {64, 200}, {23, 114}, {65, 117}, {29, 103}, {1, 128}, {80, 159}, {1, 140}, {88, 174}, {6, 107}, {109, 132}, {1, 27}, {55, 148}, {138, 184}, {35, 114}, {5, 117}, {20, 51}, {64, 132}, {26, 75}, {66, 101}, {139, 153}, {39, 104}, {15, 158}, {168, 170}, {43, 109} };
		ans = Solution().possibleBipartition(200, dislikes);
	}
}
namespace May_day28
{
	class Solution {
	public:
		std::vector<int> countBits(int num) 
		{
			if (num == 0) return { 0 };
			std::vector<int> vec;
			vec.reserve(num + 1);
			vec.push_back(0); vec.push_back(1);
			if (num == 1) return vec;
			int p1 = 1;
			int len = 1;

			for (int i = 2; i < num+1; i++)
			{
				int c = 0;
				for (int j = 0; j < len && i+j<num+1; j++)
				{
					vec.push_back(vec[p1 + j]);
					c++;
				}
				for (int j = 0; j < len && i+c < num+1; j++)
				{
					vec.push_back(vec[p1 + j]+1);
					c++;
				}
				len *= 2;
				p1 *= 2;
				i += c-1;
			}
			return vec;
		}
	};
	void PrintVec(const std::vector<int>& vec)
	{
		for (auto v : vec)
		{
			std::cout << v << ", ";
		}
		std::cout << "\n";
	}
	void RunExample()
	{
		int n;
		std::vector<int> vec;
		n = 0; vec = Solution().countBits(n); std::cout << "n=" << n << ", vec: "; PrintVec(vec);
		n = 1; vec = Solution().countBits(n); std::cout << "n=" << n << ", vec: "; PrintVec(vec);
		n = 5; vec = Solution().countBits(n); std::cout << "n=" << n << ", vec: "; PrintVec(vec);
		n = 15; vec = Solution().countBits(n); std::cout << "n=" << n << ", vec: "; PrintVec(vec);
		n = 25; vec = Solution().countBits(n); std::cout << "n=" << n << ", vec: "; PrintVec(vec);
	}
}