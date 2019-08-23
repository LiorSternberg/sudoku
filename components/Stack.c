//
// Created by USER on 23/08/2019.
//
#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

Stack* create_stack(){
    Stack *stack = (Stack)malloc(sizeof(Stack));
    validate_memory_allocation("create_stack", stack);
    stack->top = NULL;
    return stack;
}

StackNode* create_stack_node(int i, int j, int val){
    StackNode *stack_node = (StackNode)malloc(sizeof(StackNode));
    validate_memory_allocation("create_stack_node", stack_node);
    stack->top = NULL;
    return stack;
}

void push(int i, int j, int val, Stack *stack){
    StackNode *new_top = create_stack_node(i, j, val);
    new_top->next = stack->top;
    stack->top = new_top;
}

StackNode pop(Stack *stack){ /*Remember(for Tslil): free the node somewhere after using it*/
    StackNode res_node = stack->top;
    stack->top = stack->top->next;
    return res_node;
}

StackNode top(Stack *stack){
    return stack->top;
}

bool is_empty_stack(Stack *stack){
    return (stack->top == NULL);
}

void destroy_stack_node(StackNode *node){
    free(node);
}

void destroy_stack(Stack *stack){
    StackNode *node;
    while (stack->top != NULL){
        node = pop(stack);
        free(node);
    }
    free(stack);
}
