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
//#include "30DC_Apr2020.h"
//#include "30DC_May2020.h"
#include "30DC_Jun2020.h"
#include "Problems.h"
//#include "GraphClass.h" 

size_t allocated=0;

//void* operator new(size_t size)
//{
//	std::cout << "Allocating " << size << "bytes\n";
//	allocated += size;
//	std::cout << " Total allocated: " << allocated << "bytes\n";
//	return std::malloc(size);
//}
//void operator delete(void* ptr, size_t size)
//{
//	std::cout << "Freeing " << size << "bytes\n";
//	allocated -= size;
//	std::cout << " Total allocated: " << allocated << "bytes\n";
//	free(ptr);
//}
//
//void operator delete[](void* ptr)//, size_t size)
//{
//	int count = 1;
//	//const char* p = static_cast<const char*>(ptr);
//	const char* p = reinterpret_cast<const char*>(ptr);
//	for (; *p != 0; p++)
//	{
//		count++;
//	}
//	std::cout << "Freeing " << count << " bytes\n";
//	allocated += count;
//	std::cout << " Total allocated: " << count << "bytes\n";
//	std::free(ptr);
//}

int main()
{
	Jun_day21::RunExample();
	//Knapsack::RunExample();
	//Karatsuba::RunExample();
	//LC85::RunExample();
	//TriangleIntersect::RunExample();
	std::cin.get();
	return 0;
}