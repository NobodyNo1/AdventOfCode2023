#ifndef SOLUTION_H
#define SOLUTION_H

#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "string.h"

const char* digitWords[] = {
    "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
};

/*
    result:
        - (-1) no matches
        - (int > 0) matched digit
*/
int isDigitWord(int charCode, int* checkingIds) {
    int returnDigit = -1;

    for(int i = 0; i < 9; i++) {
        const char* curWord = digitWords[i];
        int n = strlen(curWord);
        
        if(curWord[checkingIds[i]] != charCode) {
            checkingIds[i] = 0;
            // Check if matching combo failed,
            // need to make sure it is not started again (e.g. onone) 
            if(curWord[checkingIds[i]] == charCode){
                checkingIds[i]++;
            }
            continue;
        }
        if(checkingIds[i] == n-1) {
            returnDigit = i+1;
            continue;
        }
        checkingIds[i]++;
    }
    return returnDigit;
}

bool isDigit(int charCode) {
    return '0' <= charCode && charCode <= '9';
}

bool isLineBreak(int charCode) {
    return charCode == '\n';
}

void resetCheckingIds(int *checkingIds) {
    for(int i = 0;  i<9; i++) checkingIds[i] = 0;
}

int solution(int part) {
    const char* filePath = "input.txt";
    FILE *filePtr = fopen(filePath, "r");
    if (!filePtr) {
        printf("ERROR: Failed to open input file: '%s'", filePath);
        return 1;
    }
    
    int sum = 0;

    int firstDigit = -1;
    int lastDigit = -1;
    int lineIdx = 0;

    int checkingIds[9] = { 0 };
    resetCheckingIds(checkingIds);

    int ch;
    while ((ch = getc(filePtr)) != EOF) {
        if(isLineBreak(ch)) {
            lineIdx++;
            // Can happen if file ends with empty line
            if(firstDigit == -1) break;
            
            int currentValue = firstDigit*10 + lastDigit;
            sum += currentValue;
            firstDigit  = -1;
            lastDigit   = -1;
            resetCheckingIds(checkingIds);
            continue;
        }

        if(isDigit(ch)) {
            // if digit found, reset digit word checking
            resetCheckingIds(checkingIds);

            if(firstDigit == -1) firstDigit = ch - '0';
            lastDigit = ch - '0';
            continue;
        }
        // used for part 2
        if(part == 2)   {
            int res = isDigitWord(ch, checkingIds);
            if(res > 0) {
                if(firstDigit   == -1)  firstDigit = res;
                lastDigit = res;
            }
        }
    }
    if(firstDigit != -1) {
        int currentValue = firstDigit*10 + lastDigit;
        sum += currentValue;
    }

    fclose(filePtr);
    return sum;
}

#endif /* SOLUTION_H */ 