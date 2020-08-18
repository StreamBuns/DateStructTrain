//
//  LinkedList.h
//  B+Tree
//
//  Created by 赵桐 on 2020/8/17.
//  Copyright © 2020 赵桐. All rights reserved.
//

#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>
#include<time.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <cstring>
#include <unistd.h>

using namespace std;
struct StuDate2{
{
    int key;
    string name;
    string sex;
    Set(int key,string name , string sex){
        this->key=key;
        this->name=name;
        this->sex=sex;
    }

};
struct LinkNode
{
    student data;
    struct LinkNode *link;
};

class List
{
public:
    LinkNode*first;
    LinkNode*last;
    List()
    {
        last=first=new LinkNode;
    }

    LinkNode*Search(int x);//搜索结构体中key是x的元素
    bool Remove(int i);
    LinkNode*Insert(student a);
    void traverse_list();

};
LinkNode*List::Search(int x)
{

    LinkNode*current=first->link;
    while(current!=NULL)
    {
        if(current->data.key==x)
        {
            cout<<current->data.name<<" "<<current->data.sex;
            break;
        }
        else
            current=current->link;
    }
    
}
bool List:: Insert(student a)
{

    LinkNode*pNew;

    pNew = (LinkNode*) malloc(sizeof(LinkNode));
    if(pNew == NULL)
    {
        cout<<"内存分配失败，程序终止"<<endl;
        exit(-1);
    }

    pNew->data = a;
    last->link = pNew;
    last = pNew;
    last->link = NULL;
    return true;
}
void List::traverse_list()
{
    //初始指向第一个有效结点
    LinkNode* p = first->link;
    while(p != NULL)
    {

        cout<<p->data.key<<" "<<p->data.name<<" "<<p->data.sex<<endl;
        p = p->link;
    }

}
bool List::Remove(int i)
{
    LinkNode*current=first;
    if(current!=NULL||current->link==NULL)
        return false;
    while(current!=NULL)
    {
        if(current->data.key==i)
        {
            LinkNode*p=current;
            current=p->link;
            delete p;
            return true;
        }
        current=current->link;
    }
    return true;
}



#endif
