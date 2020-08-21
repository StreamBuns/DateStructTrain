//
//  main.cpp
//  B+Tree
//
//  Created by 赵桐 on 2020/8/11.
//  Copyright © 2020 赵桐. All rights reserved.
//

#include <iostream>
#include "B+Tree.h"
//#include "LinkedList.h"
#include "LinkedList.h"
int main(int argc, const char * argv[]) {
    // insert code here...
    BPTree * bp = new BPTree();
    int key;
    string strName,sex;
    ifstream infile,infilebig;
    List<StuDate> list;
//    StuDate2 stu2;
    StuDate stu;
//    clock_t startB = 0,endB = 0,startList,endList = 0;
//    struct timeval start_B,end_b;
    srand((unsigned)time(NULL));
 


    infile.open("/Users/zhaotong/C++Program/DSTrain/test.txt",ios::in);
    if(!infile.is_open()){
        cout<<"数据文件打开错误"<<endl;
        exit(1);
    }
//    int i=1000;
//    startB=clock();
//    gittimeofday();
//    while (!infile.eof()) {
//        infile>>key>>strName>>sex;
//        stu.Set(strName, sex);
//        bp->Insert(key,stu);
//
//    }
//    endB=clock();

//    infile.clear();
////    startList=clock();
//    infile.seekg(0,ios::beg);
//    i=1000;
//        while (!infile.eof()&&i>=0) {
//            infile>>key>>strName>>sex;
////            bp->Search(key);r
////            key=rand()%10000;
//            bp->Remove(key);i--;
//        }
//    endList=clock();
//    infile.close();

//************************************************************************
/*
     插入小数据进行测试insert
*/
while (!infile.eof()) {
        infile>>key>>strName>>sex;
        stu.Set(strName, sex);
        bp->Insert(key,stu);
}
    
//*************************************************************************
/*
 *大数据量测试insert
 */
//    infile.close();
//infile.open("/Users/zhaotong/C++Program/DSTrain/date.txt",ios::in);
//while (!infile.eof()) {
//        infile>>key>>strName>>sex;
//        stu.Set(strName, sex);
//        bp->Insert(key,stu);
//}
 //*************************************************************************
/*
 *对Remove进行测试
 */
//bp->Insert(25, stu);
//bp->Insert(26, stu);
//bp->Remove(15);
//bp->Remove(10);

    
    
    
    
    
//    bp->Remove(24);
//    bp->Remove(44);
//    bp->Remove(53);
    
    
    

bp->Travelsal();
infile.close();

////    infile.clear();
//    while (!infile.eof())
//      {
//          infile>>key>>strName>>sex;
//          stu.Set(strName,sex);
//          list.Insert(key,stu);
//      }
//    list.output();
//    list.traverse_list();
cout<<"遍历完成"<<endl;
//    std::cout << "Hello, World!\n"<<(double)(startB-endB)/CLOCKS_PER_SEC<<(double)(startList-endList)/CLOCKS_PER_SEC;
    
    
    
    return 0;
}
