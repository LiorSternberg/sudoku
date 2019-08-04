#include <stdio.h>
#include <stdlib.h>

#include "List.h"

struct Node {
    void *item;
    Node *next;
    Node *prev;
};


List* create_list() {
    List *list = malloc(sizeof(List));
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
    Node *node = malloc(sizeof(Node));

    node->item = item;
    node->prev = list->end;
    node->next = NULL;

    list->end = node;
}

void* remove_last(List *list) {
    Node *last = list->end;
    void *item;

    if (last == NULL) {
        return NULL;
    }

    /* move end to prev */
    list->end = last->prev;
    list->end->next = NULL;

    /* pop last node */
    item = last->item;
    free(last);
    return item;
}


int next(List *list) {
    /* Check if there is a next node, if not return exit status 1 */
    if (list->head == NULL || list->head->next == NULL) {
        return 1;
    }

    list->head = list->head->next;
    return 0;
}

int prev(List *list) {
    /* Check if there is a previous node, if not return exit status 1 */
    if (list->head == NULL || list->head->prev== NULL) {
        return 1;
    }

    list->head = list->head->prev;
    return 0;
}