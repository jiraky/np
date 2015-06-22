#include <fstream>
#include "../../includes/formula.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

string absolutePath = "D:\\Development\\NP\\3SAT-Verifier\\3SAT-Verifier\\resources\\";
string istance = absolutePath + "instances\\instance_01.txt";
string certificate = absolutePath + "certificates\\certificate_01.txt";
ofstream outputFile(absolutePath + "output\\output_01.txt");

int literals;
int clauses;

Formula * f;

int main()
{
	ifstream inputFile(istance);

	if (inputFile.is_open())
	{
		string line;
		while (getline(inputFile, line))
		{
			// comment lines, only at top looks like
			if (line[0] == 'c') continue;

			// start of file heading breaks the loop.
			if (line[0] == 'p') break;

			// Garbage found.
			return -1;
		}

		stringstream headParser(line);
		string type;

		// Skip the p we checked it already.
		headParser >> type;
		headParser >> type;

		if (type != "cnf")
		{
			// Not handled format
			return -1;
		}

		headParser >> literals;
		headParser >> clauses;

		// For the rest just read directly the file.
		f = new Formula(clauses, literals);

		for (int i = 0; i < clauses; ++i)
		{
			int l1;
			int l2;
			int l3;
			int endingEntry;

			inputFile >> l1;
			inputFile >> l2;
			inputFile >> l3;
			inputFile >> endingEntry;

			if (endingEntry != 0)
			{
				// Invalid file.
				return -1;
			}

			f->addClause(abs(l1)-1, abs(l2)-1, abs(l3)-1, l1 > 0, l2 > 0, l3 > 0);
		}
	}

	ifstream certFile(certificate);

	if (certFile.is_open())
	{
		for (int i = 0; i < literals; ++i)
		{
			bool value;
			certFile >> value;
			f->SetAssignment(i, value);
		}
	}

	bool issat = f->IsSatisfied();

	outputFile << issat;
	return !issat;
}