/*
 * Avl树
 * Zaks Wang
 * 2014-1-4
 */
#ifndef __AVLTREE_H_
#define __AVLTREE_H_
#include <stdlib.h>
#include "def.h"

typedef struct avlnode{
  void * m_data;
  struct avlnode * m_left;
  struct avlnode * m_right;
  status m_bf; //balance factor,EQUAL 表示左子树 == 右子树 GREATER 表示左子树 > 右子树 LOWER 表示左子树 < 右子树
}avlnode, * avltree;

#define le2tree(le, member) to_struct((le), struct avlnode, member)

#define offsetof(type, member) ((size_t)(&((type *)0)->member))

#define to_struct(ptr, type, member) ((type *)((char *)(ptr) - offsetof(type, member)))

/*	public func define	*/
typedef status (*compareFunc)(void * a,void * b); //定义比较函数
typedef void (*visitFunc)(void * a); //遍历访问函数
status ini_avltree(avltree* pRoot); //初始化操作,赋值为NULL
status empty_avltree(const avltree * pRoot); //判断是否为空
status insert_avltree(avltree * pRoot,void * value,compareFunc func); //插入元素操作
status delete_avltree(avltree * pRoot,void * value,compareFunc func); //删除元素操作
status find_avltree(const avltree * pRoot,void * value,compareFunc func); //查找元素是否存在
status inOrder_avltree(const avltree * pRoot,visitFunc visit); //中序遍历函数
status free_avltree(avltree * pRoot); //清空树


/*	private func define	*/
status _insert_avltree(avltree * pRoot,void * value,compareFunc func,status * taller); //插入元素操作
status _delete_avltree(avltree * pRoot,void * value,compareFunc compare,status * shorter); //删除元素操作
void _leftBalance(avltree * pRoot); //调整左子树
void _rightBlance(avltree * pRoot); //调整右子树
void _leftLeftAdj(avltree * pRoot); //左左的情况
void _leftRightAdj(avltree * pRoot); //左右情况
void _rightLeftAdj(avltree * pRoot); //右左情况
void _rightRightAdj(avltree * pRoot); //右右情况
status _inOrder_avltree(const avltree pRoot,visitFunc visit);
void _free_avltree(avltree p);
/*	for debug	*/
void print(const avltree * tree){
  printf("Root:%d\tm_left:%d\tm_right:%d\tm_data:%dm_bf:%d\n",*tree,(*tree)->m_left,(*tree)->m_right,*(int *)(*tree)->m_data,(*tree)->m_bf);
}

/*	implement	*/
/*
 * 初始化操作
 * @pRoot 根指针
 * @return 返回TRUE
 */
status ini_avltree(avltree* pRoot){
  *pRoot = NULL;
  return TRUE;
}
/*
 * 判断是否为空
 * @pRoot 根指针
 * @return 空返回TRUE,否则返回FALSE
 */
status empty_avltree(const avltree * pRoot){
  return (*pRoot == NULL)?TRUE:FALSE;
}
/*
 * 插入操作
 * @pRoot 根指针
 * @value 待插入元素
 * @func 比较函数
 * @return 成功返回TRUE,存在相同节点返回FALSE,内存不够返回OVERFLOW
 */
status insert_avltree(avltree * pRoot,void * value,compareFunc compare){
  status taller;
  return  _insert_avltree(pRoot,value,compare,&taller);
}
/*
 * 插入操作辅助函数
 * @pRoot 根指针
 * @value 待插入元素
 * @taller 父节点是否长高
 * @func 比较函数
 * @return 成功返回TRUE,存在相同节点返回FALSE,内存不够返回OVERFLOW
 */
status _insert_avltree(avltree * pRoot,void * value,compareFunc compare,status * taller){
  if(*pRoot == NULL){ //找到插入节点,直接插入
	*pRoot = (avltree) malloc(sizeof(avlnode));
	if(*pRoot == NULL){ return OVERFLOW;}
	(*pRoot)->m_data = value; (*pRoot)->m_left = NULL; (*pRoot)->m_right = NULL; (*pRoot)->m_bf = EQUAL;
	*taller = TRUE;
	return TRUE;
  }else{
	if(compare((*pRoot)->m_data,value) == EQUAL){ //找到相等的
	  *taller = FALSE;
	  return FALSE;
	}else if(compare((*pRoot)->m_data,value) == GREATER){ //当前值比value大,从左子树找
	  status ret = _insert_avltree(&((*pRoot)->m_left),value,compare,taller); //在左子树中插入
	  if(ret == TRUE){ //插入成功后处理平衡
		if(*taller == TRUE){
		  if((*pRoot)->m_bf == EQUAL){ //原来左右子树相等,现在插入后左子树高
			(*pRoot)->m_bf = GREATER; *taller = TRUE;
		  }else if((*pRoot)->m_bf == GREATER){ //原来左子树高,现在插入后需要调整,调整后平衡
			_leftBalance(pRoot); *taller = FALSE;
		  }else if((*pRoot)->m_bf == LOWER){ //原来左子树低,插入后平衡
			(*pRoot)->m_bf = EQUAL; *taller = FALSE;
		  }
		}
	  }
	  return ret; //溢出或没有插入返回
	}else{ //当前值比value小,从右子树找
	  status ret = _insert_avltree(&((*pRoot)->m_right),value,compare,taller);
	  if(ret == TRUE){
		if(*taller == TRUE){
		  if((*pRoot)->m_bf == EQUAL){ //右子树增高
			(*pRoot)->m_bf = LOWER; *taller = TRUE;
		  }else if((*pRoot)->m_bf == GREATER){
			(*pRoot)->m_bf = EQUAL; *taller = FALSE;
		  }else if((*pRoot)->m_bf == LOWER){
			_rightBlance(pRoot); *taller = FALSE;
		  }
		}
	  }
	  return ret; //返回溢出
	}
  }
}

/*
 * 处理左子树失衡
 * @pRoot 根指针
 */
void _leftBalance(avltree * pRoot){
  if((*pRoot)->m_left->m_bf == GREATER){ //左左的情况
	(*pRoot)->m_bf = (*pRoot)->m_left->m_bf = EQUAL; //旋转后平衡
	_leftLeftAdj(pRoot);
  }else{ //左右的情况
	if((*pRoot)->m_left->m_right->m_bf == GREATER){ //左孩子的右孩子的平衡度,左大
	  (*pRoot)->m_bf = LOWER; (*pRoot)->m_left->m_bf = EQUAL;
	}else if((*pRoot)->m_left->m_right->m_bf == EQUAL){ //相等
	  (*pRoot)->m_bf = EQUAL; (*pRoot)->m_left->m_bf = EQUAL;
	}else{ //右大
	  (*pRoot)->m_bf = EQUAL; (*pRoot)->m_left->m_bf = GREATER;
	}
	(*pRoot)->m_left->m_right->m_bf = EQUAL;
	_leftRightAdj(pRoot);
  }
}
/*
 * 处理右子树失衡
 * @pRoot 根指针
 */
void _rightBlance(avltree * pRoot){
  if((*pRoot)->m_right->m_bf == GREATER){ //右左的情况
	if((*pRoot)->m_right->m_left->m_bf == GREATER){ //右孩子的左孩子
	  (*pRoot)->m_bf = EQUAL; (*pRoot)->m_right->m_bf = LOWER;
	}else if((*pRoot)->m_right->m_left->m_bf == EQUAL){
	  (*pRoot)->m_bf = EQUAL; (*pRoot)->m_right->m_bf = EQUAL;
	}else{
	  (*pRoot)->m_bf = GREATER; (*pRoot)->m_right->m_bf = EQUAL;
	}
	(*pRoot)->m_right->m_left->m_bf = EQUAL;
	_rightLeftAdj(pRoot);
  }else{ //右右的情况
	(*pRoot)->m_right->m_bf = (*pRoot)->m_bf = EQUAL; //旋转后平衡
	_rightRightAdj(pRoot);
  }
}
/*
 * 左左情况旋转
 * @pRoot 根指针
 */
void _leftLeftAdj(avltree * pRoot){
  avltree leftChild = (*pRoot)->m_left;
  (*pRoot)->m_left = leftChild->m_right;
  leftChild->m_right = (*pRoot);
  *pRoot = leftChild;
}
/*
 * 左右情况处理
 * @pRoot 根指针
 */
void _leftRightAdj(avltree * pRoot){
  _rightRightAdj(&((*pRoot)->m_left)); //对左儿子做右右操作
  _leftLeftAdj(pRoot); //然后左左旋转
}
/*
 * 右右情况旋转
 * @pRoot 根指针
 */
void _rightRightAdj(avltree * pRoot){
  avltree rightChild = (*pRoot)->m_right;
  (*pRoot)->m_right = rightChild->m_left;
  rightChild->m_left = (*pRoot);
  *pRoot = rightChild;
}
/*
 * 右左情况处理
 * @pRoot 根指针
 */
void _rightLeftAdj(avltree * pRoot){
  _leftLeftAdj(&((*pRoot)->m_right));
  _rightRightAdj(pRoot);
}
/*
 * 删除元素操作
 * @pRoot 根指针
 * @value 待删除的元素
 * @compare 比较函数
 * @return 没找到返回FALSE,找到并删除返回TRUE
 */
status delete_avltree(avltree * pRoot,void * value,compareFunc compare){
  status shorter;
  return _delete_avltree(pRoot,value,compare,&shorter);
}
/*
 * 删除操作的辅助操作
 * @pRoot 根指针
 * @value 待删除元素
 * @compare 比较函数
 * @shorter 高度变化
 */
status _delete_avltree(avltree * pRoot,void * value,compareFunc compare,status * shorter){
  if(*pRoot == NULL){
	return FALSE; //找不到
  }else{
	if(compare((*pRoot)->m_data,value) == EQUAL){ //当前即是删除节点
	  if((*pRoot)->m_left && (*pRoot)->m_right){ //有左右孩子
		avltree * p = &((*pRoot)->m_right);
		while(*p){
		  p = &((*p)->m_left); //找到最左
		}
		avltree pDel = le2tree(p,m_left); //找到待删除的元素指针
		void * pData = (*pRoot)->m_data; //交换当前节点和右孩子最左节点的值
		(*pRoot)->m_data = pDel->m_data;
		pDel->m_data = pData;
		_delete_avltree(&((*pRoot)->m_right),pData,compare,shorter); //去右子树中,肯定能删除,所以不会判断ret是否为TRUE
		if(*shorter == TRUE){
		  if((*pRoot)->m_bf == EQUAL){ //原来相等,现在右少
			(*pRoot)->m_bf = GREATER; *shorter = FALSE;
		  }else if((*pRoot)->m_bf == GREATER){ //原来左大一,现在左大二,调整
			_leftBalance(pRoot); *shorter = FALSE;
		  }else{ //原来右大,现在右少一,相等
			(*pRoot)->m_bf = EQUAL; *shorter = TRUE;
		  }
		}
	  }else{
		if((*pRoot)->m_left){ //只有左孩子
		  if((*pRoot)->m_data){	free((*pRoot)->m_data);}
		  (*pRoot)->m_data = (*pRoot)->m_left->m_data;
		  free((*pRoot)->m_left); //删除左孩子
		  (*pRoot)->m_left = NULL;
		  (*pRoot)->m_bf = EQUAL;
		}else if((*pRoot)->m_right){ //只有右孩子
		  if((*pRoot)->m_data){	free((*pRoot)->m_data);}
		  (*pRoot)->m_data = (*pRoot)->m_right->m_data;
		  free((*pRoot)->m_right);
		  (*pRoot)->m_right = NULL;
		  (*pRoot)->m_bf = EQUAL;
		}else{ //没有孩子
		  if((*pRoot)->m_data){	free((*pRoot)->m_data);}
		  free(*pRoot);
		  *pRoot = NULL;
		}
		*shorter = TRUE;
	  }
	  return TRUE; //对以上两种情况都返回TRUE
	}else if(compare((*pRoot)->m_data,value) == GREATER){ //比value大,到左子树删除
	  status ret = _delete_avltree(&((*pRoot)->m_left),value,compare,shorter); //左子树去
	  if(ret == TRUE){ //左子树删除了
		if(*shorter == TRUE){
		  if((*pRoot)->m_bf == GREATER){
			(*pRoot)->m_bf = EQUAL; *shorter = TRUE;
		  }else if((*pRoot)->m_bf == EQUAL){
			(*pRoot)->m_bf = LOWER; *shorter = FALSE;
		  }else{ //右高的情况,左少了,那么变成了右右的情况,做平衡处理
			_rightBlance(pRoot); *shorter = FALSE;
		  }
		}
	  }
	  return ret;
	}else{ //比value小,到右子树删除
	  status ret = _delete_avltree(&((*pRoot)->m_right),value,compare,shorter); //左子树去
	  if(ret == TRUE){ //右子树删除了
		if(*shorter == TRUE){
		  if((*pRoot)->m_bf == GREATER){
			_leftBalance(pRoot); *shorter = FALSE;
		  }else if((*pRoot)->m_bf == EQUAL){
			(*pRoot)->m_bf = GREATER; *shorter = FALSE;
		  }else{ //右高的情况,右少了一层,那么对上层来说,子树高度少一,所以*shorter = TRUE
			(*pRoot)->m_bf = EQUAL; *shorter = TRUE;
		  }
		}
	  }
	  return ret;
	}
  }
}
/*
 * 查找元素是否存在
 * @pRoot 根指针
 * @value 待查找值
 * @func 比较函数
 * @return 找到返回TRUE,否则返回FALSE
 */
status find_avltree(const avltree * pRoot,void * value,compareFunc compare){
  if(*pRoot == NULL){
	return FALSE;
  }else{
	if(compare((*pRoot)->m_data,value) == EQUAL){
	  return TRUE;
	}else if(compare((*pRoot)->m_data,value) == GREATER){
	  return find_avltree(&((*pRoot)->m_left),value,compare);
	}else{
	  return find_avltree(&((*pRoot)->m_right),value,compare);
	}
  }
}
/*
 * 中序遍历
 * @pRoot 根指针
 * @visit 访问函数
 * @return 根不为空返回TRUE,否则返回FALSE
 */
status inOrder_avltree(const avltree * pRoot,visitFunc visit){
  if(*pRoot){
	_inOrder_avltree(*pRoot,visit);
	return TRUE;
  }else{
	return FALSE;
  }
}
status _inOrder_avltree(const avltree pRoot,visitFunc visit){
  if(pRoot){
	_inOrder_avltree(pRoot->m_left,visit);
	visit(pRoot->m_data);
	_inOrder_avltree(pRoot->m_right,visit);
  }
}
/*
 * 清空树,释放内存
 * @pRoot 根指针
 * @return 成功返回TRUE,失败返回FALSE
 */
status free_avltree(avltree * pRoot){
  if(*pRoot){
	_free_avltree(*pRoot);
	*pRoot = NULL;
	return TRUE;
  }else{
	return FALSE;
  }
}
/*
 * 清空辅助函数
 * @p 待清空的树指针
 */
void _free_avltree(avltree p){
  if(p){
	_free_avltree(p->m_left);
	_free_avltree(p->m_right);
	if(p->m_data){ free(p->m_data); }
	free(p);
  }
}

#endif

