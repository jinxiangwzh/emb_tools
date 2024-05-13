/*
 * @Author: wzh
 * @Date: 2024-05-06 10:30:35
 * @LastEditors: wzh
 * @LastEditTime: 2024-05-07 13:14:29
 * @Description:
 *
 * Copyright (c) 2024 by wzh, All Rights Reserved.
 */

#ifndef __SOFT_TIMER_H__
#define __SOFT_TIMER_H__
#include "emb_tools_common.h"

struct et_soft_timer;
typedef void (*et_soft_timer_callback_t)(struct et_soft_timer *timer);

typedef struct et_soft_timer
{
    uint32_t start_time;
    uint32_t interval;
    bool  is_start;
    void *user;
    et_soft_timer_callback_t callback;
}et_soft_timer_t;

#ifdef __cplusplus
extern "C" {
#endif
    void et_soft_timer_init(et_soft_timer_t *timer, void *user);
    void et_soft_timer_start(et_soft_timer_t *timer,
        uint32_t interval, et_soft_timer_callback_t callback);
    void et_soft_timer_stop(et_soft_timer_t *timer);
    bool et_soft_timer_is_timeout(et_soft_timer_t *timer);
    /**
     *
     *  @brief: Process timer callback, put this function in while loop
     *
     *  @param: timer timer array.
     *  @param: time_cnt timer number
     *
     *  @return: void
     */
    void et_process_timer_callbacks(et_soft_timer_t *timer, uint8_t time_cnt);
#ifdef __cplusplus
    }
#endif
#endif

