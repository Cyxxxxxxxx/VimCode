/*************************************************************************
    > File Name: SearchAndSort.cpp
    > Author:Ivy
    > Mail: 2642427375@qq.com 
    > Created Time: Fri Dec 16 10:30:45 2022
 ************************************************************************/

#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<vector>
#include<algorithm>
#include<ctime>

using namespace std;

//init Array
void InitArr(int AimArr[]){
    srand((int)time(NULL));
    for (int i = 0; i <16;i++){
        AimArr[i] = (rand()%90)+10;
    }
}

void PrintArr(int AimArr[]){
    for(int i=0;i<16;i++){
        cout<<AimArr[i]<<" ";
    }
    cout<<endl;
}






int main(){
    int AimArr[16]={},AimArrCopy[16]={};	
    InitArr(AimArr);
    memcpy(AimArrCopy,AimArr,sizeof(AimArr));
    PrintArr(AimArr);
    PrintArr(AimArrCopy);


}
