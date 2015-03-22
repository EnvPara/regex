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
	void NFAtoDFA();//利用子集构造法 NFA到DFA
	void Hopcroft();//利用Hopcroft DFA到最小化DFA
	void GetAcceptState();//得到NFA的接受状态集合
	int NFAAcceptStates[500];//NFA接受状态数组
	int DFAAcceptStates[500];//DFA接受状态数组
	int NFANodeAll[100][100];//NFA的状态集合
	int EdgeNumber;//正则表达式中除运算符以外的字符的数目
	AdjacentTable *NFATable;
	char *EdgeNum;//正则表达式中除运算符以外的字符
	int JudgeVertex(char a);//判断字符是除运算符以外的字符的第几个
	void InputString();//输入需要匹配的字符串
	string Input;//需要匹配的字符串
	string Matchout; //与正则表达式匹配的字符
	void Match();//将输入的字符串与正则进行匹配
	int NFAStatesNumber;
	int DFAStatesNumber;
	AdjacentTable *DFATable;
	char DFAStates[101][101];//DFA的状态集合的数据表
	int MiniDFAStates[101][101];//最小化DFA时的状态集合
	void SetDFAStates();//设置DFA的状态集合的数据表
};
#endif