#include <fstream>
#include <string>
#include "includes/graph.h"
using namespace std;

static int nodes;
static int edges;
static int k;

static server_vc::Graph * g;

bool PB_Verifier_Server(std::istream &instance, std::istream &certificate)
{
	instance >> nodes;
	instance >> edges;
	instance >> k;

	g = new server_vc::Graph(nodes);

	for (int i = 0; i < edges; ++i)
	{
		int origin;
		int destination;
		instance >> origin;
		instance >> destination;

		g->AddEdge(origin, destination);
	}

	vector<bool> cert_vc;
	cert_vc.assign(nodes, false);

	int cert_vc_size;
	certificate >> cert_vc_size;

	for (int i = 0; i < cert_vc_size; ++i)
	{
		int node;
		certificate >> node;
		cert_vc[node] = true;
	}

	bool isVC = g->isVC(cert_vc);

	return isVC && cert_vc_size <= k;
}