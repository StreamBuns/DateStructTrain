//
//  main.cpp
//  B+Tree
//
//  Created by 赵桐 on 2020/8/11.
//  Copyright © 2020 赵桐. All rights reserved.
//

#include <iostream>
#include "B+Tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <cstring>
 #include <unistd.h>
int main(int argc, const char * argv[]) {
    // insert code here...
    BPTree * bp = new BPTree();
    int key;
    string strName,sex;
    ifstream infile;
    StuDate stu;
    srand((unsigned)time(NULL));
 


    infile.open("/Users/zhaotong/C++Program/DSTrain/date.txt",ios::in);
    if(!infile.is_open()){
        cout<<"数据文件打开错误"<<endl;
        exit(1);
    }
    int i=1000;
    while (!infile.eof()) {
        infile>>key>>strName>>sex;
        stu.Set(strName, sex);
        bp->Insert(key,stu);
        
//        sleep(0.01);
    }
////    infile.seekg(0,ios::beg);
////        while (!infile.eof()) {
////            infile>>key>>strName>>sex;
////            bp->Search(key);
//////            stu.Set(strName, sex);
//////            bp->Insert(key,stu);
////    //        sleep(0.01);
////        }
    infile.close();
//
//    bp->Insert(<#const int &x#>, <#StuDate stu#>)
       bp->Travelsal();


    std::cout << "Hello, World!\n"<<sizeof(BPTreeNode);
    return 0;
}
