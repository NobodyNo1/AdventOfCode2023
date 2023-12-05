#include "stdio.h"
#include "stdbool.h"
#include "stdlib.h"
/*
As far as the Elf has been able to figure out, 
you have to figure out which of the numbers you have appear in the list of winning numbers.
 The first match makes the card worth one point and each match after the first doubles the point value of that card.
*/
bool isDigit(int ch) {
    return '0' <= ch && ch <= '9';
}

int partOne(){
    FILE* filePtr = fopen("../input/input.txt", "r");

    int ch;
    int leftSide = true;
    bool matchMap[100] = {false};
        
    int curNumber = 0;
    int matchCount = 0;
    int result = 0;
    while((ch = getc(filePtr)) != EOF) {
        if(ch == '\n') {
            //clean
            if(matchMap[curNumber]){
                matchCount++;
            }
            curNumber = 0;
            // this vs = { false };
            for (size_t i = 0; i < 100; i++) matchMap[i] = false;

            if(matchCount > 0)
                result += 1 << (matchCount - 1);
            matchCount = 0;
            leftSide = true;
            while((ch = getc(filePtr)) != ':' || ch == EOF) {
                if(ch == EOF) break;
            }
            continue;
        }
        if(ch == '|'){
            // start of own values
            // check matches

            leftSide = false;
            continue;
        }
        //basically is space of digit
        if(isDigit(ch)) {
           curNumber = 10*curNumber + (ch - '0'); 
        } else if (curNumber!= 0) {
            if(leftSide) {
                matchMap[curNumber] = true;
            } else {
                if(matchMap[curNumber]) {
                    matchCount++;
                }
            }
            curNumber = 0;
        }
    }
    printf("result: %d \n" , result);
    return 0;
}


int partTwo() {    
    FILE* filePtr = fopen("../input/input.txt", "r");

    int ch;
    int leftSide = true;
    bool matchMap[100] = {false};

    int n = 0;
    while((ch = getc(filePtr)) != EOF) {
        if(ch == '\n') {
            n++;
        }
    }
    rewind(filePtr);
    //todo: dynamicall calculate size of cards
    int* comboMap = (int*) malloc(n*sizeof(int));

    for(int i = 0; i<n; i++){
        comboMap[i] = 1;
    }
    int currentGame = 0;

    int curNumber = 0;
    int matchCount = 0;
    int result = 0;
    while((ch = getc(filePtr)) != EOF) {
        if(ch == '\n') {
            //clean
            if(matchMap[curNumber]){
                matchCount++;
            }
            curNumber = 0;
            // this vs = { false };
            for (size_t i = 0; i < 100; i++) matchMap[i] = false;

            if(matchCount > 0)
            {
                for(int i = currentGame+1; i <= currentGame+matchCount && i<n; i++){
                    comboMap[i] += comboMap[currentGame];
                }
            }
            matchCount = 0;
            leftSide = true;
            currentGame++;
            while((ch = getc(filePtr)) != ':' || ch == EOF) {
                if(ch == EOF) break;
            }
            continue;
        }
        if(ch == '|'){
            // start of own values
            // check matches

            leftSide = false;
            continue;
        }
        //basically is space of digit
        if(isDigit(ch)) {
           curNumber = 10*curNumber + (ch - '0'); 
        } else if (curNumber!= 0) {
            if(leftSide) {
                matchMap[curNumber] = true;
            } else {
                if(matchMap[curNumber]) {
                    matchCount++;
                }
            }
            curNumber = 0;
        }
    }
    for(int i = 0; i<n; i++){
        result +=comboMap[i];
    }
    printf("result: %d \n" , result);
    return 0;
}


int main(){
    partTwo();
}
/*
1 instance of card 1, 
2 instances of card 2,
4 instances of card 3,
8 instances of card 4,
14 instances of card 5, 
1 instance of card 6.

*/