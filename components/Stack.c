#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"
#include "../MemoryError.h"


Stack* create_stack() {
    Stack *stack = (Stack*) malloc(sizeof(Stack));
    validate_memory_allocation("create_stack", stack);

    stack->top = NULL;
    return stack;
}

StackNode* create_stack_node(int row, int column, int val) {
    StackNode *stack_node = (StackNode*) malloc(sizeof(StackNode));
    validate_memory_allocation("create_stack_node", stack_node);

    stack_node->row = row;
    stack_node->column = column;
    stack_node->val = val;

    return stack_node;
}

void push(int row, int column, int val, Stack *stack) {
    StackNode *new_top = create_stack_node(row, column, val);
    new_top->next = stack->top;
    stack->top = new_top;
}

StackNode* pop(Stack *stack) { /*Remember(for Tslil): free the node somewhere after using it*/
    if (is_empty_stack(stack)) {
        return NULL;
    }

    StackNode *res_node = top(stack);
    stack->top = stack->top->next;
    return res_node;
}

StackNode* top(Stack *stack) {
    return stack->top;
}

bool is_empty_stack(Stack *stack) {
    return (top(stack) == NULL);
}

void destroy_stack_node(StackNode *node) {
    free(node);
}

void destroy_stack(Stack *stack) {
    StackNode *node;
    while (!is_empty_stack(stack)) {
        node = pop(stack);
        destroy_stack_node(node);
    }
    free(stack);
}
