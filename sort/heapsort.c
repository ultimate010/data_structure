/*
 * 堆排序算法
 * Zaks Wang
 * 2013-7-27
 */

#include <stdio.h>
void swap(int *L, int posi, int posj){
  int temp = L[posi];
  L[posi] = L[posj];
  L[posj] = temp;
}

/*
 * 调整，从start到end
 */
void adjust(int *L,int start,int end){
  int temp = L[start];
  int j = 0;
  for(j = start * 2 + 1; j <= end; j = j * 2 + 1){
    if(j < end && L[j] < L[j+1]) j++; //找出儿子中最大的
    if(temp > L[j]) break; //如果父亲比儿子大
    L[start] = L[j]; start = j;
  }
  L[start] = temp;
}

void heapsort(int *L,int len){
  int i = 0;
  for(i = len/2 - 1; i >= 0; i--){
    adjust(L,i,len-1);
  }
  for(i = len-1; i > 0; i--){
    swap(L,0,i);
    adjust(L,0,i-1);
  }
}

int main(){
  int a[14] = {1,23,12321,123,213,12321,12,321,3,12,321,3,21,321};
  int j = 0;
  for(j = 0; j < 14; j++){
    printf("%d\t",a[j]);
  }
  printf("\n");
  heapsort(a,14);
  for(j = 0; j < 14; j++){
    printf("%d\t",a[j]);
  }
  printf("\n");
}

