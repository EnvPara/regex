#include "Edge.h"
#include <iostream>
using namespace std;

Edge::Edge()
{
	number = -1;
	position = -1;
	Link = NULL;
}
Edge::Edge(int num, int pos, char ch)
{
	number = num;
	position = pos;
	weight = ch;
	Link = NULL;
}
