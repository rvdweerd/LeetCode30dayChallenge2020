#pragma once
#include <algorithm>
#include <iterator>
#include <iostream>
#include <cstring>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <queue>
#include "30DC_Apr2020.h"
#include "30DC_May2020.h"
#include "Problems.h"
#include "GraphClass.h" 

int main()
{
	//Apr20_day30::RunExample();
	//May_day6::RunExample();
	LC685::RunExample();
	Graph<std::string> graph(
		{
			{"B","C"},{"A","B"},{"C","A"},{"B","D"} ,
			{"D","E"},{"E","F"},{"F","D"},{"G","F"},
			{"G","H"},{"H","I"},{"I","J"},{"J","G"},
			{"J","K"},
		}
	);
	graph.StronglyConnectedComponents();

	std::cin.get();
	return 0;
}