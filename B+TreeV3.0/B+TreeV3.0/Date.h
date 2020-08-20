//
//  Date.h
//  B+TreeV3.0
//
//  Created by 赵桐 on 2020/8/19.
//  Copyright © 2020 赵桐. All rights reserved.
//

//---------------------------------------------------------------------------------
/*
*Date.h
*
*create by FlyingMaster Create on 2020年8月18日 9:18:15
*
*结构体: Student
*用于测试数据在数据库中数据文件以及索引文件的插入，删除和查询
*当前版本只支持插入指定Student格式的数据，不可自定义列
*
*类：DateBase
*用于在./date目录下创建DateBase数据库文件夹

*类：StudentTable
*用于：在数据库数据文件以及索引文件中添加数据,以及删除数据
*提供单个插入数据和从文件中插入数据两种insert()构造方法
*当前版本在删除数据时只支持在索引文件中删除，不支持删除数据库数据文件中的数据
*
*version: 1.0
*
*/
//---------------------------------------------------------------------------------

#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED

#include "BPTree2.h"

#include <fstream>
#include <iostream>
//#include "direct.h"
#include "assert.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string>
#define MaxTable 10
#define MaxColumn 10
#define MaxLength 20

using namespace std;

struct Student
{
    int sno;
    char sname[MaxLength];
    char ssex[MaxLength];
    int diff;
};

class DataBase
{
public:
    string dbName;
    //string dbTable[MaxTable];
    DataBase(string _dbname){
        
        this->dbName = _dbname;
            string folderPath = "/Users/zhaotong/C++Program/DSTrain/B+TreeV3.0/data/" + dbName;
            if (0 != access(folderPath.data(), 0))
            {
                // if this folder not exist, create a new one.
                int flag = mkdir(folderPath.data(),00700); // 返回 0 表示创建成功，-1 表示失败

                if (flag == 0)
                    cout << "Database make successfully" << endl;
                else
                    cout << "Database already exits" << endl;
            }
            else
                cout << "database " << dbName << " has already exits" << endl;
    }
};

//DataBase::DataBase(string _dbName)


class StudentTable
{
private:
    string tableName; //表名
    int n;            //行数
    string dbName;    //存在于哪一个数据库
    Student st_root;  //存储的数据的根
    BPTree *bptree;   //b+树
    int locate;       //存储初始文件末尾偏移量
public:
    StudentTable(){
        
            tableName = "student.td";
            dbName = "";
            n = 0;
            locate = 0;
            bptree = NULL;
    }
    bool CreateTable(string dbName);
    bool buildTrees(Student &st, int n);
    int insertData(string fileName);       //以文件的形式插入数据,返回为插入了多少条数据
    bool insertData(Student &st);          //单个数据插入
    int spilt_n(string temp);              //辅助文件形式的插入
    bool Outdate();                        //用于测试数据是否以二进制在文件中写入成功
    bool modifyDate(Student st, int diff); //测试能否修改指定位置的数据
};

//StudentTable::StudentTable()
//{
//    tableName = "student.td";
//    dbName = "";
//    n = 0;
//    locate = 0;
//    bptree = NULL;
//}

bool StudentTable::CreateTable(string _dbName){
    dbName = _dbName;
    string path = "/Users/zhaotong/C++Program/DSTrain/B+TreeV3.0/data/" + dbName + "/" + tableName;
    fstream file;
    file.open(path.data(), ios::in);
    if (file)
    {
        cout << "Table " << tableName << " has already exits in database " << dbName << endl;
        file.seekg(0, ios::end);
        locate = (int)file.tellg();
        file.close();
        cout << "locate为" << locate << endl;
    }
    else
    {
        //创建文件
        ofstream fout(path.data());
        if (fout)
        {
            // 如果创建成功
            cout << "Create table " << tableName << " successfully in database " << dbName << endl;
            // 执行完操作后关闭文件句柄
            fout.close();
        }
    }
    file.close();

    // string ProcessDatePath = "./data/" + dbName + "/" + tableName; //生成的数据库数据文件地址
    // ifstream fileOut(ProcessDatePath.data());;
    // if (!fileOut.is_open())
    // {
    //      cout << "Table " << tableName << " has already exits in database " << dbName << endl;
    // }
    // else
    // {
    //     fileOut.seekg(0, ios::end);
    //     locate = fileOut.tellg();
    //     fileOut.close();
    //     cout << "locate为" << locate << endl;
    // }
    return true;
}

//---------------------------------------------------------------------------------
/*
*int insertDate(string fileName);
*bool insertDate(Student st);
*
*create by FlyingMaster on 2020年8月18日 9:18:15
*
*分别用于从文件中插入数据，和单个插入数据
*从文件中插入数据时实际会调用单个插入数据，再调用B+Tree.insert(key,diff)在索引文件中进行插入，
*从文件中插入时返回成功插入了多少条数据，单个插入返回是否插入成功
*
*
*/
//---------------------------------------------------------------------------------

int StudentTable::insertData(string fileName)
{
    if (n == 0)
    {
        string filePath = "/Users/zhaotong/C++Program/DSTrain/B+TreeV3.0/data/" + dbName + "/" + "student.i";
        bptree = new BPTree(filePath);
    }
    Student st_temp;
    ifstream fileOut; //文件输入流
    int i = 0;        //记录插入多少数据

    string DatePath = "/Users/zhaotong/C++Program/DSTrain/B+TreeV3.0/data/" + fileName;

    cout << DatePath << endl;
    fileOut.open(DatePath.data(), ios::in); //打开原始数据文件读取
    assert(fileOut);

    if (!fileOut.is_open())
    {
        cout << "数据文件打开错误" << endl;
        exit(1);
    }
    while (!fileOut.eof())
    {
        /* code */
        fileOut >> st_temp.sno >> st_temp.sname >> st_temp.ssex; //将数据文件按行读入
        cout << st_temp.sno << st_temp.sname << st_temp.ssex << endl;
        if (insertData(st_temp))
        {
            i++;
        };
    }
    bptree->Travelsal();
    fileOut.close();
    cout << "成功插入 " << i << "条数据" << endl;
    return n;
}

bool StudentTable::insertData(Student &st)
{
    ofstream fileIn;                                               //文件输出流
    string ProcessDatePath = "/Users/zhaotong/C++Program/DSTrain/B+TreeV3.0/data/" + dbName + "/" + tableName; //生成的数据库数据文件地址
    fileIn.open(ProcessDatePath.data(), ios::binary | ios::app);   //以二进制输入的方式打开文件,打开，如果没有文件，那么生成空文件；如果有文件，那么在文件尾追加。
    if (!fileIn.is_open())
    {
        cout << "数据库数据文件打开错误" << endl;
        return false;
    }
    assert(fileIn);
    Triple loc=bptree->Search(st.sno);
    if(!loc.tag)return false;
    else{
    st.diff = locate;
    // fileIn.seekp(SEEK_SET); //将文件定位到文件尾部
    // cout << "插入文件末尾为 "<<fileIn.tellp() << endl;
    //streampos ps1 = fileIn.tellp();//获取当前偏移量
    fileIn.write((char *)&st, sizeof(Student));
    fileIn.close();
    locate += sizeof(Student);
    bptree->Insert(st.sno,locate-sizeof(Student),loc);
    //----------------------------------------------------------------
    /*
    *bptree.insert(st.sno,locate-sizeof(Student));
    *
    *bool B+Tree.insert()；参数为(key,locate-sizeof(student))
    *用于在B+树中进行插入key值，以及数据在数据库文件中的偏移量
    *如果插入成功则n++;
    */
    //----------------------------------------------------------------
    cout << "偏移量为 " << locate << endl;
    }
    return true;
}

//---------------------------------------------------------------------------------
/*
*Outdate();

*create by FlyingMaster on 2020年8月18日 9:18:15
*
*用于输出数据库数据文件，对插入数据进行测试以及输出
*
*/
//---------------------------------------------------------------------------------

bool StudentTable::Outdate()
{
    Student st;
    ifstream fileOut;
    int diff = 0;
    int n = 0;                                                     //数据量
    string ProcessDatePath = "/Users/zhaotong/C++Program/DSTrain/B+TreeV3.0/data/" + dbName + "/" + tableName; //生成的数据库数据文件地址
    cout << ProcessDatePath << endl;
    fileOut.open(ProcessDatePath.data(), ios::binary | ios::in);
    if (!fileOut.is_open())
    {
        cout << "打开数据库数据文件错误" << endl;
        return false;
    }
    assert(fileOut);
    fileOut.seekg(diff); //将文件定位到文件开头
    cout << "偏移量为" << diff << endl;
    while (fileOut.tellg() != -1) //当无数据或数据到达末尾直接退出
    {
        /* code */
        //!EOF只会检查上一次的状态，应当在循环中再次判断，防止文件末尾两次读出
        if (fileOut.peek() == EOF)
        {
            break;
        }
        fileOut.read((char *)&(st), sizeof(Student));
        cout << st.sno << " " << st.sname << " " << st.ssex << " " << st.diff << endl;
        diff = diff + sizeof(Student);
        cout << "偏移量为" << diff << endl;
        n++;
    }
    fileOut.close();
    cout << "共有 " << n << " 条数据" << endl;
    return true;
}

bool StudentTable::modifyDate(Student st, int diff)
{
    ofstream fileIn;                                                       //文件输出流
    string ProcessDatePath = "/Users/zhaotong/C++Program/DSTrain/B+TreeV3.0/data/" + dbName + "/" + tableName;         //生成的数据库数据文件地址
    fileIn.open(ProcessDatePath.data(), ios::binary | ios::out | ios::in); //用文件打开模式 ios::in，这样可以保证文件内容不会被清空，且文件指针偏移操作有效。
    if (!fileIn.is_open())
        return false;
    fileIn.seekp(diff);
    fileIn.write((char *)&st, sizeof(Student));
    fileIn.close();
    return true;
}

#endif // DATA_H_INCLUDED

