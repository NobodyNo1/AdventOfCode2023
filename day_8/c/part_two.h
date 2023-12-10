#ifndef PART_TWO
#define PART_TWO

#define END_A 26*26
#define A_SIZE END_A + 1
#define START_Z 25*26*26

#include "common.h"
#include <stdio.h>

// Function to find the GCD (Greatest Common Divisor)
long findGCD(long a, long b) {
    while (b != 0) {
        long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to find the LCM (Least Common Multiple)
long findLCM(long a, long b) {
    // return (a * b) / findGCD(a, b);
    long pp = a*b;
    return (pp) / findGCD(a, b);
}

// Function to find the LCM of an array of numbers
long findLCMArray(long* arr, int n) {
    long lcm = arr[0];

    for (int i = 1; i < n; ++i) {
        lcm = findLCM(lcm, arr[i]);
    }

    return lcm;
}

void partTwo(void) {


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
    int currentValue = ch - 'A';
    int ordinal = 1;
    int* startA = (int*) calloc(A_SIZE, sizeof(int));
    int idxStartA = 0;
    while( (ch = getc(filePtr)) != EOF) {
        if('A' <= ch && ch <= 'Z') {
            
            if(currentValue == -1) currentValue = 1;
            //hash
            switch (ordinal)
            {
            case 0:
                currentValue = (ch - 'A');      
                break;
            case 1:
                currentValue += (ch - 'A') * 26; 
                break;
            case 2:
                currentValue += (ch - 'A') * 26 * 26;
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
            if(idx >= 0 && idx < A_SIZE){
             
                // printf("%d = ", idx);
                // int a = idx%26;
                // int b = (idx/26)%26;
                // int c = (idx/26)/26;
                // putchar(a+'A');
                // putchar(b+'A');
                // putchar(c+'A');
                // printf(" : %d, %d, %d \n", a,b,c); 
                startA[idxStartA] = idx;
                idxStartA++;
            }
            // if(idx >= START_Z){
            //     printf("%d = ", idx);
            //     int a = idx%26;
            //     int b = (idx/26)%26;
            //     int c = (idx/26)/26;
            //     putchar(a+'A');
            //     putchar(b+'A');
            //     putchar(c+'A');
            //     printf(" : %d, %d, %d \n", a,b,c); 
            // }
            ordinal = 0;
            idx = -1;
            isLeft = true;
            currentValue = -1;
            continue;
        }
    }

    long steps = 0;

    
    // for(int i = 0; i < idxStartA; ++i) {
    //     printf("%d = ", startA[i]);
    //     int a = startA[i]%26;
    //     int b = (startA[i]/26)%26;
    //     int c = (startA[i]/26)/26;
    //     putchar(a+'A');
    //     putchar(b+'A');
    //     putchar(c+'A');
    //     printf(" : %d, %d, %d \n", a,b,c); 
    // }
    // return;

    int sizeStartA = idxStartA;
    //int* positions = (int*) calloc(sizeStartA, sizeof(int));
    int* positions = startA;

    // while (true)
    // {
    //      //14616363770447
            //140524718676288
    //     int navIdx = steps%navSize;
    //     bool isAllEnd = true;
    //     for(int i = 0; i < idxStartA; ++i) {
    //         positions[i] =  data[2*positions[i]+navigation[navIdx]];
    //         if(positions[i] < START_Z) {
    //             isAllEnd = false;
    //         }
    //     }
    //     if(isAllEnd){
    //         break;
    //     }
    //     steps++;
    // }
    long* res = (long*) malloc(idxStartA*sizeof(long));
    for(int p = 0; p < idxStartA; ++p) {
        steps = 0;
        while(true) {
            // printf("steps:%d\n", steps);
            // printf("position:%d\n", position);
            int i = steps%navSize;
            positions[p] = data[2*positions[p]+navigation[i]];
            if(positions[p] >= START_Z){
                res[p] = steps + 1;
                printf("i:%d steps:%d \n", p, steps);
                break;
            }
            steps++;
        }
    }
    long lcm = findLCMArray(res, idxStartA);
    
    printf("PART TWO: %ld\n", lcm);
    fclose(filePtr);
}

#endif /* PART_TWO */
