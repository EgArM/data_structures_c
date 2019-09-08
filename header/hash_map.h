#pragma once
#include <stdbool.h>
#include <stddef.h>

typedef size_t map_size_t;

struct HashMapNode {
  void *key;
  void *value;
  struct HashMapNode *next;
};

struct HashMapBucket {
  struct HashMapNode *node;
};

struct HashMap {
  map_size_t (*hash_f) (void *);
  bool (*eq_f) (void *, void *);
  map_size_t capacity;
  map_size_t buckets_number;
  struct HashMapBucket *buckets;
  map_size_t entries_number;
};

struct HashMap *create_hash_map(map_size_t (*hash_f) (void *),
                                bool (*eq_f) (void *, void *),
                                map_size_t initial_capacity);

void *hash_map_put(struct HashMap *map, void *key, void *value);

bool hash_map_contains(struct HashMap *map, void *key);

void *hash_map_get(struct HashMap *map, void *key);

void *hash_map_remove(struct HashMap *map, void *key);

void free_hash_map(struct HashMap *map);
