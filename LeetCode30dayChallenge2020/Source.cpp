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
#include "Problems.h"
//#include "30DC_Apr2020.h"
//#include "30DC_May2020.h"
//#include "30DC_Jun2020.h"
#include "30DC_Jul2020.h"
//#include "GraphClass.h" 
//#include "FTTI.h"
//#include "FTI.h" 
#include <iomanip>
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
//	allocated -= count;
//	std::cout << " Total allocated: " << allocated << "bytes\n";
//	std::free(ptr);
//}
//void TestTriangleIntersections()
//{
//	std::random_device rd;
//	std::mt19937 rng = std::mt19937(rd());
//	std::uniform_real_distribution<float> fDistr = std::uniform_real_distribution<float>(-1.0f, 1.0f);
//	size_t N = 10;
//	struct Triangle1
//	{
//		FTTI::coord p1, p2, p3;
//	};
//	struct Triangle2
//	{
//		Vec3 p1, p2, p3;
//	};
//	std::vector<std::pair<Triangle1, Triangle1>> testData1;
//	std::vector<std::pair<Triangle2, Triangle2>> testData2;
//	for (size_t i = 0; i < N; ++i)
//	{
//		testData1.push_back({ { {fDistr(rng),fDistr(rng),fDistr(rng)},{fDistr(rng),fDistr(rng),fDistr(rng)},{fDistr(rng),fDistr(rng),fDistr(rng)} },
//								{{fDistr(rng),fDistr(rng),fDistr(rng)},{fDistr(rng),fDistr(rng),fDistr(rng)},{fDistr(rng),fDistr(rng),fDistr(rng)} } });
//		testData2.push_back({ { {testData1[i].first.p1.x,testData1[i].first.p1.y,testData1[i].first.p1.z},
//								{testData1[i].first.p2.x,testData1[i].first.p2.y,testData1[i].first.p2.z},
//								{testData1[i].first.p3.x,testData1[i].first.p3.y,testData1[i].first.p3.z} },
//							  { {testData1[i].second.p1.x,testData1[i].second.p1.y,testData1[i].second.p1.z},
//								{testData1[i].second.p2.x,testData1[i].second.p2.y,testData1[i].second.p2.z},
//								{testData1[i].second.p3.x,testData1[i].second.p3.y,testData1[i].second.p3.z} } 
//			});
//	}
//
//	// TEST FTTI
//	std::cout << "=== TEST FTTI ================================================\n";
//	for (size_t i = 0; i < N; ++i)
//	{
//		auto p = FTTI::check_type_of_intersection(testData1[i].first.p1, testData1[i].first.p2, testData1[i].first.p3, testData1[i].second.p1, testData1[i].second.p2, testData1[i].second.p3);
//		std::cout.precision(2);
//		std::cout << std::setw(4)<<"i=" << i << ", " << "T1: [" << testData1[i].first.p1.x << "," << testData1[i].first.p1.y << "," << testData1[i].first.p1.z << "],";
//		std::cout << "[" << testData1[i].first.p2.x << "," << testData1[i].first.p2.y << "," << testData1[i].first.p2.z << "],";
//		std::cout << "[" << testData1[i].first.p3.x << "," << testData1[i].first.p3.y << "," << testData1[i].first.p3.z << "]:\n";
//
//		std::cout << "     ["<<p.first.x << "," << p.first.y << "," << p.first.z << "]; ";
//		std::cout << "[" << p.second.x << "," << p.second.y << "," << p.second.z << "];\n ";
//	}
//	std::cout << "=== END TEST ================================================\n\n\n";
//
//	// TEST FTI
//	std::cout << "=== TEST FTI ================================================\n";
//	for (size_t i = 0; i < N; ++i)
//	{
//		auto p = FTI::TrianglesIntersect_(testData2[i].first.p1, testData2[i].first.p2, testData2[i].first.p3, testData2[i].second.p1, testData2[i].second.p2, testData2[i].second.p3);
//		std::cout.precision(2);
//		std::cout << std::setw(4) << "i=" << i << ", " << "T1: [" << testData2[i].first.p1.x << "," << testData2[i].first.p1.y << "," << testData2[i].first.p1.z << "],";
//		std::cout <<"[" << testData2[i].first.p2.x << "," << testData2[i].first.p2.y << "," << testData2[i].first.p2.z << "],";
//		std::cout << "[" << testData2[i].first.p3.x << "," << testData2[i].first.p3.y << "," << testData2[i].first.p3.z << "]:\n";
//
//		std::cout << "     [" << p.first.x << "," << p.first.y << "," << p.first.z << "]; ";
//		std::cout << "[" << p.second.x << "," << p.second.y << "," << p.second.z << "];\n ";
//	}
//	std::cout << "=== END TEST ================================================\n\n\n";
//	std::cin.get();
//}


int main()
{

	Jul_day28::RunExample();
	//Knapsack::RunExample();
	//Karatsuba::RunExample();
	//LC85::RunExample();
	//LC1462::RunExample();

	//TestTriangleIntersections();
	//auto p1 = FTTI::check_type_of_intersection({ 0,0,2 }, { 0, 2, 2 }, { 2, 1, 0 }, { 2,0,2 }, { 2,2,2 }, { 0,1,0 });
	//auto p2 = FTI::TrianglesIntersect_({ 0,0,2 }, { 0, 2, 2 }, { 2, 1, 0 }, { 2,0,2 }, { 2,2,2 }, { 0,1,0 });
	std::cin.get();
	return 0;
}