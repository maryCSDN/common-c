/* windows system */
#ifdef _WIN32
#ifdef _cplusplus
extern "C"
{
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <windows.h>
#include <time.h>

#include "cmlog.h"

/* log color */
#define COLOR_DEFAULT           SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07)   /* 正常 */
#define COLOR_INFO              SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x02)   /* 绿色 */
#define COLOR_WARN              SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x06)   /* 黄色 */
#define COLOR_ERROR             SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x04)   /* 红色 */
/* log configuration file sub path */
#define LOG_CONF_SUB_DIR        "cmlog"
#define LOG_CONF_NAME           "cmlog.conf"


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


/**
 * 自定义模块的log接口
 * @param module_name       自定义moudule name， 用于控制指定模块的日志结构
 */
void _log_debug_module(const char *time, const char *file, const char *func, int line, const char *module_name, const char *format, ...)
{
    if (module_name == null)
    {
        log_warn("The module name is not set.");
        return;
    }

    va_list args;
    va_start(args, format);
    _clog(module_name, time, LOG_DEBUG, file, func, line, format, args);
    va_end(args);
}

void _log_info_module(const char *time, const char *file, const char *func, int line, const char *module_name, const char *format, ...)
{
    if (module_name == null)
    {
        log_warn("The module name is not set.");
        return;
    }

    va_list args;
    va_start(args, format);
    COLOR_INFO;
    _clog(module_name, time, LOG_INFO, file, func, line, format, args);
    COLOR_DEFAULT;
    va_end(args);
}

void _log_warn_module(const char *time, const char *file, const char *func, int line, const char *module_name, const char *format, ...)
{
    if (module_name == null)
    {
        log_warn("The module name is not set.");
        return;
    }

    va_list args;
    va_start(args, format);
    COLOR_WARN;
    _clog(module_name, time, LOG_WARN, file, func, line, format, args);
    COLOR_DEFAULT;
    va_end(args);
}

void _log_error_module(const char *time, const char *file, const char *func, int line, const char *module_name, const char *format, ...)
{
    if (module_name == null)
    {
        log_warn("The module name is not set.");
        return;
    }

    va_list args;
    va_start(args, format);
    COLOR_ERROR;
    _clog(module_name, time, LOG_ERROR, file, func, line, format, args);
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


/**
 * 日志系统控制方法
 */
int log_start()
{
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

/**
 * 日志配置属性 
 */ 
bool is_enable_module(const char *module_name)
{
    return true;
}
level_t log_level_module(const char *module_name)
{
    return LOG_ON;
}
/* 获取配置文件中属性值 */
char *attribute_value(const char *key)
{
    return null;
}
/* 获取配置文件路径 */
char *get_config_path(void)
{
    const char *home_profile = "USERPROFILE";
    char home_path[1024] = {0};

    unsigned int path_size = GetEnvironmentVariable(home_profile, home_path, 1024);

    if (path_size == 0 || path_size > 1024)
    {
        // 配置文件路径家目录获取失败
        log_error("Configuration file path is too long. [%d]", GetLastError());
        return null;
    }
    
    sprintf(home_path, "%s\\%s\\%s", home_path, LOG_CONF_SUB_DIR, LOG_CONF_NAME);
    
    printf("#%s\n", home_path);

    return null;
}

#ifdef _cplusplus
}
#endif
#endif  