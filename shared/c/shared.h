#ifndef SHARED_H
#define SHARED_H

#ifdef NEED_SLICE
#include "slice.h"
#endif

#include "file_work.h"

int asIdx(int c, int r, int cols) {
    return r*cols +  c;
}

bool is_digit(char ch){
    return '0' <= ch && ch <= '9';
}
 
#define try_collect_number()                                    \
    if(!is_digit_found && ch == '-') sign_holder = -1;          \
    if(is_digit(ch)) {                                          \
        if(!is_digit_found) number_holder = 0;                  \
        is_digit_found = true;                                  \
        number_holder = number_holder * 10 + (ch - '0');        \
    } else if(!is_digit_found)  sign_holder = 1;                                                          


#define if_number_collected             \
    long number_tmp = number_holder;    \
    int  sign_tmp = sign_holder;        \
    number_holder = 0;                  \
    sign_holder = 1;                    \
    if(!is_digit_found) {               \
        number_holder = number_tmp;     \
        sign_holder = sign_tmp;         \
    } else                                         


#define get_collected_number() sign_tmp > 0 ? number_tmp : -number_tmp


typedef struct {
    long rows;
    long cols;
} File2dDimentions;
    
File2dDimentions get_rows_and_col_size(const char* file_name) {
    long rows = 0;
    long cols = 0;
    File2dDimentions error = (File2dDimentions) {0};

    work_with_files(file_name);
    file_read_loop() {
        if_new_line {
            cols++;
        } else if(cols == 0) {
            rows++;
        }
    }
    if_last_line_not_handled {
        cols++;
    }
    finish_file_work();

    return (File2dDimentions) {
        .rows = rows,
        .cols = cols
    };
}

typedef struct {
    long rows;
    long cols;
    long size;
    int* items;
} File2d;

File2d get_2d_file(const char* file_name) {

    File2d error = (File2d) {0};

    long rows = 0;
    long cols = 0;

    work_with_files(file_name);
    file_read_loop() {
        if_new_line {
            rows++;
        } else if(rows == 0) {
            cols++;
        }
    }
    if_last_line_not_handled {
        rows++;
    }

    rewind_file();
    int* items = malloc(rows*cols*sizeof(int));
    
    int i = 0;
    file_read_loop() {
        if_new_line {
            continue;
        }
        items[i++] = ch;
    }

    finish_file_work();

    return (File2d) {
        .rows = rows,
        .cols = cols,
        .size = rows*cols,
        .items= items
    };
}


typedef struct {
    long row;
    long col;
} LPosition2D;

typedef struct {
    int row;
    int col;
} Position2D;

int pos_to_idx(Position2D pos, int max_cols) {
    asIdx(pos.col, pos.row, max_cols);
}

#endif /* SHARED_H */
