/*
 * 双向循环链表实现栈
 * Zaks Wang
 * 2013-8-3
 */
#ifndef __LINKED_STACK_H__
#define __LINKED_STACK_H__
#include "def.h"
#include <stdlib.h>

typedef struct stackNode{
  void * m_data;
  struct stackNode * m_pre;
  struct stackNode * m_next;
}stackNode,*linkStack;

status ini_linkedStack(linkStack * stack);
status empty_linkedStack(const linkStack * stack);
unsigned int length_linkedStack(const linkStack * stack);
status clear_linkedStack(linkStack * stack);
status destroy_linkedStack(linkStack * stack);
status push_linkedStack(linkStack * stack,void * data);
status pop_linkedStack(linkStack * stack,void ** data);
status getTop_linkedStack(linkStack * stack,void ** data);

status ini_linkedStack(linkStack * stack){
  stackNode * p = (stackNode*) malloc(sizeof(stackNode));
  if(p == NULL) exit(OVERFLOW);
  p->m_pre = p->m_next = p;
  p->m_data = NULL;
  *stack = p;
  return OK;
}

status empty_linkedStack(const linkStack * stack){
  if((*stack)->m_pre == (*stack)) return TRUE;
  return FALSE;
}

unsigned int length_linkedStack(const linkStack * stack){
  unsigned int length = 0;
  stackNode * p = (*stack)->m_next;
  while(p != *stack){
    p = p->m_next; ++length;
  }
  return length;
}

status clear_linkedStack(linkStack * stack){
  stackNode * pDel = NULL;
  while((*stack)->m_next != *stack){
    pDel = (*stack)->m_next;
    (*stack)->m_next = pDel->m_next;
    free(pDel);
  }
  free(*stack); *stack = NULL;
  return OK;
}

status destroy_linkedStack(linkStack * stack){
  stackNode * pDel = NULL;
  while((*stack)->m_next != *stack){
    pDel = (*stack)->m_next;
    (*stack)->m_next = pDel->m_next;
    if(pDel->m_data) free(pDel->m_data);
    free(pDel);
  }
  if((*stack)->m_data) free((*stack)->m_data);
  free(*stack); *stack = NULL;
  return OK;
}

status push_linkedStack(linkStack * stack,void * data){
  stackNode * node = (stackNode *) malloc(sizeof(stackNode));
  if(node == NULL) exit(OVERFLOW);
  node->m_data = data;
  node->m_pre = (*stack)->m_pre;
  node->m_next = *stack;
  node->m_pre->m_next = node;
  (*stack)->m_pre = node;
  return OK;
}

status pop_linkedStack(linkStack * stack,void ** data){
  if(*stack == (*stack)->m_pre) return ERROR;
  stackNode * pDel = (*stack)->m_pre;
  *data = pDel->m_data;
  pDel->m_pre->m_next = (*stack);
  (*stack)->m_pre = pDel->m_pre;
  free(pDel);
  return OK;
}

status getTop_linkedStack(linkStack * stack,void ** data){
  if(*stack == (*stack)->m_pre) return ERROR;
  *data = (*stack)->m_pre->m_data;
  return OK;
}
#endif
