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
int comNum,movNum;  //record number of compare and movement

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


void InsertSort(int arr[]){
    if(arr==NULL) return;
    for(int i=1;i<16;i++){
        if(arr[i]<arr[i-1]){
            comNum ++;
            int temp=arr[i];
            int j =i;
            while(j>0&&temp<arr[j-1]){
                comNum++;
                movNum++;
                arr[j]=arr[j-1];
                j--;
            }
            arr[j]=temp;
        }
        PrintArr(arr);
    }
    cout<<"☝ ☝ ☝ InsertSort 比较次数："<<comNum<<"\t"<<"移动次数："<<movNum<<endl;
    comNum = movNum =0;
}

void ShellSort(int arr[]){
    for(int gap = 8;gap>0;gap/=2){
        for(int i = gap;i<16;i++){
            int j=i;
            if(arr[j]<arr[j-gap]){
                int temp=arr[j];
                comNum++;
                while(j-gap>=0&&temp<arr[j-gap]){
                    comNum++;
                    movNum++;
                    arr[j]=arr[j-gap];
                    j-=gap;
                }
                arr[j]=temp;
            }
        }
        PrintArr(arr);
    }
    cout<<"☝ ☝ ☝ ShellSort 比较次数："<<comNum<<"\t"<<"移动次数："<<movNum<<endl;
    comNum=movNum=0;          
}

void BubbleSort(int arr[]){
    for(int i=15;i>0;i--){
        for(int j=0;j<i;j++){
            if(arr[j]>arr[j+1]){
                comNum++;
                movNum+=2;
                int temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
        PrintArr(arr);
    }
    cout<<"☝ ☝ ☝ BubbleSort 比较次数："<<comNum<<"\t"<<"移动次数："<<movNum<<endl;
    comNum=movNum=0;
}

void QuickSort(int arr[],int l,int r){
    int left=l,right=r;
    if(left<=right){
        int temp=arr[left];
        while(left!=right){
            comNum++;
            while(right>left&&arr[right]>=temp){
                comNum++;
                right --; //右到左扫描小于基准数的元素
            }
            arr[left] = arr[right];
            movNum++;
            while(left<right&&arr[left]<=temp){
                comNum++;
                left ++;  //左到右扫描大于基准数的元素
            }
            arr[right]=arr[left];
            movNum++;
            
        }
        arr[right]=temp;
        PrintArr(arr);
        QuickSort(arr,l,left-1);
        QuickSort(arr,right+1,r);
    }
}

void QS(int arr[],int l,int r){
    QuickSort(arr,l,r);
    cout<<"☝ ☝ ☝ QuickSort 比较次数："<<comNum<<"\t"<<"移动次数："<<movNum<<endl;
    comNum=movNum=0;
}

void SelectSort(int arr[]){
    int head,rear,min;
    for(rear=0;rear<16;rear++){
        min=rear;
        for(head=rear+1;head<16;head++){
            comNum++;
            if(arr[head]<arr[min]) min=head;movNum++;
        }
        if(min!=rear){
            int temp=arr[rear];
            arr[rear]=arr[min];
            arr[min]=temp;
            movNum+=2;
        }
        PrintArr(arr);
    }
    cout<<"☝ ☝ ☝ SelectSort 比较次数："<<comNum<<"\t"<<"移动次数："<<movNum<<endl;
    comNum=movNum=0;
}

void MaxHeapDown(int *arr,int start,int end){
    int cur=start,left=2*cur+1,temp=arr[cur];
    for(;left<=end;cur=left,left=2*left+1){
        comNum++;
        if(left<end&&arr[left]<arr[left+1]) left++;comNum++;
        comNum++;
        if(temp>=arr[left]) break;
        else{
            arr[cur]=arr[left];
            arr[left]=temp;
            movNum++;
        }
    }
}

void HeapSortAsc(int *arr){
    int i,temp;
    for(i=7;i>=0;i--)
        MaxHeapDown(arr,i,15);PrintArr(arr);
    for(i=15;i>0;i--){
        temp=arr[0];
        arr[0]=arr[i];
        arr[i]=temp;
        movNum+=2;
        MaxHeapDown(arr,0,i-1);
        PrintArr(arr);
    }
    cout<<"☝ ☝ ☝ HeapSortAsc 比较次数："<<comNum<<"\t"<<"移动次数："<<movNum<<endl;
    comNum=movNum=0;
}

void  Merge(int * arr, int low, int mid, int high){
    int i = low, j = mid + 1, p = 0;
    int * r = new int[high - low + 1];//申请另一个对应大小的数组来存放排好序的数据
    while (i <= mid && j <= high)
        r[p++] = (arr[i] <= arr[j]) ? arr[i++] : arr[j++];comNum+=2;movNum++;
    while (i <= mid)
        r[p++] = arr[i++];movNum++;comNum++;
    while (j <= high)
        r[p++] = arr[j++];movNum++;comNum++;
    for (p = 0, i = low; i <= high; p++, i++)
        arr[i] = r[p];movNum++;comNum++;//最后再把有序数据存进a数组中，使得a数组对应部分数据有序
    delete[] r;
    PrintArr(arr);
}

void MSort(int *arr, int low, int high){
    if (low<high){
        comNum++;
        int mid = (low + high) / 2;
        MSort(arr, low, mid);
        MSort(arr, mid + 1, high);
        Merge(arr, low, mid, high);
    }
}

void TwoMergeSort(int *arr, int low, int high){
    MSort(arr,low,high);
    cout<<"☝ ☝ ☝ TwoMergeSort 比较次数："<<comNum<<"\t"<<"移动次数："<<movNum<<endl;
    comNum=movNum=0;
}

int GetMax(int *arr){
    int i,max;
    max=arr[0];
    for(i=1;i<16;i++)
        comNum++;
        if(arr[i]>max)
            max=arr[i];movNum++;
    return max;
}

void CountSort(int *arr,int exp){
    int output[16],i,buckets[10]={0};
    for(i=0;i<16;i++)
        buckets[(arr[i]/exp)%10]++;movNum++;
    for (i = 1; i < 10; i++)
        buckets[i]+= buckets[i- 1];movNum++;
    for (i=15;i>=0;i--){
        output[buckets[ (arr[i]/exp)%10 ] - 1] = arr[i];
        movNum++;
        buckets[(arr[i]/exp)%10]--;
    }
    for (i=0;i <16;i++)
        arr[i]= output[i];
        movNum++;
}

void RadixSort(int *arr){
    int exp,max=GetMax(arr);
    for(exp=1;max/exp>0;exp*=10){
        CountSort(arr,exp);
        PrintArr(arr);
    }
    cout<<"☝ ☝ ☝ RadixSort 比较次数："<<comNum<<"\t"<<"移动次数："<<movNum<<endl;
    comNum=movNum=0;
}

int main(){
    SetConsoleOutputCP(65001);
    int AimArr[16],AimArrCopy[16];
    InitArr(AimArr);
    memcpy(AimArrCopy,AimArr,sizeof(AimArr));
    InsertSort(AimArrCopy);
    memcpy(AimArrCopy,AimArr,sizeof(AimArr));
    ShellSort(AimArrCopy);
    memcpy(AimArrCopy,AimArr,sizeof(AimArr));
    BubbleSort(AimArrCopy);
    memcpy(AimArrCopy,AimArr,sizeof(AimArr));
    QS(AimArrCopy,0,15);
    memcpy(AimArrCopy,AimArr,sizeof(AimArr));
    SelectSort(AimArrCopy);
    memcpy(AimArrCopy,AimArr,sizeof(AimArr));
    HeapSortAsc(AimArrCopy);
    memcpy(AimArrCopy,AimArr,sizeof(AimArr));
    TwoMergeSort(AimArrCopy,0,15);
    memcpy(AimArrCopy,AimArr,sizeof(AimArr));
    RadixSort(AimArrCopy);
}
