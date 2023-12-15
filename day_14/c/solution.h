#ifndef SOLUTION_H
#define SOLUTION_H

#include "common.h"

void part_one();
void part_two();

void solve() {
    part_one();
    part_two();
}

int solution(int* items, int cols, int rows){
    int result = 0;
    int count = 0;
    int anchor = 0;
    int max = rows;
    for (int i = 0; i < cols; i++)
    {
        int local_result = 0;
        for (int j = 0; j < rows; j++)
        {   
            int idx = j*cols + i;
            int cur_char = items[idx];
            if(cur_char == '#') {
                for(int p = anchor; p < anchor+count; p++){
                    local_result+= max-p;
                }
                count = 0;
                anchor = j+1;
                continue;
            }
            if(cur_char == 'O') {
                count++;
            }
        }
        if(count != 0){
            for(int p = anchor; p < anchor+count; p++){
                local_result+= max-p;
            }
        }
        count = 0;
        anchor = 0;
        result +=local_result;
    }

    printf("    RESULT: %d\n", result);
    return result;
}


int solution2(int* items, int cols, int rows){
    int north_wall_load = 0;
    int current_row_num = rows;
    for (int j = 0; j < rows; j++)
    {   
        for (int i = 0; i < cols; i++)
        {
            int idx = j*cols + i;
            // printf("            %d", idx);
            int cur_char = items[idx];
            if(cur_char == 'O') {
                north_wall_load += current_row_num;
            }
        }
        current_row_num--;
    }

    printf("    RESULT: %d\n", north_wall_load);
    return north_wall_load;
}

void part_one() {
    File2d file2d = get_2d_file("../input/input.txt");
    solution(file2d.items, file2d.cols, file2d.rows);
}

#define NORTH   1
#define WEST    2
#define SOUTH   3
#define EAST    4

void shift(int* data, int cols, int rows);

void copy_items(int* data_a, int* data_b, int size) {
    for(int i = 0; i < size; i++) {
        data_b[i] = data_a[i];
    }
}

bool equals(int* data_a, int* data_b, int size) {
    for(int i = 0; i < size; i++) {
        bool equals = data_a[i] == data_b[i];
        if(!equals) return false;
    }
    return true;
}

//64
void part_two() {
    File2d file2d = get_2d_file("../input/input.txt");
    int* copy = (int*) malloc(sizeof(int)*file2d.size);
    copy_items(file2d.items, copy, file2d.size);

    // print_file2d(file2d);
    // printf("\n");
    // print_char_arr(copy, file2d.cols, file2d.rows);
    int i = 0;
    int j = 0;
    for(i = 0, j =0; i < 1000000000; i++, j+=2) {
        shift(copy, file2d.cols, file2d.rows);
        shift(file2d.items, file2d.cols, file2d.rows);
        shift(file2d.items, file2d.cols, file2d.rows);

        if(equals(file2d.items, copy, file2d.size)) {
            printf("Found Cycle: %d | %d |\n", i, j);
            break;
        }
    }
    int period = 0;

    int* copy2 = (int*) malloc(sizeof(int)*file2d.size);
    copy_items(copy, copy2, file2d.size);
    do
    {
        shift(copy2, file2d.cols, file2d.rows);
        period++;
    } while (!equals(copy, copy2, file2d.size));
    
    printf("Period: %d \n", period);
    int repeatable_cycles = 1000000000 - i;
    int amount_of_periods = repeatable_cycles/period;
    int closest_period = amount_of_periods * period;
    
    for(i = closest_period; i < 1000000000; i++) {
        shift(copy2, file2d.cols, file2d.rows);
    }
    solution2(copy2, file2d.cols, file2d.rows);
}

void shift_north(int* data, int cols, int rows);
void shift_west(int* data, int cols, int rows);
void shift_south(int* data, int cols, int rows);
void shift_east(int* data, int cols, int rows);

void shift(int* data, int cols, int rows) {
    shift_north(data, cols, rows);
    shift_west(data, cols, rows);
    shift_south(data, cols, rows);
    shift_east(data, cols, rows);
}


void shift_north(int* data, int cols, int rows) {
    int count = 0;
    for (int i = 0; i < cols; i++)
    {
        for (int j = rows - 1; j >= 0; j--)
        {
            int idx = j*cols + i;
            int cur_char = data[idx];
            if(cur_char == '#' && count != 0) {
                for (int q = j+1; q <= j+count; q++)
                {
                    int _idx = q*cols + i;
                    data[_idx] = 'O';
                }
                count = 0;
                continue;
            }
            if(cur_char == 'O') {
                count++;
                data[idx] = '.';
            }
        }
        for (int q = 0; q < count; q++)
        {
            int _idx = q*cols + i;
            data[_idx] = 'O';
        }
        count = 0;
    }
}


void shift_west(int* data, int cols, int rows) {
    int count = 0;
    for (int j = 0; j < rows; j++)
    {
        for (int i = cols - 1; i >= 0; i--)
        {
            int idx = j*cols + i;
            int cur_char = data[idx];
            if(cur_char == '#' && count != 0) {
                for (int q = i+1; q <= i+count; q++)
                {
                    int _idx = j*cols + q;
                    data[_idx] = 'O';
                }
                count = 0;
                continue;
            }
            if(cur_char == 'O') {
                count++;
                data[idx] = '.';
            }
        }
        for (int q = 0; q < count; q++)
        {
            int _idx = j*cols + q;
            data[_idx] = 'O';
        }
        count = 0;
    }
}


void shift_south(int* data, int cols, int rows) {
    int count = 0;
    for (int i = 0; i < cols; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            int idx = j*cols + i;
            // printf("i:%d j:%d | %d \n", i, j, idx);
            int cur_char = data[idx];
            if(cur_char == '#' && count != 0) {
                for (int q = j - 1; q >= j - count; q--)
                {
                    int _idx = q*cols + i;
                    data[_idx] = 'O';
                }
                count = 0;
                continue;
            }
            if(cur_char == 'O') {
                count++;
                data[idx] = '.';
            }
        }
        for (int q = rows - 1; q >= rows - count; q--)
        {
            int _idx = q*cols + i;
            data[_idx] = 'O';
        }
        count = 0;
        // printf("\n");
        // return;
    }
}


void shift_east(int* data, int cols, int rows) {
    int count = 0;
    for (int j = 0; j < rows; j++)
    {
        for (int i = 0; i < cols; i++)
        {
            int idx = j*cols + i;
            int cur_char = data[idx];
            if(cur_char == '#' && count != 0) {

                for (int q = i - 1; q >= i-count; q--)
                {
                    int _idx = j*cols + q;
                    data[_idx] = 'O';
                }
                count = 0;
                continue;
            }
            if(cur_char == 'O') {
                count++;
                data[idx] = '.';
            }
        }
        for (int q = cols - 1; q >= cols-count; q--)
        {
            int _idx = j*cols + q;
            data[_idx] = 'O';
        }
        count = 0;
    }
}

#endif /* SOLUTION_H */
