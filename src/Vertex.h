#ifndef VERTEX_H_
#define VERTEX_H_
#include "Edge.h"

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
