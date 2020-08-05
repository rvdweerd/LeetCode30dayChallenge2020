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

namespace Aug_day5
{
	class WordDictionary
	{
		struct Node
		{
			Node()
				:
				vec(27)
			{}
			std::vector<Node*> vec;
		};
		Node* root = new Node;
	public:
		void addWord(std::string&& word)
		{
			Node* ptr = root;
			for (char ch : word)
			{
				if (ptr->vec[ch - 'a']) ptr = ptr->vec[ch - 'a'];
				else
				{
					Node* newNode = new Node;
					ptr->vec[ch - 'a'] = newNode;
					ptr = ptr->vec[ch - 'a'];
				}
			}
			ptr->vec[26] = root;
		}
		bool match(std::string& word)
		{
			return matchRemaining(word,0,root);
		}
		bool matchRemaining(std::string& word, size_t n,Node* ptr)
		{
			for (size_t i = n; i < word.size(); i++)
			{
				if (word[i] == '.')
				{
					for (size_t index = 0; index < 26; index++)
					{
						if (ptr->vec[index])
						{
							if (matchRemaining(word, i+1, ptr->vec[index])) return true;
						}
					}
					return false;
				}
				else if (ptr->vec[word[i] - 'a']) ptr = ptr->vec[word[i] - 'a'];
				else return false;
			}
			if (ptr->vec[26]) return true;
			return false;
		}
		/** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
		bool search(std::string&& word) 
		{
			return matchRemaining(word,0,root);
		}
	};
	void RunExample()
	{
		WordDictionary dict;
		dict.addWord("a");
		bool a = false;
		a = dict.search("a");
		a = dict.search("aa");
		a = dict.search(".");
		a = dict.search(".a");
		a = dict.search("a.");
		a = dict.search("..");

		return;

	}
}
