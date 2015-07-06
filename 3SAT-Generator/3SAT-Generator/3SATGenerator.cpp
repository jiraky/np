#include <fstream>
#include <string>
#include <sstream>
#include "../../includes/graph.h"
#include <iostream>
#include <queue>
#include <list>
#include <unordered_map>

using namespace std;



int PA_Generate(std::ostream &instance, std::ostream &certificate, std::unordered_map<std::string, std::string> options)
{
	if (options["type"] == "hanoi")
	{
		return 0;
	}
}


#ifndef INCLUDED_SRC
int main()
{
	string absolutePath = "D:\\Development\\NP\\3SAT-Generator\\3SAT-Generator\\resources\\";
	string instanceFile = absolutePath + "instances\\instance_01.txt";
	string certificateFile = absolutePath + "certificates\\certificate_01.txt";
	ofstream instance(instanceFile);
	ofstream certificate(certificateFile);
	std::unordered_map<std::string, std::string> options({ { "type", "bench" }, { "num_nodes", "11" } });
	PA_Generate(instance, certificate, options);
}
#endif