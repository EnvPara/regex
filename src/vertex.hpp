//
//  vertex.hpp
//  regex
//
//  Created by leviathan on 16/7/19.
//  Copyright © 2016年 leviathan. All rights reserved.
//

#ifndef VERTEX_H_
#define VERTEX_H_

#include "edge.hpp"

class Vertex
{
public:
    Vertex():next_(nullptr),out_(nullptr),number_(-1){};
    Vertex(int num):next_(nullptr),out_(nullptr),number_(num){};

    ~Vertex(){};
    Edge * GetOutPtr(){return out_;}
    Vertex *GetNextPtr(){return next_;}
    int GetNumber(){return number_;}

    void SetOut(Edge *out){out_=out;}
    void SetNumber(int number){number_=number;}
    void SetNext(Vertex * next){next_=next;}
private:
    int number_;
    Vertex * next_;
    Edge * out_;
};
#endif
