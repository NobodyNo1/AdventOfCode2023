#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

//todo: Clean up this mess

int pow(int a, int pow) {
    int i = pow;
    int res = 1;
    while(i > 0) {
        res *= a;
        i--;
    }
    return res;
}

bool isDigit(char ch){
    return '0' <= ch && ch <= '9';
}

bool isSymbol(char ch){
    return ch == '*';
}

bool checkCells(char* elements, int topRow, int bottomRow, int col, int colSize, int rowSize) {
    if(topRow >= 0) {
        if(isSymbol(elements[topRow * colSize + col])) return true;
    }
    if(bottomRow < rowSize) {
        if(isSymbol(elements[bottomRow * colSize + col])) return true;
    }
    return false;
}

int partTwo();

int main() {
    return partTwo();
}

int partOne() {
    FILE* filePtr = fopen("../input/input.txt", "r");

    fseek(filePtr, 0L, SEEK_END);
    int size = ftell(filePtr);
    // ..
    rewind(filePtr);

    char* elements = (char*) malloc(size*sizeof(char));
    char c;

    int row = 0, col = 0, rowSize = 0, colSize = 0;

    while((c = getc(filePtr)) != EOF) {
        if(c == '\n') {
            if(colSize == 0) colSize = col;
            col = 0;
            row++;
            continue;
        }
        if(isDigit(c) || c == '.')
            elements[row*colSize + col] = c;
        else    
            elements[row*colSize + col] = '*';
        col++;
    }
    
    rowSize = row;

    int result                 = 0;
    int currentNumber          = 0;
    bool isCollideWithSymbol   = false;
    for (size_t i = 0; i < size; i++)
    {
        if(!isDigit(elements[i])){
            if(isCollideWithSymbol) {
                result += currentNumber;
            }
            currentNumber = 0;
            isCollideWithSymbol = false;
            continue;
        }
        
        bool isFirstNumber = currentNumber == 0;
        currentNumber = currentNumber*10 + (elements[i] - '0');
        if(isCollideWithSymbol == true) continue;

        int col = i%colSize;
        int row = i/colSize;

        // for any position
        int topRow    = row - 1;
        int bottomRow = row + 1;
        if(checkCells(elements, topRow, bottomRow, col, colSize, rowSize)){
            isCollideWithSymbol = true;
            continue;
        }

        int leftCol = col - 1;
        if(isFirstNumber && leftCol >= 0) {
            if(isSymbol(elements[i-1])){
                isCollideWithSymbol = true;
                continue;
            }
            if(checkCells(elements, topRow, bottomRow, leftCol, colSize, rowSize)){
                isCollideWithSymbol = true;
                continue;
            }
        }
        int rightCol = col + 1;
        if(rightCol < colSize && i+1 < size && !isDigit(elements[i+1])) {
             if(isSymbol(elements[i+1])) {
                isCollideWithSymbol = true;
                continue;
            }
            if(checkCells(elements, topRow, bottomRow, rightCol, colSize, rowSize)) {
                isCollideWithSymbol = true;
                continue;
            }
        }

    }
    
    printf("result: %d\n", result);
    free(elements);
    fclose(filePtr);
    return 0;
}

int collectNumbersLeft(char* elements, int endCol, int row, int colSize, int rowSize) {
    if(row >= rowSize) return 0;

    int result = 0;
    int powI = 0;
    for(int i = endCol; i >= 0 && isDigit(elements[row*colSize +i]); i--) {
        int idx = row*colSize + i;
        result = result + ((elements[idx] - '0') * pow(10, powI));
        powI++;
    }
    return result;
}

int collectNumbersRight(char* elements, int startCol, int row, int colSize, int rowSize, int initial) {
    if(row >= rowSize) return 0;
    int result = initial;
    for(int i = startCol; i < colSize && isDigit(elements[row*colSize + i]); i++) {
        int idx = row*colSize + i;
        result = result*10 + (elements[idx] - '0');
    }
    return result;
}

int collectBothDir(char* elements, int col, int row, int colSize, int rowSize) {
    if(row >= rowSize) return 0;
    if(row < 0) return 0;
    int res = collectNumbersLeft(elements,  col,    row, colSize, rowSize);

    if(res ==0) return 0;
    res     = collectNumbersRight(elements, col+1,  row, colSize, rowSize, res);

    return res;
}

int partTwo(){

    FILE* filePtr = fopen("../input/input.txt", "r");
    // FILE* filePtr = fopen("test_input.txt", "r");


    fseek(filePtr, 0L, SEEK_END);
    int size = ftell(filePtr);
    rewind(filePtr);

    char* elements = (char*) malloc(size*sizeof(char));
    char c;

    int row = 0, col = 0, rowSize = 0, colSize = 0;

    while((c = getc(filePtr)) != EOF) {
        if(c == '\n') {
            if(colSize == 0) colSize = col;
            col = 0;
            row++;
            continue;
        }
        if(isDigit(c) || c == '.')
            elements[row*colSize + col] = c;
        else    
            elements[row*colSize + col] = '*';
        col++;
    }
    
    rowSize = row;

    long result                 = 0L;
    int resultSymbols = 0;

    for (size_t i = 0; i < size; i++)
    {
        if(!isSymbol(elements[i])) continue;
        
        int numberProd   = 1;
        int digitsAround = 0;

        int col = i%colSize;
        int row = i/colSize;
        
        // check sides
        int left    = col - 1;
        int right   = col + 1;
        int top     = row - 1;
        int bottom  = row + 1;
        int k = 0;

        if(left >= 0) {
            int res = collectNumbersLeft(elements, left, row, colSize, rowSize);
            if(res > 0) {
                numberProd *= res;
                digitsAround++;
            }
        }
        if(right < colSize){
            int res = collectNumbersRight(elements, right, row, colSize, rowSize, 0);
            if(res > 0) {
                numberProd *= res;
                digitsAround++;
            }
        }
        if(top >= 0){
            if(isDigit(elements[top*colSize + col])){
                int res = collectBothDir(elements, col, top, colSize, rowSize);
                if(res > 0) {
                    numberProd *= res;
                    digitsAround++;
                }
            } else {
                if(left >= 0) {
                    int res = collectNumbersLeft(elements, left, top, colSize, rowSize);
                    if(res > 0) {
                        numberProd *= res;
                        digitsAround++;
                    }
                }
                if(right < colSize){
                    int res = collectNumbersRight(elements, right, top, colSize, rowSize, 0);
                    if(res > 0) {
                        numberProd *= res;
                        digitsAround++;
                    }
                }
            }
        }
        if(digitsAround > 2) continue;
        if(bottom < rowSize){
            if(isDigit(elements[bottom*colSize + col])){
                int res = collectBothDir(elements, col, bottom, colSize, rowSize);
                if(res > 0) {
                    numberProd *= res;
                    digitsAround++;
                }
            } else {
                if(left >= 0) {
                    int res = collectNumbersLeft(elements, left, bottom, colSize, rowSize);
                    if(res > 0) {
                        numberProd *= res;
                        digitsAround++;
                    }
                }
                if(right < colSize){
                    int res = collectNumbersRight(elements, right, bottom, colSize, rowSize, 0);
                    if(res > 0) {
                        numberProd *= res;
                        digitsAround++;
                    }
                }
            }
        }
        if(digitsAround > 2) continue;
        if(digitsAround == 2) {
            resultSymbols++;
            // printf("numberProd: %d\n", numberProd);
            result += numberProd;
            // printf("result: %ld\n", result);
        }
    }
    

    // Expected: 78826761
    // elements : 300
    printf("Final resultSymbols: %d\n", resultSymbols);
    printf("Final result: %ld\n", result);
    free(elements);
    fclose(filePtr);
    return 0;
}
//77937222