#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__
/*
 * 定义代表头结点的单链表的操作
 * 2013-4-1
 * Zaks Wang
 */
#include "def.h"
#include <stdlib.h>
#define ELETYPE int
typedef struct linkNode{
  ELETYPE m_ele;
  struct linkNode* m_next;
}linkNode,* linkList;
status ini_linkList(linkList* list);
status insBack_linkList(linkList list,ELETYPE ele);
status ins_linkList(linkList list,const int i,ELETYPE  ele);
status delBack_linkList(linkList list,ELETYPE* ele);
status del_linkList(linkList list,const int i,ELETYPE* ele);
status destroy_linkList(linkList * list);

status destroy_linkList(linkList * list){
  linkNode * pDel;
  while((*list)->m_next){
    pDel = (*list)->m_next;
    (*list)->m_next = pDel->m_next;
    free(pDel);
  }
  free(*list); *list = NULL;
  return OK;
}
/*
 * 初始化表头结点
 * 参数:链表结点指针的指针
 * 返回:是否成功status
 */
status ini_linkList(linkList* list){
  *list = (linkList)malloc(sizeof(linkNode));
  (*list)->m_next = NULL;
  if(*list == NULL)
    return OVERFLOW;
  return OK;
}
status insBack_linkList(linkList list,ELETYPE ele){
  linkNode * newNode =(linkNode*) malloc(sizeof(linkNode));
  if(newNode == NULL) return OVERFLOW;
  newNode->m_next = NULL; newNode->m_ele = ele;
  linkNode * p = list;
  while(p->m_next) p = p->m_next; //找到最后
  p->m_next = newNode;
  return OK;
}
/*
 *  在i位置插入数据ele
 *  参数:指向链表结点的指针的指针,元素位置i(i>=0),插入的元素
 *  返回:是否成功status
 */
status ins_linkList(linkList list,const int i,ELETYPE  ele){
  linkNode* p = list;
  int j = 0;
  while(p &&j < i){
    p = p->m_next;j++;
  }
  if(!p || j > i) return ERROR;
  linkNode* newNode = (linkNode*) malloc(sizeof(linkNode));
  if(newNode == NULL) return OVERFLOW;
  newNode->m_ele = ele;newNode->m_next = p->m_next;
  p->m_next = newNode;
  return OK;
}
/*
 *  删除最后的元素
 *  参数:指向链表结点指针的指针,被删除的数据
 *  返回:是否成功的status
 */
status delBack_linkList(linkList list,ELETYPE* ele){
  linkNode* p = list;
  if(p->m_next == NULL) return ERROR;
  while(p->m_next->m_next) p = p->m_next;
  linkNode* tempP = p->m_next;
  p->m_next = tempP->m_next;
  *ele = tempP->m_ele;
  free(tempP);
  return OK;
}
/*
 *  删除i位置的元素
 *  参数:指向链表结点指针的指针,要删除的元素位置i,被删除的数据
 *  返回:是否成功的status
 */
status del_linkList(linkList list,const int i,ELETYPE* ele){
  linkNode* p = list;
  int j = 0;
  while(p && j < i){ ++j; p = p->m_next;}
  if(!p || j > i) return ERROR; //错误的删除位置
  linkNode* tempP = p->m_next;
  p->m_next = tempP->m_next;
  *ele = tempP->m_ele;
  free(tempP);
  return OK;
}
/*
 *  获得i位置的元素
 *  参数:指向链表的指针,元素位置i(i>=0),要返回的元素的指针
 *  返回:是否成功status
 */
status getEle_linkList(linkList list,const int i,ELETYPE* ele){
  linkNode* p = list; int j = 0;
  while(p && j < i){ ++j; p = p->m_next;}
  if(!p || j > i)   return ERROR;
  *ele = p->m_ele;
  return OK;
}
#endif
