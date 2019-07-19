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
    unsigned int memory_size;
    struct QueueNode* head;
    struct QueueNode* tail;
};

static inline void queue_init(struct Queue* queue, unsigned int memory_size)
{
    queue->size = 0;
    queue->memory_size = memory_size;
    queue->head = queue->tail = NULL;
}

static inline void queue_delete(struct Queue* queue)
{
    if (queue->head != NULL)
        free(queue->head);

    if (queue->tail != NULL)
        free(queue->tail);
}

static inline int queue_size(struct Queue* queue)
{
    return queue->size;
}

static inline int queue_empty(struct Queue* queue)
{
    return queue->size == 0;
}

static inline void queue_push(struct Queue* queue, void* item)
{
    struct QueueNode* new_node = malloc(sizeof(struct QueueNode));
    new_node->data = malloc(sizeof(queue->memory_size));

    memcpy(new_node->data, item, queue->memory_size);

    if (queue_empty(queue)) {
        queue->head = new_node;
        queue->tail = new_node;
    } else {
        queue->tail->prev = new_node;
        queue->tail = new_node;
    }

    queue->size++;
}

//TODO: Reduce code reuse and still be fast
static inline void queue_pop(struct Queue* queue, void* copy_buffer)
{
#ifdef BOUNDS_CHECK
    if (queue_empty(queue))
        return;
#endif

    memcpy(copy_buffer, queue->head->data, queue->memory_size);

    struct QueueNode* temp_node = queue->head->prev;
    free(queue->head->data);
    free(queue->head);
    queue->head = temp_node;
    queue->size--;
}

static inline void queue_remove(struct Queue* queue)
{
#ifdef BOUNDS_CHECK
    if (queue_empty(queue))
        return;
#endif

    struct QueueNode* temp_node = queue->head->prev;
    free(queue->head->data);
    free(queue->head);
    queue->head = temp_node;
    queue->size--;
}

static inline void* queue_front(struct Queue* queue)
{
    return queue->head->data;
}

static inline void* queue_back(struct Queue* queue)
{
    return queue->tail->data;
}

static inline void queue_clear(struct Queue* queue)
{
    struct QueueNode* temp_node = NULL;
    while (!queue_empty(queue)) {
        temp_node = queue->head->prev;
        free(queue->head->data);
        free(queue->head);
        queue->head = temp_node;
        queue->size--;
    }

    queue->head = queue->tail = NULL;
}

#endif
