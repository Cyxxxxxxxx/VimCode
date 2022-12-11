/*************************************************************************
    > File Name: HofumanTree.cpp
    > Author: Wqr_
    > Mail: xueduanwei@126.com 
    > Created Time: Tue Nov 29 22:17:03 2022
 ************************************************************************/

#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
int main(){
    int a=1,b=2;
    cout<<"a= "<<a<<"  b="<<b<<endl;
    a += b;
    cout<<"a= "<<a<<"  b="<<b<<endl;
    b = a-b;
    a -=b; 
    cout<<"a= "<<a<<"  b="<<b<<endl;
}

