#include "DFA.h"
#include <string>
#include <stack>
#include <iostream>
using namespace std;
//��ȡ��������
void DFA::InputRegex()
{
	cout << " ������������ʽ" << endl;
	cin >> Regex;
}
//���������
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
	cout << "\n��һ�������������\n" << Regex << endl;
	cout << "�ַ������ȣ�" <<length<<endl;
}
//תΪ��׺���ʽ
void DFA::RegextoPost()
{
	bool Crave = false;//�������Ƿ��Ѿ�ѹջ
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