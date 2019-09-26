#pragma once
#include <stdbool.h>
#include <stddef.h>

typedef size_t map_size_t;

struct HashMapNode {
  const void *key;
  const void *value;
  struct HashMapNode *next;
};

struct HashMapBucket {
  struct HashMapNode *node;
};

struct HashMap {
  map_size_t (*hash_f) (const void *);
  bool (*eq_f) (const void *, const void *);
  map_size_t capacity;
  map_size_t buckets_number;
  struct HashMapBucket *buckets;
  map_size_t entries_number;
};

struct HashMap *create_hash_map(map_size_t (*hash_f) (const void *),
                                bool (*eq_f) (const void *, const void *),
                                map_size_t initial_capacity);

bool hash_map_put(struct HashMap *map, const void *key, const void *value, const void **prev);

bool hash_map_contains(const struct HashMap *map, const void *key);

const void *hash_map_get(const struct HashMap *map, const void *key);

const void *hash_map_remove(struct HashMap *map, const void *key);

void free_hash_map(struct HashMap *map);
