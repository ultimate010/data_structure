#include <stdio.h>

void bubbleSort(int * arr,int len){
  int pos;
  for(pos = len;pos > 1;pos--){
    int posJ;
    for(posJ = 1;posJ < pos;posJ++){
      if(arr[posJ - 1] > arr[posJ]){
        int temp = arr[posJ];
        arr[posJ] = arr[posJ - 1];
        arr[posJ - 1] = temp;
      }
    }
  }
}

int main(){
  int a[11] = {10,21,1232,12321,123,21,2132,213213,213,21321321,321};
  int i = 0;
  for(i = 0;i < 11;i++){
    printf("%d\t",a[i]);
  }
  bubbleSort(a,11);
  printf("\n",a[i]);
  for(i = 0;i < 11;i++){
    printf("%d\t",a[i]);
  }
  return 0;
}
