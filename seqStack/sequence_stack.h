/*
 * 定义顺序存储的栈的实现
 * Zaks Wang
 * 2013-7-31
*/
#ifndef __SEQUENCE_LIST_H__
#define __SEQUENCE_LIST_H__
#include "def.h"
#include <stdlib.h>

#define ELETYPE int
#define INISIZE 100
#define DEFAULTINC 100
typedef struct{
  ELETYPE* m_top;
  ELETYPE* m_base;
  unsigned int m_stackSize;
  unsigned int m_maxStackSize;
}seqStack;

status ini_seqStack(seqStack * stack);
status destroy_seqStack(seqStack* stack);
status clear_seqStack(seqStack* stack);
status getTop_seqStack(seqStack* stack,ELETYPE* ele);
status pop_seqStack(seqStack* stack,ELETYPE* ele);
status pop_seqStack(seqStack* stack,ELETYPE* ele);
unsigned int length_seqStack(seqStack* stack);
status push_seqStack(seqStack* stack,const ELETYPE ele);

/*
 * 初始化栈
 */
status ini_seqStack(seqStack * stack){
  ELETYPE* p = (ELETYPE*) malloc(sizeof(seqStack)*INISIZE);
  if(p == NULL) return OVERFLOW;
  stack->m_top = stack->m_base = p;
  stack->m_stackSize = 0;
  stack->m_maxStackSize = INISIZE;
  return OK;
}
/*
 * 销毁栈，释放空间
 */
status destroy_seqStack(seqStack* stack){
  free(stack->m_base);
  stack->m_base = stack->m_top = NULL;
  stack->m_stackSize = stack->m_maxStackSize = 0;
  return OK;
}

/*
 * 清空栈中数据
 */
status clear_seqStack(seqStack* stack){
  stack->m_stackSize = 0;
  stack->m_top = stack->m_base;
}

/*
 * 返回栈顶元素
 */
status getTop_seqStack(seqStack* stack,ELETYPE* ele){
  if(stack->m_base == stack->m_top) return ERROR;
  ELETYPE* p = stack->m_top;
  *ele = *--p;
  return OK;
}

/*
 * 弹出栈顶元素
 */
status pop_seqStack(seqStack* stack,ELETYPE* ele){
  if(stack->m_base == stack->m_top) return ERROR;
  stack->m_top--;
  *ele = *stack->m_top;
  --stack->m_stackSize;
  return OK;
}

/*
 * 返回栈大小
 */
unsigned int length_seqStack(seqStack* stack){
  return stack->m_stackSize;
}

/*
 * 将元素压入栈中
 */
status push_seqStack(seqStack* stack,const ELETYPE ele){
  if(stack->m_stackSize >= stack->m_maxStackSize){
    ELETYPE* pTemp = (ELETYPE*) realloc(stack->m_base,(stack->m_maxStackSize + DEFAULTINC) * sizeof(ELETYPE));
    if(pTemp == NULL) return OVERFLOW;
    stack->m_base = pTemp;
    stack->m_maxStackSize += DEFAULTINC;
  }
  *stack->m_top++ = ele;
  stack->m_stackSize += 1;
  return OK;
}
#endif
