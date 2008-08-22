/**
 * Coin3dTools
 * ------------
 * Copyright (c)2007 Daniel Fiser <danfis (at) danfis (dot) cz>
 *
 *
 * This file is part of Coin3dTools
 *
 * Coin3dTools is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Coin3dTools is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Coin3dTools.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _SVT_UTILS_H_
#define _SVT_UTILS_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

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
                (long int)size);
        exit(-1);
    }

    return ret;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
