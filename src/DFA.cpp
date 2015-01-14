#include "DFA.h"
#include <string>
#include <stack>
#include <iostream>
using namespace std;
template <class T>
class LinkStack;

//定义链式栈结点类
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

// 定义链式栈类
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
//定义构造函数
template <class T>
LinkStack<T>::LinkStack()
{
	top = NULL;
}

//定义析构函数
template <class T>
LinkStack<T>::~LinkStack()
{
	Clear();
}
//判断栈是否为空
template <class T>
bool LinkStack<T>::IsEmpty()
{
	return(!top);
}
//栈的长度
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
//压栈
template <class T>
void LinkStack<T>::Push(T *&item)
{
	top = new StackNode<T>(item, top);
}
// 抽出数据(出栈)
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
//获取栈顶数据
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
//清空栈
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
