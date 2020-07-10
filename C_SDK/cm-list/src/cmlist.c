#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <cmlog.h>

#include "_cmlistwrap.h"

list_t *create_list()
{
	size_t size = sizeof(list_t);
	list_t *head = (list_t *) calloc(1, size);
	if (head != null)
	{
        log_info("create list success.");
        memset(head, 0, size);
		head->_lenght = 0;
		head->_first = null;
        head->_last = null;
		return head;
	}
	
    log_debug("craete list, flag:[%p]", head);
	return null;
}

list_node_t *create_empty_node(void)
{
    return null;
}

list_node_t *create_node(data_t *pdata)
{
    return null;
}

/*********************************** insert **********************************/
// 从头部插入一个数据节点 
bool insert_front(list_t *plist, data_t *pdata)
{
	if (plist == NULL || pdata == NULL)
	{
		return false;
	}
	
    list_node_t *pnode = (list_node_t *) malloc(sizeof(list_node_t));
    if (pnode == null)
    {
        log_warn("inset front failed, malloc node failed.");
        return false;
    }
    memset(pnode, 0, sizeof(list_node_t));
    pnode->_pdata = pdata;
    if (plist->_first == null && plist->_last == null)
    {
        pnode->_next = pnode;
        pnode->_prev = pnode;

        plist->_first = pnode;
        plist->_last = pnode;
        
        plist->_lenght ++;
        return true;
    }

    plist->_last->_next = pnode;
    plist->_first->_prev = pnode;

    pnode->_next = plist->_first;
    pnode->_prev = plist->_last;

    plist->_first = pnode;
    plist->_lenght ++;
    
	return true;
}

// 从尾部插入一个数据节点 
bool insert_back(list_t *plist, void *data)
{
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
        plist->_lenght --;
    }

    if (plist->_first == null && plist->_last == null)
    {
        pnode->_next = pnode;
        pnode->_prev = pnode;

        plist->_first = pnode;
        plist->_last = pnode;
        
        plist->_lenght ++;
        return true;
    }
    plist->_last->_next = pnode;
    plist->_first->_prev = pnode;

    pnode->_next = plist->_first;
    pnode->_prev = plist->_last;

    plist->_first = pnode;
    plist->_lenght ++;

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