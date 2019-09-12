#include <time.h>
#include <stdlib.h>
#include "random.h"

void initialize_random() {
    srand((unsigned int) time(NULL));

}

/* Get a random index between 0 and limit */
int get_rand_index(int limit) {
    return rand() % limit;
}

/* Shuffles the first <size_to_shuffle> indices of an array of size <total_size> */
void shuffle(int *array, int size_to_shuffle, int total_size) {
    int i, rand_index, temp;

    for (i = 0; i < size_to_shuffle; i++) {
        rand_index = get_rand_index(total_size);
        temp = array[i];
        array[i] = array[rand_index];
        array[rand_index] = temp;
    }
}
