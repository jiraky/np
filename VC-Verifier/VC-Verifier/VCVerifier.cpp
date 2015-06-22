#include <fstream>
#include <string>
#include "../../includes/graph.h"
using namespace std;

string absolutePath = "D:\\Development\\NP\\VC-Verifier\\VC-Verifier\\resources\\";
string istance = absolutePath + "instances\\instance_01.txt";
string certificate = absolutePath + "certificates\\certificate_01.txt";
ofstream outputFile(absolutePath + "output\\output_01.txt");


int nodes;
int edges;

Graph * g;

int main()
{
	ifstream inputFile(istance);

	if (inputFile.is_open())
	{
		inputFile >> nodes;
		inputFile >> edges;

		g = new Graph(nodes);

		for (int i = 0; i < edges; ++i)
		{
			int origin;
			int destination;
			inputFile >> origin;
			inputFile >> destination;

			g->AddEdge(origin, destination);
		}
	}

	ifstream certFile(certificate);

	vector<bool> cert_vc;
	cert_vc.assign(nodes, false);

	if (certFile.is_open())
	{
		int cert_vc_size;
		certFile >> cert_vc_size;

		for (int i = 0; i < cert_vc_size; ++i)
		{
			int node;
			certFile >> node;
			cert_vc[node] = true;
		}
	}

	bool isVC = g->isVC(cert_vc);

	outputFile << isVC;
	return !isVC;
}