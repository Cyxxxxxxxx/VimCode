/*************************************************************************
    > File Name: Graphs.cpp
    > Author:Ivy
    > Mail: 2642427375@qq.com
    > Created Time: Fri Dec  2 10:47:21 2022
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
#include<assert.h>
using namespace std;

// Node
class Node{
public:
    Node(char data = 0){
        m_cData = data;
        m_bVisited = false;
    }
    Node(const Node &node){
        if (this == &node)
            return;
        *this = node;
    }

    Node &operator=(const Node &node){
        if (this == &node)
            return *this;
        this->m_cData = node.m_cData;
        this->m_bVisited = node.m_bVisited;
        return *this;
    }

public:
    char m_cData;
    bool m_bVisited;
};

// Edge
class Edge{
public:
    Edge(int nodeIndexA = 0, int nodeIndexB = 0, int weightValue = 0) : m_iNodeIndexA(nodeIndexA),
                                                                        m_iNodeIndexB(nodeIndexB),
                                                                        m_iWeightValue(weightValue),
                                                                        m_bSelected(false) {}
    Edge(const Edge &edge){
        if (this == &edge)
            return;
        *this = edge;
    }
    Edge &operator=(const Edge &edge){
        if (this == &edge)
            return *this;
        this->m_iNodeIndexA = edge.m_iNodeIndexA;
        this->m_iNodeIndexB = edge.m_iNodeIndexB;
        this->m_iWeightValue = edge.m_iWeightValue;
        this->m_bSelected = edge.m_bSelected;
        return *this;
    }

public:
    int m_iNodeIndexA; // head node
    int m_iNodeIndexB; // tail node
    int m_iWeightValue;
    bool m_bSelected; // wheather selected
};

// Graphs
class CMap{
private:
    int m_iCapacity;     // total number of node
    int m_iNodeCount;    // current node number
    Node *m_pNodeArray; // node jihe
    int *m_pMatrix;     // lingjiejuzhneg
    Edge *m_pEdgeArray;     //最小生成树边集合

public:
    CMap(int iCapacity){
        m_iCapacity = iCapacity;
        m_iNodeCount = 0;
        m_pNodeArray = new Node[m_iCapacity];
        m_pMatrix = new int[m_iCapacity * m_iCapacity];
        memset(m_pMatrix, 0, m_iCapacity * m_iCapacity * sizeof(int));
        m_pEdgeArray = new Edge[m_iCapacity - 1];
    }
    ~CMap(void){
        delete[] m_pNodeArray;
        delete[] m_pMatrix;
        delete[] m_pEdgeArray;
    }

private:
    // Breadth-First Search
    void BreadthFirstTraverseImpl(vector<int> preVec){
        int val = 0;
        vector<int> curVec;
        for (int i = 0; i < (int)preVec.size(); i++){
            for (int j = 0; j < m_iCapacity; j++){
                GetValueFromMatrix(preVec[i], j, val);
                if (val != 0){
                    if (m_pNodeArray[j].m_bVisited)
                        continue;
                    cout << m_pNodeArray[j].m_cData << "  ";
                    m_pNodeArray[j].m_bVisited = true;
                    curVec.push_back(j);
                }else continue;
            }
        }
        if (curVec.empty())
            return;
        else
            BreadthFirstTraverseImpl(curVec);
    }

    //Floyd
    void floyd(){
        for(int i=1;i<=m_iCapacity; i++)
            for(int j=1;j<=m_iCapacity; j++)
                for(int k=1;k<=m_iCapacity; k++){
                    if(m_pMatrix[j*k]>m_pMatrix[j*i]+m_pMatrix[k*i]) m_pMatrix[j*k]=m_pMatrix[j*i]+m_pMatrix[k*i];
                }
    }

    // Get min Edge
    int GetMinEdge(const vector<Edge> &edgeVec){
        int min = 0, MinEdge = 0;
        for (int i = 0; i < (int)edgeVec.size(); i++){
            if (edgeVec[i].m_bSelected)
                continue;
            min = edgeVec[i].m_iWeightValue;
            MinEdge = i;
        }
        for (int i = 0; i < (int)edgeVec.size(); i++){
            if (edgeVec[i].m_bSelected)
                continue;
            if (min > edgeVec[i].m_iWeightValue){
                min = edgeVec[i].m_iWeightValue;
                MinEdge = i;
            }
        }
        if (min == 0)
            return -1;
        return MinEdge;
    }

    bool IsInSet(const vector<int> &nodeset,int target){
        for (int i = 0;i< (int)nodeset.size();i++){
            if (nodeset[i] == target) return true;
        }
        return false;
    }

    void MergeNodeSet(vector<int> &nodesetA,const vector<int> &nodesetB){
        for (size_t i = 0;i<(int)nodesetB.size();i++){
            nodesetA.push_back(nodesetB[i]);
        }
    }

public:
    //add node
    void AddNode(Node *node){
        assert(node);
        m_pNodeArray[m_iNodeCount].m_cData = node ->m_cData;
        m_iNodeCount++;
    }
    void ResetNode(){
        for (int i = 0; i < m_iNodeCount;i++){
            m_pNodeArray[i].m_bVisited = false;
        }
    }
    bool SetValueToMatrixForDirectedGraph(int row,int col,int val = 1){
        if(row<0 ||row>=m_iCapacity) return false;
        if (col<0 ||col>=m_iCapacity) return false;
        m_pMatrix[row*m_iCapacity+col] = val;
        return true;
    }
    bool SetValueToMatrixForUndirectedGraph(int row,int col,int val = 1){
        if(row<0 ||row>=m_iCapacity) return false;
        if (col<0 ||col>=m_iCapacity) return false;
        m_pMatrix[row*m_iCapacity+col] = val;
        m_pMatrix[col*m_iCapacity+row] = val;
        return true;
    }
    bool GetValueFromMatrix(int row,int col,int &val){
        if(row<0 ||row>=m_iCapacity) return false;
        if (col<0 ||col>=m_iCapacity) return false;
        val=m_pMatrix[row*m_iCapacity + col];
        return true;
    }

    void PrintMatrix(){
        for(int i=0;i<m_iCapacity;i++){
            for (int j =0;j<m_iCapacity;j++)
                cout<< m_pMatrix[i*m_iCapacity +j]<<"  ";
            cout<< endl;
        }
    }


    // Depth-First Search
    void DepthFirstTraverse(int index){
        int val =0;
        cout<< m_pNodeArray[index].m_cData <<"  ";
        m_pNodeArray[index].m_bVisited = true;
        for(int i=0;i<m_iCapacity;i++){
            GetValueFromMatrix(index,i,val);
            if (val != 0){
                if (m_pNodeArray[i].m_bVisited) continue;
                DepthFirstTraverse(i);
            }else continue;
        }
    }

    // Breath-First Search
    void BreadthFirstTraverse(int index){
        cout<< m_pNodeArray[index].m_cData<<"  ";
        m_pNodeArray[index].m_bVisited = true;
        vector<int> curVec;
        curVec.push_back(index);
        BreadthFirstTraverseImpl(curVec);
    }

    //Mini Tree (Prim algorithm)
    void PirmTree(int index){
        int val = 0;
        int iEdgeCount = 0;
        vector<Edge> edgeVec;

        vector<int> nodeIndexVec;
        nodeIndexVec.push_back(index);

        while(iEdgeCount < m_iCapacity -1){
            int row = nodeIndexVec.back();
            cout<< m_pNodeArray[row].m_cData<<endl;
            m_pNodeArray[row].m_bVisited = true;

            for(int i = 0; i < m_iCapacity;i++){
                GetValueFromMatrix(row,i,val);
                if (val ==0) continue;
                if(m_pNodeArray[i].m_bVisited) continue;
                Edge edge(row,i,val);
                edgeVec.push_back(edge);
            }

            int retIndex = GetMinEdge(edgeVec);
            if(retIndex !=-1){
                edgeVec[retIndex].m_bSelected = true;
                m_pEdgeArray[iEdgeCount] =  edgeVec[retIndex];
                cout<<m_pNodeArray[m_pEdgeArray[iEdgeCount].m_iNodeIndexA].m_cData <<" - ";
                cout<<m_pNodeArray[m_pEdgeArray[iEdgeCount].m_iNodeIndexB].m_cData<<" (";
                cout<<m_pEdgeArray[iEdgeCount].m_iWeightValue<<") "<<endl;
                iEdgeCount++;

                int iNodeIndex = edgeVec[retIndex].m_iNodeIndexB;
                m_pNodeArray[iNodeIndex].m_bVisited=true;
                nodeIndexVec.push_back(iNodeIndex);
            }
        }
    }

    //Mini Tree (Krushal)
    void KruskakTree(){
        int val = 0;
        int edgeCount = 0;

        vector<vector<int>> nodeSets;

        //first--get all edge
        vector<Edge> edgeVec;
        for(int i=0;i<m_iCapacity;i++){
            for(int j=i+1;j<m_iCapacity;j++){
                GetValueFromMatrix(i,j,val);
                if(val ==0) continue;
                if(m_pNodeArray[i].m_bVisited) continue;
                Edge edge(i,j,val);
                edgeVec.push_back(edge);
            }
        }
        //second find edge that make up MiniTree from all edges(first--get)
        while(edgeCount <m_iCapacity-1){
            int retIndex = GetMinEdge(edgeVec);
            if(retIndex != -1){
                edgeVec[retIndex].m_bSelected = true;

                int nodeAIndex = edgeVec[retIndex].m_iNodeIndexA;
                int nodeBIndex = edgeVec[retIndex].m_iNodeIndexB;

                bool nodeAInSet = false;
                bool nodeBInSet = false;
                int nodeAInSetLabel = -1;
                int nodeBInSetLabel = -1;;

                for(int i =0;i<(int)nodeSets.size();i++){
                    nodeAInSet = IsInSet(nodeSets[i],nodeAIndex);
                    if(nodeAInSet) nodeAInSetLabel = i;
                }
                for(int i=0;i<(int)nodeSets.size(); i++){
                    nodeBInSet = IsInSet(nodeSets[i],nodeBIndex);
                    if(nodeBInSet) nodeBInSetLabel =i;
                }

                if (nodeAInSetLabel==-1 && nodeBInSetLabel==-1){
                    vector<int> vec;
                    vec.push_back(nodeAIndex);
                    vec.push_back(nodeBIndex);
                    nodeSets.push_back(vec);
                }else if(nodeAInSetLabel ==-1&& nodeBInSetLabel !=-1){
                    nodeSets[nodeBInSetLabel].push_back(nodeAIndex);
                }else if(nodeAInSetLabel !=-1 && nodeBInSetLabel==-1){
                    nodeSets[nodeAInSetLabel].push_back(nodeBIndex);
                }else if(nodeAInSetLabel!=-1&& nodeBInSetLabel!=-1 &&nodeAInSetLabel!=nodeBInSetLabel){
                    nodeSets[nodeAInSetLabel].insert(   nodeSets[nodeAInSetLabel].end(),
                                                        nodeSets[nodeBInSetLabel].begin(),
                                                        nodeSets[nodeBInSetLabel].end());
                    for (int k = nodeBInSetLabel;k<(int)nodeSets.size(); k++){
                        nodeSets[k] = nodeSets[k+1];
                    }
                }else if(nodeAInSetLabel !=-1 && nodeBInSetLabel!=-1 &&nodeAInSetLabel==nodeBInSetLabel) continue;

                m_pEdgeArray[edgeCount] = edgeVec[retIndex];
                edgeCount++;

                cout<< m_pNodeArray[edgeVec[retIndex].m_iNodeIndexA].m_cData<<" - ";
                cout<< m_pNodeArray[edgeVec[retIndex].m_iNodeIndexB].m_cData<<" (";
                cout<< edgeVec[retIndex].m_iWeightValue<<") "<<endl;
            }
        }
    }

    void Floyd(){
        floyd();
        PrintMatrix();
    }
    
};


int main(){
    CMap *pMap = new CMap(7);

    Node *pNode0 = new Node('0');
    Node *pNode1 = new Node('1');
    Node *pNode2 = new Node('2');
    Node *pNode3 = new Node('3');
    Node *pNode4 = new Node('4');
    Node *pNode5 = new Node('5');
    Node *pNode6 = new Node('6');

    pMap->AddNode(pNode0);
    pMap->AddNode(pNode1);
    pMap->AddNode(pNode2);
    pMap->AddNode(pNode3);
    pMap->AddNode(pNode4);
    pMap->AddNode(pNode5);
    pMap->AddNode(pNode6);

    pMap->SetValueToMatrixForUndirectedGraph(0,1,28);
    pMap->SetValueToMatrixForUndirectedGraph(0,5,10);
    pMap->SetValueToMatrixForUndirectedGraph(1,2,16);
    pMap->SetValueToMatrixForUndirectedGraph(1,6,14);
    pMap->SetValueToMatrixForUndirectedGraph(2,3,12);
    pMap->SetValueToMatrixForUndirectedGraph(3,4,22);
    pMap->SetValueToMatrixForUndirectedGraph(3,6,18);
    pMap->SetValueToMatrixForUndirectedGraph(4,5,25);
    pMap->SetValueToMatrixForUndirectedGraph(4,6,24);

    cout<< "Print Matrix: " <<endl;
    pMap->PrintMatrix();
    cout<<endl;

    pMap->ResetNode(); 

    cout<< "DFS: " <<endl;
    pMap->DepthFirstTraverse(0);
    cout<<endl;

    pMap->ResetNode();

    cout<<"BFS: "<<endl;
    pMap->BreadthFirstTraverse(0);
    cout<<endl;

    pMap->ResetNode();

    cout<<endl;
    cout<<"MiniTree:"<<endl;
    cout<<"Prim algorithm: "<<endl;
    pMap->PirmTree(0);
    cout<<endl;

    pMap->ResetNode();

    cout<< "Krushal algorithm: "<<endl;
    pMap->KruskakTree();
    cout<<endl;

    pMap->ResetNode();

    // pMap->Floyd();
    return 0;
}