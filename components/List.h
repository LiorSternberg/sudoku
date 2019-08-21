#include <stdbool.h>

#ifndef FINAL_PROJECT_DLLIST_H
#define FINAL_PROJECT_DLLIST_H


typedef struct Node Node;


typedef struct {
    Node *head;
    Node *end;
} List;


List* create_list();

int destroy_list(List *list);

void add(List *list, void *item);

void clear_list(List *list);

void* remove_last(List *list);

bool has_next(List *list);

int next(List *list);

bool has_prev(List *list);

int prev(List *list);

bool is_empty(List *list);


#endif
