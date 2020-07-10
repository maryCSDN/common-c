#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <cmlog.h>

#include "cmlist.h"

#define null	NULL

/*********************************** create **********************************/ 
// 创建一个带头节点的空链表 
list_t *create_list()
{
	size_t size = sizeof(list_t);
	list_t *head = (list_t *) malloc(size);
	if (head != null)
	{
        LOG_INFO("create list success.");
        memset(head, 0, size);
		head->_lenght = 0;
		head->_first = null;
        head->_last = null;
		return head;
	}
	
	return null;
}

/*********************************** destory **********************************/ 
// 删除一个带头节点的链表 
void destory_list(list_t *plist, void *delete_data)
{
    if (plist == null)
    {
        return;
    }

    list_node_t *node = plist->_first;
    int i = 0;
    for (; i < plist->_lenght; i++)
    {
        list_node_t *_next = node->_next;
        delete_data_function = delete_data;
        delete_data_function(node->_data);

        free(node);
        node = _next;
    }

    free(plist);
}

/*********************************** print ***********************************/ 
// 显示链表所有节点的data
void print_list(list_t *plist, print_func_t printf)
{
    if (plist == null)
    {
        LOG_WARN("list is null");
        return;
    }

    if (plist->_lenght < 1)
    {
        LOG_INFO("list not node");
        return;
    }

    list_node_t *node = plist->_first;
    int i = 0;
    for (; i < plist->_lenght; i++)
    {
        print_func = printf;
        print_func(node->_data);

        node = node->_next;
    }
}

/*********************************** insert **********************************/
// 从头部插入一个数据节点 
bool insert_front(list_t *plist, void *data)
{
	if (plist == NULL || data == NULL)
	{
		return false;
	}
	
    list_node_t *pnode = (list_node_t *) malloc(sizeof(list_node_t));
    if (pnode == null)
    {
        LOG_WARN("inset front failed, malloc node failed.");
        return false;
    }
    memset(pnode, 0, sizeof(list_node_t));
    pnode->_data = data;
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

/********************************** delete ***********************************/
// 删除头部节点 
bool delete_front(list_t *plist, void *delete_data_function)
{
    return true;
}

// 删除尾部节点 
bool delete_back(list_t *plist, void *delete_data_function)
{
    return true;
}

// 删除第index节点 
bool delete_index(list_t *plist, int index, void *delete_data_function)
{
    return true;
}

bool delete_node(list_t *plist, list_node_t *pnode)
{
    if (plist == null || pnode == null)
    {
        LOG_ERROR("delete list node failed, params is null.");
        return false;
    }

    list_node_t *tmp = pnode;
    if (plist->_last == plist->_last && plist->_first == pnode)
    {
        LOG_INFO("delete node is list only node.");
        plist->_first = NULL;
        plist->_last = NULL;
    }
    else if (plist->_first == pnode)
    {
        LOG_INFO("delete node is first.");
        pnode->_next->_prev = pnode->_prev;
        pnode->_prev->_next = pnode->_next;

        plist->_first = tmp->_next;
    }
    else if (plist->_last == pnode)
    {
        LOG_INFO("delete node is last.");
        pnode->_next->_prev = pnode->_prev;
        pnode->_prev->_next = pnode->_next;

        plist->_last = tmp->_prev;
    }
    else if (plist->_lenght > 2)
    {// need check node is belong to list
        pnode->_next->_prev = pnode->_prev;
        pnode->_prev->_next = pnode->_next;
    }
    else
    {
        LOG_ERROR("delete fialed.");
        return false;
    }
    
    free(tmp);
    plist->_lenght--;
    return true;
}

/********************************** get ***************************************/
// 获取第一个节点数据
void *get_front_data(list_t *plist)
{
    return null;
}

// 获取最后一个节点的数据 
void *get_back_data(list_t *plist)
{
    return null;
}

// 获取第index节点数据 
void *get_index_data(list_t *plist, int index)
{
    return null;
}

// 获取当前节点数据
list_node_t *get_node_data(list_t *plist, list_node_t *node)
{
    return null;
}

// 获取头节点
list_node_t *get_front_node(list_t *plist)
{
    return null;
}

// 获取尾节点
list_node_t *get_back_node(list_t *plist)
{
    return null;
}

// 获取前驱节点
list_node_t *get_prev_node(list_t *plist, list_node_t *pnode)
{
    return null;
}

// 获取后继节点
list_node_t *get_next_node(list_t *plist, list_node_t *pnode)
{
    return null;
}

/********************************* sort ***************************************/ 
void sort_insert(list_t *plist, compare_func_t fcompare)
{
    LOG_DEBUG("start list sort insert.");
    if (fcompare == null)
    {
        LOG_WARN("param compare function is null, sort failed.");
        return;
    }

    if (plist == NULL)
    {
        LOG_WARN("list is null. sort failed.");
        return;
    }

    if (plist->_lenght < 1)
    {
        return;
    }

    if (plist->_first == null || plist->_first->_data == null 
        || plist->_last == null || plist->_last->_data == null)
    {
        LOG_WARN("list hava null node or data, sort failed.");
        return;
    }

    list_node_t *node = plist->_first->_next;
    compare_func = fcompare;
    int i = 1;
    for (; i < plist->_lenght; i++)
    {
        list_node_t *node_dup = node;
        node = node->_next;

        list_node_t *prev = node_dup->_prev;
        while(prev != plist->_last)
        {
            if (compare_func(prev->_data, node_dup->_data) <= 0)
            {
                if (prev == node_dup->_prev)
                {
                    break;
                }

                node_dup->_prev->_next = node_dup->_next;
                node_dup->_prev->_next->_prev = node_dup->_prev;

                node_dup->_next = prev->_next;
                node_dup->_next->_prev = node_dup;

                node_dup->_prev = prev;
                node_dup->_prev->_next = node_dup;
                break;
            }
            else if (prev == plist->_first)
            {
                // insert_front_node(plist, node_dup);
                node_dup->_prev->_next = node_dup->_next;
                node_dup->_next->_prev = node_dup->_prev;

                node_dup->_next = prev;
                node_dup->_prev = prev->_prev;

                node_dup->_next->_prev = node_dup;
                node_dup->_prev->_next = node_dup;

                plist->_first = node_dup;
                break;
            }

            prev = prev->_prev;
        }
    }
}