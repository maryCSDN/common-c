#ifndef _BILATE_LINKED_LIST_WRAP_H
#define _BILATE_LINKED_LIST_WRAP_H

#include <stdbool.h>

#ifdef _cplusplus
extern "C"
{
#endif

typedef void data_t;

typedef struct _list_node{
	data_t *_pdata;
    struct _list_head *_belong;     /* 保存头节点的地址, 用于判断节点所属链表 */
	struct _list_node *_next;
	struct _list_node *_prev;
} list_node_t;

typedef struct _list_head{
	int _lenght;
	struct _list_node *_first;
	struct _list_node *_last;
} list_t;

#define null	NULL

/*********************************** create **********************************/ 
// 创建一个带头节点的空链表 
extern list_t *create_list(void);
// 创建一个初始化的空节点
extern list_node_t *create_empty_node(void);
// 创建一个带数据的节点
extern list_node_t *create_node(data_t *pdata);

/*********************************** insert **********************************/
// 从头部插入一个节点 
extern bool insert_front_node(list_t *plist, list_node_t *pnode);
// 从头部插入一个数据节点 
extern bool insert_front(list_t *plist, data_t *pdata);
// 从尾部插入一个数据节点 
extern bool insert_back(list_t *plist, data_t *pdata);
// 在第index节点之前插入  index 属于 [1,length] 
extern bool insert_index_front(list_t *plist, int index, data_t *pdata); 
// 在第index节点之后插入  index 属于 [0,length] 
extern bool insert_index_back(list_t *plist, int index, data_t *pdata);

/*********************************** print ***********************************/ 
// 显示链表所有节点的data
typedef void (*printf_t)(data_t *pdata);
void (*print_function)(data_t *pdata);
extern void print_list(list_t *plist, printf_t print_func);

/*********************************** destory **********************************/ 
// // 删除节点数据的方法
// typedef void (*deletef_t)(data_t *);
// void (*delete_function)(data_t *);
// // 摧毁一个链表 
// extern void destory_list(list_t *plist, deletef_t delete_func);
// // 清空节点 保留链表头
// extern void clear_list(list_t *plist, deletef_t delete_func);
// // 删除头部节点 
// extern bool delete_front(list_t *plist, deletef_t delete_func);
// // 删除尾部节点 
// extern bool delete_back(list_t *plist, deletef_t delete_func);
// // 删除第index节点 
// extern bool delete_index(list_t *plist, int index, deletef_t delete_func);
// // 删除此节点
// extern bool delete_node(list_t *plist, list_node_t *pnode);

/********************************** get ***************************************/
// // 获取第一个节点数据
// extern void *get_front_data(list_t *plist);
// // 获取最后一个节点的数据 
// extern void *get_back_data(list_t *plist); 
// // 获取第index节点数据 
// extern void *get_index_data(list_t *plist, int index); 
// // 获取当前节点数据
// extern list_node_t *get_node_data(list_t *plist, list_node_t *node);
// // 获取头节点
// extern list_node_t *get_front_node(list_t *plist);
// // 获取尾节点
// extern list_node_t *get_back_node(list_t *plist);
// // 获取前驱节点
// extern list_node_t *get_prev_node(list_t *plist, list_node_t *pnode);
// // 获取后继节点
// extern list_node_t *get_next_node(list_t *plist, list_node_t *pnode);


// /********************************* sort ***************************************/ 
// typedef int (*comparef_t)(void *left, void *right);
// int (*compare_function)(void *left, void *right);
// extern void sort_insert(list_t *plist, comparef_t compare_func);

#ifdef _cplusplus
}
#endif
 
#endif