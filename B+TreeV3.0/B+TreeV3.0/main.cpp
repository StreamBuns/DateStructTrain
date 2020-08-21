//
//  main.cpp
//  B+TreeV3.0
//
//  Created by 赵桐 on 2020/8/19.
//  Copyright © 2020 赵桐. All rights reserved.
//

//---------------------------------------------------------------------------------
/*
*int main ();
*
*create by FlyingMaster Create on 2020年8月14日 9:53:33
*
*用于数据存储的测试
*
*/
//---------------------------------------------------------------------------------
#include "BPTree2.h"
#include "Date.h"
#include <iostream>
#include <fstream>
#include <string.h>


using namespace std;

int main(int argc, const char * argv[]) {
    string dbName = "mydb";
    string fileName = "data.txt";
    //string tableName = "student.t";
    DataBase *db = new DataBase(dbName);
    StudentTable *st = new StudentTable();
    st->CreateTable(db->dbName);
    st->insertData(fileName);
    //st->Outdate();
    // Student s;
    // string name = "123";
    // s.sno = 123;
    // strcpy(s.sname,"123");
    // strcpy(s.ssex,"1283");
    // st->modifyDate(s,48);

//    st->Outdate();
}
