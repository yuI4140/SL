#pragma once
#define NORMAL
#define DEF
#include "core.h"
typedef struct {size_t size;size_t capacity;void** data;} Array;
Array create_a(size_t capacity) {
    Array array;
    array.size = 0;
    array.capacity = capacity;
    array.data =nullptr;
    return array;
}
void pushBack_a(Array* array, void* data) {
    if (array->size == array->capacity) {
        array->capacity *= 2;
        array->data =data;
    }
    array->data[array->size++] = data;
}

void* get_a(Array *array, int index) {
    return array->data[index];
}

void set_a(Array* array, int index, void* data) {
    array->data[index]=0;
    array->data[index] = data;
}
