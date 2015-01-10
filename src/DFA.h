#ifndef _DFA_H
#define _DFA_H
#include <string>
using namespace std;
class DFA
{
public:
	string Regex;
	void InputRegex();
	void InsertNode();
	void RegextoPost();
};
#endif