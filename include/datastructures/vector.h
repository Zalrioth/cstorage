#pragma once
#ifndef VECTOR_H_
#define VECTOR_H_

/* Memory aligned vector in C, Nick Bedner */

#define VECTOR_INIT_CAPACITY 4

struct Vector {
    unsigned int size; // Number of items currently in vector
    unsigned int capacity; // Total size of vector currently allocated in memory
    unsigned int memory_size; // How much memory each vector item takes
    void* items; // Pointer to start of data
};

static inline void vector_init(struct Vector* vector, int memory_size)
{
    vector->size = 0;
    vector->capacity = VECTOR_INIT_CAPACITY;
    vector->memory_size = memory_size;
    vector->items = malloc(memory_size * vector->capacity);
}

static inline int vector_size(struct Vector* vector)
{
    return vector->size;
}

static inline int vector_capactiy(struct Vector* vector)
{
    return vector->capacity;
}

static inline int vector_empty(struct Vector* vector)
{
    return vector->size == 0;
}

static inline void vector_resize(struct Vector* vector, int capacity)
{
    void* newItems = realloc((char*)vector->items, vector->memory_size * capacity);

    // If realloc fails vector will not be resized
    if (newItems) {
        vector->items = newItems;
        vector->capacity = capacity;
    }
}

static inline void vector_push_back(struct Vector* vector, void* item)
{
    if (vector->capacity == vector->size)
        vector_resize(vector, vector->capacity * 2);

    memcpy((char*)vector->items + (vector->memory_size * vector->size), item, vector->memory_size);
    vector->size++;
}

static inline void vector_insert(struct Vector* vector, int index, void* item)
{
#ifdef BOUNDS_CHECK
    if (index < 0 || index >= vector->size)
        return;
#endif
    if (vector->capacity == vector->size)
        vector_resize(vector, vector->capacity * 2);

    memmove((char*)vector->items + (vector->memory_size * (index + 1)), (char*)vector->items + (vector->memory_size * index), vector->memory_size * (vector->size - (index + 1) + 1));
    memcpy((char*)vector->items + (vector->memory_size * index), item, vector->memory_size);

    vector->size++;
}

static inline void vector_set(struct Vector* vector, int index, void* item)
{
#ifdef BOUNDS_CHECK
    if (index >= 0 && index < vector->size)
        memcpy((char*)vector->items + (vector->memory_size * index), item, vector->memory_size);
#else
    memcpy((char*)vector->items + (vector->memory_size * index), item, vector->memory_size);
#endif
}

static inline void* vector_get(struct Vector* vector, int index)
{
#ifdef BOUNDS_CHECK
    if (index >= 0 && index < vector->size)
        return (char*)vector->items + (vector->memory_size * index);

    return NULL;
#else
    return (char*)vector->items + (vector->memory_size * index);
#endif
}

static inline int vector_exists(struct Vector* vector, int index)
{
    return index >= 0 && index < vector->size;
}

static inline void vector_remove(struct Vector* vector, int index)
{
#ifdef BOUNDS_CHECK
    if (index < 0 || index >= vector->size)
        return;
#endif
    memmove((char*)vector->items + (vector->memory_size * index), (char*)vector->items + (vector->memory_size * (index + 1)), vector->memory_size * (vector->size - (index + 1)));

    vector->size--;

    if (vector->size > 0 && vector->size == vector->capacity / 4)
        vector_resize(vector, vector->capacity / 2);
}

static inline void vector_clear(struct Vector* vector)
{
    vector->size = 0;
    vector->capacity = VECTOR_INIT_CAPACITY;
    free(vector->items);
    vector->items = malloc(vector->memory_size * vector->capacity);
}

static inline void vector_delete(struct Vector* vector)
{
    free(vector->items);
}

#endif
