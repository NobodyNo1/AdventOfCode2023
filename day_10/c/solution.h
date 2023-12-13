#ifndef SOLUTION_H
#define SOLUTION_H

#include "common.h"
#include "rules.h"

void part_one();
void part_two();

void solve() {
    part_one();
    part_two();
}


bool connects(int a, int dir, int b) {
    if(a =='.' || b == '.') return false;
    
    switch (a)
    {
    case 'S': return S_connects(b, dir);
    case 'F': return F_connects(b, dir);
    case 'L': return L_connects(b, dir);
    case '7': return seven_connects(b, dir);
    case 'J': return J_connects(b, dir);
    case '|': return v_connects(b, dir);
    case '-': return h_connects(b, dir);
    default:
        printf("[ERROR] unhandled case: %c %d %c \n", a, dir, b);
        break;
    }
    return false;
}

typedef struct {
    int idx;
    int come_from_idx;
} Record;

Record* create_record(
    int idx,
    int come_from_idx
) {
    Record* record = (Record*) malloc(sizeof(Record));
    record->come_from_idx = come_from_idx;
    record->idx = idx;
    return record;
}

bool is_record_empty(Record* record) {
    return record->come_from_idx == record->idx;
}

bool is_record(Record record) {
    return record.come_from_idx == record.idx;
}

Slice* bfs(int* items, int origin_idx, int cols, int rows) {
    int size = cols*rows;
    // contains [idx] => came_from
    Record* visited_map = (Record*) malloc(sizeof(Record)* size);
    // contains [ids] => can go forward to
    Slice** forward_map = (Slice**) malloc(sizeof(Slice*)* size);
    for(int i = 0; i < size; ++i) {
        visited_map[i] = (Record) { -1, -1};
        forward_map[i] = new_slice(10);
    }
    Queue queue = create_queue();
    Record* origin = create_record(origin_idx, -1);
    push_back(&queue, origin);
    while (queue_size(&queue) != 0)
    {
        Record* current_record = (Record*) pop_front(&queue);
        int current_idx = current_record->idx;
        if(is_record(visited_map[current_idx])) {
            visited_map[current_idx].come_from_idx = current_record->come_from_idx;
            visited_map[current_idx].idx = current_record->idx;
            // bug!
            if(current_record->come_from_idx != -1)
                add_item(forward_map[current_record->come_from_idx], current_record->idx);
        } else {
            int current_char = items[current_idx];
            continue;
        }
        int current_char = items[current_idx];
        int cur_col = current_idx%cols;
        int cur_row = current_idx/cols;
        
        bool connected_with_something = false;
        int top     = cur_row - 1;
        printf("connects with: ");
        if (top >= 0)
        {
            int top_idx = asIdx(cur_col, top, cols); 
            int top_ch = items[top_idx];
            if(connects(current_char, TOP, top_ch)) {
                printf("top, ");
                connected_with_something = true;
                push_back(&queue, create_record(top_idx, current_idx));
            }
        }
        
        int bot     = cur_row + 1;
        if (bot < rows)
        {
            int bot_idx = asIdx(cur_col, bot, cols); 
            int bot_ch = items[bot_idx];
            if(connects(current_char, BOTTOM, bot_ch)) {
                printf("bot, ");
                connected_with_something = true;
                push_back(&queue, create_record(bot_idx, current_idx));
            }
        }

        int left    = cur_col - 1;
        if (left >= 0)
        {
            int left_idx = asIdx(left, cur_row, cols); 
            int left_ch = items[left_idx];
            if(connects(current_char, LEFT, left_ch)) {
                printf("left, ");
                connected_with_something = true;
                push_back(&queue, create_record(left_idx, current_idx));
            }
        }

        int right   = cur_col + 1;
        if (right < cols)
        {
            int right_idx = asIdx(right, cur_row, cols); 
            int right_ch = items[right_idx];
            if(connects(current_char, RIGHT, right_ch)) {
                printf("right, ");
                connected_with_something = true;
                push_back(&queue, create_record(right_idx, current_idx));
            }
        }
        if(!connected_with_something) {
            printf("nothing");
            //clean forward_map using visited_map
            int _idx = current_idx;
            while(true) {
                if(visited_map[_idx].come_from_idx == -1) break;
                int _come_from = visited_map[_idx].come_from_idx;
                remove_item(forward_map[_come_from],  _idx); // remove _idx
                if(forward_map[_come_from]->size == 0){
                    _idx = _come_from;
                } else {
                    break;
                }
            }
        }
        printf("\n");
    }
    printf("size: %d\n", forward_map[origin_idx]->size);
    // here we should end up with clean forward_map;
    Queue queue2 = create_queue();
    push_back(&queue2, origin_idx);
    int _pending_idx = -1;
    Slice* result = new_slice(100);
    int elements = 0;
    while(queue_size(&queue2) != 0) {
        int _idx = pop_front(&queue2);
        add_item(result, _idx);
        printf("elem: %d\n", elements++);
        // printf("idx: %d\n   linked: ", _idx);
        if(forward_map[_idx]->size == 0){
            if(_pending_idx == -1) {
                _pending_idx = _idx;
                // printf("pending: %d\n", _idx);
            }
            else {
                // printf("linked %d with %d\n", _idx, _pending_idx);
                add_item(forward_map[_idx], _pending_idx);
                break;
            }
        }
        for(int i = 0; i <   forward_map[_idx]->size; i++){
            // printf("%d, ", forward_map[_idx]->data[i]);
            push_back(&queue2, forward_map[_idx]->data[i]);
        }
        // printf("\n");
        if(_idx == 0) break;
        // if(forward_map[_idx]->size == 1){
        //     printf("good!\n");
        //     _idx = (int) forward_map[_idx]->data[0];
        // } else {
        //     printf("bad!\n");
        //     break;
        // }
    }
    printf("Size:%d \n", elements);
    return result;
}

void part_one() {
    File2d file2d = get_2d_file("../input/input.txt");
    Position2D start_position = {0,0};
    for(int i = 0; i < file2d.size; i++) {
        if (file2d.items[i] != 'S') continue;
        start_position.col = i%file2d.cols;
        start_position.row = i/file2d.rows;
        break;
    }
    bfs(file2d.items, asIdx(start_position.col, start_position.row, file2d.cols), file2d.cols, file2d.rows);
}

void part_two() {

}

/*
TODO: Learn about
   Shoelace formula

   Pick's theorem
*/

#endif /* SOLUTION_H */
