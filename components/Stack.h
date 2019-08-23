//
// Created by USER on 23/08/2019.
//

#ifndef FINAL_PROJECT_STACK_H
#define FINAL_PROJECT_STACK_H

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

#endif
