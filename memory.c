#include "shell.h"

/**
 * deallocate - releases memory pointed to by a pointer and sets it to NULL
 * @pointer: address of the pointer to deallocate
 *
 * Returns 1 if deallocation was successful, else returns 0.
 */
int deallocate(void **pointer)
{
    if (pointer && *pointer)
    {
        free(*pointer);
        *pointer = NULL;
        return (1);
    }
    return (0);
}
