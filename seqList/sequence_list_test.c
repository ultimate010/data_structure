/*
 * 测试顺序表操作
 * 2013-4-1
 * Zaks Wang
 */
#include "sequence_list.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
  seq_list list;
  ini_seqList(&list); //初始化
  int i;
  for(i = 0;i < 105;i++){
    if(ins_seqList(&list,i,i) != OK){
        exit(ERROR);
    }
  }
  for(i = 0;i < 105;i++){
    if(insBack_seqList(&list,i) != OK){
        exit(ERROR);
    }
  }
  ELETYPE ele;
  del_seqList(&list,20,&ele);
  ins_seqList(&list,12,50);
  for(i=0;i<211;i++){
    getEle_seqList(&list,i,&ele);
    printf("%d ",ele);
  }
  destroy_seqList(&list);
  return 0;
}
