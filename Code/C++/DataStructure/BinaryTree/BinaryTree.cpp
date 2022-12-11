/*************************************************************************
    > File Name: BinaryTree.cpp
    > Author: Wqr_
    > Mail: xueduanwei@126.com 
    > Created Time: Thu Dec  1 14:38:09 2022
 ************************************************************************/

#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
template<typename T>
struct BinTreeNode{
     T data;    //结点中存储的数据
     BinTreeNode<T> *lc, *rc;    //左子树和右子树
     BinTreeNode() :leftChild(NULL), rightChild(NULL) {}    //无参构造函数
     BinTreeNode(T x, BinTreeNode<T> *l = NULL, BinTreeNode<T> *r = NULL) :data(x), leftChild(l), rightChild(r) {}    //带默认值的有参构造参数
};


