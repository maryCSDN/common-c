#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <cmlog.h>
// #define LOG_PRINT   // 打印日志
#include <cmlist.h>

#define null NULL

/* 打印链表数据 */
void print_list_cb(data_t *pdata);
/* 打印链表地址 */
static void printp(list_t *list);

int main()
{
    /* 打印INFO及以上级别日志 */
    log_set_level(LOG_INFO);

    /* 创建空链表（带头结点） */
    list_t *list = create_list();

    /* 插入数据 */
    char *str = "test";
    char *value = "asdasd";
    insert_head(list, str);
    insert_head(list, str);
    insert_head(list, str);
    insert_head(list, str);
    insert_tail(list, value);

    // printp(list);
    print_list(list, print_list_cb);

    return 0;
}

void print_list_cb(data_t *pdata)
{
    printf("data:%s\n", (char *) pdata);
}

static void printp(list_t *list)
{
    printf("list:%p {_length:%d | _first:%p | _last:%p}\n", list, list->_lenght, list->_first, list->_last);
    
    list_node_t *node = list->_first;
    int i = 0;
    while (list->_lenght - i++ > 0)
    {
        printf("  node:%p {_pdata:%10s | _belong:%p | _next:%p | _prev:%p}\n", node, (char *)node->_pdata, node->_belong, node->_next, node->_prev);
        node = node->_next;
    }
}

#if 0
typedef struct _time_interval_type{
    char *_begin_time;
    char *_end_time;
}time_interval_t;

time_interval_t *create_time_inter(const char *_begin_time, const char *_endtime);
void ptintf_data(void *data);
int compare(void *left, void *right);
void delete_data(void *data);
void union_node(list_t *plist);

void union_node(list_t *plist)
{
    if (plist == null)
    {
        log_error("list is null");
        return;
    }

    list_node_t *node = plist->_first->_next;
    int i = 1;
    int len = plist->_lenght;
    for (; i < len; i++)
    {
        list_node_t *tmp = node;
        time_interval_t *pt = (time_interval_t *)(tmp->_prev->_data);
        time_interval_t *ct = (time_interval_t *)(tmp->_data);
        if (strcmp(pt->_end_time, ct->_begin_time) >= 0)
        {
            if (strcmp(ct->_end_time, pt->_end_time) > 0)
            {
                log_info("{ct end > pt end} | pt [%s-%s], ct[%s-%s].",
                         pt->_begin_time, pt->_end_time, ct->_begin_time, ct->_end_time);
                free(pt->_end_time);
                pt->_end_time = ct->_end_time;
                free(ct->_begin_time);
                free(ct);
            }
            else
            {
                log_info("{ct end <= pt end} | pt [%s-%s], ct[%s-%s].",
                         pt->_begin_time, pt->_end_time, ct->_begin_time, ct->_end_time);
                free(ct->_begin_time);
                free(ct->_end_time);
                free(ct);
            }

            tmp->_next->_prev = tmp->_prev;
            tmp->_prev->_next = tmp->_next;
            node = node->_next;
            free(tmp);
            plist->_lenght--;
            continue;
        }

        log_info("{ct begin > pt end} | pt [%s-%s], ct[%s-%s].",
                 pt->_begin_time, pt->_end_time, ct->_begin_time, ct->_end_time);
        node = node->_next;
    }
}



void delete_data(void *data)
{
    time_interval_t *_data = (time_interval_t *)data;
    free(_data->_begin_time);
    free(_data->_end_time);
}

int compare(void *left, void *right)
{
    if (left == null || right == null)
    {
        log_error("compare function params is null.");
        return 0;
    }

    time_interval_t *left_date = (time_interval_t *)left;
    time_interval_t *right_data = (time_interval_t *)right;

    log_debug("call commpare. left:(%s) - right:(%s).", left_date->_begin_time, right_data->_begin_time);

    size_t left_len = strlen(left_date->_begin_time);
    size_t right_len = strlen(right_data->_begin_time);
    size_t len = (left_len > right_len) ? left_len : right_len;

    return strncmp(left_date->_begin_time, right_data->_begin_time, len);
}

time_interval_t *create_time_inter(const char *_begin_time, const char *_end_time)
{
    log_info("create time interval node [%s-%s]", _begin_time, _end_time);
    time_interval_t *ret = (time_interval_t *)malloc(sizeof(time_interval_t));
    if (ret == null)
    {
        log_error("create time interval node failed. [%s-%s]", _begin_time, _end_time);
        return null;
    }
    size_t _begin_len = strlen(_begin_time);
    char *_begin_t = (char *)malloc(_begin_len + 1);
    if (_begin_t == null)
    {
        log_error("create time interval begin time node failed. [%s]", _begin_time);
        return null;
    }

    size_t _end_len = strlen(_end_time);
    char *_end_t = (char *)malloc(_end_len + 1);
    if (_end_t == null)
    {
        log_error("create time interval end time node failed. [%s]", _end_time);
        return null;
    }

    memset(_begin_t, 0, _begin_len + 1);
    memset(_end_t, 0, _end_len + 1);
    strncpy(_begin_t, _begin_time, _begin_len);
    strncpy(_end_t, _end_time, _end_len);
    ret->_begin_time = _begin_t;
    ret->_end_time = _end_t;

    return ret;
}
#endif
