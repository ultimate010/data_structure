#include <stdio.h>

/*
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
*/

void selectSort(int a[], int len)
{
    for (int i = 0; i < len - 1;i++)
    {
        int min = a[i]; int pos = i;
        for (int j = i + 1; j < len;j++)
        {
            if (min > a[j])
            {
                min = a[j];
                pos = j;
            }
        }
        a[pos] = a[i];
        a[i] = min;
    }
}

int main(){
  int a[11] = {10,21,1232,12321,123,1,2132,213213,213,21321321,321};
  int i = 0;
  for(i = 0;i < 11;i++){
    printf("%d\t",a[i]);
  }
  selectSort(a,11);
  printf("\n");
  for(i = 0;i < 11;i++){
    printf("%d\t",a[i]);
  }
  return 0;
}
