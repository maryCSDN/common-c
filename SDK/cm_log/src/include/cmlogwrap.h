#ifndef _LIB_CMLOG_WRAP_H
#define _LIB_CMLOG_WRAP_H

#ifdef _cplusplus
extern "C"
{
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