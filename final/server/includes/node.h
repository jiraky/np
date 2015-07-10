#ifndef NODE_H 
#define NODE_H

#include <atomic>
#include <vector>

using namespace std;
namespace server_vc {
	class Node
	{
	public:
		vector<uint32_t> neighbours;
	};
};
#endif