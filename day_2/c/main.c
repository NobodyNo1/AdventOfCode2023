
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

#define STATE_PARSING_GAME_ID   0
#define STATE_PARSING_VALUES    1
#define STATE_PARSING_END       2

#define RED     1
#define GREEN   2
#define BLUE    3

#define PART_ONE 1
#define PART_TWO 2

typedef struct GameInfo
{
    int id;
    int maxRed;
    int maxGreen;
    int maxBlue;
} GameInfo;

typedef struct Cube
{
    int color;
    int value;
} Cube;

// Helper methods

bool isDigit(int ch);
bool isLineBreak(int ch);
int max(int a, int b);
int multiAvoidZero(int a, int b, int c);


bool isCubeNotEmpty(Cube *cube);


// Parse function

int parse(int ch, int state, GameInfo* gameInfo, Cube* parseCube);
int parseGameId(int ch, GameInfo* gameInfo);
int parseValues(int ch, GameInfo* gameInfo, Cube* parseCube);

// Solution functions
void run(int id);
void solution(FILE *filePtr, int part);

/*              Start             */

int main() {
    run(PART_ONE);
    run(PART_TWO);
    return 0;
}

void run(int id) {
    FILE *filePtr;
    filePtr = fopen("../input/input.txt", "r");
    solution(filePtr, id);
    fclose(filePtr);
}

void solution(FILE *filePtr, int part) {
    GameInfo gameInfo = { 0 };
    Cube parseCube = { 0 }; 

    int maxRed      = 12;
    int maxGreen    = 13;
    int maxBlue     = 14;

    int ch;
    int parsingState = STATE_PARSING_GAME_ID;
    int result = 0;
    while((ch = getc(filePtr)) != EOF) {
       if(isLineBreak(ch)) {
            parsingState = parse(ch, STATE_PARSING_END, &gameInfo, &parseCube);
            if(part == PART_ONE){
                if(gameInfo.maxBlue <= maxBlue 
                    && gameInfo.maxGreen <= maxGreen 
                    && gameInfo.maxRed <= maxRed
                ) {
                    result += gameInfo.id;
                }
            } else{
                result += multiAvoidZero(gameInfo.maxBlue, gameInfo.maxGreen, gameInfo.maxRed);
            }
            gameInfo = (GameInfo) { 0 };
            continue;
        }
        parsingState = parse(ch, parsingState, &gameInfo, &parseCube);
    }
    printf("Part %d: %d \n",part, result);
}

/*              Parsing             */

int parse(int ch, int state, GameInfo* gameInfo, Cube* parseCube) {
    switch (state)
    {
    case STATE_PARSING_GAME_ID:
        return parseGameId(ch, gameInfo);
    case STATE_PARSING_VALUES:
        return parseValues(ch, gameInfo, parseCube);
    case STATE_PARSING_END:
        // forcing value updates
        parseValues(',', gameInfo, parseCube);
        return STATE_PARSING_GAME_ID;
    default:
        break;
    }
    return state;
}

int parseGameId(int ch, GameInfo* gameInfo) {
    // Switch to parsing cube colors
    if(ch == ':') return STATE_PARSING_VALUES;
    
    if(isDigit(ch)) gameInfo->id = gameInfo->id * 10 + (ch - '0');
    
    return STATE_PARSING_GAME_ID;
}

int parseValues(int ch, GameInfo* gameInfo, Cube* parseCube) {
    if(isCubeNotEmpty(parseCube)) {
        // case where we found "red" by "r", and parsing "ed" is obsolete 
        if(ch != ',' && ch != ';') return STATE_PARSING_VALUES;
        switch (parseCube->color)
        {
            case RED:
                gameInfo->maxRed   = max(gameInfo->maxRed  , parseCube->value);
                break;
            case GREEN:
                gameInfo->maxGreen = max(gameInfo->maxGreen, parseCube->value);
                break;
            case BLUE:
                gameInfo->maxBlue  = max(gameInfo->maxBlue , parseCube->value);
                break;
        };
        parseCube->value = 0;
        parseCube->color = 0;
    } else {
        if(isDigit(ch)) {
            parseCube->value = parseCube->value * 10 + (ch - '0');
            return STATE_PARSING_VALUES;
        }
        switch (ch)
        {
            case 'r': parseCube->color = RED;
                break;
            case 'g': parseCube->color = GREEN;
                break;
            case 'b': parseCube->color = BLUE;
                break;
            default:
                break;
        }

        return STATE_PARSING_VALUES;
    }
    return STATE_PARSING_VALUES;
}

/*              Helper functions             */

bool isCubeNotEmpty(Cube *cube) {
    return cube->color != 0 && cube->value != 0;
}

bool isLineBreak(int ch) {
    return ch == '\n';
}

bool isDigit(int ch) {
    return '0' <= ch && ch <= '9';
}

int max(int a, int b) {
    return a>b ? a: b;
}

int multiAvoidZero(int a, int b, int c) {
    int result = 1;
    if(a!=0) result*=a;
    if(b!=0) result*=b;
    if(c!=0) result*=c;
    return result;
}