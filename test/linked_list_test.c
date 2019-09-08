#include <assert.h>
#include <linked_list.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

void test_create_linked_list() {
  struct LinkedList *ll = create_linked_list();
  assert(ll != NULL);
  assert(ll->head == NULL);
  assert(ll->tail == NULL);
  free_linked_list(ll);
}

void test_create_linked_list_node() {
  int8_t value = 100;
  struct LinkedListNode *node = create_linked_list_node(&value);
  assert(node->value == &value);
  free_linked_list_node(node);
}

void test_free_linked_list_node() {
  int8_t value = 100;
  struct LinkedListNode *node = create_linked_list_node(&value);
  assert(free_linked_list_node(node) == &value);
}

void test_linked_list_add_tail_node() {
  struct LinkedList *ll = create_linked_list();

  int8_t value1 = 100;
  int8_t value2 = 20;
  int8_t value3 = 3;

  struct LinkedListNode *node1 = create_linked_list_node(&value1);
  struct LinkedListNode *node2 = create_linked_list_node(&value2);
  struct LinkedListNode *node3 = create_linked_list_node(&value3);

  linked_list_add_tail_node(ll, node1);
  assert(ll->head->prev == NULL);
  assert(ll->head == node1);
  assert(ll->head->next == NULL);
  assert(ll->tail->prev == NULL);
  assert(ll->tail == node1);
  assert(ll->tail->next == NULL);

  linked_list_add_tail_node(ll, node2);
  assert(ll->head->prev == NULL);
  assert(ll->head == node1);
  assert(ll->head->next == node2);
  assert(ll->tail->prev == node1);
  assert(ll->tail == node2);
  assert(ll->tail->next == NULL);

  linked_list_add_tail_node(ll, node3);
  assert(ll->head->prev == NULL);
  assert(ll->head == node1);
  assert(ll->head->next == node2);
  assert(node2->prev == node1);
  assert(node2->next == node3);
  assert(ll->tail->prev == node2);
  assert(ll->tail == node3);
  assert(ll->tail->next == NULL);

  free_linked_list(ll);
}

void test_linked_list_add_head_node() {
  struct LinkedList *ll = create_linked_list();

  int8_t value1 = 100;
  int8_t value2 = 20;
  int8_t value3 = 3;

  struct LinkedListNode *node1 = create_linked_list_node(&value1);
  struct LinkedListNode *node2 = create_linked_list_node(&value2);
  struct LinkedListNode *node3 = create_linked_list_node(&value3);

  linked_list_add_head_node(ll, node1);
  assert(ll->head->prev == NULL);
  assert(ll->head == node1);
  assert(ll->head->next == NULL);
  assert(ll->tail->prev == NULL);
  assert(ll->tail == node1);
  assert(ll->tail->next == NULL);

  linked_list_add_head_node(ll, node2);
  assert(ll->head->prev == NULL);
  assert(ll->head == node2);
  assert(ll->head->next == node1);
  assert(ll->tail->prev == node2);
  assert(ll->tail == node1);
  assert(ll->tail->next == NULL);

  linked_list_add_head_node(ll, node3);
  assert(ll->head->prev == NULL);
  assert(ll->head == node3);
  assert(ll->head->next == node2);
  assert(node2->prev == node3);
  assert(node2->next == node1);
  assert(ll->tail->prev == node2);
  assert(ll->tail == node1);
  assert(ll->tail->next == NULL);

  free_linked_list(ll);
}

void test_linked_list_remove_tail_node() {
  struct LinkedList *ll = create_linked_list();

  int8_t value1 = 1;
  int8_t value2 = 2;
  int8_t value3 = 3;

  struct LinkedListNode *node1 = create_linked_list_node(&value1);
  struct LinkedListNode *node2 = create_linked_list_node(&value2);
  struct LinkedListNode *node3 = create_linked_list_node(&value3);

  linked_list_add_tail_node(ll, node1);
  linked_list_add_tail_node(ll, node2);
  linked_list_add_tail_node(ll, node3);

  assert(linked_list_remove_tail_node(ll) == node3);
  assert(linked_list_remove_tail_node(ll) == node2);
  assert(linked_list_remove_tail_node(ll) == node1);

  free_linked_list(ll);
}

void test_linked_list_remove_head_node() {
  struct LinkedList *ll = create_linked_list();

  int8_t value1 = 1;
  int8_t value2 = 2;
  int8_t value3 = 3;

  struct LinkedListNode *node1 = create_linked_list_node(&value1);
  struct LinkedListNode *node2 = create_linked_list_node(&value2);
  struct LinkedListNode *node3 = create_linked_list_node(&value3);

  linked_list_add_tail_node(ll, node1);
  linked_list_add_tail_node(ll, node2);
  linked_list_add_tail_node(ll, node3);

  assert(linked_list_remove_head_node(ll) == node1);
  assert(linked_list_remove_head_node(ll) == node2);
  assert(linked_list_remove_head_node(ll) == node3);

  free_linked_list(ll);
}

void test_linked_list_add_tail_general(void (*tail_adder)(struct LinkedList *, int8_t *)) {
  struct LinkedList *ll = create_linked_list();

  int8_t value1 = 1;
  int8_t value2 = 2;
  int8_t value3 = 3;

  tail_adder(ll, &value1);
  assert(ll->head->prev == NULL);
  assert(ll->head->value == &value1);
  assert(ll->head->next == NULL);
  assert(ll->tail->prev == NULL);
  assert(ll->tail->value == &value1);
  assert(ll->tail->next == NULL);
  assert(ll->head == ll->tail);

  tail_adder(ll, &value2);
  assert(ll->head->prev == NULL);
  assert(ll->head->value == &value1);
  assert(ll->head->next == ll->tail);
  assert(ll->tail->prev == ll->head);
  assert(ll->tail->value == &value2);
  assert(ll->tail->next == NULL);

  tail_adder(ll, &value3);
  assert(ll->head->prev == NULL);
  assert(ll->head->value == &value1);
  assert(ll->head->next == ll->tail->prev);
  assert(ll->head->next->prev == ll->head);
  assert(ll->head->next->next == ll->tail);
  assert(ll->head->next->value == &value2);
  assert(ll->tail->value == &value3);
  assert(ll->tail->next == NULL);

  free_linked_list(ll);
}

void test_linked_list_add_tail() {
  test_linked_list_add_tail_general((void (*)(struct LinkedList *, int8_t *)) linked_list_add_tail);
}

void test_linked_list_offer() {
  test_linked_list_add_tail_general((void (*)(struct LinkedList *, int8_t *)) linked_list_offer);
}

void test_linked_list_add_head_general(void (*head_adder)(struct LinkedList *, int8_t *)) {
  struct LinkedList *ll = create_linked_list();

  int8_t value1 = 1;
  int8_t value2 = 2;
  int8_t value3 = 3;

  head_adder(ll, &value1);
  assert(ll->head->prev == NULL);
  assert(ll->head->value == &value1);
  assert(ll->head->next == NULL);
  assert(ll->tail->prev == NULL);
  assert(ll->tail->value == &value1);
  assert(ll->tail->next == NULL);
  assert(ll->head == ll->tail);

  head_adder(ll, &value2);
  assert(ll->head->prev == NULL);
  assert(ll->head->value == &value2);
  assert(ll->head->next == ll->tail);
  assert(ll->tail->prev == ll->head);
  assert(ll->tail->value == &value1);
  assert(ll->tail->next == NULL);

  head_adder(ll, &value3);
  assert(ll->head->prev == NULL);
  assert(ll->head->value == &value3);
  assert(ll->head->next == ll->tail->prev);
  assert(ll->head->next->prev == ll->head);
  assert(ll->head->next->next == ll->tail);
  assert(ll->head->next->value == &value2);
  assert(ll->tail->value == &value1);
  assert(ll->tail->next == NULL);

  free_linked_list(ll);
}

void test_linked_list_add_head() {
  test_linked_list_add_head_general((void (*)(struct LinkedList *, int8_t *)) linked_list_add_head);
}

void test_linked_list_push() {
  test_linked_list_add_head_general((void (*)(struct LinkedList *, int8_t *)) linked_list_push);
}

void test_linked_list_remove_tail() {
  struct LinkedList *ll = create_linked_list();

  int8_t value1 = 1;
  int8_t value2 = 2;
  int8_t value3 = 3;

  linked_list_add_head(ll, &value1);
  linked_list_add_head(ll, &value2);
  linked_list_add_head(ll, &value3);

  assert(linked_list_remove_tail(ll) == &value1);
  assert(linked_list_remove_tail(ll) == &value2);
  assert(linked_list_remove_tail(ll) == &value3);

  free_linked_list(ll);
}

void test_linked_list_remove_head_general(int8_t *(*head_remover)(struct LinkedList *)) {
  struct LinkedList *ll = create_linked_list();

  int8_t value1 = 1;
  int8_t value2 = 2;
  int8_t value3 = 3;

  linked_list_add_tail(ll, &value1);
  linked_list_add_tail(ll, &value2);
  linked_list_add_tail(ll, &value3);

  assert(head_remover(ll) == &value1);
  assert(head_remover(ll) == &value2);
  assert(head_remover(ll) == &value3);

  free_linked_list(ll);
}

void test_linked_list_remove_head() {
  test_linked_list_remove_head_general((int8_t *(*)(struct LinkedList *)) linked_list_remove_head);
}

void test_linked_list_poll() {
  test_linked_list_remove_head_general((int8_t *(*)(struct LinkedList *)) linked_list_pop);
}

void test_linked_list_pop() {
  test_linked_list_remove_head_general((int8_t *(*)(struct LinkedList *)) linked_list_pop);
}

void test_clean_linked_list() {
  struct LinkedList *ll = create_linked_list();

  int8_t value1 = 1;
  int8_t value2 = 2;
  int8_t value3 = 3;

  linked_list_add_tail(ll, &value1);
  linked_list_add_tail(ll, &value2);
  linked_list_add_tail(ll, &value3);

  clean_linked_list(ll);
  assert(ll->head == NULL);
  assert(ll->tail == NULL);

  free_linked_list(ll);
}

int main(int argc, char const *argv[]) {
  printf("Starting test execution.\n");
  test_create_linked_list();
  printf("test_create_linked_list passed.\n");
  test_create_linked_list_node();
  printf("test_create_linked_list_node passed.\n");
  test_free_linked_list_node();
  printf("test_free_linked_list_node passed.\n");
  test_linked_list_add_tail_node();
  printf("test_linked_list_add_tail_node passed.\n");
  test_linked_list_add_head_node();
  printf("test_linked_list_add_head_node passed.\n");
  test_linked_list_remove_tail_node();
  printf("test_linked_list_remove_tail_node passed.\n");
  test_linked_list_remove_head_node();
  printf("test_linked_list_remove_head_node passed.\n");
  test_linked_list_add_tail();
  printf("test_linked_list_add_tail passed.\n");
  test_linked_list_offer();
  printf("test_linked_list_offer passed.\n");
  test_linked_list_add_head();
  printf("test_linked_list_add_head passed.\n");
  test_linked_list_push();
  printf("test_linked_list_push passed.\n");
  test_linked_list_remove_tail();
  printf("test_linked_list_remove_tail passed.\n");
  test_linked_list_remove_head();
  printf("test_linked_list_remove_head passed.\n");
  test_linked_list_poll();
  printf("test_linked_list_poll passed.\n");
  test_linked_list_pop();
  printf("test_linked_list_pop passed.\n");
  test_clean_linked_list();
  printf("test_clean_linked_list passed.\n");
  printf("Test execution finished.\n");
  return 0;
}
