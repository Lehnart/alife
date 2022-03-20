#ifndef ALIFE_ARRAY_H
#define ALIFE_ARRAY_H

typedef struct array{
    unsigned int size;
    unsigned int memory_size;
    void **data_array;
} Array;

Array *array_new(unsigned int size);

void* array_get(const Array *array, unsigned int index);

void array_set(Array *array, unsigned int index, void *data);

void array_append(Array *array, void *data);

void array_clear(Array *array);

#endif //ALIFE_ARRAY_H
