#include <fstream>
#include <string>
#include <sstream>
#include "includes/graph.h"
#include <iostream>
#include <queue>
#include <list>
#include <unordered_map>

using namespace std;



int PA_Generate(std::ostream &instance, std::ostream &certificate, std::unordered_map<std::string, std::string> options)
{
	/*instance << "c test" << endl;
	instance << "p cnf 6 2" << endl;
	instance << "1 -2 3 0" << endl;
	instance << "-4 5 -6 0" << endl;
	certificate << "1 1 0 0 0 1" << endl;
	*/

	instance << "c test" << endl;
	instance << "p cnf 3 7" << endl;
	instance << "1 2 3 0" << endl;
	instance << "1 2 -3 0" << endl;
	instance << "1 -2 3 0" << endl;
	instance << "-1 2 3 0" << endl;
	instance << "1 -2 -3 0" << endl;
	instance << "-1 2 -3 0" << endl;
	instance << "-1 -2 3 0" << endl;
	//instance << "-1 -2 -3 0" << endl;

	certificate << "1 1 1" << endl;
	return 0;
}