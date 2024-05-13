#include "queue.h"

void queue_reset(queue_t *q)
{
    q->_head = q->_tail = 0;
}

bool queue_empty(queue_t *q)
{
    return q->_tail == q->_head ? true : false;
}

bool queue_full(queue_t *q)
{
    uint32_t pos = (q->_head + 1) % QUEUE_SIZE;
    return pos == q->_tail ? true : false;
}

bool queue_push(queue_t *q, uint8_t _data)
{
    uint32_t pos = (q->_head + 1) % QUEUE_SIZE;

    if(!queue_full(q)) // not full
    {
        q->_data[q->_head] = _data;
        q->_head = pos;
        return true;
    }
    return false;
}

bool queue_pop(queue_t *q, uint8_t* _data)
{
    if(!queue_empty(q))
    {
        *_data = q->_data[q->_tail];
        q->_tail = (q->_tail + 1) % QUEUE_SIZE;
        return true;
    }
    return false;
}

uint32_t queue_size(queue_t *q)
{
    return ((q->_head + QUEUE_SIZE - q->_tail) % QUEUE_SIZE);
}

