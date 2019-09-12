#ifndef FINAL_PROJECT_RANDOM_H
#define FINAL_PROJECT_RANDOM_H

void initialize_random();

/* Get a random index between 0 and limit */
int get_rand_index(int limit);

/* Shuffles the first <size_to_shuffle> indices of an array of size <total_size> */
void shuffle(int *array, int size_to_shuffle, int total_size);

#endif
