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
int main(int argc, const char * argv[]) {
    // insert code here...
    BPTree * bp = new BPTree();
    int key;
    string strName,sex;
    ifstream infile;
//    List list;
    StuDate2 stu2;
    StuDate stu;
    clock_t startB,endB,startList,endList;
    struct timeval start_B,end_b;
    srand((unsigned)time(NULL));
 


    infile.open("/Users/zhaotong/C++Program/DSTrain/test.txt",ios::in);
    if(!infile.is_open()){
        cout<<"数据文件打开错误"<<endl;
        exit(1);
    }
    int i=1000;
    startB=clock();
//    gittimeofday();
    while (!infile.eof()) {
        infile>>key>>strName>>sex;
        stu.Set(strName, sex);
        bp->Insert(key,stu);

    }
    endB=clock();
    
    infile.clear();
    startList=clock();
    infile.seekg(0,ios::beg);
        while (!infile.eof()) {
            infile>>key>>strName>>sex;
//            bp->Search(key);
            bp->Remove(key);
        }
    endList=clock();
    infile.close();

       bp->Travelsal();
    
//    while (!infile.eof())
//      {
//          infile>>key>>strName>>sex;
//
//          stu.Set(strName,sex);
//
//          list.Insert(key,stu);
//
//      }
//        list.traverse_list();

    std::cout << "Hello, World!\n"<<(double)(startB-endB)/CLOCKS_PER_SEC<<(double)(startList-endList)/CLOCKS_PER_SEC;
    return 0;
}
