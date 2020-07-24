#ifndef _LIB_CMLOG_H
#define _LIB_CMLOG_H

#include "_cmlogwrap.h"

/* log 公有API */
#define log_debug(format, args...)  _log_debug(__FILE__, __func__, __LINE__, format, ##args)
#define log_info(format, args...)   _log_info(__FILE__, __func__, __LINE__, format, ##args)
#define log_warn(format, args...)   _log_warn(__FILE__, __func__, __LINE__, format, ##args)
#define log_error(format, args...)  _log_error(__FILE__, __func__, __LINE__, format, ##args)
void _log_debug(const char *file, const char *func, int line, const char *format, ...);
void _log_info(const char *file, const char *func, int line, const char *format, ...);
void _log_warn(const char *file, const char *func, int line, const char *format, ...);
void _log_error(const char *file, const char *func, int line, const char *format, ...);
int log_init(const char *module);
void log_set_level(level_t level);

#endif