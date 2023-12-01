/*
Day 1
link: https://adventofcode.com/2023/day/1

Short description:

The newly-improved calibration document consists of lines of text; 
each line originally contained a specific calibration value that the Elves
now need to recover. On each line, the calibration value can be found by 
combining the first digit and the last digit (in that order) to form a single two-digit
number.

For example:

1abc2
pqr3stu8vwx
a1b2c3d4e5f
treb7uchet
In this example, the calibration values of these four lines are 12, 38, 15, and 77.
Adding these together produces 142.
*/
#include "solution.h"
#include "stdio.h"

int run(int part){
    int result = solution(part);
    if(result < 0) return -1;
    printf("Part %d | result: %d\n", part, result);
}

int main() {
    run(1);
    run(2);

    return 0;
}