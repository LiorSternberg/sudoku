#include <time.h>
#include <stdlib.h>
#include "random.h"

void initialize_random() {
    srand((unsigned int) time(NULL));

}

int get_rand_index(int limit) {
    return rand() % limit;
}

void shuffle(int *array, int size_to_shuffle, int total_size) {
    int i, rand_index, temp;

    for (i = 0; i < size_to_shuffle; i++) {
        rand_index = get_rand_index(total_size);
        temp = array[i];
        array[i] = array[rand_index];
        array[rand_index] = temp;
    }
}

int weighted_random_choice(double *weights, int size) {
    double sum = 0.0, rand_value = ((double) rand()) / RAND_MAX;
    int i;

    for (i = 0; i < size; i++) {
        sum += weights[i];
        if (rand_value <= sum) {
            return i;
        }
    }
    return size-1;
}

int weighted_random_choice_with_threshold(double *weights, int size, double threshold) {
    double sum = 0.0;
    int i;

    for (i = 0; i < size; i++) {
        if (weights[i] >= threshold) {
            sum += weights[i];
        }
    }
    if (sum == 0.0) {
        return ERROR_VALUE;
    }

    for (i = 0; i < size; i++) {
        if (weights[i] >= threshold) {
            weights[i] = weights[i] / sum;
        } else {
            weights[i] = 0.0;
        }
    }
    return weighted_random_choice(weights, size);
}

