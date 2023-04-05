#include <iostream>
#include <vector>
#include <set>
#include <stack>

using namespace std;



class TruthTable 
{
	vector < string > truthTable = {};
	set <char> plentyOfVariables;

	void FindVariables(set <char> &plentyOfVariables, string logicalFunc);
	bool CalcTruthTable(string logicalFunc);
	void Inverse(stack <char>& StakOfVariables, stack <char>& StakOfOperations);
	void Sum(stack <char> &StakOfVariables, stack <char> &StakOfOperations);
	void Mult(stack <char>& StakOfVariables, stack <char>& StakOfOperations);
	void Implication(stack <char>& StakOfVariables, stack <char>& StakOfOperations);
	void Equialense(stack <char>& StakOfVariables, stack <char>& StakOfOperations);
	bool CheckPriority(stack <char> StakOfOperations, char newOperator);
	void CalcBracket(stack <char>& StakOfVariables, stack <char>& StakOfOperations);
	bool getBool(stack <char>& StakOfVariables);
	void DoPrevOperation(stack <char>& StakOfVariables, stack <char>& StakOfOperations);
	void AddOperation(stack <char>& StakOfVariables, stack <char>& StakOfOperations, char operation, string logicalFunc, int index);
	string ReplaceVariables(string stringToReplace, string stringOfMeanings);
	string BinaryPlusOne(string inString);
	

public:
	TruthTable();
	TruthTable(string logicalFunc);
	void SKNF();
	void SDNF();
};

TruthTable::TruthTable()
{
}
TruthTable::TruthTable(string logicalFunc)
{

	string varOfMeaning = "";
	FindVariables(this->plentyOfVariables, logicalFunc);
	for (int i = 0; i < plentyOfVariables.size(); i++)
		varOfMeaning.push_back('0');
	for (int i = 0; i < pow(2, plentyOfVariables.size()); i++) 
	{
		this->truthTable.push_back(varOfMeaning);
		varOfMeaning = BinaryPlusOne(varOfMeaning);
	}
	for (int i = 0; i < truthTable.size(); i++) 
	{
		bool tmp = CalcTruthTable(ReplaceVariables(logicalFunc, truthTable[i]));
		if (tmp == 0)
			truthTable[i].push_back('0');
		else if (tmp == 1)
			truthTable[i].push_back('1');
	}
		
	cout << "end" << endl;
	
}
void TruthTable::FindVariables(set <char>& plentyOfVariables, string logicalFunc)
{
	for (int i = 0; i < logicalFunc.size(); i++)
		if (logicalFunc[i] > 64 && logicalFunc[i] < 91) 
			plentyOfVariables.insert(logicalFunc[i]);
}
bool TruthTable::CheckPriority(stack<char> StakOfOperations, char newOperator)
{
	if (StakOfOperations.top() == '(')
		return true;
	if (newOperator == '+')
		if (StakOfOperations.top() != '-')
			return false;
	if (newOperator == '*')
		if (StakOfOperations.top() != '+' || StakOfOperations.top() != '-')
			return false;
	if (newOperator == '>')
		if (StakOfOperations.top() != '+' || StakOfOperations.top() != '*' || StakOfOperations.top() != '-')
			return false;
	if (newOperator == '=')
		if (StakOfOperations.top() != '+' || StakOfOperations.top() != '*' || StakOfOperations.top() != '>' || StakOfOperations.top() != '-')
			return false;	
	return true;
}
void TruthTable::Inverse(stack<char>& StakOfVariables, stack<char>& StakOfOperations)
{
	bool variable = getBool(StakOfVariables);
	if(variable == true)
		StakOfVariables.push('f');
	else
		StakOfVariables.push('t');
	StakOfOperations.pop();
	return;
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
void TruthTable::Implication(stack<char>& StakOfVariables, stack<char>& StakOfOperations)
{
	bool secondVariable = getBool(StakOfVariables);
	bool firstVariable = getBool(StakOfVariables);
	if (firstVariable == true && secondVariable == false)
		StakOfVariables.push('f');
	else
		StakOfVariables.push('t');
	StakOfOperations.pop();
	return;
}
void TruthTable::Equialense(stack<char>& StakOfVariables, stack<char>& StakOfOperations)
{
	bool firstVariable = getBool(StakOfVariables);
	bool secondVariable = getBool(StakOfVariables);
	if (firstVariable == secondVariable)
		StakOfVariables.push('t');
	else
		StakOfVariables.push('f');
	StakOfOperations.pop();
	return;
}
void TruthTable::CalcBracket(stack<char>& StakOfVariables, stack<char>& StakOfOperations)
{
	while (StakOfOperations.top() != '(')
	{
		if (StakOfOperations.top() == '-')
			Inverse(StakOfVariables, StakOfOperations);
		else if (StakOfOperations.top() == '+')
			Sum(StakOfVariables, StakOfOperations);
		else if (StakOfOperations.top() == '*')
			Mult(StakOfVariables, StakOfOperations);
		else if (StakOfOperations.top() == '>')
			Implication(StakOfVariables, StakOfOperations);
		else if (StakOfOperations.top() == '=')
			Equialense(StakOfVariables, StakOfOperations);
	}
	StakOfOperations.pop();
}
bool TruthTable::CalcTruthTable(string logicalFunc)
{
	stack <char> StakOfVariables;
	stack <char> StakOfOperations;
	for (int i = 0; i < logicalFunc.size(); i++)
	{
		if (logicalFunc[i] == '(')
			StakOfOperations.push(logicalFunc[i]);
		else if (logicalFunc[i] == 't' || logicalFunc[i] == 'f')
			StakOfVariables.push(logicalFunc[i]);
		else if (logicalFunc[i] == '-' || logicalFunc[i] == '+' || logicalFunc[i] == '*' || logicalFunc[i] == '>' || logicalFunc[i] == '=')
			AddOperation(StakOfVariables, StakOfOperations, logicalFunc[i], logicalFunc, i);
		else if (logicalFunc[i] == ')')
			CalcBracket(StakOfVariables, StakOfOperations);
	}
	cout << StakOfVariables.top() << endl;
	return getBool(StakOfVariables);
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
void TruthTable::DoPrevOperation(stack<char>& StakOfVariables, stack<char>& StakOfOperations)
{
	if(StakOfOperations.top() == '-')
		Inverse(StakOfVariables, StakOfOperations);
	else if (StakOfOperations.top() == '+')
		Sum(StakOfVariables, StakOfOperations);
	else if (StakOfOperations.top() == '*')
		Mult(StakOfVariables, StakOfOperations);
	else if (StakOfOperations.top() == '>')
		Implication(StakOfVariables, StakOfOperations);
	else if (StakOfOperations.top() == '=')
		Equialense(StakOfVariables, StakOfOperations);
}
void TruthTable::AddOperation(stack<char>& StakOfVariables, stack<char>& StakOfOperations, char operation, string logicalFunc, int i)
{
	if (CheckPriority(StakOfOperations, operation) == false)
	{
		DoPrevOperation(StakOfVariables, StakOfOperations);
		StakOfOperations.push(logicalFunc[i]);
	}
	else
		StakOfOperations.push(logicalFunc[i]);
}
string TruthTable::ReplaceVariables(string stringToReplace, string stringOfMeanings)
{
	vector <char> Variables;
	int numOfMeaning = 0;
	for (std::set<char>::iterator i = this->plentyOfVariables.begin(); i != this->plentyOfVariables.end(); ++i)
	{
		for(int j = 0; j < stringToReplace.size(); j++)
			if (stringToReplace[j] == *i)
			{
				if (stringOfMeanings[numOfMeaning] == '0')
					stringToReplace[j] = 'f';
				else if (stringOfMeanings[numOfMeaning] == '1')
					stringToReplace[j] = 't';
			}
		numOfMeaning++;
	}
	return stringToReplace;
}
string TruthTable::BinaryPlusOne(string inString)
{
	string output;
	bool addOne = 1;
	for(int i = inString.size() - 1; i >= 0; i--)
	{
		if (addOne == 1 && inString[i] == '1')
			inString[i] = '0';
		else if (addOne == 1 && inString[i] == '0')
		{
			inString[i] = '1';
			addOne = 0;
		}
	}
	output = inString;
	return output;
}
void TruthTable::SKNF()
{
	string output = "";
	for (int i = 0; i < truthTable.size(); i++)
	{
		if (truthTable[i].back() == '1')
		{
			if (output != "")
				output.push_back('*');
			output.push_back('(');
			int numOfMeaning = 0;
			for (std::set<char>::iterator j = this->plentyOfVariables.begin(); j != this->plentyOfVariables.end(); ++j) 
			{
				if (truthTable[i][numOfMeaning] == '1')
					output.push_back(*j);
				else if (truthTable[i][numOfMeaning] == '0')
					output = output + "(-" + *j + ')';
				if (numOfMeaning < truthTable[i].size() - 2)
					output.push_back('+');
				numOfMeaning++;
			}
			output.push_back(')');
		}
	}
	cout << output << endl;
}
void TruthTable::SDNF()
{
	string output = "";
	for (int i = 0; i < truthTable.size(); i++)
	{
		if (truthTable[i].back() == '0')
		{
			if (output != "")
				output.push_back('+');
			output.push_back('(');
			int numOfMeaning = 0;
			for (std::set<char>::iterator j = this->plentyOfVariables.begin(); j != this->plentyOfVariables.end(); ++j)
			{
				if (truthTable[i][numOfMeaning] == '0')
					output.push_back(*j);
				else if (truthTable[i][numOfMeaning] == '1')
					output = output + "(-" + *j + ')';
				if (numOfMeaning < truthTable[i].size() - 2)
					output.push_back('*');
				numOfMeaning++;
			}
			output.push_back(')');
		}
	}
	cout << output << endl;
}

int main()
{
	TruthTable a("((A+B*(D*A+B)*D)>(-C))");
	a.SKNF();
	a.SDNF();
}

