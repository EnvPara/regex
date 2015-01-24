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
	void Thompson();//��Thompson���취����NFA
	void NFAtoDFA();//�����Ӽ����취 NFA��DFA
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