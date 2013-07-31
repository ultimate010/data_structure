/*
 * 单链表的测试
 * 2013-7-31
 * Zaks Wang
 */
#include "linked_list.h"
#include <stdio.h>

int main(){
  linkList list;
  ini_linkList(&list);
  int i = 0;
  for(i = 0;i < 105;i++){
    if(ins_linkList(list,i,i) != OK){
        exit(ERROR);
    }
  }
  for(i = 0;i < 105;i++){
    if(insBack_linkList(list,i) != OK){
        exit(ERROR);
    }
  }
  ELETYPE ele;
  del_linkList(list,20,&ele);
  ins_linkList(list,12,50);
  for(i = 0;i < 211;i++){
    getEle_linkList(list,i,&ele);
    printf("%d ",ele);
  }
  destroy_linkList(list);
  return 0;
}
