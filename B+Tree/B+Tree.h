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
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <cstring>
 #include <unistd.h>
#include<ctime>
#include <iostream>
using namespace std;

struct StuDate{
    string strName;
    string strSex;
    
    void Set(string strName,string strSex){
        this->strName=strName;
        this->strSex = strSex;
    }
    StuDate(StuDate const &stu){
        this->strName=stu.strName;
        this->strSex =stu.strSex;
    }
    StuDate(){
        this->strName="";
        this->strSex ="";
    }
//    StuDate &operator = (StuDate &L){
////        StuDate temp;
//        this->strName=L.strName;
//        this->strSex=L.strSex;
//        return *this;
//    }
};
/*
 *子节点的数据结构
 */
struct BPTreeNode
{
    int n; //关键码的数量
    BPTreeNode * parent;//父结点指针
    int key[m+2];//Key[0]未用
    BPTreeNode * ptr[ m+2];//子树结点指针数组，ptr[m]在一出事使用
    BPTreeNode * right;//B+树叶结点指向右边相邻叶结点
    StuDate * recptr[m+2];//每个索引项中指向数据区相应记录起始地址的指针
    BPTreeNode(){
        n=0;
        parent=NULL;
        for(int i=1;i<=m+1;i++){
            key[i]=MaxValue;
            ptr[i-1]=NULL;
            recptr[i-1]=NULL;
        }
        ptr[m+1]=NULL;
        recptr[m+1]=NULL;
        right = NULL;
    }
};
//---------------------------------------------------------------------------------
//2020年 8月11日 星期二 16时59分15秒 CST
/*
*Search()函数返回值的数据结构
*/
struct Triple
{
    BPTreeNode * r;//节点地址指针
    int i,tag;
    //节点中关键码序号i
    //tag=0,搜索成功，tag=1,搜索不成功
};
//---------------------------------------------------------------------------------
/*
 *B+数定义
 */
class BPTree
{
private:
    BPTreeNode * root;//根指针
    BPTreeNode * sqt;


public:
    BPTree(){
        root = NULL;
        sqt = NULL;
    };//构造函数
    bool Insert(const int& x , StuDate stu);
    bool Remove(const int& x);//删除关键码x
    Triple Search(const int& x);//搜索
    void Travelsal(){
        BPTreeNode * p = sqt;
        int i=0;
        while(p!=NULL){
            for(i=1;i<=p->n;i++)
                std::cout<<p->key[i]<< " " <<p->recptr[i-1]->strName<<" "<<p->recptr[i-1]->strSex<<std::endl;
            p=p->right;
        }
    
    }
};//用来测试插入成功与否

//---------------------------------------------------------------------------------
/*
*void insertKey(BPTreeNode* p,int j,int k,BPTreeNode* ap)
*Created by 赵桐 on 2020年 8月11日 星期二 16时59分15秒 CST
*把关键码k插入到p的key[j+1]的位置，需要先把后面的移动一个然后再插入
*同理也是把ap插入到p的ptr[j+1]的位置
*/
void insertKey(BPTreeNode* p,int j,int k,BPTreeNode* ap,StuDate * pstu){

    for(int i=p->n;i>j;i--){
        p->key[i+1]=p->key[i];
        p->ptr[i]=p->ptr[i-1];
        p->recptr[i]=p->recptr[i-1];
    }

    p->key[j+1]=k;
    p->ptr[j]=ap;
    p->recptr[j]=pstu;
    p->n++;
}
//---------------------------------------------------------------------------------
/*
*void move(BPTreeNode*p,BPTreeNode*q,int s,int x )分裂函数
*Created by 赵桐 on 2020年 8月11日 星期二 16时59分15秒 CST
*把p的右指针指向新分裂出来的q
*把p的key[s+2,m+1]移动到q的key[1,s]
*把p的ptr[s+1,m+1]移动到q的key[0,s]
*p->n变为s+1，q->n变为m-s
*/
//---------------------------------------------------------------------------------
void move(BPTreeNode*p,BPTreeNode*q,int s,int x ){
    int i=0,j=p->n-s+1;
    for(i=0;i<s;i++){
        q->key[i+1]=p->key[j];
        q->ptr[i]=p->ptr[j-1];
        if(q->ptr[i]!=NULL&&q->ptr[i]->parent!=NULL){
        q->ptr[i]->parent=q;
        }
        q->recptr[i]=p->recptr[j-1];
        j++;
    }
//    i=0;
//    BPTreeNode* t=p->parent;
//    while(t->ptr[i]!=p)i++;
//    for(j=t->n-1;j>=i;j--){
//        t->ptr[j+1]=t->ptr[j];
//    }
//    t->ptr[i+1]=q;
    q->ptr[i]=p->ptr[j-1];
    q->recptr[i]=p->recptr[j-1];
    p->n=p->n-s;
    q->n=s;
    
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
bool BPTree::Insert(const int& x , StuDate stu){
    
    Triple loc = Search(x);
    if(!loc.tag)return false;//先搜索如果有就不用插入
    BPTreeNode *p =loc.r,*q;
    BPTreeNode *ap=NULL,*t;
    StuDate * pstu;
    //    strArray = new string*();
    pstu = new StuDate(stu);
    
    if(loc.r==NULL){
        sqt = root=new BPTreeNode();
        insertKey(root, 0, x, ap,pstu);
        root->recptr[0]=pstu;
        return true;
    }
        
    
//    int k=x,j=loc.i,i=0;
      int k=x,j=loc.i,k1,i=0;
    //k是要插入的关键码，j是插入的位置，k1是存储原来p的最大值（用来判断是否刷新父树上的p的最大值），i用来遍历
    //如果节电p的个数小于m那么可以直接插入，但是需要判断，插入的是不是这个分组中最大的数，
    //如果是最大的数且有父节点，那么需要把父节点相应的之前p节点最大的数换成现在p节电最大的数
    while(1){
    if(p->n<m){
        if(k<p->key[p->n]||p->parent==NULL)
        insertKey(p, j, k, ap ,pstu);
        else{
//            k1=p->key[p->n];
            insertKey(p, j, k, ap,pstu);
            i=0;
            while(p->parent!=NULL){
            while(p->parent->ptr[i]!=p)i++;//定位到父节点相应的与之前p中最大值相等的位置，换成现在p中的最大值
                p->parent->key[i+1]=p->key[p->n];
                p=p->parent;
                i=0;
            }
        }
        return true;
    }
    
    int s=(m+1)/2;
    k1=p->key[p->n];   //k1存储现在插入分裂前的时候的p的最大值
    insertKey(p, j, k, ap,pstu);
    q=new BPTreeNode();
        
    q->right=p->right;
    p->right=q;    //把p的右指针指向新分裂出来的q
    move(p,q,s,m);//把p的key[s+2,m+1]移动到q的key[1,s]
                  //把p的ptr[s+1,m+1]移动到q的key[0,s]
                  //p->n变为s+1，q->n变为m-s

    k=p->key[p->n];     //k存储q当前的最大的key
    ap=q;
    if(p->parent!=NULL){

        t=p->parent;
//        while(t->ptr[i]!=p)i++;
//        for(j=t->n-1;j>=i;j--){
//            t->ptr[j+1]=t->ptr[j];
//        }
//        t->ptr[i+1]=q;
        i=j=0;
        while(t->ptr[i]!=p)i++;
        t->key[i+1]=k;
        //找到与之前p的最大key值相等的key，并且替换成现在p中最大的值
//        while(t->key[j+1]<k1)j++;
        j=i+1;
        //找到现在的q的最大key值要插入的地方
        q->parent=p->parent;
        k=q->key[q->n];
        p=t;
    }
    else{                                      //第一次没有父节点，创建一个父节点然后把pq加进去
        root = new BPTreeNode();
        root->n=2;                           //加入两个key
        root->parent=NULL;                   //创建新的根
        root->key[1]=p->key[p->n];root->key[2]=q->key[q->n];     //把子树的两个最大值整进去
        root->ptr[0]=p;root->ptr[1]=q;       //把子节点连接到p，和新分裂的q
        p->parent=q->parent=root;
        
//        sqt=p;                              //p就是以后无论如何最小的那个组，
                                            // 所以把左指针给它
        return true;
    }
    }
    return true;
}
//---------------------------------------------------------------------------------
/*
*Triple Search ( const int& x );
*
*create by FlyingMaster Create on 2020年 8月11日 星期二 17时08分28秒 CST
*
*用x关键码搜索
*返回一个类型为Triple(r,i,tag)的记录
*tag=0，表示x在节点r找到
*tag=1，表示没有找到x，这时可以插入的节点是r
*插入到该结点的K[i]与K[i+1]之间
*
*/
//---------------------------------------------------------------------------------
Triple BPTree::Search(const int &x)
{
    Triple result;

    BPTreeNode *p = root, *q = NULL;
    int i = 0;
    while (p != NULL)
    {
        i = 0;

        //        cout <<p->n << " ";
        p->key[p->n + 1] = MaxValue;
        //将Key值最大的后一个Key值设为MaxValue
        //        {
        //            i++;
        //        }
        while (p->key[i + 1] < x) //以防止找不到相应的小于x的Key值while ( p->key[i + 1] < x )
            i++;
        if (p->key[i + 1] == x)
        {
            if (p->ptr[i] != NULL)
            {
                p = p->ptr[i];
                while (p != NULL)
                {
                    result.r = p;
                    i = p->n;             //更新i使其等于n
                    p = p->ptr[p->n - 1]; //如果在非叶子节点找到等于x的key值
                    //直接遍历叶子结点
                }
                result.i = i;
                result.tag = 0;
                return result;
            }
            else
            {
                result.r = p;
                result.i = i+1;
                result.tag = 0;
                return result;
            }
        }
        q = p;

        if (i == p->n)
            p = p->ptr[i - 1];
        else
            p = p->ptr[i];

        //GetNode(p);
    }
    result.r = q;
    result.i = i;
    result.tag = 1;
    return result; //搜索失败，返回插入位置
    //x可能落入的区间K[i]与K[i+1]
}


//---------------------------------------------------------------------------------
/*
*Remove()函数的辅助函数bool compress(BPTreeNode* p , int j);
*
*create by 赵桐 Create on 2020年 8月12日 星期三 08时14分46秒 CST
*
*主要功能就是把叶节点的key值直接删除，直接删除之前需要把叶节点的值往前搬动，以保证时时刻刻都是处在平衡状态
*
*/
//---------------------------------------------------------------------------------
void compress(BPTreeNode* p , int j){
    for(int i=j;i<p->n;i++){
        p->key[i]=p->key[i+1];          //从删除的位置往前搬
        p->ptr[i-1]=p->ptr[i];
        p->recptr[i-1]=p->recptr[i];
    }
    p->n--;                             //删除了就把原来的关键码的个数减少一个
}
//---------------------------------------------------------------------------------
/*
*最左边的子树的调整void LeftAdjust(BPTreeNode* p,BPTreeNode *q,int d, int j);
*
*create by 赵桐 Create on 2020年 8月12日 星期三 08时14分46秒 CST
*
*当左边删除完了关键码的个数小于d就是把节点p中的值进行调整，
*首先是如果左边p与右边pl的关键码个数加起来小于m的时候，直接两个节点合并
*其次是如果加起来大与m的时候，直接把右节点中部分个值给左边节点，然后把右边节点后面的key值搬到前面形成平衡树
*/
//---------------------------------------------------------------------------------
void LeftAdjust(BPTreeNode* p,BPTreeNode *q,int d, int j){
    
    BPTreeNode * pl = p->right;       //pl是p同父亲的右边的子树
    if((pl->n+p->n)<=m){
                                //如果p的关键码的个数与pl的关键码的个数加起来小于等于m那么直接合并
        int i=0;
        for(i=1;i<=pl->n;i++){       //这个循环把右节点的数据传送到左节点
            p->key[p->n+1]=pl->key[i];
            p->recptr[p->n]=pl->recptr[i-1];
            p->ptr[p->n]=pl->ptr[i-1];
            p->n++;
            }
            p->right = pl->right;
        for(int i=j+1;i<q->n;i++){     //这个循环把父节点上面的p q合并为一个
            q->key[i]=q->key[i+1];
            q->ptr[i]=q->ptr[i+1];
        }
        q->key[j+1]=p->key[p->n];
        q->n--;
//        delete pl;
    }
    else{
                                        //如果此节点跟右边的节点大于1，就需要把右边节点的部分数据
                                        //移动到左节点宏观上实现，“先合并再分裂”微观实现其实只需要
                                        //移动右节点部分数据，然后把后面的数据挪到前面去
        int k=0;
        for(int i=0;i<m-d;i++){        //移动部分数据到左节点
            p->key[p->n+1]=pl->key[i+1];
            p->recptr[p->n]=pl->recptr[i];
            p->n++;
            k++;
        }

        k=1;
        for(int i=m-d+1;i<=pl->n;i++){    //把后面的数据挪到前面去形成平衡树
            pl->key[k++]=pl->key[i];
            pl->recptr[k-2]=pl->recptr[i-1];
        }
        pl->n=d;
        q->key[j+1]=p->key[p->n];       //把父节点上左节点的最大值改成现在的最大值
    }
}
//---------------------------------------------------------------------------------
/*
*非最左边的子树的调整void RightAdjust(BPTreeNode* p,BPTreeNode *q,int d, int j)
*
*create by 赵桐 Create on 2020年 8月12日 星期三 08时14分46秒 CST
*
*原理与最左边的子树调整类似，不过是左右互换。
*这个p不是必定不是q的ptr[0]所以只要整一个pl=p的左边节点
*然后pl与p互换就能复用最左树调整的代码
*
*/
//---------------------------------------------------------------------------------
void RightAdjust(BPTreeNode* p,BPTreeNode *q,int d, int j){
    BPTreeNode * pl = q->ptr[j-1],*temp;
    temp=pl;
    pl=p;
    p=temp;
   if((pl->n+p->n)<=m){
                                    //如果p的关键码的个数与pl的关键码的个数加起来小于等于m那么直接合并
            int i=0;
            for(i=1;i<=pl->n;i++){       //这个循环把右节点的数据传送到左节点
                p->key[p->n+1]=pl->key[i];
                p->recptr[p->n]=pl->recptr[i-1];
                p->ptr[p->n]=pl->ptr[i-1];
                p->n++;
                }
                p->right = pl->right;
            for(int i=j+1;i<q->n;i++){     //这个循环把父节点上面的p q合并为一个
                q->key[i]=q->key[i+1];
                q->ptr[i]=q->ptr[i+1];
            }
            q->key[j+1]=p->key[p->n];
            q->n--;
    //        delete pl;
        }
        else{
                                            //如果此节点跟右边的节点大于1，就需要把右边节点的部分数据
                                            //移动到左节点宏观上实现，“先合并再分裂”微观实现其实只需要
                                            //移动右节点部分数据，然后把后面的数据挪到前面去
            int k=0;
            for(int i=0;i<m-d;i++){        //移动部分数据到左节点
                p->key[p->n+1]=pl->key[i+1];
                p->recptr[p->n]=pl->recptr[i];
                p->n++;
                k++;
            }

            k=1;
            for(int i=m-d+1;i<=pl->n;i++){    //把后面的数据挪到前面去形成平衡树
                pl->key[k++]=pl->key[i];
                pl->recptr[k-2]=pl->recptr[i-1];
            }
            pl->n=d;
            q->key[j+1]=p->key[p->n];       //把父节点上左节点的最大值改成现在的最大值
        }
}
//---------------------------------------------------------------------------------
/*
*bool remove ( const int& x );
*
*create by 赵桐 Create on 2020年 8月12日 星期三 08时14分46秒 CST
*
*用x关键码搜索如果找到了就把相应的key值的数据节点进行删除
*
*/
//---------------------------------------------------------------------------------
bool BPTree::Remove(const int&x){
    Triple loc = Search(x);
    if(loc.tag==1)return false;        //找不到就返回
    BPTreeNode *p=loc.r,*q;
    int j = loc.i;
    
    
    if(x==p->key[p->n]&&p->parent!=NULL){  //如果不是p里最大的数或者没有父母直接删除
                                    //否则，删除完p以后需要把父母里面的p的最大值更改为现在的最大值
        compress(p, j);
        int i=0;
        while(p->parent->ptr[i]!=p)i++;
        p->parent->key[i+1]=p->key[p->n];
    }
    else compress(p, j);


    int d = (m+1)/2;
    while(1){                           //如果个数小余d那就从下面叶节点循环往上面更改
        if(p->n<d){
            j=0;q=p->parent;
            if(p==root)break;
//            GetNode(q);
            while(j<=q->n&&q->ptr[j]!=p)j++;
            if(j==0)LeftAdjust( p, q, d, j);       //如果是最左边的子孩子就与右边的孩子调整
            else RightAdjust( p, q, d, j);          //如果不是最左边的孩子，就与左边的孩子进行调整
            p=p->parent;
            if(p==root)break;
        }
        else break;
    }
    if(root->n == 1){                               //如果父母的关键码个数==1
                                                    //那就取消这一层
        p=root->ptr[0];
        delete root;root = p;
        root->parent=NULL;
    }
    return true;
}
#endif /* B_Tree_h */
