#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

static int literals;
static int clauses;

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