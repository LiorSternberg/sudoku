#ifndef HW3_MEMORYERROR_H
#define HW3_MEMORYERROR_H

/* MemoryError:
 *
 * Handles failed dynamic memory allocations.
 * */


/* Alert of a failed memory allocation, and exit */
void report_memory_allocation_error(char* function_name);

/* Validate that a memory allocation was successful. If not, report failure */
void validate_memory_allocation(char* function_name, void *p);

#endif
