#include <iostream>
#include "DFA.h"
using namespace std;
int main()
{
	DFA DFA_each;
	DFA_each.InputRegex();//输入正则
	DFA_each.InsertNode();//添加连结符
	DFA_each.RegextoPost();//转为后缀表达式
	system("pause");
	return 0;
}