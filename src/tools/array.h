#ifndef ALIFE_ARRAY_H
#define ALIFE_ARRAY_H

/**
 * Dynamic array data structure.
 * Each element is a void*.
 */
typedef struct Array{
    unsigned int size;          // Number of element present in array
    unsigned int memory_size;   // Number of memory block allocated for element
    void **data_array;          // Pointer to array
} Array;

Array*      array_new       (unsigned int size);
void*       array_get       (const Array *array, unsigned int index);
void        array_set       (Array *array, unsigned int index, void *data);
void        array_append    (Array *array, void *data);
void        array_clear     (Array *array);

#endif //ALIFE_ARRAY_H
