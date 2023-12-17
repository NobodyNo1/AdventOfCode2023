#ifndef SOLUTION_H
#define SOLUTION_H

#include "common.h"

void part_one();
void part_two();

void solve() {
    part_one();
    part_two();
}

#define LEFT    1
#define RIGHT   2
#define UP      3
#define DOWN    4

typedef struct
{
    short direction;
    int idx;
} Beam;

Beam* create_beam(short direction, int idx){
    Beam* beam = malloc(sizeof(beam));
    beam->direction = direction;
    beam->idx = idx;
    return beam;
}

int solution(File2d* file2d, Beam* start_beam) {
    Slice visited = create_slice(100);
    Slice active_beams = create_slice(10);
    add_item(&active_beams, start_beam);
    int cols = file2d->cols;
    int rows = file2d->rows;
    int _i = 0;
    while (active_beams.size != 0)
    {
        Beam* current = (Beam*) active_beams.data[0];
        // pop action
        remove_item(&active_beams, current);
        // printf("active_beams size: %d\n", active_beams.size);
        if(visited.size != 0) {
            bool is_found = false;
            for (int i = 0; i < visited.size; i++)
            {
                Beam* vis_data = (Beam*)visited.data[i];
                if(vis_data->idx == current->idx && vis_data->direction == current->direction){
                    is_found = true;
                    break;
                }
            }
            if(is_found) continue;
        }
        add_item(&visited, current);
        int col = (current->idx)%cols;
        int row = (current->idx)/cols;

        int top     = row - 1 >= 0      ? row - 1 : -1;
        int bot     = row + 1 < rows    ? row + 1 : -1;
        int right   = col + 1 < cols    ? col + 1 : -1;
        int left    = col - 1 >= 0      ? col - 1 : -1;

        int current_char = file2d->items[current->idx];

        switch(current->direction) {
            case LEFT:{
                if(current_char == '|') {
                    if(top != -1)
                        add_item(&active_beams, create_beam(UP, asIdx(col, top, cols)));
                    if(bot != -1)
                        add_item(&active_beams, create_beam(DOWN, asIdx(col, bot, cols)));
                    //add top bot
                    break;
                }
                if(current_char =='\\'){
                    //go top
                    if(top != -1)
                        add_item(&active_beams, create_beam(UP, asIdx(col, top, cols)));
                    break;
                }
                if(current_char == '/'){
                    //go bot
                    if(bot != -1)
                        add_item(&active_beams, create_beam(DOWN, asIdx(col, bot, cols)));
                    break;
                }

                if(left != -1)
                    add_item(&active_beams, create_beam(LEFT, asIdx(left, row, cols)));
                // go left
                break;
            }
            case RIGHT:{
                if(current_char == '|') {
                    if(top != -1)
                        add_item(&active_beams, create_beam(UP, asIdx(col, top, cols)));
                    if(bot != -1)
                        add_item(&active_beams, create_beam(DOWN, asIdx(col, bot, cols)));
                    break;
                }
                if(current_char == '\\'){
                    //go bot
                    if(bot != -1)
                        add_item(&active_beams, create_beam(DOWN, asIdx(col, bot, cols)));
                    break;
                }
                if(current_char == '/'){
                    //go top
                    if(top != -1)
                        add_item(&active_beams, create_beam(UP, asIdx(col, top, cols)));
                    break;
                }
                // go right
                if(right != -1)
                    add_item(&active_beams, create_beam(RIGHT, asIdx(right, row, cols)));
                break;
            }
            case UP:{
                if(current_char == '-') {
                    if(left != -1)
                        add_item(&active_beams, create_beam(LEFT, asIdx(left, row, cols)));
                    if(right != -1)
                        add_item(&active_beams, create_beam(RIGHT, asIdx(right, row, cols)));
                    //add left right
                    break;
                }
                if(current_char == '\\'){
                    //go left
                    if(left != -1)
                        add_item(&active_beams, create_beam(LEFT, asIdx(left, row, cols)));
                    break;
                }
                if(current_char == '/'){
                    //go right
                    if(right != -1)
                        add_item(&active_beams, create_beam(RIGHT, asIdx(right, row, cols)));
                    break;
                }
                if(top != -1)
                    add_item(&active_beams, create_beam(UP, asIdx(col, top, cols)));

                break;
            }
            case DOWN:{

                if(current_char == '-') {
                    if(left != -1)
                        add_item(&active_beams, create_beam(LEFT, asIdx(left, row, cols)));
                    if(right != -1)
                        add_item(&active_beams, create_beam(RIGHT, asIdx(right, row, cols)));
                    break;
                }
                if(current_char == '\\'){
                    //go right
                    if(right != -1)
                        add_item(&active_beams, create_beam(RIGHT, asIdx(right, row, cols)));
                    break;
                }
                if(current_char == '/'){
                    //go left
                    if(left != -1)
                        add_item(&active_beams, create_beam(LEFT, asIdx(left, row, cols)));
                    break;
                }
                if(bot != -1)
                    add_item(&active_beams, create_beam(DOWN, asIdx(col, bot, cols)));
                break;
            }
        }

        // printf("i = %d\n", _i++);
        // if(_i == 10) break;
        // Slice visited_idx = create_slice(visited.size);
        // for(int i = 0; i < visited.size; i++) {
        //     Beam* current_data = (Beam*)visited.data[i];
        //     if(visited_idx.size != 0){
        //         if(contains(&visited_idx, (void*) ( current_data->idx))) continue;
        //     }
        //     add_item(&visited_idx, (void*) (current_data->idx));
        // }
        // printf("\n ");
        // for(int i = 0; i<rows; i++){
        //     for(int j = 0; j < cols; j++) {
        //         int idx = asIdx(j, i, cols);
        //         if(contains(&visited_idx, (void*) ( idx))) {
        //             printf("# ");
        //         } else{
        //             printf(". ");
        //         }
        //     }
        //     printf("\n ");
        // }
    }

    printf("Visited size: %d | size: %d \n", visited.size, file2d->size);
    Slice visited_idx = create_slice(visited.size);
    for(int i = 0; i < visited.size; i++) {
        Beam* current_data = (Beam*)visited.data[i];
        if(visited_idx.size != 0){
            if(contains(&visited_idx, (void*) ( current_data->idx))) continue;
        }
        add_item(&visited_idx, (void*) (current_data->idx));
    }

    printf("Visited idx size: %d \n", visited_idx.size);
    //TODO:Free
    return visited_idx.size;
    // printf("\n ");
    // for(int i = 0; i<rows; i++){
    //     for(int j = 0; j < cols; j++) {
    //         int idx = asIdx(j, i, cols);
    //         if(contains(&visited_idx, (void*) ( idx))) {
    //             printf("# ");
    //         } else{
    //             printf(". ");
    //         }
    //     }
    //     printf("\n ");
    // }
}

void part_one() {
    File2d file2d = get_2d_file("../input/input.txt");
    solution(&file2d, create_beam(RIGHT, 0));
}

void part_two() {
    //TODO: Optimize
    File2d file2d = get_2d_file("../input/input.txt");
    int max_val = 0;
    //top to down, dir right
    Beam start_beam = {RIGHT, 0};
    for(int i = 0; i < file2d.rows; i++){
        start_beam.idx = asIdx(0, i, file2d.cols);
        start_beam.direction = RIGHT;
        int result = solution(&file2d, &start_beam);
        max_val = max_val < result ? result : max_val;
    }

    //left to right, dir up
    for(int i = 0; i < file2d.cols; i++){
        start_beam.idx = asIdx(i, file2d.rows-1, file2d.cols);
        start_beam.direction = UP;
        int result = solution(&file2d,&start_beam);
        max_val = max_val < result ? result : max_val;
    }
    //bot to top, dir left
    for(int i = file2d.rows - 1; i >= 0; i--){
        start_beam.idx = asIdx(file2d.cols -1, i, file2d.cols);
        start_beam.direction = LEFT;
        int result = solution(&file2d,&start_beam);
        max_val = max_val < result ? result : max_val;
    }

    //right to left, dir down
    for(int i = file2d.cols - 1; i >= 0; i--){
        start_beam.idx = asIdx(i, 0, file2d.cols);
        start_beam.direction = DOWN;
        int result = solution(&file2d,&start_beam);
        max_val = max_val < result ? result : max_val;
    }
    printf("max: %d\n", max_val);
}

#endif /* SOLUTION_H */
