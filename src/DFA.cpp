#include "DFA.h"
#include <string>
#include <stack>
#include <iostream>
using namespace std;
//获取正则输入
void DFA::InputRegex()
{
	cout << " 请输入正则表达式" << endl;
	cin >> Regex;
}
//加入连结点
void DFA::InsertNode()
{
	int i = 0, bool_value, len = Regex.length();
	int length = len;
	while (len--&&i<=length-1)
	{
		if (((Regex[i] != '(' && Regex[i] != '.' && Regex[i] != '|')
			|| Regex[i] == ')'
			|| Regex[i] == '*')
			&& (Regex[i + 1] != ')' && Regex[i + 1] != '.' && Regex[i + 1] != '|' && Regex[i + 1] != '*'))
		{
			Regex.insert(i+1,1, '.');
			length++;
			i++;
			len++;
		}
		i++;
	}
	cout << "\n第一步：加入连结点\n" << Regex << endl;
	cout << "字符串长度：" <<length<<endl;
}
//转为后缀表达式
void DFA::RegextoPost()
{
	bool Crave = false;//左括号是否已经压栈
	stack<char > PostStack;
	int len = Regex.length();
	int i = len;
	while (len--)
	{
		if (Regex[i] == '(')
		{
			PostStack.push(Regex[i]);
			i++;
			Crave = true;
		}
		else if (Regex[i] == ')')
		{

		}
	}

}