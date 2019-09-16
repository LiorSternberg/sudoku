#ifndef HW3_MEMORYERROR_H
#define HW3_MEMORYERROR_H

/** MemoryError:
 *
 * Handles failed dynamic memory allocations.
 * */


/**
 * Validates that a memory allocation was successful. If not, reports failure,
 * and exits with error code 1.
 * @param function_name: the name of the function where the memory allocation
 * was attempted.
 * @param p: the pointer to the alleged allocated memory.
 */
void validate_memory_allocation(char *function_name, void *p);

#endif
