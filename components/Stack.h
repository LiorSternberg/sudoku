#ifndef FINAL_PROJECT_STACK_H
#define FINAL_PROJECT_STACK_H

#include <stdbool.h>

typedef struct StackNode_ {
    int row;
    int column;
    int val;
    struct StackNode_ *next;
} StackNode;

typedef struct{
    StackNode *top;
} Stack;

Stack* create_stack();

StackNode* create_stack_node(int row, int column, int val);

void push(int row, int column, int val, Stack *stack);

StackNode* pop(Stack *stack);

StackNode* top(Stack *stack);

bool is_empty_stack(Stack *stack);

void destroy_stack_node(StackNode *node);

void destroy_stack(Stack *stack);

#endif
