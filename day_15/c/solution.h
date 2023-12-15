#ifndef SOLUTION_H
#define SOLUTION_H

#include "common.h"

void part_one();
void part_two();

void solve() {
    part_one();
    part_two();
}

int hash(char* text) {
    int current_value = 0;
    int i = 0;
    while(text[i] != '\0') {
        current_value += text[i];
        current_value *= 17;
        current_value %= 256;
        i++;
    }
    return current_value;
}

int hash_chars(char* text) {
    int i = 0;
    long result = 0;
    char buffer[256]; 
    int j = 0;
    while(text[i] != '\0') {
        if(text[i] == '\n') continue;
        if(text[i] == ',') {
            buffer[j] = '\0';
            result += hash(buffer);
            j = 0;
            i++;
            continue;
        }
        buffer[j] = text[i];
        j++;
        i++;
        if(j >= 256) {
            printf("PANIC: Exceeded buffer size\n");
            return 0;
        }
    }
    if(j!=0){
        buffer[j] = '\0';
        result += hash(buffer);
    }
    return result;
}

void part_one() {
    long result = 0;
    char buffer[256]; 
    int j = 0;
    work_with_files("../input/input.txt");
    file_read_loop() {
        if_new_line {
            continue;
        }
        if(ch == ',') {
            buffer[j] = '\0';
            result += hash(buffer);
            j = 0;
            continue;
        }
        buffer[j] = ch;
        j++;
        if(j >= 256) {
            printf("PANIC: Exceeded buffer size\n");
            return;
        }
    }
    if_last_line_not_handled {
        buffer[j] = '\0';
        result += hash(buffer);
    }
    printf("result: %ld\n", result);
    finish_file_work();
}

typedef struct
{
    char* name;
    int value;
} Label;


Label *create_label() {
    Label* label = (Label*) malloc(sizeof(Label));
    label->name = (char*) malloc(sizeof(char)*256);
    return label;
}

void remove_from_map(Slice* map, Label* label){
    if(map->size == 0) {
        return;
    }
    int i = 0;
    while(i < map->size){
        Label* cur_label = (Label*)(map->data[i]);
        if(text_equals(cur_label->name, label->name)) break;
        i++;
    }
    if(i == map->size) {
        return;
    }
    remove_item(map, map->data[i]);
}

void add_to_map(Slice* map, Label* label) {
    if(map->size == 0) {
        add_item(map, label);
        return;
    }
    int i = 0;
    while(i < map->size){
        Label* cur_label = (Label*)(map->data[i]);
        if(text_equals(cur_label->name, label->name)) break;
        i++;
    }
    if(i == map->size) {
        add_item(map, label);
        return;
    }
    ((Label*)map->data[i])->value = label->value;
}

void part_two() {
    Slice* hash_map[256];
    for(int i = 0; i < 256; i++){
        hash_map[i] = new_slice(10);
    }
    bool operation_add = false;
    int j = 0;
    Label* label = create_label();
    work_with_files("../input/input.txt");
    file_read_loop() {
        if_new_line {
            continue;
        }
        if(ch == ',') {
            label->name[j] = '\0';
            if(operation_add){
               add_to_map(hash_map[hash(label->name)], label);
            } else{
               remove_from_map(hash_map[hash(label->name)], label);
            }
            label = create_label();
            j = 0;
            continue;
        }
        if(ch == '-') {
            operation_add = false;
        } else if(ch == '=') {
            operation_add = true;
        }
        else if(is_digit(ch)) {
            label->value = ch - '0';
        } else {
            label->name[j] = ch;
        }
        j++;
        if(j >= 256) {
            printf("PANIC: Exceeded buffer size\n");
            return;
        }
    }
    if(j!=0) {
        label->name[j] = '\0';
        if(operation_add){
            add_to_map(hash_map[hash(label->name)], label);
        } else{
            remove_from_map(hash_map[hash(label->name)], label);
        }
    }
    long result = 0;
    for(int i = 0; i <256; i++){
        if(hash_map[i]->size==0) continue;
        for(int j = 0; j < hash_map[i]->size; j++) {
            Label* cur_label = ((Label*) hash_map[i]->data[j]);
            result += (i+1) * (j+1) * ( cur_label->value);
        }
    }
    printf("result: %ld\n", result);
    finish_file_work();
}

#endif /* SOLUTION_H */
