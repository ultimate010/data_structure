#include <stdio.h>

void selectSort(int * arr,int len){
  unsigned int pos;
  for(pos = 0;pos < len - 1;pos++){
    unsigned int posJ,posTemp = pos;
    for(posJ = pos + 1;posJ < len;posJ++){
      if(arr[posTemp] > arr[posJ]){
        posTemp = posJ;
      }
    }
    if(posTemp != pos){
      int temp = arr[pos];
      arr[pos] = arr[posTemp];
      arr[posTemp] = temp;
    }
  }
}
int main(){
  int a[11] = {10,21,1232,12321,123,21,2132,213213,213,21321321,321};
  int i = 0;
  for(i = 0;i < 11;i++){
    printf("%d\t",a[i]);
  }
  selectSort(a,11);
  printf("\n",a[i]);
  for(i = 0;i < 11;i++){
    printf("%d\t",a[i]);
  }
  return 0;
}
