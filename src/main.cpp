#include <iostream>
#include "DFA.h"
using namespace std;
int main()
{
	DFA DFA_each;
	DFA_each.InputRegex();//输入正则
	DFA_each.InsertNode();//添加连结符
	DFA_each.RegextoPost();//转为后缀表达式
	DFA_each.GetEdgeNumber();//扫描逆波兰式中除运算符以外的字符的数目
	DFA_each.Thompson();//用Thompson构造法构造NFA
	DFA_each.NFAtoDFA();//利用子集构造法 NFA到DFA
	DFA_each.Hopcroft();//利用最小化DFA算法
	DFA_each.InputString();//输入需要匹配的字符串
	DFA_each.Match();//进行正则匹配
	system("pause");
	return 0;
}