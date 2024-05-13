/*
 * @Author: wzh
 * @Date: 2024-05-10 10:59:03
 * @LastEditors: wzh
 * @LastEditTime: 2024-05-10 15:45:19
 * @Description:
 *
 * Copyright (c) 2024 by wzh, All Rights Reserved.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "element_queue.h"

#if USING_STATIC_BUF
static uint8_t element_buffer[RING_ELEMENT_DATA_SIZE_MAX * RING_ELEMENT_COUNT];
static uint8_t queue_buffer[RING_QUEUE_BUFFER_SIZE];
#else
#error "USING_STATIC_BUF must be defined, now only support this type!"
#endif

 /**
  * @brief: Returns the number of elements in the ring buffer
  * return:  Number of elements in the ring buffer
  */
uint32_t element_queue_count(element_queue_t *b)
{
    if (b != NULL)
    {
        return b->head - b->tail;
    }

    return 0;
}

/**
 * @brief: Returns the empty/full status of the ring buffer
 * return: true if the ring buffer is full, false if it is not.
 */
bool element_queue_full(element_queue_t *b)
{
    return (b ? (element_queue_count(b) == b->element_count) : true);
}

/**
 * @brief: Returns the empty/full status of the ring buffer
 * return: true if the ring buffer is empty, false if it is not.
 */
bool element_queue_empty(element_queue_t *b)
{
    return (b ? (element_queue_count(b) == 0) : true);
}

/**
 * @brief: Adds an element of data to the ring buffer
 * @param b - ring buffer structure
 * @param data_element - one element to add to the ring
 * return: true on successful add, false if not added
 */
#if USING_ELEMENT_NAME
bool element_queue_put_element(element_queue_t *b,
    uint8_t *element_buf,
    uint32_t element_size,
    char *name)
#else
bool element_queue_put_element(element_queue_t *b,
    uint8_t *element_buf,
    uint32_t element_size)
#endif
{
    bool status = false;
    element_t *element_start = NULL;

    if (b && element_buf)
    {
        if (element_size > RING_ELEMENT_DATA_SIZE_MAX)
            return false;
        element_start = (element_t *) b->buffer;
        if (!element_queue_full(b))
        {
            element_start += (b->head % b->element_count);
            element_start->size = element_size;
            memcpy(element_start->buffer, element_buf, element_size);
#if USING_ELEMENT_NAME
            snprintf(element_start->name, RING_ELEMENT_NAME_MAX, "%s", name);
#endif
            b->head++;

            status = true;
        }
        else if (b->type == RING_ELEMENT_QUEUE_TYPE)
        {
            b->tail++; // throw one element
#if USING_ELEMENT_NAME
            element_queue_put_element(b, element_buffer, element_size, name); // put again
#else
            element_queue_put_element(b, element_buffer, element_size); // put again
#endif
        }
    }

    return status;
}

// note:you should check the length malloc to element_t->buffer by yourself
bool element_queue_pop_element(element_queue_t *b, element_t *data_element)
{
    bool status = false;
    element_t *ring_data = NULL;

    if (!element_queue_empty(b))
    {
        ring_data = (element_t *) b->buffer;
        ring_data += (b->tail % b->element_count);
        if (data_element)
        {
            data_element->size = ring_data->size;
#ifdef USING_ELEMENT_NAME
            memcpy(data_element->name, ring_data->name, RING_ELEMENT_NAME_MAX);
#endif
            memcpy(data_element->buffer, ring_data->buffer, ring_data->size);
            b->tail++;
            status = true;
        }
    }

    return status;
}

void element_queue_flush(element_queue_t *b)
{
    if (b)
    {
        b->head = 0;
        b->tail = 0;
    }
}

/**
 * @brief: Configures the ring buffer
 * @param b - ring buffer structure
 * @param element_size - size of one element in the data block
 * @param element_count - number of elements in the data block
 * NOTES:element_count must be a power of two
 */
#if USING_STATIC_BUF
int element_queue_init(element_queue_t *b, ElementQueueType type)
{
    element_t *element = NULL;

    if (b == NULL)
        return -1;
    // check the size of queue
    if (RING_QUEUE_BUFFER_SIZE < RING_ELEMENT_COUNT * sizeof(element_t))
        return -2;

    b->head = 0;
    b->tail = 0;
    b->element_count = RING_ELEMENT_COUNT;
    b->element_size = sizeof(element_t);
    b->type = type;
    b->buffer = queue_buffer;
    element = (element_t *) b->buffer; // first element address

    // malloc memory for every element
    for (uint32_t index = 0; index < RING_ELEMENT_COUNT; index++)
    {
        // addressing in element_buffer
        element->buffer = element_buffer + index * RING_ELEMENT_DATA_SIZE_MAX;
        element++; // addressing in queue_buffer
    }

    return 0;
}
#else
int element_queue_init(element_queue_t *b,
    uint32_t content_size,
    uint32_t element_count, enum ElementQueueType type)
{
    if (b == NULL)
        return -1;

    b->head = 0;
    b->tail = 0;
    b->element_count = element_count;
    b->element_size = content_size;
    b->type = type;
    b->buffer = malloc(element_count * sizeof(content_size));
    if (b->buffer == NULL)
    {
        mft_err("fifo create failure\n");
        return -1;
    }

    return 0;
}
#endif

