#ifndef _DFA_H
#define _DFA_H
#include <string>
#include "TransTable.h"
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
	void NFAtoDFA();//利用子集构造法 NFA到DFA
	int EdgeNumber;
	AdjacentTable *NFATable;
	char *EdgeNum;
	int NFAStatesNumber;
	int DFAStatesNumber;
	int DtranNumber;
	AdjacentTable *DFATable;
	int *AcceptStates;
	void SetStart();
};
#endif