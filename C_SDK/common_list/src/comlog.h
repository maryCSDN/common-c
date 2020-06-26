#ifndef _COMMON_LOG_H
#define _COMMON_LOG_H

// 文字颜色
#define COLOR_RED "\033[31m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_GREEN "\033[32m"
#define COLOR_END "\033[0m"

// 显示时间
#define DATE_FORMAT_SIZE    1024

#define LOG_PRINT
// 日志封装
#ifdef LOG_PRINT

#define LOG_DEBUG(formats, args...) \
    printf("[%s:%d] <debug> # " formats COLOR_END "\n", __FILE__, __LINE__, ##args)
#define LOG_INFO(formats, args...) \
    printf(COLOR_GREEN "[%s:%d] <info> # " formats COLOR_END "\n", __FILE__, __LINE__, ##args)
#define LOG_WARN(formats, args...) \
    printf(COLOR_YELLOW "[%s:%d] <warn> # " formats COLOR_END "\n", __FILE__, __LINE__, ##args)
#define LOG_ERROR(formats, args...) \
    printf(COLOR_RED "[%s:%d] <ERROR> # " formats COLOR_END "\n", __FILE__, __LINE__, ##args)

#else

#define LOG_DEBUG(formats, args...) \
    // printf("[%s:%d] <debug> #"formats"\n", __FILE__, __LINE__, ##args)
#define LOG_INFO(formats, args...) \
    // printf("[%s:%d] <info> #"formats"\n", __FILE__, __LINE__, ##args)
#define LOG_WARN(formats, args...) \
    // printf("[%s:%d] <warn> #"formats"\n", __FILE__, __LINE__, ##args)
#define LOG_ERROR(formats, args...) \
    // printf("[%s:%d] <info> #"formats"\n", __FILE__, __LINE__, ##args)
#endif

#endif
