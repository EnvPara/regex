#ifndef _VERTEX_H
#define _VERTEX_H
#include "Edge.h"
// �����ڽӱ�Ķ�����
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