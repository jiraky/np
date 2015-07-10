#ifndef CLAUSE_H 
#define CLAUSE_H

#include <vector>
#include <string>

using namespace std;
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

#endif
