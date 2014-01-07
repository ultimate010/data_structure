#include <stdio.h>
#include <string.h>
#include "avltree.h"

status compare_for_int(void * a,void * b){
  int * pa = (int *) a;
  int * pb = (int *) b;
  if(*pa > *pb){
	return GREATER;
  }else if(*pa == *pb){
	return EQUAL;
  }else{
	return LOWER;
  }
}
void myPrint(void * a){
  int * pa = (int *) a;
  printf("%d\t",*pa);
}

int main(){
  avltree tree;
  ini_avltree(&tree); //初始化
  int i;
  int * pData;
  for(i = 0;i < 5;i++){
	pData = (int *) malloc(sizeof(int));
	*pData = i;
	if(insert_avltree(&tree,(void *)pData,compare_for_int) != TRUE){
	  free(pData);
	}
  }
  printf("Insert [0,3) tree is \n");
  inOrder_avltree(&tree,myPrint);
  printf("\n");
  pData = (int *) malloc(sizeof(int));
  for(i = 2;i < 5;i++){
	*pData = i;
	if(delete_avltree(&tree,(void *)pData,compare_for_int) != TRUE){
	  printf("\nERROR\n");
	}
	printf("Delete%d\n",i);
	inOrder_avltree(&tree,myPrint);
	printf("\n");
  }
  for(i = 40;i > 1;i--){
	pData = (int *) malloc(sizeof(int));
	*pData = i;
	if(insert_avltree(&tree,(void *)pData,compare_for_int) != TRUE){
	  free(pData);
	}
  }
  printf("\n");
  printf("Insert (1,40] tree is \n");
  inOrder_avltree(&tree,myPrint);
  printf("\n");
  pData = (int *) malloc(sizeof(int));
  for(i = 23;i < 30;i++){
	*pData = i;
	if(delete_avltree(&tree,(void *)pData,compare_for_int) != TRUE){
	  printf("ERROR");
	}
  }
  printf("After delete [23,30)\n");
  inOrder_avltree(&tree,myPrint);
  printf("\n");
  for(i = 53;i >= 0;i--){
	*pData = i;
	if(delete_avltree(&tree,(void *)pData,compare_for_int) != TRUE){
	  printf("NO %d\t",*pData);
	}
  }
  printf("\n");
  printf("After delete [53,0]\n");
  inOrder_avltree(&tree,myPrint);
  printf("\n");
  free(pData);
  if(empty_avltree(&tree) == TRUE){
	printf("The tree is empty\n");
  }
  free_avltree(&tree);
  return 0;
}

