#ifndef FILE_WORK_H
#define FILE_WORK_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define work_with_files(file_name)                  \
    FILE* filePtr = fopen(file_name, "r");          \
    if (filePtr == NULL) {                          \
        perror("Error opening file\n");             \
        goto end_file_work;                         \
    }                                               \
    int ch =-1;                                     \
    bool is_digit_found = false;                    \
    long number_holder = 0;                         \
    int sign_holder = 1;                            \
    int prevChar = -1;                           


#define file_read_loop()                                \
    while ((prevChar = ch) && (ch = getc(filePtr)) != EOF)  

#define if_last_line_not_handled if(prevChar != '\n' && ch == EOF) 

#define finish_file_work()                          \
end_file_work:                                      \
    fclose(filePtr);                                

#define rewind_file() rewind(filePtr)    

#define if_new_line                            if(ch == '\n')

#endif /* FILE_WORK_H */
