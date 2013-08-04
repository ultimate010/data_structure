#include "bitree.h"
#include <stdio.h>
int count = 0;

void visit(void * data){
  printf("%d %c\n",++count,*(char *)data);
}

int main(){
  biTree tree;
  iniPreOrder_bitree(&tree);
  printf("This is preOrder\n");
  preOrder_bitree(&tree,&visit);
  printf("This is inOrder\n");
  inOrder_bitree(&tree,&visit);
  printf("This is postOrder\n");
  postOrder_bitre(&tree,&visit);
  printf("This is levelOrder\n");
  levelTraverse_bitree(&tree,&visit);
  printf("This is preOrder iterater\n");
  preOrder_iterate_bitree(&tree,&visit);
  printf("This is inOrder iterater\n");
  inOrder_iterate_bitree(&tree,&visit);
  destroy_bitree(&tree);
  if(tree == NULL) printf("Destroyed\n");
  return 0;
}
