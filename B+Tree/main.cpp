//
//  main.cpp
//  B+Tree
//
//  Created by 赵桐 on 2020/8/11.
//  Copyright © 2020 赵桐. All rights reserved.
//

#include <iostream>
#include "B+Tree.h"
int main(int argc, const char * argv[]) {
    // insert code here...
    BPTree * bp = new BPTree();
    bp->Insert(01);
    bp->Insert(24);
    bp->Insert(39);
    bp->Insert(72);
    bp->Insert(53);
     bp->Insert(63);
//    bp->Insert(71);
     bp->Insert(90);
     bp->Insert(88);
    bp->Insert(15);
    bp->Insert(10);
//    bp->Insert(91);
    bp->Insert(44);
    bp->Insert(68);
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
