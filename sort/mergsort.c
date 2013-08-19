/*
 * 归并排序
 * Zaks Wang
 * 2013-7-26
 */

#include <stdio.h>

void merge(int *L, int *LAns, int pStart, int pEnd, int qStart, int qEnd){
  int begin = 0;
  for(;pStart <= pEnd && qStart <= qEnd;){
    if(L[pStart] < L[qStart]){
      LAns[begin++] = L[pStart]; pStart++;
    }else{
      LAns[begin++] = L[qStart]; qStart++;
    }
  }
  if(pStart < pEnd){
    for(; pStart < pEnd; ){
      LAns[begin++] = L[pStart]; pStart++;
    }
  }
  if(qStart < qEnd){
    for(; qStart < qEnd; ){
      LAns[begin++] = L[qStart]; qStart++;
    }
  }
}

void sort(int *L,int *LAns, int start, int end){
  if(start < end){
    int mid = (start + end) / 2;
    sort(L,LAns,start,mid);
    sort(L,LAns,mid+1,end);
    merge(L,LAns,start,mid,mid+1,end);
  }
}

void mergesort(int * L, int *LAns, int len){
    sort(L,LAns,0,len-1);
}

int main(){
  int a[11] = {10,21,1232,12321,123,21,2132,213213,213,21321321,321};
  int i = 0;
  for(i = 0;i < 11;i++){
    printf("%d\t",a[i]);
  }
  int b[11] = {0};
  mergesort(a,b,11);
  printf("\n");
  for(i = 0;i < 11;i++){
    printf("%d\t",b[i]);
  }
  return 0;

}
