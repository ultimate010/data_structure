#include <stdio.h>

void insertSort(int * arr,int len){
    int pos;
    for(pos = 1;pos < len;pos++){
      if(arr[pos] < arr[pos - 1]){
        int temp = arr[pos]; int posJ;
        for(posJ = pos;posJ > 0 && arr[posJ - 1] > temp;posJ--){
          arr[posJ] = arr[posJ - 1];
        }
        arr[posJ] = temp;
      }
    }
}

int main(){
  int a[11] = {10,21,1232,12321,123,1,2132,213213,213,21321321,321};
  int i = 0;
  for(i = 0;i < 11;i++){
    printf("%d\t",a[i]);
  }
  insertSort(a,11);
  printf("\n",a[i]);
  for(i = 0;i < 11;i++){
    printf("%d\t",a[i]);
  }
  return 0;
}
