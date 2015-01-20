#include "Vertex.h"
#include <iostream>
using namespace std;
Vertex::Vertex()
{
	number = -1;
	Next = NULL;
	Out = NULL;
}
Vertex::Vertex(int num)
{
	number = num;
	Next = NULL;
	Out = NULL; 
}