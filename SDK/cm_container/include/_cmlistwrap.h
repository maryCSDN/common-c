#ifndef _BILATE_LINKED_LIST_WRAP_H
#define _BILATE_LINKED_LIST_WRAP_H

#include <stdbool.h>

#ifdef _cplusplus
extern "C"
{
#endif

/* 定义链表节点结构（私有，不允许在外部使用） */
typedef struct _list_node{
    data_t *_pdata;                 /* 数据类型 */
    struct _list_head *_belong;     /* 保存头节点的地址, 用于判断节点所属链表 */
    struct _list_node *_next;       /* 后继节点 */
    struct _list_node *_prev;       /* 前驱结点 */
} list_node_t;

/* 定义链表头部结构 */
typedef struct _list_head{
    int _lenght;                    /* 节点个数 */
    struct _list_node *_first;      /* 头节点标记 */
    struct _list_node *_last;       /* 尾节点标记 */
} list_t;

#define null	NULL
/* 标识回调函数 */
#define LIST_CALLBACK

/* 定义数据类型 */
typedef void data_t;
/* 打印data的回调函数 */
typedef void (*print_f)(data_t *);
/* 删除data的回调函数 */
typedef void (*delete_f)(data_t *);


/*********************************** create **********************************/ 
/* 创建一个带头节点的空链表 */
extern list_t *create_list(void);


/*********************************** destory **********************************/ 
/* 清空数据节点 保留链表头 */
extern void clear_list(list_t *plist, LIST_CALLBACK delete_f delete_cb);
/* 摧毁一个链表 */
extern void destory_list(list_t **pplist, LIST_CALLBACK delete_f delete_cb);


/*********************************** insert **********************************/ 
/* 从头部插入一个数据节点 */
extern bool insert_head(list_t *plist, const data_t *pdata);
/* 从尾部插入一个数据节点 */
extern bool insert_tail(list_t *plist, const data_t *pdata);
/* 在第index节点之前插入  index 属于 [1,length] */
extern bool insert_front(list_t *plist, const unsigned int index, const data_t *pdata); 
/* 在第index节点之后插入  index 属于 [0,length] */
extern bool insert_back(list_t *plist, const unsigned int index, const data_t *pdata);


/*********************************** delete **********************************/ 
/* 删除头部节点 */
extern bool delete_head(list_t *plist, LIST_CALLBACK delete_f delete_cb);
/* 删除尾部节点 */
extern bool delete_tail(list_t *plist, LIST_CALLBACK delete_f delete_cb);
/* 删除node */
extern bool delete_node_by_data(list_t *plist, const data_t *pdata, LIST_CALLBACK delete_f delete_cb);
/* 删除第index节点 */
extern bool delete_node_by_index(list_t *plist, const unsigned int index, LIST_CALLBACK delete_f delete_cb);


/*********************************** print ***********************************/ 
/* 打印链表数据 */
extern void print_list(list_t *plist, LIST_CALLBACK print_f print_cb);


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

/********************************* check ***************************************/
/* 无数据节点的空链表 */
bool is_empty_list(list_t *plist);

#ifdef _cplusplus
}
#endif
 
#endif