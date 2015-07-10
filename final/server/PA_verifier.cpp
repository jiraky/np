#include <fstream>
#include "../../includes/formula.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

static int literals;
static int clauses;

static Formula * f;

bool PA_Verifier(std::istream &instance, std::istream &certificate);

// FIXME: add a -DPA_Verifier_Server to make it invalid during compilation for user submitted sources.
bool PA_Verifier_Server(std::istream &instance, std::istream &certificate)
{
	return PA_Verifier(instance, certificate);
}

bool PA_Verifier(std::istream &instance, std::istream &certificate)
{
		string line;
		while (getline(instance, line))
		{
			// comment lines, only at top looks like
			if (line[0] == 'c') continue;

			// start of file heading breaks the loop.
			if (line[0] == 'p') break;

			// Garbage found.
			return false;
		}

		stringstream headParser(line);
		string type;

		// Skip the p we checked it already.
		headParser >> type;
		headParser >> type;

		if (type != "cnf")
		{
			// Not handled format
			return false;
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

			instance >> l1;
			instance >> l2;
			instance >> l3;
			instance >> endingEntry;

			if (endingEntry != 0)
			{
				// Invalid file.
				return -1;
			}

			f->addClause(abs(l1)-1, abs(l2)-1, abs(l3)-1, l1 > 0, l2 > 0, l3 > 0);
		}

		for (int i = 0; i < literals; ++i)
		{
			bool value;
			certificate >> value;
			f->SetAssignment(i, value);
		}

	bool issat = f->IsSatisfied();
	return issat;
}