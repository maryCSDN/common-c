#ifndef _BILATE_LINKED_LIST_H
#define _BILATE_LINKED_LIST_H

#include "_cmlistwrap.h"

/* create */
list_t *create_list(void);
list_node_t *create_empty_node(void);
list_node_t *create_node(data_t *pdata);

/* insert */
bool insert_front_node(list_t *plist, list_node_t *pnode);
bool insert_front(list_t *plist, data_t *pdata);
bool insert_index_front(list_t *plist, int index, data_t *pdata); 
bool insert_index_back(list_t *plist, int index, data_t *pdata);

/* print */
void print_list(list_t *plist, printf_t print_func);

#endif

