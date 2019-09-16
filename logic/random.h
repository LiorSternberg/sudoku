#ifndef FINAL_PROJECT_RANDOM_H
#define FINAL_PROJECT_RANDOM_H

#define ERROR_VALUE (-1)

/**
 * Initializes the random module (sets a seed).
 */
void initialize_random();

/**
 * Get a random index between 0 and limit.
 * @param limit: the limit of the random int range.
 * @return: random index between 0 and limit.
 */
int get_rand_index(int limit);

/**
 * Shuffles the first <size_to_shuffle> indices of an array of size <total_size>
 * @param array: the array to shuffle.
 * @param size_to_shuffle: the number of indices to shuffle (from the start of
 * the array).
 * @param total_size: the total size of the array (with values available for
 * shuffling).
 */
void shuffle(int *array, int size_to_shuffle, int total_size);

/**
 * Chooses an index of the array (between 0 and size-1), based on the weights.
 * For example, the array {0.1, 0.3, 0.6} means the index 2 is twice more likely
 * to be picked than the index 1 (it's 6 to 3), and the index 1 is 3 times
 * more likely to be picked than the index 0 (it's 3 to 1).
 * Note: the weights must sum up to 1. Otherwise behavior is not defined.
 * @param weights: an array of weights for the indices. Must sum up to 1.
 * @param size: the size of the weights array.
 * @return: the chosen index.
 */
int weighted_random_choice(double *weights, int size);

/**
 * Choose an index of the array (between 0 and size-1), based on the weights, and only
 * consider indices where the weight is over the threshold.
 * @param weights: array of weights that sum up to 1.0.
 * @param size: the size of the array.
 * @param threshold: the threshold value (between 0.0 and 1.0).
 * @return the chosen index of the array. if no index is above the threshold -1 is returned.
 */
int weighted_random_choice_with_threshold(double *weights, int size, double threshold);

#endif
