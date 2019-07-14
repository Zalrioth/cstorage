#include "../include/datastructures/datastructures.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
    struct Vector vec;
    vector_Init(&vec, sizeof(int));

    int testNum = 10;

    vector_PushBack(&vec, &testNum);
    vector_PushBack(&vec, &testNum);
    vector_PushBack(&vec, &testNum);
    vector_PushBack(&vec, &testNum);

    printf("Num: %d\n", *(int*)vector_Get(&vec, 3));

    printf("Total: %d\n", vector_Size(&vec));
    printf("Size: %d\n", vector_Size(&vec));

    vector_PushBack(&vec, &testNum);
    vector_PushBack(&vec, &testNum);

    printf("Total: %d\n", vector_Size(&vec));
    printf("Size: %d\n", vector_Size(&vec));

    vector_Remove(&vec, 0);
    vector_Remove(&vec, 0);
    vector_Remove(&vec, 0);
    vector_Remove(&vec, 0);

    printf("Total: %d\n", vector_Size(&vec));
    printf("Size: %d\n", vector_Size(&vec));

    int testNum2 = 20;

    vector_Insert(&vec, 1, &testNum2);

    printf("Num: %d\n", *(int*)vector_Get(&vec, 1));

    printf("Total: %d\n", vector_Size(&vec));
    printf("Size: %d\n", vector_Size(&vec));

    if (vector_Get(&vec, 10) == NULL)
        printf("Outside of vector!\n");
#ifndef BOUNDS_CHECK
    else
        printf("Bounds check off!");
#endif

    vector_Delete(&vec);

    return 0;
}