//
//  edge.hpp
//  regex
//
//  Created by leviathan on 16/7/19.
//  Copyright © 2016年 leviathan. All rights reserved.
//

#ifndef EDGE_H_
#define EDGE_H_

class Edge
{
public:
    Edge():number_(-1),position_(-1),link_(nullptr){};
    Edge(int num, int pos, char ch):number_(num),position_(pos),weight_(ch),link_(nullptr){}
    
    Edge * GetLink(){return link_;}
    void SetLink(Edge *link){link_=link;}
    int GetNumber(){return number_;}
    int GetPosition(){return position_;}
    char GetWeight(){return weight_;}
private:
    Edge * link_;
    int number_;
    int position_;
    char weight_;
};
#endif
