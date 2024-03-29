#include <fstream>
#include <string>
#include <sstream>
#include "../includes/graph.h"
#include <iostream>
#include <queue>
#include <list>
#include <unordered_map>
#include "../includes/formula.h"

static int literals;
static int clauses;

static Formula * f;
static Graph *g;

void ReductionHard_FromPA_ToPB(std::istream &PA_Instance, std::istream &PB_Certificate, std::ostream &PA_Output_Certificate)
{
	string line;
	while (getline(PA_Instance, line))
	{
		// comment lines, only at top looks like
		if (line[0] == 'c') continue;

		// start of file heading breaks the loop.
		if (line[0] == 'p') break;

		// Garbage found.
		return;
	}

	stringstream headParser(line);
	string type;

	// Skip the p we checked it already.
	headParser >> type;
	headParser >> type;

	if (type != "cnf")
	{
		// Not handled format
		return;
	}

	headParser >> literals;
	headParser >> clauses;

	// For the rest just read directly the file.
	f = new Formula(clauses, literals);
	g = new Graph(2 * literals + 3 * clauses);

	int startPos = 0;
	int startNeg = literals;
	int startL1 = startNeg + literals;
	int startL2 = startL1 + clauses;
	int startL3 = startL2 + clauses;

	// variable gadget.
	for (int i = 0; i < literals; ++i)
	{
		g->AddEdge(startPos + i, startNeg + i);
	}

	for (int i = 0; i < clauses; ++i)
	{
		int l1;
		int l2;
		int l3;
		int endingEntry;

		PA_Instance >> l1;
		PA_Instance >> l2;
		PA_Instance >> l3;
		PA_Instance >> endingEntry;

		if (endingEntry != 0)
		{
			// Invalid file.
			return;
		}

		f->addClause(abs(l1) - 1, abs(l2) - 1, abs(l3) - 1, l1 > 0, l2 > 0, l3 > 0);

		// Clause Gadget.
		g->AddEdge(startL1 + i, startL2 + i); g->AddEdge(startL2 + i, startL3 + i); g->AddEdge(startL3 + i, startL1 + i);

		// Connection to variable gadget.
		g->AddEdge(startL1 + i, l1 > 0 ? startPos + abs(l1) - 1 : startNeg + abs(l1) - 1);
		g->AddEdge(startL2 + i, l2 > 0 ? startPos + abs(l2) - 1 : startNeg + abs(l2) - 1);
		g->AddEdge(startL3 + i, l3 > 0 ? startPos + abs(l3) - 1 : startNeg + abs(l3) - 1);
	}


	// read certificate and convert.
	int vc_size;
	PB_Certificate >> vc_size;

	for (int i = 0; i < vc_size; ++i)
	{
		int node;
		PB_Certificate >> node;
		g->AddToVC(node);
	}

	for (int i = 0; i < literals; ++i)
	{
		// if it's vc of i it's true.
		PA_Output_Certificate << (g->vc[i] ? "1":"0");
	}	
}