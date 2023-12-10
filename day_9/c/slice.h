#ifndef SLICE_H
#define SLICE_H

#include <stdlib.h>

typedef struct
{
    int capacity;
    size_t size;
    void** data;
} Slice;

Slice create_slice(int initialCapacity) {
    return (Slice) {
        initialCapacity,
        0,
        (void**) malloc(initialCapacity * sizeof(void*))
    };
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
        printf("grow cap: %d -> %d \n", cap, slice->capacity);
        slice->data = (void**) realloc(slice->data, slice->capacity * sizeof(void*));
    }
    slice->data[slice->size] = data;
    slice->size++;
}

void clean_content(Slice* slice) {
    slice->size = 0;
}

#endif /* SLICE_H */
