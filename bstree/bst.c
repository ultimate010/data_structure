#include <stdio.h>
#include <string.h>
#include "bst.h"

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
  bstree tree;
  ini_bstree(&tree); //初始化
  int i;
  int * pData;
  for(i = 0;i < 36;i++){
	pData = (int *) malloc(sizeof(int));
	*pData = i;
	if(insert_bstree(&tree,(void *)pData,compare_for_int) != TRUE){
	  free(pData);
	}
  }
  printf("Insert [0,36) tree is \n");
  inOrder_bstree(&tree,myPrint);
  for(i = 40;i > 1;i--){
	pData = (int *) malloc(sizeof(int));
	*pData = i;
	if(insert_bstree(&tree,(void *)pData,compare_for_int) != TRUE){
	  free(pData);
	}
  }
  printf("\n");
  printf("Insert (1,40] tree is \n");
  inOrder_bstree(&tree,myPrint);
  printf("\n");
  pData = (int *) malloc(sizeof(int));
  for(i = 23;i < 30;i++){
	*pData = i;
	if(delete_bstree(&tree,(void *)pData,compare_for_int) != TRUE){
	  printf("ERROR");
	}
  }
  printf("After delete [23,30)\n");
  inOrder_bstree(&tree,myPrint);
  printf("\n");
  for(i = 53;i >= 0;i--){
	*pData = i;
	if(delete_bstree(&tree,(void *)pData,compare_for_int) != TRUE){
	  printf("NO %d\t",*pData);
	}
  }
  printf("\n");
  printf("After delete [53,0]\n");
  inOrder_bstree(&tree,myPrint);
  printf("\n");
  free(pData);
  if(empty_bstree(&tree) == TRUE){
	printf("The tree is empty\n");
  }
  free_bstree(&tree);

  return 0;
}

