#ifndef SLICE_H
#define SLICE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DEFAULT_CAPACITY 20

typedef struct
{
    int capacity;
    size_t size;
    void** data;
} Slice;

#define for_slice(slice, element)               \
    void* element = 1;                          \
    for (size_t _i = 0; _i < (slice)->size && ((element) = (slice)->data[_i]); _i++)

Slice create_slice(int initialCapacity) {
    return (Slice) {
        initialCapacity,
        0,
        (void**) malloc(initialCapacity * sizeof(void*))
    };
}


Slice* copy_slice(Slice slice) {
    Slice* new_slice = (Slice*) malloc(sizeof(Slice));
    new_slice->capacity = slice;
    new_slice->data = slice.data;
    new_slice->size = slice.size;
    return new_slice;
}

// Make sure that size of data is less than 8 bytes
void add_item(Slice* slice, void* data) {
    // if(sizeof(data) > sizeof(void*)) {
    //     printf("can't fit data, please allocate and put pointer to data");
    //     return;
    // }
    if(slice->capacity <= slice->size) {
        int cap = slice->capacity;
        slice->capacity += slice->capacity/2;
        // printf("grow cap: %d -> %d \n", cap, slice->capacity);
        slice->data = (void**) realloc(slice->data, slice->capacity * sizeof(void*));
    }
    slice->data[slice->size] = data;
    slice->size++;
}

bool contains(Slice* slice, void* data) {
    for (size_t i = 0; i < slice->size; i++)
    {
        if(slice->data[i] == data) return true;
    }
    return false;
}

void clean_content(Slice* slice) {
    slice->size = 0;
}

#endif /* SLICE_H */
