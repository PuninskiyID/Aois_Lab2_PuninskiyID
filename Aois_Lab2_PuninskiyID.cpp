#include <iostream>
#include <vector>
#include <set>

using namespace std;

class TruthTable 
{
	vector < vector <bool> > truthTable;
	class Variable 
	{
		char simbol;
		bool meaning;
	};
	set <Variable> plentyOfVariables;
	const string trueMeaning = "t_";
	const string falseMeaning = "f_";
	const string andMeaning = "/\\";
	const string orMeaning = "\\/";
	const string implication = "->";
	const string equivalence = "~~";

	int MaxBreacketSearch(string logicalFunc);
	void SolveNukeFunc(string& logicalFunc, int index);
	bool LogicalAnd(bool num1, bool num2);
	void ReplaceNukeFunc(string& logicalFunc, int index, bool meaningToReplace);

public:
	TruthTable();
	TruthTable(string logicalFunc);
};

TruthTable::TruthTable()
{
}

TruthTable::TruthTable(string logicalFunc)
{
	
}

int TruthTable::MaxBreacketSearch(string logicalFunc)
{
	int maxBracketLevel = 0;
	int bracketLevel = 0;
	int startOfBracket = 0;
	for (int i = 0; i < logicalFunc.size(); i++) 
	{
		if (logicalFunc[i] == '(')
			bracketLevel++;
		if (logicalFunc[i] == ')')
			bracketLevel--;
		if (bracketLevel > maxBracketLevel)
		{
			maxBracketLevel = bracketLevel;
			startOfBracket = i;
		}
	}
	return startOfBracket;
}
void TruthTable::SolveNukeFunc(string& logicalFunc, int index)
{
	index += 2;
	bool num1 = false;
	bool num2 = false;
	if (logicalFunc[index - 2] == 't')
		num1 = true;
	if(logicalFunc[index + 2] == 't')
		num2 = true;

	if (logicalFunc[index] == '/' && logicalFunc[index + 1] == '\\')   //need more funcs
		ReplaceNukeFunc(logicalFunc, index, LogicalAnd(num1, num2));

}

bool TruthTable::LogicalAnd(bool num1, bool num2)
{
	if (num1 && num2)
		return true;
	return false;
}

void TruthTable::ReplaceNukeFunc(string& logicalFunc, int index, bool meaningToReplace)
{
	string output = "";
	for (int i = 0; i < index; i++) 
		output.push_back(logicalFunc[i]);
	if (meaningToReplace == true)
		output += "t_";
	if (meaningToReplace == false)
		output += "f_";
	for (int i = index + 6; i < logicalFunc.size(); i++)
		output.push_back(logicalFunc[i]);
	logicalFunc = output;
}

int main()
{
   
}

