#pragma once
#ifndef VECTOR_H_
#define VECTOR_H_

/* Memory aligned vector in C, Nick Bedner */

// TODO: Move

#define VECTOR_INIT_CAPACITY 4
#define VECTOR_RESIZE_FACTOR 2

struct Vector {
  size_t size;         // Number of items currently in vector
  size_t capacity;     // Total size of vector currently allocated in memory
  size_t memory_size;  // How much memory each vector item takes
  void* items;         // Pointer to start of data
};

static inline void vector_init(struct Vector* vector, size_t memory_size) {
  vector->size = 0;
  vector->capacity = VECTOR_INIT_CAPACITY;
  vector->memory_size = memory_size;
  vector->items = malloc(memory_size * VECTOR_INIT_CAPACITY);
}

static inline void vector_delete(struct Vector* vector) {
  free(vector->items);
}

static inline size_t vector_size(struct Vector* vector) {
  return vector->size;
}

static inline size_t vector_capactiy(struct Vector* vector) {
  return vector->capacity;
}

static inline int vector_empty(struct Vector* vector) {
  return vector->size == 0;
}

static inline void vector_resize(struct Vector* vector, size_t capacity) {
  void* new_items = realloc((char*)vector->items, vector->memory_size * capacity);

  // If realloc fails vector will not be resized
  if (new_items) {
    vector->items = new_items;
    vector->capacity = capacity;
  }
}

static inline void vector_push_back(struct Vector* vector, void* item) {
  if (vector->capacity == vector->size)
    vector_resize(vector, vector->capacity * VECTOR_RESIZE_FACTOR);

  memcpy((char*)vector->items + (vector->memory_size * vector->size), item, vector->memory_size);
  vector->size++;
}

// TODO: Add test case
static inline void vector_pop_back(struct Vector* vector, void* copy_buffer) {
#ifdef BOUNDS_CHECK
  if (vector->size == 0)
    return;
#endif
  memcpy(copy_buffer, (char*)vector->items + (vector->memory_size * (vector->size - 1)), vector->memory_size);

  vector->size--;

  if (vector->size > 0 && vector->size == vector->capacity / 4)
    vector_resize(vector, vector->capacity / 2);
}

static inline void vector_insert(struct Vector* vector, size_t index, void* item) {
#ifdef BOUNDS_CHECK
  if (index < 0 || index >= vector->size)
    return;
#endif
  if (vector->capacity == vector->size)
    vector_resize(vector, vector->capacity * VECTOR_RESIZE_FACTOR);

  memmove((char*)vector->items + (vector->memory_size * (index + 1)), (char*)vector->items + (vector->memory_size * index), vector->memory_size * (vector->size - (index + 1) + 1));
  memcpy((char*)vector->items + (vector->memory_size * index), item, vector->memory_size);

  vector->size++;
}

static inline void vector_set(struct Vector* vector, size_t index, void* item) {
#ifdef BOUNDS_CHECK
  if (index >= 0 && index < vector->size)
    memcpy((char*)vector->items + (vector->memory_size * index), item, vector->memory_size);
#else
  memcpy((char*)vector->items + (vector->memory_size * index), item, vector->memory_size);
#endif
}

static inline void* vector_get(struct Vector* vector, size_t index) {
#ifdef BOUNDS_CHECK
  if (index >= 0 && index < vector->size)
    return (char*)vector->items + (vector->memory_size * index);

  return NULL;
#else
  return (char*)vector->items + (vector->memory_size * index);
#endif
}

static inline int vector_exists(struct Vector* vector, size_t index) {
  return index >= 0 && index < vector->size;
}

static inline void vector_remove(struct Vector* vector, size_t index) {
#ifdef BOUNDS_CHECK
  if (index < 0 || index >= vector->size)
    return;
#endif
  memmove((char*)vector->items + (vector->memory_size * index), (char*)vector->items + (vector->memory_size * (index + 1)), vector->memory_size * (vector->size - (index + 1)));

  vector->size--;

  if (vector->size > 0 && vector->size == vector->capacity / 4)
    vector_resize(vector, vector->capacity / 2);
}

// TODO: More testing needed of performance of realloc vs. free/malloc
static inline void vector_clear(struct Vector* vector) {
  vector->size = 0;
  vector->capacity = VECTOR_INIT_CAPACITY;
  vector_resize(vector, VECTOR_INIT_CAPACITY);
  //free(vector->items);
  //vector->items = malloc(vector->memory_size * vector->capacity);
}

#endif
