#pragma once
#ifndef STACK_H_
#define STACK_H_

#define STACK_INIT_CAPACITY 4

struct Stack {
    unsigned int top;
    unsigned int capacity;
    unsigned int memory_size;
    void* items;
};

static inline void stack_init(struct Stack* stack, unsigned int memory_size)
{
    stack->top = 0;
    stack->capacity = STACK_INIT_CAPACITY;
    stack->memory_size = memory_size;
    stack->items = malloc(memory_size * stack->capacity);
}

static inline void stack_delete(struct Stack* stack)
{
    free(stack->items);
}

static inline int stack_empty(struct Stack* stack)
{
    return stack->top == 0;
}

static inline int stack_size(struct Stack* stack)
{
    return stack->top;
}

static inline int stack_capacity(struct Stack* stack)
{
    return stack->capacity;
}

static inline void stack_resize(struct Stack* stack, int capacity)
{
    void* newItems = realloc((char*)stack->items, stack->memory_size * capacity);

    // If realloc fails stack will not be resized
    if (newItems) {
        stack->items = newItems;
        stack->capacity = capacity;
    }
}

static inline void stack_push(struct Stack* stack, void* item)
{
    if (stack->capacity == stack->top)
        stack_resize(stack, stack->capacity * 2);

    memcpy((char*)stack->items + (stack->memory_size * stack->top++), item, stack->memory_size);
}

static inline void* stack_pop(struct Stack* stack)
{
#ifdef BOUNDS_CHECK
    if (stack_empty(stack))
        return NULL;
#endif
    stack->top--;

    if (stack->top > 0 && stack->top == stack->capacity / 4)
        stack_resize(stack, stack->capacity / 2);

    return (char*)stack->items + (stack->memory_size * (stack->top));
}

//TODO: Check asm here could be optimized probably
static inline void* stack_peek(struct Stack* stack)
{
#ifdef BOUNDS_CHECK
    if (stack_empty(stack))
        return NULL;
#endif
    return (char*)stack->items + (stack->memory_size * (stack->top - 1));
}

static inline void stack_clear(struct Stack* stack)
{
    stack->top = 0;
    stack->capacity = STACK_INIT_CAPACITY;
    free(stack->items);
    stack->items = malloc(stack->memory_size * stack->capacity);
}

#endif
