#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <cinttypes>
#include "node.h"

using namespace std;
class Graph
{
public:
	vector<Node> nodes;

	int edges_size = 0;

	vector<bool> alive;
	vector<bool> vc;
	uint32_t vcCounter = 0;

	string VCtoString() {
		string result;
		for (int n = 0; n < vc.size(); ++n) {
			if (vc[n])
				result += to_string(n) + " ";
		}
		return result;
	}

	string ToString() {
		string result;// = to_string(nodes.size()) + " " + to_string(edges_size) + "\n";

		vector<bool> printed;
		printed.resize(nodes.size());
		printed.assign(nodes.size(), false);

		for (int n = 0; n<nodes.size(); n++) {
			printed[n] = true;
			for (int ne = 0; ne < nodes[n].neighbours.size(); ++ne) {
				if (!printed[nodes[n].neighbours[ne]]) {
					result += to_string(n) + " " + to_string(nodes[n].neighbours[ne]) + "\n";
				}
			}
		}
		return result;
	}

	Graph(uint32_t nodeNumber)
	{
		nodes.assign(nodeNumber, Node());
		alive.assign(nodeNumber, true);
		vc.assign(nodeNumber, false);
	}

	void AddEdge(uint32_t source, uint32_t destination)
	{
		nodes[source].neighbours.push_back(destination);
		nodes[destination].neighbours.push_back(source);
		edges_size++;
	}

	void RemoveEdge(uint32_t source, uint32_t destination)
	{
		for (size_t i = 0; i < nodes[source].neighbours.size(); ++i)
		{
			if (nodes[source].neighbours[i] == destination)
			{
				nodes[source].neighbours[i] = nodes[source].neighbours.back();
				nodes[source].neighbours.resize(nodes[source].neighbours.size() - 1);
				return;
			}
		}
		edges_size--;
	}

	bool HasEdge(uint32_t source, uint32_t destination)
	{
		for (uint32_t i = 0; i < nodes[source].neighbours.size(); ++i)
		{
			if (nodes[source].neighbours[i] == destination)
			{
				return true;
			}
		}

		return false;
	}

	void RemoveVertex(uint32_t vertex)
	{
		alive[vertex] = false;
		for (size_t i = 0; i < nodes[vertex].neighbours.size(); ++i)
		{
			RemoveEdge(nodes[vertex].neighbours[i], vertex);
		}

		// not really needed.
		nodes[vertex].neighbours.clear();
	}

	uint32_t APX()
	{
		Graph newChart = *this;
		while (true)
		{
			uint32_t v1 = (uint32_t)-1;
			for (int i = 0; i < newChart.nodes.size(); ++i)
			{
				if (newChart.alive[i])
				{
					v1 = i;
					break;
				}
			}

			if (v1 == (uint32_t)-1) {
				return newChart.vcCounter;
			}

			// Vertex with no edges left.
			if (newChart.nodes[v1].neighbours.size() == 0)
			{
				newChart.RemoveVertex(v1);
				continue;
			}
			uint32_t v2 = newChart.nodes[v1].neighbours[rand() % newChart.nodes[v1].neighbours.size()];
			newChart.AddToVC(v1);
			newChart.AddToVC(v2);
		}
	}

	void AddToVC(uint32_t node_index) {
		if (vc[node_index])
			return;
		vc[node_index] = true;
		RemoveVertex(node_index);
		++vcCounter;
	}

	void ExcludeFromVC(uint32_t node_index) {
		vector<uint32_t> toBeAdd;
		toBeAdd.reserve(nodes[node_index].neighbours.size());
		for (uint32_t kk = 0; kk < nodes[node_index].neighbours.size(); ++kk)
		{
			toBeAdd.push_back(nodes[node_index].neighbours[kk]);
		}
		for (uint32_t kk = 0; kk < toBeAdd.size(); ++kk)
		{
			AddToVC(toBeAdd[kk]);
		}
		vc[node_index] = false;
		RemoveVertex(node_index);
	}

	bool isVC(vector<bool> &localVC) {
		for (int node = 0; node < this->nodes.size(); ++node)
			if (localVC[node] == 0)
				for (int nei = 0; nei < this->nodes[node].neighbours.size(); nei++)
					if (localVC[this->nodes[node].neighbours[nei]] == 0)
						return false;
		return true;
	}

};


#endif
