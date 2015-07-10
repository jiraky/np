#ifndef FORMULA_H 
#define FORMULA_H

#include <atomic>
#include <vector>
#include <string>
#include "clause.h"

using namespace std;

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

#endif
