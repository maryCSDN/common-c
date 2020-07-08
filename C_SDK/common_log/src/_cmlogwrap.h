#ifndef _LIB_COMMON_LOG_H
#define _LIB_COMMON_LOG_H

#ifdef _cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdio.h>

/* 服务器地址 */
#define     LOG_SERV_IP                 "127.0.0.1"
#define     LOG_SERV_PORT               "44444"

// 日期(yyyy:mm:dd) 时间(HH:MM:SS) 模块 日志级别 代码位置(file:func:line) logmsg
#define     LOG_FORMAT                  "[%04d-%02d-%02d %s %s %s %s:%s:%05d] # %s\n"
#define     LOG_FORMAT_SIZE             2048
#define     LOG_COMMON_MODULE           "cmlog"
#define     null                        NULL
/* log configuration file sub path */
#define     LOG_CONF_SUB_DIR            "cmlog"
#define     LOG_CONF_NAME               "cmlog.conf"
#define     LOG_DEFAULT_PATH_SIZE       128
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

/**
 * 打印日志级别  （输出选定级别及以上的日志）
 * DEBUG < INFO < WARN <　ERROR
 * example:
 *      level = INFO
 *      输出  INFO WARN ERROR 级别的日志
 */
typedef enum _log_level_type{LOG_ON = 0, LOG_DEBUG, LOG_INFO, LOG_WARN, LOG_ERROR, LOG_OFF} level_t;

// typedef struct _config_attribute_info_type{
//     char _module_name[16];          /* 模块名 "log-"##module_name example: log-cmlog */
//     char _level[16];                /* 模块日志级别 key = 模块名##"-level", value = ON/DEBUG/INFO/WARN/ERROR/OFF  默认INFO */
// }_log_attr_t;

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

/* log服务器 API */
extern int log_server_start();
extern int log_server_restart();
extern int log_server_stop();
extern int log_server_status();
extern char *log_server_conf_path(char *dest_buf);


/* 日志配置属性  */

/**
 * 获取配置文件默认路径 (系统默认)
 * @param conf_path             用于存储配置文件路径
 * @return 成功-返回conf_path
 */
char *get_config_path(char *conf_path);

/**
 * 获取log属性值 
 * @param key       关键字
 * @param config    true-从配置文件中获取获取value，false-从内存中获取value
 * @return 成功-返回0或非空字符串
 */
char *get_attr_string(const char *key, bool config);
int get_attr_int(const char *key, bool config);

/**
 * 修改内存中log配置 （临时生效，重启后失效）
 * @param key       关键字
 * @param value     新值
 * @return 成功-返回0
 */ 
bool set_attr_string(const char *key, const char *value);
bool set_attr_int(const char *key, int value);


/* 模块日志是否开启 */
bool is_enable_module(const char *module_name);
/* 模块日志级别 */
level_t log_level_module(const char *module_name);

#ifdef _cplusplus
}
#endif

#endif
