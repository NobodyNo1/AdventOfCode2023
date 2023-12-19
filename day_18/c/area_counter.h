#ifndef AREA_COUNTER_H
#define AREA_COUNTER_H

#include "common.h"


// Simple: BFS solutuin
long count_area(char* area, int start_col, int start_row,  int cols, int rows) {
    Slice queue = create_slice(1000);
    Slice visited = create_slice(1000);
    add_item(&queue, (void*)asIdx(start_col, start_row, cols));
    int _i = 0;
    while(queue.size != 0) {
        printf("i: %d\n", _i++);
        int current = (int) queue.data[0];
        remove_item(&queue, (void*)current);
         // printf("active_beams size: %d\n", active_beams.size);
        if(visited.size != 0) {
            bool is_found = false;
            for (int i = 0; i < visited.size; i++)
            {
                int vis_data = (int)visited.data[i];
                if(vis_data == current){
                    is_found = true;
                    break;
                }
            }
            if(is_found) continue;
        }
        area[current] = '#';
        add_item(&visited, (void*)current);
        int col = current%cols;
        int row = current/cols;

        int top     = row - 1 >= 0      ? row - 1 : -1;
        int bot     = row + 1 < rows    ? row + 1 : -1;
        int right   = col + 1 < cols    ? col + 1 : -1;
        int left    = col - 1 >= 0      ? col - 1 : -1;

        if(top != -1 ){
            int idx = asIdx(col, top, cols);
            if(area[idx] == '.'){
                add_item(&queue, (void*)idx);
            }
        }
        if(bot != -1 ){
            int idx = asIdx(col, bot, cols);
            if(area[idx] == '.'){
                add_item(&queue, (void*)idx);
            }
            
        }
        if(right != -1 ){
            int idx = asIdx(right, row, cols);
            if(area[idx] == '.'){
                add_item(&queue, (void*)idx);
            }
            
        }
        if(left != -1 ){
            int idx = asIdx(left, row, cols);
            if(area[idx] == '.'){
                add_item(&queue, (void*)idx);
            }
        }
    }

    int count = 0;
    for (size_t i = 0; i < cols*rows; i++)
    {
        if(area[i] == '#') count++;
    }
    printf("area: %d \n", count);
    return count;
}


#endif /* AREA_COUNTER_H */

//TODO: https://en.wikipedia.org/wiki/Shoelace_formula

//LPos2d
long shoelace_area(Slice* slice) {
    // long area = 0;
    // for(int i = 0; i < slice->size; i++){
    //     int a_idx = i;
    //     int b_idx = i+1;
    //     if(b_idx == slice->size){
    //         b_idx = 0;
    //     }
    //     long det = 
    // }
    return 0;
}
