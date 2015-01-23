#include "DFA.h"
#include "Edge.h"
#include "Vertex.h"
#include <string>
#include <stack>
#include <vector>
#include <iostream>
#include <queue>
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
		data = item;
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
void LinkStack<T>::Push(const T &item)
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
		DFA
*/
//DFA���캯��
DFA::DFA()
{
	Regex = new char[128];
	RegexPost = new char[128]; 
	EdgeNum = new char[128];
	EdgeNumber = 0;
	DFAStatesNumber = 0;
	NFAStatesNumber = 0;
	DtranNumber = 0;
	NFATable = new AdjacentTable();
	DFATable = new AdjacentTable();
}
//DFA����������
DFA::~DFA()
{
	delete[] Regex;
	delete[] RegexPost;
	//delete[] Edge;
	//delete[] AcceptStates;
	//NFATable->Clear();
	//DFATable->clear();
}
//��ȡ��������
void DFA::InputRegex()
{
	cout << " ������������ʽ" << endl;
	cin >> Regex;
}
//����"."�����
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
	cout << "����������     " << endl;
	cout<<Regex << endl;
	cout << "�ַ������ȣ�" <<length<<endl;
}
//�ж���������ȼ�
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
//������ʽתΪ�沨��ʽ
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
	cout << "\n�ڶ���: תΪ��׺ʽ\n"
		<< RegexPost << "\n"
		<< "�ַ�������: " << strlen(RegexPost)
		<< "\n\n------------------------" << endl;
}
//ɨ���沨��ʽ�г������������ַ�����Ŀ
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
			if (RegexPost[i] == EdgeNum[j])
				break;
		}
		if (j == EdgeNumber)
		{
			EdgeNum[EdgeNumber] = RegexPost[i];
			EdgeNumber++;
		}
		i++;
	}
	EdgeNum[EdgeNumber] = '\0';
	cout << "\n������: ��ȡ�ַ���\n";
	for (i = 0; i<EdgeNumber; i++)
	{
		cout << EdgeNum[i] << ' ';
	}
	cout << "\n�ַ�����: " << EdgeNumber
		<< "\n\n------------------------" << endl;
}

//��Thompson���취����NFA
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
	i = 1; j = 0;
	ch = RegexPost[j];
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
		j++;
		ch = RegexPost[j];
	}
	s2 = States->Pop();
	s1 = States->Pop();
	NFAStatesNumber = s2 + 1;
}
//�����Ӽ����취 NFA��DFA
void DFA::NFAtoDFA()
{
	int states;
	int VertexNode[1001];
	queue<int > DFAStates;//DFA��״̬����
	queue<int >NFANode;//NFA��״̬�Ӽ���
	int NFANodeAll[100][100];
	DFAStates.push(1);
	int Pointer = 0;
	for (int i = 0; i < NFATable->numOfVertexs; i++)
		VertexNode[i] = 0;//����һ�����飬�洢�Ƿ���ʹ�
	states = DFAStates.front();//���DFA״̬���еĵ�һ��
	/*
		��1״̬��ʼ���ҳ����������λ��
	*/
	for (int i = 0; i < EdgeNumber; i++)
	{
		char weight = EdgeNum[i];
		Vertex *P = new Vertex;
		P = NFATable->StartVertex;
		for (int j = 0; j < states; j++)
			P = P->Next;
		if (P->Out->Link == NULL)
		{
			if (P->Out->weight == weight&&VertexNode[P->Out->position] == 0)//û�б����ʹ� 
				NFANode.push(P->Out->position);
		}
		while (P->Out->Link != NULL)
		{
			if (P->Out->weight == weight&&VertexNode[P->Out->position] == 0)//û�б����ʹ� 
				NFANode.push(P->Out->position);
		}
		if (NFANode.empty())
			break;
		states++;
		while (!NFANode.empty())
		{
			int Visual = NFANode.front();
			NFANode.pop();
			NFANodeAll[states][Pointer] = Visual;
			Pointer++;
			P = NFATable->StartVertex;
			for (int j = 0; j < Visual; j++)
				P = P->Next;
			if (P->Out&&P->Out->Link == NULL)
			{
				if (P->Out->weight == '~'&&VertexNode[P->Out->position] == 0)//û�б����ʹ� 
					NFANode.push(P->Out->position);
			}
			else if (P->Out)
			{
				if (P->Out->weight == '~'&&VertexNode[P->Out->position] == 0)//û�б����ʹ� 
					NFANode.push(P->Out->position);
				Edge *LinkNode= P->Out->Link;
				while (LinkNode!= NULL)
				{
					if (LinkNode->weight == '~'&&VertexNode[LinkNode->position] == 0)
						NFANode.push(LinkNode->position);
					LinkNode = LinkNode->Link;
				}
			}
		}
		DFATable->InsertEdgeByValue(1, states, EdgeNum[i]);
	}
	/*
		����1״̬�ó���NFA��״̬��ȥ���� ��
	*/
	
}