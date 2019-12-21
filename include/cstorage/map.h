#pragma once
#ifndef MAP_H
#define MAP_H

/* Map in C, Nick Bedner */

#include "common.h"

struct MapNode {
  unsigned int hash;
  void* value;
  struct MapNode* next;
};

struct Map {
  struct MapNode** buckets;
  unsigned int num_buckets;
  unsigned int num_nodes;
};

struct MapIter {
  unsigned int bucket_idx;
  struct MapNode* node;
};

static inline void map_init(struct Map* map) {
  memset(map, 0, sizeof(struct Map));
}

static inline void map_delete(struct Map* map) {
  struct MapNode *next, *node;
  int i = map->num_buckets;
  while (i--) {
    node = map->buckets[i];
    while (node) {
      next = node->next;
      free(node);
      node = next;
    }
  }
  free(map->buckets);
}

static inline unsigned int map_hash(const char* str) {
  unsigned int hash = 5381;
  while (*str)
    hash = ((hash << 5) + hash) ^ *str++;
  return hash;
}

static inline struct MapNode* map_new_node(const char* key, void* value, int vsize) {
  struct MapNode* node;
  int ksize = strlen(key) + 1;
  int voffset = ksize + ((sizeof(void*) - ksize) % sizeof(void*));
  node = malloc(sizeof(*node) + voffset + vsize);
  if (!node) return NULL;
  memcpy(node + 1, key, ksize);
  node->hash = map_hash(key);
  node->value = ((char*)(node + 1)) + voffset;
  memcpy(node->value, value, vsize);
  return node;
}

static inline int map_bucket_idx(struct Map* map, unsigned int hash) {
  return hash & (map->num_buckets - 1);
}

static inline void map_add_node(struct Map* map, struct MapNode* node) {
  int n = map_bucketidx(map, node->hash);
  node->next = map->buckets[n];
  map->buckets[n] = node;
}

static int map_resize(struct Map* map, int num_buckets) {
  struct MapNode *nodes, *node, *next;
  struct MapNode** buckets;
  int i;

  nodes = NULL;
  i = map->num_buckets;
  while (i--) {
    node = (map->buckets)[i];
    while (node) {
      next = node->next;
      node->next = nodes;
      nodes = node;
      node = next;
    }
  }

  buckets = realloc(map->buckets, sizeof(*map->buckets) * num_buckets);
  if (buckets != NULL) {
    map->buckets = buckets;
    map->num_buckets = num_buckets;
  }
  if (map->buckets) {
    memset(map->buckets, 0, sizeof(*map->buckets) * map->num_buckets);

    node = nodes;
    while (node) {
      next = node->next;
      map_add_node(map, node);
      node = next;
    }
  }

  return (buckets == NULL) ? -1 : 0;
}

static inline struct MapNode** map_get_ref(struct Map* map, const char* key) {
  unsigned hash = map_hash(key);
  struct MapNode** next;
  if (map->num_buckets > 0) {
    next = &map->buckets[map_bucket_idx(map, hash)];
    while (*next) {
      if ((*next)->hash == hash && !strcmp((char*)(*next + 1), key))
        return next;
      next = &(*next)->next;
    }
  }
  return NULL;
}

static inline void* map_get(struct MapBase* map, const char* key) {
  struct MapNode** next = map_get_ref(map, key);
  return next ? (*next)->value : NULL;
}

static inline int map_set(struct Map* map, const char* key, void* value, int vsize) {
  int n, err;
  struct MapNode **next, *node;

  next = map_get_ref(map, key);
  if (next) {
    memcpy((*next)->value, value, vsize);
    return 0;
  }

  node = map_newnode(key, value, vsize);
  if (node == NULL)
    goto fail;
  if (map->num_nodes >= map->num_buckets) {
    n = (map->num_buckets > 0) ? (map->num_buckets << 1) : 1;
    err = map_resize(map, n);
    if (err)
      goto fail;
  }
  map_addnode(map, node);
  map->num_nodes++;
  return 0;
fail:
  if (node)
    free(node);
  return -1;
}

static inline void map_remove(struct Map* map, const char* key) {
  struct MapNode* node;
  struct MapNode** next = map_get_ref(map, key);
  if (next) {
    node = *next;
    *next = (*next)->next;
    free(node);
    map->num_nodes--;
  }
}

static inline struct MapIter map_iter() {
  struct MapIter iter;
  iter.bucket_idx = -1;
  iter.node = NULL;
  return iter;
}

static inline const char* map_next(struct Map* map, struct MapIter* iter) {
  if (iter->node) {
    iter->node = iter->node->next;
    if (iter->node == NULL) goto nextBucket;
  } else {
  nextBucket:
    do {
      if (++iter->bucket_idx >= map->num_buckets)
        return NULL;
      iter->node = map->buckets[iter->bucket_idx];
    } while (iter->node == NULL);
  }
  return (char*)(iter->node + 1);
}

#endif  // MAP_H
