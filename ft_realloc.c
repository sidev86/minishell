#include "minishell.h"
#include <stdlib.h>
#include <malloc.h>

void *ft_realloc(void *ptr, size_t newSize) {
    if (newSize == 0) {
        free(ptr);
        return NULL;
    }

    void *newPtr = malloc(newSize);

    if (newPtr) {
        size_t oldSize = malloc_usable_size(ptr);
        size_t copySize = oldSize < newSize ? oldSize : newSize;
        ft_memcpy(newPtr, ptr, copySize);
        free(ptr);
    }

    return newPtr;
}

