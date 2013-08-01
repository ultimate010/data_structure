#include "linked_queue.h"
#include <stdio.h>

int main(){
  linked_queue queue;
  ini_linedQueue(&queue);
  int i = 0;
  for(i = 0;i < 100;i++){
    int * data = (int *) malloc(sizeof(int));
    *data = i;
    enQueue_linkedQueue(&queue,(void *)data);
  }
  int * data;
  getHead_linkedQueue(&queue,(void **)&data);
  printf("%d\n",*data);
  for(i = 0;i < 110;i++){
    deQueue_linkedQueue(&queue,(void **)&data);
    printf("%d\t",*data);
  }
  printf("\n");
  destroy_linkedQueue(&queue);
  return 0;
}
