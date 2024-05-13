#ifndef __QUEUE_H__
#define __QUEUE_H__
#include <stdint.h>
#include <stdbool.h>

#define QUEUE_SIZE 1024

typedef struct queue
{
    uint32_t _head;
    uint32_t _tail;
    uint8_t _data[QUEUE_SIZE];
}queue_t;

void queue_reset(queue_t *q);
bool queue_empty(queue_t *q);
bool queue_full(queue_t *q);
bool queue_push(queue_t *q, uint8_t _data);
bool queue_pop(queue_t *q, uint8_t* _data);
uint32_t queue_size(queue_t *q);

#endif

