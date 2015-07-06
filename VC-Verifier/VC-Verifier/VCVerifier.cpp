#include <fstream>
#include <string>
#include "../../includes/graph.h"
using namespace std;

int nodes;
int edges;

Graph * g;

bool PA_Verifier(std::istream &instance, std::istream &certificate);

#ifndef INCLUDED_SRC
int main()
{
	string absolutePath = "C:\\Users\\stefano\\Documents\\nigoro\\np\\VC-Verifier\\VC-Verifier\\resources\\";
	string istance = absolutePath + "instances\\instance_01.txt";
	string certificateFile = absolutePath + "certificates\\certificate_01.txt";
	ifstream instance(istance);
	ifstream certificate(certificateFile);

	bool result = PA_Verifier(instance, certificate);
}
#endif
bool PA_Verifier(std::istream &instance, std::istream &certificate)
{
	instance >> nodes;
	instance >> edges;

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

	return isVC;
}