/* windows system */
#ifdef _WIN32

#include <stdbool.h>
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

static const char *g_log_level[LOG_OFF + 1] = {"ON", "DEBUG", "INFO", "WARN", "ERROR", "OFF"};
static char g_module[LOG_MODULE_SIZE] = {0};
static level_t g_level = LOG_ON;
static bool g_init_flag = false;

static void _cvlog(const char *_time, level_t level, const char *_file, const char *_func, int _line, const char *format, va_list args);

void _log_debug(const char *time, const char *file, const char *func, int line, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    _cvlog(time, LOG_DEBUG, file, func, line, format, args);
    va_end(args);
}

void _log_info(const char *time, const char *file, const char *func, int line, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    COLOR_INFO;
    _cvlog(time, LOG_INFO, file, func, line, format, args);
    COLOR_DEFAULT;
    va_end(args);
}

void _log_warn(const char *time, const char *file, const char *func, int line, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    COLOR_WARN;
    _cvlog(time, LOG_WARN, file, func, line, format, args);
    COLOR_DEFAULT;
    va_end(args);
}

void _log_error(const char *time, const char *file, const char *func, int line, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    COLOR_ERROR;
    _cvlog(time, LOG_ERROR, file, func, line, format, args);
    COLOR_DEFAULT;
    va_end(args);
}


static void _cvlog(const char *_time, level_t level, const char *_file, const char *_func, int _line, const char *format, va_list args)
{
    time_t _date;
    _date = time(&_date);
    struct tm *date = gmtime(&_date);
    char _format[LOG_FORMAT_SIZE] = {0};
    if (!g_init_flag)
    {
        sprintf(_format, LOG_FORMAT, date->tm_year + 1900, date->tm_mon + 1, date->tm_mday, _time, 
            LOG_MODULE_SYSVALUE, g_log_level[level], _file, _func, _line, format);
    }
    else
    {
        sprintf(_format, LOG_FORMAT, date->tm_year + 1900, date->tm_mon + 1, date->tm_mday, _time, 
            g_module, g_log_level[level], _file, _func, _line, format);
    }
    
    vsprintf(_format, _format, args);
    printf("%s", _format);
}


int log_init(const char *module)
{
    if (module == null)
    {
        log_warn("log init failed, param module is null.");
        return -1;
    }

    if (strlen(g_module) > 0)
    {
        log_warn("log init failed, already initialized.");
        return -1;
    }

    if (strlen(module) > LOG_MODULE_SIZE - 1)
    {
        log_warn("log init failed, module len too long");
        return -1;
    }

    strcpy(g_module, module);
    g_init_flag = true;
    return 0;
}

void log_set_level(level_t level)
{
    if (level > LOG_OFF || level < LOG_ON)
    {
        log_warn("The log level you set is illegal");
    }
    else
    {
        g_level = level;
    }
}

#endif  