#include <stdio.h>
#include "../include/cstorage/cstorage.h"

int vector_test();
int stack_test();
int queue_test();
int array_list_test();
int priority_queue_test();
//int octree_test();

int main(int argc, char *argv[]) {
  if (vector_test() == 0)
    printf("Vector test passed!\n");

  if (stack_test() == 0)
    printf("Stack test passed!\n");

  if (queue_test() == 0)
    printf("Queue test passed!\n");

  if (array_list_test() == 0)
    printf("Array list test passed!\n");

  if (priority_queue_test() == 0)
    printf("Priority queue test passed!\n");

  //if (octree_test() == 0)
  //  printf("Octree test passed!\n");

  return 0;
}

int vector_test() {
  struct Vector vec;
  vector_init(&vec, sizeof(int));

  int testNum1 = 10;

  vector_push_back(&vec, &testNum1);
  vector_push_back(&vec, &testNum1);
  vector_push_back(&vec, &testNum1);
  vector_push_back(&vec, &testNum1);

  printf("Num: %d\n", *(int *)vector_get(&vec, 3));

  printf("Total: %d\n", vector_size(&vec));
  printf("Size: %d\n", vector_size(&vec));

  vector_push_back(&vec, &testNum1);
  vector_push_back(&vec, &testNum1);

  printf("Total: %d\n", vector_size(&vec));
  printf("Size: %d\n", vector_size(&vec));

  vector_remove(&vec, 0);
  vector_remove(&vec, 0);
  vector_remove(&vec, 0);
  vector_remove(&vec, 0);

  printf("Total: %d\n", vector_size(&vec));
  printf("Size: %d\n", vector_size(&vec));

  int testNum2 = 20;

  vector_insert(&vec, 1, &testNum2);

  printf("Num: %d\n", *(int *)vector_get(&vec, 1));
  printf("Total: %d\n", vector_size(&vec));
  printf("Size: %d\n", vector_size(&vec));

  if (vector_get(&vec, 10) == NULL)
    printf("Outside of vector!\n");
#ifndef BOUNDS_CHECK
  else
    printf("Bounds check off!");
#endif

  printf("Clearing vector!\n");

  vector_clear(&vec);

  vector_push_back(&vec, &testNum1);
  vector_push_back(&vec, &testNum2);

  printf("Num: %d\n", *(int *)vector_get(&vec, 1));
  printf("Total: %d\n", vector_size(&vec));
  printf("Size: %d\n", vector_size(&vec));

  vector_delete(&vec);

  return 0;
}

int stack_test() {
  struct Stack stack;
  stack_init(&stack);

  int val1 = 10;
  int val2 = 20;
  int val3 = 30;

  stack_push(&stack, &val1);
  stack_push(&stack, &val2);
  stack_push(&stack, &val3);

  printf("%d peeked on stack!\n", *(int *)stack_peek(&stack));
  printf("%d popped from stack!\n", *(int *)stack_pop(&stack));
  printf("%d peeked from stack!\n", *(int *)stack_peek(&stack));

  stack_push(&stack, &val1);
  stack_push(&stack, &val2);
  stack_push(&stack, &val3);

  printf("%d popped from stack!\n", *(int *)stack_pop(&stack));
  printf("%d popped from stack!\n", *(int *)stack_pop(&stack));
  printf("%d popped from stack!\n", *(int *)stack_pop(&stack));
  printf("%d popped from stack!\n", *(int *)stack_pop(&stack));
  printf("%d popped from stack!\n", *(int *)stack_pop(&stack));

  if (stack_pop(&stack) == NULL)
    printf("Stack empty!\n");
#ifndef BOUNDS_CHECK
  else
    printf("Bounds check off!");
#endif

  printf("Clearing stack!\n");

  stack_clear(&stack);

  stack_push(&stack, &val1);
  stack_push(&stack, &val2);
  stack_push(&stack, &val3);

  printf("%d popped from stack!\n", *(int *)stack_pop(&stack));
  printf("Size: %d\n", stack_size(&stack));
  printf("%d popped from stack!\n", *(int *)stack_pop(&stack));
  printf("Size: %d\n", stack_size(&stack));

  stack_delete(&stack);

  return 0;
}

int queue_test() {
  struct Queue queue;
  queue_init(&queue, 10);

  int queueNum1 = 10;
  int queueNum2 = 20;
  int queueNum3 = 30;

  queue_push(&queue, &queueNum1);
  queue_push(&queue, &queueNum2);
  queue_push(&queue, &queueNum3);

  printf("Front of queue: %d\n", *(int *)queue_front(&queue));
  printf("Back of queue: %d\n", *(int *)queue_back(&queue));

  queue_pop(&queue);

  printf("Front of queue: %d\n", *(int *)queue_front(&queue));
  printf("Back of queue: %d\n", *(int *)queue_back(&queue));

  queue_pop(&queue);

  printf("Front of queue: %d\n", *(int *)queue_front(&queue));
  printf("Back of queue: %d\n", *(int *)queue_back(&queue));

  printf("Final popped value: %d\n", *(int *)queue_pop(&queue));

  if (queue_empty(&queue))
    printf("Queue is empty!\n");

  queue_clear(&queue);

  queue_delete(&queue);

  return 0;
}

int array_list_test() {
  struct ArrayList array_list;
  array_list_init(&array_list);

  // Memory freed after function is left
  int num1 = 10;
  array_list_add(&array_list, &num1);

  printf("Current size of array list: %d\n", array_list_size(&array_list));
  printf("Last value in array list: %d\n", *(int *)array_list_get(&array_list, array_list_size(&array_list) - 1));

  // Must call free manually
  int *num2 = malloc(sizeof(int));
  *num2 = 20;
  array_list_add(&array_list, num2);

  printf("Current size of array list: %d\n", array_list_size(&array_list));
  printf("Last value in array list: %d\n", *(int *)array_list_get(&array_list, array_list_size(&array_list) - 1));

  int num3 = 30;
  array_list_insert(&array_list, 0, &num3);

  printf("Current size of array list: %d\n", array_list_size(&array_list));
  printf("Last value in array list: %d\n", *(int *)array_list_get(&array_list, array_list_size(&array_list) - 1));
  printf("First value in array list: %d\n", *(int *)array_list_get(&array_list, 0));

  array_list_set(&array_list, array_list_size(&array_list) - 1, &num3);

  printf("Last value in array list: %d\n", *(int *)array_list_get(&array_list, array_list_size(&array_list) - 1));
  printf("First value in array list: %d\n", *(int *)array_list_get(&array_list, 0));

  num3 = 15;

  printf("Last value in array list: %d\n", *(int *)array_list_get(&array_list, array_list_size(&array_list) - 1));
  printf("First value in array list: %d\n", *(int *)array_list_get(&array_list, 0));

  free(num2);

  array_list_clear(&array_list);
  array_list_delete(&array_list);

  return 0;
}

int priority_queue_test() {
  struct PriorityQueue priority_queue;
  priority_queue_init(&priority_queue);

  int num1 = 10;
  priority_queue_push(&priority_queue, &num1, 20);

  int num2 = 20;
  priority_queue_push(&priority_queue, &num2, 10);

  int num3 = 30;
  priority_queue_push(&priority_queue, &num3, 30);

  printf("Current size of priority queue: %d\n", priority_queue_size(&priority_queue));
  printf("Front of priority queue: %d\n", *(int *)priority_queue_front(&priority_queue));

  priority_queue_pop(&priority_queue);

  printf("Current size of priority queue: %d\n", priority_queue_size(&priority_queue));
  printf("Front of priority queue: %d\n", *(int *)priority_queue_front(&priority_queue));

  priority_queue_pop(&priority_queue);

  printf("Current size of priority queue: %d\n", priority_queue_size(&priority_queue));
  printf("Front of priority queue: %d\n", *(int *)priority_queue_front(&priority_queue));

  priority_queue_pop(&priority_queue);

  printf("Current size of priority queue: %d\n", priority_queue_size(&priority_queue));

  if (priority_queue_empty(&priority_queue))
    printf("Queue is empty!\n");

  priority_queue_clear(&priority_queue);
  priority_queue_delete(&priority_queue);

  return 0;
}

//int octree_test()
//{
//    struct Octree octree;
//    octree_init(&octree, (float[3]){0.0f, 0.0f, 0.0f}, (float[3]){1.0f, 1.0f, 1.0f});
//
//    struct OctreePoint *octreePoints = malloc(sizeof(struct OctreePoint) * 1000);
//
//    octree_delete(&octree);
//}
