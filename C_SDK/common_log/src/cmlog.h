#ifndef _LIB_COMMON_LOG_H
#define _LIB_COMMON_LOG_H

#include <stdbool.h>

/**
 * 打印日志级别  （输出选定级别及以上的日志）
 * DEBUG < INFO < WARN <　ERROR
 * example:
 *      level = INFO
 *      输出  INFO WARN ERROR 级别的日志
 */
typedef enum _log_level_type{LOG_ON = 0, LOG_DEBUG, LOG_INFO, LOG_WARN, LOG_ERROR, LOG_OFF} level_t;

// 日期(yyyy:mm:dd) 时间(HH:MM:SS) 模块 日志级别 代码位置(file:func:line) logmsg
#define LOG_FORMAT                  "[%04d-%02d-%02d %s %s %s %s:%s:%05d] # %s\n"
#define LOG_FORMAT_SIZE             2048
#define LOG_COMMON_MODULE           "log-common"
#define null                        NULL

/**
 * 日志模块的log接口
 */ 
#define log_debug(format, args...)  _log_debug(__TIME__, __FILE__, __func__, __LINE__, format, ##args)
#define log_info(format, args...)   _log_info(__TIME__, __FILE__, __func__, __LINE__, format, ##args)
#define log_warn(format, args...)   _log_warn(__TIME__, __FILE__, __func__, __LINE__, format, ##args)
#define log_error(format, args...)  _log_error(__TIME__, __FILE__, __func__, __LINE__, format, ##args)
void _log_debug(const char *time, const char *file, const char *func, int line, const char *format, ...);
void _log_info(const char *time, const char *file, const char *func, int line, const char *format, ...);
void _log_warn(const char *time, const char *file, const char *func, int line, const char *format, ...);
void _log_error(const char *time, const char *file, const char *func, int line, const char *format, ...);

/**
 * 自定义模块的log接口
 * @param module_name       自定义moudule name， 用于控制指定模块的日志结构
 */
#define log_debug_module(module_name, format, args...)  _log_debug_module(__TIME__, __FILE__, __func__, __LINE__, module_name, format, ##args)
#define log_info_module(module_name, format, args...)   _log_info_module(__TIME__, __FILE__, __func__, __LINE__, module_name, format, ##args)
#define log_warn_module(module_name, format, args...)   _log_warn_module(__TIME__, __FILE__, __func__, __LINE__, module_name, format, ##args)
#define log_error_module(module_name, format, args...)  _log_error_module(__TIME__, __FILE__, __func__, __LINE__, module_name, format, ##args)
void _log_debug_module(const char *time, const char *file, const char *func, int line, const char *module_name, const char *format, ...);
void _log_info_module(const char *time, const char *file, const char *func, int line, const char *module_name, const char *format, ...);
void _log_warn_module(const char *time, const char *file, const char *func, int line, const char *module_name, const char *format, ...);
void _log_error_module(const char *time, const char *file, const char *func, int line, const char *module_name, const char *format, ...);

/**
 * 日志系统控制方法
 */
int log_start();
int log_restart();
int log_stop();
int log_status();

/**
 * 日志配置属性 
 */
/* 模块日志是否开启 */
bool is_enable_module(const char *module_name);
/* 模块日志级别 */
level_t log_level_module(const char *module_name);
/* 获取配置文件中属性值 */
char *attribute_value(const char *key);
/* 获取配置文件路径 */
char *get_config_path(void);

#endif
