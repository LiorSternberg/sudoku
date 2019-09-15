#ifndef FINAL_PROJECT_STACK_H
#define FINAL_PROJECT_STACK_H

#include <stdbool.h>

/** Stack:
 *
 *  The component is used to manage pseudo-recursive calls in the
 *  Backtracking algorithm. It's a generic stack that supports pop, push
 *  and top. The stack nodes are specific to the Backtracking algorithm
 *  requirements.
 */

typedef struct StackNode_ {
    int row;
    int column;
    int val;
    struct StackNode_ *next;
} StackNode;

typedef struct{
    StackNode *top;
} Stack;

/**
 * Creates a new empty stack.
 * @return: the new stack that was created.
 */
Stack* create_stack();

/**
 * Creates a new stack node.
 * @param row: the row to pass to the stack node.
 * @param column: the column to pass to the stack node.
 * @param val: the value to pass to the stack node.
 * @return: the new stack node that was created.
 */
StackNode* create_stack_node(int row, int column, int val);

/**
 * Pushes a new node to the stack.
 * @param row: the row to pass to the stack node.
 * @param column: the column to pass to the stack node.
 * @param val: the value to pass to the stack node.
 * @param stack: the stack to push the new node to.
 */
void push(int row, int column, int val, Stack *stack);

/**
 * Removes the top node of the stack, and returns it.
 * @param stack: the stack to remove the top node from.
 * @return: the removed node.
 */
StackNode* pop(Stack *stack);

/**
 * Peeks at the top node of the stack, without removing it.
 * @param stack: the stack to get the top node of.
 * @return: a pointer to the top node of the given stack.
 */
StackNode* top(Stack *stack);

/**
 * Checks if the stack is empty.
 * @param stack: the stack to be checked.
 * @return: true if the stack is empty, and false if it isn't.
 */
bool is_stack_empty(Stack *stack);

/**
 * Destroys the given stack node (frees all related memory).
 * @param node: the node to be destroyed.
 */
void destroy_stack_node(StackNode *node);

/**
 * Destroys the given stack (frees all related memory).
 * @param stack: the stack to be destroyed.
 */
void destroy_stack(Stack *stack);

#endif
