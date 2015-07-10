#include <fstream>
#include <string>
#include <sstream>
#include <atomic>
#include <vector>

using namespace std;

static int literals;
static int clauses;

class Node
{
public:
	vector<uint32_t> neighbours;
};

class Graph
{
public:
	vector<Node> nodes;

	int edges_size = 0;

	vector<bool> alive;
	vector<bool> vc;
	uint32_t vcCounter = 0;

	string VCtoString() {
		string result;
		for (int n = 0; n < vc.size(); ++n) {
			if (vc[n])
				result += to_string(n) + " ";
		}
		return result;
	}

	string ToString() {
		string result;// = to_string(nodes.size()) + " " + to_string(edges_size) + "\n";

		vector<bool> printed;
		printed.resize(nodes.size());
		printed.assign(nodes.size(), false);

		for (int n = 0; n < nodes.size(); n++) {
			printed[n] = true;
			for (int ne = 0; ne < nodes[n].neighbours.size(); ++ne) {
				if (!printed[nodes[n].neighbours[ne]]) {
					result += to_string(n) + " " + to_string(nodes[n].neighbours[ne]) + "\n";
				}
			}
		}
		return result;
	}

	Graph(uint32_t nodeNumber)
	{
		nodes.assign(nodeNumber, Node());
		alive.assign(nodeNumber, true);
		vc.assign(nodeNumber, false);
	}

	void AddEdge(uint32_t source, uint32_t destination)
	{
		nodes[source].neighbours.push_back(destination);
		nodes[destination].neighbours.push_back(source);
		edges_size++;
	}

	void RemoveEdge(uint32_t source, uint32_t destination)
	{
		for (size_t i = 0; i < nodes[source].neighbours.size(); ++i)
		{
			if (nodes[source].neighbours[i] == destination)
			{
				nodes[source].neighbours[i] = nodes[source].neighbours.back();
				nodes[source].neighbours.resize(nodes[source].neighbours.size() - 1);
				return;
			}
		}
		edges_size--;
	}

	bool HasEdge(uint32_t source, uint32_t destination)
	{
		for (uint32_t i = 0; i < nodes[source].neighbours.size(); ++i)
		{
			if (nodes[source].neighbours[i] == destination)
			{
				return true;
			}
		}

		return false;
	}

	void RemoveVertex(uint32_t vertex)
	{
		alive[vertex] = false;
		for (size_t i = 0; i < nodes[vertex].neighbours.size(); ++i)
		{
			RemoveEdge(nodes[vertex].neighbours[i], vertex);
		}

		// not really needed.
		nodes[vertex].neighbours.clear();
	}

	uint32_t APX()
	{
		Graph newChart = *this;
		while (true)
		{
			uint32_t v1 = (uint32_t)-1;
			for (int i = 0; i < newChart.nodes.size(); ++i)
			{
				if (newChart.alive[i])
				{
					v1 = i;
					break;
				}
			}

			if (v1 == (uint32_t)-1) {
				return newChart.vcCounter;
			}

			// Vertex with no edges left.
			if (newChart.nodes[v1].neighbours.size() == 0)
			{
				newChart.RemoveVertex(v1);
				continue;
			}
			uint32_t v2 = newChart.nodes[v1].neighbours[rand() % newChart.nodes[v1].neighbours.size()];
			newChart.AddToVC(v1);
			newChart.AddToVC(v2);
		}
	}

	void AddToVC(uint32_t node_index) {
		if (vc[node_index])
			return;
		vc[node_index] = true;
		RemoveVertex(node_index);
		++vcCounter;
	}

	void ExcludeFromVC(uint32_t node_index) {
		vector<uint32_t> toBeAdd;
		toBeAdd.reserve(nodes[node_index].neighbours.size());
		for (uint32_t kk = 0; kk < nodes[node_index].neighbours.size(); ++kk)
		{
			toBeAdd.push_back(nodes[node_index].neighbours[kk]);
		}
		for (uint32_t kk = 0; kk < toBeAdd.size(); ++kk)
		{
			AddToVC(toBeAdd[kk]);
		}
		vc[node_index] = false;
		RemoveVertex(node_index);
	}

	bool isVC(vector<bool> &localVC) {
		for (int node = 0; node < this->nodes.size(); ++node)
			if (localVC[node] == 0)
				for (int nei = 0; nei < this->nodes[node].neighbours.size(); nei++)
					if (localVC[this->nodes[node].neighbours[nei]] == 0)
						return false;
		return true;
	}

};

class Clause
{
public:
	int l1_pos;
	int l2_pos;
	int l3_pos;

	bool l1_state;
	bool l2_state;
	bool l3_state;

	Clause(int l1_pos, int l2_pos, int l3_pos, bool l1_state, bool l2_state, bool l3_state)
	{
		this->l1_pos = l1_pos;
		this->l2_pos = l2_pos;
		this->l3_pos = l3_pos;

		this->l1_state = l1_state;
		this->l2_state = l2_state;
		this->l3_state = l3_state;
	}

	bool IsSatisfiable(vector<bool> &assignment)
	{
		return assignment[l1_pos] == this->l1_state || assignment[l2_pos] == this->l2_state || assignment[l3_pos] == this->l3_state;
	}

	string ToString()
	{
		string l1 = l1_state ? "" + to_string(l1_pos) : "!" + to_string(l1_pos);
		string l2 = l2_state ? "" + to_string(l2_pos) : "!" + to_string(l2_pos);
		string l3 = l3_state ? "" + to_string(l3_pos) : "!" + to_string(l3_pos);
		return "(" + l1 + " OR " + l2 + " OR " + l3 + ")";
	}

	string AssignmentToString(vector<bool> &assignment)
	{
		string l1 = assignment[l1_pos] ? "T" : "F";
		string l2 = assignment[l2_pos] ? "T" : "F";
		string l3 = assignment[l3_pos] ? "T" : "F";
		return "(" + l1 + " OR " + l2 + " OR " + l3 + ")";
	}
};

class Formula
{
public:
	vector<Clause> clauses;
	vector<bool> assignment;

	Formula(int clauses_size, int literals_size)
	{
		this->clauses.reserve(clauses_size);
		this->assignment.assign(literals_size, false);
	}

	bool IsSatisfied()
	{
		for (int i = 0; i < clauses.size(); ++i)
		{
			if (!clauses[i].IsSatisfiable(assignment))
			{
				return false;
			}
		}
		return true;
	}

	void addClause(int l1_pos, int l2_pos, int l3_pos, bool l1_state, bool l2_state, bool l3_state)
	{
		clauses.push_back(Clause(l1_pos, l2_pos, l3_pos, l1_state, l2_state, l3_state));
	}

	void SetAssignment(int l_pos, bool l_value)
	{
		this->assignment[l_pos] = l_value;
	}

	string ToString()
	{
		string result = "";
		result += clauses[0].ToString();
		for (int i = 1; i < clauses.size(); ++i)
		{
			result += " AND " + clauses[i].ToString();
		}
		return result;
	}

	string AssignmentToString()
	{
		string result = "";
		result += clauses[0].AssignmentToString(assignment);
		for (int i = 1; i < clauses.size(); ++i)
		{
			result += " AND " + clauses[i].AssignmentToString(assignment);
		}
		return result;
	}
};

static Formula * f;
static Graph *g;

void ReductionEasy_FromPA_ToPB(std::istream &PA_Instance, std::istream &PA_Certificate, std::ostream &PB_Output_Instance, std::ostream &PB_Output_Certificate)
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

	for (int i = 0; i < literals; ++i)
	{
		bool value;
		PA_Certificate >> value;
		f->SetAssignment(i, value);
	}

	PB_Output_Instance << g->nodes.size() << " " << g->edges_size << " " << (literals + 2 * clauses) << endl;
	PB_Output_Instance << g->ToString();

	// Create certificate.
	for (int i = 0; i < clauses; ++i)
	{
		Clause tmp = f->clauses[i];
		if (f->assignment[tmp.l1_pos] == tmp.l1_state)
		{
			g->ExcludeFromVC(startL1 + i);
		}
		else if (f->assignment[tmp.l2_pos] == tmp.l2_state)
		{
			g->ExcludeFromVC(startL2 + i);
		}
		else if (f->assignment[tmp.l3_pos] == tmp.l3_state)
		{
			g->ExcludeFromVC(startL3 + i);
		}
		/*else
		{
			break;
		}*/
	}

	for (int i = startPos; i < startNeg; ++i)
	{
		if (!g->vc[i])
		{
			g->AddToVC(startNeg + i);
		}
	}


	PB_Output_Certificate << g->vcCounter << " " << g->VCtoString();
}