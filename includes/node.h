#ifndef NODE_H 
#define NODE_H

#include <atomic>
#include <vector>

using namespace std;

class Node
{
public:
	vector<uint32_t> neighbours;
	string GetNeighAsString()
	{
		string result = "[";
		for (int i = 0; i < neighbours.size(); i++)
		{
			result += " " + neighbours[i];
		}
		return result+"]";
	}
};

#endif