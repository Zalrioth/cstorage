#pragma once
#ifndef PRIORITY_QUEUE_H_
#define PRIORITY_QUEUE_H_

/* Priority queue in C, Nick Bedner */

struct PriorityQueueNode {
    void* data;
    unsigned int priority;
    struct PriorityQueueNode* prev;
};

struct PriorityQueue {
    unsigned int size;
    struct PriorityQueueNode* head;
    struct PriorityQueueNode* tail;
};

static inline void queue_init(struct PriorityQueue* priority_queue)
{
    priority_queue->size = 0;
    priority_queue->head = priority_queue->tail = NULL;
}

static inline void queue_delete(struct PriorityQueue* priority_queue)
{
    if (priority_queue->head != NULL)
        free(priority_queue->head);

    if (priority_queue->tail != NULL)
        free(priority_queue->tail);
}

static inline int queue_size(struct PriorityQueue* priority_queue)
{
    return priority_queue->size;
}

static inline int queue_empty(struct PriorityQueue* priority_queue)
{
    return priority_queue->size == 0;
}

static inline void queue_push(struct PriorityQueue* priority_queue, void* item, int priority)
{
    struct PriorityQueueNode* new_node = malloc(sizeof(struct PriorityQueueNode));
    new_node->data = item;
    new_node->priority = priority;

    if (queue_empty(priority_queue)) {
        priority_queue->head = new_node;
        priority_queue->tail = new_node;
    } else {
        PriorityQueueNode* start = priority_queue->head;
        while (start->next != NULL && start->next->priority < priority)
            start = start->next;

        //priority_queue->tail->prev = new_node;
        //priority_queue->tail = new_node;
    }

    priority_queue->size++;
}

static inline void* queue_pop(struct PriorityQueue* priority_queue)
{
#ifdef BOUNDS_CHECK
    if (queue_empty(priority_queue))
        return NULL;
#endif

    struct PriorityQueueNode* temp_node = priority_queue->head->prev;
    void* node_data = priority_queue->head->data;

    free(priority_queue->head);

    priority_queue->head = temp_node;
    priority_queue->size--;

    return node_data;
}

static inline void* queue_front(struct PriorityQueue* priority_queue)
{
    return priority_queue->head->data;
}

static inline void* queue_back(struct PriorityQueue* priority_queue)
{
    return priority_queue->tail->data;
}

static inline void queue_clear(struct PriorityQueue* priority_queue)
{
    struct PriorityQueueNode* temp_node = NULL;
    while (!queue_empty(priority_queue)) {
        temp_node = priority_queue->head->prev;
        free(priority_queue->head);
        priority_queue->head = temp_node;
        priority_queue->size--;
    }

    priority_queue->head = priority_queue->tail = NULL;
}

static inline void queue_clear_free(struct PriorityQueue* priority_queue)
{
    struct PriorityQueueNode* temp_node = NULL;
    while (!queue_empty(priority_queue)) {
        temp_node = priority_queue->head->prev;
        free(priority_queue->head->data);
        free(priority_queue->head);
        priority_queue->head = temp_node;
        priority_queue->size--;
    }

    priority_queue->head = priority_queue->tail = NULL;
}

#endif
* /