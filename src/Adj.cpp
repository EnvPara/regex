#include "Adj.h"
#include <iostream>
using namespace std;
//���캯��
AdjacentTable::AdjacentTable()
{
	numOfVertexs = 1;
	numOfEdge = 0;
	StartVertex = new Vertex();
}
//��������
AdjacentTable::~AdjacentTable()
{
	Vertex *p;
	Edge *q;
	p = StartVertex;
	for (int i = 0; i < numOfVertexs; i++)
	{
		q = p->Out;
		while (q)
		{
			p->Out = q->Link;
			delete q;
			q = p->Out;
		}
		p = p->Next;
	}
}
//������λ�û�ȡ�����ֵ
int AdjacentTable::GetValueByPos(int pos) const
{
	if ((pos >= 0) && (pos < numOfVertexs))
	{
		Vertex *p = StartVertex;
		for (int i = 0; i < pos; i++)
		{
			p = p->Next;
		}
		return p->number;
	}
	else
		return -1;
}
//�������ֵ��ȡ�����λ��
int AdjacentTable::GetPosByValue(int value) const
{
	Vertex *p = StartVertex;
	for (int i = 0; i < numOfVertexs; i++)
	{
		if (p->number == value)
			return i;
		p = p->Next;
	}
	return -1;
}
//������λ�û�ȡ�ߵ�Ȩ
char AdjacentTable::GetWeightByPos(int v1, int v2) const
{
	if ((v1 >= 0) && (v2 >= 0) && (v1 < numOfVertexs) && (v2 < numOfVertexs))
	{
		Vertex *p = StartVertex;
		for (int i = 0; i < v1; i++)
		{
			p = p->Next;
		}
		Edge *q = p->Out;
		while (q)
		{ 
			if (q->position == v2)
				return q->weight;
			else q = q->Link;
		}
	}
	return '#';
}
//������ֵ��ȡ�ߵ�Ȩ
char AdjacentTable::GetWeightByValue(int value1, int value2) const
{
	return GetWeightByPos(GetPosByValue(value1), GetPosByValue(value2));
}
//���ö����ֵ
void AdjacentTable::SetValue(int value, int pos)
{
	if (pos < 0 || pos >= numOfVertexs)
	{
		cout << "illegal setting" << endl;
		exit(1);
	}
	Vertex *p = StartVertex;
	for (int i = 0; i < pos; i++)
	{
		p = p->Next;
	}
	p->number = value;
}
//���붥��
void AdjacentTable::InsertVertex(int value)
{

}