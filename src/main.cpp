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
	DFA_each.SetStart();//将NFA状态图的1号结点设为NFA图的开始状态
	DFA_each.GetAcceptState();////得到NFA的接受状态集合
	return 0;
}