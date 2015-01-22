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
		data = item;
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
void LinkStack<T>::Push(const T &item)
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
		DFA
*/
//DFA构造函数
DFA::DFA()
{
	Regex = new char[128];
	RegexPost = new char[128]; 
	Edge = new char[128];
	EdgeNumber = 0;
	DFAStatesNumber = 0;
	NFAStatesNumber = 0;
	DtranNumber = 0;
	NFATable = new AdjacentTable();
}
//DFA的析构函数
DFA::~DFA()
{
	delete[] Regex;
	delete[] RegexPost;
	//delete[] Edge;
	//delete[] AcceptStates;
	//NFATable->Clear();
	//DFATable->clear();
}
//获取正则输入
void DFA::InputRegex()
{
	cout << " 请输入正则表达式" << endl;
	cin >> Regex;
}
//加入"."连结点
void DFA::InsertNode()
{
	int i = 0,j, len = strlen(Regex);
	int length = len;
	len--;
	while (len--)
	{
		if (((Regex[i] != '(' && Regex[i] != '.' && Regex[i] != '|')
			|| Regex[i] == ')'|| Regex[i] == '*')
			&& (Regex[i + 1] != ')' && Regex[i + 1] != '.' && Regex[i + 1] != '|' && Regex[i + 1] != '*'))
		{
			for (j =length; j >i;j--)
			{
				Regex[j+1] = Regex[j];
			}
			Regex[i + 1] = '.';
			length++;
			Regex[length] = '\0';
			i++;
		}
		i++;
	}
	cout << endl;
	cout << "加入连结点后     " << endl;
	cout<<Regex << endl;
	cout << "字符串长度：" <<length<<endl;
}
//判断运算符优先级
int DFA::Precedence(char symbol)
{
	int priority;
	switch (symbol)
	{
	case '|':priority = 1; break;
	case '.':priority = 2; break;
	case '*':priority = 3; break;
	default:priority = 0; break;
	}
	return priority;
}
//将正则式转为逆波兰式
void DFA::RegextoPost()
{
	int i = 0, j = 0;
	char ch, cl;
	strcpy(RegexPost, "\0");
	LinkStack<char> *Value = new LinkStack<char>();
	Value->Clear();
	ch = Regex[i];
	Value->Push('#');
	ch = Regex[i];
	while (ch != '\0')
	{
		if (ch == '(')
		{
			Value->Push(ch);
			ch = Regex[++i];
		}
		else if (ch == ')')
		{
			while (Value->GetTop() != '(')
			{
				RegexPost[j++] = Value->Pop();
			}
			Value->Pop();
			ch = Regex[++i];
		}
		else if ((ch == '|') || (ch == '*') || (ch == '.'))
		{
			cl = Value->GetTop();
			while (Precedence(cl) >= Precedence(ch))
			{
				RegexPost[j++] = cl;
				Value->Pop();
				cl = Value->GetTop();
			}
			Value->Push(ch);
			ch = Regex[++i];
		}
		else
		{
			RegexPost[j++] = ch;
			ch = Regex[++i];
		}
	}
	ch = Value->Pop();
	while ((ch == '|') || (ch == '*') || (ch == '.'))
	{
		RegexPost[j++] = ch;
		ch = Value->Pop();
	}
	RegexPost[j] = '\0';
	Value->Clear();
	cout << "\n第二步: 转为后缀式\n"
		<< RegexPost << "\n"
		<< "字符串长度: " << strlen(RegexPost)
		<< "\n\n------------------------" << endl;
}
//扫描逆波兰式中除运算符以外的字符的数目
void DFA::GetEdgeNumber()
{
	int i = 0, j;
	EdgeNumber = 0;
	while (RegexPost[i] != '\0')
	{
		if (RegexPost[i] == '.' || RegexPost[i] == '|' || RegexPost[i] == '*')
		{
			i++;
			continue;
		}
		for (j = 0; j < EdgeNumber; j++)
		{
			if (RegexPost[i] == Edge[j])
				break;
		}
		if (j == EdgeNumber)
		{
			Edge[EdgeNumber] = RegexPost[i];
			EdgeNumber++;
		}
		i++;
	}
	Edge[EdgeNumber] = '\0';
	cout << "\n第三步: 获取字符集\n";
	for (i = 0; i<EdgeNumber; i++)
	{
		cout << Edge[i] << ' ';
	}
	cout << "\n字符个数: " << EdgeNumber
		<< "\n\n------------------------" << endl;
}

//用Thompson构造法构造NFA
void DFA::Thompson()
{ 
	int i, j;
	char ch;
	int s1, s2;
	LinkStack<int >*States = new LinkStack<int >();
	States->Clear();
	if (strlen(RegexPost) < 1)
	{
		cout << "No Regex Expression Find" << endl;
		exit(1);
	}
	NFATable->SetValue(0, 0);
	i = 1; j = 0;
	ch = RegexPost[i];
	while (ch != '\0')
	{
		if (ch == '.')
		{
			s2 = States->Pop();
			int Ex1 = States->Pop();
			int Ex2 = States->Pop();
			s1 = States->Pop();
			NFATable->InsertEdgeByValue(Ex2, Ex1, '~');
			States->Push(s1);
			States->Push(s2);
		}
		else if (ch == '*')
		{
			s2 = States->Pop();
			s1 = States->Pop();
			NFATable->InsertVertex(i);
			NFATable->InsertVertex(i + 1);
			NFATable->InsertEdgeByValue(i, i + 1, '~');
			NFATable->InsertEdgeByValue(s2, s1, '~');
			NFATable->InsertEdgeByValue(i, s1, '~');
			NFATable->InsertEdgeByValue(s2, i + 1, '~');
			s1 = i;
			s2 = i + 1;
			States->Push(s1);
			States->Push(s2);
			i += 2;
		}
		else if (ch == '|')
		{
			s2 = States->Pop();
			int temp1 = States->Pop();
			int temp2 = States->Pop();
			s1 = States->Pop();
			NFATable->InsertVertex(i);
			NFATable->InsertVertex(i + 1);
			NFATable->InsertEdgeByValue(i, s1, '~');
			NFATable->InsertEdgeByValue(i, temp1, '~');
			NFATable->InsertEdgeByValue(temp2, i + 1, '~');
			NFATable->InsertEdgeByValue(s2, i + 1, '~');
			s1 = i;
			s2 = i + 1;
			States->Push(s1);
			States->Push(s2);
			i += 2;
		}
		else 
		{
			NFATable->InsertVertex(i);
			NFATable->InsertVertex(i + 1);
			NFATable->InsertEdgeByValue(i, i + 1, ch);
			s1 = i;
			s2 = i + 1;
			States->Push(s1);
			States->Push(s2);
			i += 2;
		}
	}
	s2 = States->Pop();
	s1 = States->Pop();
	NFAStatesNumber = s2 + 1;
}