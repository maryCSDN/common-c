#ifndef _LIB_CMLOG_WRAP_H
#define _LIB_CMLOG_WRAP_H

#ifdef _cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdio.h>

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
#define     LOG_FORMAT                  "[%04d-%02d-%02d %s %s %5s %s:%s:%05d] # %s\n"
#define     LOG_FORMAT_SIZE             2048

/* log empty string */
#define     LOG_EMPTY_STRING            ""
/* log key value size */
#define     LOG_CONF_KEY_SIZE           64
#define     LOG_CONF_VALUE_SIZE         128
#define     LOG_CONF_LINE_SIZE          512
/* cmlog key */
#define     KEY_CMLOG_LEVEL             "log-cmlog-level"
#define     KEY_CMLOG_ROOT_DIR          "log-root-dir"
#define     KEY_CMLOG_PRINT             "log-print"
#define     KEY_CMLOG_VALId_TIME        "log-valid-time"


typedef enum _log_level_type{LOG_ON = 0, LOG_DEBUG, LOG_INFO, LOG_WARN, LOG_ERROR, LOG_OFF} level_t;
typedef struct _config_info_type{
    unsigned int _valid_time;                   /* 日志保存时间(天)  key = valid-time, value = [0, n] */
    char _level[16];                            /* 日志级别  key = "log-"##"module_name"##"-level", value = ON/DEBUG/ERROR/INFO/WARN/ERROR/OFF (OFF-关闭模块log)*/
    char _print_way[16];                        /* 打印方式 key = "log-"##print， value = unconsole/stdin/stdout/stderr  默认控制台 */
    char _root_dir[LOG_DEFAULT_PATH_SIZE];      /* 日志文件保存的根目录 key = "log-root-dir", value = ${path} */
} _log_conf_t;

/* log客户端 API */ 
#define log_debug(format, args...)  _log_debug(__TIME__, __FILE__, __func__, __LINE__, format, ##args)
#define log_info(format, args...)   _log_info(__TIME__, __FILE__, __func__, __LINE__, format, ##args)
#define log_warn(format, args...)   _log_warn(__TIME__, __FILE__, __func__, __LINE__, format, ##args)
#define log_error(format, args...)  _log_error(__TIME__, __FILE__, __func__, __LINE__, format, ##args)
extern void _log_debug(const char *time, const char *file, const char *func, int line, const char *format, ...);
extern void _log_info(const char *time, const char *file, const char *func, int line, const char *format, ...);
extern void _log_warn(const char *time, const char *file, const char *func, int line, const char *format, ...);
extern void _log_error(const char *time, const char *file, const char *func, int line, const char *format, ...);
extern int log_init(const char *module);
extern void log_set_level(level_t level);

/* log服务器 API */
extern int log_server_start();
extern int log_server_restart();
extern int log_server_stop();
extern int log_server_status();
extern char *log_server_conf_path(char *dest_buf);

#ifdef _cplusplus
}
#endif

#endif
