#ifndef SOLUTION_H
#define SOLUTION_H

#include "common.h"
#include <math.h>

void part_one();
void part_two();

void solve() {
    part_one();
    part_two();
}

typedef struct {
    int idx;
    long row;
    long col;
} Star;

Star* create_star(int idx, long row, long col){
    Star* star = (Star*) malloc(sizeof(Star));
    star->idx = idx;
    star->row = row;
    star->col = col;
    return star;
}

void solution(int empty_space_price);

void part_one(){ solution(2);}
void part_two(){ solution(1000000);}

//TODO: learn https://www.reddit.com/r/adventofcode/comments/18fqxuq/an_on_algorithm_for_day_11/
void solution(int empty_space_price) {
    File2d file2d = get_2d_file("../input/input.txt");
    Slice stars = create_slice(10);
    int size = file2d.cols*file2d.rows;
    int idx = 1;
    // USING MAP IS PREFERRED
    Slice empty_rows  = create_slice(file2d.rows);
    for (size_t i = 0; i < file2d.rows; i++)
    {
        bool is_no_star = true;
        for(size_t j = 0; j < file2d.cols; j++){
            int idx = asIdx(j, i, file2d.cols);
            if(file2d.items[idx] == '#'){
                is_no_star = false;
                break;
            }
        }
        if(is_no_star) add_item(&empty_rows, i);
    }
    // USING MAP IS PREFERRED
    Slice empty_cols = create_slice(file2d.cols);
    for (size_t i = 0; i < file2d.cols; i++)
    {
        bool is_no_star = true;
        for(size_t j = 0; j < file2d.rows; j++){
            int idx = asIdx(i, j, file2d.cols);
            if(file2d.items[idx] == '#') {
                is_no_star = false;
                break;
            }
        }
        if(is_no_star) add_item(&empty_cols, i);
    }

    long y = 0;

    for (size_t i = 0; i < file2d.rows; i++)
    {
        if(contains(&empty_rows, i)) {
            y += empty_space_price;
            continue;
        } 
        long x = 0;
        for (size_t j = 0; j < file2d.cols; j++)
        {
            if(contains(&empty_cols, j)) {
                x+= empty_space_price;
                continue;
            }        
            int idx = asIdx(j, i, file2d.cols);
            if(file2d.items[idx] == '#'){

                add_item(&stars, create_star(idx++, x, y));
            }
            x++;
        }
        y++;
    }
    printf("found : %d stars\n", stars.size);
    
    long result = 0;

    for (size_t i = 0; i < stars.size; i++)
    {
        Star* from = (Star*) stars.data[i];
        for(size_t j = i+1; j < stars.size; j++) {
            Star* to = (Star*) stars.data[j];
            long col_diff = abs(from->col - to->col);
            long row_diff = abs(from->row - to->row);
            long star_distance = abs(from->col - to->col) + abs(from->row - to->row);
            result += star_distance;
        }
    }
    printf("Result: %ld\n", result);
}

#endif /* SOLUTION_H */
