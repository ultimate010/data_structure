/*
 * 二叉排序树
 * Zaks Wang
 * 2014-1-4
 */
#ifndef __BSTREE_H_
#define __BSTREE_H_
#include <stdlib.h>
#include "def.h"
typedef struct bsnode{
  void * m_data;
  struct bsnode * m_left;
  struct bsnode * m_right;
}bsnode, * bstree;
/*	public func define	*/
typedef status (*compareFunc)(void * a,void * b); //定义比较函数
typedef void (*visitFunc)(void * a); //遍历访问函数
status ini_bstree(bstree * pRoot); //初始化操作,赋值为NULL
status insert_bstree(bstree * pRoot,void * value,compareFunc func); //插入元素操作
status delete_bstree(bstree * pRoot,void * value,compareFunc func); //删除元素操作
status find_bstree(bstree * pRoot,void * value,compareFunc func); //查找元素是否存在
status inOrder_bstree(bstree pRoot,visitFunc visit); //中序遍历函数
status free_bstree(bstree * pRoot); //清空树
status empty_bstree(bstree * pRoot); //判断是否为空
/*	private func define	*/
void _free_bstree(bstree p);
void _inOrder_bstree(bstree p,visitFunc visit);
/*	implement	*/
status empty_bstree(bstree * pRoot){
  return (*pRoot == NULL)?TRUE:FALSE;
}
/*	private func define	*/
/*
 * 初始化操作
 * @pRoot 根指针
 * @return 总是返回TRUE
 */
status ini_bstree(bstree * pRoot){
  *pRoot = NULL;
  return TRUE;
}
/*
 * 插入函数
 * @pRoot 树的根指针
 * @value 待插入的数据
 * @func 比较函数,a == b 返回 EQUAL, a > b 返回 GREATER, a < b 返回 LOWER
 * @return	当存在相同节点时候返回false,内存不够返回OVERFLOW
 */
status insert_bstree(bstree * pRoot,void * value,compareFunc compare){
  bstree * p = pRoot;
  while(*p){
	if(compare((*p)->m_data,value) == EQUAL){ //当前等于value
	  //存在相同节点,返回错误
	  return FALSE;
	}else if(compare((*p)->m_data,value) == GREATER){
	  p = &((*p)->m_left); //指向左子树的那个数据的指针
	}else{
	  p = &((*p)->m_right);
	}
  }
  *p = (bsnode *) malloc(sizeof(bsnode)); (*p)->m_left = (*p)->m_right = NULL;
  if(*pRoot == NULL){
	return OVERFLOW;
  }
  (*p)->m_data = value;
  return TRUE;
}
/*
 * 删除函数
 * @pRoot 树的根指针
 * @value 待删除的值
 * @func 比较函数
 * @return 找到并删除返回TRUE,找不到返回FALSE
 */
status delete_bstree(bstree * pRoot,void * value,compareFunc compare){
  bstree * p = pRoot;
  while(*p){
	if(compare((*p)->m_data,value) == EQUAL){
	  //找到待删除的元素
	  bstree * pLeft = &((*p)->m_left); //指向左孩子的指针的指针
	  while(*pLeft){
		pLeft = &((*pLeft)->m_right);//找到左孩子的最右
	  }
	  *pLeft = (*p)->m_right; //把待删除节点的右孩子接过去
	  bstree pDel = (*p); //指向待删除节点的指针
	  *p = pDel->m_left;
	  free(pDel->m_data); //释放data域
	  free(pDel); //释放待删除节点
	  return TRUE;
	}else if(compare((*p)->m_data,value) == GREATER){
	  p = &((*p)->m_left);
	}else{
	  p = &((*p)->m_right);
	}
  }
  return FALSE;
}
/*
 * 查找函数
 * @pRoot 树的根指针
 * @value 待查找的元素
 * @func 比较函数
 * @return 找到返回TRUE,找不到返回FALSE
 */
status find_bstree(bstree * pRoot,void * value,compareFunc compare){
  bstree * p = pRoot;
  while(*p){
	if(compare((*p)->m_data,value) == EQUAL){
	  return TRUE;
	}else if(compare((*p)->m_data,value) == GREATER){
	  p = &((*p)->m_left);
	}else{
	  p = &((*p)->m_right);
	}
  }
  return FALSE;
}
/*
 * 清空树操作
 * @pRoot 树的根指针
 * @return 成功返回TRUE,失败返回FALSE
 */
status free_bstree(bstree * pRoot){
  if(*pRoot){
	_free_bstree(*pRoot);
	*pRoot = NULL;
	return TRUE;
  }else{
	return FALSE; //空树
  }
}
/*
 * 清空辅助函数
 * @p 待清空的树指针
 */
void _free_bstree(bstree p){
  if(p){
	_free_bstree(p->m_left);
	_free_bstree(p->m_right);
	free(p);
  }
}
/*
 * 中序遍历函数
 * @pRoot 根指针
 * @visit 访问函数
 * @return 成功返回TRUE,错误返回FALSE
 */
status inOrder_bstree(bstree pRoot,visitFunc visit){
  if(pRoot){
	_inOrder_bstree(pRoot,visit);
	return TRUE;
  }else{
	return FALSE;
  }
}
/*
 * 中序遍历函数
 * @p 指针
 * @visit 访问函数
 */
void _inOrder_bstree(bstree p,visitFunc visit){
  if(p){
	_inOrder_bstree(p->m_left,visit);
	visit(p->m_data);
	_inOrder_bstree(p->m_right,visit);
  }
}

#endif
