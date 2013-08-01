/*
 * 链式栈的实现
 * 2013-8-1
 * Zaks Wang
 */
#ifndef __LINKED_QUEUE_H__
#define __LINKED_QUEUE_H__
#include "def.h"
#include <stdlib.h>

typedef struct queueNode{
  void * m_data;
  struct queueNode* m_next;
}queueNode;

typedef struct{
  queueNode* m_front;
  queueNode* m_rear;
}linked_queue;
status ini_linedQueue(linked_queue* queue);
status destroy_linkedQueue(linked_queue* queue);
status getHead_linkedQueue(linked_queue* queue,void** data);
unsigned int length_linkedQueue(linked_queue* queue);
status deQueue_linkedQueue(linked_queue* queue,void** data);
status enQueue_linkedQueue(linked_queue* queue,void* data);

/*
 * 初始化操作
 */
status ini_linedQueue(linked_queue* queue){
  queue->m_front = queue->m_rear = NULL;
  return OK;
}

/*
 * 清空队列，尽可能释放资源
 */
status destroy_linkedQueue(linked_queue* queue){
  queueNode* node = NULL;
  while(queue->m_front != NULL){
    node = queue->m_front;
    queue->m_front = node->m_next;
    if(node->m_data) free(node->m_data);
    free(node);
  }
  queue->m_front = queue->m_rear = NULL;
  return OK;
}

/*
 * 获取头部元素
 */
status getHead_linkedQueue(linked_queue* queue,void** data){
  if(queue->m_front == NULL) return ERROR;
  *data = queue->m_front->m_data;
  return OK;
}

/*
 * 获取队列长度
 */
unsigned int length_linkedQueue(linked_queue* queue){
  unsigned int len = 0;
  queueNode* node = queue->m_front;
  while(node){
    node = node->m_next; ++len;
  }
  return len;
}

/*
 * 出队列操作
 */
status deQueue_linkedQueue(linked_queue* queue,void** data){
  if(queue->m_front == NULL) return ERROR;
  queueNode* node = queue->m_front;
  *data = node->m_data;
  queue->m_front = node->m_next;
  if(queue->m_front == NULL) queue->m_rear = NULL;
  free(node);
  return OK;
}

/*
 * 入队列操作
 */
status enQueue_linkedQueue(linked_queue* queue,void* data){
  queueNode* node = (queueNode*)malloc(sizeof(queueNode));
  if(node == NULL) return OVERFLOW;
  node->m_data = data; node->m_next = NULL;
  if(queue->m_front == NULL){
    queue->m_front = queue->m_rear = node;
    return OK;
  }
  queue->m_rear->m_next = node;
  queue->m_rear = node;
  return OK;
}
#endif

