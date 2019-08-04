#include "StatesList.h"

#include <stdio.h>
#include <stdlib.h>

StatesList* create_list() {
    StatesList* states = malloc(sizeof(StatesList));
    states->head = NULL;
    states->end = NULL;
    return states;
}

int destroy_list(StatesList* states) {
    if (states->end != NULL || states->head != NULL) {
        return 1;
    }

    free(states);
    return 0;
}

void add(StatesList* states, Board* board) {
    State* state = malloc(sizeof(State));

    state->board = board;
    state->prev = states->end;
    state->next = NULL;

    states->end = state;
}

void delete_last(StatesList* states) {
    State* last = states->end;
    if (last == NULL) {
        return;
    }

    /* move end to prev */
    states->end = last->prev;
    states->end->next = NULL;

    /* delete last state */
    free_board_resources(last->board);
    free(last->board);
    free(last);
}


int next(StatesList* states) {
    /* Check if there is a next state, if not return exit status 1 */
    if (states->head == NULL || states->head->next == NULL) {
        return 1;
    }

    states->head = states->head->next;
    return 0;
}

int prev(StatesList* states) {
    /* Check if there is a previous state, if not return exit status 1 */
    if (states->head == NULL || states->head->prev== NULL) {
        return 1;
    }

    states->head = states->head->prev;
    return 0;
}

void clear_all(StatesList* states) {
    while (states->end != NULL) {
        delete_last(states);
    }
}

void clear_next(StatesList* states) {
    while (states->end != states->head) {
        delete_last(states);
    }
}

