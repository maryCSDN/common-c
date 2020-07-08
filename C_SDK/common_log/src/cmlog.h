/* log API */
#ifndef _LIB_COMMON_LOG_H
#define _LIB_COMMON_LOG_H

#include "_cmlogwrap.h"

/* log 公有API */
#define log_debug(format, args...)  _log_debug(__TIME__, __FILE__, __func__, __LINE__, format, ##args)
#define log_info(format, args...)   _log_info(__TIME__, __FILE__, __func__, __LINE__, format, ##args)
#define log_warn(format, args...)   _log_warn(__TIME__, __FILE__, __func__, __LINE__, format, ##args)
#define log_error(format, args...)  _log_error(__TIME__, __FILE__, __func__, __LINE__, format, ##args)
void _log_debug(const char *time, const char *file, const char *func, int line, const char *format, ...);
void _log_info(const char *time, const char *file, const char *func, int line, const char *format, ...);
void _log_warn(const char *time, const char *file, const char *func, int line, const char *format, ...);
void _log_error(const char *time, const char *file, const char *func, int line, const char *format, ...);

/* log 系统调用API */
int log_server_start();
int log_server_restart();
int log_server_stop();
int log_server_status();

#endif