#pragma once
#ifndef PRIORITY_QUEUE_H_
#define PRIORITY_QUEUE_H_

/* Priority queue in C, Nick Bedner */

struct PriorityQueueNode {
    void* data;
    int priority;
    struct PriorityQueueNode* next;
};

struct PriorityQueue {
    struct PriorityQueueNode* head;
};

static inline void priority_queue_Init(struct PriorityQueue* p)
{
}

#endif