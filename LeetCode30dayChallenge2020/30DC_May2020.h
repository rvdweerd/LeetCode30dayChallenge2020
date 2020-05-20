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
namespace May_day20
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