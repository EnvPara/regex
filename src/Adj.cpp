#include "Adj.h"
#include <iostream>
using namespace std;
//构造函数
AdjacentTable::AdjacentTable()
{
	numOfVertexs = 1;
	numOfEdge = 0;
	StartVertex = new Vertex();
}
//析构函数
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
//按顶点位置获取顶点的值
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
//按顶点的值获取顶点的位置
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
//按顶点位置获取边的权
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
//按顶点值获取边的权
char AdjacentTable::GetWeightByValue(int value1, int value2) const
{
	return GetWeightByPos(GetPosByValue(value1), GetPosByValue(value2));
}
//设置顶点的值
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
//插入顶点
void AdjacentTable::InsertVertex(int value)
{

}