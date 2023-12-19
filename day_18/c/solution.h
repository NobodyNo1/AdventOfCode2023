#ifndef SOLUTION_H
#define SOLUTION_H

#include "common.h"
#include "area_counter.h"
#include <math.h>

void part_one();
void part_two();

void solve() {
    // part_one();
    part_two();
}

typedef struct {
    int direction;
    int times;
} DigAction;

bool is_dir(int ch) {
    return ch == 'R' || ch == 'L' || ch == 'U' || ch == 'D';
}

#define RIGHT   0
#define DOWN    1
#define LEFT    2
#define UP      3

int to_dir(int ch) {
    if(ch == 'R') return RIGHT;
    if(ch == 'L') return LEFT;
    if(ch == 'U') return UP;
    if(ch == 'D') return DOWN;
    return -1;
}

DigAction* create_dig_action(int dir, int times){
    DigAction* digaction = (DigAction*) malloc(sizeof(DigAction));
    digaction->direction=dir;
    digaction->times = times;
    return digaction;
}

void part_one() {
    work_with_files("../input/input.txt");
    int times = -1;
    int dir = -1;
    Slice slice = create_slice(100);
    file_read_loop() {
        if_new_line {
            add_item(&slice, create_dig_action(dir, times));
            times = -1;
            dir = -1;
            continue;
        }
        if(times != -1 && dir != -1){
            continue;
        }
        if(is_dir(ch)){
            dir = to_dir(ch);
        }
        if (is_digit(ch)){
            times = 0;
            while (is_digit(ch))
            {
                times = times*10 + (ch - '0');
                ch = getc(filePtr);
            }
        }
    }
    if_last_line_not_handled {
        if(times != -1 && dir != -1)
            add_item(&slice, create_dig_action(dir, times));
    }
    finish_file_work();
    int x = 0, y =0;
    int max_x = 0, max_y =0;
    int min_x = 1000, min_y = 1000;
    for (int i = 0; i < slice.size; i++)
    {
        DigAction* data = (DigAction*) slice.data[i];
        switch (data->direction)
        {
            case RIGHT:
                x+=data->times;
                break;
            case LEFT:
                x-=data->times;
                break;
            case UP:
                y-=data->times;
                break;
            case DOWN:
                y+=data->times;
                break;
            default:
                break;
        } 
        printf("x: %d | y: %d\n", x,y);
        max_x = max_x < x ? x : max_x;
        max_y = max_y < y ? y : max_y;
        min_x = min_x > x ? x : min_x;
        min_y = min_y > y ? y : min_y;
    }

    //Normailize
    int cols = (max_x-min_x)+1;
    int rows = (max_y-min_y)+1;
    char* canvas = (char*) malloc(cols*rows*sizeof(char));
    for (size_t i = 0; i < cols*rows; i++)
    {
        canvas[i] = '.';
    }
    int col = 0-min_x;
    int row = 0-min_y;
    printf("[Start] col :%d, row: %d\n",col, row);
    for (int i = 0; i < slice.size; i++)
    {
        DigAction* data = (DigAction*) slice.data[i];
        int start_col = col;
        int start_row = row;
        switch (data->direction)
        {
        case RIGHT:
            for(col = start_col; col < start_col+data->times; col++){
                int idx = asIdx(col, row, cols);
                canvas[idx] = '#';
            }
            break;
            // 0123456
        case LEFT:
            for(col = start_col; col > start_col-data->times; col--){
                int idx = asIdx(col, row, cols);
                canvas[idx] = '#';
            }
            break;
        case UP:
            for(row = start_row; row > start_row-data->times; row--){
                int idx = asIdx(col, row, cols);
                canvas[idx] = '#';
            }
            break;
        case DOWN:
            for(row = start_row; row < start_row + data->times; row++){
                int idx = asIdx(col, row, cols);
                canvas[idx] = '#';
            }
            break;
        default:
            break;
        }
    }
    printf("cols:%d | rows:%d \n", cols, rows);

    long inner = count_area(canvas, 0-min_x, 0-min_y - 1, cols, rows);
    printf("TOTAL AREA: %d\n", inner);
    FILE *output = fopen("../input/output.txt", "w");
    for (size_t i = 0; i < cols*rows; i++)
    {
        int col = i%cols;
        if(col == 0) 
            putc('\n', output);
        putc(canvas[i], output);
    }
    putc('\n', output);

}

void part_two() {
    Slice slice = create_slice(100);
    int times = -1;
    int dir = -1;

    FILE* filePtr = fopen("../input/input.txt", "r");
    int ch;
    while(ch!=EOF) {
        times = 0;
        dir = -1;
        // skip till #
        while((ch = getc(filePtr)) != '#'){
            if(ch == EOF) break;
        }
        int digit_pos = 0;
        
        while((ch = getc(filePtr)) != ')'){
            if(ch == EOF) break;
            int digit = hex_to_int(ch);;
            if(digit_pos == 5){
                dir = digit;
            } else {
                times = times + (digit)*pow((double)16, (double)(4-digit_pos)); 
                digit_pos++;
            }
        }
        if(times != 0 && dir != -1)
        {
            printf("times:%d | dir:%d\n", times, dir);
            add_item(&slice, create_dig_action(dir, times));
        }        
    }
    fclose(filePtr);

    // sholase
    long first_x = 0, first_y = 0;
    long prev_x = 0, prev_y = 0;
    long result = 0;
    long x = 0, y = 0;
    long perimeter = 0;
    for (int i = 0; i < slice.size; i++)
    {
        DigAction* data = (DigAction*) slice.data[i];
        perimeter+=data->times;
        switch (data->direction)
        {
            case RIGHT:
                x+=data->times;
                break;
            case LEFT:
                x-=data->times;
                break;
            case UP:
                y-=data->times;
                break;
            case DOWN:
                y+=data->times;
                break;
            default:
                break;
        } 
        long det = 0;
        if(i != 0) {
            long a = prev_x * y;
            long b = x*prev_y;
            det = (a) - (b);
        } else {
            first_x = x;
            first_y = y;
        }
        prev_x = x;
        prev_y = y;
        result += det;
    }
    //expected: 952408144115
    //got:      952411346745
    // 40654918441248
    // 40654918441247
    printf("result: %ld  \n", result);
    long det = (x * first_y) - (first_x*y);
    result += det;
    //TODO: learn why we added perimeter, why perimeter divided 2, and why + 1
    printf("result: %ld | area: %ld \n", result, (result + perimeter)/2l + 1);
}

#endif /* SOLUTION_H */
