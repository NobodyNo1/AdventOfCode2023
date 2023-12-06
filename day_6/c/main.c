#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    long time;
    long distance;
} Data;

/*  Formulae
   
    
    time = holdTime + travelTime
    
    speed = holdTime
    speed = distance/travelTime

    holdTime = distance/travelTime
    holdTime = distance/(time - holdTime)

    holdTime*(time - holdTime) = distance
    holdTime*time - holdTime^2 = distance

    
    x*time - x^2 > distance

e.g. (time = 7; distance = 9)
    7*x - x^2 > 9

    amount of numbers = x_2 - x_1 + 1 
*/
long getCount(Data data) {
    long time = data.time;
    long distance = data.distance;
    // distance = 0 case?
    long count = 0;

    /*
    // Simple solution
    for(int holdTime = 1; holdTime < time; holdTime++) {
        count += holdTime*(time - holdTime) > distance;
    }
    */

    long start = -1;
    for(int holdTime = 1; holdTime < time; holdTime++) {
        if(holdTime*(time - holdTime) > distance){
            start = holdTime;
            break;
        }
    }
    if(start == -1) return -1;
    long end = -1;
    for(int holdTime = time-1; holdTime > start; holdTime--) {
        if(holdTime*(time - holdTime) > distance){
            end = holdTime;
            break;
        }
    }
    if(end == -1) return -1;
    count =  end - start + 1;
    return count;
}

// TODO: better to define it dynamicallly
#define BUF_SIZE 10

void partOne(void);
void partTwo(void);

int main(void) {
    partOne();
    partTwo();
}


void partOne(void) {
    FILE* filePtr = fopen("../input/input.txt", "r");

    Data* dataArr = (Data*) malloc(BUF_SIZE*sizeof(Data));
    int number = -1;
    int elements = 0;
    int i = 0;
    int j = 0;
    int c;
    while ((c=getc(filePtr)) != EOF)
    {
        if('0' <= c && c<= '9'){
            if(number == -1) number = 0;
            number = 10*number + (c-'0');
        } else {
            if(number != -1) {
                if(i > BUF_SIZE) {
                    printf("Index out of bounds!\nIncrease buffer size\n");
                    return;
                }
                if(j==0)
                    dataArr[i].time = number;
                else
                    dataArr[i].distance = number;
                number = -1;
                i++;
            }
        }
        if(c=='\n') {
            if(i>elements)
                elements = i;
            i = 0;
            j++;
            continue;
        }
    }
    
    int result = 1;
    for(int i = 0; i<elements; i++){
        result *= getCount(dataArr[i]);
    }
    printf("result: %d\n", result);
    fclose(filePtr);
}

void partTwo(void) {
    FILE* filePtr = fopen("../input/input.txt", "r");
    Data data = {};
    long number = -1;
    int j = 0;
    int c;
    while ((c=getc(filePtr)) != EOF)
    {
        if('0' <= c && c<= '9'){
            if(number == -1) number = 0;
            number = 10*number + (c-'0');
        }
        if(c=='\n') {
            if(number != -1) {
                if(j==0) data.time = number;
                else data.distance = number;
            }
            number = -1;
            j++;
            continue;
        }
    }
    long result = getCount(data);
    printf("result: %ld\n", result);
    fclose(filePtr);
}

