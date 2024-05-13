/*
 * @Author: wzh
 * @Date: 2024-05-10 10:59:03
 * @LastEditors: wzh
 * @LastEditTime: 2024-05-10 15:43:40
 * @Description:
 *
 * Copyright (c) 2024 by wzh, All Rights Reserved.
 */
#ifndef __ELEMENT_QUEUE_H__
#define __ELEMENT_QUEUE_H__
#include <stdint.h>
#include <stdbool.h>

#define USING_STATIC_BUF 1
#define USING_ELEMENT_NAME 1

#if USING_STATIC_BUF
#define RING_QUEUE_BUFFER_SIZE (1024)  // queue buffer size which is used to put element
#define RING_ELEMENT_DATA_SIZE_MAX (64) // element buffer max size
#define RING_ELEMENT_COUNT (16) // how many element in queue
#endif

#if USING_ELEMENT_NAME
#define RING_ELEMENT_NAME_MAX (32)
#endif

typedef struct
{
    uint8_t *buffer;
    uint32_t size; // data real size in element buffer
#if USING_ELEMENT_NAME
    char name[RING_ELEMENT_NAME_MAX];
#endif
}element_t;

typedef enum
{
    RING_ELEMENT_QUEUE_TYPE = 0,
    FIFO_ELEMENT_QUEUE_TYPE,
}ElementQueueType;

typedef struct
{
    uint8_t *buffer;   /* block of memory or array of data */
    uint32_t element_size;      /* how many bytes of each @element_t */
    uint32_t element_count;     /* number of chunks of element_t */
    volatile uint32_t head;     /* where the writes go */
    volatile uint32_t tail;     /* where the reads come from */
    ElementQueueType type;
}element_queue_t;

#ifdef __cplusplus
extern "C" {
#endif
    uint32_t element_queue_count(element_queue_t *b);

    bool element_queue_full(element_queue_t *b);

    bool element_queue_empty(element_queue_t *b);

    void element_queue_flush(element_queue_t *b);

#if USING_ELEMENT_NAME
    bool element_queue_put_element(element_queue_t *b,
        uint8_t *element_buf,
        uint32_t element_size,
        char *name);
#else
    bool element_queue_put_element(element_queue_t *b,
        uint8_t *element_buf,
        uint32_t element_size);
#endif

    bool element_queue_pop_element(element_queue_t *b, element_t *data_element);

#if USING_STATIC_BUF
    int element_queue_init(element_queue_t *b, ElementQueueType type);
#else
    int element_queue_init(element_queue_hdl_t *b,
        uint32_t content_size,
        uint32_t element_count, ElementQueueTypee type);
#endif
#ifdef __cplusplus
}
#endif
#endif
