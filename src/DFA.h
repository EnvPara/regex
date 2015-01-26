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
	void Hopcroft();//利用Hopcroft DFA到最小化DFA
	void GetAcceptState();//得到NFA的接受状态集合
	int NFAAcceptStates[500];//NFA接受状态数组
	int EdgeNumber;
	AdjacentTable *NFATable;
	char *EdgeNum;
	int NFAStatesNumber;
	int DFAStatesNumber;
	int DtranNumber;
	AdjacentTable *DFATable;
	void SetStart();
};
#endif