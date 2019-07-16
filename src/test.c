#include "../include/datastructures/datastructures.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
    struct Vector vec;
    vector_init(&vec, sizeof(int));

    int testNum = 10;

    vector_push_back(&vec, &testNum);
    vector_push_back(&vec, &testNum);
    vector_push_back(&vec, &testNum);
    vector_push_back(&vec, &testNum);

    printf("Num: %d\n", *(int*)vector_get(&vec, 3));

    printf("Total: %d\n", vector_size(&vec));
    printf("Size: %d\n", vector_size(&vec));

    vector_push_back(&vec, &testNum);
    vector_push_back(&vec, &testNum);

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

    vector_delete(&vec);

    return 0;
}