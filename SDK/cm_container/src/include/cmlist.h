#ifndef _BILATE_LINKED_LIST_H
#define _BILATE_LINKED_LIST_H

#include "_cmlistwrap.h"

/* create */
list_t *create_list(void);

/* destory */
void clear_list(list_t *plist, LIST_CALLBACK delete_f delete_cb);
void destory_list(list_t **pplist, LIST_CALLBACK delete_f delete_cb);

/* insert */
bool insert_head(list_t *plist, data_t* const pdata);
bool insert_tail(list_t *plist, data_t* const pdata);
bool insert_front(list_t *plist, const int index, data_t* const pdata); 
bool insert_back(list_t *plist, const int index, data_t* const pdata);

/* delete */
bool delete_head(list_t *plist, LIST_CALLBACK delete_f delete_cb);
bool delete_tail(list_t *plist, LIST_CALLBACK delete_f delete_cb);
bool delete_node_by_data(list_t *plist, const data_t *pdata, LIST_CALLBACK delete_f delete_cb);
bool delete_node_by_index(list_t *plist, const unsigned int index, LIST_CALLBACK delete_f delete_cb);

/* print */
void print_list(list_t *plist, LIST_CALLBACK print_f print_cb);

/* check */
bool is_empty_list(list_t *plist);

#endif

