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
    new_slice->capacity = slice.capacity;
    new_slice->data = slice.data;
    new_slice->size = slice.size;
    return new_slice;
}

Slice* new_slice(int initialCapacity) {
    Slice* new_slice = (Slice*) malloc(sizeof(Slice));
    new_slice->capacity = initialCapacity;
    new_slice->data = (void**) malloc(initialCapacity * sizeof(void*));
    new_slice->size = 0;
    return new_slice;
}

// Make sure that size of data is less than 8 bytes
void add_item(Slice* slice, void* data) {
    // if(sizeof(data) > sizeof(void*)) {
    //     printf("can't fit data, please allocate and put pointer to data");
    //     return;
    // }
    // printf("cap: %d, ", slice->capacity);
    // printf("size: %d\n",slice->size);
    if(slice->capacity <= slice->size) {
        int cap = slice->capacity;
        slice->capacity += slice->capacity/2;
        // printf("grow cap: %d -> %d \n", cap, slice->capacity);
        slice->data = (void**) realloc(slice->data, slice->capacity * sizeof(void*));
    }
    // printf("Put data\n");
    slice->data[slice->size] = data;
    // printf("Increase size\n");
    slice->size++;
    // printf("Done\n");
}

void remove_item(Slice* slice, void* data) {
    if(slice->size <= 0) {
        return;
    }
    int i = 0;
    while(i < slice->size) {
        if(slice->data[i] == data) break;
        i++;
    }
    if(i == slice->size) return;
    for(int j = i; j < slice->size-1; j++){
        slice->data[j] = slice->data[j+1]; 
    }
    slice->size -= 1;
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
