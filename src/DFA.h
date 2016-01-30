#ifndef DFA_H_
#define DFA_H_
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
	void Thompson();
	void NFAtoDFA();
	void Hopcroft();
	void GetAcceptState();
	int NFAAcceptStates[500];
	int DFAAcceptStates[500];
	int NFANodeAll[100][100];
	int EdgeNumber;
	AdjacentTable *NFATable;
	char *EdgeNum;
	int JudgeVertex(char a);
	void InputString();
	string Input;
	string Matchout;
	void Match();
	int NFAStatesNumber;
	int DFAStatesNumber;
	AdjacentTable *DFATable;
	char DFAStates[101][101];
	int MiniDFAStates[101][101];
	void SetDFAStates();
};
#endif
