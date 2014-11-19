#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__
/*
 * 定义带表头结点的单链表的操作
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
/*
 * 删掉所有结点,包括头结点
 */
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
 * core low level coding 
 * 删掉表头结点
 */
status destroy_linkList_v1(linkList * list){
  linkList pDel;
  while(*list){
    pDel = *list;
    *list = pDel->m_next;
    free(pDel);
  }
  return OK;
}

typedef status (* del_fun)(linkList p);
status del_linkList(linkList pNode, del_fun rm){
    linkList pDel = NULL;
    while(pNode->m_next){ // The node after header
        if(rm(pNode->m_next) == OK){
            pDel = pNode->m_next;
            pNode = pDel->m_next;
            free(pDel);
        }else{
            pNode = pNode->m_next;
        }
    }
    return OK;
}

status del_linkList_v1(linkList * list, del_fun rm){
    linkList pCur = *list;
    while(pCur){
        if(rm(pCur) == OK){
            if(pCur == *list){
            }else{
            }
        }else{
        }
    }
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
