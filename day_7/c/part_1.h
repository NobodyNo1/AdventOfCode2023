#ifndef PART_1
#define PART_1
#include "common.h"

int toOrdinal(char ch) {
    switch (ch)
    {
    case 'A':
        return 12;
    case 'K':
        return 11;
    case 'Q':
        return 10;
    case 'J':
        return 9;
    case 'T':
        return 8;
    default:
        //from 2 to 9 -> 0 ..7
        return ch - '2';
    }
    return -1;
}

int convertToHex(char* hand) {
    int hexValue = 0;
    for (int i = 0; i < HAND_SIZE; ++i) {
        char currentChar = hand[i];
        int digitValue = toOrdinal(currentChar);

        if (digitValue == -1) {
            return 1; // Exit with an error code
        }
        //TODO: learn more
        hexValue = (hexValue << 4) | digitValue;
    }
    //printf("Hexadecimal Value: 0x%X\n", hexValue);
    return hexValue;
}


int determineType(char* hand, HandInfo* handInfo) {
    int map[CART_TYPE_COUNT] = {0};
    int size = 13;
    for(int i = 0; i < HAND_SIZE; ++i) {
        int ordinal = toOrdinal(hand[i]);
        
        map[ordinal]++;
    }
    
    /*
        Five of kind:   combo have 4 zero's                 AAAAA
        Four of a kind:            3 zero's (highest 4)     AA8AA
        Full house:                3 zero's (highest 3)     23332
        Three kind:                2 zero's (highest 3)     TTT98
        Two pair:                  2 zero's (highest 2)     23432
        One pair:                  1 zero's                 A23A4
        High card:                 0 zero's                 23456
    */
    int combos[HAND_SIZE] = {0};
    int i = 0;
    int highest = 0;
    for(int j = 0; j < CART_TYPE_COUNT; ++j){
        if(map[j] != 0) {
            highest = highest < map[j] ? map[j] : highest;
            combos[i] = map[j];
            i++;
        }
    }
    int hexValue = convertToHex(hand);
    
    // TODO: maybe more smarter code
    int handType = 5 - i;
    if(i <= 3){
        if(i == 3) {
            handType = highest == 3 ? 3 : 2;
        } else if(i == 2) {
            handType = highest == 4 ? 5 : 4;
        } else {
            handType = FIVE_PAIR_HAND_TYPE;
        }
    }
    
    handInfo->handHex = hexValue;
    // handInfo->handType = handType;

    // printf("Hand Info:\n    hex: 0x%X\n    handType: %d\n   handPrice: %d\n", 
    // handInfo->handHex, handInfo->handType, handInfo->handPrice);

    return handType;
}

int partOne(void) {
    char handBuffer[HAND_SIZE+1];
    FILE *filePtr = fopen("input.txt", "r");
    HandInfo handCollection[HAND_TYPE_SIZE][BUFFER_SIZE];
    int handSizes[HAND_TYPE_SIZE] = {0};

    int ch;
    int i = 0;
    int handPrice = 0;

    while ((ch=getc(filePtr))!=EOF)
    {
        if(i < HAND_SIZE){
            handBuffer[i] = ch;
            i++;
            continue;
        }
        if(ch == ' '){
            handBuffer[i+1] = '\0';
            continue;
        }
        if('0'<= ch && ch<='9'){
            handPrice = handPrice*10 + (ch-'0');
            continue;
        }
        if(ch == '\n')
        {   
            HandInfo handInfo = {.handPrice=handPrice};
            int type = determineType(handBuffer, &handInfo);
            //int type = determineType(handBuffer, &handInfo);
            
            // printf("type:%d | %s \n", type, handBuffer);
            handCollection[type][handSizes[type]] = handInfo;
            handSizes[type] ++;
            handPrice = 0;
            i = 0;
            continue;
        }
    }
    fclose(filePtr);

    int kRank = 1;
    long result = 0;
    for(int i = 0; i < HAND_TYPE_SIZE; i++){
        if(handSizes[i] == 0){
            continue;
        }
        qsort(handCollection[i],handSizes[i],sizeof(HandInfo),compare_function);
        for(int j = 0; j < handSizes[i]; j++){
            // printf("rank:%d, price:%d \n", kRank, handCollection[i][j].handPrice);
            result += kRank * handCollection[i][j].handPrice;
            // printf("r:%ld\n", result);
            kRank++;
        }
    }
    //250994085
    printf("PART 1: %ld\n", result);
    return 0;
}
#endif /* PART_1 */
