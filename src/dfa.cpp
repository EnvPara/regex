//
//  dfa.cpp
//  regex
//
//  Created by leviathan on 16/7/19.
//  Copyright © 2016年 leviathan. All rights reserved.
//


#include <string>
#include <stack>
#include <iostream>

#include "dfa.hpp"
#include "edge.hpp"
#include "vertex.hpp"
using namespace std;


template <class T>
LinkStack<T>::LinkStack()
{
    top = NULL;
}


template <class T>
LinkStack<T>::~LinkStack()
{
    Clear();
}

template <class T>
bool LinkStack<T>::IsEmpty()
{
    return(!top);
}

template <class T>
int LinkStack<T>::Length()
{
    StackNode<T> *temp =top;
    int length = 0;
    while (temp)
    {
        temp = temp->next;
        length++;
    }
    return length;
}

template <class T>
void LinkStack<T>::Push(const T &item)
{
    top = new StackNode<T>(item, top);
}

template <class T>
T LinkStack<T>::Pop()
{
    if (!IsEmpty())
    {
        StackNode<T> *temp = top;
        top = top->next;
        T value = temp->data;
        delete temp;
        return value;
    }
    else
    {
        cout << "The Stack is Empty" << endl;
        exit(1);
    }
}

template<class T>
T LinkStack<T>::GetTop()
{
    if (!IsEmpty())
        return top->data;
    else
    {
        cout << "The Stack is Empty" << endl;
        exit(1);
    }
}

template<class T>
void LinkStack<T>::Clear()
{
    StackNode<T> *temp;
    while (top)
    {
        temp = top;
        top = top->next;
        delete temp;
    }
}

DFA::DFA()
{
    regex_ = new char[127];
    regexPost_ = new char[127];
    edgeNum_ = new char[127];
    edgeNumber_ = 0;
    dfaStatesNumber = 0;
    nfaStatesNumber_ = 0;
    nfaTable_= new AdjacentTable();
    dFATable_ = new AdjacentTable();
}

DFA::~DFA()
{
    delete[] regex_;
    delete[] regexPost_;
    delete[] edgeNum_;
    //delete[] AcceptStates;
    nfaTable_->Clear();
    dFATable_->Clear();
    delete nfaTable_;
    delete dFATable_;
}

void DFA::InputRegex()
{
    cout << "First step:please enter regex expression:\n";
    cin.getline(regex_,127);
}

void DFA::InsertNode()
{
    int i = 0, j, len = int(strlen(regex_));
    int length = len;
    len--;
    while (len--)
    {
        if (((regex_[i] != '(' && regex_[i] != '.' && regex_[i] != '|')
             || regex_[i] == ')' || regex_[i] == '*')
            && (regex_[i + 1] != ')' && regex_[i + 1] != '.' && regex_[i + 1] != '|' && regex_[i + 1] != '*'))
        {
            for (j = length; j >i; j--)
            {
                regex_[j + 1] = regex_[j];
            }
            regex_[i + 1] = '.';
            length++;
            regex_[length] = '\0';
            i++;
        }
        i++;
    }
    cout << endl;
    cout << "Regex expression:\n";
    cout << regex_ << endl;
    cout << "String length: " << length << endl;
}

int DFA::Precedence(char symbol)
{
    int priority;
    switch (symbol)
    {
        case '|':priority = 1; break;
        case '.':priority = 2; break;
        case '*':priority = 3; break;
        default:priority = 0; break;
    }
    return priority;
}

void DFA::RegextoPost()
{
    int i = 0, j = 0;
    char ch, cl;
    strcpy(regexPost_, "\0");
    LinkStack<char> *Value = new LinkStack<char>();
    Value->Clear();
    ch = regex_[i];
    Value->Push('#');
    ch = regex_[i];
    while (ch != '\0')
    {
        if (ch == '(')
        {
            Value->Push(ch);
            ch = regex_[++i];
        }
        else if (ch == ')')
        {
            while (Value->GetTop() != '(')
            {
                regexPost_[j++] = Value->Pop();
            }
            Value->Pop();
            ch = regex_[++i];
        }
        else if ((ch == '|') || (ch == '*') || (ch == '.'))
        {
            cl = Value->GetTop();
            while (Precedence(cl) >= Precedence(ch))
            {
                regexPost_[j++] = cl;
                Value->Pop();
                cl = Value->GetTop();
            }
            Value->Push(ch);
            ch = regex_[++i];
        }
        else
        {
            regexPost_[j++] = ch;
            ch = regex_[++i];
        }
    }
    ch = Value->Pop();
    while ((ch == '|') || (ch == '*') || (ch == '.'))
    {
        regexPost_[j++] = ch;
        ch = Value->Pop();
    }
    regexPost_[j] = '\0';
    Value->Clear();
    delete Value;
    cout << "\nThird step:transform RegexPost\n"
    << regexPost_ << "\n"
    << "String length :" << strlen(regexPost_);
}

void DFA::GetEdgeNumber()
{
    int i = 0, j;
    edgeNumber_ = 0;
    while (regexPost_[i] != '\0')
    {
        if (regexPost_[i] == '.' || regexPost_[i] == '|' || regexPost_[i] == '*')
        {
            i++;
            continue;
        }
        for (j = 0; j < edgeNumber_; j++)
        {
            if (regexPost_[i] == edgeNum_[j])
                break;
        }
        if (j == edgeNumber_)
        {
            edgeNum_[edgeNumber_] = regexPost_[i];
            edgeNumber_++;
        }
        i++;
    }
    edgeNum_[edgeNumber_] = '\0';
    cout << endl;
    cout << "\nFourth step:get char list\n";
    for (i = 0; i<edgeNumber_; i++)
    {
        cout << edgeNum_[i] << ' ';
    }
    cout << "\nchar numbers: " << edgeNumber_ << endl;
    cout << "\n\n------------------------" << endl;
}

void DFA::Thompson()
{
    int i, j;
    char ch;
    int s1, s2;
    LinkStack<int >*States = new LinkStack<int >();
    States->Clear();
    if (strlen(regexPost_) < 1)
    {
        cout << "No Regex Expression Find" << endl;
        exit(1);
    }
    i = 1; j = 0;
    ch = regexPost_[j];
    while (ch != '\0')
    {
        if (ch == '.')
        {
            s2 = States->Pop();
            int Ex1 = States->Pop();
            int Ex2 = States->Pop();
            s1 = States->Pop();
            nfaTable_->InsertEdgeByValue(Ex2, Ex1, '~');
            States->Push(s1);
            States->Push(s2);
        }
        else if (ch == '*')
        {
            s2 = States->Pop();
            s1 = States->Pop();
            nfaTable_->InsertVertex(i);
            nfaTable_->InsertVertex(i + 1);
            nfaTable_->InsertEdgeByValue(i, i + 1, '~');
            nfaTable_->InsertEdgeByValue(s2, s1, '~');
            nfaTable_->InsertEdgeByValue(i, s1, '~');
            nfaTable_->InsertEdgeByValue(s2, i + 1, '~');
            s1 = i;
            s2 = i + 1;
            States->Push(s1);
            States->Push(s2);
            i += 2;
        }
        else if (ch == '|')
        {
            s2 = States->Pop();
            int temp1 = States->Pop();
            int temp2 = States->Pop();
            s1 = States->Pop();
            nfaTable_->InsertVertex(i);
            nfaTable_->InsertVertex(i + 1);
            nfaTable_->InsertEdgeByValue(i, s1, '~');
            nfaTable_->InsertEdgeByValue(i, temp1, '~');
            nfaTable_->InsertEdgeByValue(temp2, i + 1, '~');
            nfaTable_->InsertEdgeByValue(s2, i + 1, '~');
            s1 = i;
            s2 = i + 1;
            States->Push(s1);
            States->Push(s2);
            i += 2;
        }
        else
        {
            nfaTable_->InsertVertex(i);
            nfaTable_->InsertVertex(i + 1);
            nfaTable_->InsertEdgeByValue(i, i + 1, ch);
            s1 = i;
            s2 = i + 1;
            States->Push(s1);
            States->Push(s2);
            i += 2;
        }
        j++;
        ch = regexPost_[j];
    }
    s2 = States->Pop();
    s1 = States->Pop();
    nfaStatesNumber_ = s2 + 1;
    delete States;
}

void SetNFANodeAll(int(*A)[100])
{
    for (int i = 0; i < 101; i++)
        for (int j = 0; j < 101; j++)
            A[i][j] = 0;
}

int Judge(int States, int Jud[][100])
{
    int i, j, sum;
    i = 2;
    while (Jud[i][0] != 0)
    {
        sum = 0;
        j = 0;
        while (Jud[i][j] != 0)
        {
            if (Jud[States][j] == Jud[i][j])
                sum++;
            j++;
        }
        if (sum == j)
            return i;
        i++;
    }
    return States;
}
void SetAcceptStates(int *States)
{
    for (int i = 0; i <= 500; i++)
        States[i] = 0;
}

void DFA::NFAtoDFA()
{
    int States;
    //, update = 0;
    int VertexNode[1001] = { 0 };
    LinkStack<int> DFAStates;
    LinkStack<int>NFANode;
    int NFANodeAll[100][100];
    SetNFANodeAll(NFANodeAll);
    int Pointer = 0;
    for (int i = 0; i <=nfaTable_->GetNumOfVertexs(); i++)
        VertexNode[i] = 0;
    States = 1;
    dFATable_->InsertVertex(1);

    for (int i = 0; i < edgeNumber_; i++)
    {
        char weight = edgeNum_[i];
        Vertex *P =nfaTable_->GetStartVertex();
        for (int j = 0; j < States; j++)
            P = P->GetNextPtr();
        if (P->GetOutPtr()->GetLink() == NULL)
        {
            if (P->GetOutPtr()->GetWeight()== weight&&VertexNode[P->GetOutPtr()->GetPosition()] == 0)
                NFANode.Push(P->GetOutPtr()->GetPosition());
            VertexNode[P->GetOutPtr()->GetPosition()] = 1;
        }
        if (P->GetOutPtr()->GetLink() != NULL)
        {
            if (P->GetOutPtr()->GetWeight()== weight&&VertexNode[P->GetOutPtr()->GetPosition()] == 0)
                NFANode.Push(P->GetOutPtr()->GetPosition());
            VertexNode[P->GetOutPtr()->GetPosition()] = 1;
            Edge *PLink = P->GetOutPtr()->GetLink();
            while (PLink != NULL)
            {
                if (P->GetOutPtr()->GetWeight()== weight&&VertexNode[P->GetOutPtr()->GetPosition()] == 0)
                    NFANode.Push(P->GetOutPtr()->GetPosition());
                VertexNode[P->GetOutPtr()->GetPosition()] = 1;
                PLink = PLink->GetLink();
            }
        }
        if (NFANode.IsEmpty())
            continue;
        States++;
        DFAStates.Push(States);
        while (!NFANode.IsEmpty())
        {
            int Visual = NFANode.GetTop();
            NFANode.Pop();
            NFANodeAll[States][Pointer] = Visual;
            Pointer++;
            P =nfaTable_->GetStartVertex();
            for (int j = 0; j < Visual; j++)
                P = P->GetNextPtr();
            if (P->GetOutPtr()&&P->GetOutPtr()->GetLink()== NULL)
            {
                if (P->GetOutPtr()->GetWeight() == '~'&&VertexNode[P->GetOutPtr()->GetPosition()] == 0)
                    NFANode.Push(P->GetOutPtr()->GetPosition());
                VertexNode[P->GetOutPtr()->GetPosition()] = 1;
            }
            else if (P->GetOutPtr())
            {
                if (P->GetOutPtr()->GetWeight() == '~'&&VertexNode[P->GetOutPtr()->GetPosition()] == 0)
                    NFANode.Push(P->GetOutPtr()->GetPosition());
                VertexNode[P->GetOutPtr()->GetPosition()] = 1;
                Edge *LinkNode = P->GetOutPtr()->GetLink();
                while (LinkNode != NULL)
                {
                    if (LinkNode->GetWeight() == '~'&&VertexNode[LinkNode->GetPosition()] == 0)
                        NFANode.Push(LinkNode->GetPosition());
                    VertexNode[P->GetOutPtr()->GetPosition()] = 1;
                    LinkNode = LinkNode->GetLink();
                }
            }
        }
        dFATable_->InsertVertex(States);
        dFATable_->InsertEdgeByValue(1, States, edgeNum_[i]);
    }

    while (!DFAStates.IsEmpty())
    {
        nfaStatesNumber_ = DFAStates.GetTop();
        DFAStates.Pop();
        for (int j = 0; j < edgeNumber_; j++)
        {
            int i = 0;
            char weight = edgeNum_[j];
            while (NFANodeAll[nfaStatesNumber_][i] != 0)
            {
                int VertexNode[1001] = { 0 };
                Vertex *P =nfaTable_->GetStartVertex();
                for (int k = 0; k < NFANodeAll[nfaStatesNumber_][i]; k++)
                    P = P->GetNextPtr();
                i++;
                if (P->GetOutPtr() == NULL)
                    continue;
                if (P->GetOutPtr()->GetLink() == NULL)
                {
                    if (P->GetOutPtr()->GetWeight()== weight&&VertexNode[P->GetOutPtr()->GetPosition()] == 0)
                        NFANode.Push(P->GetOutPtr()->GetPosition());
                    VertexNode[P->GetOutPtr()->GetPosition()] = 1;
                }
                if (P->GetOutPtr()->GetLink()!= NULL)
                {
                    if (P->GetOutPtr()->GetWeight() == weight&&VertexNode[P->GetOutPtr()->GetPosition()] == 0)
                        NFANode.Push(P->GetOutPtr()->GetPosition());
                    VertexNode[P->GetOutPtr()->GetPosition()] = 1;
                    Edge *PLink = P->GetOutPtr()->GetLink();
                    while (PLink != NULL)
                    {
                        if (P->GetOutPtr()->GetWeight()== weight&&VertexNode[P->GetOutPtr()->GetPosition()] == 0)
                            NFANode.Push(P->GetOutPtr()->GetPosition());
                        VertexNode[P->GetOutPtr()->GetPosition()] = 1;
                        PLink = PLink->GetLink();
                    }
                }
                if (NFANode.IsEmpty())
                    continue;
                States++;
                Pointer = 0;
                while (!NFANode.IsEmpty())
                {
                    int Visual = NFANode.GetTop();
                    NFANode.Pop();
                    NFANodeAll[States][Pointer] = Visual;
                    Pointer++;
                    P = nfaTable_->GetStartVertex();
                    for (int j = 0; j < Visual; j++)
                        P = P->GetNextPtr();
                    if (P->GetOutPtr()&&P->GetOutPtr()->GetLink()== NULL)
                    {
                        if (P->GetOutPtr()->GetWeight() == '~'&&VertexNode[P->GetOutPtr()->GetPosition()] == 0)
                            NFANode.Push(P->GetOutPtr()->GetPosition());
                        VertexNode[P->GetOutPtr()->GetPosition()] = 1;
                    }
                    else if (P->GetOutPtr())
                    {
                        if (P->GetOutPtr()->GetWeight()== '~'&&VertexNode[P->GetOutPtr()->GetPosition()] == 0)
                            NFANode.Push(P->GetOutPtr()->GetPosition());
                        VertexNode[P->GetOutPtr()->GetPosition()] = 1;
                        Edge *LinkNode = P->GetOutPtr()->GetLink();
                        while (LinkNode != NULL)
                        {
                            if (LinkNode->GetWeight()== '~'&&VertexNode[LinkNode->GetPosition()] == 0)
                                NFANode.Push(LinkNode->GetPosition());
                            VertexNode[P->GetOutPtr()->GetPosition()] = 1;
                            LinkNode = LinkNode->GetLink();
                        }

                    }
                }
                int Sign = States;
                States = Judge(States, NFANodeAll);
                if (States == Sign)
                {
                    dFATable_->InsertVertex(States);
                    DFAStates.Push(States);
                }
                dFATable_->InsertEdgeByValue(nfaStatesNumber_, States, edgeNum_[j]);
                States = Sign;
            }
        }
    }
    nfaStatesNumber_ = States;
    dfaStatesNumber = dFATable_->GetNumOfVertexs() - 1;

    dFATable_->SetStartVertex(dFATable_->GetStartVertex()->GetNextPtr());
    nfaTable_->SetStartVertex(nfaTable_->GetStartVertex()->GetNextPtr());

    SetAcceptStates(NFAAcceptStates);
    SetAcceptStates(DFAAcceptStates);
    Vertex *P = nfaTable_->GetStartVertex();

    for (int i = 1; i <nfaTable_->GetNumOfVertexs(); i++)
    {
        if (P->GetOutPtr() == NULL)
        {
            NFAAcceptStates[i] = i;
        }
        P = P->GetNextPtr();
    }

    for (int i = 2; i <= States; i++)
    {
        for (int j = 0; j <= nfaTable_->GetNumOfVertexs(); j++)
        {
            int k = 0;
            while (NFANodeAll[i][k] != 0)
            {
                for (int n = 0; n <= nfaTable_->GetNumOfVertexs(); n++)
                {
                    if (NFAAcceptStates[n] == NFANodeAll[i][k])
                        DFAAcceptStates[i] = i;
                }
                k++;
            }
        }
    }
    int Vol = 0;
    for (int i = 0; i <= States; i++)
    {
        if (DFAAcceptStates[i] != 0)
            Vol = Judge(DFAAcceptStates[i], NFANodeAll);
        if (Vol != DFAAcceptStates[i])
            DFAAcceptStates[i] = 0;
    }
}

void InitializationDFAStates(int(*A)[101],char(*B)[101])
{
    for (int i = 0; i < 101; i++)
        for (int j = 0; j < 101; j++)
        {
            A[i][j] = 0;
            B[i][j] = '$';
        }
}
void DFA::Hopcroft()
{

}

void DFA::InputString()
{
    cout << endl;
    cout << "Please input match string: " << endl;
    cin >> input_;
    cout << "Match string:         " << input_ << endl;
}

void DFA::Match()
{
    int Position = 0, Sign = 0;
    matchOut_= input_;
    Vertex *P = dFATable_->GetStartVertex();
    for (int i = 0; i < input_.length(); i++)
    {
        if (P->GetOutPtr() == NULL)
        {
            P = dFATable_->GetStartVertex();
            continue;
        }
        if (P->GetOutPtr()->GetLink()== NULL)
        {
            if (P->GetOutPtr()->GetWeight()== input_[i])
            {
                Position = P->GetOutPtr()->GetPosition();
                P = dFATable_->GetStartVertex();
                for (int j = 1; j < Position; j++)
                    P = P->GetNextPtr();
                if (DFAAcceptStates[Position] == Position)
                {
                    for (int j = Sign; j <= i; j++)
                        matchOut_[j] = input_[j];
                    Sign = i + 1;
                }
            }
            else
            {
                if (P == dFATable_->GetStartVertex())
                {
                    for (int j = Sign; j <= i; j++)
                        matchOut_[j] = '#';
                    P = dFATable_->GetStartVertex();
                    Sign = i + 1;
                }
                else
                {
                    for (int j = Sign; j < i; j++)
                        matchOut_[j] = '#';
                    P = dFATable_->GetStartVertex();
                    Sign = i;
                    i--;
                }
            }
        }
        else
        {
            if (P->GetOutPtr()->GetWeight() == input_[i])
            {
                matchOut_[i] = input_[i];
                Position = P->GetOutPtr()->GetPosition();
                P = dFATable_->GetStartVertex();
                for (int j = 1; j < Position; j++)
                    P = P->GetNextPtr();
                if (DFAAcceptStates[Position] == Position)
                {
                    for (int j = Sign; j <= i; j++)
                        matchOut_[j] = input_[j];
                    Sign = i + 1;
                }
                continue;
            }
            Edge * Plink = new Edge;
            Plink = P->GetOutPtr()->GetLink();
            while (Plink != NULL)
            {
                if (Plink->GetWeight()== input_[i])
                {
                   matchOut_[i] = input_[i];
                    Position = Plink->GetPosition();
                    P = dFATable_->GetStartVertex();
                    for (int j = 1; j < Position; j++)
                        P = P->GetNextPtr();
                    if (DFAAcceptStates[Position] == Position)
                    {
                        for (int j = Sign; j <= i; j++)
                            matchOut_[j] = input_[j];
                        Sign = i + 1;
                    }
                    break;
                }
                else
                    Plink = Plink->GetLink();
            }
            if (Plink == NULL)
            {
                P = dFATable_->GetStartVertex();
                for (int j = Sign; j < i; j++)
                    matchOut_[j] = '#';
                Sign = i;
                i--;
            }

        }
    }
    for (int i = Sign; i < input_.length(); i++)
        matchOut_[i] = '#';
    cout << "Regex expression:     " << regex_ << endl;
    cout << "Input match string:   " << input_ << endl;
    cout << "Matchout:             " << matchOut_ << endl;
    cout<<endl;
}
