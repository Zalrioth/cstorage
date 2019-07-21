#pragma once
#ifndef QUEUE_H_
#define QUEUE_H_

/* Queue in C, Nick Bedner */

struct Queue {
    unsigned int size;
    unsigned int capacity;
    int front;
    int back;
    void** items;
};

static inline void queue_init(struct Queue* queue, int capacity)
{
    queue->size = queue->front = 0;
    queue->back = -1;
    queue->capacity = capacity;
    void** items = malloc(sizeof(void*) * capacity);
}

static inline void queue_delete(struct Queue* queue)
{
    free(queue->items);
}

static inline int queue_size(struct Queue* queue)
{
    return queue->size;
}

static inline int queue_empty(struct Queue* queue)
{
    return queue->size == 0;
}

static inline int queue_full(struct Queue* queue)
{
    return queue->size == queue->capacity;
}

static inline void queue_push(struct Queue* queue, void* item)
{
#ifdef BOUNDS_CHECK
    if (queue->size == queue->capacity)
        return;
#endif
    if (queue->back == queue->capacity - 1)
        queue->back = -1;

    queue->items[++queue->back] = item;
    queue->size++;
}

static inline void* queue_pop(struct Queue* queue)
{
#ifdef BOUNDS_CHECK
    if (queue_empty(queue))
        return NULL;
#endif
    void* node_data = queue->items[queue->front++];

    if (queue->front == queue->capacity)
        queue->front = 0;

    queue->size--;
    return node_data;
}

static inline void* queue_front(struct Queue* queue)
{
#ifdef BOUNDS_CHECK
    if (queue_empty(queue))
        return NULL;
#endif

    return queue->items[queue->front];
}

static inline void* queue_back(struct Queue* queue)
{
#ifdef BOUNDS_CHECK
    if (queue_empty(queue))
        return NULL;
#endif

    return queue->items[queue->back];
}

static inline void queue_clear(struct Queue* queue)
{
    queue->size = queue->front = queue->back = 0;
}

#endif
