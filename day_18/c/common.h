#ifndef COMMON_H
#define COMMON_H

#define NEED_SLICE
#include "../../shared/c/shared.h"

int hex_to_int(char ch) {
    switch (ch)
    {
        case 'a': 
            return 10; 
        case 'b': 
            return 11; 
        case 'c': 
            return 12; 
        case 'd': 
            return 13; 
        case 'e': 
            return 14; 
        case 'f': 
            return 15; 
        default:
            return ch - '0';
    }
    return -1;
}

#endif /* COMMON_H */
