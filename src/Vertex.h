#ifndef _VERTEX_H
#define _VERTEX_H
#include "Edge.h"
// 定义邻接表的顶点类
class Vertex
{
public:
	int number;
	Vertex *Next;
	Edge *Out;
	Vertex();
	Vertex(int num);
};
#endif