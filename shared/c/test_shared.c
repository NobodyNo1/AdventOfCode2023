#include "shared.h"

void basics();
void numbers();

int main(void) {
    numbers();
    return 0;
}

void basics() {
    work_with_files("text.txt") {
        putchar(prevChar);
    }
    if_last_line_not_handled {
        printf("line ended abruptly");
    }
    finish_file_work();
}

void numbers() {
    work_with_files("text.txt") {
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