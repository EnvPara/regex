#include <iostream>
#include "DFA.h"
using namespace std;
int main()
{
    DFA DFA_each;
    DFA_each.InputRegex();
    DFA_each.InsertNode();
    DFA_each.RegextoPost();
    DFA_each.GetEdgeNumber();
    DFA_each.Thompson();
    DFA_each.NFAtoDFA();
    DFA_each.Hopcroft();
    DFA_each.InputString();
    DFA_each.Match();
    cout<<"quit!        "<<endl;
    return 0;
}
