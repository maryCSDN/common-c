#ifndef _BILATE_LINKED_LIST_H
#define _BILATE_LINKED_LIST_H

#include <stdbool.h>

typedef struct _list_node{
	void *_data;
	struct _list_node *_next;
	struct _list_node *_prev;
} list_node_t;

typedef struct _list_head{
	int _lenght;
	struct _list_node *_first;
	struct _list_node *_last;
} list_t;

/******************************************************
*
*	public interface	
*
******************************************************/

/*********************************** create **********************************/ 
// 创建一个带头节点的空链表 
list_t *create_list(void);

/*********************************** destory **********************************/ 
// 删除一个带头节点的链表 
void (*delete_data_function)(void *delete_data);
void destory_list(list_t *plist, void *delete_data);

/*********************************** print ***********************************/ 
// 显示链表所有节点的data
typedef void (*print_data_function_t)(void *print_data);
void (*print_data_function)(void *print_data);
void print_list(list_t *plist, print_data_function_t print_func);

/*********************************** insert **********************************/
// 从头部插入一个节点 
bool insert_front_node(list_t *plist, list_node_t *pnode);

// 从头部插入一个数据节点 
bool insert_front(list_t *plist, void *data);

// 从尾部插入一个数据节点 
bool insert_back(list_t *plist, void *data);

// 在第index节点之前插入  index 属于 [1,length] 
bool insert_index_front(list_t *plist, int index, void *data); 

// 在第index节点之后插入  index 属于 [0,length] 
bool insert_index_back(list_t *plist, int index, void *data);


/********************************** delete ***********************************/
// 删除节点的方法 
typedef void (*_delete_data_method)(void *data);

// 删除头部节点 
bool delete_front(list_t *plist, void *delete_data_function);

// 删除尾部节点 
bool delete_back(list_t *plist, void *delete_data_function);

// 删除第index节点 
bool delete_index(list_t *plist, void *delete_data_function);


/********************************** get ***************************************/
// 获取第一个节点数据
void *get_front_data(list_t *plist);

// 获取最后一个节点的数据 
void *get_back_data(list_t *plist); 

// 获取第index节点数据 
void *get_index_data(list_t *plist, int index); 


/********************************* sort ***************************************/ 
typedef int (*compare_func_t)(void *left, void *right);
int (*compare_func)(void *left, void *right);
void sort_insert(list_t *plist, compare_func_t fcompare);

/******************************************************
*
*	private interface	
*
******************************************************/
 
#endif
