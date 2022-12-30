/*************************************************************************
    > File Name: CourseDesign.cpp
    > Author:Ivy
    > Mail: 2642427375@qq.com 
    > Created Time: Thu Dec 22 17:21:59 2022
 ************************************************************************/

#include <iostream>
#include <cstring>
#include <stack>
#include <queue>
using namespace std;
#define MaxVecNum 14
#define ArcNum 14
#define MaxInt 32767
#define MaxFloat 32767.0 


struct ArcType {
    int KM;
    float Time;
    int Cost; 
};

struct VertexType {
    int ID;
    string StationName;
};

typedef struct {
    ArcType arcs[MaxVecNum][MaxVecNum];
    VertexType vexs[MaxVecNum];
    int arcnum, vexnum;
}AMGraph;

//辅助数组Edge
struct {
    VertexType head;
    VertexType tail;
    ArcType weight;
}Edge[ArcNum];

int vexset[MaxVecNum];

int locateId(AMGraph G, string station) {
    int num = -1;
    for (int i = 0; i < G.vexnum; i++) {
        if (G.vexs[i].StationName == station) {
            num = i;
            return num;
        }
    }
    return num;
}

//craete AMGraph 
void CreateAMGraph(AMGraph &G){
    G.arcnum = 10;
    G.vexnum = 7;

    int id[7]={1,2,3,4,5,6,7};
    string name[7]={"北京","西安","郑州","徐州","成都","广州","上海"};
    for (int i = 0; i < G.vexnum; i++) {
        G.vexs[i].ID = id[i];
        G.vexs[i].StationName = name[i];
    }
    for (int i = 0; i < G.arcnum; i++) {
        for (int j = 0; j < G.arcnum; j++) {
            G.arcs[i][j].KM = MaxInt;
            G.arcs[i][j].Cost = 32767.0;
            G.arcs[i][j].Time = MaxInt;
        }
    }

    int start[10]={1,1,1,2,2,3,3,4,5,6},end[10]={2,3,4,3,5,4,6,7,6,7};
    int KM[10]={2553,695,704,511,812,349,1579,651,2368,1385};
    float Time[10]={8.0,2.3,2.5,1.5,3.0,1.2,5.0,2.0,7.0,4.0};
    int Money[10]={885,202,225,148,283,112,495,162,684,386};
    for (int i = 0; i < G.arcnum; i++) {
        int v1 = start[i], v2 = end[i];
        G.arcs[v1][v2].KM = KM[i];
        G.arcs[v1][v2].Time = Time[i];
        G.arcs[v1][v2].Cost = Money[i];
        G.arcs[v2][v1].KM = KM[i];
        G.arcs[v2][v1].Time = Time[i];
        G.arcs[v2][v1].Cost = Money[i];
    }
}

void PrintAMGraph(AMGraph G){
    for (int i = 0; i < G.vexnum; i++) {
        for (int j = 0; j < G.vexnum; j++) {
            cout << G.arcs[i][j].KM << "\t";
        }
        cout << "\n";
    }
}


//最短距离KM
bool S[MaxVecNum]={};//记录从源点v0到终点vi是否已经被确定最短长度
VertexType Path[MaxVecNum]={};//path记录的是v0到vi结点的路径上vi结点的前驱结点
int D[ArcNum]={};//D记录的是从源头v0到vi的最短路径长度
void MinPathByKm(AMGraph G,string station){
    cout<<station<<endl;
    cout<<"111"<<endl;
    int v0 = locateId(G, station);
    cout<<"333"<<endl;
    for (int i = 0; i < G.vexnum; i++) {
        cout<<"444"<<endl;
        S[i] = false;
        D[i] = G.arcs[v0][i].KM;
        if (D[i] < MaxInt) Path[i] = G.vexs[v0];
        else {
            Path[i].ID = -1;
            Path[i].StationName = "";
        }
    }
    S[v0] = true;
    cout<<"111"<<endl;
    D[v0] = 0;
    int v=0;
    cout<<"555"<<endl;
    for (int i = 1; i < G.vexnum; i++) {
        int min = MaxInt;
        for (int j = 0; j < G.vexnum; j++) {
            if (!S[j] && D[j] < min) {
                min = D[j];
                v = j;
            }
        }
        S[v] = true;
        for (int w = 0; w < G.vexnum; w++) {
            if (!S[w] && D[w] > D[v] + G.arcs[v][w].KM) {
                D[w] = D[v] + G.arcs[v][w].KM;
                Path[w] = G.vexs[v];
            }
        }
    }
}

VertexType num[MaxVecNum];
void PrintMinPathKM(AMGraph G, string startStation, string endStation) {
    int v1, v2;
    v1 = locateId(G, startStation);
    v2 = locateId(G, endStation);
    cout << startStation << "-->" << endStation << "最短路径: " << D[v2] <<"公里" << endl;
    int d = v2;
    int i = 0;
    num[i].ID = v2;
    num[i].StationName = endStation;
    i++;
    while (G.vexs[d].ID != v1+1){
        num[i] = Path[d];
        d = Path[d].ID-1;
        i++;
    }
    cout << "最短路径是: ";
    for (int v = i; v >= 0; v--) {
        cout << num[v].StationName<<"->";
    }
    cout << endl;
}

//最短时间Time
bool S1[MaxVecNum];//记录从源点v0到终点vi是否已经被确定最短长度
VertexType Path1[MaxVecNum];//path记录的是v0到vi结点的路径上vi结点的前驱结点
float D1[ArcNum];//D记录的是从源头v0到vi的最短路径长度
void MinPathByTime(AMGraph G, string station) {
    int v0 = locateId(G, station);
    for (int i = 0; i < G.vexnum; i++) {
        S1[i] = false;
        D1[i] = G.arcs[v0][i].Time;
        if (D1[i] < MaxInt) Path1[i] = G.vexs[v0];
        else {
            Path1[i].ID = -1;
            Path1[i].StationName = "";
        }
    }
    S1[v0] = true;
    D1[v0] = 0;
    int v;
    for (int i = 1; i < G.vexnum; i++) {
        float min = MaxInt;
        for (int j = 0; j < G.vexnum; j++) {
            if (!S1[j] && D1[j] < min) {
                min = D1[j];
                v = j;
            }
        }
        S1[v] = true;
        for (int w = 0; w < G.vexnum; w++) {
            if (!S1[w] && D1[w] > D1[v] + G.arcs[v][w].Time) {
                D1[w] = D1[v] + G.arcs[v][w].Time;
                Path1[w] = G.vexs[v];
            }
        }
    }
}

void PrintMinPathTime(AMGraph G, string startStation, string endStation) {
    int v1, v2;
    v1 = locateId(G, startStation);
    v2 = locateId(G, endStation);
    cout << startStation << "-->" << endStation << "最短时间:" << D1[v2] << "小时" << endl;
    stack<VertexType> S;
    int d = v2;
    S.push(G.vexs[v2]);
    while (G.vexs[d].ID != v1 + 1)
    {
        S.push(Path[d]);
        d = Path[d].ID - 1;
    }
    cout << "路线为:";
    VertexType V;
    while (!S.empty()) {
        V = S.top();
        S.pop();
        cout << V.StationName << "->";
    }
    cout << endl;
}



//最小价格cost
bool S2[MaxVecNum];//记录从源点v0到终点vi是否已经被确定
VertexType Path2[MaxVecNum];//path记录的是v0到vi结点的路径上vi结点的前驱结点
int D2[ArcNum];//D记录的是从源头v0到vi的最短路径长度
void MinPathByCost(AMGraph G, string station) {
    int v0 = locateId(G, station);
    for (int i = 0; i < G.vexnum; i++) {
        S2[i] = false;
        D2[i] = G.arcs[v0][i].Cost;
        if (D2[i] < MaxInt) Path2[i] = G.vexs[v0];
        else {
            Path2[i].ID = -1;
            Path2[i].StationName = "";
        }
    }
    S[v0] = true;
    D[v0] = 0;
    int v;
    for (int i = 1; i < G.vexnum; i++) {
        int min = MaxInt;
        for (int j = 0; j < G.vexnum; j++) {
            if (!S2[j] && D2[j] < min) {
                min = D2[j];
                v = j;
            }
        }
        S2[v] = true;
        for (int w = 0; w < G.vexnum; w++) {
            if (!S2[w] && D2[w] > D2[v] + G.arcs[v][w].Cost) {
                D2[w] = D2[v] + G.arcs[v][w].Cost;
                Path2[w] = G.vexs[v];
            }
        }
    }
}

void PrintMinPathCost(AMGraph G, string startStation, string endStation) {
    int v1, v2;
    v1 = locateId(G, startStation);
    v2 = locateId(G, endStation);
    cout << startStation << "->" << endStation << "最小价格: " << D2[v2] << "元" << endl;
    stack<VertexType> S;
    int d = v2;
    S.push(G.vexs[v2]);
    while (G.vexs[d].ID != v1 + 1)
    {
        S.push(Path[d]);
        d = Path[d].ID - 1;
    }
    cout << "路线为: ";
    VertexType V;
    while (!S.empty()) {
        V = S.top();
        S.pop();
        cout << V.StationName << "->";
    }
    cout << endl;
}



//求最小中转数
int dist[ArcNum];
VertexType Path3[MaxVecNum];
void MinPathByStationCount(AMGraph G,string startStation){
    int k = locateId(G, startStation);
    for (int i = 0; i < G.vexnum; i++) {
        if (i != k) dist[i] = -1;
    }
    dist[k] = 0;
    queue<VertexType> Q;
    Q.push(G.vexs[k]);
    VertexType V;
    while (!Q.empty()) {
        V = Q.front();
        Q.pop();
        for (int i = 0; i < G.vexnum; i++) {
            //这里如果两点间无边,边里面的三个值都是MAXInt,故可三选一
            if (G.arcs[V.ID-1][i].KM < MaxInt && dist[i] == -1) {
                dist[i] = dist[V.ID-1] + 1;
                Path3[i] = V;
                Q.push(G.vexs[i]);  
            }
        }
    }
}

void PrintUnweightedPath(AMGraph G,string startStation,string endStation) {
    int v1, v2;
    v1 = locateId(G, startStation);
    v2 = locateId(G, endStation);
    cout << startStation << "->" << endStation << "最小中转次数: " << dist[v2] << "次" << endl;
    stack<VertexType> S;
    int d = v2;
    S.push(G.vexs[v2]);
    while (G.vexs[d].ID != v1 + 1)
    {
        S.push(Path3[d]);
        d = Path3[d].ID - 1;
    }
    cout << "路线为: ";
    VertexType V;
    while (!S.empty()) {
        V = S.top();
        S.pop();
        cout << V.StationName << "->";
    }
    cout << endl;
}

void Show(){
    cout << "    **********************************************\n";
    cout << "    ----------------------------------------------\n";
    cout << "        1-距离短 2-最便宜 3-最快抵达 4-最小中转\n";
    cout << "    ----------------------------------------------\n";
    cout << "    站台: 北京  西安  郑州  徐州  成都  广州  上海\n";
    cout << "    ----------------------------------------------\n";
    cout << "    **********************************************\n";
}

int main(){
    system("chcp 65001");   
    AMGraph G;
    CreateAMGraph(G);
    // PrintAMGraph(G);
    int c;
    while (1){
        Show();
        string startStation, endStation;
        cout << "选择的查询方式：";
        cin >> c;
        if (c != 0) {
            cout<< "起始站--终点站：";
            cin >> startStation >> endStation;
        }
        cout<<startStation<<"\t"<<endStation<<endl;
        switch (c){
        case 1: 
            cout<<"111"<<endl;
            MinPathByKm(G, startStation);
            PrintMinPathKM(G, startStation, endStation);
            break;
        case 2: 
            MinPathByCost(G, startStation);
            PrintMinPathCost(G, startStation, endStation);
            break;
        case 3: 
            MinPathByTime(G, startStation);
            PrintMinPathTime(G, startStation, endStation);
            break;
        case 4: 
            MinPathByStationCount(G, startStation);
            PrintUnweightedPath(G, startStation, endStation);
            break;
        case 5: 
            break;
        default:
            break;
        }
        int ci;
        cout<<"输入 0--退出：";cin>>ci;
        if (ci==0) break;
        system("cls");
    }
}


