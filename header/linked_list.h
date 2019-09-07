#pragma once

struct LinkedListNode {
  void *value;
  struct LinkedListNode *next;
  struct LinkedListNode *prev;
};

struct LinkedList {
  struct LinkedListNode *head;
  struct LinkedListNode *tail;
};

struct LinkedList *create_linked_list();

struct LinkedListNode *create_linked_list_node(void *value);

void *free_linked_list_node(struct LinkedListNode *result_node);

void linked_list_add_tail_node(struct LinkedList *list, struct LinkedListNode *node);

void linked_list_add_head_node(struct LinkedList *list, struct LinkedListNode *node);

struct LinkedListNode *linked_list_remove_tail_node(struct LinkedList *list);

struct LinkedListNode *linked_list_remove_head_node(struct LinkedList *list);

void linked_list_add_tail(struct LinkedList *list, void *value);

void linked_list_offer(struct LinkedList *list, void *value);

void linked_list_add_head(struct LinkedList *list, void *value);

void linked_list_push(struct LinkedList *list, void *value);

void *linked_list_remove_tail(struct LinkedList *list);

void *linked_list_remove_head(struct LinkedList *list);

void *linked_list_poll(struct LinkedList *list);

void *linked_list_pop(struct LinkedList *list);

void clean_linked_list(struct LinkedList *list);

void free_linked_list(struct LinkedList *list);
