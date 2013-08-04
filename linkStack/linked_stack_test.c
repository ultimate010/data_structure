#include "linked_stack.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
  linkStack stack;
  ini_linkedStack(&stack);
  if(empty_linkedStack(&stack) == TRUE){
    printf("Empty\n");
  }
  for(int i = 0;i < 100;i++){
    int * p = (int *) malloc(sizeof(int));
    if(p == NULL) exit(OVERFLOW);
    *p = i+1;
    push_linkedStack(&stack,(void *)p);
  }
  printf("The length :%d\n",length_linkedStack(&stack));
  for(int i = 0;i < 100;i++){
    int * p = (int *) malloc(sizeof(int));
    if(p == NULL) exit(OVERFLOW);
    *p = i+201;
    push_linkedStack(&stack,(void *)p);
  }
  printf("The length :%d\n",length_linkedStack(&stack));
  for(int i = 0;i < 201;i++){
    int * p = NULL;
    if(pop_linkedStack(&stack,(void **)&p) == OK)
    printf("%d ",*p);
  }
  printf("\n");
  if(empty_linkedStack(&stack) == TRUE){
    printf("Empty\n");
  }
  destroy_linkedStack(&stack);
  if(stack == NULL) printf("Destroy\n");
  return 0;
}
