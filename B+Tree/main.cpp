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
#include <fstream>
#include <string>
int main(int argc, const char * argv[]) {
    // insert code here...
    BPTree * bp = new BPTree();
//    FILE *fp;
    int key,strId;
    string strName,sex;
    ifstream infile;
    infile.open("/Users/zhaotong/C++Program/DSTrain/date.txt",ios::in);
    if(!infile.is_open()){
        cout<<"数据文件打开错误"<<endl;
        exit(1);
    }
    while (!infile.eof()) {
        infile>>key>>strName>>sex;
        bp->Insert(key);
    }
    

//    char strName[80],sex[80];
//    fp = fopen("date.txt", "r");
//    while(fscanf(fp, "%d  %s  %s \n", &key,&strName,&sex )){
//        bp->Insert(key);
//    }
//    bp->Insert(01);
//    bp->Insert(24);
////    bp->Remove(01);
////    bp->Insert(24);
//    bp->Insert(39);
//    bp->Insert(72);
//    bp->Insert(53);
//    bp->Remove(53);
//    bp->Remove(39);
//    bp->Remove(24);
//    bp->Remove(01);
//    bp->Remove(72);
//    bp->Insert(54);
//    bp->Insert(55);
//
//    bp->Insert(39);
//     bp->Insert(63);
////    bp->Insert(71);
//     bp->Insert(90);
//     bp->Insert(88);
////    bp->Insert(54);
////        bp->Remove(39);
////        bp->Remove(24);
//    bp->Insert(15);
//    bp->Insert(10);
////////    bp->Insert(91);
//    bp->Insert(44);
//    bp->Insert(68);
//    bp->Insert(74);
//    bp->Remove(15);
//    bp->Remove(10);
    bp->Travelsal();

//    int n=4;
//    int array[m+1];
//
//    for (int i=0; i<=m+1; i++) {
//        cout<<array[i]<<endl;
//    }
    std::cout << "Hello, World!\n";
    return 0;
}
