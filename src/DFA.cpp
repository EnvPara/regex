#include "DFA.h"
#include "Edge.h"
#include "Vertex.h"
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
	NFATable->Clear();
	DFATable->Clear();
}
//��ȡ��������
void DFA::InputRegex()
{
	cout << "��һ��: ������������ʽ\n";
	cin >> Regex;
}
//����"."�����
void DFA::InsertNode()
{
	int i = 0, j, len = strlen(Regex);
	int length = len;
	len--;
	while (len--)
	{
		if (((Regex[i] != '(' && Regex[i] != '.' && Regex[i] != '|')
			|| Regex[i] == ')' || Regex[i] == '*')
			&& (Regex[i + 1] != ')' && Regex[i + 1] != '.' && Regex[i + 1] != '|' && Regex[i + 1] != '*'))
		{
			for (j = length; j >i; j--)
			{
				Regex[j + 1] = Regex[j];
			}
			Regex[i + 1] = '.';
			length++;
			Regex[length] = '\0';
			i++;
		}
		i++;
	}
	cout << endl;
	cout << "�ڶ���: ����������\n";
	cout << Regex << endl;
	cout << "�ַ������ȣ�" << length << endl;
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
	cout << "\n������: תΪ��׺ʽ\n"
		<< RegexPost << "\n"
		<< "�ַ�������: " << strlen(RegexPost);
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
	cout << endl;
	cout << "\n���Ĳ�����ȡ�ַ���\n";
	for (i = 0; i<EdgeNumber; i++)
	{
		cout << EdgeNum[i] << ' ';
	}
	cout << "\n�ַ�����: " << EdgeNumber << endl;
	cout << "\n\n------------------------" << endl;
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
//�趨��������Ϊ0
void SetNFANodeAll(int(*A)[100])
{
	for (int i = 0; i < 101; i++)
	for (int j = 0; j < 101; j++)
		A[i][j] = 0;
}
//�ж��Ƿ���ͬһ��DFA״̬
int Judge(int States, int Jud[][100])
{
	int i, j, sum;
	i = 2;
	while (Jud[i][0] != 0)
	{
		sum = 0;
		j = 0;
		while (Jud[i][j] != 0)
		{
			if (Jud[States][j] == Jud[i][j])
				sum++;
			j++;
		}
		if (sum == j)
			return i;
		i++;
	}
	return States;
}
void SetAcceptStates(int *States)
{
	for (int i = 0; i <= 500; i++)
		States[i] = 0;
}
//�����Ӽ����취 NFA��DFA
void DFA::NFAtoDFA()
{
	int States, update = 0;
	int VertexNode[1001] = { 0 };
	LinkStack<int> DFAStates;//DFA��״̬����
	LinkStack<int>NFANode;//NFA��״̬�Ӽ���
	int NFANodeAll[100][100];
	SetNFANodeAll(NFANodeAll);
	int Pointer = 0;
	for (int i = 0; i < NFATable->numOfVertexs; i++)
		VertexNode[i] = 0;//����һ�����飬�洢�Ƿ���ʹ�
	States = 1;
	DFATable->InsertVertex(1);
	/*
	��1״̬��ʼ���ҳ����������λ��
	*/
	for (int i = 0; i < EdgeNumber; i++)
	{
		char weight = EdgeNum[i];
		Vertex *P = new Vertex;
		P = NFATable->StartVertex;
		for (int j = 0; j < States; j++)
			P = P->Next;
		if (P->Out->Link == NULL)
		{
			if (P->Out->weight == weight&&VertexNode[P->Out->position] == 0)//û�б����ʹ� 
				NFANode.Push(P->Out->position);
			VertexNode[P->Out->position] = 1;
		}
		if (P->Out->Link != NULL)
		{
			if (P->Out->weight == weight&&VertexNode[P->Out->position] == 0)//û�б����ʹ� 
				NFANode.Push(P->Out->position);
			VertexNode[P->Out->position] = 1;
			Edge *PLink = P->Out->Link;
			while (PLink != NULL)
			{
				if (P->Out->weight == weight&&VertexNode[P->Out->position] == 0)//û�б����ʹ� 
					NFANode.Push(P->Out->position);
				VertexNode[P->Out->position] = 1;
				PLink = PLink->Link;
			}
		}
		if (NFANode.IsEmpty())
			continue;
		States++;
		DFAStates.Push(States);
		while (!NFANode.IsEmpty())
		{
			int Visual = NFANode.GetTop();
			NFANode.Pop();
			NFANodeAll[States][Pointer] = Visual;
			Pointer++;
			P = NFATable->StartVertex;
			for (int j = 0; j < Visual; j++)
				P = P->Next;
			if (P->Out&&P->Out->Link == NULL)
			{
				if (P->Out->weight == '~'&&VertexNode[P->Out->position] == 0)//û�б����ʹ� 
					NFANode.Push(P->Out->position);
				VertexNode[P->Out->position] = 1;
			}
			else if (P->Out)
			{
				if (P->Out->weight == '~'&&VertexNode[P->Out->position] == 0)//û�б����ʹ� 
					NFANode.Push(P->Out->position);
				VertexNode[P->Out->position] = 1;
				Edge *LinkNode = P->Out->Link;
				while (LinkNode != NULL)
				{
					if (LinkNode->weight == '~'&&VertexNode[LinkNode->position] == 0)
						NFANode.Push(LinkNode->position);
					VertexNode[P->Out->position] = 1;
					LinkNode = LinkNode->Link;
				}
			}
		}
		DFATable->InsertVertex(States);
		DFATable->InsertEdgeByValue(1, States, EdgeNum[i]);
	}
	/*
	����1״̬�ó���NFA��״̬��ȥ���� ��
	*/
	while (!DFAStates.IsEmpty())
	{
		NFAStatesNumber = DFAStates.GetTop();
		DFAStates.Pop();
		for (int j = 0; j < EdgeNumber; j++)
		{
			int i = 0;
			char weight = EdgeNum[j];
			while (NFANodeAll[NFAStatesNumber][i] != 0)
			{
				int VertexNode[1001] = { 0 };
				Vertex *P = new Vertex;
				P = NFATable->StartVertex;
				for (int k = 0; k < NFANodeAll[NFAStatesNumber][i]; k++)
					P = P->Next;
				i++;
				if (P->Out == NULL)
					continue;
				if (P->Out->Link == NULL)
				{
					if (P->Out->weight == weight&&VertexNode[P->Out->position] == 0)//û�б����ʹ� 
						NFANode.Push(P->Out->position);
					VertexNode[P->Out->position] = 1;
				}
				if (P->Out->Link != NULL)
				{
					if (P->Out->weight == weight&&VertexNode[P->Out->position] == 0)//û�б����ʹ� 
						NFANode.Push(P->Out->position);
					VertexNode[P->Out->position] = 1;
					Edge *PLink = P->Out->Link;
					while (PLink != NULL)
					{
						if (P->Out->weight == weight&&VertexNode[P->Out->position] == 0)//û�б����ʹ� 
							NFANode.Push(P->Out->position);
						VertexNode[P->Out->position] = 1;
						PLink = PLink->Link;
					}
				}
				if (NFANode.IsEmpty())
					continue;
				States++;
				Pointer = 0;
				while (!NFANode.IsEmpty())
				{
					int Visual = NFANode.GetTop();
					NFANode.Pop();
					NFANodeAll[States][Pointer] = Visual;
					Pointer++;
					P = NFATable->StartVertex;
					for (int j = 0; j < Visual; j++)
						P = P->Next;
					if (P->Out&&P->Out->Link == NULL)
					{
						if (P->Out->weight == '~'&&VertexNode[P->Out->position] == 0)//û�б����ʹ� 
							NFANode.Push(P->Out->position);
						VertexNode[P->Out->position] = 1;
					}
					else if (P->Out)
					{
						if (P->Out->weight == '~'&&VertexNode[P->Out->position] == 0)//û�б����ʹ� 
							NFANode.Push(P->Out->position);
						VertexNode[P->Out->position] = 1;
						Edge *LinkNode = P->Out->Link;
						while (LinkNode != NULL)
						{
							if (LinkNode->weight == '~'&&VertexNode[LinkNode->position] == 0)
								NFANode.Push(LinkNode->position);
							VertexNode[P->Out->position] = 1;
							LinkNode = LinkNode->Link;
						}

					}
				}
				int Sign = States;
				States = Judge(States, NFANodeAll);
				if (States == Sign)
				{
					DFATable->InsertVertex(States);
					DFAStates.Push(States);
				}
				DFATable->InsertEdgeByValue(NFAStatesNumber, States, EdgeNum[j]);
				States = Sign;
			}
		}
	}
	NFAStatesNumber = States;
	DFAStatesNumber = DFATable->numOfVertexs - 1;
	/*
	��NFA��DFA״̬ͼ��1�Ž����ΪNFAͼ�Ŀ�ʼ״̬
	*/
	DFATable->StartVertex = DFATable->StartVertex->Next;
	NFATable->StartVertex = NFATable->StartVertex->Next;
	/*
	�õ�NFA��DFA�Ľ���״̬����
	*/
	SetAcceptStates(NFAAcceptStates);
	SetAcceptStates(DFAAcceptStates);
	Vertex *P = NFATable->StartVertex;
	//�õ�NFA�Ľ���״̬����
	for (int i = 1; i <NFATable->numOfVertexs; i++)
	{
		if (P->Out == NULL)
		{
			NFAAcceptStates[i] = i;
		}
		P = P->Next;
	}
	//�õ� DFA�Ľ���״̬����
	for (int i = 2; i <= States; i++)
	{
		for (int j = 0; j <= NFATable->numOfVertexs; j++)
		{
			int k = 0;
			while (NFANodeAll[i][k] != 0)
			{
				for (int n = 0; n <= NFATable->numOfVertexs; n++)
				{
					if (NFAAcceptStates[n] == NFANodeAll[i][k])
						DFAAcceptStates[i] = i;
				}
				k++;
			}
		}
	}
	int Vol;
	for (int i = 0; i <= States; i++)
	{
		if (DFAAcceptStates[i] != 0)
			Vol = Judge(DFAAcceptStates[i], NFANodeAll);
		if (Vol != DFAAcceptStates[i])
			DFAAcceptStates[i] = 0;
	}
}
//��ʼ��DFA״̬���ݱ��DFA״̬����
void InitializationDFAStates(int(*A)[101],char(*B)[101])
{
	for (int i = 0; i < 101; i++)
	for (int j = 0; j < 101; j++)
	{
		A[i][j] = 0;
		B[i][j] = '$';
	}
}
void DFA::Hopcroft()
{

}
//������Ҫƥ����ַ���
void DFA::InputString()
{
	cout << endl;
	cout << "��������Ҫƥ����ַ���" << endl;
	cin >> Input;
	cout << "������ַ���Ϊ:" << Input << endl;
}
//��������ƥ��
void DFA::Match()
{
	int Position = 0, Sign = 0;
	Matchout = Input;
	Vertex *P = DFATable->StartVertex;
	for (int i = 0; i < Input.length(); i++)
	{
		if (P->Out == NULL)
		{
			P = DFATable->StartVertex;
			continue;
		}
		if (P->Out->Link == NULL)
		{
			if (P->Out->weight == Input[i])
			{
				Position = P->Out->position;
				P = DFATable->StartVertex;
				for (int j = 1; j < Position; j++)
					P = P->Next;
				if (DFAAcceptStates[Position] == Position)//����ǽ���״̬
				{
					for (int j = Sign; j <= i; j++)
						Matchout[j] = Input[j];
					Sign = i + 1;
				}
			}
			else
			{
				if (P == DFATable->StartVertex)
				{
					for (int j = Sign; j <= i; j++)
						Matchout[j] = '#';
					P = DFATable->StartVertex;
					Sign = i + 1;
				}
				else
				{
					for (int j = Sign; j < i; j++)
						Matchout[j] = '#';
					P = DFATable->StartVertex;
					Sign = i;
					i--;
				}
			}
		}
		else
		{
			if (P->Out->weight == Input[i])
			{
				Matchout[i] = Input[i];
				Position = P->Out->position;
				P = DFATable->StartVertex;
				for (int j = 1; j < Position; j++)
					P = P->Next;
				if (DFAAcceptStates[Position] == Position)//����ǽ���״̬
				{
					for (int j = Sign; j <= i; j++)
						Matchout[j] = Input[j];
					Sign = i + 1;
				}
				continue;
			}
			Edge * Plink = new Edge;
			Plink = P->Out->Link;
			while (Plink != NULL)
			{
				if (Plink->weight == Input[i])
				{
					Matchout[i] = Input[i];
					Position = Plink->position;
					P = DFATable->StartVertex;
					for (int j = 1; j < Position; j++)
						P = P->Next;
					if (DFAAcceptStates[Position] == Position)//����ǽ���״̬
					{
						for (int j = Sign; j <= i; j++)
							Matchout[j] = Input[j];
						Sign = i + 1;
					}
					break;
				}
				else
					Plink = Plink->Link;
			}
			if (Plink == NULL)
			{
				P = DFATable->StartVertex;
				for (int j = Sign; j < i; j++)
					Matchout[j] = '#';
				Sign = i;
				i--;
			}

		}
	}
	for (int i = Sign; i < Input.length(); i++)
		Matchout[i] = '#';
	cout << "������ʽ��" << Regex << endl;
	cout << "������ַ�����" << Input << endl;
	cout << "����ƥ����ִ���" << Matchout << endl;
	cout << endl;
}
