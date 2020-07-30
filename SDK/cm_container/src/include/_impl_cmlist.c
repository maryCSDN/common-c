#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <cmlog.h>

#include "_cmlistwrap.h"

/* 创建空节点（初始化） */
static list_node_t *create_empty_node(void);
/* 创建带数据节点 */
static list_node_t *create_node(data_t *pdata);
/* _do系列不需要参数检查，删除头结点 */
static void delete_head_do(list_t *list);

/*********************************** create **********************************/ 
list_t *create_list(void)
{
    list_t *head = (list_t *)calloc(1, sizeof(list_t));
    if (head == null)
    {
        log_error("Failed to create list @[out of memory]");
        return null;
    }

    log_debug("craete list success @[address flag:%p]", head);
    head->_lenght = 0;
    head->_first = null;
    head->_last = null;
    return head;
}

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


/*********************************** destory **********************************/
void clear_list(list_t *plist, LIST_CALLBACK delete_f delete_cb)
{
    if (plist == null || plist->_lenght == 0)
    {
        return;
    }

    list_node_t *pnode = plist->_first;
    unsigned int len = plist->_lenght;
    unsigned int i;
    for (i = 0; i < len; i++)
    {
        if (pnode == null)
        {
            log_warn("Error clearing the list @[node is null]");
            return;
        }
        pnode = pnode->_next;
        delete_head_do(plist, delete_cb);
    }
}

void destory_list(list_t **pplist, LIST_CALLBACK delete_f delete_cb)
{
    if (null == pplist || null == *pplist)
    {
        return;
    }

    clear_list(*pplist);
    free(*pplist);
    *pplist = null;
}


/*********************************** insert **********************************/
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

        plist->_first = pnode;
        plist->_last = pnode;
    }
    else
    {
        /* 头插 */
        pnode->_next = plist->_first;
        pnode->_prev = plist->_last;

        plist->_first->_prev = pnode;
        plist->_last->_next = pnode;

        plist->_first = pnode;
    }

    plist->_lenght++;
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

        plist->_first = pnode;
        plist->_last = pnode;
    }
    else
    {
        /* 尾插 */
        pnode->_next = plist->_first;
        pnode->_prev = plist->_last;

        plist->_first->_prev = pnode;
        plist->_last->_next = pnode;

        plist->_last = pnode;
    }

    plist->_lenght++;
    pnode->_belong = plist;
    return true;
}

bool insert_front(list_t *plist, int index, void *pdata)
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

bool insert_back(list_t *plist, int index, void *data)
{
    return true;
}


/* delete */
bool delete_head(list_t *plist, LIST_CALLBACK delete_f delete_cb);
bool delete_tail(list_t *plist, LIST_CALLBACK delete_f delete_cb);
bool delete_node_by_data(list_t *plist, const data_t *pdata, LIST_CALLBACK delete_f delete_cb);
bool delete_node_by_index(list_t *plist, const unsigned int index, LIST_CALLBACK delete_f delete_cb);


/*********************************** print ***********************************/
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

    list_node_t *node = plist->_first;
    int i;
    for (i = 0; i < plist->_lenght; i++)
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

//     if (plist->_lenght < 1)
//     {
//         return;
//     }

//     if (plist->_first == null || plist->_first->_data == null
//         || plist->_last == null || plist->_last->_data == null)
//     {
//         log_warn("list hava null node or data, sort failed.");
//         return;
//     }

//     list_node_t *node = plist->_first->_next;
//     compare_func = fcompare;
//     int i = 1;
//     for (; i < plist->_lenght; i++)
//     {
//         list_node_t *node_dup = node;
//         node = node->_next;

//         list_node_t *prev = node_dup->_prev;
//         while(prev != plist->_last)
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
//             else if (prev == plist->_first)
//             {
//                 // insert_front_node(plist, node_dup);
//                 node_dup->_prev->_next = node_dup->_next;
//                 node_dup->_next->_prev = node_dup->_prev;

//                 node_dup->_next = prev;
//                 node_dup->_prev = prev->_prev;

//                 node_dup->_next->_prev = node_dup;
//                 node_dup->_prev->_next = node_dup;

//                 plist->_first = node_dup;
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

    return (plist->_lenght == 0);
}