#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <cmlog.h>

#include "_cmlistwrap.h"

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

list_node_t *create_empty_node(void)
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

list_node_t *create_node(data_t *pdata)
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

/*********************************** insert **********************************/
bool insert_front(list_t *plist, data_t *pdata)
{
    if (plist == NULL || pdata == NULL)
    {
        log_error("The node failed to insert into the linked list @[The parameter cannot be null]");
        return false;
    }

    list_node_t *pnode = create_node(pdata);
    if (pnode == null)
    {
        log_error("The node failed to insert into the linked list @[create node failed]");
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

bool insert_back(list_t *plist, void *pdata)
{
    if (plist == NULL || pdata == NULL)
    {
        log_error("The node failed to insert into the linked list @[The parameter cannot be null]");
        return false;
    }

    list_node_t *pnode = create_node(pdata);
    if (pnode == null)
    {
        log_error("The node failed to insert into the linked list @[create node failed]");
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

// 在第index节点之前插入  index 属于 [1,length]
bool insert_index_front(list_t *plist, int index, void *data)
{
    return true;
}

// 在第index节点之后插入  index 属于 [0,length]
bool insert_index_back(list_t *plist, int index, void *data)
{
    return true;
}

// 从头部插入一个节点
bool insert_front_node(list_t *plist, list_node_t *pnode)
{
    if (plist == NULL || pnode == NULL)
    {
        return false;
    }

    // 如果此节点是当前链表中已存在的节点, 需要将此节点前后链接
    if (pnode->_next != null && pnode->_prev != null && pnode->_next != pnode->_prev)
    {
        pnode->_prev->_next = pnode->_next;
        pnode->_next->_prev = pnode->_prev;
        plist->_lenght--;
    }

    if (plist->_first == null && plist->_last == null)
    {
        pnode->_next = pnode;
        pnode->_prev = pnode;

        plist->_first = pnode;
        plist->_last = pnode;

        plist->_lenght++;
        return true;
    }
    plist->_last->_next = pnode;
    plist->_first->_prev = pnode;

    pnode->_next = plist->_first;
    pnode->_prev = plist->_last;

    plist->_first = pnode;
    plist->_lenght++;

    return true;
}

/*********************************** print ***********************************/
// 显示链表所有节点的data
void print_list(list_t *plist, printf_t print_func)
{
    if (plist == null)
    {
        log_warn("list is null");
        return;
    }

    if (plist->_lenght < 1)
    {
        log_info("list not node");
        return;
    }

    list_node_t *node = plist->_first;
    int i = 0;
    for (; i < plist->_lenght; i++)
    {
        print_function = print_func;
        print_function(node->_pdata);

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
bool is_empty_list(list_t *list)
{
    if (list == null)
    {
        log_error("Error checking linked list for empty@[The parameter cannot be null]");
        exit(1);
    }

    return (list->_lenght == 0);
}