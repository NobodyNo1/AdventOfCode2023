#ifndef COMMON_H
#define COMMON_H

#define NEED_SLICE
#include "../../shared/c/shared.h"



typedef struct {
    Slice* slice;
    int start;
    int end; 
} Queue;

Queue create_queue() {
    Queue queue = {
        new_slice(100),
        0,
        0
    };
    return queue;
}

int queue_size(Queue* queue) {
    return queue->end - queue -> start;
}

void* pop_front(Queue* queue) {
    queue->start++;
    return queue->slice->data[queue->start-1];
}

void push_back(Queue* queue, void* data) {
    queue->end++;
    add_item(queue->slice, data);
}


#endif /* COMMON_H */
