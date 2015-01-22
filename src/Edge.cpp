#include "Edge.h"
#include <iostream>
using namespace std;
// 定义邻接表的边表类
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