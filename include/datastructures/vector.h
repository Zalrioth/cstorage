#pragma once
#ifndef VECTOR_H_
#define VECTOR_H_

/* Memory aligned vector in C, Nick Bedner */

#define VECTOR_INIT_CAPACITY 4

struct Vector {
    unsigned int capacity; // Total size of vector currently allocated in memory
    unsigned int size; // Number of items currently in vector
    unsigned int memory_size; // How much memory each vector item takes
    void* items; // Pointer to start of data
};

static inline void vector_init(struct Vector* v, int memory_size)
{
    v->capacity = VECTOR_INIT_CAPACITY;
    v->size = 0;
    v->memory_size = memory_size;
    v->items = malloc(memory_size * v->capacity);
}

static inline int vector_size(struct Vector* v)
{
    return v->size;
}

static inline int vector_capactiy(struct Vector* v)
{
    return v->capacity;
}

static inline int vector_empty(struct Vector* v)
{
    return v->size == 0;
}

static inline void vector_resize(struct Vector* v, int capacity)
{
    void* newItems = realloc((char*)v->items, v->memory_size * capacity);

    // If realloc fails vector will not be resized
    if (newItems) {
        v->items = newItems;
        v->capacity = capacity;
    }
}

static inline void vector_push_back(struct Vector* v, void* item)
{
    if (v->capacity == v->size)
        vector_resize(v, v->capacity * 2);

    memcpy((char*)v->items + (v->memory_size * v->size), item, v->memory_size);
    v->size++;
}

static inline void vector_insert(struct Vector* v, int index, void* item)
{
#ifdef BOUNDS_CHECK
    if (index < 0 || index >= v->size)
        return;
#endif
    if (v->capacity == v->size)
        vector_resize(v, v->capacity * 2);

    memmove((char*)v->items + (v->memory_size * (index + 1)), (char*)v->items + (v->memory_size * index), v->memory_size * (v->size - (index + 1) + 1));
    memcpy((char*)v->items + (v->memory_size * index), item, v->memory_size);

    v->size++;
}

static inline void vector_set(struct Vector* v, int index, void* item)
{
#ifdef BOUNDS_CHECK
    if (index >= 0 && index < v->size)
        memcpy((char*)v->items + (v->memory_size * index), item, v->memory_size);
#else
    memcpy((char*)v->items + (v->memory_size * index), item, v->memory_size);
#endif
}

static inline void* vector_get(struct Vector* v, int index)
{
#ifdef BOUNDS_CHECK
    if (index >= 0 && index < v->size)
        return (char*)v->items + (v->memory_size * index);

    return NULL;
#else
    return (char*)v->items + (v->memory_size * index);
#endif
}

static inline int vector_exists(struct Vector* v, int index)
{
    return index >= 0 && index < v->size;
}

static inline void vector_remove(struct Vector* v, int index)
{
#ifdef BOUNDS_CHECK
    if (index < 0 || index >= v->size)
        return;
#endif
    memmove((char*)v->items + (v->memory_size * index), (char*)v->items + (v->memory_size * (index + 1)), v->memory_size * (v->size - (index + 1)));

    v->size--;

    if (v->size > 0 && v->size == v->capacity / 4)
        vector_resize(v, v->capacity / 2);
}

static inline void vector_clear(struct Vector* v)
{
    memset((char*)v->items, 0, v->memory_size * v->capacity);
    v->size = 0;
    vector_resize(v, VECTOR_INIT_CAPACITY);
}

static inline void vector_free(struct Vector* v)
{
    free(v->items);
}

static inline void vector_delete(struct Vector* v)
{
    vector_clear(v);
    free(v->items);
}

#endif