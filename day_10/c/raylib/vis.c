#ifndef VIS_H
#define VIS_H

#include <raylib.h>
#include "../solution.h"
#define WIDTH 1280
#define HEIGHT 1280

Color get_color(int i);
int* toColorGrid(File2d* file2d, Slice* slice);

int main(void) {
    InitWindow(WIDTH, HEIGHT, "PIPI");
    File2d file2d = get_2d_file("../../input/input.txt");
    Position2D start_position = {0,0};
     for(int i = 0; i < file2d.size; i++) {
        if (file2d.items[i] != 'S') continue;
        start_position.col = i%file2d.cols;
        start_position.row = i/file2d.rows;
        break;
    }
    //13894
    //6947
    Slice* slice = bfs(file2d.items, asIdx(start_position.col, start_position.row, file2d.cols), file2d.cols, file2d.rows);
    printf("slice size: %d \n", slice->size/2);
    int* color_grid = toColorGrid(&file2d, slice);
    int r_cols = file2d.cols*3;
    int r_rows = file2d.rows*3;
    int r_size = r_cols*r_rows;
    float cells_by_width = ((float)WIDTH)/r_cols;
    float cells_by_height = ((float)HEIGHT)/r_rows;
    float cell_size = cells_by_width<cells_by_height?cells_by_width:cells_by_height;
    printf("r_cols: %d, r_rows: %d\n", r_cols, r_rows);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        for (size_t i = 0; i < r_size; i++)
        {
            int ro = i/r_cols;
            int co = i%r_cols;

            Rectangle rect = {
                .x = co*cell_size,
                .y = ro*cell_size,
                .width = cell_size,
                .height = cell_size
            };
            DrawRectangleRec(rect, get_color(color_grid[i]));
        }
        
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}

#endif /* VIS_H */


/*
    [   ][   ][   ]
    [   ][ x ][ x  ]
    [   ][ x ][   ]



*/

#define EMPTY   0
#define GREEN_PIPE   1
#define DEFAULT 2
#define S_COLOR 3


void image(char a, int col, int* put) {
    switch (a)
    {
        case 'F': {
            put[4] = col;
            put[5] = col;
            put[7] = col;
            return;
        }
        case 'L': {
            put[1] = col;
            put[4] = col;
            put[5] = col;
            return;
        }
        case '7': {
            put[3] = col;
            put[4] = col;
            put[7] = col;
            return;
        }
        case 'J': {
            put[1] = col;
            put[4] = col;
            put[3] = col;
            return;
        }
        case '|': {
            put[1] = col;
            put[4] = col;
            put[7] = col;
            return;
        }
        case '-': {
            put[3] = col;
            put[4] = col;
            put[5] = col;
            return;
        }
        case 'S': {
            put[6] = S_COLOR;
            put[7] = S_COLOR;
            put[4] = S_COLOR;
            put[1] = S_COLOR;
            put[2] = S_COLOR;
            return;
        }
        default:
            printf("[ERROR] unhandled case\n");
            break;
    }
}

int* toColorGrid(File2d* file2d, Slice* slice) {
    int size = file2d->cols*file2d->rows;
    int r_cols = file2d->cols*3;
    int r_rows = file2d->rows*3;
    
    int* result = (int*) calloc(r_cols*r_rows, sizeof(int));

    for (size_t i = 0; i < size; i++)
    {
        if(file2d->items[i] == '.') continue;
        int put[9] = {0};
        int color = DEFAULT; 
        if(contains(slice, i)){
            color = GREEN_PIPE;
        }
       
        image(file2d->items[i], color, &put);
        
        int f_row = i/file2d->cols;
        int f_col = i%file2d->cols;

        int p = 0;
        for(int i = 3*f_row; i < 3*f_row + 3; i++) {
            for(int j = 3*f_col; j < 3*f_col + 3; j++) {
                int _idx = asIdx(j, i, r_cols);
                result[_idx] = put[p++];
            }
        }
    }
    return result;
    
}

Color get_color(int i) {
    switch (i)
    {
    case EMPTY: return RAYWHITE;
    case GREEN_PIPE: return GREEN;
    case DEFAULT: return BLACK;
    case S_COLOR: return RED;
    
    }
    return YELLOW;
}