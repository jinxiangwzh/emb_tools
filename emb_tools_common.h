/*
 * @Author: wzh
 * @Date: 2024-05-06 10:32:36
 * @LastEditors: wzh
 * @LastEditTime: 2024-05-06 13:06:00
 * @Description: 
 * 
 * Copyright (c) 2024 by wzh, All Rights Reserved. 
 */

#ifndef __EMB_TOOLS_COMMON_H__
#define __EMB_TOOLS_COMMON_H__
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "emb_tools_config.h"
#include "emb_tools_platform.h"

#define EMB_TOOLS_VERSION "0.1.0"

#define ET_ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

extern volatile uint32_t g_tick_ms;

#ifdef __cplusplus
extern "C" {
#endif
#ifdef __cplusplus
    extern "C" {
#endif
    void et_system_tick_increase(void);

    uint32_t et_get_tick_ms(void);
#ifdef __cplusplus
}
#endif

#endif
