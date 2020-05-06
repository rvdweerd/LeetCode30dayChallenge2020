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
public:  // to be made private later
	struct Edge;
	struct Node
	{
		Node(T name)
			:
			name(name)
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
	std::unordered_map<T, Node*> nodemap;
	std::set<Edge*> edgelist;
private:
	bool hasRoot = false;
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
	void AddNode(T name)
	{
		nodemap[name] = new Node(name);
	}
	void AddEdge(T n1, T n2, int cost)
	{
		if (nodemap.find(n1) == nodemap.end())
		{
			nodemap.insert({n1,new Node(n1)});
		}
		if (nodemap.find(n2) == nodemap.end())
		{
			nodemap.insert({ n2,new Node(n2) });
		}
		Node* node1 = nodemap[n1];
		Node* node2 = nodemap[n2];
		Edge* e = new Edge(node1, node2, cost);
		node1->edges_out.insert(e);
		node2->edges_in.insert(e);
		edgelist.insert(e);
	}
	bool HasRoot() const
	{
		return hasRoot;
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
	std::vector<std::vector<Node*>> StronglyConnectedComponents() // Kosaraju's algorithm
	{
		std::set<Node*> visited;
		std::stack<Node*> finishTimeStack;
		for (auto p : nodemap) // for all pairs {nodename, Node*}
		{
			if (visited.find(p.second) == visited.end()) // if not visited yet
			{
				visited.insert(p.second);
				KStep(p.second, visited, finishTimeStack);
			}
		}
		
		Inverse();
		std::vector<std::vector<Node*>> componentVector;
		std::vector<Node*> component;
		visited.clear();
		while (!finishTimeStack.empty())
		{
			Node* n = finishTimeStack.top(); finishTimeStack.pop();
			if (visited.find(n) == visited.end())
			{
				if (n->edges_out.size() == 0)
				{
					visited.insert(n);
					component.push_back(n);
					componentVector.push_back(component);
					component.clear();
				}
				else
				{
					std::stack<Node*> DFS_stack;
					DFS_stack.push(n);
					while (!DFS_stack.empty())
					{
						Node* current = DFS_stack.top(); DFS_stack.pop();
						visited.insert(current);
						component.push_back(current);
						for (Edge* e : current->edges_out)
						{
							if (visited.find(e->end) == visited.end())
							{
								DFS_stack.push(e->end);
							}
						}
					}
					componentVector.push_back(component);
					component.clear();
				}
			}
		}
		Inverse();
		return componentVector;
	}
	std::set<Node*> GetCircularNodes()
	{
		std::vector<std::vector<Node*>> componentVec = StronglyConnectedComponents();
		std::set<Node*> set;
		for (std::vector<Node*> v : componentVec)
		{
			if (v.size() > 1)
			{
				for (Node* n : v)
				{
					set.insert(n);
				}
			}
		}
		return set;
	}
	void KStep(Node* n, std::set<Node*>& visited, std::stack<Node*>& finishTimeStack)
	{
		if (n->edges_out.size() != 0)
		{
			for (Edge* e : n->edges_out)
			{
				if (visited.find(e->end) == visited.end())
				{
					visited.insert(e->end);
					KStep(e->end, visited, finishTimeStack);
				}
			}
			finishTimeStack.push(n);
		}
		else
		{
			finishTimeStack.push(n);
		}
	}
public:  // to be made private later
	void Inverse()
	{
		for (Edge* e : edgelist)
		{
			std::swap(e->start, e->end);
		}
		for (auto p : nodemap)
		{
			std::swap(p.second->edges_out, p.second->edges_in);
		}
		CheckRoot();
	}
	Graph GetInverse() const
	{
		Graph g;
		for (auto e : edgelist)
		{	
			g.AddEdge(e->end->name,e->start->name,e->cost);
		}
		return g;
	}
	void CheckRoot()
	{
		hasRoot = false;
		for (auto p : nodemap)
		{
			if (p.second->InDegree() == 0)
			{
				hasRoot = true;
				break;
			}
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
