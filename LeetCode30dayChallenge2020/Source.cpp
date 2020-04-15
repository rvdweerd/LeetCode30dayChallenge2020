#include <iostream>
#include <cstring>
#include <vector>
#include <set>
#include <unordered_map>
#include <unordered_set>


namespace day12a
{
	class Solution {
		int nSinglePass(std::vector<int>& nums, int& max_len)
		{
			int balance = 0;
			int count = 0;
			for (int i = 0; i < nums.size(); i++)
			{
				balance += (nums[i] == 0 ? -1 : 1);
				if (balance == 0)
				{
					count++;
					if (i + 1 > max_len) max_len = i + 1;
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
namespace day12b
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
namespace day13
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
		std::cout << day13::Solution().stringShift(str13, shift);
	}
}

namespace day14
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

			for (int i = 1; i < len; i++)
			{
				right[i] = right[i - 1] * nums[i];
				left[len - 1 - i] = left[len - i] * nums[len - 1 - i];
			}
			std::vector<int> out(len, 0);
			out[0] = left[1];
			out[len - 1] = right[len - 2];
			for (int i = 1; i < len - 1; i++)
			{
				out[i] = right[i - 1] * left[i + 1];
			}
			return out;
		}
	};
	void RunExample()
	{
		std::vector<int> vec_in = { 1,2,3,4 };
		std::vector<int> vec_out = day14::Solution().productExceptSelf(vec_in);
	}
}

int main()
{
	day14::RunExample();

	std::cin.get();
	return 0;
}