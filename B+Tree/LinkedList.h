//
//  LinkedList2.h
//  B+Tree
//
//  Created by 赵桐 on 2020/8/18.
//  Copyright © 2020 赵桐. All rights reserved.
//

#ifndef LinkedList2_h
#define LinkedList2_h

#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>
#include <cassert>
using namespace std;
#ifndef INSMOD_INF_INR
#define INSMOD_INF_INR
enum InsMod {INF, INR};
#endif
template <typename T>struct LinkNode{
    int key;
    T data;
    LinkNode<T> *link;
    LinkNode(LinkNode<T> *ptr = NULL){
        link = ptr;
    }
    LinkNode(const T &item, LinkNode<T> *ptr = NULL){
        data.strName = item.strName;
        data.strSex = item.strSex;
        link = ptr;
    }
};

template <typename T>class List{
public:
    List(){
        first = new LinkNode<T>;
    }
    List(const T &x){
        first = new LinkNode<T>(x);
    }
    List(List<T> &L);
    ~List(){
        makeEmpty();
        delete first;
    }
    void makeEmpty();
    int Length()const;
    LinkNode<T> *getHead()const{
        return first;
    }
    LinkNode<T> *Search(const T &x);
    LinkNode<T> *Locate(int i);
    bool getData(int i,T&x)const;
    void setData(int i, T &x);
    bool Insert(int i, T &x);
    bool Remove(int i, T &x);
    bool IsEmpty()const{
        return (first->link == NULL)?true:false;
    }
    bool IsFull()const{
        return false;
    }
    void Sort();
    void Inverse();
    void input(T endTag, InsMod im = INR);
    void output();
    List<T> &operator = (List<T> &L);
    friend ostream& operator << (ostream &out, List<T> &L){
        LinkNode<T> *current = L.first->link;
        while (current){
            out << current->data <<'\t';
            current = current->link;
        }
        out<<endl;
        return out;
    }
    friend istream& operator >> (istream &in, List<T> &L){//“—∏ƒ
        LinkNode<T> *newNode,*last;
        T val;
        L.makeEmpty();
        last = L.first;
        while (!in.eof()){
            in >> val;
            newNode = new LinkNode<T>(val);
            assert(newNode);
            last->link = newNode;
            last = newNode;
        }
        last->link = NULL;
        return in;
    }
protected:
    LinkNode<T> *first;
    void inputFront(T endTag);
    void inputRear(T endTag);
};

template <typename T>List<T>::List(List<T> &L){
    T value;
    LinkNode<T> *srcptr = L.first();
    LinkNode<T> *destptr = first = new LinkNode<T>;
    while (srcptr->link){
        value = srcptr->link->data;
        destptr->link = new LinkNode<T>(value);
        destptr = destptr->link;
        srcptr = srcptr->link;
    }
    destptr->link = NULL;
}

template <typename T>void List<T>::makeEmpty(){
    LinkNode<T> *q;
    while (first->link)    {
        q = first->link;
        first->link = q->link;
        delete q;
    }
}

template <typename T>int List<T>::Length()const{
    LinkNode<T> *p = first->link;
    int count = 0;
    while (p){
        p = p->link;
        count++;
    }
    return count;
}

template <typename T>LinkNode<T> *List<T>::Search(const T &x){
    LinkNode<T> *current = first->link;
    while (current && current->data != x){
        current = current->link;
    }
    return current;
}

template <typename T>LinkNode<T> *List<T>::Locate(int i){//∏ƒ
    if (i < 0)    return NULL;
    LinkNode<T> *current = first;
   
    while (current && current->key != i){
        current = current->link;
    }
    return current;
}

template <typename T>bool List<T>::getData(int i,T&x)const{
    if (i <= 0)    return NULL;
    LinkNode<T> *current = Locate(i);
    if (!current)    return false;
    else{
        x=current->data;
        return true;
    }
}

template <typename T>void List<T>::setData(int i, T &x){
    if (i <= 0)    return;
    LinkNode<T> *current = Locate(i);
    if (!current)    return;
    else    current->data = x;
}

template <typename T> bool List<T>::Insert(int i, T &x){
    LinkNode<T> *current = Locate(i);
    if (current!=NULL)    return false;
    LinkNode<T> *newNode = new LinkNode<T>(x);
    newNode->key=i;
    if (!newNode){
        cerr << "Memory allocating error!" << endl;
        exit(1);
    }
    newNode->link = first->link;
    first->link = newNode;
    return true;
}

template <typename T>bool List<T>::Remove(int i, T &x){
    LinkNode<T> *current = Locate(i-1);
    if (!current || !current->link)    return false;
    LinkNode<T> *del = current->link;
    current->link = del->link;
    x = del->data;
    delete del;
    return true;
}

template <typename T> void List<T>::output(){
    LinkNode<T> *current = first->link;
    while (current){
        cout << current->key<<" "<<current->data.strName<<" " <<current->data.strSex<<" "<< endl;
        current = current->link;
    }
}

template <typename T> List<T> &List<T>::operator = (List<T> &L){//∏ƒ
    T value;
    LinkNode<T> *destptr=first,*srcptr = L.first;
    makeEmpty();
    while (srcptr->link)
    {
        value = srcptr->link->data;
        destptr->link = new LinkNode<T>(value);
        destptr = destptr->link;
        srcptr = srcptr->link;
    }
    destptr->link = NULL;
    return *this;
}

template <typename T>void List<T>::input(T endTag, InsMod im){
    if (im == INF)    inputFront(endTag);
    else    inputRear(endTag);
}

template <typename T>void List<T>::inputFront(T endTag){//∏ƒ£¨ÃÌº”
    LinkNode<T> *newNode;
    T val;
    cin >> val;
    while ( val != endTag){
        newNode = new LinkNode<T>(val);
        if (!newNode){
            cerr << "Memory allocating error!" << endl;
            exit(1);
        }
        newNode->link = first->link;
        first->link = newNode;
        cin >> val;
    }
}

template <typename T>void List<T>::inputRear(T endTag){//∏ƒ
    LinkNode<T> *newNode, *last=first;
    T val;
    while(last->link!=NULL) last=last->link;
    cin >> val;
    while (val != endTag){
        newNode = new LinkNode<T>(val);
        if (!newNode){
            cerr << "Memory allocating error!" << endl;
            exit(1);
        }
        last->link = newNode;
        last = newNode;
        cin >> val;
    }
    last->link = NULL;
}

template <typename T>void List<T>::Sort(){
}

template <typename T>void List<T>::Inverse(){
    LinkNode<T> *h, *p, *pr;
    h = NULL;
    p = first->link;
    while (p){
        pr = h;
        h = p;
        p = h->link;
        h->link = pr;
    }
    first->link = h;
}
#endif

#endif /* LinkedList2_h */
