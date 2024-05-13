/*
 * @Author: wzh
 * @Date: 2024-05-06 10:30:46
 * @LastEditors: wzh
 * @LastEditTime: 2024-05-06 16:39:41
 * @Description:
 *
 * Copyright (c) 2024 by wzh, All Rights Reserved.
 */
#include "soft_timer.h"

void et_soft_timer_init(et_soft_timer_t *timer, void *user)
{
    timer->interval = 0;
    timer->is_start = false;
    timer->callback = NULL;
    timer->start_time = 0;
    timer->user = user;
}

bool et_soft_timer_is_timeout(et_soft_timer_t *timer)
{
    if (timer->is_start == false)
    {
        return false;
    }
    else
    {
        if (et_get_tick_ms() - timer->start_time > timer->interval)
        {
            return true;
        }
    }
    return false;
}

void et_soft_timer_start(et_soft_timer_t *timer, uint32_t interval,
    et_soft_timer_callback_t callback)
{
    timer->interval = interval;
    timer->start_time = et_get_tick_ms();
    timer->is_start = true;
    timer->callback = callback;
}

void et_soft_timer_stop(et_soft_timer_t *timer)
{
    timer->is_start = false;
}

/**
 *
 *  @brief: Process timer callback, put this function in while loop
 *
 *  @param: timer timer array.
 *  @param: time_cnt timer number
 *
 *  @return: void
 */
void et_process_timer_callbacks(et_soft_timer_t *timers, uint8_t time_cnt)
{
    for (int i = 0; i < time_cnt; i++)
    {
        if (timers[i].callback != NULL)
        {
            if (et_soft_timer_is_timeout(&timers[i]))
            {
                if(timers[i].callback != NULL)
                    timers[i].callback(&timers[i]);
                // reset the start time
                timers[i].start_time = et_get_tick_ms();
            }
        }
    }
}

