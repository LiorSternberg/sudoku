#ifndef FINAL_PROJECT_STACK_H
#define FINAL_PROJECT_STACK_H

#include <stdbool.h>

/* TODO (question for Tslil): if you don't hide the implementation of a struct in the '.c' file
 * you don't need to split the declaration of the Node. I do wonder though - don't you want to
 * hide it? do you want other modules to access the Node directly?
 *
 * typedef struct StackNode StackNode;*/

typedef struct StackNode_ {
    int i; /* TODO (question for Tslil): What are i and j? row and column? */
    int j;
    int val;
    struct StackNode_ *next;
} StackNode;

typedef struct{
    StackNode *top;
} Stack;

Stack* create_stack();

StackNode* create_stack_node(int i, int j, int val);

void push(int i, int j, int val, Stack *stack);

StackNode* pop(Stack *stack);

StackNode* top(Stack *stack);

bool is_empty_stack(Stack *stack);

void destroy_stack_node(StackNode *node);

void destroy_stack(Stack *stack);

#endif
