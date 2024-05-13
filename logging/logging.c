/*
 * @Author: wzh
 * @Date: 2023-08-22 15:12:20
 * @LastEditors: wzh
 * @LastEditTime: 2023-08-22 15:16:59
 * @Description: 
 * 
 * Copyright (c) 2023 by Inomec, All Rights Reserved. 
 */
#include "logging.h"

int logging_level = DEBUG_LEVEL;

void set_log_level(int level)
{
    if (level > 3)
        level = 3;
    else if (level < 0)
        level = 0;
    logging_level = level;
}

