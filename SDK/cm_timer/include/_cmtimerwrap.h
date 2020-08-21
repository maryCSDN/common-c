#ifndef __LIB_CMTIMER_WRAP_H__
#define __LIB_CMTIMER_WRAP_H__

#include "_cmtimerwrap.h"

typedef struct _time_task{

} time_task_t;


extern bool start_timer();

extern bool stop_timer();

extern bool push_time_task(time_task_t *task);

extern bool pop_time_task(time_task_t task);

#endif