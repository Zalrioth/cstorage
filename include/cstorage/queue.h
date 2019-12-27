#pragma once
#ifndef QUEUE_H
#define QUEUE_H

/* Queue in C, Nick Bedner */

#include <stdlib.h>
#include <string.h>

struct Queue {
  size_t size;
  size_t capacity;
  int front;
  int back;
  void** items;
};

static inline void queue_init(struct Queue* queue, size_t capacity) {
  queue->capacity = capacity;
  queue->size = queue->front = 0;
  queue->back = capacity - 1;
  queue->items = malloc(sizeof(void*) * capacity);
}

static inline void queue_delete(struct Queue* queue) {
  free(queue->items);
}

static inline size_t queue_size(struct Queue* queue) {
  return queue->size;
}

static inline int queue_empty(struct Queue* queue) {
  return queue->size == 0;
}

static inline int queue_full(struct Queue* queue) {
  return queue->size == queue->capacity;
}

static inline void queue_push(struct Queue* queue, void* item) {
  if (queue->size == queue->capacity)
    return;

  queue->back = (queue->back + 1) % queue->capacity;
  queue->items[queue->back] = item;
  queue->size++;
}

static inline void* queue_pop(struct Queue* queue) {
  if (queue_empty(queue))
    return NULL;

  void* item_data = queue->items[queue->front];
  queue->front = (queue->front + 1) % queue->capacity;
  queue->size--;

  return item_data;
}

static inline void* queue_front(struct Queue* queue) {
  if (queue_empty(queue))
    return NULL;

  return queue->items[queue->front];
}

static inline void* queue_back(struct Queue* queue) {
  if (queue_empty(queue))
    return NULL;

  return queue->items[queue->back];
}

static inline void queue_clear(struct Queue* queue) {
  queue->size = queue->front = 0;
  queue->back = queue->capacity - 1;
}

#endif  // QUEUE_H
