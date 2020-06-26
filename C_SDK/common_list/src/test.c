#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// #define LOG_PRINT   // 打印日志
#include "comlist.h"
#include "comlog.h"
#include "test.h"

#define null NULL

// 时间
static time_t g_time;
static char *_date();

time_interval_t *create_time_inter(const char *_begin_time, const char *_endtime);
void ptintf_data(void *data);
int compare( void *left, void *right);
void delete_data(void *data);

int main()
{
    LOG_INFO("(%s) start main.", _date());
    list_t *plist = create_list();

    time_interval_t *tmp = null;

    tmp = create_time_inter("00:01:00", "03:00:00"); 
    insert_front(plist, tmp);

    tmp = create_time_inter("02:00:00", "05:00:00"); 
    insert_front(plist, tmp);

    tmp = create_time_inter("07:00:00", "09:00:00"); 
    insert_front(plist, tmp);

    tmp = create_time_inter("17:00:00", "23:00:00"); 
    insert_front(plist, tmp);

    tmp = create_time_inter("18:00:00", "23:00:00"); 
    insert_front(plist, tmp);

    tmp = create_time_inter("08:00:00", "26:00:00"); 
    insert_front(plist, tmp);

    tmp = create_time_inter("02:00:00", "05:00:00"); 
    insert_front(plist, tmp);

    sort_insert(plist, compare);
    print_list(plist, ptintf_data);
    destory_list(plist, delete_data);
    return 0;
}

void delete_data(void *data)
{
    time_interval_t *_data = (time_interval_t *) data;
    free(_data->_begin_time);
    free(_data->_end_time);
}

int compare(void *left, void *right)
{
    if (left == null || right == null)
    {
        LOG_ERROR("compare function params is null.");
        return 0;
    }

    time_interval_t *left_date = (time_interval_t *) left;
    time_interval_t *right_data = (time_interval_t *) right;

    LOG_DEBUG("call commpare. left:(%s) ^ right:(%s).", left_date->_begin_time, right_data->_begin_time);

    size_t left_len = strlen(left_date->_begin_time);
    size_t right_len = strlen(right_data->_begin_time);
    size_t len = (left_len > right_len) ? left_len : right_len;

    return strncmp(right_data->_begin_time, left_date->_begin_time,  len);
}

time_interval_t *create_time_inter(const char *_begin_time, const char *_end_time)
{
    LOG_INFO("create time interval node [%s-%s]", _begin_time, _end_time);
    time_interval_t *ret = (time_interval_t *) malloc(sizeof(time_interval_t));
    if (ret == null)
    {
        LOG_ERROR("create time interval node failed. [%s-%s]", _begin_time, _end_time);
        return null;
    }
    size_t _begin_len = strlen(_begin_time);
    char *_begin_t = (char *) malloc(_begin_len + 1);
    if (_begin_t == null)
    {
        LOG_ERROR("create time interval begin time node failed. [%s]", _begin_time);
        return null;
    }

    size_t _end_len = strlen(_end_time);
    char *_end_t = (char *) malloc(_end_len + 1);
    if (_end_t == null)
    {
        LOG_ERROR("create time interval end time node failed. [%s]", _end_time);
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

void ptintf_data(void *data)
{
    time_interval_t *tm = (time_interval_t *) data;
    LOG_INFO("[%s-%s]", tm->_begin_time, tm->_end_time);
}

char *_date()
{
    g_time = time(NULL);
	// struct tm *tm_time;
	//tm_time = gmtime(&gt_time);

    //格式化输出
	// strftime(_date_cache, DATE_FORMAT_SIZE, "%F-%T", tm_time);
    char *_dt = ctime(&g_time);
    size_t len = strlen(_dt);
    *(_dt + len - 1) = 0;
    return _dt;
}