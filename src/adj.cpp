//
//  adj.cpp
//  regex
//
//  Created by leviathan on 16/7/19.
//  Copyright © 2016年 leviathan. All rights reserved.
//

#include "adj.hpp"
#include <iostream>
using namespace std;


AdjacentTable::~AdjacentTable()
{
    Vertex *p=startVertex_;
    for (int i = 0; i < numOfVertexs_; i++)
    {
        Edge *q = p->GetOutPtr();
        while (q)
        {
            p->SetOut(q->GetLink());
            delete q;
            q = p->GetOutPtr();
        }
        p = p->GetNextPtr();
    }
    delete startVertex_;
}

int AdjacentTable::GetValueByPos(int pos) const
{
    if ((pos >= 0) && (pos < numOfVertexs_))
    {
        Vertex *p = startVertex_;
        for (int i = 0; i < pos; i++)
        {
            p = p->GetNextPtr();
        }
        return p->GetNumber();
    }
    else
        return -1;
}

int AdjacentTable::GetPosByValue(int value) const
{
    Vertex *p =startVertex_;
    for (int i = 0; i < numOfVertexs_; i++)
    {
        if (p->GetNumber() == value)
            return i;
        p = p->GetNextPtr();
    }
    return -1;
}

char AdjacentTable::GetWeightByPos(int v1, int v2) const
{
    if ((v1 >= 0) && (v2 >= 0) && (v1 < numOfVertexs_) && (v2 < numOfVertexs_))
    {
        Vertex *p = startVertex_;
        for (int i = 0; i < v1; i++)
        {
            p = p->GetNextPtr();
        }
        Edge *q = p->GetOutPtr();
        while (q)
        {
            if (q->GetPosition() == v2)
                return q->GetWeight();
            else q = q->GetLink();
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
    if (pos < 0 || pos >= numOfVertexs_)
    {
        cout << "illegal setting" << endl;
        exit(1);
    }
    Vertex *p = startVertex_;
    for (int i = 0; i < pos; i++)
    {
        p = p->GetNextPtr();
    }
    p->SetNumber(value);
}

void AdjacentTable::InsertVertex(int value)
{
    int pos = GetPosByValue(value);
    if (pos >= 0 && pos < numOfVertexs_)
    {
        cout << "illegal setting" << endl;
        exit(1);
    }
    Vertex *p = startVertex_;
    while (p->GetNextPtr())
        p = p->GetNextPtr();
    Vertex *newVertex = new Vertex(value);
    p->SetNext(newVertex);
    numOfVertexs_++;
}

void AdjacentTable::InsertEdgeByPos(int v1, int v2, char weight)
{
    if ((v1 < 0) || (v1 >= numOfVertexs_) || (v2 < 0) || (v2 >= numOfVertexs_))
    {
        cout << "Illegal insertion: The vertex doesn't exist!" << endl;
        exit(1);
    }
    Vertex *p = startVertex_;
    for (int i = 0; i < v1; i++)
    {
        p = p->GetNextPtr();
    }
    Edge *q = p->GetOutPtr();
    Edge *newEdge = new Edge(GetValueByPos(v2), v2, weight);
    if (!q)
    {
        p->SetOut(newEdge);
        numOfEdge_++;
        return;
    }
    while (q->GetPosition()== v2&&q->GetLink())
    {
        q = q->GetLink();
    }
    if (q->GetPosition() == v2)
    {
        cout << "Illegal insertion: The Edge has existed!" << endl;
        exit(1);
    }
    if (!q->GetLink())
    {
        q->SetLink(newEdge);
        numOfEdge_++;
    }
}

void AdjacentTable::InsertEdgeByValue(int value1, int value2, char weight)
{
    int v1 = GetPosByValue(value1), v2 = GetPosByValue(value2);
    InsertEdgeByPos(v1, v2, weight);
}

void AdjacentTable::RemoveAllEdges(void)
{
    Vertex *p = startVertex_;
    for (int i = 0; i<numOfVertexs_; i++)
    {
        Edge *q = p->GetOutPtr();
        while (q)
        {
            p->SetOut(q->GetLink());
            delete q;
            q = p->GetOutPtr();
        }
        p = p->GetNextPtr();
        if (p == NULL)
            break;
    }
    numOfEdge_ = 0;
}

void AdjacentTable::Clear(void)
{
    RemoveAllEdges();
    Vertex *p = startVertex_->GetNextPtr();
    while (p)
    {
        startVertex_->SetNext(p->GetNextPtr());
        delete p;
        p = startVertex_->GetNextPtr();
    }
    numOfVertexs_ = 1;
}

