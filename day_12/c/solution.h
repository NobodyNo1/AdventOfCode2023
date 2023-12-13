#ifndef SOLUTION_H
#define SOLUTION_H

#include "common.h"

void part_one();
void part_two();

void solve() {
    part_one();
    part_two();
}

void part_one() {
    work_with_files("../input/input.txt");
    file_read_loop() {
        try_collect_number();
        if_new_line {
            if_number_collected {
                printf("%d, ", get_collected_number());
            }
        }
    }
    if_last_line_not_handled {
        printf("line ended abruptly");
    }
    finish_file_work();
}

void part_two() {

}

#endif /* SOLUTION_H */
