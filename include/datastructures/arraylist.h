#pragma once
#ifndef ARRAY_LIST_H_
#define ARRAY_LIST_H_

/* Array list in C, Nick Bedner */

#define ARRAY_LIST_INIT_CAPACITY 4
#define ARRAY_LIST_RESIZE_FACTOR 0.5

struct ArrayList {
    unsigned int size; // Number of items currently in array list
    unsigned int capacity; // Total size of array list currently allocated in memory
    void** items; // Pointer to start of data
};

static inline void array_list_init(struct ArrayList* array_list)
{
    array_list->size = 0;
    array_list->capacity = ARRAY_LIST_INIT_CAPACITY;
    array_list->items = malloc(sizeof(void*) * ARRAY_LIST_INIT_CAPACITY);
}

static inline void array_list_delete(struct ArrayList* array_list)
{
    free(array_list->items);
}

static inline int array_list_size(struct ArrayList* array_list)
{
    return array_list->size;
}

static inline int array_list_capactiy(struct ArrayList* array_list)
{
    return array_list->capacity;
}

static inline int array_list_empty(struct ArrayList* array_list)
{
    return array_list->size == 0;
}

static inline void array_list_resize(struct ArrayList* array_list, int capacity)
{
    void** new_items = realloc((char*)array_list->items, sizeof(void*) * capacity);

    // If realloc fails array list will not be resized
    if (new_items) {
        array_list->items = new_items;
        array_list->capacity = capacity;
    }
}

static inline void array_list_add(struct ArrayList* array_list, void* item)
{
    if (array_list->capacity == array_list->size)
        array_list_resize(array_list, array_list->capacity * ARRAY_LIST_RESIZE_FACTOR);

    array_list->items[array_list->size++] = item;
}

static inline void* array_list_pop_back(struct ArrayList* array_list)
{
#ifdef BOUNDS_CHECK
    if (array_list->size == 0)
        return NULL;
#endif
    if (array_list->size > 0 && array_list->size == array_list->capacity / 4)
        array_list_resize(array_list, array_list->capacity / 2);

    return array_list->items[--array_list->size];
}

static inline void array_list_insert(struct ArrayList* array_list, int index, void* item)
{
#ifdef BOUNDS_CHECK
    if (index < 0 || index >= array_list->size)
        return;
#endif
    if (array_list->capacity == array_list->size)
        array_list_resize(array_list, array_list->capacity * ARRAY_LIST_RESIZE_FACTOR);

    memmove((char*)array_list->items + (sizeof(void*) * (index + 1)), (char*)array_list->items + (sizeof(void*) * index), sizeof(void*) * (array_list->size - (index + 1) + 1));
    array_list->items[index] = item;
    array_list->size++;
}

static inline void array_list_set(struct ArrayList* array_list, int index, void* item)
{
#ifdef BOUNDS_CHECK
    if (index >= 0 && index < array_list->size)
        array_list->items[index] = item;
#else
    array_list->items[index] = item;
#endif
}

static inline void* array_list_get(struct ArrayList* array_list, int index)
{
#ifdef BOUNDS_CHECK
    if (index >= 0 && index < array_list->size)
        return array_list->items[index];

    return NULL;
#else
    return array_list->items[index];
#endif
}

static inline int array_list_exists(struct ArrayList* array_list, int index)
{
    return index >= 0 && index < array_list->size;
}

static inline void array_list_remove(struct ArrayList* array_list, int index)
{
#ifdef BOUNDS_CHECK
    if (index < 0 || index >= array_list->size)
        return;
#endif
    memmove((char*)array_list->items + (sizeof(void*) * index), (char*)array_list->items + (sizeof(void*) * (index + 1)), sizeof(void*) * (array_list->size - (index + 1)));

    array_list->size--;

    if (array_list->size > 0 && array_list->size == array_list->capacity / 4)
        array_list_resize(array_list, array_list->capacity / 2);
}

static inline void array_list_clear(struct ArrayList* array_list)
{
    array_list->size = 0;
    array_list->capacity = ARRAY_LIST_INIT_CAPACITY;
    array_list_resize(array_list, ARRAY_LIST_INIT_CAPACITY);
}

static inline void array_list_clear_free(struct ArrayList* array_list)
{
    for (unsigned int iterate_num = 0; iterate_num < array_list->size; iterate_num++)
        free(array_list->items[iterate_num]);

    array_list->size = 0;
    array_list->capacity = ARRAY_LIST_INIT_CAPACITY;
    array_list_resize(array_list, ARRAY_LIST_INIT_CAPACITY);
}

#endif
