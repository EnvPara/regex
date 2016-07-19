//
//  main.cpp
//  regex
//
//  Created by leviathan on 16/7/19.
//  Copyright © 2016年 leviathan. All rights reserved.
//


#include <iostream>
#include "dfa.hpp"
using namespace std;
int main()
{
    DFA dfa;
    dfa.InputRegex();
    dfa.InsertNode();
    dfa.RegextoPost();
    dfa.GetEdgeNumber();
    dfa.Thompson();
    dfa.NFAtoDFA();
    dfa.Hopcroft();
    dfa.InputString();
    dfa.Match();
    cout<<"quit!"<<endl;
    return 0;
}
