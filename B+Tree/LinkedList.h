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
#include "B+Tree.h"
using namespace std;

struct LinkNode
{   int key;
    StuDate data;
    struct LinkNode *link;
    LinkNode(){
        this->key=-1;
        data.strName="";
        data.strSex="";
        link=NULL;
    }
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

    bool Search(int x);//搜索结构体中key是x的元素
    bool Remove(int i);
   bool Insert(int key,StuDate a);
    void traverse_list();
    bool ceshi(int x);

};
bool List::Search(int x)
{

    LinkNode*current=first->link;
    while(current!=NULL)
    {
        if(current->key==x)
        {
            cout<<"链表已含有key:"<<x<<" "<<current->data.strName<<" "<<current->data.strSex<<endl;
             return true;
        }
        else
            current=current->link;
    }
    return false;

}
bool List::ceshi(int x)
{

    LinkNode*current=first->link;
    while(current!=NULL)
    {
        if(current->key==x)
        {

             return true;
        }
        else
            current=current->link;
    }
    return false;

}
bool List:: Insert(int keys,StuDate a)
{
    StuDate stu(a);
    if(first->link==NULL)
  {
     LinkNode*pNew;

    pNew = (LinkNode*) malloc(sizeof(LinkNode));
    if(pNew == NULL)
    {
        cout<<"内存分配失败，程序终止"<<endl;
        exit(-1);
    }
    pNew->key=keys;
    pNew->data = stu;
    last->link = pNew;
    last = pNew;
    last->link = NULL;
  }
   else
    {
    if(ceshi(keys))
  {
    return false;
  }
   else{
  LinkNode*pNew;

    pNew = (LinkNode*) malloc(sizeof(LinkNode));
    if(pNew == NULL)
    {
        cout<<"内存分配失败，程序终止"<<endl;
        exit(-1);
    }
    pNew->key=keys;
    pNew->data = stu;
    last->link = pNew;
    last = pNew;
    last->link = NULL;
    }
    }
    return true;

}
void List::traverse_list()
{
    //初始指向第一个有效结点
    LinkNode* p = first->link;
    while(p != NULL)
    {

        cout<<p->key<<" "<<p->data.strName<<" "<<p->data.strSex<<endl;
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
        if(current->key==i)
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
