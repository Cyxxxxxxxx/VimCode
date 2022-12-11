/*************************************************************************
    > File Name: Graph.cpp
    > Author:Ivy
    > Mail: 2642427375@qq.com 
    > Created Time: Sun Dec  4 21:10:18 2022
 ************************************************************************/

#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

#define MaxInt 32767
#define MaxNode 100
#define QueueMaxSize 100
#define OK 1

typedef int VerTexType;
typedef int ArcType;


typedef struct {
    VerTexType vexs[MaxNode];
    ArcType arcs[MaxNode][MaxNode];
    int vexnum,arcnum;
}AMGraph;

AMGraph G;

//use adjuvant queue
typedef struct {
    int *base;
    int front,rear;
}AdjuQueue;


int InitAdjuQueue(AdjuQueue &AQ){
    AQ.base = new int[QueueMaxSize];
    if (!AQ.base) exit(0);
    AQ.front = AQ.rear=0;
    return OK;
}

int InsQueue(AdjuQueue &AQ,int e){
    if ((AQ.rear+1)%QueueMaxSize == AQ.front) return 0;
    AQ.base[AQ.rear]=e;
    AQ.rear = (AQ.rear+1)%QueueMaxSize;
    return OK;
}

int DelQueue(AdjuQueue &AQ,int &e){
    if(AQ.front==AQ.rear) return 0;
    e=AQ.base[AQ.front];
    AQ.front = (AQ.front+1)%QueueMaxSize;
    return OK;
}

int AdjuQueueEmpty(AdjuQueue &AQ){
    if(AQ.front==AQ.rear) return OK;
    else return 0;
}

int LocateVex(AMGraph G,int b){
    int a;
    for(a=0;a<G.vexnum;a++){
        if(G.vexs[a]==b)
        return a;
    }
}

int CreateUDN(AMGraph &G,int vex,int arc,int Avex[],int Aarc[],int AddAvex[]){
    G.vexnum = vex;
    G.arcnum =arc;
    for (int i=0;i<G.vexnum;i++) 
        G.vexs[i]=Avex[i];
    for (int i=0;i<G.vexnum;i++)
        for (int j=0;j<G.vexnum;j++)
            G.arcs[i][j]=MaxInt;
    for (int k=0;k<AddAvex.lenght;k++){
        G.arcs[AddAvex[k]][AddAvex[k+1]]=Aarc[k%2];
        G.arcs[AddAvex[k+1]][AddAvex[k]]=G.arcs[AddAvex[k]][AddAvex[k+1]];
        k+=2;
    }
    return OK;
}

bool Visited[MaxNode];  //visited array   init"false"

void DFS_AM(AMGraph G,int v){
    cout<<v;
    int w;
    Visited[v]=1;
    for(w=1;w<=G.vexnum;w++)
        if ((G.arcs[v][w]!=0)&&(!Visited[w]))
            DFS_AM(G,w);
}

void DFSTraverse(AMGraph G){
    int v;
    for(v=0;v<G.vexnum;v++)
        Visited[v]=0;
    for(v=1;v<=G.vexnum;v++)
        if(!Visited[v])
            DFS_AM(G,v);  //call DFS_AM()
}

void BFS(AMGraph G,int v){
    cout<<v;
    int u,w;
    AdjuQueue AQ;
    
    Visited[v]=1;
    InitAdjuQueue(AQ);
    while(!AdjuQueueEmpty(AQ)){
        DelQueue(AQ,u);
        for(w=1;w<=G.vexnum;w++)
            if((G.arcs[u][w]!=0)&&(!Visited[w])){
                cout<<w;
                Visited[w]=1;
                InsQueue(AQ,w);
            }
    }
}

int main(){
    int vex=7,arc=9;
    int Avex[7]={0,1,2,3,4,5,6};
    int AddAvex[18]={0,1,1,2,2,3,3,4,4,5,5,0,1,6,3,6,4,6};
    int Aarc[9]={28,16,12,22,25,10,14,18,24};
    CreateUDN(G,vex,arc,Avex[],Aarc[]);
    

}
