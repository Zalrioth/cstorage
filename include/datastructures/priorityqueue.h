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

static inline void priority_queue_init(struct PriorityQueue* priority_queue)
{
    priority_queue->size = 0;
    priority_queue->head = priority_queue->tail = NULL;
}

static inline void priority_queue_delete(struct PriorityQueue* priority_queue)
{
    if (priority_queue->head != NULL)
        free(priority_queue->head);

    if (priority_queue->tail != NULL)
        free(priority_queue->tail);
}

static inline int priority_queue_size(struct PriorityQueue* priority_queue)
{
    return priority_queue->size;
}

static inline int priority_queue_empty(struct PriorityQueue* priority_queue)
{
    return priority_queue->size == 0;
}

//TODO: Make this faster
static inline void priority_queue_push(struct PriorityQueue* priority_queue, void* item, int priority)
{
    struct PriorityQueueNode* new_node = malloc(sizeof(struct PriorityQueueNode));
    new_node->data = item;
    new_node->priority = priority;

    if (priority_queue_empty(priority_queue)) {
        new_node->prev = NULL;
        priority_queue->head = new_node;
        priority_queue->tail = new_node;
    } else if (priority_queue->head->priority < priority) {
        new_node->prev = priority_queue->head;
        priority_queue->head = new_node;
    } else {
        struct PriorityQueueNode* iterate_node = priority_queue->head;
        while (iterate_node->prev != NULL && iterate_node->priority <= priority)
            iterate_node = iterate_node->prev;

        new_node->prev = iterate_node->prev;
        iterate_node->prev = new_node;
    }

    priority_queue->size++;
}

static inline void* priority_queue_pop(struct PriorityQueue* priority_queue)
{
#ifdef BOUNDS_CHECK
    if (priority_queue_empty(priority_queue))
        return NULL;
#endif

    struct PriorityQueueNode* temp_node = priority_queue->head->prev;
    void* node_data = priority_queue->head->data;

    free(priority_queue->head);

    priority_queue->head = temp_node;
    priority_queue->size--;

    return node_data;
}

static inline void* priority_queue_front(struct PriorityQueue* priority_queue)
{
    return priority_queue->head->data;
}

static inline void* priority_queue_back(struct PriorityQueue* priority_queue)
{
    return priority_queue->tail->data;
}

static inline void priority_queue_clear(struct PriorityQueue* priority_queue)
{
    struct PriorityQueueNode* temp_node = NULL;
    while (!priority_queue_empty(priority_queue)) {
        temp_node = priority_queue->head->prev;
        free(priority_queue->head);
        priority_queue->head = temp_node;
        priority_queue->size--;
    }

    priority_queue->head = priority_queue->tail = NULL;
}

static inline void priority_queue_clear_free(struct PriorityQueue* priority_queue)
{
    struct PriorityQueueNode* temp_node = NULL;
    while (!priority_queue_empty(priority_queue)) {
        temp_node = priority_queue->head->prev;
        free(priority_queue->head->data);
        free(priority_queue->head);
        priority_queue->head = temp_node;
        priority_queue->size--;
    }

    priority_queue->head = priority_queue->tail = NULL;
}

#endif
