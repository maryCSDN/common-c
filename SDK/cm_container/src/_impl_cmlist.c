/**
 * 注释：
 * static方法仅为内部调用
 * _do系列方法不需要参数检查
 * LIST_CALLBACK作为回调函数的标识
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <cmlog.h>

#include "include/cmlistwrap.h"

static list_node_t *create_empty_node(void);
static list_node_t *create_node(data_t *pdata);
static void delete_head_do(list_t *plist, LIST_CALLBACK delete_f delete_cb);
static void free_node_do(list_node_t *pnode, LIST_CALLBACK delete_f delete_cb);


/*** create ***/ 

/**
 * 创建空链表
 */ 
list_t *create_list(void)
{
    list_t *head = (list_t *)calloc(1, sizeof(list_t));
    if (head == null)
    {
        log_error("Failed to create list @[out of memory]");
        return null;
    }

    log_debug("craete list success @[address flag:%p]", head);
    head->_length = 0;
    head->_head = null;
    head->_tail = null;
    return head;
}

/**
 * 创建无数据节点
 */ 
static list_node_t *create_empty_node(void)
{
    list_node_t *node = (list_node_t *)calloc(1, sizeof(list_node_t));
    if (null == node)
    {
        log_error("Failed to create list node @[out of memory]");
        return null;
    }

    node->_belong = null;
    node->_next = null;
    node->_prev = null;

    return node;
}

/**
 * 创建带数据节点
 * pdata：数据 （数据不能为空，除非使用指定的创建空数据节点方法）
 */ 
static list_node_t *create_node(data_t *pdata)
{
    if (null == pdata)
    {
        log_error("Failed to create list node @[The parameter cannot be null]");
        return null;
    }

    list_node_t *node = create_empty_node();
    if (null == node)
    {
        log_error("Failed to create list node @[out of memory]");
        return null;
    }

    node->_pdata = pdata;
    return node;
}


/*** destory ***/

/**
 * 清空链表节点
 * plist：非空链表
 * delete_cb: 释放自定义数据的
 */
void clear_list(list_t *plist, LIST_CALLBACK delete_f delete_cb)
{
    log_debug("clear list");
    if (plist == null || plist->_length == 0)
    {
        return;
    }

    while (plist->_length > 0)
    {
        delete_head_do(plist, delete_cb);
    }
}

/**
 * 销毁链表（释放所有节点，并删除链表自身）
 * pplist:链表的指针，为了在销毁后将链表置空，避免误操作
 * delete_cb:删除自定义节点的回调方法
 */ 
void destory_list(list_t **pplist, LIST_CALLBACK delete_f delete_cb)
{
    if (null == pplist || null == *pplist)
    {
        return;
    }

    clear_list(*pplist, delete_cb);
    free(*pplist);
    *pplist = null;
}


/*** delete ***/
bool delete_head(list_t *plist, LIST_CALLBACK delete_f delete_cb)
{
    return true;
}

bool delete_tail(list_t *plist, LIST_CALLBACK delete_f delete_cb)
{
    return true;
}

bool delete_node_by_data(list_t *plist, data_t *pdata, LIST_CALLBACK delete_f delete_cb)
{
    return true;
}

bool delete_node_by_index(list_t *plist, const unsigned int index, LIST_CALLBACK delete_f delete_cb)
{
    return true;
}

static void delete_head_do(list_t *plist, LIST_CALLBACK delete_f delete_cb)
{
    list_node_t *pnode = plist->_head;
    
    if (plist->_length == 1)
    {
        if (plist->_head != plist->_tail)
        {
            log_error("Failed to delete head node @[list only have one node, but head node unequal tail node]");
            exit(1);
        }

        plist->_head = null;
        plist->_tail = null;
        plist->_length = 0;
    }

    else if (plist->_length > 1)
    {
        plist->_head = pnode->_next;
        pnode->_next->_prev = plist->_tail;
        plist->_tail->_next = plist->_head;
        plist->_length--;
    }

    free_node_do(pnode, delete_cb);
}

static inline void free_node_do(list_node_t *pnode, LIST_CALLBACK delete_f delete_cb)
{
    delete_cb(pnode->_pdata);
    free(pnode);
}


/*** insert ***/
bool insert_head(list_t *plist, data_t *pdata)
{
    if (plist == null || pdata == null)
    {
        log_error("The node failed to insert into the linked list head @[The parameter cannot be null]");
        return false;
    }

    list_node_t *pnode = create_node(pdata);
    if (pnode == null)
    {
        log_error("The node failed to insert into the linked list head @[create node failed]");
        return false;
    }

    if (is_empty_list(plist))
    {
        /* 给空链表添加第一个节点 */
        pnode->_next = pnode;
        pnode->_prev = pnode;

        plist->_head = pnode;
        plist->_tail = pnode;
    }
    else
    {
        /* 头插 */
        pnode->_next = plist->_head;
        pnode->_prev = plist->_tail;

        plist->_head->_prev = pnode;
        plist->_tail->_next = pnode;

        plist->_head = pnode;
    }

    plist->_length++;
    pnode->_belong = plist;
    return true;
}

bool insert_tail(list_t *plist, data_t *pdata)
{
    if (plist == NULL || pdata == NULL)
    {
        log_error("The node failed to insert into the linked list tail @[The parameter cannot be null]");
        return false;
    }

    list_node_t *pnode = create_node(pdata);
    if (pnode == null)
    {
        log_error("The node failed to insert into the linked list tail @[create node failed]");
        return false;
    }

    if (is_empty_list(plist))
    {
        /* 给空链表添加第一个节点 */
        pnode->_next = pnode;
        pnode->_prev = pnode;

        plist->_head = pnode;
        plist->_tail = pnode;
    }
    else
    {
        /* 尾插 */
        pnode->_next = plist->_head;
        pnode->_prev = plist->_tail;

        plist->_head->_prev = pnode;
        plist->_tail->_next = pnode;

        plist->_tail = pnode;
    }

    plist->_length++;
    pnode->_belong = plist;
    return true;
}

bool insert_front(list_t *plist, const unsigned int index, data_t *pdata)
{
    if (plist == NULL || pdata == NULL)
    {
        log_error("The node failed to insert into the linked list @[The parameter cannot be null]");
        return false;
    }

    if (is_empty_list(plist))

    if (index < 1)
    {
        log_warn("");
    }
    return true;
}

bool insert_back(list_t *plist, const unsigned int index, data_t *pdata)
{
    return true;
}


/*** print ***/
void print_list(list_t *plist, LIST_CALLBACK print_f print_cb)
{
    if (plist == null || print_cb == null)
    {
        log_warn("Failed to print list@[The parameter cannot be null]");
        return;
    }

    if (is_empty_list(plist))
    {
        log_info("Failed to print list@[empty linked list, no nodes]");
        return;
    }

    list_node_t *node = plist->_head;
    int i;
    for (i = 0; i < plist->_length; i++)
    {
        print_cb(node->_pdata);
        node = node->_next;
    }
}

/********************************* sort ***************************************/
// void sort_insert(list_t *plist, comparef_t compare_func)
// {
//     log_debug("start list sort insert.");
//     if (fcompare == null)
//     {
//         log_warn("param compare function is null, sort failed.");
//         return;
//     }

//     if (plist == NULL)
//     {
//         log_warn("list is null. sort failed.");
//         return;
//     }

//     if (plist->_length < 1)
//     {
//         return;
//     }

//     if (plist->_head == null || plist->_head->_data == null
//         || plist->_tail == null || plist->_tail->_data == null)
//     {
//         log_warn("list hava null node or data, sort failed.");
//         return;
//     }

//     list_node_t *node = plist->_head->_next;
//     compare_func = fcompare;
//     int i = 1;
//     for (; i < plist->_length; i++)
//     {
//         list_node_t *node_dup = node;
//         node = node->_next;

//         list_node_t *prev = node_dup->_prev;
//         while(prev != plist->_tail)
//         {
//             if (compare_func(prev->_data, node_dup->_data) <= 0)
//             {
//                 if (prev == node_dup->_prev)
//                 {
//                     break;
//                 }

//                 node_dup->_prev->_next = node_dup->_next;
//                 node_dup->_prev->_next->_prev = node_dup->_prev;

//                 node_dup->_next = prev->_next;
//                 node_dup->_next->_prev = node_dup;

//                 node_dup->_prev = prev;
//                 node_dup->_prev->_next = node_dup;
//                 break;
//             }
//             else if (prev == plist->_head)
//             {
//                 // insert_front_node(plist, node_dup);
//                 node_dup->_prev->_next = node_dup->_next;
//                 node_dup->_next->_prev = node_dup->_prev;

//                 node_dup->_next = prev;
//                 node_dup->_prev = prev->_prev;

//                 node_dup->_next->_prev = node_dup;
//                 node_dup->_prev->_next = node_dup;

//                 plist->_head = node_dup;
//                 break;
//             }

//             prev = prev->_prev;
//         }
//     }
// }


/********************************* check ***************************************/
bool is_empty_list(list_t *plist)
{
    if (plist == null)
    {
        log_error("Error checking linked list for empty@[The parameter cannot be null]");
        exit(1);
    }

    return (plist->_length == 0);
}