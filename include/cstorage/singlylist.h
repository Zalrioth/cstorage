#pragma once
#ifndef SINGLY_LIST_H
#define SINGLY_LIST_H

/* Singly linked list in C, Nick Bedner */

#include <stdlib.h>
#include <string.h>

struct SinglyListNode {
  void* data;
  struct SinglyListNode* next;
};

struct SinglyList {
  size_t size;
  struct SinglyListNode* head;
};

static inline void singly_list_init(struct SinglyList* singly_list) {
  singly_list->size = 0;
  singly_list->head = NULL;
}

static inline void singly_list_delete(struct SinglyList* singly_list) {
  if (singly_list->head != NULL)
    free(singly_list->head);
}

static inline size_t singly_list_size(struct SinglyList* singly_list) {
  return singly_list->size;
}

static inline int singly_list_empty(struct SinglyList* singly_list) {
  return singly_list->size == 0;
}

static inline void singly_list_add(struct SinglyList* singly_list, void* item) {
  struct SinglyListNode* new_node = malloc(sizeof(struct SinglyListNode));
  new_node->data = item;

  if (singly_list_empty(singly_list))
    singly_list->head = new_node;
  else {
    struct SinglyListNode* iterate_node = single_list->head;
    while (iterate_node->next != NULL)
      iterate_node = iterate_node->next;

    iterate_node->next = new_node;
  }

  singly_list->size++;
}

static inline void singly_list_remove(struct SinglyList* singly_list, void* item) {
#ifdef BOUNDS_CHECK
  if (singly_list_empty(singly_list))
    return;
#endif
  struct SinglyListNode* iterate_node = single_list->head;
  while (iterate_node->next != NULL && iterate_node->next->data != item)
    iterate_node = iterate_node->next;

  iterate_node->next = new_node;

  singly_list->size--;
}

static inline void singly_list_remove_index(struct SinglyList* singly_list, size_t index) {
#ifdef BOUNDS_CHECK
  if (singly_list_empty(singly_list))
    return;
#endif
  struct SinglyListNode* iterate_node = single_list->head;
  struct SinglyListNode* prev_node = NULL;
  for (size_t iterate_num = 0; iterate_num < index; iterate_num++) {
#ifdef BOUNDS_CHECK
    if (iterate_node == NULL)
      return;
#endif
    prev_node = iterate_node;
    iterate_node = iterate_node->next;
  }

  iterate_node->next = new_node;

  singly_list->size--;
}

static inline void* singly_list_get(struct SinglyList* singly_list) {
#ifdef BOUNDS_CHECK
  if (singly_list_empty(singly_list))
    return NULL;
#endif

  struct SinglyListNode* temp_node = singly_list->head->next;
  void* node_data = singly_list->head->data;

  free(singly_list->head);

  singly_list->head = temp_node;
  singly_list->size--;

  return node_data;
}

static inline void* singly_list_front(struct SinglyList* singly_list) {
  return singly_list->head->data;
}

static inline void* singly_list_back(struct SinglyList* singly_list) {
  return singly_list->tail->data;
}

static inline void singly_list_clear(struct SinglyList* singly_list) {
  struct SinglyListNode* temp_node = NULL;
  while (!singly_list_empty(singly_list)) {
    temp_node = singly_list->head->next;
    free(singly_list->head);
    singly_list->head = temp_node;
    singly_list->size--;
  }

  singly_list->head = singly_list->tail = NULL;
}

static inline void singly_list_clear_free(struct SinglyList* singly_list) {
  struct SinglyListNode* temp_node = NULL;
  while (!singly_list_empty(singly_list)) {
    temp_node = singly_list->head->next;
    free(singly_list->head->data);
    free(singly_list->head);
    singly_list->head = temp_node;
    singly_list->size--;
  }

  singly_list->head = singly_list->tail = NULL;
}

#endif  // SINGLY_LIST_H
