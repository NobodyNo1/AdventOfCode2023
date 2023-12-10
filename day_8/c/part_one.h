#ifndef PART_ONE
#define PART_ONE

#include "common.h"

void partOne(void) {


    // |left,right|
    int* data = (int*) calloc(MAX_COMBINATION*2, sizeof(int));
    int* navigation = (int*) malloc(MAX_COMBINATION*sizeof(int));
    // for(int i = 0; i < MAX_COMBINATION; ++i){
    //     data[2*i] = 0;
    //     data[2*i+1] = 0;
    //     navigation[i] = -1;
    // }
    FILE* filePtr = fopen("test_input.txt", "r");
    

    int i = 0;
    int ch;
    // Read instructions
    while( (ch = getc(filePtr)) != EOF ) {
        if(ch == 'L'){
            navigation[i] = 0;
            i++; continue;
        }
        if(ch == 'R'){
            navigation[i] = 1;
            i++; continue;
        }
        if(ch == '\n') {
            break;
        }
    }
    int navSize = i;
    // printf("nav size: %d\n", i);
    //skip new line
    while( (ch = getc(filePtr)) == '\n' ) {

    }
    int idx = -1;
    bool isLeft = true;
    int currentValue = ch-'A';
    int ordinal = 0;
    while( (ch = getc(filePtr)) != EOF) {
        if('A' <= ch && ch <= 'Z') {
            if(currentValue == -1) currentValue = 1;
            //hash
            switch (ordinal)
            {
            case 0:
                currentValue = (ch - 'A') * 26 * 26; 
                break;
            case 1:
                currentValue += (ch - 'A') * 26;
                break;
            case 2:
                currentValue += (ch - 'A');
                break;
            default:
                break;
            }
            ordinal++;
        } else if(currentValue != -1) {
            
            if(idx == -1) {
                idx = currentValue;
                // printf("%d = ", idx);
            } else {
                if(isLeft) {
                    data[2*idx] = currentValue;
                    // printf("(%d, ", currentValue);
                    isLeft = false;
                } else {
                    data[2*idx + 1] = currentValue;
                    // printf(" %d)\n", currentValue);
                }
            }
            ordinal = 0;
            currentValue = -1;
        }
        if('\n' == ch) {
            ordinal = 0;
            idx = -1;
            isLeft = true;
            currentValue = -1;
            continue;
        }
    }
    long steps = 0;
    int position = AAA;
    while(position != ZZZ){
        // printf("steps:%d\n", steps);
        // printf("position:%d\n", position);
        int i = steps%navSize;
        position = data[2*position+navigation[i]];
        if(position == ZZZ){
            break;
        }
        steps++;
    }
    printf("PART ONE: %ld\n", steps+1);
    fclose(filePtr);
}

#endif /* PART_ONE */
