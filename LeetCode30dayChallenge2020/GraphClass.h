#pragma once
#include <string>
#include <set>
#include <map>
#include <vector>
#include <iostream>
#include <cassert>
#include <queue>

template <typename T>
class Graph
{
public:
	struct Edge;
	struct Node
	{
		Node(T n)
			:
			name(n)
		{}
		bool PointsTo(Node* target)
		{
			for (auto e : edges_out)
			{
				if (e->end == target) return true;
			}
			return false;
		}
		int InDegree()
		{
			return edges_in.size();
		}
		int OutDegree()
		{
			return edges_out.size();
		}
		T name;
		std::set<Edge*> edges_out;
		std::set<Edge*> edges_in;
	};
	struct Edge
	{
		Edge(Node* s, Node* e, int c)
			:
			start(s),
			end(e),
			cost(c)
		{}
		Node* start;
		Node* end;
		int cost;
	};
	std::map<T, Node*> nodemap;
	std::set<Edge*> edgelist;
	bool hasRoot = false;
private:
	void CheckRoot()
	{
		for (auto p : nodemap)
		{
			if (p.second->InDegree() == 0)
			{
				hasRoot = true;
				break;
			}
		}
	}
public:
	Graph() = default;
	Graph(std::vector<std::vector<T>> edges)
	{
		for (std::vector<T> e : edges)
		{
			if (nodemap.find(e[0]) == nodemap.end()) nodemap[e[0]] = new Node(e[0]);
			if (nodemap.find(e[1]) == nodemap.end()) nodemap[e[1]] = new Node(e[1]);
			AddEdge(e[0], e[1], 1);
		}
		CheckRoot();
	}
	bool HasRoot() const
	{
		return hasRoot;
	}
	void AddNode(T name)
	{
		nodemap[name] = new Node(name);
	}
	void AddEdge(T n1, T n2, int cost)
	{
		assert(nodemap.find(n1) != nodemap.end() && nodemap.find(n2) != nodemap.end());
		if (nodemap.find(n1) == nodemap.end() || nodemap.find(n2) == nodemap.end()) return;
		Node* node1 = nodemap[n1];
		Node* node2 = nodemap[n2];
		Edge* e = new Edge(node1, node2, cost);
		node1->edges_out.insert(e);
		node2->edges_in.insert(e);
		edgelist.insert(e);
	}
	std::vector<Node*> GetAllNodes() const
	{
		std::vector<Node*> vec;
		for (auto p : nodemap)
		{
			vec.push_back(p.second);
		}
		return vec;
	}
	void PrintAdjacencyMap() const
	{
		for (auto p : nodemap)
		{
			std::cout << p.first << ", Name: " << p.second->name << ", Connected to: ";
			for (auto e : p.second->edges_out)
			{
				std::cout << e->end->name << "[" << e->cost << "], ";
			}
			std::cout << std::endl;
		}
	}
	bool IsCircularNode(T node)
	{
		return IsCircularNode(nodemap[node]);
	}
	bool IsCircularNode(Node* node) const
	{
		std::queue<Node*> queue;
		std::set<Node*> visited;
		queue.push(node);
		while (!queue.empty())
		{
			Node* current = queue.front(); queue.pop();
			if (visited.find(current) != visited.end() && current == node) return true;
			visited.insert(current);
			for (auto e : current->edges_out)
			{
				if (e->end == node || visited.find(e->end) == visited.end()) // only  add if not visited earlier (node under investigation gets readded)
				//if (visited.find(e->end) == visited.end()) // only  add if not visited earlier 
				{
					queue.push(e->end);
				}
			}
		}
		return false;
	}
	void WrapCircularNodeInto(Node* source, Node* target)
	{
		if (target == nullptr) return;
		std::set<Edge*> toBeDeleted;
		for (auto e : source->edges_out) // rebase all edges originating from source to originating from target
		{
			if (e->end == target) // this edge points to target
			{
				toBeDeleted.insert(e);
				//delete edge from source (or do nothing and delete outside loop)
				// update edgelist
			}
			else if (target->PointsTo(e->end)) // target already has this destination
			{
				toBeDeleted.insert(e);
				// delete edge from source
				// update edgelist
			}
			else
			{
				e->start = target;
				target->edges_out.insert(e);
				//source->edges.erase(e);
				// move edge to target
				// update edgelist
			}
		}
		for (auto e : source->edges_in) // redirect all edges pointing to source towards target
		{
			if (e->start == target) //if e comes from target
			{
				toBeDeleted.insert(e);
				// delete edge (from target and nodelist)
				// update edgelist
			}
			else if (e->start->PointsTo(target)) //  target already has this incoming
			{
				toBeDeleted.insert(e);
				//  delete edge from incoming
				// update edgelist
			}
			else
			{
				e->end = target;
				target->edges_in.insert(e);
				//source->incoming.erase(e);
				// move incoming to point to target
				// update edgelist
			}
		}
		// process delete queue
		for (auto e : toBeDeleted)
		{
			e->start->edges_out.erase(e);
			e->end->edges_in.erase(e);
			edgelist.erase(e);
			delete e; e = nullptr;
		}

		// delete source node
		nodemap.erase(source->name);
		delete source; source = nullptr;
	}
};
