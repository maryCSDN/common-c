#ifndef _LIB_CMLOG_WRAP_H
#define _LIB_CMLOG_WRAP_H

#ifdef _cplusplus
extern "C"
{
#endif

/*** 公共头文件 ***/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>


/*** common default value ***/
/* 服务器IP地址 */
#define     LOG_SERV_IP                 "127.0.0.1"
/* 服务器端口 */
#define     LOG_SERV_PORT               44444
/* 模块名最大长度 */
#define     LOG_MODULE_LIMIT            64
#define     LOG_MODULE_SYSVALUE         "syslog"
#define     LOG_CONF_HOME_WIN           "USERPROFILE"   /* windows configuration home */
#define     LOG_CONF_HOME_UNIX          "/etc"          /* linux configuration home*/
#define     LOG_CONF_SUB_DIR            "cmlog"
#define     LOG_CONF_NAME               "cmlog.conf"
#define     LOG_DEFAULT_PATH_SIZE       128
#define     null                        NULL

/** 模块 日期(yyyy:mm:dd) 时间(HH:MM:SS)  代码位置、日志级别、日志内容 */
/** <module> [yyyy-mm-dd HH:MM:SS FILE:FUNCTION:LINE] {LOG_LEVEL} # */
#define     DEFAULT_LOG_FORMAT          "<%s> [%04d-%02d-%02d %02d:%02d:%02d %s:%s:%05d] <%5s>$ %s\n"
/** 一条格式化日志的最大长度 */
#define     LOG_FORMAT_SIZE             256
/** 枚举日志级别 */
typedef enum _log_level_type{LOG_ON = 0, LOG_DEBUG, LOG_INFO, LOG_WARN, LOG_ERROR, LOG_OFF} level_t;

#ifdef _cplusplus
}
#endif

#endif