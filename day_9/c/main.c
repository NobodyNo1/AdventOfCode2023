#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "slice.h"
#include "test.h"
#include "math.h"

#define DEBUG 0

#define INITIAL_SIZE_SLICE 100
void solve(int part);

//test only
void print_slice(Slice* slice) {
    for (size_t i = 0; i < slice->size; i++)
    {
        printf("%d ", slice->data[i]);
    }
    printf("\n");
}

void print_slice_last(Slice* slice, int last) {
    for (size_t i = slice->size-last; i < slice->size; i++)
    {
        printf("%d ", slice->data[i]);
    }
    // printf("\n");
}
int main(void) {
    solve(1);
    solve(2);
    return 0;
}

void find_prev_number(Slice* slice) {
    Slice diffSlice = create_slice(INITIAL_SIZE_SLICE);
    bool is_all_zeros = true;
    long prevSize = slice->size;
    // should have empty item in front
    add_item(&diffSlice, 0);
    // should start with 1
    for (size_t i = 1; i < slice->size - 1; i++)
    {
        long next = slice->data[i+1];
        long this = slice->data[i];
        // long diff = next > this ? next - this : this - next;
        long diff = next - this;
        if (is_all_zeros && diff != 0){
            is_all_zeros = false;
        }
        add_item(&diffSlice, diff);
    }
    if(!is_all_zeros) {
#if DEBUG
        print_slice(&diffSlice);
#endif
        find_prev_number(&diffSlice);
#if DEBUG
        print_slice(&diffSlice);
#endif
    }
    long to_subtract = diffSlice.data[0];
    // calc next
    slice->data[0] = slice->data[1] - to_subtract;
    return;
}

void find_next_number(Slice* slice) {
    Slice diffSlice = create_slice(INITIAL_SIZE_SLICE);
    bool is_all_zeros = true;
    long prevSize = slice->size;
    for (size_t i = 0; i < slice->size - 1; i++)
    {
        long next = slice->data[i+1];
        long this = slice->data[i];
        // long diff = next > this ? next - this : this - next;
        long diff = next - this;
        if (is_all_zeros && diff != 0){
            is_all_zeros = false;
        }
        add_item(&diffSlice, diff);
    }
    if(!is_all_zeros) {
#if DEBUG
        print_slice(&diffSlice);
#endif
        find_next_number(&diffSlice);
#if DEBUG
        print_slice(&diffSlice);
#endif
    }
    long toAdd = diffSlice.data[slice->size-1];
    // calc next
    add_item(slice, slice->data[slice->size-1] + toAdd);
    return;
}

void solve(int part) {
    FILE* filePtr = fopen("input.txt", "r");
    Slice slice = create_slice(INITIAL_SIZE_SLICE);
    long result = 0;
    int ch;
    long current_number = -1;
    int sign = 1;
    if(part == 2) {
        // add empty item in front
         add_item(&slice, 0);
    }
#if DEBUG
    int idX = 0;
#endif
    while((ch = getc(filePtr)) != EOF) {
        if('-' == ch) {
            sign = -1;
        }
        if ('0' <= ch && ch <= '9')
        {
            if (current_number == -1) current_number = 0;
            current_number = current_number*10 + (ch - '0');
        } else {
            if(current_number != -1){
                add_item(&slice, sign == 1 ? current_number : -current_number);
                sign = 1;
                current_number = -1;
            }
        }
        
        if(ch == '\n') {
            sign = 1;
            current_number = -1;
#if DEBUG
            printf("IDX: %d\n", idX++);
            print_slice(&slice);
#else
            // print_slice_last(&slice,3);
#endif
            long newNumb = 0l;
            if(part == 1){
                find_next_number(&slice);
                newNumb = slice.data[slice.size-1];
                clean_content(&slice);
            } else{
                find_prev_number(&slice);
                newNumb = slice.data[0];
                clean_content(&slice);
                // add empty first item
                add_item(&slice, 0);
            }
            // printf(" [%d] \n", newNumb);
            result += newNumb;
        }
    }
    if(current_number!= -1) {
        add_item(&slice, sign == 1 ? current_number : -current_number);
        // print_slice_last(&slice,3);
        long newNumb = 0l;
        if(part == 1){
            find_next_number(&slice);
            newNumb = slice.data[slice.size-1];
        } else{
            find_prev_number(&slice);
            newNumb = slice.data[0];
        }
        // printf(" [%ld] \n", newNumb);
        clean_content(&slice);
        result += newNumb;
    }
    printf("RESULT: %ld\n", result);
}