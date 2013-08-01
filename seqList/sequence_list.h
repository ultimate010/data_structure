#ifndef __SQUENCE_LIST_H__
#define __SQUENCE_LIST_H__
/*
 * 定义顺序表的操作
 * 2013-4-1
 * Zaks Wang
 */
#include "def.h"
#include <stdlib.h>

#define ELETYPE int
#define DEFAUT_SIZE 100
#define DEFAUT_INC_SIZE 100

typedef struct{
  int m_listSize; //当前表长度
  int m_maxListSize; //当前表的最大长度
  ELETYPE * m_pList; //指向元素数组的指针
}seq_list;
status ini_seqList(seq_list* list);
status insBack_seqList(seq_list* list,const ELETYPE ele);
status ins_seqList(seq_list* list,const int i,const ELETYPE  ele);
status delBack_seqList(seq_list* list,ELETYPE* ele);
status del_seqList(seq_list* list,const int i,ELETYPE* ele);
status getBackEle_seqList(const seq_list* list,ELETYPE *ele);
status getEle_seqList(const seq_list* list,const int i,ELETYPE *ele);
status destroy_seqList(seq_list* list);


status destroy_seqList(seq_list* list){
  if(list->m_pList == NULL) return ERROR;
  free(list->m_pList); list->m_pList = NULL;
  list->m_listSize = list->m_maxListSize = 0;
}

/*
 *  链表的数据的初始化操作
 *  参数:指向链表的指针
 *  返回:是否成功status
 */
status ini_seqList(seq_list* list){
  list->m_pList=(ELETYPE *)malloc(sizeof(ELETYPE) * DEFAUT_SIZE);
  if(list->m_pList == NULL){
    list->m_listSize = list->m_maxListSize = 0;
    return OVERFLOW;
  }
  list->m_listSize = 0;list->m_maxListSize = DEFAUT_SIZE;
  return OK;
}
/*
 *  在最后插入数据ele
 *  参数：指向链表，插入元素
 *  返回：是否成功status
 */
status insBack_seqList(seq_list* list,const ELETYPE ele){
  return ins_seqList(list,list->m_listSize,ele);
}
/*
 *  在i位置插入数据ele
 *  参数:指向链表的指针,元素位置i(i>=1),插入元素
 *  返回:是否成功status
 */
status ins_seqList(seq_list* list,const int i,const ELETYPE  ele){
  if(i < 0||i > (list->m_listSize)) //插入错误的位置
  return ERROR;
  if(list->m_listSize >= list->m_maxListSize){
    //表已经满了，增加表容量
    ELETYPE * pEle = (ELETYPE*) realloc(list->m_pList,(list->m_maxListSize + DEFAUT_INC_SIZE)
    * sizeof(ELETYPE));
    if(!pEle){
        return OVERFLOW;
    }
    list->m_pList = pEle;
    list->m_maxListSize += DEFAUT_INC_SIZE;
  }
  int j;
  for(j = list->m_listSize;j > i;j--){
    list->m_pList[j] = list->m_pList[j-1];
  }
  list->m_pList[j]=ele;
  list->m_listSize++;
  return OK;
}
/*
 *  删除最后的元素
 *  参数：指向元素数组的指针，用来获得删除的元素的指针
 *  返回：是否成功status
 */
status delBack_seqList(seq_list* list,ELETYPE* ele){
  return del_seqList(list,list->m_listSize,ele);
}
/*
 *  删除i位置的元素
 *  参数:指向链表的指针,元素位置i(i>=0),用来获得删除的元素的指针
 *  返回:是否成功status
 */
status del_seqList(seq_list* list,const int i,ELETYPE* ele){
  if(i < 0 || i >= list->m_listSize) return ERROR;
  int j=0;
  for(j = i;j < list->m_listSize;j++){
    *ele = list->m_pList[j];
    list->m_pList[j]=list->m_pList[j+1];
  }
  list->m_listSize--;
  return OK;
}

/*
 *  获得最后的元素
 *  参数：指向链表的指针,要返回的元素的指针
 *  返回：是否成功status
 */
status getBackEle_seqList(const seq_list* list,ELETYPE *ele){
  return getEle_seqList(list,list->m_listSize-1,ele);
}

/*
 *  获得i位置的元素
 *  参数:指向链表的指针,元素位置i(i>=0),要返回的元素的指针
 *  返回:是否成功status
 */
status getEle_seqList(const seq_list* list,const int i,ELETYPE *ele){
  if(i < 0|| i >= list->m_listSize) return ERROR;
  *ele = list->m_pList[i];
  return OK;
}

#endif
