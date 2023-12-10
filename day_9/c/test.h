#ifndef TEST_H
#define TEST_H

#include "slice.h"

void test_parser() {
    FILE* filePtr = fopen("input.txt", "r");
    long result = 0;
    int ch;
    long current_number = -1;
    int sign = 1;
     while((ch = getc(filePtr)) != EOF) {
        if('-' == ch) {
            sign = -1;
        }
        if ('0' <= ch && ch <= '9')
        {
            if (current_number == -1) current_number = 0;
            current_number = current_number*10 + (ch - '0');
        } else {
            if(current_number!= -1){
                printf("%ld ,", sign*current_number);
                sign = 1;
                current_number = -1;
            }
        }
    }
    return;
}

void test_slice(void) {
    Slice slice = create_slice(10);

    long long test = 8223372036854775807;
    for(int i = 0; i< 10; i++){
        add_item(&slice, test);
    }

    for(int i = 0; i< 10; i++){
        long data = slice.data[i];
        printf("l: %ld", data);
    }
}

void test(void) {
    test_parser();
}

#endif