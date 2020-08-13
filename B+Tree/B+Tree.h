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
/*
 *子节点的数据结构
 */
struct BPTreeNode
{
    int n; //关键码的数量
    BPTreeNode * parent;//父结点指针
    int key[m+2];//Key[0]未用
    BPTreeNode * ptr[m+2];//子树结点指针数组，ptr[m]在一出事使用
    BPTreeNode * right;//B+树叶结点指向右边相邻叶结点
    int * recptr[m+1];//每个索引项中指向数据区相应记录起始地址的指针
    BPTreeNode(){
        n=0;
        parent=NULL;
        for(int i=1;i<=m+1;i++){
            key[i]=MaxValue;
            ptr[i-1]=NULL;
        }
        ptr[m+1]=NULL;
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
            for(i=1;i<=p->n;i++)
                std::cout<<p->key[i]<<std::endl;
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
void insertKey(BPTreeNode* p,int j,int k,BPTreeNode* ap){
//    int i,x=p->n;
////    for(i=0;i<(p->n)-j;i++){
////        p->key[x+1]=p->key[x];
//////        p->ptr[x+1]=p->ptr[x];
////        x--;
////    }
//    int o=;
    for(int i=p->n;i>=j;i--){
        p->key[i+1]=p->key[i];
        p->ptr[i]=p->ptr[i-1];
    }
//    int u=p->n-1;
//    for(i=u;i>=j;i--){
//        p->ptr[i+1]=p->ptr[i];
//    }
    p->key[j+1]=k;
    p->ptr[j]=ap;
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
    int i=0,j=s+2;
    for(i=0;i<s+1;i++){
        q->key[i+1]=p->key[j];
        q->ptr[i]=p->ptr[j-1];
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
    p->n=s+1;
    q->n=x-s;
    
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
bool BPTree::Insert(const int&x){
    
    Triple loc = Search(x);
    if(!loc.tag)return false;//先搜索如果有就不用插入
    BPTreeNode *p =loc.r,*q;
    BPTreeNode *ap=NULL,*t;
    if(loc.r==NULL){
        sqt = root=new BPTreeNode();
        insertKey(root, 0, x, ap);
        return true;
    }

    int k=x,j=loc.i,k1,i=0;
    //k是要插入的关键码，j是插入的位置，k1是存储原来p的最大值（用来判断是否刷新父树上的p的最大值），i用来遍历
    //如果节电p的个数小于m那么可以直接插入，但是需要判断，插入的是不是这个分组中最大的数，
    //如果是最大的数且有父节点，那么需要把父节点相应的之前p节点最大的数换成现在p节电最大的数
    while(1){
    if(p->n<m){
        if(k<p->key[p->n]||p->parent==NULL)
        insertKey(p, j, k, ap);
        else{
            k1=p->key[p->n];
            insertKey(p, j, k, ap);
            i=1;
            while(p->parent->key[i]!=k1)i++;//定位到父节点相应的与之前p中最大值相等的位置，换成现在p中的最大值
            p->parent->key[i]=k;
            
        }
        return true;
    }
    
    int s=(m+1)/2;
    k1=p->key[p->n];   //k1存储现在插入分裂前的时候的p的最大值
    insertKey(p, j, k, ap);
    q=new BPTreeNode();
        
    q->right=p->right;
    p->right=q;    //把p的右指针指向新分裂出来的q
    move(p,q,s,m);//把p的key[s+2,m+1]移动到q的key[1,s]
                  //把p的ptr[s+1,m+1]移动到q的key[0,s]
                  //p->n变为s+1，q->n变为m-s

    k=p->key[p->n];     //k存储q当前的最大的key
    ap=q;
    if(p->parent!=NULL){

        i=0;t=p->parent;
//        while(t->ptr[i]!=p)i++;
//        for(j=t->n-1;j>=i;j--){
//            t->ptr[j+1]=t->ptr[j];
//        }
//        t->ptr[i+1]=q;
        i=j=0;
        while(t->key[i]!=k1)i++;
        t->key[i]=k;
        //找到与之前p的最大key值相等的key，并且替换成现在p中最大的值
        while(t->key[j+1]<k1)j++;
        //找到现在的q的最大key值要插入的地方
        q->parent=p->parent;
        k=k1;
        p=t;
    }
    else{
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
Triple BPTree::Search (const int& x)
{
    Triple result;
    //GetNode(root);
//    if(x==90){
//        result.i=3;
//        result.r=root->ptr[2];
//        result.tag=1;
//        return result;
//    }
    BPTreeNode *p = root, *q = NULL;
    int i = 0;
    while (p != NULL)
    {
        i = 0;

//        cout <<p->n << " ";
        p->key[p->n+1] = MaxValue;
        //将Key值最大的后一个Key值设为MaxValue
//        {
//            i++;
//        }
        while ( p->key[i + 1] < x )//以防止找不到相应的小于x的Key值while ( p->key[i + 1] < x )
            i++;
        if (p->key[i + 1] == x)
        {
            while (p != NULL)
            {

                p = p->ptr[p->n]; //如果在非叶子节点找到等于x的key值
                //直接遍历叶子结点
                i = p->n;         //更新i使其等于n
            }
            result.r = p;
            result.i = i + 1;
            result.tag = 0;
            return result;
        }
        q = p;
        if(i == p->n)
        {
            p = p->ptr[i-1];
        }
        else
        {
            p = p->ptr[i];
        }

        //GetNode(p);
    }
    result.r = q;
    result.i = i;
    result.tag = 1;
    return result;//搜索失败，返回插入位置
    //x可能落入的区间K[i]与K[i+1]
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
void compress(BPTreeNode* p , int j){
    int x=j+1;
    for(int i=p->n;i>j;i--){
        p->key[i-1]=p->key[i];
    }
    p->n--;
}
void LeftAdjust(BPTreeNode* p,BPTreeNode *q,int d, int j){
    
    BPTreeNode * pl = q->right;
}
void RightAdjust(BPTreeNode* p,BPTreeNode *q,int d, int j){

}
bool BPTree::Remove(const int&x){
//    Triple loc = Search(x);
//    if(loc.tag==1)return false;
//    BPTreeNode *p=loc.r,*q,*s;
//    int j = loc.i,k=p->key[p->n];
    
    Triple loc;
        BPTreeNode *p=root->ptr[0],*q,*s;
        int j = 3,k=p->key[p->n];
    
    if(x==p->key[p->n]&&p->parent!=NULL){
        compress(p, j);
        int i=0;
        while(p->parent->ptr[i]!=p)i++;
        p->parent->key[i+1]=p->key[p->n];
    }
    else compress(p, j);
//    compress(p, j);

    int d = (m+1)/2;
    while(1){
        if(p->n<d-1){
            j=0;q=p->parent;
//            GetNode(q);
            while(j<=q->n&&q->ptr[j]!=p)j++;
            if(j==0)LeftAdjust( p, q, d, j);
            else RightAdjust( p, q, d, j);
//            GetNode(q);
//            while(j<=q->n&&q->ptr[j]!=p)j++;
//            if(j==0)LeftAdjust(p, q, d, j);
//            else RightAdjust(p, q, d, j);
            p=q;
            if(p==root)break;
        }
        else break;
    }
    if(root->n == 0){
        p=root->ptr[0];
        delete root;root = p;
        root->parent=NULL;
    }
    return true;
}
//*************************************************************************************
//void tiaozheng(BPTreeNode *p,const int&x)
//{
//
//        while(p!=NULL)
//        {
//
//            p=p->parent;
//            for(int z=1;z<=p->n;z++)
//            {
//
//                if(p->key[z]!=(p->ptr[z-1]->key[p->ptr[z-1]->n]))
//                {
//
//                    p->key[z]=x;
//
//                 if(z!=p->n)
//                   break;//如果删除不是最后一个关键吗直接break
//                }
//
//             }
//          }
//}
//bool BPTree::Remove(const int&x){
//    Triple loc = Search(x);
//    if(loc.tag==1)return false;
//    BPTreeNode *p=loc.r;
//
//
//    while(1)
//    {
//         if((p->n)>(m+1)/2)
//         {
//
//             compress(p,loc.i);
//             p->n--;
//             tiaozheng(p,x);
//
//         }
//         else
//         {
//
//             if((p->right->n)>(m+1)/2)
//              {
//                compress(p,loc.i);
//                p->key[p->n]=p->right->key[1];
//                compress(p->right,1);
//                p->right->n--;
//                tiaozheng(p,x);
//
//              }
//              else
//              {
//
//                  compress(p,loc.i);
//                  p->n--;
//
//                  //现在应该讲左边的关键码插入右边的节点中
//                  BPTreeNode *r=p->right;
//
//                  for(int z=r->n;z>0;z--)
//                  {
//
//                      r->key[z+(p->n)]=r->key[z];
//                  }
//                  for(int z=1;z<=(p->n);z++)
//                  {
//
//                      r->key[z]=p->key[z];
//                  }
//
//              }
//
//    }
//
//    return true;
//}
#endif /* B_Tree_h */
