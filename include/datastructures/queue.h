#pragma once
#ifndef QUEUE_H_
#define QUEUE_H_

/* Queue in C, Nick Bedner */

struct QueueNode {
    void* data;
    struct QueueNode* prev;
};

struct Queue {
    unsigned int size;
    struct QueueNode* head;
    struct QueueNode* tail;
};

static inline void queue_init(struct Queue* q)
{
    q->size = 0;
    q->head = NULL;
    q->tail = NULL;
}

static inline void queue_push(struct Queue* q)
{
}

static inline void queue_pop(struct Queue* q)
{
}

static inline void queue_empty(struct Queue* q)
{
}

static inline int queue_size(struct Queue* q)
{
    return q->size;
}

static inline void queue_swap(struct Queue* q)
{
}

static inline void queue_front(struct Queue* q)
{
}

static inline void queue_back(struct Queue* q)
{
}

#endif