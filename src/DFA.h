#ifndef _DFA_H
#define _DFA_H
#include <string>
using namespace std;
class DFA
{
public:
	char *Regex;
	char *RegexPost;
	void InputRegex();
	void InsertNode();
	void RegextoPost();
	int Precedence(char symbol);
	void GetEdgeNumber();
	void Thompson();//用Thompson构造法构造NFA
	int EdgeNumber;
	char *Edge;
};
#endif