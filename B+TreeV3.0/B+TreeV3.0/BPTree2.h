//
//  BPTree2.h
//  B+TreeV3.0
//
//  Created by 赵桐 on 2020/8/19.
//  Copyright © 2020 赵桐. All rights reserved.
//

//---------------------------------------------------------------------------------
/*
*Date.h
*
*create by FlyingMaster on 2020年8月18日 10:14:36
*
*结构体: BPTreeNode
*B+树的节点,包含关键码和关键码数量，父节点，子节点以及相邻节点的偏移量
*
*类：Triple
*用于在Search时返回查询结果，包括关键码在原索引文件中是否存在，
*存在的节点或者应当插入该关键码节点的偏移量，以及在节点中应当插入的位置
*
*类：BPTree
*数据：根节点，索引文件路径
*功能：将关键码以B+树索引的形式插入到BPTreeNode中，支持关键码，以及关键码所在数据库数据文件偏移量插入，关键码的查询以及修改
*此B+树中，只有root节点常驻内存，其余数据均在磁盘文件上读取和写入
*
*version: 2.0
*
*/
//---------------------------------------------------------------------------------

#ifndef B_Tree_h
#define B_Tree_h

#include <fstream>
#include <iostream>
//#include "direct.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#define MaxValue 2000000
#define m 4
#define MaxLength 20
using namespace std;
/*
 *子节点的数据结构
 */

struct BPTreeNode
{
    int n;              //关键码数量
    int partentDiff;    //父节点指针
    int key[m + 2];     //关键码，key[0]未用
    int ptrDiff[m + 2]; //子树节点偏移量
    int rightDiff;      //右边相邻叶节点的偏移量
    int recptr[m + 2];  //每个索引项中指向数据库数据文件的偏移量

    BPTreeNode()
    {
        n = 0;
        partentDiff = -1;
        for (int i = 0; i < m + 2; i++)
        {
            key[i] = MaxValue;
            ptrDiff[i] = -1;
            recptr[i] = -1;
        }
        rightDiff = -1;
    }
    const BPTreeNode& operator=(const BPTreeNode& good){
        this->n=good.n;
        this->partentDiff=good.partentDiff;
        this->rightDiff=good.rightDiff;
        for(int i=0;i<m+2;i++){
            this->key[i]=good.key[i];
            this->ptrDiff[i]=good.ptrDiff[i];
            this->recptr[i]=good.recptr[i];
        }
        return *this;
    }
//    BPTreeNode()
};
//---------------------------------------------------------------------------------
//2020年 8月11日 星期二 16时59分15秒 CST
/*
*Search()函数返回值的数据结构
*/
//---------------------------------------------------------------------------------
struct Triple
{
    int diff; //节点地址在数据库数据文件偏移量
    int i, tag;
    //节点中关键码序号i
    //tag=0,搜索成功，tag=1,搜索不成功
};
//---------------------------------------------------------------------------------
/*
*B+数定义
*/
//----------------------------------------------------------------------------------
class BPTree
{
private:
    int root; //根节点
    string filePath; //索引文件所在的位置
    int sqt;
    int size;
public:
    BPTree()
    {
        // root = NULL;
        // sqt = NULL;
        
        filePath = "";
        size = 0;
        ifstream fileOut;                                                  //文件输出流
        fileOut.open("/Users/zhaotong/C++Program/DSTrain/B+TreeV3.0/data/mydb/student.r", ios::binary | ios::out |ios::in);//用文件打开模式 ios::in，这样可以保证文件内容不会被清空，且文件指针偏移操作有效。
        if(!fileOut.is_open()) {
            cout<<"打开目录文件错误"<<endl;
        }
        fileOut.seekg(0);
        fileOut.read((char *)&root, sizeof(int));
        fileOut.seekg(sizeof(int));
        fileOut.read((char *)&sqt, sizeof(int));
        fileOut.close();
//        root = 
    }; //无参构造函数
    BPTree(string &_filePath)
    {
        
        // sqt = NULL;
        filePath = _filePath;
        size = 0;
        ifstream fileOut;                                                  //文件输出流
        fileOut.open("/Users/zhaotong/C++Program/DSTrain/B+TreeV3.0/data/mydb/student.r", ios::binary | ios::out |ios::in);//用文件打开模式 ios::in，这样可以保证文件内容不会被清空，且文件指针偏移操作有效。
        if(!fileOut.is_open()) {
            cout<<"打开目录文件错误"<<endl;
        }
        fileOut.seekg(0);
        fileOut.read((char *)&root, sizeof(int));
        fileOut.seekg(sizeof(int));
        fileOut.read((char *)&sqt, sizeof(int));
        fileOut.close();
    }
    Triple Search(const int &x);                //搜索
    bool Insert(const int &x, const int &diff,Triple loc); //插入关键码x,并将数据在数据库数据文件中的头偏移量存入到recptr[];
    bool Remove(const int &x);                  //删除关键码x
    void Travelsal(){
        BPTreeNode temp;
        int p=sqt;
        while(GetNode(temp, p)&&p!=-1){
            for(int i=0;i<temp.n ;i++){
                cout<<temp.key[i+1]<<endl;
        }
            p=temp.rightDiff;
        }
    }
    bool GetNode(BPTreeNode &bpn, int pidff); //从数据库数据文件里读入节点bpn，需要已知节点偏移量
    int PutNode(BPTreeNode &bpn); //从数据库文件中在末尾添加节点，返回该节点的偏移量
    bool ModifyNode(BPTreeNode &bpn, int pidff);//在文件原位置修改节点数据
    bool ModifyRootSqt(int tag,int diff);
    void move(BPTreeNode& p,BPTreeNode& q,int s,int x,int qd);//用于分配分裂形成的子节点的数据。
};

bool BPTree::GetNode(BPTreeNode &bpn, int pidff)
{
    ifstream fileOut;
    string ProcessDatePath = filePath; //生成的数据库索引文件
    fileOut.open(ProcessDatePath.data(), ios::binary | ios::in);
    if (!fileOut.is_open())
    {
        cout << "数据库索引文件打开错误" << endl;
        return false;
    }
    else
    {
        /* code */
        fileOut.seekg(pidff);
        fileOut.read((char *)&bpn, sizeof(BPTreeNode));
        fileOut.close();
    }
    return true;
}

int BPTree::PutNode(BPTreeNode &bpn)
{
    ofstream fileIn;
    fileIn.open(filePath.data(), ios::binary | ios::app); //直接在末尾添加
    if (!fileIn.is_open())
    {
        cout << "打开数据库索引文件错误" << endl;
        return -1;
    }
    assert(fileIn);
    fileIn.write((char *)&bpn, sizeof(BPTreeNode));
    size += sizeof(BPTreeNode);
    fileIn.close();
    return size - sizeof(BPTreeNode); //返回插入Node的头偏移量
}

Triple BPTree::Search(const int &x)
{
    Triple result;

    // GetNode(root, 0); //从索引文件中获取偏移量为0的root,使root节点常驻内存
    // cout << root.key[1] << endl;
    BPTreeNode p, q;
    GetNode(p, root);
    int resultDiff = 0;
    int i = 0;
    while (1)
    {
        /* code */
        i = 0;
        //cout <<"search的p key为"<<p.key[1]<<endl;
        p.key[p.n + 1] = MaxValue;
        if (p.n == 0)
        {
            resultDiff = -1;
            break;
        }
        while (p.key[i + 1] < x)
        {
            i++;
        }
        if (p.key[i + 1] == x)
        {
            if (p.ptrDiff[i] != -1)
            {
                resultDiff = p.ptrDiff[i];
                GetNode(p, p.ptrDiff[i]); //如果拥有子节点，则更新p,使其为子节点
                while (1)
                {
                    /* code */
                    if (p.ptrDiff[p.n - 1] == -1)
                    {
                        break;
                    }
                    i = p.n;
                    resultDiff = p.ptrDiff[p.n - 1];
                    GetNode(p, p.ptrDiff[p.n - 1]);
                }
                result.diff = resultDiff;
                result.i = i;
                result.tag = 0;
                return result;
            }
            else
            {
                /* code */
                result.diff = resultDiff;
                result.i = i + 1;
                result.tag = 0;
                return result;
            }
        }

        if (p.ptrDiff[i-1] == -1)
        {
            break;
        }
        if (i == p.n)
        {
            resultDiff = p.ptrDiff[i - 1];
            GetNode(p, p.ptrDiff[i - 1]);
        }
        else
        {
            resultDiff = p.ptrDiff[i];
            GetNode(p, p.ptrDiff[i]);
        }
    }
    result.diff = resultDiff;
    result.i = i;
    result.tag = 1;
    return result; //搜索失败，返回插入位置
    //x可能落入的区间K[i]与K[i+1]
}
//---------------------------------------------------------------------------------
/*
*void insertKey(BPTreeNode& p,int j,int k,int ap,int pstu)插入函数
*Created by 赵桐 2020年 8月19日 星期三 15时58分49秒 CST
*把关键码k插入到p的key[j+1]的位置，需要先把后面的移动一个然后再插入
*同理也是把ap插入到p的ptrDiff[j+1]的位置
*/
//---------------------------------------------------------------------------------
void insertKey(BPTreeNode& p,int j,int k,int ap,int pstu){
    for(int i=p.n;i>j;i--){
        p.key[i+1]=p.key[i];
        p.ptrDiff[i]=p.ptrDiff[i-1];
        p.recptr[i]=p.recptr[i-1];
    }

    p.key[j+1]=k;
    p.ptrDiff[j]=ap;
    p.recptr[j]=pstu;
    p.n++;
    
};
//---------------------------------------------------------------------------------
/*
*void BPTree::move(BPTreeNode& p,BPTreeNode& q,int s,int x,int qd)分裂分配函数
*Created by 赵桐 2020年 8月19日 星期三 15时58分49秒 CST
*把p的key[s+2,m+1]移动到q的key[1,s]
*把p的ptr[s+1,m+1]移动到q的key[0,s]
*p->n变为s+1，q->n变为m-s
*/
//---------------------------------------------------------------------------------
void BPTree::move(BPTreeNode& p,BPTreeNode& q,int s,int x,int qd){
    
    int i=0,j=p.n-s+1;
         for(i=0;i<s;i++){
             q.key[i+1]=p.key[j];
             q.ptrDiff[i]=p.ptrDiff[j-1];
//             if(q.ptrDiff[i]!=NULL&&q.ptr[i]->parent!=NULL){
             if(q.ptrDiff[i]!=-1){
                 BPTreeNode temp;
                 GetNode(temp, q.ptrDiff[i]);
                 temp.partentDiff=qd;
                 ModifyNode(temp, q.ptrDiff[i]);
             }
             q.recptr[i]=p.recptr[j-1];
             j++;
         }
     //    i=0;
     //    BPTreeNode* t=p->parent;
     //    while(t->ptr[i]!=p)i++;
     //    for(j=t->n-1;j>=i;j--){
     //        t->ptr[j+1]=t->ptr[j];
     //    }
     //    t->ptr[i+1]=q;
    q.ptrDiff[i]=p.ptrDiff[j-1];
    q.recptr[i]=p.recptr[j-1];
    p.n=p.n-s;
    q.n=s;
}
//---------------------------------------------------------------------------------
/*
*bool Insert(const int&x)插入函数
*Created by 赵桐 on 2020年 8月11日 星期二 16时59分15秒 CST
*把x插入到最符合它的那个地方，如果插入的子节点的key的个数大于m则进行分裂
*把q分裂形成p，q，分别有「m+1/2 个 和 m+1/2」个
*然后把分裂形成的p，q子节点的最大值添加进父节点
*/
//---------------------------------------------------------------------------------
bool BPTree::Insert(const int &x, const int &diff,Triple loc){
//    Triple loc = Search(x);
//    if (!loc.tag)
//        return false;
    
    BPTreeNode p,q,pp,teststruct;
    BPTreeNode t;
    
    int ap = -1,qd=-1,pd =loc.diff;
    int pstu=diff;
    int k=x,j=loc.i,k1,i=-1;
    
    if (loc.diff == -1){
            ofstream fileIn;//文件输出流
            fileIn.open(filePath.data(), ios::binary | ios::app); //以二进制输入的方式打开文件,打开，如果没有文件，那么生成空文件；如果有文件，那么在文件尾追加。
            p.key[1]=x;
            p.recptr[0]=pstu;
            p.partentDiff=-1;
            p.n++;

        sqt=root=PutNode(p);
        ModifyRootSqt(1,root);
        ModifyRootSqt(0,sqt);
        return true;
    }
    GetNode(p,pd);
    GetNode(teststruct, root);
    while(1){
        if(p.n<m){
            if(k<p.key[p.n]||p.partentDiff==-1)
            {
            insertKey(p, j, k, ap ,pstu);
            ModifyNode(p, pd);
            }
            else{
                insertKey(p, j, k, ap,pstu);
                ModifyNode(p, pd);
                i=0;
                while(p.partentDiff!=-1){
                GetNode(t, p.partentDiff);
                while(t.ptrDiff[i]!=loc.diff)i++;
                    //定位到父节点相应的与之前p中最大值相等的位置，换成现在p中的最大值
                t.key[i+1]=p.key[p.n];
                ModifyNode(t, p.partentDiff);
                pd=p.partentDiff;
                GetNode(p, p.partentDiff);
//                pd=p.partentDiff;
                i=0;
                }
                ModifyNode(p, pd);
            }
            return true;
        }
        int s=(m+1)/2;
        k1=p.key[p.n];   //k1存储现在插入分裂前的时候的p的最大值
        insertKey(p, j, k, ap,pstu);
        qd=PutNode(q);
        q.rightDiff=p.rightDiff;
        p.rightDiff=qd;    //把p的右指针指向新分裂出来的q
        move(p,q,s,m,qd);//把p的key[s+2,m+1]移动到q的key[1,s]
                          //把p的ptr[s+1,m+1]移动到q的key[0,s]
                          //p->n变为s+1，q->n变为m-s

        k=p.key[p.n];     //k存储q当前的最大的key
        ap=qd;
        if(p.partentDiff!=-1){
        GetNode(t, p.partentDiff);
        i=j=0;
        while(t.ptrDiff[i]!=pd)i++;
        t.key[i+1]=k;
                //找到与之前p的最大key值相等的key，并且替换成现在p中最大的值
        //        while(t->key[j+1]<k1)j++;
        j=i+1;
                //找到现在的q的最大key值要插入的地方
        q.partentDiff=p.partentDiff;
        ModifyNode(p, pd);
        ModifyNode(t, p.partentDiff);
        ModifyNode(q, qd);
        k=q.key[q.n];
        pd=p.partentDiff;
        p=t;
        
    }
            else{                                      //第一次没有父节点，创建一个父节点然后把pq加进去
//                root = new BPTreeNode();
                t.n=2;                              //加入两个key
                t.partentDiff=-1;//创建新的根
                ModifyNode(p, pd);
                ModifyNode(q, qd);
                t.key[1]=p.key[p.n];t.key[2]=q.key[q.n];     //把子树的两个最大值整进去
                t.ptrDiff[0]=pd;t.ptrDiff[1]=qd;       //把子节点连接到p，和新分裂的q
                root=p.partentDiff=q.partentDiff=PutNode(t);
                
                ModifyNode(p, pd);
                ModifyNode(q, qd);
                                        
                ModifyRootSqt(1, root);                                  //修改父节点后把父节点“指针”更新到新的文件
                return true;
            }
        }
            return true;
}
//---------------------------------------------------------------------------------

bool BPTree::ModifyNode(BPTreeNode &bpn,int diff){
    ofstream fileIn;                                                  //文件输出流
    fileIn.open(filePath.data(), ios::binary | ios::out |ios::in);//用文件打开模式 ios::in，这样可以保证文件内容不会被清空，且文件指针偏移操作有效。
    if(!fileIn.is_open()) return false;
    fileIn.seekp(diff);
    fileIn.write((char *)&bpn,sizeof(BPTreeNode));
    fileIn.close();
    return true;
}
bool BPTree::ModifyRootSqt(int tag,int diff){
    ofstream fileIn;                                                  //文件输出流
    fileIn.open("/Users/zhaotong/C++Program/DSTrain/B+TreeV3.0/data/mydb/student.r", ios::binary | ios::out |ios::in);//用文件打开模式 ios::in，这样可以保证文件内容不会被清空，且文件指针偏移操作有效。
    if(!fileIn.is_open()) return false;
    if(tag){
    fileIn.seekp(0);
    fileIn.write((char *)&diff,sizeof(int));
    fileIn.close();
    return true;
    }else{
        fileIn.seekp(sizeof(int));
        fileIn.write((char*)&diff, sizeof(int));
        fileIn.close();
        return true;
    }
    return true;
}


#endif /* B_Tree_h */
