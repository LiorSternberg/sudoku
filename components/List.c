#include <stdio.h>
#include <stdlib.h>

#include "List.h"
#include "../MemoryError.h"

struct Node {
    void *item;
    Node *next;
    Node *prev;
};


List* create_list() {
    List *list = malloc(sizeof(List));
    validate_memory_allocation("create_list", list);

    list->head = NULL;
    list->end = NULL;
    return list;
}

int destroy_list(List *list) {
    if (list->end != NULL || list->head != NULL) {
        return 1;
    }

    free(list);
    return 0;
}

void add(List *list, void *item) {
    if (item == NULL) {
        return;
    }

    Node *node = malloc(sizeof(Node));
    validate_memory_allocation("List -> add", node);

    node->item = item;
    node->prev = list->end;
    node->next = NULL;

    if (is_empty(list)) {
        list->head = node;
    } else {
        list->end->next = node;
    }

    list->end = node;

}

void clear_list(List *list) {
    while (remove_last(list) != NULL);
}

void* remove_last(List *list) {
    Node *last = list->end;
    void *item;

    if (last == NULL) {
        return NULL;
    }

    /* move end to prev */
    list->end = last->prev;
    if (list->end != NULL) {
        list->end->next = NULL;
    }

    /* pop last node */
    item = last->item;
    free(last);
    return item;
}

bool has_next(List *list) {
    return (list->head != NULL && list->head->next != NULL);
}

int next(List *list) {
    /* Check if there is a next node, if not return exit status 1 */
    if (has_next(list) == false) {
        return 1;
    }

    list->head = list->head->next;
    return 0;
}

bool has_prev(List *list) {
    return (list->head != NULL && list->head->prev != NULL);
}

int prev(List *list) {
    /* Check if there is a previous node, if not return exit status 1 */
    if (has_prev(list) == false) {
        return 1;
    }

    list->head = list->head->prev;
    return 0;
}

bool is_empty(List *list) {
    return list->end == NULL;
}
