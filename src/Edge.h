#ifndef _EDGE_H_
#define _EDGE_H_

class Edge
{
public:
	int number;
	int position;
	char weight;
	Edge *Link;
	Edge();
	Edge(int num, int pos, char ch);
};
#endif 
