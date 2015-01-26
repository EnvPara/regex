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
	void Hopcroft();//����Hopcroft DFA����С��DFA
	void GetAcceptState();//�õ�NFA�Ľ���״̬����
	int NFAAcceptStates[500];//NFA����״̬����
	int DFAAcceptStates[500];//DFA����״̬����
	int NFANodeAll[100][100];//NFA��״̬����
	TransTable *MiniDFATable;//��С����DFA�ľ���
	int EdgeNumber;//������ʽ�г������������ַ�����Ŀ
	AdjacentTable *NFATable;
	char *EdgeNum;//������ʽ�г������������ַ�
	int JudgeVertex(char a);//�ж��ַ��ǳ������������ַ��ĵڼ���
	int NFAStatesNumber;
	int DFAStatesNumber;
	int DtranNumber;
	AdjacentTable *DFATable;
};
#endif