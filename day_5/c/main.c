#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
/*

The almanac (your puzzle input) lists all of the seeds that need to be planted.
It also lists what type of soil to use with each kind of seed, 
what type of fertilizer to use with each kind of soil, what type of water to use with each kind of fertilizer,
and so on. Every type of seed, soil, fertilizer and so on is identified with a number,
but numbers are reused by each category - that is, soil 123 and fertilizer 123 aren't necessarily related to each other.
*/
#define INTIAL_SEEDS_BUFFER_SIZE    20
#define MAP_SIZE                    7
// #define DEBUG

#define PART_ONE 1
#define PART_TWO 2

bool isDigit(int ch){
    return '0'<=ch&&ch<='9';
}

typedef struct {
    //start
    long from;
    // range
    long to;
    // destination
    long toAdd;
} RangeInfo;

#ifdef DEBUG

#include <stdio.h>
#include <stdarg.h>

void log_mes(const char *format, ...) {
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}
#else
void log_mes(const char *format, ...) {}
#endif

int solve(int part);

int main(void) {
    solve(PART_ONE);
    solve(PART_TWO);
    return EXIT_SUCCESS;
}

int partOne(int seedsSize, long* seedsBuffer, int* mapSizes, RangeInfo** maps);
int partTwo(int seedsSize, long* seedsBuffer, int* mapSizes, RangeInfo** maps);
int partTwo2(int seedsSize, long* seedsBuffer, int* mapSizes, RangeInfo** maps);

int solve(int part) {
    FILE* filePtr = fopen("../input/input.txt", "r");

    int ch;
    
    long collectedNumber = -1;

    size_t seedsBufferCapacity = INTIAL_SEEDS_BUFFER_SIZE;
    long* seedsBuffer = calloc(seedsBufferCapacity, sizeof(long));
    size_t seedsSize = 0;

    // [START]  COLLECTING SEEDS
    while((ch = getc(filePtr)) != ':'){
        //skipping "seeds:" text"
    }
    while((ch = getc(filePtr)) != EOF){
        if(isDigit(ch)) {
            if(collectedNumber == -1) collectedNumber = 0;
            collectedNumber = collectedNumber*10 + (ch - '0');
            continue;
        } else if(collectedNumber != -1) {
            if(seedsSize == seedsBufferCapacity) {
                seedsBufferCapacity = seedsBufferCapacity+seedsBufferCapacity/2;
                seedsBuffer = (long*) realloc(seedsBuffer, seedsBufferCapacity*sizeof(long));
            }
            seedsBuffer[seedsSize] = collectedNumber;
            seedsSize++;
            collectedNumber = -1;
        }
        if(ch == '\n') break;
    }

    int mapIdx = 0;
    // [START]  PARSING MAP DATA
    long rangeBuffer[3] = {0L};
    int rangeBufferIdx = 0;
    int mapSizes[MAP_SIZE] = {0};
    RangeInfo* maps[MAP_SIZE];
    
    for (size_t i = 0; i < MAP_SIZE; i++)
    {
        maps[i] = (RangeInfo*) calloc(0, sizeof(RangeInfo));
    }

    while (ch!=EOF)
    {
        while((ch = getc(filePtr)) != ':'){
            //skipping title
        }
        // skipping newline
        getc(filePtr);
        
        bool lastChWasNewLine = false;
        while((ch = getc(filePtr)) != EOF) {
            if(isDigit(ch)) {
                if(collectedNumber == -1) collectedNumber = 0;
                collectedNumber = collectedNumber*10 + (ch - '0');
                continue;
            } else if(collectedNumber != -1) {
                rangeBuffer[rangeBufferIdx] = collectedNumber;
                collectedNumber = -1;
                rangeBufferIdx++;
            }

            if(ch == '\n') {
                log_mes("    RANGES: ");
                for (size_t i = 0; i < 3; i++)
                {
                    log_mes("%d, ", rangeBuffer[i]);
                }
                log_mes("\n");
                
                rangeBufferIdx = 0;
                RangeInfo rangeInfo = { 
                    .from=rangeBuffer[1],
                    .to=rangeBuffer[1] + rangeBuffer[2],
                    .toAdd=rangeBuffer[0] - rangeBuffer[1],
                };
                mapSizes[mapIdx]++;
                log_mes("    mapsize: %d\n", mapSizes[mapIdx]);

                maps[mapIdx] = (RangeInfo*) realloc(maps[mapIdx], mapSizes[mapIdx]*sizeof(RangeInfo));
                maps[mapIdx][mapSizes[mapIdx] - 1] = rangeInfo;

                if(lastChWasNewLine){
                    break;
                }
                lastChWasNewLine = true;
                //indicate somehow about new range data?
                continue;
            } else{
                lastChWasNewLine = false;
            }
        }
        mapIdx++;
        log_mes("mapIdx: %d \n", mapIdx);
    }
    // [END]    PARSING MAP DATA

   
    // [START]  MAPPING DATA
    if(part == PART_ONE)
        partOne(seedsSize, seedsBuffer, mapSizes, maps);
    else if(part == PART_TWO)
        partTwo2(seedsSize, seedsBuffer, mapSizes, maps);
        // partTwo(seedsSize, seedsBuffer, mapSizes, maps);
    // [END]  MAPPING DATA
    
    return EXIT_SUCCESS;
}



int partOne(int seedsSize, long* seedsBuffer, int* mapSizes, RangeInfo** maps) {
    long minLocation = -1;
    for (size_t i = 0; i < seedsSize; i++)
    {
        long seed = seedsBuffer[i];
        long curVal = seed;
        log_mes("%d", seed);
        for (size_t j = 0; j < MAP_SIZE; j++)
        {
            long mapResult = curVal;
            log_mes(" -> ");
            for (size_t k = 0; k < mapSizes[j]; k++)
            {
                RangeInfo rangeInfo = maps[j][k];
                if(rangeInfo.from <= curVal && curVal < rangeInfo.to){
                    mapResult += rangeInfo.toAdd;
                }
                if(mapResult != curVal) break;
            }
            curVal = mapResult;
            log_mes("%d", mapResult);
        }
        // curval last value (or "location")
        if(minLocation == -1) minLocation = curVal;
        else minLocation = minLocation > curVal ? curVal : minLocation;
        log_mes("\n");
        
    }

    printf("PART 1: %ld\n", minLocation);
    return EXIT_SUCCESS;
}

//Dumb Solution
int partTwo(int seedsSize, long* seedsBuffer, int* mapSizes, RangeInfo** maps) {
    printf("Depricated!\n  Reason: Very dumb, use `partTwo2(...)` function instead.\n");
    return EXIT_FAILURE;
    long minLocation = -1;
    for (size_t i = 0; i < seedsSize/2; i++)
    {
        long seedStart = seedsBuffer[2*i];
        long seedEnd = seedStart+ seedsBuffer[2*i+1];
        printf("Start: %ld | End: %ld\n", seedStart, seedEnd);
        for(long seed = seedStart; seed<seedEnd; seed++) {
            long curVal = seed;
            for (size_t j = 0; j < MAP_SIZE; j++)
            {
                long mapResult = curVal;
                for (size_t k = 0; k < mapSizes[j]; k++)
                {
                    RangeInfo rangeInfo = maps[j][k];
                    if(rangeInfo.from <= curVal && curVal < rangeInfo.to){
                        mapResult += rangeInfo.toAdd;
                    }
                    if(mapResult != curVal) break;
                }
                curVal = mapResult;
            }
            // curval last value (or "location")
            if(minLocation == -1) minLocation = curVal;
            else minLocation = minLocation > curVal ? curVal : minLocation;
        }
    }

    printf("PART 2 : %ld\n", minLocation);
    return EXIT_SUCCESS;
}

typedef struct {
    long start;
    long end;
} Range;

Range findIntersection(Range range1, Range range2) {
    Range intersection;

    // Check if there is an intersection
    if (range1.start <= range2.end && range2.start <= range1.end) {
        // Calculate the intersection
        intersection.start = (range1.start > range2.start) ? range1.start : range2.start;
        intersection.end = (range1.end < range2.end) ? range1.end : range2.end;
    } else {
        // No intersection
        intersection.start = -1;
        intersection.end = -1;
    }

    return intersection;
}

//result: 57451709

#define CVECTOR_LOGARITHMIC_GROWTH

#include "vector.h"

/*
    Optimizes by taking ranges instead of single seed

    Solution have few issues:
        - Range intersection: we might have intersected ranges,
                                which will lead duplicated calculations

*/
int partTwo2(int seedsSize, long* seedsBuffer, int* mapSizes, RangeInfo** maps) {

    long minLocation = -1;
    
    int seedRangeSize = seedsSize/2;
    // Create range seed
    cvector_vector_type(Range) v = NULL;
    for (size_t i = 0; i < seedRangeSize; i++)
    {
        long seedStart = seedsBuffer[2*i];
        long seedEnd = seedStart+ seedsBuffer[2*i+1];
        Range range = {seedStart, seedEnd};
        cvector_push_back(v, range);
    }

    int currentRangeIdx = 0;
    // Iterate by map items, so collected ranges would be same type
    for (size_t j = 0; j < MAP_SIZE; j++)
    {
        // interate ranges until it reaches end of ranges with same type (last size)
        /*
            basically ranges contain all ranges, and we pushing data to same range "vector"
            in order to stay within single "type" we use last position (before interating to new map)
            as end of type
            [1,1,1,1,1,2,2,2,2,2,2,3,3,3,3,3,3,3,]
            e.g. start with
            [1,1,1,1,1]
            then
            [ (i)1,1,1,1,1|(end)...newly pushed]
        */
        int newRange = cvector_size(v);
        while(currentRangeIdx < newRange) {
            Range currentRange = v[currentRangeIdx];
            for (size_t k = 0; k < mapSizes[j]; k++)
            {
                RangeInfo rangeInfo = maps[j][k];
                //TODO: somehow find where ranges lies
                Range mapRange = {rangeInfo.from, rangeInfo.to};
                Range intersection = findIntersection(mapRange, currentRange);
                // create multiple if needed and push it to ranges
                if (intersection.start == -1) continue;
                Range result = {
                    intersection.start + rangeInfo.toAdd,
                    intersection.end   + rangeInfo.toAdd
                };
                // collect intersection
                cvector_push_back(v, result);
            }
            currentRangeIdx++;
        }
    }
    int rangeSize = cvector_size(v);
    for(int i = currentRangeIdx; i < rangeSize; i++){
        long curVal = v[i].start;
        if(minLocation == -1) minLocation = curVal;
        else minLocation = minLocation > curVal ? curVal : minLocation;
    }
    printf("PART 2: %ld\n", minLocation);
    cvector_free(v);
    return EXIT_SUCCESS;
}
