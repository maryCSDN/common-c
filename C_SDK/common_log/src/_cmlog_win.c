/* windows system */
#ifdef _WIN32

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <windows.h>
#include <fcntl.h>
#include <time.h>

#include "_cmlogwrap.h"

/* log color */
#define COLOR_DEFAULT               SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07)   /* 正常 */
#define COLOR_INFO                  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x02)   /* 绿色 */
#define COLOR_WARN                  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x06)   /* 黄色 */
#define COLOR_ERROR                 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x04)   /* 红色 */
/* current user home directory */
#define USER_HOME_WIN               "USERPROFILE"


static const char *g_log_level[LOG_OFF + 1] = {"ON", "DEBUG", "INFO", "WARN", "ERROR", "OFF"};

/**
 * 日志格式
 *      日期(yyyy:mm:dd) 时间(HH:MM:SS) 模块 日志级别、代码位置、日志内容、错误码
 *      (yyyy-mm-dd) HH:MM:SS LEVEL FILE:FUNC:LINE MSG ECODE
 */
static void _clog(const char  *module_name, const char *_time, level_t level, const char *_file, const char *_func, int _line, const char *format, va_list args);
static void _cvlog(int yyyy, int mm, int dd, const char *time, const char *module_name, level_t level, const char *file, const char *func, int line, const char *format, va_list args);

/**
 * 日志模块的log接口
 */ 
void _log_debug(const char *time, const char *file, const char *func, int line, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    _clog(LOG_COMMON_MODULE, time, LOG_DEBUG, file, func, line, format, args);
    va_end(args);
}

void _log_info(const char *time, const char *file, const char *func, int line, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    COLOR_INFO;
    _clog(LOG_COMMON_MODULE, time, LOG_INFO, file, func, line, format, args);
    COLOR_DEFAULT;
    va_end(args);
}

void _log_warn(const char *time, const char *file, const char *func, int line, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    COLOR_WARN;
    _clog(LOG_COMMON_MODULE, time, LOG_WARN, file, func, line, format, args);
    COLOR_DEFAULT;
    va_end(args);
}

void _log_error(const char *time, const char *file, const char *func, int line, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    COLOR_ERROR;
    _clog(LOG_COMMON_MODULE, time, LOG_ERROR, file, func, line, format, args);
    COLOR_DEFAULT;
    va_end(args);
}


static void _clog(const char  *module_name, const char *_time, level_t level, const char *_file, const char *_func, int _line, const char *format, va_list args)
{
    if (!is_enable_module(module_name))
    {
        /* 当前模块日志已关闭 */
        return;
    }

    if (level < log_level_module(module_name))
    {
        /* 当前模块日志级别高于level， 不打印此级别日志 */
        return;
    }

    time_t _date;
    _date = time(&_date);
    struct tm *date = gmtime(&_date);
    
    _cvlog(date->tm_year + 1900, date->tm_mon + 1, date->tm_mday, _time, module_name, level, _file, _func, _line, format, args);
}

static void _cvlog(int yyyy, int mm, int dd, const char *time, const char *module_name, level_t level, const char *file, const char *func, int line, const char *format, va_list args)
{
    char _format[LOG_FORMAT_SIZE] = {0};
    sprintf(_format, LOG_FORMAT, yyyy, mm, dd, time, module_name, g_log_level[level], file, func, line, format);
    vprintf(_format, args);
}


/* 日志系统控制方法 */

int log_start()
{

    char conf_path[LOG_DEFAULT_PATH_SIZE] = {0};
    if (get_config_path(conf_path) == null)
    {
        log_error("Cmlog startup failed");
        return -1;
    }

    FILE *fp = fopen(conf_path, "r+");
    if (fp == null)
    {
        log_error("open cmlog configuration file failed, path:[%s]", conf_path);
        return -1;
    }
    
    char line[LOG_CONF_LINE_SIZE] = {0};
    char key[LOG_CONF_KEY_SIZE] = {0};
    char value[LOG_CONF_VALUE_SIZE] = {0};
    while (fgets(line, LOG_CONF_LINE_SIZE, fp) != null)
    {
        memset(key, 0, LOG_CONF_KEY_SIZE);
        memset(value, 0, LOG_CONF_VALUE_SIZE);

        sscanf(line, "%s = %s", key, value);
        log_info("key:%s | value:%s", key, value);

        memset(line, 0, LOG_CONF_LINE_SIZE);
    }
    
    fclose(fp);
    return 0;
}

int log_restart()
{
    return 0;
}
int log_stop()
{
    return 0;
}
int log_status()
{
    return 0;
}

/* 日志属性 */ 
char *get_config_path(char *conf_path)
{
    if (conf_path == null)
    {
        log_error("The parameter to get the configuration file path cannot be null (this parameter is the user stores processing results)");
        return null;
    }

    char home_path[LOG_DEFAULT_PATH_SIZE] = {0};
    unsigned int path_size = GetEnvironmentVariable(USER_HOME_WIN, home_path, LOG_DEFAULT_PATH_SIZE);
    if (path_size == 0 || path_size > LOG_DEFAULT_PATH_SIZE)
    {
        // 当前用户家目录获取失败
        log_error("Configuration file path is too long [%d]", GetLastError());
        return null;
    }
    
    sprintf(home_path, "%s\\%s\\%s", home_path, LOG_CONF_SUB_DIR, LOG_CONF_NAME);
    int fd = open(home_path, O_RDONLY);
    if (fd < 0)
    {
        log_error("Failed to open configuration file, path:[%s]", home_path);
        return null;
    }
    close(fd);
    
    strcpy(conf_path, home_path);
    return conf_path;
}

char *get_attr_string(const char *key, bool config)
{
    if (key == null || strcmp(key, LOG_EMPTY_STRING) == 0)
    {
        log_warn("The keyword argument passed in is empty");
        return null;
    }

    if (config)
    {
        /* 从配置文件读取属性值 */
    }

    return null;
}

int get_attr_int(const char *key, bool config)
{
    return 0;
}

bool set_attr_string(const char *key, const char *value)
{
    return true;
}

bool set_attr_int(const char *key, int value)
{
    return true;
}

bool is_enable_module(const char *module_name)
{
    return true;
}

level_t log_level_module(const char *module_name)
{
    return LOG_ON;
}

#endif  