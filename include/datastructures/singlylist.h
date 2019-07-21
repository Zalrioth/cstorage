/*/#pragma once
#ifndef QUEUE_H_
#define QUEUE_H_

struct QueueNode {
    void* data;
    struct QueueNode* prev;
};

struct Queue {
    unsigned int size;
    struct QueueNode* head;
    struct QueueNode* tail;
};

static inline void queue_init(struct Queue* queue)
{
    queue->size = 0;
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
    new_node->data = item;

    if (queue_empty(queue)) {
        queue->head = new_node;
        queue->tail = new_node;
    } else {
        queue->tail->prev = new_node;
        queue->tail = new_node;
    }

    queue->size++;
}

static inline void* queue_pop(struct Queue* queue)
{
#ifdef BOUNDS_CHECK
    if (queue_empty(queue))
        return NULL;
#endif

    struct QueueNode* temp_node = queue->head->prev;
    void* node_data = queue->head->data;

    free(queue->head);

    queue->head = temp_node;
    queue->size--;

    return node_data;
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
        free(queue->head);
        queue->head = temp_node;
        queue->size--;
    }

    queue->head = queue->tail = NULL;
}

static inline void queue_clear_free(struct Queue* queue)
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
*/