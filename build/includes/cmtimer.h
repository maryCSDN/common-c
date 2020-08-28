#ifndef __LIB_CMTIMER_H__
#define __LIB_CMTIMER_H__

#ifdef _cplusplus
extern "C"
{
#endif

#include "cmtimerwrap.h"

/* 启动定时器 */
extern bool start_timer();
/* 关闭计时器 */
extern bool stop_timer();
/* 导入定时任务 */
extern bool push_time_task(time_task_t task);
/* 导出定时任务 */
extern bool pop_time_task(time_task_t task);

#ifdef _cplusplus
}
#endif

#endif