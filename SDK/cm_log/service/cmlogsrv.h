#ifndef _LIB_CMLOG_WRAP_H
#define _LIB_CMLOG_WRAP_H

#ifdef _cplusplus
extern "C"
{
#endif

/* log服务器 API */
extern int log_server_start();
extern int log_server_restart();
extern int log_server_stop();
extern int log_server_status();

#ifdef _cplusplus
}
#endif

#endif
