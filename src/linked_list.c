#include <linked_list.h>
#include <stdlib.h>

struct LinkedList *create_linked_list() {
  struct LinkedList *list = malloc(sizeof(struct LinkedList));
  if (list != NULL) {
    list->head = NULL;
    list->tail = NULL;
  }
  return list;
}

struct LinkedListNode *create_linked_list_node(void *value) {
  struct LinkedListNode *node = malloc(sizeof(struct LinkedListNode));
  if (node != NULL) {
    node->value = value;
    node->next = NULL;
    node->prev = NULL;
  }
  return node;
}

void *free_linked_list_node(struct LinkedListNode *node) {
  void *result = node->value;
  free(node);
  return result;
}

void __add_single_node__(struct LinkedList *list, struct LinkedListNode *node) {
  list->head = node;
  list->tail = node;
}

void linked_list_add_tail_node(struct LinkedList *list, struct LinkedListNode *node) {
  if (list->tail == NULL) {
    __add_single_node__(list, node);
  } else {
    list->tail->next = node;
    node->prev = list->tail;
    list->tail = node;
  }
}

void linked_list_add_head_node(struct LinkedList *list, struct LinkedListNode *node) {
  if (list->head == NULL) {
    __add_single_node__(list, node);
  } else {
    list->head->prev = node;
    node->next = list->head;
    list->head = node;
  }
}

struct LinkedListNode *linked_list_remove_tail_node(struct LinkedList *list) {
  struct LinkedListNode *result = list->tail;
  if (result == NULL) {
    return NULL;
  }
  struct LinkedListNode *prev = result->prev;
  list->tail = prev;
  if (prev == NULL) {
    list->head = NULL;
  } else {
    prev->next = NULL;
  }

  return result;
}

struct LinkedListNode *linked_list_remove_head_node(struct LinkedList *list) {
  struct LinkedListNode *result = list->head;
  if (result == NULL) {
    return NULL;
  }
  struct LinkedListNode *next = result->next;
  list->head = next;
  if (next == NULL) {
    list->tail = NULL;
  } else {
    next->prev = NULL;
  }

  return result;
}

void linked_list_add_tail(struct LinkedList *list, void *value) {
  struct LinkedListNode *node = create_linked_list_node(value);
  linked_list_add_tail_node(list, node);
}

void linked_list_offer(struct LinkedList *list, void *value) {
  linked_list_add_tail(list, value);
}

void linked_list_add_head(struct LinkedList *list, void *value) {
  struct LinkedListNode *node = create_linked_list_node(value);
  linked_list_add_head_node(list, node);
}

void linked_list_push(struct LinkedList *list, void *value) {
  linked_list_add_head(list, value);
}

void *linked_list_remove_tail(struct LinkedList *list) {
  struct LinkedListNode *result_node = linked_list_remove_tail_node(list);
  if (result_node == NULL) {
    return NULL;
  }
  return free_linked_list_node(result_node);
}

void *linked_list_remove_head(struct LinkedList *list) {
  struct LinkedListNode *result_node = linked_list_remove_head_node(list);
  if (result_node == NULL) {
    return NULL;
  }
  return free_linked_list_node(result_node);
}

void *linked_list_poll(struct LinkedList *list) {
  return linked_list_remove_head(list);
}

void *linked_list_pop(struct LinkedList *list) {
  return linked_list_remove_head(list);
}

void clean_linked_list(struct LinkedList *list) {
  while (linked_list_remove_tail(list) != NULL) {
  }
}

void free_linked_list(struct LinkedList *list) {
  clean_linked_list(list);
  free(list);
}
