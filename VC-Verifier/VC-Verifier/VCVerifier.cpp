#include <fstream>
#include <string>
#include "../../includes/graph.h"
using namespace std;

static int nodes;
static int edges;
static int k;

static Graph * g;

bool PB_Verifier(std::istream &instance, std::istream &certificate);

#ifndef INCLUDED_SRC
int main()
{
	string absolutePath = "C:\\Users\\stefano\\Documents\\nigoro\\np\\VC-Verifier\\VC-Verifier\\resources\\";
	string istance = absolutePath + "instances\\instance_01.txt";
	string certificateFile = absolutePath + "certificates\\certificate_01.txt";
	ifstream instance(istance);
	ifstream certificate(certificateFile);

	bool result = PB_Verifier(instance, certificate);
}
#endif

// FIXME: add a -DPA_Verifier_Server to make it invalid during compilation for user submitted sources.
bool PB_Verifier_Server(std::istream &instance, std::istream &certificate)
{
	return PB_Verifier(instance, certificate);
}

bool PB_Verifier(std::istream &instance, std::istream &certificate)
{
	instance >> nodes;
	instance >> edges;
	instance >> k;

	g = new Graph(nodes);

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

	return isVC && g->vcCounter <= k;
}