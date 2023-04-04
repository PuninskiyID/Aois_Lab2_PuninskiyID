#include <iostream>
#include <vector>
#include <set>
#include <stack>

using namespace std;

class TruthTable 
{
	vector < vector <bool> > truthTable = {};
	class Variable 
	{
		char simbol;
		bool meaning;
	};
	set <Variable> plentyOfVariables;
	const string trueMeaning = "t";
	const string falseMeaning = "f";
	const string andMeaning = "+";
	const string orMeaning = "*";
	const string implication = "-";

	int MaxBreacketSearch(string logicalFunc);
	void CalcTruthTable(string logicalFunc);
	void Sum(stack <char> &StakOfVariables, stack <char> &StakOfOperations);
	void Mult(stack <char>& StakOfVariables, stack <char>& StakOfOperations);
	bool CheckPriority(stack <char> StakOfOperations, char newOperator);
	void CalcBracket(stack <char>& StakOfVariables, stack <char>& StakOfOperations);
	bool getBool(stack <char>& StakOfVariables);

public:
	TruthTable();
	TruthTable(string logicalFunc);
};

TruthTable::TruthTable()
{
}
TruthTable::TruthTable(string logicalFunc)
{
	CalcTruthTable(logicalFunc);
	
}

bool TruthTable::CheckPriority(stack<char> StakOfOperations, char newOperator)
{
	if (StakOfOperations.top() == '(')
		return true;
	if (newOperator == '*')
		if (StakOfOperations.top() != '+')
			return false;
	if (newOperator == '>')
		if (StakOfOperations.top() != '+' || StakOfOperations.top() != '*')
			return false;
	if (newOperator == '=')
		if (StakOfOperations.top() != '+' || StakOfOperations.top() != '*' || StakOfOperations.top() != '>')
			return false;	
	return true;
}
void TruthTable::Sum(stack <char> &StakOfVariables, stack <char> &StakOfOperations)
{
	bool firstVariable = getBool(StakOfVariables);
	bool secondVariable = getBool(StakOfVariables);
	if (firstVariable == true && secondVariable == true)
		StakOfVariables.push('t');
	else
		StakOfVariables.push('f');
	StakOfOperations.pop();
	return;
}
void TruthTable::Mult(stack<char>& StakOfVariables, stack<char>& StakOfOperations)
{
	bool firstVariable = getBool(StakOfVariables);
	bool secondVariable = getBool(StakOfVariables);
	if (firstVariable == false && secondVariable == false)
		StakOfVariables.push('f');
	else
		StakOfVariables.push('t');
	StakOfOperations.pop();
	return;
}
void TruthTable::CalcBracket(stack<char>& StakOfVariables, stack<char>& StakOfOperations)
{
	while (StakOfOperations.top() != '(')
	{
		if (StakOfOperations.top() == '+')
			Sum(StakOfVariables, StakOfOperations);
		else if (StakOfOperations.top() == '*')
			Mult(StakOfVariables, StakOfOperations);
	}
	StakOfOperations.pop();
}
void TruthTable::CalcTruthTable(string logicalFunc)
{
	stack <char> StakOfVariables;
	stack <char> StakOfOperations;
	for (int i = 0; i < logicalFunc.size(); i++)
	{
		if (logicalFunc[i] == '(')
			StakOfOperations.push(logicalFunc[i]);
		else if (logicalFunc[i] == 't' || logicalFunc[i] == 'f')
			StakOfVariables.push(logicalFunc[i]);
		else if (logicalFunc[i] == '+')
			if (CheckPriority(StakOfOperations, '+') == false)
				Sum(StakOfVariables, StakOfOperations);
			else
				StakOfOperations.push(logicalFunc[i]);
		else if (logicalFunc[i] == '*')
			if (CheckPriority(StakOfOperations, '*') == false)
				Mult(StakOfVariables, StakOfOperations);
			else
				StakOfOperations.push(logicalFunc[i]);
		else if (logicalFunc[i] == ')')
			CalcBracket(StakOfVariables, StakOfOperations);
	}
	cout << StakOfVariables.top() << endl;
}
bool TruthTable::getBool(stack <char>& StakOfVariables)
{
	if (StakOfVariables.top() == 't')
	{
		StakOfVariables.pop();
		return true;
	}
	else 
	{
		StakOfVariables.pop();
		return false;
	}
}

int main()
{
	TruthTable a("(t+f*(t*t+t)*f)");
}

