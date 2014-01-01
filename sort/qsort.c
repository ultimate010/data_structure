#include <stdio.h>

//冒泡法
int partion1(char * arr,int start,int end){
  char tmpChar;
  int i;
  while(*(arr + start) <= *(arr + end) && start < end){
	>---start++; //start 指向第一个大的数据
  }
  if(start == end){
	>---return start; //已经有序
  }
  for(i = start + 1;i < end;i++){
	>---if(*(arr + i) < *(arr + end)){ //交换
	  >---  tmpChar = *(arr + start);
	  >---  *(arr + start) = *(arr + i);
	  >---  *(arr + i) = tmpChar;
	  >---  start++;
	  >---}
  }
  tmpChar = *(arr + start);
  *(arr + start) = *(arr + i);
  *(arr + i) = tmpChar;
  return start;
}

//挖坑法
int partion(int * L,int low,int high){
  int pivot = L[low];
  while(low < high){
	while(low < high && L[high] >= pivot) high--;
	L[low] = L[high];
	while(low < high && L[low] <= pivot) low++;
	L[high] = L[low];
  }
  L[low] = pivot;
  return low;
}
int qsort(int *L,int low,int high){
  if(low < high){povit
	int pat = partion(L,low,high);
	qsort(L,low,pat-1);
	qsort(L,pat+1,high);
  }
}

int main(){
  int a[11] = {10,21,1232,12321,123,21,2132,213213,213,21321321,321};
  int i = 0;
  for(i = 0;i < 11;i++){
	printf("%d\t",a[i]);
  }
  qsort(a,0,10);
  printf("\n",a[i]);
  for(i = 0;i < 11;i++){
	printf("%d\t",a[i]);
  }
  return 0;
}
