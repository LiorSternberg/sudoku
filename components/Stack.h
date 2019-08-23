//
// Created by USER on 23/08/2019.
//

#ifndef FINAL_PROJECT_STACK_H
#define FINAL_PROJECT_STACK_H

#include <stdbool.h>

typedef struct{
    int i;
    int j;
    int val;
} Parameters;

typedef struct StackNode StackNode;

struct StackNode{
    Parameters params;
    StackNode *next;
};

typedef struct{
    StackNode *top;
} Stack;

Stack* create_stack();

StackNode* create_stack_node(int i, int j, int val);

void push(int i, int j, int val, Stack *stack);

StackNode pop(Stack *stack);

StackNode top(Stack *stack);

bool is_empty_stack(Stack *stack);

void destroy_stack_node(StackNode *node);

void destroy_stack(Stack *stack);

#endif
