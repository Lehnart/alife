#include <malloc.h>
#include <string.h>
#include "array.h"

/**
 * Allocate a new array.
 * @param size initial size of the array
 * @return the newly allocated array
 */
Array *array_new(unsigned int size) {
    Array *array = malloc(sizeof(Array));
    array->size = size;
    array->memory_size = size > 0 ? size : 1;
    array->data_array = malloc(size * sizeof(void *));
    return array;
}

/**
 * Get the element at the given index. If the index is invalid, NULL is returned.
 * @param array
 * @param index
 * @return element at the given index
 */
void *array_get(const Array *array, unsigned int index) {
    if (index >= array->size) {
        return NULL;
    }

    return array->data_array[index];
}

/**
 * Set the element at the given index. If the index is invalid, nothing is done.
 * @param array
 * @param index
 * @param data
 */
void array_set(Array *array, unsigned int index, void *data) {
    if (index >= array->size) {
        return;
    }
    array->data_array[index] = data;
}

/**
 * Append an element at the end of the array. If needed, memory is allocated.
 * @param array
 * @param index
 * @param data
 */
void array_append(Array *array, void *data) {
    if (array->size + 1 > array->memory_size) {
        void **new_data_array = malloc(2 * array->memory_size * sizeof(void *));
        memcpy(new_data_array, array->data_array, array->size * sizeof(void *));
        free(array->data_array);
        array->data_array = new_data_array;
        array->memory_size *= 2;
    }

    array->size++;
    array->data_array[array->size - 1] = data;
}

/**
 * Clear the array, not freeing element memories.
 * @param array
 */
void array_clear(Array *array) {
    array->size = 0;
}