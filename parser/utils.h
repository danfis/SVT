#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdlib.h>
#include <stdio.h>

/* Memory allocation: */
#define _ALLOC_MEMORY(type, ptr_old, size) \
    (type *)xrealloc((void *)ptr_old, (size))

/**
 * Allocate memory for one element of type.
 */
#define ALLOC(type) \
    _ALLOC_MEMORY(type, NULL, sizeof(type))

/**
 * Allocate memory for array of elements of type type.
 */
#define ALLOC_ARR(type, num_elements) \
    _ALLOC_MEMORY(type, NULL, sizeof(type) * (num_elements))

/**
 * Reallocate memory of array.
 */
#define REALLOC_ARR(type, old, num_elements) \
    _ALLOC_MEMORY(type, (old), sizeof(type) * (num_elements))


static void *xrealloc(void *ptr, size_t size)
{
    void *ret = realloc(ptr, size);
    if (ret == NULL && size != 0){
        fprintf(stderr, "Allocation of memory of size %ld failed, exiting...",
                size);
        exit(-1);
    }

    return ret;
}
#endif
