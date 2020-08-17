/*
 * =====================================================================================
 *
 *       Filename:  makeDate.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2020/08/17 15时22分41秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  赵桐
 *   Organization:  
 *
 * =====================================================================================
 */
// #include <stdlib.h>
// #include <stdio.h>
// #include <time.h>

// int main(){
// 	char *strArrayLastName[]={"赵","钱","孙","李","周","吴","郑","王","冯","陈","褚","卫","蒋","沈","韩","杨"};
// 	char *strArrayFirstName[]={"管波","新竹","信阳","与寻","沈","龙藏","云新","自汉","景雷","自旋","与泽","瑞军","家文","晓明","一番","佳凝","玉飞","子龙"};
// 	char *strArraySex[2]={"男","女"};
// 	srand((unsigned)time(NULL));
// 	int i=100000,key;
// 	char shell[80];
// 	while(i--&&i>=0){
// 		key=rand()%100000;
// 		sprintf(shell,"echo \"%d %s%s %s\">> date.txt",key,strArrayLastName[rand()%16],strArrayFirstName[rand()%18],strArraySex[rand()%2]);
// 		system(shell);
// 	}
// }
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>

int main()
{      FILE* fd;

       fd=fopen("./date.txt","a+");
       char*surname[]={"赵","钱","孙","李","周","吴","郑","王","冯","陈","褚","卫","蒋","沈","韩","杨"};
       char *lastname[]={"管波","新竹","信阳","与寻","沈","龙藏","云新","自汉","景雷","自旋","与泽","瑞军","家文","晓明","一番","佳凝","玉飞","子龙"};
       char *gender[]={"男","女"};
       srand((int)time(0));
     int i=100000;

      while(i>0)
{    int z=rand()%16;
        int x=rand()%18;
        int b=rand()%2;
      char*s=surname[z];
      char*v=lastname[x];
      char*m=gender[b];
        fprintf(fd,"%d %s%s %s\n",rand()%100000,s,v,m);
        i--;
}
}
