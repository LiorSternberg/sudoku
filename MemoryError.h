#ifndef HW3_MEMORYERROR_H
#define HW3_MEMORYERROR_H

/* MemoryError:
 *
 * Handles failed dynamic memory allocations.
 * */


/* Validate that a memory allocation was successful. If not, report failure */
void validate_memory_allocation(char *function_name, void *p);

#endif
