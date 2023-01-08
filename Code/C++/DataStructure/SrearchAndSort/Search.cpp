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
#include<windows.h>

using namespace std;
#define KeyType int
#define MAXSIZE 50

typedef struct Link {
	char data;
	Link *next;
	Link *front;
	Link *rear;
}LNode,*LinkList;

typedef struct {
	KeyType key[MAXSIZE];
	int len;
}SSTable;

typedef struct {
	char key;
}ElemType;

typedef struct BST {
	ElemType data;
	BST *lchild, *rchild;
}BSTNode,*BSTree;

typedef struct {
	KeyType key;
}HashTable[MAXSIZE];

typedef struct HNode {
	KeyType data;
	HNode* next;
}HashNode;

typedef struct {
	HashNode *next;
}HashLinkTable[MAXSIZE];


void InitRandChar(char a[16]) {
	char c[26];
	srand(time(0));
	for (int i = 0; i < 26; i++)
		c[i] = 'a' + i;
	int n;
	for (int i = 0; i < 26; i++) {
		n = rand() % 26;
		char temp = c[i];
		c[i] = c[n];
		c[n] = temp;
	}
	for (int i = 0; i < 16; i++) 
		a[i] = c[i];
}

void CreatLinkList(LinkList &L, char a[16]) {
	L = new LNode();
	L->next = NULL;
	LNode *p = L;
	for (int i = 0; i < 16; i++) {
		LNode* q = new LNode();
		q->data = a[i];
		if (L->next == NULL) {
			q->next = NULL;
			p->next = q;
			q->front = p;
			p->rear = q;
		}
		else {
			p->next->front = q;
			q->next = p->next;
			p->next = q;
			q->front = p;
		}
	}
}

void PrintLinkList(LinkList L) {
	LNode *p = L;
	p = p->next;
	while (p) {
		cout << p->data<<" ";
		p = p->next;
	}
	cout << "\n";
}

//sequential search
int countSearch = 0;
int SequSearch(LinkList L, char c) {
	LNode *p = L->rear;
	L->data = c;//set 哨兵
	for (int i = 15; i >=0; i--) {
		if (p->data == c) return i+1;
		p = p->front;
		countSearch++;
	}
}

//Half search
KeyType BiSearch(SSTable& ST,KeyType key) {
	int low = 1, high = ST.len;
	while (low <= high) {
		int mid = (low + high) / 2;
		if (ST.key[mid] == key) return mid;
		else if (ST.key[mid] > key) high = mid - 1;
		else if (ST.key[mid] < key) low = mid + 1;
	}
	return 0;//no found
}

//binary search	
BSTree InsertBSTree(BSTree &T, char e) {
	if (!T) {
		BSTNode *S = new BSTNode();
		S->data.key = e;
		S->lchild = NULL;
		S->rchild = NULL;
		T = S;
		return NULL;
	}
	else if (e < T->data.key) return InsertBSTree(T->lchild, e);
	else if (e > T->data.key) return InsertBSTree(T->rchild, e);
	else return T;
}

void PreOrderTraverse(BSTree T) {
	if (T == NULL) return;
	else {
		cout << T->data.key<<" ";
		PreOrderTraverse(T->lchild);
		PreOrderTraverse(T->rchild);
	}
}

void MidOrderTraverse(BSTree T) {
	if (T == NULL) return;
	else {
		MidOrderTraverse(T->lchild);
		cout << T->data.key<<" ";
		MidOrderTraverse(T->rchild);
	}
}

int BSTcount = 0;
void DeleteBST(BSTree& T, char key) {
	BSTree p = T;
	BSTNode *f = NULL;//father node
	while (p) {
		BSTcount++;
		if (p->data.key == key) break;
		f = p;
		if (p->data.key > key) p = p->lchild;
		else p = p->rchild;
	}
	if (!p) return;
	BSTNode *q = p;
	BSTNode *s = NULL;

	if (q->lchild != NULL && q->rchild != NULL) {
		s = p->lchild;
		while (s->rchild) {
			q = s;
			s = s->rchild;
		}
		p->data = s->data;
		if (p != q) q->rchild = s->lchild;//yes
		else q->lchild = s->lchild;//no
		delete s;
		return;
	}

	else if (!p->rchild) p = p->lchild;
	else if (!p->lchild) p = p->rchild;
	if (!f) T = p;//delete root node
	else if (q == f->rchild) f->rchild = p;
	else f->lchild = p;
	delete q;
}

//Hash search
//除留余数法
void CreateHash(HashTable& HT,int m) {
	int x;
	for (int i = 0; i < m; i++) {
		HT[i].key = 0;
	}
	for (int i = 0; i < m; i++) {
		x = rand() % 90 + 10;
		cout << x << " ";
		if (HT[x % m].key==0) HT[x % 16].key = x;
		else {
			int j = x % m;
			while (HT[j].key != 0) j=(j+1)%m;
			HT[j].key = x;
		}
	}
	cout << endl;
}

void PrintHash(HashTable HT,int m) {
	for (int i = 0; i < m; i++) {
		cout << HT[i].key << " ";
	}
	cout << endl;
}

int H(KeyType key,int m) {
	return key % m;
}

int hashCount = 0;
int HashSearch(HashTable HT, KeyType key,int m) {
	int h = H(key,m);
	if (HT[h].key == 0) return -1;
	else {
		for(int i=0;i<m;i++){
			hashCount++;
			int Hi = (h + i) % m;
			if (HT[Hi].key == key) {
				return Hi+1;
			}
			else if(HT[Hi].key == 0) return -1;
		}
		return -1;
	}
}

//Hash search
//开发地址法
void CreateHash(HashLinkTable& HT, int m) {
	int x;
	for (int i = 0; i < m; i++) 
		HT[i].next = NULL;
	for (int i = 0; i < m; i++) {
		x = rand() % 90 + 10;
		cout << x << " ";
		HashNode* h = new HashNode();
		h->data = x;
		h->next = HT[x%m].next;
		HT[x % m].next = h;
	}
	cout << endl;
}
void PrintHash(HashLinkTable HT, int m) {
	for (int i = 0; i < m; i++) {
		if (HT[i].next) {
			HashNode* p = HT[i].next;
			while (p) {
				cout << p->data << " ";
				p = p->next;
			}
		}
	}
}

int SearchHash(HashLinkTable HLT,KeyType key, int m) {
	hashCount = 0;
	int h = H(key,m);
	if (HLT[h].next == NULL) return -1;
	else {
		HashNode* p = HLT[h].next;
		while (p) {
			hashCount++;
			if (p->data == key) return h;
			p = p->next;
		}
		return -1;
	}
}


void operation() {
	char a[16];
	InitRandChar(a);
	for (int i = 0; i < 16; i++) cout << a[i]<<" ";
	cout << endl;

	LinkList L;
	CreatLinkList(L, a);
	PrintLinkList(L);
	char c;
	cout << "顺序查找" << endl;
	cout << "请输入要查找的字母：";   cin >> c;
	cout<<"要查找的字母的序号位："<<SequSearch(L, c)<<endl;
	cout << "查找的次数为：" << countSearch<<endl;
    cout<<endl;
	
	//二分查找
	SSTable ST;
	ST.len = 16;
	for (int i = 1; i <= ST.len; i++) {
		ST.key[i] = rand() % 90 + 10;
	}
	//sort
	sort(ST.key+1, ST.key + ST.len+1);
	for (int i = 1; i <= ST.len; i++) cout << ST.key[i] << " "; 
	cout<<endl;
    KeyType key;
	cout << "二分查找" << endl;
	cout << "输入待查找的值：";   cin >> key;
	cout << "待查找值序号位：" << BiSearch(ST,key) << endl;
    cout<<endl;
	//binary search tree
	cout << "二叉查找树" << endl;
	BSTree BST;
	BST = NULL;
    cout<<"输入十个字母：";
	for (int i = 0; i < 10; i++) {
		char x;
		cin >> x;
		InsertBSTree(BST, x);
	}
	cout << "先序遍历：";
	PreOrderTraverse(BST);
	cout << endl;
	cout << "后序遍历：";
	MidOrderTraverse(BST);
	char deleteChar;
    cout<<endl;
	cout << "输入你想删除的字母：";  cin >> deleteChar;
	DeleteBST(BST, deleteChar);
	MidOrderTraverse(BST);
	cout << "\n共比较了" << BSTcount << "次"<<endl;
    cout<<endl;
	//Hash tacle
	HashTable HT;
	CreateHash(HT,16);
	cout << "哈希数组的值：";
	PrintHash(HT,16);
	int hashKey;
	cout << "哈希查找-除留余数法"<<endl;
	cout << "输入你想要的查找的数："; cin >> hashKey;
	int flag=HashSearch(HT, hashKey, 16);
	if (flag < 0) cout << "没找到对应的值\n";
	else{
		cout << "对应的位置为："<<flag<<endl;
		cout << "共查找了" << hashCount << "次"<<endl;
	}
	HashLinkTable HLT;
	CreateHash(HLT, 16);
	cout << "哈希数组的值：";
	PrintHash(HLT, 16);
    cout<<endl;
	cout << "哈希查找-开发地址法" << endl;
	cout << "输入你想要的查找的数："; cin >> hashKey;
	flag=SearchHash(HLT, hashKey, 16);
	if (flag <0)cout << "没找到对应的值\n";
	else{
		cout << "对应的位置为："<<flag<<endl;
		cout << "共查找了" << hashCount << "次" << endl;
	}
}
//e c b d a g f h i j

int main(){
    operation();
}