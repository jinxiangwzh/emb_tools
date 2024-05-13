/*
 * @Author: wzh
 * @Date: 2024-05-10 14:28:30
 * @LastEditors: wzh
 * @LastEditTime: 2024-05-10 14:49:11
 * @Description: 
 * 
 * Copyright (c) 2024 by wzh, All Rights Reserved. 
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "element_queue.h"
#include "logging.h"

#define TEST_ARRAY_SIZE 5

element_queue_t test_queue;
uint8_t test_buffer[TEST_ARRAY_SIZE][RING_ELEMENT_DATA_SIZE_MAX];
uint8_t test_read_buffer[RING_ELEMENT_DATA_SIZE_MAX];
element_t test_read_element;
int test_element_queue(void)
{
    int ret = 0;
#if USING_STATIC_BUF
    ret = element_queue_init(&test_queue, RING_ELEMENT_QUEUE_TYPE);
#endif
    if (ret != 0)
        err("element queue init failure:%d\n", ret);
    info("element count:%d ?= 0", element_queue_count(&test_queue));
    srand(65326);
    for (uint8_t i = 0; i < TEST_ARRAY_SIZE; i++)
    {
        for (uint8_t j = 0; j < RING_ELEMENT_DATA_SIZE_MAX; j++)
        {
            test_buffer[i][j] = rand();
        }
        element_queue_put_element(&test_queue, test_buffer[i], RING_ELEMENT_DATA_SIZE_MAX, "test");
    }
    info("element count:%d ?= %d", element_queue_count(&test_queue), TEST_ARRAY_SIZE);
    test_read_element.buffer = test_read_buffer;
    for (uint8_t i = 0; i < TEST_ARRAY_SIZE; i++)
    {
        element_queue_pop_element(&test_queue, &test_read_element);
        for (uint8_t j = 0; j < RING_ELEMENT_DATA_SIZE_MAX; j++)
        {
            if (test_read_buffer[j] != test_buffer[i][j])
            {
                err("[%d][%d]element put in queue:0x%02x != read:0x%02x", 
                    i, j, test_read_buffer[j], test_buffer[i][j]);
                break;
            }
        }
        info("data in row:%d compare result:%d", i, element_queue_count(&test_queue) == (TEST_ARRAY_SIZE - i - 1) ? 1: 0);
    }

    info("element test finished");
    return 0;
}

