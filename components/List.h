#include <stdbool.h>

#ifndef FINAL_PROJECT_DLLIST_H
#define FINAL_PROJECT_DLLIST_H

/** List:
 *
 *  The component is a generic implementation of a doubly-linked-list.
 *  It is used as the main data type in the StatesList, and Move components.
 *  Also used in the Board component to maintain the lists of neighbors, and
 *  of conflicting cells.
 */

typedef struct Node Node;


typedef struct {
    Node *head;
    Node *end;
} List;

/**
 * Creates a new empty list.
 * @return: the list that was created.
 */
List* create_list();

/**
 * Destroys the given list (frees all related memory). Note that the list
 * must be empty before it is destroyed.
 * @param list: the list to destroy.
 * @return: success_code. 0 means the list was destroyed successfully, and 1
 * means an error occurred (for example if the list wasn't empty).
 */
int destroy_list(List *list);

/**
 * Adds a node to the end of the list, with the given item.
 * @param list: the list to add the item to.
 * @param item: the item to add to the list.
 */
void add(List *list, void *item);

/**
 * Clears the given list. Note that this does not handle freeing the memory of
 * the items in the list, or modify them in any way.
 * @param list: the list to clear.
 */
void clear_list(List *list);

/**
 * Removes the last node of the list, and returns it's item.
 * @param list: the list to remove the last node from.
 * @return: the item of the last node of the list.
 */
void* remove_last(List *list);

/**
 * Deletes nodes with the specified item.
 * May change the order of the list. resets the head.
 * @param list: the list to delete all matching nodes from.
 * @param item: the item of which to delete all related nodes.
 */
void delete(List *list, void *item);

/**
 * Checks if the list has another item after the current item.
 * @param list: the list to check.
 * @return: true if there is a next item, and false otherwise.
 */
bool has_next(List *list);

/**
 * Updates the list's head to the next item on the list.
 * @param list: the list to update.
 * @return: success_code. 0 means the list was updated successfully, and 1
 * means an error occurred (for example, there isn't a next node)
 */
int next(List *list);

/**
 * Checks if the list has another item before the current item.
 * @param list: the list to check.
 * @return: true if there is a previous item, and false otherwise.
 */
bool has_prev(List *list);

/**
 * Updates the list's head to the previous item on the list.
 * @param list: the list to update.
 * @return: success_code. 0 means the list was updated successfully, and 1
 * means an error occurred (for example, there isn't a previous node)
 */
int prev(List *list);

/**
 * Returns the current item on the list (of the node pointed to by the head).
 * @param list: the list to get the current item from.
 * @return: the current item.
 */
void* get_current_item(List *list);

/**
 * Resets the head of the list to the first item on the list.
 * @param list: the list to reset the head of.
 */
void reset_head(List *list);

/**
 * Checks if the list is empty.
 * @param list: the list to check.
 * @return: true if the list is empty, and false otherwise.
 */
bool is_empty(List *list);


#endif
