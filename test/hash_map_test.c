#include <assert.h>
#include <hash_map.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

map_size_t hash_f(int8_t *key) {
  return *key % 100;
}

bool eq_f(int8_t *key1, int8_t *key2) {
  return *key1 == *key2;
}

void test_create_hash_map() {
  struct HashMap *map = create_hash_map((map_size_t (*)(const void *)) hash_f,
                                        (bool (*)(const void *, const void*)) eq_f,
                                        0);
  assert(map->capacity == 12);
  assert(map->buckets_number == 16);
  assert(map->entries_number == 0);

  for (size_t i = 0; i < map->buckets_number; i++) {
    assert((map->buckets + i)->node == NULL);
  }

  free_hash_map(map);

  map = create_hash_map((map_size_t (*)(const void *)) hash_f,
                        (bool (*)(const void *, const void*)) eq_f,
                        1000);

  assert(map->capacity == 1536);
  assert(map->buckets_number == 2048);
  assert(map->entries_number == 0);

  free_hash_map(map);
}

void hash_map_print(struct HashMap *map) {
  printf("{\n");
  for (int8_t i = 0; i < map->buckets_number; i++) {
    struct HashMapBucket *bucket = map->buckets + i;
    printf("{i: %d->", i);
    struct HashMapNode *node = bucket->node;
    while (node != NULL) {
      printf("{key: %d, value: %d}->", *(int8_t *) (node->key), *(int8_t *) (node->value));
      node=node->next;
    }
    printf("NULL\n");
  }
  printf("}\n");
}

void test_hash_map_put() {
  struct HashMap *map = create_hash_map((map_size_t (*)(const void *)) hash_f,
                                        (bool (*)(const void *, const void*)) eq_f,
                                        0);
  int8_t key0 = 0;
  int8_t key3 = 3;
  int8_t key1 = 1;
  int8_t key101 = 101;
  int8_t value0 = 0;
  int8_t value3 = 3;
  int8_t value1 = 1;
  int8_t value101 = 101;

  const void *prev = NULL;

  assert(hash_map_put(map, &key0, &value0, &prev));
  assert(map->buckets->node->key == &key0);
  assert(map->buckets->node->value == &value0);
  assert(map->buckets->node->next == NULL);
  assert(map->capacity == 12);
  assert(map->buckets_number == 16);
  assert(map->entries_number == 1);
  assert(prev == NULL);

  assert(hash_map_put(map, &key3, &value3, &prev));
  assert((map->buckets + 3)->node->key == &key3);
  assert((map->buckets + 3)->node->value == &value3);
  assert((map->buckets + 3)->node->next == NULL);
  assert(map->capacity == 12);
  assert(map->buckets_number == 16);
  assert(map->entries_number == 2);
  assert(prev == NULL);

  assert(hash_map_put(map, &key1, &value1, &prev));
  struct HashMapNode *node1 = (map->buckets + 1)->node;
  assert(node1->key == &key1);
  assert(node1->value == &value1);
  assert(node1->next == NULL);
  assert(map->capacity == 12);
  assert(map->buckets_number == 16);
  assert(map->entries_number == 3);
  assert(prev == NULL);

  assert(hash_map_put(map, &key101, &value101, &prev));
  struct HashMapNode *node101 = (map->buckets + 1)->node;
  assert(node101->key == &key101);
  assert(node101->value == &value101);
  assert(node101->next == node1);
  assert(map->capacity == 12);
  assert(map->buckets_number == 16);
  assert(map->entries_number == 4);
  assert(prev == NULL);

  assert(hash_map_put(map, &key101, &value1, &prev));
  assert(prev == &value101);

  free_hash_map(map);

  map = create_hash_map((map_size_t (*)(const void *)) hash_f,
                        (bool (*)(const void *, const void*)) eq_f,
                        0);

  int8_t *keys[12];
  int8_t *values[12];
  for (int8_t i = 0; i < 12; i++) {
    int8_t *key = malloc(sizeof(int8_t));
    int8_t *value = malloc(sizeof(int8_t));
    *key = i + 16;
    *value = i;
    keys[i] = key;
    values[i] = value;
    assert(hash_map_put(map, key, value, &prev));
  }

  assert(map->capacity == 12);
  assert(map->buckets_number == 16);
  assert(map->entries_number == 12);

  struct HashMapNode *node16 = (map->buckets)->node;
  assert(node16->key == keys[0]);
  assert(node16->value == values[0]);
  assert(node16->next == NULL);

  for (int8_t i = 1; i < 12; i++) {
    struct HashMapNode *node = (map->buckets + i)->node;
    assert(node->key == keys[i]);
    assert(node->value == values[i]);
    assert(node->next == NULL);
  }

  for (int8_t i = 12; i < 16; i++) {
    assert((map->buckets + i)->node == NULL);
  }

  int8_t key116 = 116;
  int8_t value116 = 116;
  assert(hash_map_put(map, &key116, &value116, &prev));

  assert(map->capacity == 24);
  assert(map->buckets_number == 32);
  assert(map->entries_number == 13);

  for (int8_t i = 0; i < 16; i++) {
    assert((map->buckets + i)->node == NULL);
  }

  assert((map->buckets + 16)->node == node16);
  assert(node16->next->key == &key116);
  assert(node16->next->value == &value116);
  assert(node16->next->next == NULL);

  for (int8_t i = 1; i < 12; i++) {
    struct HashMapNode *node = (map->buckets + i + 16)->node;
    assert(node->key == keys[i]);
    assert(node->value == values[i]);
    assert(node->next == NULL);
  }

  for (int8_t i = 28; i < 32; i++) {
    assert((map->buckets + i)->node == NULL);
  }

  free_hash_map(map);

  for (int8_t i = 0; i < 12; i++) {
    free(keys[i]);
    free(values[i]);
  }
}

void test_hash_map_contains() {
  struct HashMap *map = create_hash_map((map_size_t (*)(const void *)) hash_f,
                                        (bool (*)(const void *, const void*)) eq_f,
                                        0);

  const void *prev = NULL;
  int8_t *keys[256];
  int8_t *values[256];
  for (int8_t i = -128; i < 127; i++) {
    int8_t *key = malloc(sizeof(int8_t));
    int8_t *value = malloc(sizeof(int8_t));
    *key = i;
    *value = i;
    keys[i + 128] = key;
    values[i + 128] = value;
    assert(hash_map_put(map, key, value, &prev));
  }

  for (int8_t i = -128; i < 126; i++) {
    assert(hash_map_contains(map, keys[i + 128]));
  }

  int8_t key126 = 126;
  assert(hash_map_contains(map, &key126));
  int8_t key127 = 127;
  assert(!hash_map_contains(map, &key127));

  free_hash_map(map);

  for (int8_t i = -128; i < 127; i++) {
    free(keys[i + 128]);
    free(values[i + 128]);
  }
}

void test_hash_map_get() {
  struct HashMap *map = create_hash_map((map_size_t (*)(const void *)) hash_f,
                                        (bool (*)(const void *, const void*)) eq_f,
                                        0);

  const void *prev = NULL;
  int8_t *keys[256];
  int8_t *values[256];
  for (int8_t i = -128; i < 127; i++) {
    int8_t *key = malloc(sizeof(int8_t));
    int8_t *value = malloc(sizeof(int8_t));
    *key = i;
    *value = i;
    keys[i + 128] = key;
    values[i + 128] = value;
    assert(hash_map_put(map, key, value, &prev));
  }

  for (int8_t i = -128; i < 126; i++) {
    assert(hash_map_get(map, keys[i + 128]) == values[i + 128]);
  }

  int8_t key126 = 126;
  assert(* (int8_t *) hash_map_get(map, &key126) == 126);
  int8_t key127 = 127;
  assert(hash_map_get(map, &key127) == NULL);

  free_hash_map(map);

  for (int8_t i = -128; i < 127; i++) {
    free(keys[i + 128]);
    free(values[i + 128]);
  }
}

void test_hash_map_remove() {
  struct HashMap *map = create_hash_map((map_size_t (*)(const void *)) hash_f,
                                        (bool (*)(const void *, const void*)) eq_f,
                                        0);

  const void *prev = NULL;
  int8_t *keys[256];
  int8_t *values[256];
  for (int8_t i = -128; i < 127; i++) {
    int8_t *key = malloc(sizeof(int8_t));
    int8_t *value = malloc(sizeof(int8_t));
    *key = i;
    *value = i;
    keys[i + 128] = key;
    values[i + 128] = value;
    assert(hash_map_put(map, key, value, &prev));
  }

  assert(map->entries_number == 255);
  assert(hash_map_get(map, keys[-1 + 128]) == values[-1 + 128]);
  assert(hash_map_remove(map, keys[-1 + 128]) == values[-1 + 128]);
  assert(map->entries_number == 254);

  free_hash_map(map);

  for (int8_t i = -128; i < 127; i++) {
    free(keys[i + 128]);
    free(values[i + 128]);
  }
}

int main(int argc, char const *argv[]) {
  printf("Starting test execution.\n");
  test_create_hash_map();
  printf("test_create_hash_map passed.\n");
  test_hash_map_put();
  printf("test_assert(hash_map_put passed.\n");
  test_hash_map_contains();
  printf("test_hash_map_contains passed.\n");
  test_hash_map_get();
  printf("test_hash_map_get passed.\n");
  test_hash_map_remove();
  printf("test_hash_map_remove passed.\n");
  printf("Test execution finished.\n");
  return 0;
}
