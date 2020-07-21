#pragma once
#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <stdlib.h>
#include <string.h>

#define ARRAY_LIST_INIT_CAPACITY 4
#define ARRAY_LIST_RESIZE_FACTOR 1.5

struct ArrayList {
  size_t size;      // Number of items currently in array list
  size_t capacity;  // Total size of array list currently allocated in memory
  void** items;     // Pointer to start of data
};

static inline void array_list_init(struct ArrayList* array_list) {
  array_list->size = 0;
  array_list->capacity = ARRAY_LIST_INIT_CAPACITY;
  array_list->items = malloc(sizeof(void*) * ARRAY_LIST_INIT_CAPACITY);
}

static inline void array_list_delete(struct ArrayList* array_list) {
  free(array_list->items);
}

static inline int array_list_size(struct ArrayList* array_list) {
  return array_list->size;
}

static inline int array_list_capactiy(struct ArrayList* array_list) {
  return array_list->capacity;
}

static inline int array_list_empty(struct ArrayList* array_list) {
  return array_list->size == 0;
}

static inline void array_list_resize(struct ArrayList* array_list, size_t capacity) {
  void** new_items = realloc(array_list->items, sizeof(void*) * capacity);

  // If realloc fails array list will not be resized
  if (new_items) {
    array_list->items = new_items;
    array_list->capacity = capacity;
  }
}

static inline void array_list_add(struct ArrayList* array_list, void* item) {
  if (array_list->capacity == array_list->size)
    array_list_resize(array_list, array_list->capacity * ARRAY_LIST_RESIZE_FACTOR);

  array_list->items[array_list->size++] = item;
}

static inline void* array_list_pop_back(struct ArrayList* array_list) {
  if (array_list->size == 0)
    return NULL;

  if (array_list->size > 0 && array_list->size == array_list->capacity / 4)
    array_list_resize(array_list, array_list->capacity / 2);

  return array_list->items[--array_list->size];
}

static inline void array_list_insert(struct ArrayList* array_list, size_t index, void* item) {
  if (index < 0 || index >= array_list->size)
    return;

  if (array_list->capacity == array_list->size)
    array_list_resize(array_list, array_list->capacity * ARRAY_LIST_RESIZE_FACTOR);

  memmove((char*)array_list->items + (sizeof(void*) * (index + 1)), (char*)array_list->items + (sizeof(void*) * index), sizeof(void*) * (array_list->size - (index + 1) + 1));
  array_list->items[index] = item;
  array_list->size++;
}

static inline void array_list_set(struct ArrayList* array_list, size_t index, void* item) {
  if (index >= 0 && index < array_list->size)
    array_list->items[index] = item;
}

static inline void* array_list_get(struct ArrayList* array_list, size_t index) {
  if (index >= 0 && index < array_list->size)
    return array_list->items[index];
  return NULL;
}

static inline void array_list_swap(struct ArrayList* array_list, size_t index1, size_t index2) {
  void* temp = array_list->items[index1];
  array_list->items[index1] = array_list->items[index2];
  array_list->items[index2] = temp;
}

static inline int array_list_exists(struct ArrayList* array_list, size_t index) {
  return index >= 0 && index < array_list->size;
}

static inline void array_list_remove(struct ArrayList* array_list, size_t index) {
  if (index < 0 || index >= array_list->size)
    return;

  memmove((char*)array_list->items + (sizeof(void*) * index), (char*)array_list->items + (sizeof(void*) * (index + 1)), sizeof(void*) * (array_list->size - (index + 1)));
  array_list->size--;

  if (array_list->size > 0 && array_list->size == array_list->capacity / 4)
    array_list_resize(array_list, array_list->capacity / 2);
}

static inline void array_list_clear(struct ArrayList* array_list) {
  array_list->size = 0;
  array_list->capacity = ARRAY_LIST_INIT_CAPACITY;
  array_list_resize(array_list, ARRAY_LIST_INIT_CAPACITY);
}

static inline void array_list_clear_free(struct ArrayList* array_list) {
  for (size_t iterate_num = 0; iterate_num < array_list->size; iterate_num++)
    free(array_list->items[iterate_num]);

  array_list->size = 0;
  array_list->capacity = ARRAY_LIST_INIT_CAPACITY;
  array_list_resize(array_list, ARRAY_LIST_INIT_CAPACITY);
}

#endif  // ARRAY_LIST_H
