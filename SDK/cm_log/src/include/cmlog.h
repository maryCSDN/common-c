#ifndef _LIB_CMLOG_H
#define _LIB_CMLOG_H

#ifdef _cplusplus
extern "C"
{
#endif

#include "cmlogwrap.h"

/* debug日志的宏方法*/
#define log_debug(format, args...)  _log_debug(__FILE__, __func__, __LINE__, format, ##args)
/* info日志的宏方法*/
#define log_info(format, args...)   _log_info(__FILE__, __func__, __LINE__, format, ##args)
/* warn日志的宏方法*/
#define log_warn(format, args...)   _log_warn(__FILE__, __func__, __LINE__, format, ##args)
/* error日志的宏方法*/
#define log_error(format, args...)  _log_error(__FILE__, __func__, __LINE__, format, ##args)
/* 项目使用cmlog，必须调用此接口进行初始化 */
extern int log_init(const char *module);
/* 设置本地日志打印级别 */
extern void log_set_level(level_t level);
/* 记录debug级别日志，可以自己填充前三个参数，也可以调用对应的宏方法自动填充 */
extern void _log_debug(const char *file, const char *func, int line, const char *format, ...);
/* 记录info级别日志，可以自己填充前三个参数，也可以调用对应的宏方法自动填充 */
extern void _log_info(const char *file, const char *func, int line, const char *format, ...);
/* 记录warn级别日志，可以自己填充前三个参数，也可以调用对应的宏方法自动填充 */
extern void _log_warn(const char *file, const char *func, int line, const char *format, ...);
/* 记录error级别日志，可以自己填充前三个参数，也可以调用对应的宏方法自动填充 */
extern void _log_error(const char *file, const char *func, int line, const char *format, ...);

#ifdef _cplusplus
}
#endif

#endif