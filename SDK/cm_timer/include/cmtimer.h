#ifndef __LIB_CMTIMER_H__
#define __LIB_CMTIMER_H__

bool start_timer();

bool stop_timer();

bool push_time_task(time_task_t *task);

bool pop_time_task(time_task_t task);

#endif