/*
 * 二叉树的实现
 * Zaks Wang
 * 2013-8-3
 */
#ifndef __BITREE_H_
#define __BITREE_H_
#include "def.h"
//为了实现levelTraverse
#include "../linkQueue/linked_queue.h"
#include "../linkStack/linked_stack.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct biNode{
  void * m_data;
  struct biNode * m_left;
  struct biNode * m_right;
}biNode,* biTree;

typedef void (*visitFunc)(void *);
status iniPreOrder_bitree(biTree * tree);
status iniFromArr_bitree(biTree * tree,char ** array);
status postOrder_bitre(const biTree * tree,visitFunc visit);
status inOrder_bitree(const biTree * tree,visitFunc visit);
status preOrder_bitree(const biTree * tree,visitFunc visit);
status preOrder_iterate_bitree(const biTree * tree,visitFunc visit);
status inOrder_iterate_bitree(const biTree * tree,visitFunc visit);
status inOrder_iterate_bitree1(const biTree * tree,visitFunc visit);
status levelTraverse_bitree(const biTree * tree,visitFunc visit);
status destroy_bitree(biTree * tree);

status iniFromArr_bitree(biTree * tree,char ** array){
  if(**array != '\0'){
    if(**array == ' '){
      *tree = NULL;
      return END;
    }
    biNode* node = (biNode*) malloc(sizeof(biNode));
    if(node == NULL) exit(OVERFLOW);
    char * p = (char *) malloc(sizeof(char));
    if(p == NULL) exit(OVERFLOW);
    *p = **array; *tree = node;
    node->m_data = p;
    node->m_left = node->m_right = NULL;
    ++(*array);
    iniFromArr_bitree(&(node->m_left),array);
    ++(*array);
    iniFromArr_bitree(&(node->m_right),array);
  }
  return OK;
}


status iniPreOrder_bitree(biTree * tree){
  printf("Input tree Node(Space for NULL,a line one char):\n");
  char ch = fgetc(stdin);
  while(fgetc(stdin) != '\n');
  if(ch == ' '){
    *tree = NULL;
    return END;
  }
  biNode* node = (biNode*) malloc(sizeof(biNode));
  if(node == NULL) exit(OVERFLOW);
  char * p = (char *) malloc(sizeof(char));
  if(p == NULL) exit(OVERFLOW);
  *p = ch; *tree = node;
  node->m_data = p;
  node->m_left = node->m_right = NULL;
  iniPreOrder_bitree(&(node->m_left));
  iniPreOrder_bitree(&(node->m_right));
  return OK;
}

status postOrder_bitre(const biTree * tree,visitFunc visit){
  if(*tree == NULL) return ERROR;
  if((*tree)->m_left) postOrder_bitre(&((*tree)->m_left),visit);
  if((*tree)->m_right) postOrder_bitre(&((*tree)->m_right),visit);
  visit((*tree)->m_data);
  return OK;
}

status inOrder_bitree(const biTree * tree,visitFunc visit){
  if(*tree == NULL) return ERROR;
  if((*tree)->m_left) inOrder_bitree(&((*tree)->m_left),visit);
  visit((*tree)->m_data);
  if((*tree)->m_right) inOrder_bitree(&((*tree)->m_right),visit);
  return OK;
}

status preOrder_iterate_bitree(const biTree * tree,visitFunc visit){
  linkStack stack; ini_linkedStack(&stack);
  biNode * node = *tree;
  push_linkedStack(&stack,(void *)*tree);
  while(empty_linkedStack(&stack) != TRUE){
    pop_linkedStack(&stack,(void **)&node);
    visit(node->m_data);
    if(node->m_right) push_linkedStack(&stack,(void *)node->m_right);
    if(node->m_left) push_linkedStack(&stack,(void *)node->m_left);
  }
  clear_linkedStack(&stack);
  return OK;
}
status inOrder_iterate_bitree(const biTree * tree,visitFunc visit){
  linkStack stack; ini_linkedStack(&stack);
  biNode * node = *tree;
  while(node != NULL || empty_linkedStack(&stack) == FALSE){
    if(node != NULL){
      push_linkedStack(&stack,(void *)node); node = node->m_left;
    }else{
      pop_linkedStack(&stack,(void **)&node);
      visit(node->m_data);
      node = node->m_right;
    }
  }
  clear_linkedStack(&stack);
  return OK;
}
status inOrder_iterate_bitree1(const biTree * tree,visitFunc visit){
  linkStack stack; ini_linkedStack(&stack);
  biNode * node = *tree; push_linkedStack(&stack,(void *)node);
  while(empty_linkedStack(&stack) == FALSE){
    while(getTop_linkedStack(&stack,(void **)&node) && node != NULL){
      push_linkedStack(&stack,(void *)node->m_left);
    }
    pop_linkedStack(&stack,(void **)&node);
    if(empty_linkedStack(&stack) == FALSE){
      pop_linkedStack(&stack,(void **)&node);
      visit(node->m_data);
      push_linkedStack(&stack,(void *)node->m_right);
    }
  }
  return OK;
}

status preOrder_bitree(const biTree * tree,visitFunc visit){
  if(*tree == NULL) return ERROR;
  visit((*tree)->m_data);
  if((*tree)->m_left) preOrder_bitree(&((*tree)->m_left),visit);
  if((*tree)->m_right) preOrder_bitree(&((*tree)->m_right),visit);
  return OK;
}

status levelTraverse_bitree(const biTree * tree,visitFunc visit){
  linked_queue queue;
  ini_linkedQueue(&queue);
  biNode * pNode = NULL;
  enQueue_linkedQueue(&queue,(void *)*tree);
  while(empty_linkedQueue(&queue) == FALSE){
    deQueue_linkedQueue(&queue,(void **)& pNode);
    visit(pNode->m_data);
    if(pNode->m_left){
      enQueue_linkedQueue(&queue,(void *)pNode->m_left);
    }
    if(pNode->m_right){
      enQueue_linkedQueue(&queue,(void *)pNode->m_right);
    }
  }
  clear_linkedQueue(&queue);
  return OK;
}

status destroy_bitree(biTree * tree){
  if(*tree == NULL) return ERROR;
  if((*tree)->m_left) destroy_bitree(&((*tree)->m_left));
  if((*tree)->m_right) destroy_bitree(&((*tree)->m_right));
  if((*tree)->m_data) free((*tree)->m_data);
  free(*tree);
  *tree = NULL;
  return OK;
}

status clear_bitree(biTree * tree){
  if(*tree == NULL) return ERROR;
  if((*tree)->m_left) destroy_bitree(&((*tree)->m_left));
  if((*tree)->m_right) destroy_bitree(&((*tree)->m_right));
  free(*tree);
  *tree = NULL;
  return OK;
}



#endif
