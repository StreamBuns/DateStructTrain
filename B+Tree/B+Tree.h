//
//  B+Tree.h
//  B+Tree
//
//  Created by 赵桐 on 2020/8/11.
//  Copyright © 2020 赵桐. All rights reserved.
//

#ifndef B_Tree_h
#define B_Tree_h


#define MaxValue 2000000
#define m 4
#include <iostream>
using namespace std;
struct BPTreeNode
{
    int n; //关键码的数量
    BPTreeNode * parent;//父结点指针
    int key[m+1];//Key[0]未用
    BPTreeNode * ptr[m+1];//子树结点指针数组，ptr[m]在一出事使用
    BPTreeNode * right;//B+树叶结点指向右边相邻叶结点
    int * recptr[m+1];//每个索引项中指向数据区相应记录起始地址的指针
    BPTreeNode(){
        n=0;
        parent=NULL;
        for(int i=1;i<=m+1;i++){
            key[i]=MaxValue;
            ptr[i-1]=NULL;
        }
//        ptr[m+1]=NULL;
        right = NULL;
    }
};

struct Triple
{
    BPTreeNode * r;//节点地址指针
    int i,tag;
    //节点中关键码序号i
    //tag=0,搜索成功，tag=1,搜索不成功
};

class BPTree
{
private:
    BPTreeNode * root;//根指针
    BPTreeNode * sqt;
public:
    BPTree(){};//构造函数
    Triple Search(const int& x);//搜索
    bool Insert(const int& x);//插入关键码x
    bool Remove(const int& x);//删除关键码x
    void Travelsal(){
//        BPTreeNode * q = root,*p;
//        int i = 0;
//        p=q;
//        while(p!=NULL){
//        while(p->key[(p->n)<MaxValue]){
//            cout<<p->key[(p->n)]<<endl;
//            break;
//        }
//            p=q->ptr[i++];
//      }
        BPTreeNode * p = sqt;
        int i=0;
        while(p!=NULL){
            for(i=2;i<=p->n;i++)
                std::cout<<p->key[i]<<std::endl;
            p=p->right;
        }
    
    }
};
void move(BPTreeNode*p,BPTreeNode*q,int s,int x );
void insertKey(BPTreeNode* p,int j,int k,BPTreeNode*bp);
bool BPTree::Insert(const int&x){
    
    Triple loc = Search(x);
    if(!loc.tag)return false;
    
    BPTreeNode *p =loc.r,*q;
    BPTreeNode *ap=NULL,*t;
    int k=x,j=loc.i;
    if(p->n<m){
        insertKey(p, j, k, ap);
        return true;
    }
    int s=(m+1)/2;
    q=new BPTreeNode();
    
    
    return true;
}

Triple BPTree::Search(const int&x){
    Triple result;
    
    return result;
}
#endif /* B_Tree_h */
