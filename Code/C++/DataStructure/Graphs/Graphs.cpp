/*************************************************************************
    > File Name: Graphs.cpp
    > Author:Ivy
    > Mail: 2642427375@qq.com 
    > Created Time: Fri Dec  2 10:47:21 2022
 ************************************************************************/

#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

//Node
class Node {
    public:
        Node(char data=0){
            m-cData=data;
            m_bVisited=false;
        }
        Node(const Node＆node){
            if(this ==＆node)return;
            ＊this = node;
        }

        Node＆operator=(const Node＆node){
            if(this==＆node)return ＆this;
            this->m_cData =node.m_cData;
            this->m_bVisited = node.m_bVisited;
            return ＊this;
        }

    public:
        char m_cData;
        bool m_bVisited;
}

//Edge
class Edge{
    public:
       Edge(int nodeIndexA =0,int nodeIndexB=0,int weightValue=0):
           m_iNodeIndexA(nodeIndexA),
           m_iNodeIndexB(nodeIndexB),
           m_iWeightValue(weightValue),
           m_bSelected(false){ }
       Edge(const Edge &edge){
           if(this=&edge)return;
           *this=edge;
       }
       Edge &operator =(const Edge &edge){
           if (this=&edge)return *this;
           this->m_iNodeIndexA=edge.m_iNodeIndexA;
           this->m_iNodeIndexB=edge.m_iNodeIndexB;
           this->m_iWeightValue=edge.m_iWeightValue;
           this->m_bSelected=edge.m_bSelected;
           return *this;
       }

    public:
        int m_iNodeIndexA; //head node
        int m_iNodeIndexB; //tail node
        int m_iWeightValue;
        bool m_bSelected; //wheather selected
}

//Graphs
class CMap{
    private:
        int m_iCapacity; //total number of node
        int m_iNodeCount;//current node number
        Node ＊m_pNodeArray;//
        int ＊m_pMatrix;//lingjiejuzhneg
        Edge ＊m_pEdgeArray;

    public:
        CMap(int iCapacity){
            m_iCapacity =iCapacity;
            m_iNodeCount=0;
            m_pNodeArray=new Node[m_iCapacity];
            m_pMatrix=new int[m_iCapacity*m_iCapacity];
            memset(m_pMatrix,0,m_iCapacity*m_iCapacity*sizeof(int));
            m_pEdgeArray=new Edge[m_iCapacity-1];
        }
        ~Map(void){
            delete[]m_pNodeArray;
            delete[]m_pMatrix;
            delete[]m_pEdgeArray;
        }

    private:
        //guangdubianli
        void BreadthFirstTraverseImpl(vector<int> preVec){
            int val=0;
            vector<int>curVec;
            for (int i=0;i<(int)preVec.size();i++){
                for (int j=0;j<m_iCapacity;j++){
                    GetValueFromMatrix(preVec[i],j,val);
                    if(val !=0){
                        if (m_pNodeArray[j].m_bVisited) continue;
                        cout<<m_pNodeArray[j].m_cData<<" ";
                        m_pNodeArray[j].m_bVisited=true;
                        curVec.push_back(j);
                    }else continue;
                }
            }
            if (curVec.empty()) return;
            else BreadthFirstTraverseImpl(curVec);
        }

        //Get min Edge
        int GetMinEdge(const vector<Edge> &edgeVec){
            int min =0,MinEdge=0;
            for (int i=0;i<(int)edgeVec.size();i++){
                if (edgeVec[i].m_bSelected) continue;
                min = edgeVec[i].m_iWeightValue;
                MinEdge =i;
            }
            for (int i=0;i<(int)edgeVec.size();i++){
                if (edgeVec[i].m_bSelected) continue;
                if (min>edgeVec[i].m_iWeightValue){
                    min =edgeVec[i].m_iWeightValue;
                    MinEdge=i;
                }
            }
            if (min==0) return -1;
            return MinEdge;
        }

    
        
}
