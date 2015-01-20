#ifndef _DFA_H
#define _DFA_H
#include <string>
#include "Adj.h"
using namespace std;
class DFA
{
public:
	DFA();
	~DFA();
	char *Regex;
	char *RegexPost;
	void InputRegex();
	void InsertNode();
	void RegextoPost();
	int Precedence(char symbol);
	void GetEdgeNumber();
	void Thompson();//用Thompson构造法构造NFA
	int EdgeNumber;
	AdjacentTable *NFATable;
	char *Edge;
	int NFAStatesNumber;
	int DFAStatesNumber;
	int DtranNumber;
	AdjacentTable *NFATable;
	int *AcceptStates;
};
#endif