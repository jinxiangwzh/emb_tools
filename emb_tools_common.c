/*
 * @Author: wzh
 * @Date: 2024-05-06 10:38:03
 * @LastEditors: wzh
 * @LastEditTime: 2024-05-06 16:29:37
 * @Description: 
 * 
 * Copyright (c) 2024 by wzh, All Rights Reserved. 
 */
#include "emb_tools_common.h"

volatile uint32_t g_tick_ms = 0;

/**
 * @brief  Put this function in the SysTick_Handler function
 */
void et_system_tick_increase(void)
{
    g_tick_ms++;
}

uint32_t et_get_tick_ms(void)
{
    return g_tick_ms;
}

