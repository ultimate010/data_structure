#include "sequence_stack.h"
#include <stdio.h>

int main(){
  seqStack stack;
  ini_seqStack(&stack);
  int i = 0;
  for(i = 0;i < 120;i++){
    push_seqStack(&stack,i);
  }
  getTop_seqStack(&stack,&i);
  printf("%d \n",i);
  for(i = 0;i < 120;i++){
    push_seqStack(&stack,i);
  }
  int j = 0;
  for(i = 0;i < 270;i++){
    pop_seqStack(&stack,&j);
    printf("%d ",j);
  }
  printf("\n");
  clear_seqStack(&stack);
  destroy_seqStack(&stack);
  return 0;
}
