#include "Adj.h"
#include <iostream>
using namespace std;

AdjacentTable::AdjacentTable()
{
	numOfVertexs = 1;
	numOfEdge = 0;
	StartVertex = new Vertex();
}

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

char AdjacentTable::GetWeightByValue(int value1, int value2) const
{
	return GetWeightByPos(GetPosByValue(value1), GetPosByValue(value2));
}

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

void AdjacentTable::InsertVertex(int value)
{
	int pos = GetPosByValue(value);
	if (pos >= 0 && pos < numOfVertexs)
	{
		cout << "illegal setting" << endl;
		exit(1);
	}
	Vertex *p = StartVertex;
	while (p->Next)
		p = p->Next;
	Vertex *newVertex = new Vertex(value);
	p->Next = newVertex;
	numOfVertexs++;
}

void AdjacentTable::InsertEdgeByPos(int v1, int v2, char weight)
{
	if ((v1 < 0) || (v1 >= numOfVertexs) || (v2 < 0) || (v2 >= numOfVertexs))
	{
		cout << "Illegal insertion: The vertex doesn't exist!" << endl;
		exit(1);
	}
	Vertex *p = StartVertex;
	for (int i = 0; i < v1; i++)
	{
		p = p->Next;
	}
	Edge *q = p->Out;
	Edge *newEdge = new Edge(GetValueByPos(v2), v2, weight);
	if (!q)
	{
		p->Out = newEdge;
		numOfEdge++;
		return;
	}
	while (q->position != v2&&q->Link)
	{
		q = q->Link;
	}
	if (q->position == v2)
	{
		cout << "Illegal insertion: The Edge has existed!" << endl;
		exit(1);
	}
	if (!q->Link)
	{
		q->Link = newEdge;
		numOfEdge++;
	}
}

void AdjacentTable::InsertEdgeByValue(int value1, int value2, char weight)
{
	int v1 = GetPosByValue(value1), v2 = GetPosByValue(value2);
	InsertEdgeByPos(v1, v2, weight);
}

void AdjacentTable::RemoveAllEdges(void)
{
	Vertex *p = StartVertex;
	for (int i = 0; i<numOfVertexs; i++)
	{
		Edge *q = p->Out;
		while (q)
		{
			p->Out = q->Link;
			delete q;
			q = p->Out;
		}
		p = p->Next;
		if (p == NULL)
			break;
	}
	numOfEdge = 0;
}

void AdjacentTable::Clear(void)
{
	RemoveAllEdges();
	Vertex *p = StartVertex->Next;
	while (p)
	{
		StartVertex->Next = p->Next;
		delete p;
		p = StartVertex->Next;
	}
	numOfVertexs = 1;
}
