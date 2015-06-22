#include <fstream>
#include "../../includes/formula.h"
#include <iostream>
#include <string>

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
		inputFile >> literals;
		inputFile >> clauses;

		f = new Formula(clauses, literals);

		for (int i = 0; i < clauses; ++i)
		{
			int l1;
			int l2;
			int l3;

			inputFile >> l1;
			inputFile >> l2;
			inputFile >> l3;

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