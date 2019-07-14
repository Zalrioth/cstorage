#pragma once
#ifndef VECTOR_H_
#define VECTOR_H_

/* Memory aligned vector in C, Nick Bedner */

#define VECTOR_INIT_CAPACITY 4

struct Vector {
    void* items; // Pointer to start of data
    int capacity; // Total size of vector currently allocated in memory
    int size; // Number of items currently in vector
    int memorySize; // How much memory each vector item takes
};

static inline void vector_Init(struct Vector* v, int memorySize)
{
    v->memorySize = memorySize;
    v->capacity = VECTOR_INIT_CAPACITY;
    v->size = 0;
    v->items = malloc(memorySize * v->capacity);
}

static inline int vector_Size(struct Vector* v)
{
    return v->size;
}

static inline int vector_Capactiy(struct Vector* v)
{
    return v->capacity;
}

static inline int vector_Empty(struct Vector* v)
{
    return (v->size == 0) ? 1 : 0;
}

static inline void vector_Resize(struct Vector* v, int capacity)
{
    void* newItems = realloc((char*)v->items, v->memorySize * capacity);

    if (newItems) {
        v->items = newItems;
        v->capacity = capacity;
    }
}

static inline void vector_Swap(struct Vector* v1, struct Vector* v2)
{
    struct Vector* vTemp = v1;
    v1 = v2;
    v2 = vTemp;
}

static inline void vector_PushBack(struct Vector* v, void* item)
{
    if (v->capacity == v->size)
        vector_Resize(v, v->capacity * 2);

    memcpy((char*)v->items + (v->memorySize * v->size), item, v->memorySize);
    v->size++;
}

static inline void vector_Insert(struct Vector* v, int index, void* item)
{
#ifdef BOUNDS_CHECK
    if (index < 0 || index >= v->size)
        return;
#endif
    if (v->capacity == v->size)
        vector_Resize(v, v->capacity * 2);

    memmove((char*)v->items + (v->memorySize * (index + 1)), (char*)v->items + (v->memorySize * index), v->memorySize * (v->size - (index + 1) + 1));
    memcpy((char*)v->items + (v->memorySize * index), item, v->memorySize);

    v->size++;
}

static inline void vector_Set(struct Vector* v, int index, void* item)
{
#ifdef BOUNDS_CHECK
    if (index >= 0 && index < v->size)
        memcpy((char*)v->items + (v->memorySize * index), item, v->memorySize);
#else
    memcpy((char*)v->items + (v->memorySize * index), item, v->memorySize);
#endif
}

static inline void* vector_Get(struct Vector* v, int index)
{
#ifdef BOUNDS_CHECK
    if (index >= 0 && index < v->size)
        return (char*)v->items + (v->memorySize * index);

    return NULL;
#else
    return (char*)v->items + (v->memorySize * index);
#endif
}

static inline int vector_Exists(struct Vector* v, int index)
{
    return (index >= 0 && index < v->size) ? 1 : 0;
}

static inline void vector_Remove(struct Vector* v, int index)
{
#ifdef BOUNDS_CHECK
    if (index < 0 || index >= v->size)
        return;
#endif
    memmove((char*)v->items + (v->memorySize * index), (char*)v->items + (v->memorySize * (index + 1)), v->memorySize * (v->size - (index + 1)));

    v->size--;

    if (v->size > 0 && v->size == v->capacity / 4)
        vector_Resize(v, v->capacity / 2);
}

static inline void vector_Clear(struct Vector* v)
{
    memset((char*)v->items, 0, v->memorySize * v->capacity);
    v->size = 0;
    vector_Resize(v, VECTOR_INIT_CAPACITY);
}

static inline void vector_Free(struct Vector* v)
{
    free(v->items);
}

static inline void vector_Delete(struct Vector* v)
{
    vector_Clear(v);
    free(v->items);
}

#endif