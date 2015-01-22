#ifndef _EDGE_H_
#define _EDGE_H_
// 定义邻接表的边表类
class Edge
{
public:
	int number;
	int position;
	char weight;
	Edge *Link;
	Edge();
	Edge(int num, int pos, char ch);//带参数的构造函数
};
#endif 