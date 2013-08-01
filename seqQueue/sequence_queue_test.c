#include "sequence_queue.h"
#include <stdio.h>

int main(){
  seqQueue queue;
  ini_seqQueue(&queue);
  int i = 0;
  for(i = 0;i < 111; i++){
    int * p = (int *) malloc(sizeof(int));
    *p = i;
    enQueue_seqQueue(&queue,(void *) p);
  }
  int * p = NULL;
  getHead_seqQueue(&queue,(void **)&p);
  printf("%d \n",*p);
  for(i = 0;i<20;i++){
    deQueue_seqQueue(&queue,(void **)&p);
    printf("%d ",*p);
  }
  printf("\n");
  for(i = 0;i < 101; i++){
    int * p = (int *) malloc(sizeof(int));
    *p = i;
    enQueue_seqQueue(&queue,(void *) p);
  }
  for(i = 0;i < 200;i++){
    deQueue_seqQueue(&queue,(void **)&p);
    printf("%d ",*p);
  }
  destroy_seqQueue(&queue);
  return 0;
}
