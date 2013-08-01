/*
 * 循环队列的实现
 * 2013-8-1
 * Zaks Wang
 */
#ifndef __SEQUENCE_QUEUE_H__
#define __SEQUENCE_QUEUE_H__
#include "def.h"
#include <stdlib.h>

#define DEFAULTINC 100
#define INISIZE 100
#define ELETYPE int

typedef struct seqQueue{
  void ** m_base;
  unsigned int m_front;
  unsigned int m_rear;
  unsigned int m_maxSize;
}seqQueue;

status ini_seqQueue(seqQueue* queue);
status destroy_seqQueue(seqQueue* queue);
unsigned int length_seqQueue(seqQueue* queue);
status getHead_seqQueue(seqQueue* queue,void ** data);
status enQueue_seqQueue(seqQueue* queue,void * data);
status deQueue_seqQueue(seqQueue* queue,void ** data);

status ini_seqQueue(seqQueue* queue){
  void ** p = (void **) malloc(sizeof(void *) * INISIZE);
  if(p == NULL) return OVERFLOW;
  queue->m_base = p; queue->m_maxSize = INISIZE;
  queue->m_front = queue->m_rear = 0;
  return OK;
}

status destroy_seqQueue(seqQueue* queue){
  if(queue->m_base == NULL) return ERROR;
  while(queue->m_front != queue->m_rear){
    if(queue->m_base[queue->m_front] != NULL) free(queue->m_base[queue->m_front]);
    queue->m_front = (queue->m_front + 1) % queue->m_maxSize;
  }
  free(queue->m_base); queue->m_base = NULL;
  queue->m_front = queue->m_rear = queue->m_maxSize = 0;
  return OK;
}

unsigned int length_seqQueue(seqQueue* queue){
  if(queue->m_front > queue->m_rear){
    return queue->m_maxSize - queue->m_front + queue->m_rear;
  }else{
    return queue->m_rear - queue->m_front;
  }
}

status getHead_seqQueue(seqQueue* queue,void ** data){
  if(queue->m_base == NULL || queue->m_front == queue->m_rear) return ERROR;
  *data = queue->m_base[queue->m_front];
  return OK;
}

status enQueue_seqQueue(seqQueue* queue,void * data){
  if(queue->m_base == NULL) return ERROR;
  if((queue->m_rear + 1) % queue->m_maxSize == queue->m_front){
    //增加容量
    void * p = (void *) realloc(queue->m_base,(queue->m_maxSize + DEFAULTINC) * sizeof(void *));
    if(p == NULL) return OVERFLOW;
    queue->m_base = p; queue->m_maxSize += DEFAULTINC;
  }
  queue->m_base[queue->m_rear] = data;
  queue->m_rear = (queue->m_rear + 1) %queue->m_maxSize;
  return OK;
}

status deQueue_seqQueue(seqQueue* queue,void ** data){
  if(queue->m_base == NULL || queue->m_front == queue->m_rear) return ERROR;
  *data = queue->m_base[queue->m_front];
  queue->m_front = (queue->m_front + 1) % queue->m_maxSize;
  return OK;
}


#endif
