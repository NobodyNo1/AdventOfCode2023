#ifndef COMMON_H
#define COMMON_H
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    // hex representation of hand
    int handHex;
    // type of combo
    // int handType;
    // price
    int handPrice;
} HandInfo;

int compare_function(const void *a,const void *b) {
    HandInfo *x = (HandInfo *) a;
    HandInfo *y = (HandInfo *) b;
    return x->handHex - y->handHex;
}


#define CART_TYPE_COUNT       13
#define HAND_SIZE             5
#define FIVE_PAIR_HAND_TYPE   6
#define HAND_TYPE_SIZE        7 // FIVE_PAIR_HAND_TYPE+1

//TODO: define dynamically?
#define BUFFER_SIZE 1000

#endif /* COMMON_H */
