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
	int DFAAcceptStates[500];//DFA接受状态数组
	int NFANodeAll[100][100];//NFA的状态集合
	TransTable *MiniDFATable;//最小化的DFA的矩阵
	int EdgeNumber;//正则表达式中除运算符以外的字符的数目
	AdjacentTable *NFATable;
	char *EdgeNum;//正则表达式中除运算符以外的字符
	int JudgeVertex(char a);//判断字符是除运算符以外的字符的第几个
	int NFAStatesNumber;
	int DFAStatesNumber;
	int DtranNumber;
	AdjacentTable *DFATable;
};
#endif