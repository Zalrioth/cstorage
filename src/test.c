#include "../include/datastructures/datastructures.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
    // Vector test
    struct Vector vec;
    vector_init(&vec, sizeof(int));

    int testNum1 = 10;

    vector_push_back(&vec, &testNum1);
    vector_push_back(&vec, &testNum1);
    vector_push_back(&vec, &testNum1);
    vector_push_back(&vec, &testNum1);

    printf("Num: %d\n", *(int*)vector_get(&vec, 3));

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

    printf("Num: %d\n", *(int*)vector_get(&vec, 1));
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

    printf("Num: %d\n", *(int*)vector_get(&vec, 1));
    printf("Total: %d\n", vector_size(&vec));
    printf("Size: %d\n", vector_size(&vec));

    vector_delete(&vec);

    // Stack test
    struct Stack stack;

    stack_init(&stack, sizeof(int));

    int val1 = 10;
    int val2 = 20;
    int val3 = 30;

    stack_push(&stack, &val1);
    stack_push(&stack, &val2);
    stack_push(&stack, &val3);

    printf("%d peeked on stack!\n", *(int*)stack_peek(&stack));
    printf("%d popped from stack!\n", *(int*)stack_pop(&stack));
    printf("%d peeked from stack!\n", *(int*)stack_peek(&stack));

    stack_push(&stack, &val1);
    stack_push(&stack, &val2);
    stack_push(&stack, &val3);

    printf("%d popped from stack!\n", *(int*)stack_pop(&stack));
    printf("%d popped from stack!\n", *(int*)stack_pop(&stack));
    printf("%d popped from stack!\n", *(int*)stack_pop(&stack));
    printf("%d popped from stack!\n", *(int*)stack_pop(&stack));
    printf("%d popped from stack!\n", *(int*)stack_pop(&stack));

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

    printf("%d popped from stack!\n", *(int*)stack_pop(&stack));
    printf("Size: %d\n", stack_size(&stack));
    printf("%d popped from stack!\n", *(int*)stack_pop(&stack));
    printf("Size: %d\n", stack_size(&stack));

    stack_delete(&stack);

    // Queue test
    struct Queue queue;
    queue_init(&queue, sizeof(int));

    int queueNum1 = 10;
    int queueNum2 = 20;
    int queueNum3 = 30;

    queue_push(&queue, &queueNum1);
    queue_push(&queue, &queueNum2);
    queue_push(&queue, &queueNum3);

    printf("Front of queue: %d\n", *(int*)queue_front(&queue));
    printf("Back of queue: %d\n", *(int*)queue_back(&queue));

    queue_remove(&queue);

    printf("Front of queue: %d\n", *(int*)queue_front(&queue));
    printf("Back of queue: %d\n", *(int*)queue_back(&queue));

    queue_remove(&queue);

    printf("Front of queue: %d\n", *(int*)queue_front(&queue));
    printf("Back of queue: %d\n", *(int*)queue_back(&queue));

    int* popNum = malloc(sizeof(int));
    queue_pop(&queue, popNum);

    printf("Final popped value: %d\n", *popNum);

    if (queue_size(&queue) == 0)
        printf("Queue is empty!\n");

    queue_clear(&queue);

    queue_delete(&queue);

    return 0;
}