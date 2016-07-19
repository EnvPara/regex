//
//  dfa.hpp
//  regex
//
//  Created by leviathan on 16/7/19.
//  Copyright © 2016年 leviathan. All rights reserved.
//

#ifndef DFA_H_
#define DFA_H_

#include <string.h>
#include "adj.hpp"

using namespace std;

template <class T>
class LinkStack;


template <class T>
class StackNode
{
    friend class LinkStack<T>;
private:
    T data;
    StackNode<T> *next;
    StackNode(T item = 0, StackNode<T> *p = NULL)
    {
        data = item;
        next = p;
    }
};

// 定义链式栈类
template <class T>
class LinkStack
{
private:
    StackNode<T> *top;
public:
    LinkStack();
    ~LinkStack();
    bool IsEmpty();
    int Length();
    void Push(const T &item);
    T Pop();
    T GetTop();
    void Clear();
};

class DFA
{
public:
    DFA();
    ~DFA();
    void InputRegex();
    void InsertNode();
    void RegextoPost();
    int Precedence(char symbol);
    void GetEdgeNumber();
    void Thompson();
    void NFAtoDFA();
    void Hopcroft();
    void GetAcceptState();
    int NFAAcceptStates[500];
    int DFAAcceptStates[500];
    int NFANodeAll[100][100];
    int JudgeVertex(char a);
    void InputString();
    void Match();
    char DFAStates[101][101];
    int MiniDFAStates[101][101];
    void SetDFAStates();
private:
    char * regex_;
    char * regexPost_;
    AdjacentTable * nfaTable_;
    AdjacentTable * dFATable_;
    int nfaStatesNumber_;
    int dfaStatesNumber;

    int edgeNumber_;

    char * edgeNum_;
    string input_;
    string matchOut_;
};
#endif

