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