#include <iostream>
#include "DFA.h"
using namespace std;
int main()
{
	DFA DFA_each;
	DFA_each.InputRegex();//��������
	DFA_each.InsertNode();//��������
	DFA_each.RegextoPost();//תΪ��׺���ʽ
	DFA_each.GetEdgeNumber();
	system("pause");
	return 0;
}