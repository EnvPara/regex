#include "DFA.h"
#include <string>
#include <stack>
#include <iostream>
using namespace std;
template <class T>
class LinkStack;

//������ʽջ�����
template <class T>
class StackNode
{
	friend class LinkStack<T>;
private:
	T data;
	StackNode<T> *next;
	StackNode(T item = 0, StackNode<T> *p = NULL)
	{
		date = item;
		next = p;
	}
};

// ������ʽջ��
template <class T>
class LinkStack
{
private:
	StackNode<T> *top;
public:
	LinkStack();
	~LinkStack();
	bool IsEmpty();
	int Length();
	void Push(const T &item);
	T Pop();
	T GetTop();
	void Clear();
};
//���幹�캯��
template <class T>
LinkStack<T>::LinkStack()
{
	top = NULL;
}

//������������
template <class T>
LinkStack<T>::~LinkStack()
{
	Clear();
}
//�ж�ջ�Ƿ�Ϊ��
template <class T>
bool LinkStack<T>::IsEmpty()
{
	return(!top);
}
//ջ�ĳ���
template <class T>
int LinkStack<T>::Length()
{
	StackNode<T> *temp = new StackNode<T>();
	temp = top;
	int length = 0;
	while (temp)
	{
		temp = temp->next;
		length++;
	}
	return length;
}
//ѹջ
template <class T>
void LinkStack<T>::Push(T *&item)
{
	top = new StackNode<T>(item, top);
}
// �������(��ջ)
template <class T>
T LinkStack<T>::Pop()
{
	if (!IsEmpty())
	{
		StackNode<T> *temp = top;
		top = top->next;
		T value = temp->data;
		delete temp;
		return value;
	}
	else
	{
		cout << "Stack is Empty" << endl;
		exit(1);
	}
}
//��ȡջ������
template<class T>
T LinkStack<T>::GetTop()
{
	if (!IsEmpty())
		return top->data;
	else
	{
		cout << "The Stack is Empty" << endl;
		exit(1);
	}
}
//���ջ
template<class T>
void LinkStack<T>::Clear()
{
	StackNode<T> *temp = new StackNode<T>();
	while (top)
	{
		temp = top;
		top = top->next; 
		delete temp;
	}
}
/*
*/
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
