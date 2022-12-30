/*************************************************************************
    > File Name: CourseDesign.cpp
    > Author:Ivy
    > Mail: 2642427375@qq.com 
    > Created Time: Thu Dec 22 17:21:59 2022
 ************************************************************************/

#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<vector>
#include<algorithm>
#include<assert.h>
using namespace std;
#define max 7

bool S[max]={};
int Path[max]={};
int D[max]={};


//Node
class Node{
    public:
        char Num;
        string Name;
        bool Visited;

    public:
        Node(char num = 0,string name = ""){
            Num = num;
            Name = name;
            Visited =  false;
        }
        Node(const Node &other){
            if(this == &other) return;
            *this = other;
        }

        Node &operator=(const Node &other){
            if(this == &other) return *this;
            this->Num = other.Num;
            this->Name = other.Name;
            this->Visited = other.Visited;
            return *this;
        }
};

//Edge
class Edge{
    public:
        int NodeIndexA; //head node
        int NodeIndexB; //tail node
        int Distance;
        double Time;
        int Spending;
        bool    Selected; //wheather selected
    public:
        Edge(int nodeIndexA = 0,int nodeIndexB =0,int distance = 0,char time = 0,int spending =0 ): NodeIndexA(nodeIndexA),
                                                                                                    NodeIndexB(nodeIndexB),
                                                                                                    Distance(distance),
                                                                                                    Time(time),
                                                                                                    Spending(spending),
                                                                                                    Selected(false){}
        Edge(const Edge &other){
            if(this == &other) return;
            *this = other ;
        }

        Edge &operator=(const Edge &edge){
            if(this ==&edge) return *this;
            this->NodeIndexA = edge.NodeIndexA;
            this->NodeIndexB = edge.NodeIndexB;
            this->Distance = edge.Distance;
            this->Time = edge.Time;
            this->Spending = edge.Spending;
            this->Selected = edge.Selected;
            return *this;
        }
};

//Graphs
class CMap{
    private:
        int Capacity; //total number of node
        int NodeCount; //current node number;
        Node *NodeArray; //node set
        int *Matrix; //Ajacency Matrix
        Edge *EdgeArray; //miniTree set

    public:
        CMap(int capacity){
            Capacity = capacity;
            NodeCount = 0;
            NodeArray = new Node[Capacity];
            Matrix = new int[Capacity*Capacity];
            memset(Matrix,0,Capacity*Capacity *sizeof(int));
            EdgeArray = new Edge[10];
        }
        ~CMap(void){
            delete[] NodeArray;
            delete[] Matrix;
            delete[] EdgeArray;
        }
    
    public:
        //add node
        void AddNode(Node *node){
            assert(node);
            NodeArray[NodeCount].Num = node->Num;
            NodeArray[NodeCount].Name = node->Name;
            NodeCount++;
        }
        void ResetNode(){
            for(int i = 0; i < NodeCount;i++){
                NodeArray[i].Visited = false;
            }
        }
        bool SetValueToMatrixForUndirectedGraph(int row,int col,int distance,double time,int spending){
            if(row>0||row>=Capacity)return false;
            if(col>0||col>=Capacity)return false;
            Matrix[row*Capacity+col] = distance;
            Matrix[col*Capacity+row] = distance;
            EdgeArray[row].Distance=distance;
            EdgeArray[row].Time=time;
            EdgeArray[row].Spending=spending;
            return true;
        }
        bool GetValueFromMatrix(int row,int col,int &val){
            if(row<0|| row>=Capacity) return false;
            if(col<0|| col>=Capacity) return false;
            val = Matrix[row*Capacity+col];
            return true;
        }
        void PrintMatrix(){
            for(int i = 0; i < Capacity;i++){
                for(int j=0;j<Capacity;j++)
                    cout<<Matrix[i*Capacity+j]<<"  ";
                cout<<endl;
            }
        }

    public:
        void ShortestPathDijkstra(int index){
            //init required things
            for(int v= 0;v < Capacity;v++){
                S[v] = false;
                int valu = GetValueFromMatrix(v,index,valu);
                D[v] = valu;
                if (D[v]!=0) Path[v]=index;
                else Path[v]= -1;
            }
            S[index]=true; //index join S[]
            D[index] = 0; //index to index weight is 0

            for (int i=1;i<Capacity;i++){
                int v = index,min = 0;
                for(int w=0;w<Capacity;w++){
                    if(!S[w]&&D[w]!=min){ //choose one path about destination is v
                        v = w;
                        min = D[w];
                    }
                    S[v]=true;
                    for(int w= 0;w<Capacity;w++){
                        int val ;
                        GetValueFromMatrix(v,w,val);
                        if(!S[w]&&(D[v]+val <D[w])){
                            D[w] = D[v] +val; //renew D[w]
                            Path[w] = v; //renew w's preVec is v
                        }
                    }
                }
            }
        }
};
int main(){
    system("chcp 65001");
    CMap *pMap  =new CMap(7);

    Node *pNode0 = new Node('1',"北京");
    Node *pNode1 = new Node('2',"西安");
    Node *pNode2 = new Node('3',"郑州");
    Node *pNode3 = new Node('4',"徐州");
    Node *pNode4 = new Node('5',"成都");
    Node *pNode5 = new Node('6',"广州");
    Node *pNode6 = new Node('7',"上海");

    pMap->AddNode(pNode0);
    pMap->AddNode(pNode1);
    pMap->AddNode(pNode2);
    pMap->AddNode(pNode3);
    pMap->AddNode(pNode4);
    pMap->AddNode(pNode5);
    pMap->AddNode(pNode6);

    pMap->SetValueToMatrixForUndirectedGraph(0,1,2553,8,885);
    pMap->SetValueToMatrixForUndirectedGraph(0,2,695,2.3,202);
    pMap->SetValueToMatrixForUndirectedGraph(0,3,704,2.5,225);
    pMap->SetValueToMatrixForUndirectedGraph(1,2,511,1.5,148);
    pMap->SetValueToMatrixForUndirectedGraph(1,4,812,3,283);
    pMap->SetValueToMatrixForUndirectedGraph(2,3,349,1.2,112);
    pMap->SetValueToMatrixForUndirectedGraph(2,3,349,1.2,112);
    pMap->SetValueToMatrixForUndirectedGraph(3,6,651,2,162);
    pMap->SetValueToMatrixForUndirectedGraph(4,5,2368,7,684);
    pMap->SetValueToMatrixForUndirectedGraph(5,6,1385,4,386);


    pMap->PrintMatrix();
    cout<<"1-北京 2-西安 3-郑州 4-徐州 5-成都 6-广州 7-上海"<<endl;
    cout<<"请选择始发地与目的地(0-退出选择): "<<endl;
    int s,e;
    cin>>s;cin>>e;
    pMap->ShortestPathDijkstra(s);
    for(int i=0;i<sizeof(S);i++){
        cout<<S[i]<<"\t";
    }
    cout<<endl;
    for(int i=0;i<sizeof(D);i++){
        cout<<D[i]<<" ";
    }
    cout<<endl;
    for(int i=0;i<sizeof(Path);i++){
        cout<<Path[i]<<" ";
    }
    // pMap->PrintMatrix();

}
