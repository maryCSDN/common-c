#ifndef _LIB_CMLOG_WRAP_H
#define _LIB_CMLOG_WRAP_H

#ifdef _cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <stdbool.h>
#include <stdio.h>
    #ifdef _WIN32
    #include <winsock2.h>
    #include <windows.h>
    #endif

/* 服务器地址 */
#define     LOG_SERV_IP                 "127.0.0.1"
#define     LOG_SERV_PORT               44444
/* common define */
#define     LOG_MODULE_SIZE             64
#define     LOG_MODULE_SYSVALUE         "syslog"
#define     LOG_CONF_HOME_WIN           "USERPROFILE"   /* windows configuration home */
#define     LOG_CONF_HOME_UNIX          "/etc"          /* linux configuration home*/
#define     LOG_CONF_SUB_DIR            "cmlog"
#define     LOG_CONF_NAME               "cmlog.conf"
#define     LOG_DEFAULT_PATH_SIZE       128
#define     null                        NULL
/* 日期(yyyy:mm:dd) 时间(HH:MM:SS) 模块 日志级别、代码位置、日志内容、错误码 */
/* <module> [yyyy-mm-dd HH:MM:SS FILE:FUNCTION:LINE] {LOG_LEVEL} # */
#define     _LOG_FORMAT                 "<%s> [%04d-%02d-%02d %02d:%02d:%02d %s:%s:%05d] <%5s>$ %s\n"
//#define   LOG_FORMAT                  "[%04d-%02d-%02d %02d:%02d:%02d %s %5s %s:%s:%05d] # %s\n"
#define     LOG_FORMAT_SIZE             2048

typedef enum _log_level_type{LOG_ON = 0, LOG_DEBUG, LOG_INFO, LOG_WARN, LOG_ERROR, LOG_OFF} level_t;

/* log客户端 API */ 
#define log_debug(format, args...)  _log_debug(__FILE__, __func__, __LINE__, format, ##args)
#define log_info(format, args...)   _log_info(__FILE__, __func__, __LINE__, format, ##args)
#define log_warn(format, args...)   _log_warn(__FILE__, __func__, __LINE__, format, ##args)
#define log_error(format, args...)  _log_error(__FILE__, __func__, __LINE__, format, ##args)
extern void _log_debug(const char *file, const char *func, int line, const char *format, ...);
extern void _log_info(const char *file, const char *func, int line, const char *format, ...);
extern void _log_warn(const char *file, const char *func, int line, const char *format, ...);
extern void _log_error(const char *file, const char *func, int line, const char *format, ...);
extern int log_init(const char *module);
extern void log_set_level(level_t level);

/* log服务器 API */
extern int log_server_start();
extern int log_server_restart();
extern int log_server_stop();
extern int log_server_status();

#ifdef _cplusplus
}
#endif

#endif
